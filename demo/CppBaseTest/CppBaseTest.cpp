#include <iostream>
#include "common.hpp"

int main()
{
	int ret = cmath_::test_cmath_compare();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
