#include <iostream>
#include "funset.hpp"

int main()
{
	if (auto ret = test_sqlite(); ret == 0)
		std::cout << "========== test success ==========\n";
	else
		std::cerr << "########## test fail ##########\n";

	return 0;
}

