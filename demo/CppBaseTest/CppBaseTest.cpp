#include <iostream>
#include "common.hpp"

int main()
{
	int ret = operator_::test_operator_6();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
