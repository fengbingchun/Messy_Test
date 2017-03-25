#include <iostream>
#include "common.hpp"

int main()
{
	int ret = test_exception7();

	if (ret == 0) fprintf(stderr, "test success\n");
	else fprintf(stderr, "test fail\n");

	return 0;
}
