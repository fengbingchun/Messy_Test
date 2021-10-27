#include "coding_optimizations.hpp"
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <chrono>
#include <string>

// Blog: https://blog.csdn.net/fengbingchun/article/details/85934251

namespace coding_optimizations_ {

// reference: 《提高C++性能的编程技术》：第十三章：编码优化

namespace {
static char uppercaseTable[256];

void initLookupTable()
{
	for (int i = 0; i < 256; ++i) {
		uppercaseTable[i] = toupper(i);
	}
}

class Student1 {
public:
	// C++保证在Student1的构造函数体执行之前，所有的成员对象已经创建完成，此处即string型的name对象。
	// 既然我们没有显示告诉编译器如何构造它，编译器就插入了对string默认构造函数的调用。该调用在Student1的构造函数体执行之前进行。
	Student1(char* nm) { name = nm; }
private:
	std::string name;
};

class Student2 {
public:
	// 通过在Student2的构造函数初始化列表中显示指明string构造函数，可以避免Student1中的无效计算
	// 由于我们明确告诉编译器使用哪个string构造函数，编译器将不再隐式地调用string默认构造函数。因此我们实现了一步完成string成员对象的构造
	Student2(char* nm) : name(nm) {}
private:
	std::string name;
};

} // namespace

int test_coding_optimizations_1()
{
	initLookupTable();

	std::chrono::high_resolution_clock::time_point time_start, time_end;
	const int count{10000}, count2{100000};
	const char* header{"afaIELQEadsfjl943082jdfaadfajqwppreijfadfadfaoueheufiekasdLdamsaldfadfawweevKKA"};
	int length = strlen(header);
	char ch;
 
{ // test lowercase letter to uppercase letter: normal
	time_start = std::chrono::high_resolution_clock::now();
	for (int t = 0; t < count; ++t) {
		for (int i = 0; i < count; ++i) {
			char* p = const_cast<char*>(header);
			for (int j = 0; j < length; ++j) {
				ch = toupper(*p++);
				//fprintf(stdout, "%c", ch);	
			}
			//fprintf(stdout, "\n");
		}
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "lowercase letter to uppercase letter normal time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // test lowercase letter to uppercase letter: pre-calculated
	time_start = std::chrono::high_resolution_clock::now();
	for (int t = 0; t < count; ++t) {
		for (int i = 0; i < count; ++i) {
			char* p = const_cast<char*>(header);
			for (int j = 0; j < length; ++j) {
				ch = uppercaseTable[*p++];
				//fprintf(stdout, "%c", ch);	
			}
			//fprintf(stdout, "\n");
		}
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "lowercase letter to uppercase letter pre-calculated time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // test unuseful calculate: normal
	time_start = std::chrono::high_resolution_clock::now();
	for (int t = 0; t < count2; ++t) {
		Student1 st("beijing");
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "unuseful calculate normal time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // test unuseful calculate: list init
	time_start = std::chrono::high_resolution_clock::now();
	for (int t = 0; t < count2; ++t) {
		Student2 st("beijing");
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "unuseful calculate list init time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

	return 0;
}

} // namespace coding_optimizations_

