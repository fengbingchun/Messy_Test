#include <iostream>
#include "common.hpp"

int main()
{
	int ret = numeric_::test_numeric_iota();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
