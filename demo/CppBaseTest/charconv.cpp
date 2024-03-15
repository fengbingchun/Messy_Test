#include "charconv.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <charconv>
#include <string_view>

// Blog: https://blog.csdn.net/fengbingchun/article/details/136736884
int test_charconv()
{
	constexpr int val_int{ 88 };
	constexpr float val_float{ 66.66f };
	constexpr double val_double{ 88.8888 };
	const std::string str1{ "123" }, str2{ "456.789" };

	// std::to_chars: converts an integer or floating-point value to a character sequence
	std::array<char, 10> buffer;
	// 注意:std::errc没有到bool的隐式转换,所以你不能像下面这样检查: if (res.ec) {} or if (!res.ec) {}
	if (auto [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), val_int); ec == std::errc()) {
		std::cout << "str:" << std::string_view(buffer.data(), ptr - buffer.data()) << "\n"; // str:88

		*ptr = '\0'; // 保证结尾有一个空字符
		std::cout << "buffer:" << buffer.data() << "\n"; // buffer:88
	} else {
		std::cerr << "fail to call to_char:" << std::make_error_code(ec).message() << "\n";
		return -1;
	}

	buffer.fill(0);
	if (auto [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), val_float); ec == std::errc()) {
		std::cout << "str:" << std::string_view(buffer.data(), ptr - buffer.data()) << "\n"; // str:66.66

		*ptr = '\0'; // 保证结尾有一个空字符
		std::cout << "buffer:" << buffer.data() << "\n"; // buffer:66.66
	} else {
		std::cerr << "fail to call to_char:" << std::make_error_code(ec).message() << "\n";
		return -1;
	}

	buffer.fill(0);
	if (auto [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), val_double); ec == std::errc()) {
		std::cout << "str:" << std::string_view(buffer.data(), ptr - buffer.data()) << "\n"; // str:88.8888
	} else {
		std::cerr << "fail to call to_char:" << std::make_error_code(ec).message() << "\n";
		return -1;
	}

	// std::from_chars: converts a character sequence to an integer or floating-point value
	int val1{ 0 };
	auto [ptr, ec] = std::from_chars(str1.data(), str1.data() + str1.size(), val1);
	if (ec == std::errc()) // 注意:std::errc没有到bool的隐式转换,所以你不能像下面这样检查: if (res.ec) {} or if (!res.ec) {} 
		std::cout << "val1:" << val1 << "\n"; // val1:123
	else if (ec == std::errc::invalid_argument)
		std::cerr << "Error: this is not a number: " << str1 << "\n";
	else if (ec == std::errc::result_out_of_range)
		std::cerr << "Error: this number is larger than an int: " << str1 << "\n";
	else
		std::cerr << "fail to call from_chars:" << std::make_error_code(ec).message() << "\n";

	float val2{ 0.f };
	auto [ptr2, ec2] = std::from_chars(str2.data(), str2.data() + str2.size(), val2);
	if (ec2 == std::errc())
		std::cout << "val2:" << val2 << "\n"; // val2:456.789
	else if (ec2 == std::errc::invalid_argument)
		std::cerr << "Error: this is not a number: " << str2 << "\n";
	else if (ec2 == std::errc::result_out_of_range)
		std::cerr << "Error: this number is larger than an float: " << str2 << "\n";
	else
		std::cerr << "fail to call from_chars:" << std::make_error_code(ec2).message() << "\n";


	// std::stringstream: int/float/double->std::string
	std::stringstream ss1;
	ss1 << val_int << "," << val_float << "," << val_double;
	std::string str = ss1.str();
	std::cout << "str:" << str << "\n"; // str:88,66.66,88.8888

	std::stringstream ss2;
	ss2 << str1 << "," << str2;
	str = ss2.str();
	std::cout << "str:" << str << "\n"; // str:123,456.789

	// std::to_string: int/float/double->std::string
	str = std::to_string(val_int);
	std::cout << "str:" << str << "\n"; // str:88
	str = std::to_string(val_float);
	std::cout << "str:" << str << "\n"; // str:66.660004
	str = std::to_string(val_double);
	std::cout << "str:" << str << "\n"; // str:88.888800

	// std::stoi, std::stol, std::stoll: std::string->int/long/long long
	auto ret1 = std::stoi(str1);
	std::cout << "ret1:" << ret1 << "\n"; // ret:123

	// std::stoul, std::stoull: std::string->unsigned long/unsigned long long
	auto ret2 = std::stoul(str1);
	std::cout << "ret2:" << ret2 << "\n"; // ret2:123

	// std::stof, std::stod, std::stold: std::string->float/double/long double
	auto ret3 = std::stof(str2);
	std::cout << "ret3:" << ret3 << "\n"; // ret3:456.789

	return 0;
}
