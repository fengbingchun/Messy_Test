#include <iostream>
#include "common.hpp"

int main()
{
	int ret = memory_::test_enable_shared_from_this_4();
	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
