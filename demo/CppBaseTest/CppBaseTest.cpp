#include <iostream>
#include "common.hpp"

int main()
{
	int ret = signal_::test_signal_SIGINT();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
