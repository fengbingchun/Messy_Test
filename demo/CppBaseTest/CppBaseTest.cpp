#include <iostream>
#include "common.hpp"

int main()
{
	int ret = atomic::test_atomic_flag_atomic_clear();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "********** test fail **********\n");

	return 0;
}
