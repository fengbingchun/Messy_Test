#include <iostream>
#include "common.hpp"

int main()
{
	int ret = test_chrono_time_point();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "********** test fail **********\n");

	return 0;
}
