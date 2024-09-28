#include "concepts.hpp"
#include <concepts>
#include <iostream>
#include <string>
#include <vector>

// Blog: https://blog.csdn.net/fengbingchun/article/details/142618418

namespace {

struct A{
	int x, y;

	//A(int x,int y):x(x), y(y) {}

	bool operator==(const A& other) const
	{
		return x == other.x && y == other.y;
	}

	//bool operator!=(const A& other) const
	//{
	//	return !(*this == other);
	//}
};

struct B{
	int x, y;

	auto operator<=>(const B& other) const = default;
	auto operator()() const
	{
		return x % 2 == 0;
	}
};

struct C : public A{
	C(C&&) = delete;
	C& operator=(C&&) = delete;
};

struct D : private A{
	int x, y;

	D() = delete;

	auto operator()() 
	{
		return (x + y);
	}
};

using INT = int;
using FLOAT = float;

} // namespace

int test_concepts_core_lanuage()
{
	static_assert(std::same_as<A, B> == false, "A and B are not the same"); // std::is_same_v<T, U>
	static_assert(std::derived_from<C, A> == true);
	static_assert(std::derived_from<A, C> == false);
	static_assert(!std::derived_from<D, A>);
	static_assert(std::convertible_to<C, A>);
	static_assert(std::common_reference_with<C, A>);
	static_assert(std::common_with<C, A>);

	static_assert(std::integral<INT>);
	static_assert(!std::integral<FLOAT>);
	static_assert(std::signed_integral<INT>);
	static_assert(!std::unsigned_integral<INT>);
	static_assert(std::floating_point<FLOAT>);

	static_assert(std::assignable_from<std::string&, std::string>);
	static_assert(!std::assignable_from<std::string, std::string>);
	static_assert(!std::assignable_from<std::string, std::string&>);

	static_assert(std::default_initializable<A>);
	static_assert(std::move_constructible<B>);
	static_assert(std::copy_constructible<D>);

	return 0;
}

int test_concepts_comparison()
{
	static_assert(std::equality_comparable<A>);
	static_assert(std::equality_comparable<B>);
	static_assert(std::equality_comparable<C>);

	static_assert(!std::totally_ordered<A>);
	static_assert(std::totally_ordered<B>);

	return 0;
}

int test_concepts_object()
{
	static_assert(std::movable<A>);
	static_assert(std::movable<B>);
	static_assert(!std::movable<C>);

	static_assert(std::copyable<A>);
	static_assert(std::copyable<B>);
	static_assert(!std::copyable<C>);

	static_assert(std::semiregular<A>);
	static_assert(!std::semiregular<D>);

	static_assert(std::regular<A>);
	static_assert(!std::regular<D>);

	return 0;
}

int test_concepts_callable()
{
	static_assert(!std::regular_invocable<A>);
	static_assert(std::regular_invocable<D>);

	static_assert(!std::predicate<A>);
	static_assert(std::predicate<B>);

	static_assert(!std::relation<A, B, C>);


	return 0;
}

int test_concepts_customization_point_objects()
{
	int x{ 1 }, y{ -1 };
	std::cout << "x=" << x << ", y=" << y << std::endl;
	std::ranges::swap(x, y);
	std::cout << "x=" << x << ", y=" << y << std::endl;

	std::string addr1{ "TianJin" }, addr2{ "BeiJing" };
	std::cout << "addr1=" << addr1 << ", addr2=" << addr2 << std::endl;
	std::ranges::swap(addr1, addr2);
	std::cout << "addr1=" << addr1 << ", addr2=" << addr2 << std::endl;

	auto print = [](const std::vector<int>& vec) {
		for (const auto& value : vec)
			std::cout << value << ",";
		std::cout << std::endl;
	};

	std::vector vec1{ 1, 2, 3 }, vec2{ -1,-2,-3,-4,-5 };
	std::cout << "vec1: "; print(vec1);
	std::cout << "vec2: "; print(vec2);
	std::ranges::swap(vec1, vec2);
	std::cout << "vec1: "; print(vec1);
	std::cout << "vec2: "; print(vec2);

	return 0;
}
