#include "if.hpp"
#include <map>
#include <string>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <random>

// Blog: https://blog.csdn.net/fengbingchun/article/details/135036577

namespace {

std::mutex mx;
bool shared_flag = true; // guarded by mx
constexpr int get_value() { return 66; }

// reference: https://learn.microsoft.com/en-us/cpp/cpp/if-else-statement-cpp?view=msvc-170
template<typename T>
auto show(T t)
{
	//if (std::is_pointer_v<T>) // show(a) results in compiler error for return *t. show(p) results in compiler error for return t.
	if constexpr (std::is_pointer_v<T>) // this statement goes away for show(a)
		return *t;
	else
		return t;
}

template<typename T>
void print_value(const T& value)
{
	if constexpr (std::is_same_v<T, std::string>)
		std::cout << "type: std::string: value: " << value << ", length: " << value.length() << "\n";
	else if constexpr (std::is_same_v<T, int>)
		std::cout << "type: int: value: " << value << "\n";
	else if constexpr (std::is_same_v<T, float>)
		std::cout << "type: float: value: " << value << "\n";
	else
		std::cout << "unsupported type\n";
}

} // namespace

int test_if_init()
{
	std::map<std::string, std::string> addrs{
		{"csdn", "https://blog.csdn.net/fengbingchun/"},
		{"github", "https://github.com/fengbingchun"}
	};

	if (auto it = addrs.find("github"); it != addrs.end())
		std::cout << "github:" << it->second << "\n"; // github:https://github.com/fengbingchun

	if (auto it = addrs.find("csdn"); it == addrs.end())
		std::cout << "no find\n";
	else // if中的it变量在else分支中也有效
		std::cout << "csdn:" << it->second << "\n"; // csdn:https://blog.csdn.net/fengbingchun/

	if (auto [it, inserted] = addrs.insert({ "gitee", "https://gitee.com/fengbingchun/test.git" }); !inserted)
		std::cout << "already exists\n";
	else
		std::cout << "inserted successfully: key:" << it->first << ", value:" << it->second << "\n"; // inserted successfully: key:gitee, value:https://gitee.com/fengbingchun/test.git

	if (auto x = get_value(); x == 66)
		std::cout << "x is:" << x << "\n"; // x is:66

	if (std::lock_guard<std::mutex> lock(mx); shared_flag) {
		std::cout << "setting shared_flag to false\n"; // setting shared_flag to false
		shared_flag = false;
	}

	if (auto val1 = addrs.cbegin()->first, val2 = addrs.crbegin()->first; val1 != val2)
		std::cout << "val1:" << val1 << ", val2:" << val2 << "\n"; // val1:csdn, val2:github

	const std::string str{ "if" };
	if (auto keywords = { "if", "for", "while" }; std::any_of(keywords.begin(), keywords.end(), [&str](const char* kw) { return str == kw; }))
		std::cout << "Error:Token must not be a keyword\n"; // Error:Token must not be a keyword

	return 0;
}

int test_if_constexpr()
{
	int a = 66;
	int* p = &a;

	std::cout << show(a) << "\n"; // 66
	std::cout << show(p) << "\n"; // 66

	std::string str{ "hello" };
	print_value(str); // type: std::string: value: hello, length: 5
	print_value(a); // type: int: value: 66
	float val{.6f };
	print_value(val); // type: float: value: 0.6
	print_value(p); // unsupported type

	return 0;
}

int test_switch_init()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 100);

	switch (auto val = dist(mt); val) {
		default:
			std::cout << "val:" << val << "\n"; // val:20
	}
	
	return 0;
}
