#include "structured_binding.hpp"
#include <iostream>
#include <tuple>
#include <string>
#include <map>

// Blog: https://blog.csdn.net/fengbingchun/article/details/134762654

namespace {

typedef struct Info {
	mutable std::string name;
	volatile int number;
} Info;

inline Info func()
{
	return Info{ "csdn", 666 };
}

typedef struct Data {
	int b{ 1 }, d{ 2 }, p{ 3 }, q{ 4 };
} Data;

} // namespace

int test_structured_binding()
{
	{ // binding an array
		int arr1[3] = { 1, 2, 3 };

		auto [x, y, z] = arr1; // 拷贝
		std::cout << "x:" << x << ",y:" << y << ",z:" << z << "\n"; // x:1,y:2,z:3
		x = 4;
		std::cout << "arr1:" << arr1[0] << "\n"; // arr1:1

		auto& [x2, y2, z2] = arr1; // 引用
		std::cout << "x2:" << x2 << ",y2:" << y2 << ",z2:" << z2 << "\n"; // x2:1,y2:2,z2:3
		x2 = 5;
		std::cout << "arr1:" << arr1[0] << "\n"; // arr1:5

		const auto& [x3, y3, z3] {arr1};
		const auto& [x4, y4, z4](arr1);
		std::cout << "x3:" << x3 << ",x4:" << x4 << "\n"; // x3:5,x4:5
	}

	{ // binding a tuple-like type
		std::tuple<std::string, int, float> foo{ "csdn", 8, 6.6 };

		const auto& [x3, y3, z3] = foo;
		std::cout << "x3:" << x3 << ",y3:" << y3 << ",z3:" << z3 << "\n"; // x3:csdn,y3:8,z3:6.6

		auto& [x4, y4, z4] = foo;
		x4 = "github";
		y4 = 6;
		z4 = 8.8;
		std::cout << "foo:" << std::get<0>(foo) << "," << std::get<1>(foo) << "," << std::get<2>(foo) << "\n"; // foo:github,6,8.8

		int a = 1, b = 2;
		const auto& [x6, y6] = std::tie(a, b); // x6 and y6 are of type int&
		x6 = 6;
		auto [x7, y7] = std::tie(a, b); // x7 and y7 are still of type int&
		std::cout << "x7:" << x7 << ",a:" << a << "\n"; // x7:6,a:6
		x7 = 8;
		std::cout << "x6:" << x6 << ",a:" << a << "\n"; // x6:8,a:8
		if (&x6 != &x7)
			std::cout << "Error: &x6 != &x7\n"; // 不会执行
	}

	{ // binding to data members
		const auto [x5, y5] = func();
		std::cout << "x5:" << x5 << ",y5:" << y5 << "\n"; // x5:csdn,y5:666
		x5 = "github";
		//y5 = 888; //表达式必须是可修改的左值,需将const auto[x5, y5]调整为auto[x5, y5]

		const auto [b1, d1, p1, q1] = Data{};
		std::cout << "b1:" << b1 << ",d1:" << d1 << ",p1:" << p1 << ",q1:" << q1 << "\n"; // b1:1,d1:2,p1:3,q1:4

		const auto [b2, d2, p2, q2] = Data{ 4, 3, 2, 1 };
		std::cout << "b2:" << b2 << ",d2:" << d2 << ",p2:" << p2 << ",q2:" << q2 << "\n"; // b2:4,d2:3,p2:2,q2:1

		Data s;
		auto& [b3, d3, p3, q3] = s;
		std::cout << "b3:" << b3 << ",d3:" << d3 << ",p3:" << p3 << ",q3:" << q3 << "\n"; // b3:1,d3:2,p3:3,q3:4

		b3 = 4, d3 = 3, p3 = 2, q3 = 1;
		std::cout << "s.b:" << s.b << ",s.d:" << s.d << ",s.p:" << s.p << ",s.q:" << s.q << "\n"; // s.b:4,s.d:3,s.p:2,s.q:1
	}

	const std::map<std::string, std::string> addrs{
		{"csdn", "https://blog.csdn.net/fengbingchun/"},
		{"github", "https://github.com/fengbingchun"}
	};

	for (const auto& [key, val] : addrs) {
		std::cout << "key: " << key << ", addr: " << val << "\n"; // key: csdn, addr: https://blog.csdn.net/fengbingchun/
																  // key: github, addr: https://github.com/fengbingchun
	}

	Info info{ "github", 888 };
	auto&& [u, v] = std::move(info); // u和v指向的匿名实体是info的右值引用,同时info仍持有值
	std::cout << "info.name:" << info.name << "\n"; // info.name:github
	Info info2{ "csdn", 666 };
	auto [u2, v2] = std::move(info2); // info2已失去了值
	std::cout << "info2.name:" << info2.name << "\n"; // info2.name:

	return 0;
}

