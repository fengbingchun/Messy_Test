#include <iostream>
#include "common.hpp"

int main()
{
	int ret = extern_c_::test_extern_c_1();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
