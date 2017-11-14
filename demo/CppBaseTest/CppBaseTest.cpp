#include <iostream>
#include "common.hpp"

int main()
{
	int ret = enum_class_::test_enum_class_3();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
