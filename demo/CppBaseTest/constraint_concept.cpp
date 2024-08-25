#include "constraint_concept.hpp"
#include <type_traits>
#include <iostream>
#include <vector>
#include <string>

// Blog: https://blog.csdn.net/fengbingchun/article/details/141526951

namespace {

template<typename T>
requires std::is_integral_v<T> || std::is_floating_point_v<T> void print_value(T value) // requires clause
{
	std::cout << "value is: " << value << std::endl;
}

template<typename T>
concept Integral = std::is_integral_v<T> && sizeof(T) == 4;

template<typename T>
concept unsigned_integral = Integral<T> && !std::is_signed_v<T>;

auto func(Integral auto value)
{
	std::cout << "integer value is: " << value << std::endl;
}

template<typename T>
concept Container = requires(T t) // requires expression
{
    { std::size(t) } -> std::same_as<std::size_t>;
    { std::begin(t) } -> std::same_as<typename T::iterator>;
    { std::end(t) } -> std::same_as<typename T::iterator>;
};

template<Container C>
class ContainerWrapper
{
    // reference: https://www.geeksforgeeks.org/constraints-and-concepts-in-cpp-20/
public:
    ContainerWrapper(C c) : container(c) {}

    void print()
    {
        for (auto it = std::begin(container); it != std::end(container); ++it)
            std::cout << *it << " ";
        std::cout << "; size:" << container.size() << std::endl;
    }

private:
    C container;
};

} // namespace

int test_constraint()
{
	print_value(66);
	//print_value("hello"); // error C2672: "print_value":未找到匹配的重载函数
    print_value(6.6);

	return 0;
}

int test_concept()
{
	func(6);
	//func(6.6); // error C2672: "func":未找到匹配的重载函数
    short val{ 8 };
    //func(val); // error C2672: "func":未找到匹配的重载函数

    std::vector<int> vec1{ 1, 2, 3 };
    ContainerWrapper wrapper1(vec1);
    wrapper1.print();

    std::vector<std::string> vec2{ "hello", "world", "!"};
    ContainerWrapper wrapper2(vec2);
    wrapper2.print();

	return 0;
}
