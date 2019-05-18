#include <iostream>
#include "common.hpp"

int main()
{
	int ret = coding_optimizations_::test_coding_optimizations_1();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
