#include <iostream>
#include "common.hpp"

int main()
{
	int ret = local_class_::test_local_class_7();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
