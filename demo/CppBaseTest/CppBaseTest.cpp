#include <iostream>
#include "common.hpp"

int main()
{
	int ret = nested_class_::test_nested_class_7();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
