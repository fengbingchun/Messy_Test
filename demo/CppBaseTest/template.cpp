#include <iostream>
#include "template.hpp"

void test_template1()
{
	int a = 3, b = 7;
	float x = 3.0, y = 7.0;
	//Calling template function
	std::cout << maximum<int>(a, b) << std::endl; //输出 7
	std::cout << maximum(a, b) << std::endl; //自动补充类型声明,输出 7
	std::cout << maximum<double>(x, y) << std::endl; //输出 7
}
