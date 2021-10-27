#include "design_optimizations.hpp"
#include <string.h>
#include <iostream>
#include <chrono>
#include <string>
#include <numeric>
#include <vector>

// Blog: https://blog.csdn.net/fengbingchun/article/details/86549506

namespace design_optimizations_ {

// reference: 《提高C++性能的编程技术》：第十四章：设计优化
namespace {

void stringSum1(const std::vector<std::string>& vs, std::string& result)
{
	int vectorSize = vs.size();
	int* stringSizes = new int[vectorSize];
	int totalInputLength = 0;

	for (int i = 0; i < vectorSize; ++i) {
		stringSizes[i] = vs[i].length();
		totalInputLength += stringSizes[i];
	}
	
	char* s = new char[totalInputLength+1];
	memset(s, 0, totalInputLength+1);

	int sp = 0;
	for (int i = 0; i < vectorSize; ++i) {
		memcpy(&s[sp], vs[i].c_str(), stringSizes[i]);
		sp += stringSizes[i];
	}

	delete[] stringSizes;
	result = s;
	delete[] s;
}

} // namespace

int test_design_optimizations_1()
{
	std::chrono::high_resolution_clock::time_point time_start, time_end;
	const int count{1000000}, count2{100000};
	std::vector<std::string> vectorx;
	for (int i = 0; i < 100; ++i) {
		vectorx.emplace_back("abcd");
	}
 
{ // test string add: std::accumulate: 此函数的性能弱点测试
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		std::string empty;
		std::string result = std::accumulate(vectorx.cbegin(), vectorx.cend(), empty);
		//fprintf(stdout, "result: %s\n", result.c_str());
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "string add operation std::accumulate time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // test string add: custom function: 为了提高性能而牺牲了通用性
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		std::string result;
		stringSum1(vectorx, result);
		//fprintf(stdout, "result: %s\n", result.c_str());
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "string add operation custom function time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

	return 0;
}

} // namespace design_optimizations_

