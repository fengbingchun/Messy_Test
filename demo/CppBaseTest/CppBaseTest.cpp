#include <iostream>
#include "common.hpp"

int main()
{
	int ret = memory_alignment_::test_memory_alignment_4();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
