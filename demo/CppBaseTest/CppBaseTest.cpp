#include <iostream>
#include "common.hpp"

int main()
{
	int ret = cplusplus_secure_coding_::test_secure_coding_8();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
