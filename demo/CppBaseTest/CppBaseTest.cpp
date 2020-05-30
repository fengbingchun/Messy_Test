#include <iostream>
#include "common.hpp"

int main()
{
	int ret = cplusplus_secure_coding_::test_secure_coding_5();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
