#include <iostream>
#include "common.hpp"

int main()
{
	int ret = call_once_::test_call_once_3();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
