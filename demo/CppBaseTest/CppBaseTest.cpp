#include <iostream>
#include "common.hpp"

int main()
{
	int ret = virtual_function_table_::test_virtual_function_table_1();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
