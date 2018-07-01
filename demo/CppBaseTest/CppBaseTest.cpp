#include <iostream>
#include "common.hpp"

int main()
{
	int ret = static_::test_static_7();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
