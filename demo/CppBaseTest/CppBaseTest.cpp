#include <iostream>
#include "common.hpp"

int main()
{
	int ret = test_this_thread_yield();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "********** test fail **********\n");

	return 0;
}
