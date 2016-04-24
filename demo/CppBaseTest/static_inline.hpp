#ifndef FBC_MESSY_TEST_STATIC_INLINE_HPP_
#define FBC_MESSY_TEST_STATIC_INLINE_HPP_

class FastMath {
public:
	int round(float value) { //类体内部定义的函数默认就是内联函数,也可以加 inline 关键字，但这是多余的
		return (int)(value + (value >= 0 ? 0.5f : -0.5f));
	}

	inline int floor(float value); // 声明为内联函数
};

int FastMath::floor(float value)
{
	int i = round(value);
	float diff = (float)(value - i);
	return i - (diff < 0);
}

static inline int Ceil(float value)
{
	int i = (int)(value + (value >= 0 ? 0.5f : -0.5f));
	float diff = (float)(i - value);
	return i + (diff < 0);
}

void test_static_inline1();
void test_static_inline2();

#endif // FBC_MESSY_TEST_STATIC_INLINE_HPP_