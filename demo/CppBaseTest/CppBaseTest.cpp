#include <iostream>
#include "common.hpp"

int main()
{
	int ret = lvalue_rvalue_::test_lvalue_rvalue_7();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
