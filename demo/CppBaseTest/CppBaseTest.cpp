#include <iostream>
#include "explicit.hpp"
#include "this_pointer.hpp"
#include "static_assert.hpp"
#include "static_inline.hpp"
#include "static_cast.hpp"
#include "istream.hpp"
#include "operator.hpp"

int main()
{
	test_operator();

	std::cout << "ok" << std::endl;
	return 0;
}
