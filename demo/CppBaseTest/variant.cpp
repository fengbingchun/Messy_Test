#include "variant.hpp"
#include <variant>
#include <string>
#include <vector>
#include <iostream>

// Blog: https://blog.csdn.net/fengbingchun/article/details/134482388

namespace {

template<class T>
auto& operator<<(std::ostream& out, const std::vector<T>& v)
{
	out << "{";
	for (const auto& e : v)
		out << e << " ";
	return out << "}";
}

struct S {
	S(int i) : i(i) {}
	int i;
};

class Derived : public std::variant<int, std::string> { };

} // namespace

int test_variant_init()
{
	std::variant<int, float> var1;
	std::cout << "index: " << var1.index() << ", value: " << std::get<int>(var1) << "\n"; // index: 0, value: 0

	std::variant<std::string, int> var2{ "CHINA" };
	std::cout << "index: " << var2.index() << ", value: " << std::get<std::string>(var2) << "\n"; // index: 0, value: CHINA

	std::variant<std::string, int> var3{ 66 };
	std::cout << "index: " << var3.index() << ", value: " << std::get<int>(var3) << "\n"; // index: 1, value: 66

	std::variant<std::vector<int>, std::string, float> var4{ std::in_place_type<std::string>, "CHINA" };
	std::cout << "index: " << var4.index() << ", value: " << std::get<std::string>(var4) << "\n"; // index: 1, value: CHINA

	std::variant<std::string, std::vector<int>, float> var5{ std::in_place_type<std::vector<int>>, {1, 2, 3, 4, 5} };
	std::cout << "index: " << var5.index() << ", value: " << std::get<std::vector<int>>(var5) << "\n"; // index: 1, value: {1 2 3 4 5 }

	std::variant<std::string, bool, std::vector<std::string>> var6{ std::in_place_index<2>, 5, "hi" };
	std::cout << "index: " << var6.index() << ", value: " << std::get<std::vector<std::string>>(var6) << "\n"; // index: 2, value: {hi hi hi hi hi }

	//std::variant<S> var7; // error C2512: "std::variant<`anonymous-namespace'::S>::variant": 没有合适的默认构造函数可用
	std::variant<std::monostate, S> var7;
	std::cout << "index: " << var7.index() << "\n"; // index: 0
	if (std::holds_alternative<std::monostate>(var7))
		std::cout << "var7 has monostate\n"; // var7 has monostate
	var7 = std::monostate{};

	return 0;
}

int test_variant_functions()
{
	std::variant<int, float, std::string> var1{ 66.6f };
	std::cout << "index: " << var1.index() << ", value: " << std::get<float>(var1) << "\n"; // index: 1, value: 66.6

	var1.emplace<2>("CHINA");
	std::cout << "index: " << var1.index() << ", value: " << std::get<std::string>(var1) << "\n"; // index: 2, value: CHINA
	var1.emplace<0>(88);
	std::cout << "index: " << var1.index() << ", value: " << std::get<int>(var1) << "\n"; // index: 0, value: 88

	std::cout << std::boolalpha
		<< "holds int: " << std::holds_alternative<int>(var1)
		<< ", holds string: " << std::holds_alternative<std::string>(var1) << "\n"; // holds int: true, holds string: false

	if (std::holds_alternative<int>(var1))
		std::cout << "var1 type: int\n"; // var1 type : int

	std::variant<std::string, int, float, std::vector<float>> var2;
	var2 = std::get<int>(var1);
	std::cout << "index: " << var2.index() << ", value: " << std::get<int>(var2) << "\n"; // index: 1, value: 88
	var2 = std::get<0>(var1); // <==> var2 = std::get<int>(var1);
	std::cout << "index: " << var2.index() << ", value: " << std::get<int>(var2) << "\n"; // index: 1, value: 88
	std::get<0>(var1) = 99;
	std::cout << "index: " << var1.index() << ", value: " << std::get<int>(var1) << "\n"; // index: 0, value: 99

	try {
		//var2 = std::get<2>(var1);
		var2 = std::get<std::string>(var1);
	} catch (std::bad_variant_access const& ex) {
		std::cout << "exception: " << ex.what() << "\n"; // windows: exception: bad variant access; linux: exception: std::get:wrong index for variant
	}

	std::variant<std::string, std::string> var3;
	std::get<0>(var3) = "China";
	std::cout << "index: " << var3.index() << ", value: " << std::get<0>(var3) << "\n"; // index: 0, value: China
	var3.emplace<1>("Beijing");
	std::cout << "index: " << var3.index() << ", value: " << std::get<1>(var3) << "\n"; // index: 1, value: Beijing

	auto check_value = [](const std::variant<int, float>& v) {
		if (const int* pval = std::get_if<int>(&v))
			std::cout << "variant value: " << *pval << '\n';
		else
			std::cout << "failed to get value" << '\n';
	};

	std::variant<int, float> var4{ 12 }, var5{ 3.f };
	check_value(var4); // variant value: 12
	check_value(var5); // failed to get value

	Derived var6{ "Beijing" };
	std::cout << "index:" << var6.index() << ", value: " << std::get<1>(var6) << "\n"; // index:1, value: Beijing

	std::swap(var4, var5);
	std::cout << "var4 index: " << var4.index() << ", value: " << std::get<1>(var4) << "\n"; // var4 index: 1, value: 3
	std::cout << "var5 index: " << var5.index() << ", value: " << std::get<0>(var5) << "\n"; // var5 index: 0, value: 12

	std::cout << std::boolalpha << "var4 == var5: " << (var4 == var5) << "\n"; // var4 == var5: false

	std::variant<std::string, std::string> var7{ std::in_place_index<1>, "China" }, var8;
	std::cout << "index: " << var7.index() << ", value: " << std::get<1>(var7) << "\n"; // index: 1, value: China
	var7.emplace<0>("Bejing");
	std::cout << "index: " << var7.index() << ", value: " << std::get<0>(var7) << "\n"; // index: 0, value: Bejing

	var8 = std::move(var7);
	std::cout << "index: " << var7.index() << ", value: " << std::get<0>(var7) << "\n"; // index: 0, value:
	std::cout << "index: " << var8.index() << ", value: " << std::get<0>(var8) << "\n"; // index: 0, value: Bejing

	return 0;
}