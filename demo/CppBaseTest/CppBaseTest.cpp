#include <iostream>
#include "common.hpp"

int main()
{
	int ret = binary_search_tree_::test_binary_search_tree();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
