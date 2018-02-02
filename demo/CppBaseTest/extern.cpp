#include "extern.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78941738

extern std::string extern_variable_blog_addr;
extern std::string extern_variable_github_addr;
extern int extern_function_add(int a, int b);
extern const std::string extern_function_name();

namespace extern_ {

namespace {
	int fcn() { return 0; }
}

extern double pi = 3.1415; // 定义

/* reference: C++ Primer(Fifth 中文版) pages 63
某些时候有这样一种const变量，它的初始值不是一个常量表达式，但又确实有必要在文件间共享。
这种情况下，我们不希望编译器为每个文件分别生成独立的变量。相反，我们想让这类const对象
像其它(非常量)对象一样工作，也就是说，只在一个文件中定义const，而在其它多个文件中声明
并使用它。解决的办法是，对于const变量不管是声明还是定义都添加extern关键字，这样只需定义一次就可以了
*/
extern const int bufsize = fcn();

int test_extern_1()
{
	extern int i; // 声明i而非定义i
	int j; // 声明并定义j
	//extern double pi = 3.1415; // 定义,在函数体内部，如果试图初始化一个由extern关键字标记的变量，将引发错误

	return 0;
}

int test_extern_2()
{
	fprintf(stdout, "blob addr: %s\n", extern_variable_blog_addr.c_str());
	fprintf(stdout, "github addr: %s\n", extern_variable_github_addr.c_str());

	fprintf(stdout, "a + b = %d\n", extern_function_add(2, 3));

	fprintf(stdout, "name: %s\n", extern_function_name().c_str());

	return 0;
}

} // namespace extern_

