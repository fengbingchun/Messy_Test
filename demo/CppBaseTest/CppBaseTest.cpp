#include <iostream>
#include "common.hpp"

int main()
{
	int ret = cplusplus_api_design_::test_api_design_12();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
