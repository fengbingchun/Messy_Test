#include <iostream>
#include "common.hpp"

int main()
{
	if (auto ret = test_template_argument_auto(); ret == 0)
		std::cout << "========== test success ==========\n";
	else
		std::cerr << "########## test fail ##########\n";

	return 0;
}
