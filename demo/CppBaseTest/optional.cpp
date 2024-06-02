#include "optional.hpp"
#include <optional>
#include <string>
#include <iostream>
#include <vector>

// Blog: https://blog.csdn.net/fengbingchun/article/details/134353178

int test_optional_init()
{
	std::optional<int> var;
	if (!var.has_value())
		std::cout << "var is not set\n"; // var is not set

	var = 8; // error: *var = 8, 因为var采用默认初始化为空
	if (var.has_value())
		std::cout << "var is present: " << var.value() << "\n"; // var is present: 8
	if (var)
		std::cout << "var is present: " << *var << "\n"; // var is present: 8

	std::optional<int> var2{ std::nullopt }; // 将var2初始化置于"empty"状态
	if (!var2.has_value())
		std::cout << "var2 is not set\n"; // var2 is not set

	std::optional<std::string> var3{ "China" };
	if (var3 > std::nullopt)
		std::cout << "var3 > std::nullopt\n"; // var3 > std::nullopt

	auto var4 = std::make_optional<std::vector<const char*>>({ "China", "Beijing", "Haidian" });
	for (const auto& v : *var4)
		std::cout << " " << v; //  China Beijing Haidian
	std::cout << "\n";

	// 内建类型可不需指明存储类型,deduction guide
	std::optional var5{ 2 }; 
	std::cout << "var5: " << var5.value() << "\n"; // var5: 2

	std::optional var6{ std::string{"China"} };
	std::cout << "var6: " << var6.value() << "\n"; // var6: China

	return 0;
}

int test_optional_member_functions()
{
	// 获取std::optional值: var.value(), *var, var.value_or, var->
	std::optional<int> var{ 8 };
	std::cout << "var: " << var.value() << ", " << *var << "\n"; // var: 8, 8
	*var = 6; std::cout << "var: " << *var << "\n"; // var: 6
	var = 8; std::cout << "var: " << *var << "\n"; // var: 8
	*var = 10; std::cout << "var: " << var.value_or(66) << "\n"; // var: 10
	var.reset(); std::cout << "var: " << var.value_or(66) << "\n"; // var: 66

	std::optional<std::string> var2{ "China" };
	std::cout << "var2: " << var2->data() << "\n"; // var2: China

	var.reset(); // or: var = {};
	try {
		std::cout << "var: " << var.value() << "\n";
		//std::cout << "var: " << *var << "\n"; // 直接crash掉
	}
	catch (const std::bad_optional_access& e) {
		std::cout << "exception: " << e.what() << "\n"; // var: exception: Bad optional access
	}

	std::string str{ "Beijing" }; // 不要对常量变量使用std::move
	std::optional<std::string> var3(std::move(str));
	std::cout << "var3: " << var3.value() << ", str: " << str << "\n"; // var3: Beijing, str:

	var3.emplace("Haidian");
	std::cout << "var3: " << var3.value() << "\n"; // var3: Haidian

	if (var3.has_value())
		std::cout << "var3 has value\n"; // var3 has value
	if (var3)
		std::cout << "var3 has value\n"; // var3 has value

	std::cout << "var2: " << var2.value() << ", var3: " << var3.value() << "\n"; // var2: China, var3: Haidian
	var2.swap(var3);
	std::cout << "var2: " << var2.value() << ", var3: " << var3.value() << "\n"; // var2: Haidian, var3: China

	if (var2 != var3)
		std::cout << "var2 != var3\n"; // var2 != var3

	return 0;
}
