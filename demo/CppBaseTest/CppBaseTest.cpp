#include <iostream>
#include "common.hpp"

int main()
{
	int ret = unique_ptr_::test_unique_ptr12();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
