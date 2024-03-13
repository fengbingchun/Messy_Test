#include "parallel_stl.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <execution>

// Blog: https://blog.csdn.net/fengbingchun/article/details/136688038
namespace {

template<typename T>
inline void print(const std::vector<T>& vec)
{
	std::cout << "result: ";
	for (const auto& i : vec) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

} // namespace

int test_parallel_stl()
{
	// 1.std::execution::sequenced_policy
	std::vector<int> vec1 = { 5, 2, 3, 1, 4 };
	std::sort(std::execution::seq, vec1.begin(), vec1.end());
	print(vec1); // result: 1 2 3 4 5

	// 2.std::execution::parallel_policy
	std::vector<int> vec2(5);
	std::transform(std::execution::par, vec1.begin(), vec1.end(), vec2.begin(), [](int x) { return x * x; });
	print(vec2); // result: 1 4 9 16 25

	// 3.std::execution::parallel_unsequenced_policy
	std::vector<int> vec3(5);
	std::transform(std::execution::par_unseq, vec1.begin(), vec1.end(), vec3.begin(), [](int x) { return x * x; });
	print(vec3); // result: 1 4 9 16 25

	return 0;
}
