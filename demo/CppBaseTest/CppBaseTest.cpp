#include <iostream>
#include "common.hpp"

int main()
{
	int ret = emplace_::test_emplace_4();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
