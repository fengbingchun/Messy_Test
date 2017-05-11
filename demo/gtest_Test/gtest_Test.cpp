#include <iostream>
#include <vector>
#include <gtest/gtest.h>

int main()
{
	std::vector<char*> argv{
#ifdef _DEBUG
		"E:/GitCode/Messy_Test/lib/dbg/x64_vc12/gtest_Test.exe",
#else
		"E:/GitCode/Messy_Test/lib/rel/x64_vc12/gtest_Test.exe",
#endif
		"--gtest_repeat=2", // 重复运行测试
		//"--gtest_break_on_failure", // 遇到failure退出
		"--gtest_filter=*", // 指定需要运行的tests
		//"--gtest_print_time=0", // don't print the elapsed time of each test
		"--gtest_output=xml:E:/GitCode/Messy_Test/testdata/info.xml" // 结果输出到指定的xml文件
	};
	int argc = argv.size();

	// Initializes Google Test.  This must be called before calling RUN_ALL_TESTS()
	// 初始化并解析命令行参数
	testing::InitGoogleTest(&argc, argv.data());

	// Use this function in main() to run all tests.  It returns 0 if all
	// tests are successful, or 1 otherwise
	int ret = RUN_ALL_TESTS();
	if (ret == 0) fprintf(stderr, "========== all tests are succeseful =========\n");
	else fprintf(stderr, "********** some tests are failed **********\n");

	return 0;
}
