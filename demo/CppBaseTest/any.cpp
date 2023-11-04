#include "any.hpp"
#include <any>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

// Blog: https://blog.csdn.net/fengbingchun/article/details/134222096

int test_any_init()
{
	// copy initialisation
	std::any value = 66; // 推荐: std::any value = std::make_any<int>(66); // std::make_any:类型安全、异常安全
	std::cout << "value: " << std::any_cast<int>(value) << "\n"; // value: 66

	// assignment operator
	value = "China";
	std::cout << "value: " << std::any_cast<const char*>(value) << "\n"; // value: China

	// parametrized constructor
	std::any value2(88.);
	std::cout << "value2: " << std::any_cast<double>(value2) << "\n"; // value2: 88

	// brace initializer
	try {
		std::any value3{ "China" };
		std::cout << "value3: " << std::any_cast<std::string>(value3) << "\n"; // std::any_cast<const char*>(value3)
	} catch (std::bad_any_cast& e) {
		std::cout << "Error: " << e.what() << "\n"; // value3: Error: Bad any_cast
	}

	auto value4 = std::make_any<std::string>("Beijing");
	std::cout << "value4: " << std::any_cast<std::string&>(value4) << "\n"; // value4: Beijing 推荐转换为引用类型来避免创建临时对象

	std::string str = "Tianjin";
	std::any value5 = std::move(str);
	std::cout << "value5: " << std::any_cast<std::string&>(value5) << "\n"; // value5: Tianjin

	return 0;
}

int test_any_member_functions()
{
	// emplace, type
	std::any value = 6;
	std::cout << "value: " << std::any_cast<int>(value) << "\n"; // value: 6
	std::cout << "type name: " << value.type().name() << "\n"; // type name: int(windows), i(linux)

	auto& tmp = std::any_cast<int&>(value); // 引用
	tmp = 8;
	std::cout << "value: " << std::any_cast<int>(value) << "\n"; // value: 8
	std::any_cast<int&>(value) = 10;
	std::cout << "value: " << std::any_cast<int>(value) << "\n"; // value: 10

	auto ptr = std::any_cast<int>(&value); // 指针
	std::cout << "value: " << *ptr << "\n"; // value: 10

	// 避免抛异常
	auto ptr2 = std::any_cast<std::string>(&value);
	if (ptr2 == nullptr)
		std::cout << "value dons't contain a string\n"; // value dons't contain a string

	value.emplace<std::string>("China");
	std::cout << "value: " << std::any_cast<std::string>(value) << "\n"; // value: China
	std::cout << "type name: " << value.type().name() << "\n"; // windows: type name: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
															   // linux:   type name: NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE

	if (value.type() == typeid(std::string))
		std::cout << "value type is std::string\n"; // value type is std::string

	// reset, has_value
	if (value.has_value()) std::cout << "value found\n"; // value found
	value.reset();
	if (!value.has_value()) std::cout << "no value found\n"; // no value found

	std::any tmp2;
	if (!tmp2.has_value()) std::cout << "tmp2 no value found\n"; // tmp2 no value found

	// std::any的主要问题是额外的动态内存分配
	std::cout << "size(any): " << sizeof(std::any) << "\n"; // size(any): 64(windows 10 vs2022), 16(ubuntu22.04 g++ 11.4)

	value = std::vector<int>{ 1, 2, 3 };
	std::cout << "value size: " << std::any_cast<std::vector<int>&>(value).size() << "\n"; // value size: 3

	return 0;
}
