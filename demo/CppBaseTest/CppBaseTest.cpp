#include <iostream>
#include "common.hpp"

int main()
{
	if (auto ret = test_lambda_20_parameter_pack(); ret == 0)
		std::cout << "========== test success ==========\n";
	else
		std::cerr << "########## test fail ##########\n";

	return 0;
}
