#include <iostream>
#include <string>
#include "funset.hpp"

int main()
{
	int ret = test_miniz_2();
	if (ret == 0)
		std::cout << "ok" << std::endl;
	else
		std::cout << "fail" << std::endl;

	return 0;
}
