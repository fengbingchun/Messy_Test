#include <iostream>
#include "common.hpp"

int main()
{
	int ret = effective_modern_cplusplus_::test_item_25();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
