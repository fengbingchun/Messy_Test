#include <iostream>
#include "common.hpp"

int main()
{
	int ret = test_string_ifstream_to_string();

	if (ret == 0) fprintf(stderr, "test success\n");
	else fprintf(stderr, "test fail\n");

	return 0;
}
