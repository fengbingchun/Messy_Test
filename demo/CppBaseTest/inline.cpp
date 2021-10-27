#include "inline.hpp"
#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <cmath>

// Blog: https://blog.csdn.net/fengbingchun/article/details/85030305

namespace inline_ {

// reference: 《提高C++性能的编程技术》：第八、九、十章：内联
//////////////////////////////////////////////////////////////
void generator_random_number(double* data, int length, double a, double b)
{
	//std::random_device rd; std::mt19937 generator(rd()); // 每次产生不固定的不同的值
	std::default_random_engine generator; // 每次产生固定的不同的值
	std::uniform_real_distribution<double> distribution(a, b);
	for (int i = 0; i < length; ++i) {
		data[i] = distribution(generator);
	}
}

double calc1(double a, double b) // 非内联
{
	return (a+b);
}

inline double calc2(double a, double b) // 内联
{
	return (a+b);
}

int test_inline_1()
{
	using namespace std::chrono;
	high_resolution_clock::time_point time_start, time_end;
	const int count{2000};
	const int cycle_number1{count}, cycle_number2{count}, cycle_number3{count};
	double x[count], y[count], z1[count], z2[count];

	generator_random_number(x, count, -1000., 1000.);
	generator_random_number(y, count, -10000, 10000.);
 
{ // 测试简单的非内联函数调用执行时间
	time_start = high_resolution_clock::now();
	for (int j = 0; j < cycle_number1; ++j) {
		for (int i = 0; i < cycle_number2; ++i) {
			for (int k = 0; k < cycle_number3; ++k) {
				z1[i] = calc1(x[k], y[k]);
			}
		}
	}
	time_end = high_resolution_clock::now();
 
	fprintf(stdout, "z1: %f, %f, %f, no inline calc time spent: %f seconds\n",
		 z1[0], z1[1], z1[2], (duration_cast<duration<double>>(time_end - time_start)).count());
}

{ // 测试简单的内联函数调用执行时间
	time_start = high_resolution_clock::now();
	for (int j = 0; j < cycle_number1; ++j) {
		for (int i = 0; i < cycle_number2; ++i) {
			for (int k = 0; k < cycle_number3; ++k) {
				z2[i] = calc2(x[k], y[k]);
			}
		}
	}
	time_end = high_resolution_clock::now();
 
	fprintf(stdout, "z2: %f, %f, %f, inline calc time spent: %f seconds\n",
		z2[0], z2[1], z2[2], (duration_cast<duration<double>>(time_end - time_start)).count());
}

	return 0;
}

} // namespace inline_

