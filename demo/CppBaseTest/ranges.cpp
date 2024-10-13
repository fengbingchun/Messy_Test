#include "ranges.hpp"
#include <iostream>
#include <ranges>
#include <forward_list>
#include <list>
#include <vector>
#include <map>
#include <numbers>
#include <tuple>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <cassert>

namespace {

struct SimpleRange { // a minimum range
    int* begin();
    int* end();
};

struct NotRange { // not a range: begin does not return an input_or_output_iterator
    void* begin();
    int* end();
};

} // namespace

int test_ranges_concepts()
{
#ifdef _MSC_VER
	static_assert(std::ranges::range<SimpleRange>);
	static_assert(!std::ranges::range<NotRange>);
#endif

	static_assert(std::ranges::sized_range<std::list<int>> and not std::ranges::sized_range<std::forward_list<int>>);

	static_assert(std::ranges::contiguous_range<const std::vector<int>> and not std::ranges::contiguous_range<std::list<int>>);

	return 0;
}

int test_ranges_classes()
{
	// std::ranges::views == std::views
	// std::ranges::subrange
	const std::multimap<int, char> mm{ {1, 'a'}, {2, 'a'}, {1, 'c'}, {3, 'd'}, {1, 'e'}, {1, 'f'} };
	auto [first, last] = mm.equal_range(1);
	for (const auto& [_, v] : std::ranges::subrange(first, last))
		std::cout << v << ",";
	std::cout << std::endl;

	// std::ranges::empty_view
	std::ranges::empty_view<long> e;
	static_assert(std::ranges::empty(e));
	static_assert(0 == e.size());
	static_assert(nullptr == e.data());
	static_assert(nullptr == e.begin());
	static_assert(nullptr == e.end());

	// std::ranges::single_view
	constexpr std::ranges::single_view sv1{ std::numbers::pi };
	static_assert(sv1);
	static_assert(not sv1.empty());
	std::cout << "data:" << *sv1.data() << ";begin:" << *sv1.begin() << ";size:" << sv1.size() << ";distance:" << std::distance(sv1.begin(), sv1.end()) << std::endl;

	std::ranges::single_view<std::tuple<int, double, std::string>> sv2{ {1, std::numbers::sqrt2, "^-^"} };
	std::cout << "value:" << std::get<0>(sv2[0]) << "," << std::get<1>(sv2[0]) << "," << std::get<2>(sv2[0]) << std::endl;

	// std::ranges::views::iota/std::ranges::iota_view
	for (auto i : std::ranges::iota_view{ 1, 10 })
		std::cout << i << ' ';
	std::cout << std::endl;

	for (auto i : std::ranges::views::iota(1, 10))
		std::cout << i << ' ';
	std::cout << std::endl;

	// std::ranges::views::istream
	auto words = std::istringstream{ "today is yesterday's tomorrow" };
	for (const auto& s : std::views::istream<std::string>(words))
		std::cout << std::quoted(s, '/') << ' ';
	std::cout << '\n';

	// std::views::all
	const std::vector<int> vec{ 0, 1, 2, 3, 4, 5 };
	for (auto n : std::views::all(vec))
		std::cout << n << ' ';
	std::cout << std::endl;

	// std::ranges::take_view,std::ranges::ref_view
	const std::string str{ "Messy_Test" };
	const std::ranges::take_view tv{ str, 5 };
	std::cout << "second element:" << *(tv.data()+1) << ",size:" << tv.size() << std::endl;
	const std::ranges::ref_view rv{ tv };
	std::cout << "empty:" << rv.empty() << ",size:" << rv.size() << ",begin:" << *rv.begin() << ",end:" << *(rv.end() - 1) << ",data:" << rv.data() << std::endl;
	for (const auto c : rv)
		std::cout << c;
	std::cout << std::endl;

	// std::ranges::owning_view
	using namespace std::literals;
	std::ranges::owning_view ov{ "Messy_Test"s }; // <== ov{std::string{"Messy_Test"}}
	assert(ov.empty() == false && ov.size() == 10 && ov.front() == 'M' && ov.back() == 't');

	// std::ranges::drop_view,std::views::drop
	const auto nums = { 1, 2, 3, 4, 5, 6, 7 };
	for (auto i : std::ranges::drop_view{ nums, 2 })
		std::cout << i << ' ';
	std::cout << std::endl;

	for (auto i : nums | std::views::drop(3))
		std::cout << i << ' ';
	std::cout << std::endl;;

	// std::ranges::join_view
	const std::vector<std::vector<int>> v{ {1, 2}, {3, 4, 5}, {6}, {7, 8, 9} };
	auto jv = std::ranges::join_view(v);
#ifdef __linux__
	for (int const e : jv)
		std::cout << e << ' ';
	std::cout << std::endl;
#endif

	// std::views::counted
	const int a[]{ 1, 2, 3, 4, 5, 6, 7 };
	for (int i : std::views::counted(a, 3))
		std::cout << i << ' '; // 1 2 3
	std::cout << std::endl;

	// std::views::elements
	const std::vector<std::tuple<int, char>> vt {{1, 'A'},{2, 'B'},{3, 'C'},{4, 'D'},{5, 'E'}};
	for (int const e : std::views::elements<0>(vt))
		std::cout << e << ' '; // 1 2 3 4 5
	std::cout << std::endl;

	for (char const e : vt | std::views::elements<1>)
		std::cout << e << ' ';
	std::cout << std::endl;

	return 0;
}

int test_ranges_customization_point_objects()
{
	std::vector v{ 3, 1, 4 };
	auto vi = std::ranges::begin(v);
	std::cout << *vi << std::endl;

	return 0;
}

int test_ranges_helpers()
{
	return 0;
}
