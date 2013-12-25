#ifndef CACHE_H
#define CACHE_H
#define MAX_BLOCK_SIZE 256
#define MAX_SET_SIZE 256
#define MAX_CL_SIZE 64
#define ALIGN(address, n) (address & (~(n-1)))

typedef struct {
	int valid;
	int tag;
	int atcycle;
} cache_line_t;

typedef struct {
	int s;
	int S;
	int b;
	int B;
	int E;
	int t;
	int nmiss;
	int nhit;
	cache_line_t lines[MAX_SET_SIZE][MAX_CL_SIZE];
} cache_t;

extern cache_t icache;
extern cache_t dcache;

int cache_init(cache_t *cache, int s, int b, int E);
int cache_fetch(cache_t *cache, char *dest, int src, int size);
int cache_write(cache_t *cache, int dest, char *sdsrc, int size);
void check_cache(cache_t *cache);
extern int ncycle;

#endif
