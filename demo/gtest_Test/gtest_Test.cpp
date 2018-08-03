#include <iostream>
#include <vector>
#include <gtest/gtest.h>

// Blog: http://blog.csdn.net/fengbingchun/article/details/72353374

int main(int argc, char* argv[])
{
	std::vector<char*> argv_{
		argv[0],
		//"--gtest_repeat=2 ", // 重复运行测试次数
		//"--gtest_break_on_failure", // 遇到failure退出
		"--gtest_filter=*", // 指定需要运行的tests
		//"--gtest_print_time=0", // don't print the elapsed time of each test
#ifdef __linux__
		"--gtest_output=xml:testdata/info.xml" // 结果输出到指定的xml文件
#else
		"--gtest_output=xml:E:/GitCode/Messy_Test/testdata/info.xml" // 结果输出到指定的xml文件
#endif
	};
	int argc_ = argv_.size();

	// Initializes Google Test.  This must be called before calling RUN_ALL_TESTS()
	testing::InitGoogleTest(&argc_, argv_.data());

	// Use this function in main() to run all tests.  It returns 0 if all
	// tests are successful, or 1 otherwise
	int ret = RUN_ALL_TESTS();
	if (ret == 0) fprintf(stderr, "========== all tests are succeseful =========\n");
	else fprintf(stderr, "********** some tests are failed **********\n");

	return ret;
}

