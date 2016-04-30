#include <iostream>
#include "explicit.hpp"
#include "this_pointer.hpp"
#include "static_assert.hpp"
#include "static_inline.hpp"
#include "static_cast.hpp"
#include "istream.hpp"

int main()
{
	test_istream();

	std::cout << "ok" << std::endl;
	return 0;
}
