#include <iostream>
#include "common.hpp"

int main()
{
	int ret = type_traits_::test_type_traits_type_transformations();
	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
