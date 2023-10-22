#include "string_view.hpp"
#include <iostream>
#include <string>
#include <iterator> // std::size
#include <string_view>
#include <string.h>

// Blog: https://blog.csdn.net/fengbingchun/article/details/133971138

int test_string_view_copy()
{
	std::string str1{ "china" };
	std::string_view strv1{ "beijing" };

	// str2和str1的数据存放在完全不同的两个位置(副本); strv2和strv1的数据都指向同一个指针地址,没有额外的拷贝(副本)
	std::string str2{ str1 };
	std::string_view strv2{ strv1 };
	std::cout << "str2: " << str2 << ", strv2: " << strv2 << "\n"; // str2: china, strv2: beijing

	str1.clear();
	strv1 = {}; //strv1 = strv1.substr(0, 0); //strv1.remove_prefix(strv1.size()); // 注意它们的区别
	// clear str1完全不会影响到str2; "clear" strv1也不会影响到strv2,因为strv2指向的指针地址没有变,对strv1 "clear"操作并不会影响到它之前指向的指针地址数据
	std::cout << "str2: " << str2 << ", strv2: " << strv2 << "\n"; // str2: china, strv2: beijing

	return 0;
}

int test_string_view_functions()
{
	// unlike std::string, std::string_view has full support for constexpr
	constexpr std::string_view strv{ "china beijing" };

	// substr
	auto strv1 = strv.substr(6);
	std::cout << "strv1: " << strv1 << std::endl; // strv1: beijing
	//strv1[0] = 'B'; // 无论strv是不是constexpr, strv1都不能作修改

	char str1[]{ "beijing" };
	std::string_view strv2{ str1 };
	std::cout << "strv2: " << strv2 << std::endl; // strv2: beijing
	str1[0] = 'B';
	std::cout << "strv2: " << strv2 << std::endl; // strv2: Beijing

	std::cout << "at 2: " << strv2.at(2) << ", back: " << strv2.back() << "\n"; // at 2: i, back: g
	strv2.remove_prefix(3);
	std::cout << "remove_prefix 3: " << strv2 << "\n"; // remove_prefix 3: jing
	strv2.remove_suffix(2);
	std::cout << "remove_suffix 2: " << strv2 << "\n"; // remove_suffix 2: ji

	std::string str{};
	strv.copy(str.data(), strv.size()); // 注意str并非完整的std::string对象,str.size()为0
	std::cout << "str: " << str.data() << "\n"; // str: china beijing  note:是str.data()而不能是str

	// 注意以下两条语句的差异, str.size()为0
	std::cout << "strv.compare(str.data()): " << strv.compare(str.data()) << "\n"; // strv.compare(str.data()): 0
	std::cout << "strv.compare(str): " << strv.compare(str) << "\n"; // windows: strv.compare(str): 1  linux: strv.compare(str): 13

	auto found = strv.find(strv2);
	std::cout << "found: " << found << "\n"; // found: 9
	std::cout << "strv rfind: " << strv.rfind("i") << "\n"; // strv rfind: 10
	std::cout << "strv find_first_of: " << strv.find_first_of("i") << "\n"; // strv find_first_of: 2
	std::cout << "strv find_last_of: " << strv.find_last_of("i") << "\n"; // strv find_last_of: 10
	std::cout << "strv find_last_not_of: " << strv.find_last_not_of("in") << "\n"; // strv find_last_not_of: 12
	std::cout << "strv find_first_not_of: " << strv.find_first_not_of("in", 1) << "\n"; // strv find_first_not_of: 1

	// std::string_view不需要空终止符来标记字符串的结尾,因为它记录了字符串的长度
	char name[]{ 'c', 'h', 'i', 'n', 'a' };
	std::string_view strv3{ name, std::size(name) };
	std::cout << "strv3: " << strv3 << "\n"; // strv3: china
	std::cout << "name: " << name << "\n"; // windows: name: china烫烫烫烫烫烫烫烫烫烫烫烫烫烫烫蘐?宋 linux: name: chinaBeijing

	// std::string_view to std::string: std::string_view不会隐式转换为std::string
	std::string str2{ strv }; // explicit conversion
	std::cout << "str2: " << str2 << "\n"; // str2: china beijing

	// std::string_view to C-style string: std::string_view -> std::string -> C-style string
	auto str3{ str2.c_str() };
	std::cout << "str3 length: " << strlen(str3) << "\n"; // str3 length: 13

	// std::string_view just only a view
	auto addr = [] {
		std::string str_csdn{ "https://blog.csdn.net/fengbingchun/" };
		std::string_view strv_csdn{ str_csdn };
		std::cout << "strv csdn: " << strv_csdn << "\n"; // strv csdn: https://blog.csdn.net/fengbingchun/
		return strv_csdn;
	};

	std::string_view strv4{ addr() };
	std::cout << "strv4 csdn: " << strv4 << "\n"; // windows: strv4 csdn: 葺葺葺葺葺葺葺葺葺葺葺葺葺葺葺葺葺 linux: strv4 csdn: ▒(a▒▒\▒▒G▒cn.net/fengbingchun/

	// literals for std::string_view: 可以通过在双引号字符串文字后面使用sv后缀来创建类型为std::string_view的C风格字符串常量
	using namespace std::string_literals;      // access the s suffix
	using namespace std::string_view_literals; // access the sv suffix

	std::cout << "foo\n";   // no suffix is a C-style string literal
	std::cout << "goo\n"s;  // s suffix is a std::string literal
	std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

	return 0;
}
