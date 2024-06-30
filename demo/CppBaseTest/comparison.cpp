#include "comparison.hpp"
#include <iostream>
#include <compare>
#include <random>
#include <vector>
#include <string>

// Blog: https://blog.csdn.net/fengbingchun/article/details/140078283

namespace {

template<typename T>
void compare(T x, T y)
{
    auto ret = x <=> y;
    std::cout << "name: " << typeid(ret).name() << std::endl;
    if (ret < 0)
        std::cout << "x < y:" << x << "," << y << std::endl;
    else if (ret == 0)
        std::cout << "x == y:" << x << "," << y << std::endl;
    else
        std::cout << "x > y:" << x << "," << y << std::endl;
}

struct Person {
    std::string name_{""};
    int age_{0};

    auto operator<=>(const Person& other) const noexcept
    {
        if (age_ != other.age_)
            return age_ <=> other.age_;
        
        if (name_ != other.name_)
            return name_ <=> other.name_;

        if (age_ == other.age_ && name_ == other.name_) {
            //return name_ <=> other.name_;
            return std::strong_ordering::equal;
        }
    }
};

struct Person2 {
    // 注意: age_和name_定义的顺序不同,会产生不同的比较结果
    int age_{ 0 };
    std::string name_{ "" };
    //int age_{ 0 };

    auto operator<=>(const Person2&) const = default;
    //bool operator==(const Person2&) const = default;
};

} // namespace

int test_comparison_three_way()
{
    // numerical comparison
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1000);

    auto x = dist(gen);
    auto y = dist(gen);
    compare(x, y);
    compare(y, x);
    compare(5, 5);

    // vector comparison
    const std::vector<int> a{ 1,2,3 }, b{ 1,2,4 };
    auto ret = a <=> b;
    if (ret < 0)
        std::cout << "a < b" << std::endl;
    else if (ret == 0)
        std::cout << "a == b" << std::endl;
    else
        std::cout << "a > b" << std::endl;

    // std::string comparison
    const std::string str1{ "Hello" }, str2{ "hello" };
    compare(str1, str2);
    compare(str2, str1);
    compare(std::string("hello"), std::string("hello"));

    // struct/class comparison
    const Person tom{ "Tom", 20 }, lisy{ "Lisy", 21 }, bob{ "Bob", 20 };

    ret = tom <=> bob;
    if (ret > 0) std::cout << "tom > bob" << std::endl;
    if (ret >= 0) std::cout << "tom >= bob" << std::endl;
    if (ret != 0) std::cout << "tom != bob" << std::endl;

    ret = tom <=> lisy;
    if (ret < 0) std::cout << "tom < lisy" << std::endl;
    if (ret <= 0) std::cout << "tom <= lisy" << std::endl;
    if (ret != 0) std::cout << "tom != lisy" << std::endl;
    if (ret == 0) std::cout << "tom == lisy" << std::endl;

    ret = tom <=> tom;
    if (ret == 0) std::cout << "tom == tom" << std::endl;

	return 0;
}

int test_comparison_default()
{
    const Person2 tom{ 20, "Tom" }, lisy{ 21, "Lisy" }, bob{ 20, "Bob" };

    auto ret = tom <=> bob;
    if (ret > 0) std::cout << "tom > bob" << std::endl;
    if (ret >= 0) std::cout << "tom >= bob" << std::endl;
    if (ret != 0) std::cout << "tom != bob" << std::endl;

    ret = tom <=> lisy;
    if (ret < 0) std::cout << "tom < lisy" << std::endl;
    if (ret <= 0) std::cout << "tom <= lisy" << std::endl;
    if (ret != 0) std::cout << "tom != lisy" << std::endl;
    if (ret == 0) std::cout << "tom == lisy" << std::endl;

    ret = tom <=> tom;
    if (ret == 0) std::cout << "tom == tom" << std::endl;

    if (tom == tom) std::cout << "tom == tom" << std::endl;
    if (tom > bob) std::cout << "tom > bob" << std::endl;
    if (tom >= bob) std::cout << "tom >= bob" << std::endl;
    if (tom != lisy) std::cout << "tom != lisy" << std::endl;
    if (tom < lisy) std::cout << "tom < lisy" << std::endl;
    if (tom <= lisy) std::cout << "tom <= lisy" << std::endl;

    return 0;
}
