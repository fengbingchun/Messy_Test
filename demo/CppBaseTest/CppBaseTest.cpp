#include <iostream>
#include "common.hpp"

int main()
{
	int ret = operator_new_::test_operator_new_5();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
