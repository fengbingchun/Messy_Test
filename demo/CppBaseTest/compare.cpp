#include "common.hpp"
#include <compare>
#include <vector>
#include <string>

// Blog: https://blog.csdn.net/fengbingchun/article/details/142434129

namespace {
auto compare = []<typename T>(const T & x, const T & y) {
	return x <=> y;
};

struct Point {
	int x, y;
	
	auto operator<=>(const Point& other) const = default;
};

const std::string str1{ "abc" }, str2{ "Abc" }, str3{ "abc" };

template<class Ord>
void print_cmp_type()
{
	if constexpr (std::is_same_v<Ord, std::strong_ordering>)
		std::cout << "strong ordering\n";
	else if constexpr (std::is_same_v<Ord, std::weak_ordering>)
		std::cout << "weak ordering\n";
	else if constexpr (std::is_same_v<Ord, std::partial_ordering>)
		std::cout << "partial ordering\n";
	else
		std::cout << "illegal comparison result type\n";
}

} // namespace

int test_compare_concepts()
{
	constexpr auto x{ 1 }, y{ 2 }, z{ 1 };
	if (compare(x, y) < 0) std::cout << x << " < " << y << std::endl;
	if (compare(y, x) > 0) std::cout << y << " > " << x << std::endl;
	if (compare(x, z) == 0) std::cout << x << " == " << z << std::endl;

	if (compare(str2, str1) < 0) std::cout << str2 << " < " << str1 << std::endl;
	if (compare(str1, str2) > 0) std::cout << str1 << " > " << str2 << std::endl;
	if (compare(str1, str3) == 0) std::cout << str1 << " == " << str3 << std::endl;

	return 0;
}

int test_compare_classes()
{
	if (compare(str2, str1) == std::strong_ordering::less) std::cout << str2 << " < " << str1 << std::endl;
	if (compare(str1, str2) == std::strong_ordering::greater) std::cout << str1 << " > " << str2 << std::endl;
	if (compare(str1, str3) == std::strong_ordering::equal) std::cout << str1 << " == " << str3 << std::endl;

	constexpr float x{ 1.f }, y{ 2.f }, z{ 1.f };
	if (compare(x, y) == std::weak_ordering::less) std::cout << x << " < " << y << std::endl;
	if (compare(y, x) == std::weak_ordering::greater) std::cout << y << " > " << x << std::endl;
	if (compare(x, z) == std::weak_ordering::equivalent) std::cout << x << " == " << z << std::endl;

	constexpr Point p1{ 1,2 }, p2{ 2,3 };
	auto ret = p1 <=> p2;
	if (ret == std::partial_ordering::less) std::cout << "p1 < p2" << std::endl;
	if (std::compare_three_way{}(p1, p2) == std::strong_ordering::less) std::cout << "p1 < p2" << std::endl;

	print_cmp_type<std::compare_three_way_result_t<int>>(); // strong ordering
	print_cmp_type<std::compare_three_way_result_t<double>>(); // partial ordering

	return 0;
}

int test_compare_customization_point_objects()
{
	if (std::strong_order(str1, str2) == std::strong_ordering::greater) std::cout << str1 << " > " << str2 << std::endl;
	if (std::weak_order(str2, str1) == std::weak_ordering::less) std::cout << str2 << " < " << str1 << std::endl;
	if (std::partial_order(str1, str3) == std::partial_ordering::equivalent) std::cout << str1 << " == " << str3 << std::endl;

	if (std::compare_strong_order_fallback(str1, str2) == std::strong_ordering::greater) std::cout << str1 << " > " << str2 << std::endl;
	if (std::compare_weak_order_fallback(str2, str1) == std::weak_ordering::less) std::cout << str2 << " < " << str1 << std::endl;
	if (std::compare_partial_order_fallback(str1, str3) == std::partial_ordering::equivalent) std::cout << str1 << " == " << str3 << std::endl;

	return 0;
}

int test_compare_functions()
{
	if (std::is_eq(std::strong_order(str1, str3))) std::cout << str1 << " == " << str3 << std::endl;
	if (std::is_neq(std::strong_order(str1, str2))) std::cout << str1 << " != " << str2 << std::endl;

	if (std::is_lt(std::weak_order(str2, str1))) std::cout << str2 << " < " << str1 << std::endl;
	if (std::is_lteq(std::weak_order(str2, str1))) std::cout << str2 << " <= " << str1 << std::endl;

	if (std::is_gt(std::partial_order(str1, str2))) std::cout << str1 << " > " << str2 << std::endl;
	if (std::is_gteq(std::partial_order(str1, str3))) std::cout << str1 << " >= " << str3 << std::endl;

	return 0;
}
