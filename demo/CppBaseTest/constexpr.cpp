#include "constexpr.hpp"
#include <stdlib.h>
#include <iostream>

////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/131024200
namespace {

// C++14 constexpr functions may use local variables and loops
constexpr int pow2(int base, int exp) noexcept
{
	auto result = 1;
	for (int i = 0; i < exp; ++i) result *= base;
	return result;
}

constexpr unsigned int factorial(unsigned int n) {
	if (n <= 1)
		return 1;
	else
		return n * factorial(n - 1);
}

} // namespace

int test_constexpr_14_1()
{
	constexpr auto value = pow2(2, 4);
	std::cout << "pow2 value:" << value << "\n"; // pow2 value:16

	constexpr auto value2 = factorial(5);
	std::cout << "factorial value:" << value2 << "\n"; // factorial value:120

	return 0;
}

/////////////////////////////////////////////////////////////////
namespace {

// constexpr function: constexpr函数被隐式地指定为内联函数
constexpr int new_sz() { return 42; }
constexpr size_t scale(size_t cnt) { return new_sz() * cnt; }
constexpr int product(int x, int y) { return (x * y); }

// pow前面写的那个constexpr并不表明pow要返回一个const值,它表明的是如果base和exp是编译期常量,pow的返回结果
// 就可以当一个编译期常量使用;如果base和exp中有一个不是编译期常量,则pow的返回结果就将在执行期计算
constexpr int pow(int base, int exp) noexcept
{
	return (exp == 0 ? 1 : base * pow(base, exp - 1));
}

class Debug {
public:
	// constexpr构造函数必须初始化所有数据成员
	constexpr Debug(bool b = true) noexcept : hw_(b), io_(b), other_(b) {}
	constexpr Debug(bool h, bool i, bool o) noexcept : hw_(h), io_(i), other_(o) {}

	constexpr bool any() const noexcept { return hw_ || io_ || other_; }

	constexpr bool get_hw() const noexcept { return hw_; }
	constexpr bool get_io() const noexcept { return io_; }
	constexpr bool get_other() const noexcept { return other_; }

	void set_hw(bool b) noexcept { hw_ = b; }
	void set_io(bool b) noexcept { io_ = b; }
	void set_other(bool b) noexcept { other_ = b; }
	//constexpr void set_hw(bool b) noexcept { hw_ = b; } // C++14
	//constexpr void set_io(bool b) noexcept { io_ = b; }
	//constexpr void set_other(bool b) noexcept { other_ = b; }

private:
	bool hw_, io_, other_;
};

constexpr Debug hw_debug(const Debug& d1, const Debug& d2) noexcept
{
	return d1.get_hw() && d2.get_hw(); // 调用constexpr成员函数
}

} // namespace

int test_constexpr_1()
{
	// constexpr variables
	constexpr int mf = 20; // 20 is a constant expression
	constexpr int limit = mf + 1; // mf + 1 is a constant expression
	
	constexpr int foo = new_sz(); // foo is a constant expression
	std::cout << "foo:" << foo << "\n"; // foo:42

	// 当scale的实参是常量表达式时,它的返回值也是常量表达式;反之则不然
	int arr[scale(2)]; // ok
	int i = 2;
	//int a2[scale(i)]; // error: scale(i)不是常量表达式
	size_t value = scale(i); // ok,constexpr函数不一定返回常量表达式
	std::cout << "value:" << value << "\n"; // value:84

	int sz = 1;
	//constexpr auto array_size = sz; // error, sz的值在编译期未知
	const auto array_size1 = sz; // ok, array_size1是sz的一个const副本

	int arr2[product(2, 3)] = { 1, 2, 3, 4, 5, 6 };
	std::cout << "arr2[5]:" << arr2[5] << "\n"; // arr2[5]:6

	return 0;
}

int test_constexpr_2()
{
	constexpr Debug debug(false, true, false);
	if (debug.any())
		std::cout << "any true" << std::endl; // will output

	if (debug.get_io())
		std::cout << "get_io true" << "\n"; // will output

	constexpr Debug prod(false);
	if (prod.any())
		std::cout << "any true" << std::endl; // will not output

	constexpr auto hw = hw_debug(debug, prod); // 使用constexpr函数的结果来初始化constexpr对象
	std::cout << "hw:" << hw.get_hw() << "\n"; // hw:0

	return 0;
}

