#include "span.hpp"
#include <iostream>
#include <span>
#include <vector>
#include <cstring>

// Blog: https://blog.csdn.net/fengbingchun/article/details/143082300

int test_span_span()
{
	int a[]{ 8, 7, 6 };
	std::span<int> sp1(a);
	std::cout << sp1.front() << "," << sp1.back() << "," << sp1[1] << "," << *sp1.data() << std::endl; // 8,6,7,8

	auto print = [](auto sp) {
		for (auto v : sp)
			std::cout << v << ",";
		std::cout << std::endl;
	};

	std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::span<int> sp2(vec.data()+1, 6);
	print(sp2); // 1,2,3,4,5,6,
	std::cout << sp2.size() << "," << sp2.size_bytes() << "," << sp2.empty() << std::endl; // 6,24,0

	std::span<int> sp3 = sp2.subspan(1, 4);
	print(sp3); // 2,3,4,5,

	auto sp4 = sp3.first<3>();
	print(sp4); // 2,3,4,

	auto extent = [](auto sp) {
		if (std::dynamic_extent == sp.extent)
			std::cout << "dynamic extent:" << sp.extent << std::endl;
		else
			std::cout << "static extent:" << sp.extent << std::endl;
	};

	auto sp5 = sp3.last<3>();
	print(sp5); // 3,4,5,
	extent(sp5); // static extent:3

	std::span<int, std::dynamic_extent> sp6{ vec };
	extent(sp6); // dynamic extent:18446744073709551615

	return 0;
}

int test_span_functions()
{
	std::vector<int> vec{ 3, 1, 4, 6, 8 };

	std::cout << *std::begin(vec) << "," << *(std::end(vec)-1) << std::endl; // 3,8
	std::cout << *std::crbegin(vec) << "," << *(std::crend(vec) - 1) << std::endl; // 8,3

	std::cout << std::size(vec) << "," << std::ssize(vec) << std::endl; // 5,5

	std::string s{ "Hello world!" };
	char a[20]; // storage for a C-style string
	std::strcpy(a, std::data(s));
	std::cout << a << std::endl; // Hello world!

	std::cout << std::empty(vec) << std::endl; // 0
	vec.clear(); 
	std::cout << std::empty(vec) << std::endl; // 1

	return 0;
}

