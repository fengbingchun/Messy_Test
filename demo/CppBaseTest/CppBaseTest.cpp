#include <iostream>
#include "explicit.hpp"
#include "this_pointer.hpp"
#include "static_assert.hpp"

int main()
{
	test_static_assert2();

	std::cout << "ok" << std::endl;
	return 0;
}
