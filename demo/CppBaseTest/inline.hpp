#ifndef FBC_CPPBASETEST_INLINE_HPP_
#define FBC_CPPBASETEST_INLINE_HPP_

#include <string>

namespace inline_ {

class InlineVariable {
public:
	inline static int var{ 10 }; // 不带inline,则只能在类外初始化;即使在类外初始化,如果被多个cpp文件包含也会error;带inline后,即使被多个cpp文件包含也OK
	const char* csdn_addr{ "https://blog.csdn.net/fengbingchun/" };
	static constexpr int num{ 6 }; // 对于静态成员,constexpr修饰符隐含着inline,等价于: inline static constexpr int num{ 6 };

	inline static std::string name{ "Messy_Test" }; // 整个程序中只有一个
	inline static thread_local int count{ 1 }; // 每个线程有一个
	std::string city{ "BeiJing" }; // 每个实例有一个
};

inline InlineVariable inline_variable; // 不带inline,则会报重复定义;带inline后,即使被多个cpp文件包含也OK
inline thread_local InlineVariable inline_variable2; // 每个线程一个对象

int test_inline_1();
int test_inline_variable_1();

} // namespace inline_

#endif // FBC_CPPBASETEST_INLINE_HPP_
