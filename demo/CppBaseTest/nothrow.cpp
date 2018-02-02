#include "nothrow.hpp"
#include <iostream>
#include <new> // std::nothrow

// Blog: http://blog.csdn.net/fengbingchun/article/details/63686673

// reference: http://www.cplusplus.com/reference/new/nothrow/
int test_nothrow1()
{
	std::cout << "Attempting to allocate 1 MiB...";
	char* p = new (std::nothrow) char[1048576];
	if (p == 0)
		std::cout << "Failed!\n";
	else {
		std::cout << "Succeeded!\n";
		delete[] p;
	}

	return 0;
}

// reference: http://en.cppreference.com/w/cpp/memory/new/nothrow
int test_nothrow2()
{
	try {
		while (true) {
			new int[100000000ul];   // throwing overload
		}
	}
	catch (const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
	}

	while (true) {
		int* p = new(std::nothrow) int[100000000ul]; // non-throwing overload
		if (p == nullptr) {
			std::cout << "Allocation returned nullptr\n";
			break;
		}
	}

	return 0;
}
