#include <iostream>
#include "common.hpp"

int main()
{
	int ret = variable_arguments_::test_variable_arguments_template_function_3();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
