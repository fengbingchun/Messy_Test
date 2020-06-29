#include <iostream>
#include "common.hpp"

int main()
{
	int ret = time_::test_gmtime_localtime();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
