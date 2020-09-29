#include <iostream>
#include "common.hpp"

int main()
{
	int ret = get_mac_and_cpuid();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
