#include <iostream>
#include "common.hpp"

int main()
{
	int ret = iterator_::test_iterator_20();

	if (ret == 0) fprintf(stderr, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
