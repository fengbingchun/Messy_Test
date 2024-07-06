#include "aggregate_initialization.hpp"
#include <iostream>
#include <string>

// Blog: https://blog.csdn.net/fengbingchun/article/details/140225138
namespace {

struct A { int x; int y; int z; };
union u { int a; const char* b; };

struct B {
	std::string str;
	int n = 42;
	int m = -1;
};

struct D {
	A a;
	int m;
	int n;
};

} // namespace

int test_designated_initializers()
{
	A a{ .x = 1, .z = 2 }; // a.y initialized to 0
	std::cout << "value: " << a.x << "," << a.y << "," << a.z << std::endl;

	A b = { .y{1}, .z{2} }; // b.x initialized to 0
	std::cout << "value: " << b.x << "," << b.y << "," << b.z << std::endl;

	//A c{ .y = 2, .x = 1 }; // error; designator order does not match declaration order

	u f = { .b = "blog" }; // active member of the union is b
	std::cout << "value: " << f.b << std::endl;

	B x{ .m = 8 };
	std::cout << "value: " << x.str << "," << x.n << "," << x.m << std::endl;

	//B y{ .str{"c++20"}, .n{6}, 8 }; // error C7556: 不能将指定初始值设定项与非指定初始值设定项混合

	//D t{ .a.x{1} }; // error C7558: 标准C++指定初始值设定项中不允许嵌套的成员访问; 请使用嵌套的初始值设定项列表
	D w{ .a{a}, .m{6}, .n{8} };
	std::cout << "value: " << w.a.x << "," << w.a.y << "," << w.a.z << "," << w.m << "," << w.n << std::endl;

	return 0;
}

