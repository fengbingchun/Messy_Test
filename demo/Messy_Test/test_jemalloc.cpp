#include "funset.hpp"
#include <iostream>
#include <jemalloc/jemalloc.h>

// define to jemalloc
#define malloc(size) je_malloc(size)
#define calloc(nmemb, size) je_calloc(nmemb, size)
#define realloc(ptr, size) je_realloc(ptr, size)
#define free(ptr) je_free(ptr)

// Blog: https://blog.csdn.net/fengbingchun/article/details/109700652

int test_jemalloc()
{
	char* a = static_cast<char*>(malloc(10));
	if (!a) {
		fprintf(stderr, "fail to malloc\n");
		return -1;
	}
	free(a);

	return 0;
}
