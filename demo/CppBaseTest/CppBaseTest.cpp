#include <iostream>
#include "common.hpp"

int main()
{
	int ret = more_effective_cplusplus_::test_item_30();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
