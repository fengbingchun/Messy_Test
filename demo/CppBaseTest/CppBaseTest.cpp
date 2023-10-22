#include <iostream>
#include "common.hpp"

int main()
{
	int ret = test_string_view_functions();
	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
