#include "funset.hpp"
#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <type_traits>

// Blog: https://blog.csdn.net/fengbingchun/article/details/169651492

namespace deducing_this_ {

class TestDeduce {
public:
    //std::string& get() & { std::cout << "&\n";  return value_; }                                // 返回内部成员的可修改引用,只允许左值对象调用(&)
    //const std::string& get() const& { std::cout << "const&\n";  return value_; }                // 返回内部成员的只读引用,只允许左值对象调用
    //std::string&& get() && { std::cout << "&&\n"; return std::move(value_); }                   // 只允许右值对象调用(&&)
    //const std::string&& get() const&& { std::cout << "const&&\n";  return std::move(value_); }  // 只允许右值对象调用

    template <typename Self>
    auto&& get(this Self&& self) {  // 此一个函数可替代上面4种重载版本
        using T = std::remove_reference_t<Self>;
        constexpr bool is_const = std::is_const_v<T>;
        constexpr bool is_lval = std::is_lvalue_reference_v<Self>;

        if constexpr (!is_const && is_lval)
            std::cout << "&\n";
        else if constexpr (is_const && is_lval)
            std::cout << "const&\n";
        else if constexpr (!is_const && !is_lval)
            std::cout << "&&\n";
        else if constexpr (is_const && !is_lval)
            std::cout << "const&&\n";

        return std::forward<Self>(self).value_;
    }

    void foo(this TestDeduce const& self, int i); // same as void foo(int i) const &;
    void bar(this TestDeduce self, int i); // pass object by value: makes a copy of "*this"

private:
    std::string value_{ "hello" };
};

} // namespace deducing_this_

int test_deducing_this()
{
    // overload
    deducing_this_::TestDeduce p;
    const deducing_this_::TestDeduce cp;

    p.get() = "world"; // &
    p.get(); // &
    cp.get(); // const&

    std::move(p).get(); // &&
    deducing_this_::TestDeduce{}.get(); // &&
    std::move(cp).get(); // const&&
    const deducing_this_::TestDeduce{}.get(); // const&&

    // recursive lambda
    std::function<int(int)> fib1 = [&](int n) {
        if (n <= 1) return n;
        return fib1(n - 1) + fib1(n - 2);
    };

    auto fib2 = [](this auto&& self, int n) -> int {
        if (n <= 1) return n;
        return self(n - 1) + self(n - 2);
    };

    std::cout << "fib1: " << fib1(10) << "; fib2: " << fib2(10) << std::endl; // fib1: 55; fib2: 55

	return 0;
}

