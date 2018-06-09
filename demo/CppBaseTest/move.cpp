#include "move.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52558914

//////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/utility/move
int test_move1()
{
	std::string str = "Hello";
	std::vector<std::string> v;

	// uses the push_back(const T&) overload, which means we'll incur the cost of copying str
	v.push_back(str);
	std::cout << "After copy, str is \"" << str << "\"\n";

	// uses the rvalue reference push_back(T&&) overload, which means no strings will be copied;
	// instead, the contents of str will be moved into the vector.
	// This is less expensive, but also means str might now be empty.
	v.push_back(std::move(str));
	std::cout << "After move, str is \"" << str << "\"\n";

	std::cout << "The contents of the vector are \"" << v[0] << "\", \"" << v[1] << "\"\n";

	return 0;
}

////////////////////////////////////////////////////
// reference: http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/
void ProcessValue(int& i)
{
	std::cout << "LValue processed: " << i << std::endl;
}

void ProcessValue(int&& i)
{
	std::cout << "RValue processed: " << i << std::endl;
}

int test_move2()
{
	int a = 0;
	ProcessValue(a);
	// std::move函数可以以非常简单的方式将左值引用转换为右值引用
	ProcessValue(std::move(a));

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/utility/move/
int test_move3()
{
	std::string foo = "foo-string";
	std::string bar = "bar-string";
	std::vector<std::string> myvector;

	// The first call to myvector.push_back copies the value of foo into
	// the vector (foo keeps the value it had before the call).
	// The second call moves the value of bar into the vector.
	// This transfers its content into the vector(while bar loses its value,
	// and now is in a valid but unspecified state)
	myvector.push_back(foo);                    // copies
	myvector.push_back(std::move(bar));         // moves

	std::cout << "myvector contains:";
	for (std::string& x : myvector)
		std::cout << ' ' << x;
	std::cout << '\n';

	return 0;
}
