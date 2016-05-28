#include <iostream>
#include "explicit.hpp"
#include "this_pointer.hpp"
#include "static_assert.hpp"
#include "static_inline.hpp"
#include "static_cast.hpp"
#include "istream.hpp"
#include "operator.hpp"
#include "template.hpp"
#include "data_type_convert.hpp"
#include "vector.hpp"

int main()
{
	test_vector_access();

	std::cout << "\nok" << std::endl;
	return 0;
}
