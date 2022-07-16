#include <iostream>
#include "common.hpp"

int main()
{
	int ret = lazy_evaluation_::test_evaluation_2();
	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
