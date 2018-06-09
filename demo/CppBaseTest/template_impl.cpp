#include <iostream>
#include "template.hpp"

template <typename T>
const T& max_mum(const T& x, const T& y)
{
	if (y > x){
		return y;
	}
	else{
		return x;
	}
}

// 函数模板声明与定义分开：函数模板显示实例化
template const int& max_mum<int>(const int&, const int&);

template<class T>
void A<T>::f()
{
	std::cout << " template class impl" << std::endl;
}

// 类模板声明与定义分开：类模板显示实例化
template class A < int > ;
