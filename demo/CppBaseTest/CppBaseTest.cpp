#include <iostream>
#include "common.hpp"

int main()
{
	int ret = class_::test_class3();
	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
