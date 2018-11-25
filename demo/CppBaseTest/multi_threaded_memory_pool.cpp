#include "multi_threaded_memory_pool.hpp"
#include <iostream>
#include <chrono>
#include <string>

namespace multi_threaded_memory_pool_ {

// reference: 《提高C++性能的编程技术》：第七章：多线程内存池

class Rational {
	friend Rational operator + (const Rational&, const Rational&);

public:
	Rational(int a = 0, int b = 1) : m(a), n(b) {}
private:
	int m; // 分子
	int n; // 分母
};

int test_multi_threaded_memory_pool_1()
{
	return 0;
}

} // namespace multi_threaded_memory_pool_

