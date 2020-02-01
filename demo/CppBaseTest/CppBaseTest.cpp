#include <iostream>
#include "common.hpp"

int main()
{
	int ret = future_::test_async_3();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
