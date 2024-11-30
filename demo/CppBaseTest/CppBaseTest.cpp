#include <iostream>
#include "common.hpp"

int main()
{
	if (auto ret = test_calling_convention(); ret == 0)
		std::cout << "========== test success ==========\n";
	else
		std::cerr << "########## test fail ##########\n";

	return 0;
}
