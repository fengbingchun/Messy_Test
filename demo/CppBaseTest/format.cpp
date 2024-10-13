#include "format.hpp"
#include <iostream>
#include <format>
#include <chrono>
#include <string>
#include <iterator>
#include <array>
#include <string.h>
#include <string_view>
#include <vector>
#include <any>

// Blog: https://blog.csdn.net/fengbingchun/article/details/142897136

int test_format_functions()
{
	constexpr auto value{ 66.6666f };
	constexpr auto name{ "Tom" };

	// std::format
	auto ret = std::format("Name is {}, value is {}", name, value);
	std::cout << ret << std::endl; // Name is Tom, value is 66.6666

	ret = std::format("Name is {1}, value is {0}", value, name);
	std::cout << ret << std::endl; // Name is Tom, value is 66.6666

	ret = std::format("Name is {1:.2s}, value is {0:.2f}", value, name);
	std::cout << ret << std::endl; // Name is To, value is 66.67

	// std::format_to
	std::string buffer;
	std::format_to(std::back_inserter(buffer), "Name is {1:.2s}, value is {0:.2f}", value, name);
	std::cout << buffer << std::endl; // Name is To, value is 66.67

	// std::format_to_n
	constexpr int length{ 16 };
	std::array<char, length> buf;
	//std::memset(buf.data(), 0, buf.size());
	const std::format_to_n_result result = std::format_to_n(buf.data(), buf.size()-1, "Name is {1:.2s}, value is {0:.2f}", value, name);
	*result.out = '\0'; // adds terminator to buf, no longer required: std::memset(buf.data(), 0, buf.size());
	std::cout << "untruncated output size: " << result.size << ",result: " << buf.data() << std::endl; // untruncated output size: 26,result: Name is To, val

	// std::formatted_size
	const auto required_size{ std::formatted_size(name, value) }; // the result is incorrect, why?
	std::cout << required_size << std::endl; // 3

	// std::vformat
	std::string_view strv{ "Name is {1:.2s}, value is {0:.2f}" };
	auto args_fmt = std::make_format_args(value, name);
	ret = std::vformat(strv, args_fmt);
	std::cout << ret << std::endl; // Name is To, value is 66.67

	// std::vformat_to
	std::string buf2;
	std::vformat_to(std::back_inserter(buf2), strv, args_fmt);
	std::cout << buf2 << std::endl; // Name is To, value is 66.67

	// std::format_error
	try {
		std::string_view strv{ "Name is {1:.2s}, value is {0:.2f}" };
		auto args_fmt = std::make_format_args(name, value);
		ret = std::vformat(strv, args_fmt);
	}
	catch (const std::format_error& ex) {
		std::cout << "error info: " << ex.what() << std::endl; // error info: Invalid presentation type for floating-point
	}

	return 0;
}
