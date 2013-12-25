#include "cache.h"
#include "loader.h"
#include "sim.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

cache_t cache;

static void test_helper()
{
	assert(ALIGN(16, 16) == 16);
	assert(ALIGN(33, 4) == 32);
}

int main()
{
	mem_init();
	test_helper();
	cache_init(&cache, 2, 4, 4);

	int numbers[] = {1, 2, 3, 4};
	cache_write(&cache, 0x0, (char *)numbers, sizeof(numbers));
	int b = 0;
	cache_fetch(&cache, (char *)&b, 0x0, 4);
	assert(b == 1);
	cache_fetch(&cache, (char *)&b, 0x4, 4);
	assert(b == 2);
	cache_fetch(&cache, (char *)&b, 0x8, 4);
	assert(b == 3);
	cache_fetch(&cache, (char *)&b, 0xc, 4);
	assert(b == 4);


	int number = 10;
	cache_write(&cache, 0x4, (char *)&number, sizeof(number));
	cache_fetch(&cache, (char *)&b, 0x4, 4);
	assert(b == 10);

	char *bytes = "1234567890qwertyuiopasdfghjkl;zxcvbnm,.";
	char c;
	cache_write(&cache, 0x58, bytes, strlen(bytes) + 1);

	cache_fetch(&cache, &c, 0x58, 1);
	assert(c == '1');
	cache_fetch(&cache, &c, 0x58+1, 1);
	assert(c == '2');
	cache_fetch(&cache, &c, 0x58+2, 1);
	assert(c == '3');
	cache_fetch(&cache, &c, 0x58+12, 1);
	assert(c == 'e');
	cache_fetch(&cache, &c, 0x58+16, 1);

	printf("hit: %d, miss: %d\n", cache.nhit, cache.nmiss);
	printf("cache test passed.\n");
	mem_destroy();
}
