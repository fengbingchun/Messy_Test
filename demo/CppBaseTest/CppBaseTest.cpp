#include <iostream>
#include "common.hpp"

int main()
{
	int ret = condition_variable_::test_condition_variable_2();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "********** test fail **********\n");

	return 0;
}
