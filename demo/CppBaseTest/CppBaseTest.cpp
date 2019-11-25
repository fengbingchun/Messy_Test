#include <iostream>
#include "common.hpp"

int main()
{
	int ret = effective_stl_::test_item_46();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
