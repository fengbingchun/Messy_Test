#include "extern2.hpp"

std::string extern_variable_blog_addr{ "http://blog.csdn.net/fengbingchun" };
std::string extern_variable_github_addr{ "https://github.com/fengbingchun" };

int extern_function_add(int a, int b)
{
	return (a + b);
}

extern const std::string extern_function_name()
{
	return "C++";
}

