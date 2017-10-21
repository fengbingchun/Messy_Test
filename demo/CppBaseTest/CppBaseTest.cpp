#include <iostream>
#include "common.hpp"

int main()
{
	int ret = exception_::test_exception_3();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
