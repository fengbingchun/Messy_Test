#include <iostream>
#include "common.hpp"

int main()
{
	int ret = functional_::test_functional_is_placeholder();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
