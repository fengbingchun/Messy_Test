#include "static.hpp"
#include <iostream>

///////////////////////////////////////////////////////////
size_t count_calls()
{
	// 局部静态对象(local static object)在程序的执行路径第一次经过对象定义
	// 语句时初始化,并且直到程序终止才被销毁，在此期间即使对象所在的函数结
	// 束执行也不会对它有影响。
	static size_t ctr = 0; // 调用结束后，这个值仍然有效
	return ++ctr;
}

int test_static_1()
{
	for (int i = 0; i < 10; ++i) {
		std::cout << count_calls() << std::endl;
	}

	return 0;
}

