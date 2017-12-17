#include "test_library.hpp"
#include <iostream>
#include <string>

#include <library.hpp>

namespace test_library_ {

int test_library_1()
{
	int a{ 4 }, b{ 5 }, c{ 0 };

	c = library_add(a, b);
	fprintf(stdout, "%d + %d = %d\n", a, b, c);
	fprintf(stdout, "value: %d\n", value);

	return 0;
}

int test_library_2()
{
	Simple<int> simple1;
	int a{ 4 }, b{ 5 }, c{ 0 };

	simple1.Init(a, b);
	c = simple1.Add();
	fprintf(stdout, "%d + %d = %d\n", a, b, c);

	Simple<std::string> simple2;
	std::string str1{ "csdn blog: " }, str2{ "http://blog.csdn.net/fengbingchun" }, str3;

	simple2.Init(str1, str2);
	str3 = simple2.Add();
	fprintf(stdout, "contents: %s\n", str3.c_str());

	return 0;
}

int test_library_3()
{
	return 0;
}

int test_library_4()
{
	return 0;
}

} // namespace test_library_
