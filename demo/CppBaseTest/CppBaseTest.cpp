#include <iostream>
#include "common.hpp"

int main()
{
	int ret = test_thread_hardware_concurrency();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
