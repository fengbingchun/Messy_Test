#include <iostream>
#include "common.hpp"

int main()
{
	int ret = variable_arguments_::test_variable_arguments_macro_3();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
