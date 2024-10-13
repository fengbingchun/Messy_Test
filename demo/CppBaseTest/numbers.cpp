#include "numbers.hpp"
#include <numbers>
#include <iostream>

// Blog: https://blog.csdn.net/fengbingchun/article/details/142897339

int test_numbers()
{
	std::cout << "pi: " << std::numbers::pi <<"," << std::numbers::pi_v<float> << std::endl; // pi: 3.14159,3.14159
	std::cout << "inv_pi: " << std::numbers::inv_pi << "," << std::numbers::inv_pi_v<float> << std::endl; // inv_pi: 0.31831,0.31831
	std::cout << "e: " << std::numbers::e << "," << std::numbers::e_v<double> << std::endl; // e: 2.71828,2.71828
	std::cout << "log2e: " << std::numbers::log2e << "," << std::numbers::log2e_v<long double> << std::endl; // log2e: 1.4427,1.4427
	std::cout << "ln2: " << std::numbers::ln2 << "," << std::numbers::ln2_v<float> << std::endl; // ln2: 0.693147,0.693147
	std::cout << "log10e: " << std::numbers::log10e << "," << std::numbers::log10e_v<float> << std::endl; // log10e: 0.434294,0.434294
	std::cout << "ln10: " << std::numbers::ln10 << "," << std::numbers::ln10_v<float> << std::endl; // ln10: 2.30259,2.30259
	std::cout << "sqrt2: " << std::numbers::sqrt2 << "," << std::numbers::sqrt2_v<float> << std::endl; // sqrt2: 1.41421,1.41421
	std::cout << "sqrt3: " << std::numbers::sqrt3 << "," << std::numbers::sqrt3_v<float> << std::endl; // sqrt3: 1.73205,1.73205
	std::cout << "inv_sqrt3: " << std::numbers::inv_sqrt3 << "," << std::numbers::inv_sqrt3_v<float> << std::endl; // inv_sqrt3: 0.57735,0.57735

	return 0;
}
