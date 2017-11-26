#include <iostream>
#include "common.hpp"

int main()
{
	int ret = unique_lock_::test_unique_lock_10();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
