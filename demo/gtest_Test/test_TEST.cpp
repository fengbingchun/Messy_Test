#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "funset.hpp"

TEST(add_test, sum)
{
	EXPECT_EQ(add(1, 2), 3);
	EXPECT_EQ(add(-1, 2), 3) << "this is a error!"; // 可以通过操作符”<<”将一些自定义的信息输出
	EXPECT_EQ(add(2, 3), 5);
	ASSERT_NE(add(3, 4), 1);
	fprintf(stderr, "EXPECT_*版本的断言失败时产生非致命失败，但不会中止当前函数\n");
	ASSERT_EQ(add(3, 4), 2);
	fprintf(stderr, "ASSERT_*版本的断言失败时会产生致命失败，并结束当前函数，当前函数中ASSERT_*后面的语句将不会执行\n");
}

// 临时禁用测试, 只需在逻辑测试名或单元测试名前面加上 DISABLE_ 前缀，它就不会执行了
TEST(DISABLE_add_test, no_run_test) // TEST(add_test, DISABLE_no_run_test)
{
	EXPECT_EQ(add(1, 2), 3);
}
