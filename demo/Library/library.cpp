#include "library.hpp"
#include <iostream>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78825004

FBC_API int library_add(int a, int b)
{
	value = 11;

	fprintf(stdout, "File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
	return (a+b);
}

template<typename T>
void Simple<T>::Init(T a, T b)
{
	this->a = a;
	this->b = b;
}

template<typename T>
T Simple<T>::Add() const
{
	fprintf(stdout, "File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
	return (a + b);
}

template class Simple<int>;
template class Simple<std::string>;
