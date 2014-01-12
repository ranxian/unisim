#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cache.h"
#include "helper.h"
#include "memory.h"
#include <stdio.h>

#define ALIGN(address, n) (address & (~(n-1)))

static int extract_s(cache_t *cache, int n)
{
	return bits(n, cache->b, cache->b + cache->s - 1);
}

static int extract_b(cache_t *cache, int n)
{
	return bits(n, 0, cache->b - 1);
}

static int extract_tag(cache_t *cache, int n)
{
	return bits(n, cache->b + cache->s, 31);
}

static int combine(cache_t *cache, int b, int s, int tag)
{
	int res;
	res = b;
	res |= s << cache->b;
	res |= tag << (cache->b + cache->s);
	return res;
}

static int power2(int n)
{
	int res = 1;
	while (n--)
		res *= 2;
	return res;
}

static int log22(int n)
{
	int res = 0;
	while ((n /= 2) != 0)
		res++;
	return res;
}

int cache_init(cache_t * cache, int s, int b, int E)
{
	cache->s = s;
	cache->b = b;
	cache->E = E;
	cache->S = power2(s);
	cache->B = power2(b);
	cache->t = 32 - s - b;
	cache->nmiss = cache->nhit = cache->ndirty = 0;
	int i, j;
	for (i = 0; i < cache->S; i++) {
		for (j = 0; j < cache->E; j++) {
			cache->lines[i][j].valid = 0;
			cache->lines[i][j].atcycle = 0;
			cache->lines[i][j].dirty = 0;
		}
	}
	return 0;
}

static cache_line_t *find_line(cache_t *cache, int address)
{
	int S = extract_s(cache, address);
	int tag = extract_tag(cache, address);

	int i;
	for (i = 0; i < cache->E; i++) {
		cache_line_t *line;		
		line = &cache->lines[S][i];
		if (line->valid && line->tag == tag) {
			line->atcycle = ncycle;
			return line;
		}
	}
	return NULL;
}

static int cache_insert(cache_t *cache, int address)
{
	address = ALIGN(address, cache->B);
	int S = extract_s(cache, address);
	int tag = extract_tag(cache, address);
	int i;
	for (i = 0; i < cache->E; i++) {
		cache_line_t *line = &cache->lines[S][i];
		if (line->valid == 0) {
			line->valid = 1;
			line->tag = tag;
			line->atcycle = ncycle;
			return 0;
		}
	}

	cache_line_t *out = NULL;
	int recent = ncycle + 1;
	for (i = 0; i < cache->E; i++) {
		cache_line_t *line = &cache->lines[S][i];
		if (line->atcycle < recent) {
			recent = line->atcycle;
			out = line;
		}
	}

	if (out) {
		if (out->dirty)
			cache->ndirty++;
		out->dirty = 0;
		out->tag = tag;
		out->atcycle = ncycle;
	}
	else printf("cache_insert panic!\n");
	return 0;
}

static int cache_fetchw(cache_t *cache, char *dest, int src)
{
	cache_line_t *line = find_line(cache, src);
	if (line != NULL) {
		cache->nhit++;
		mem_read(src, dest, 4);
	} else {
		cache->nmiss++;
		mem_read(src, dest, 4);
		cache_insert(cache, src);
	}
	return 0;
}

static int cache_writew(cache_t *cache, int dest, char *dsrc)
{
	cache_line_t *line = find_line(cache, dest);
	mem_write(dest, dsrc, 4);
	if (line != NULL) {
		line->dirty = 1;
		return 0;
	} else {
		cache_insert(cache, dest);
		return 1;
	}
}

int cache_fetch(cache_t *cache, char *dest, int src, int size)
{
	while (size > 0) {
		cache_fetchw(cache, dest, src);
		dest += 4; src += 4; size -= 4;
	}
	return 0;
}

int cache_write(cache_t *cache, int dest, char *dsrc, int size)
{
	int first = 1;
	while (size > 0) {
		int missed = cache_writew(cache, dest, dsrc);
		if (missed && first) { 
			cache->nmiss += 1;
			first = 0;
		}
		dest += 4; dsrc += 4; size -= 4;
	}

	return 0;
}

void check_cache(cache_t *cache)
{
	int i, j, k, tag;
	for (i = 0; i < cache->S; i++) {
		for (j = 0; j < cache->E - 1; j++) {
			if (cache->lines[i][j].valid)
				tag = cache->lines[i][j].tag;
			else continue;
			for (k = j + 1; k < cache->E; k++) {
				assert(!(cache->lines[i][k].valid && cache->lines[i][k].tag == tag));
			}
		}
	}
}
