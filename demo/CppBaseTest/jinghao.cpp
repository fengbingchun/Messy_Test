#include "jinghao.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/44133701

//test1
#define WARN_IF(EXP) \
	if (EXP) \
	fprintf(stderr, "warning: "#EXP" \n");

//test2
#define STR(s) #s

//test3
#define _STRI(s) #s
#define STRI(s) _STRI(s) //转换宏

//test4
#define paster(n) printf("token"#n" = %d\n", token##n)

//test5
#define _CONS(a, b) int(a##+##b)
#define CONS(a, b) _CONS(a, b) //转换宏

//test6
#define  _GET_FILE_NAME(f)   #f
#define  GET_FILE_NAME(f)    _GET_FILE_NAME(f)  //转换宏

//test7
#define  _TYPE_BUF_SIZE(type)  sizeof #type
#define  TYPE_BUF_SIZE(type)   _TYPE_BUF_SIZE(type) 

//test8
#define D(x)  #@x  //仅对单一标记转换有效

int test_jinghao1()
{
	//test1
	int divider = 0;
	WARN_IF(divider == 0);// warning: divider == 0

	//test2
	printf("int max: %s\n", STR(INT_MAX));// int max: INT_MAX

	//test3
	printf("int max: %s\n", STRI(INT_MAX));// int max: 2147483647

	//test4
	int token9 = 9;
	paster(9);// token9 = 9

	//test5
	int A = 15, B = 2;
	printf("A + B = %d\n", CONS(A, B));// A + B = 17

	//test6
	char  FILE_NAME[] = GET_FILE_NAME(__FILE__);
	std::cout << FILE_NAME << std::endl;// "..\\..\..\\demo\\CppBaseTest\\jinghao.cpp"

	//test7
	std::cout << TYPE_BUF_SIZE(INT_MAX) << std::endl;// 11

	//test8
	std::cout << D(F) << std::endl;//F

	return 0;
}

#define CHECK_PARAMS(condition, ret)			\
	{if (!(condition)) {						\
		fprintf(stderr, "Error: "#condition"  %d\n", ret);	\
		return ret;}}

int test_jinghao2()
{
	int* param1 = nullptr;

	CHECK_PARAMS(param1, -1);// Error: param1 -1

	return 0;
}
