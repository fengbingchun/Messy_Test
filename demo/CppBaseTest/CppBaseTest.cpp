#include <iostream>
#include "common.hpp"

int main()
{
	int ret = single_threaded_memory_pool_::test_single_threaded_memory_pool_1();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
