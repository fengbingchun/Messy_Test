#include <iostream>
#include "common.hpp"

int main()
{
	if (auto ret = inline_::test_inline_variable_1(); ret == 0)
		std::cout << "========== test success ==========\n";
	else
		std::cerr << "########## test fail ##########\n";

	return 0;
}
