#include "data_type_convert.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/49404293

int test_data_type_convert()
{
	// 1--> int to char[]
	int tmp1 = 100;
	char ch1[15];
	sprintf(ch1, "%d", tmp1);
	std::cout << ch1 << std::endl;

	// 2--> int to string
	int tmp2 = 111;
	char ch2[15];
	sprintf(ch2, "%d", tmp2);
	std::string str2;
	str2 = std::string(ch2);
	std::cout << str2 << std::endl;

	// 3--> int to enum
	enum enum3 {
		A,
		B
	};
	int tmp3 = 222;
	enum3 val3 = static_cast<enum3>(tmp3);
	std::cout << val3 << std::endl;

	// 4--> char[] to string  
	char arr4[] = "this is a sample";
	std::string str4;
	str4 = std::string(arr4);
	std::cout << str4 << std::endl;

	std::string str4_;
	str4_.assign(arr4);
	std::cout << str4_ << std::endl;

	// 5--> char to int
	char ch5 = '8';
	int val5 = ch5 - '0';// val5 is bounded by 0 to 9
	std::cout << val5 << std::endl;

	// 6--> char[] to int
	char arr6[] = "12345";
	int tmp6;
	sscanf(arr6, "%d", &tmp6);
	std::cout << tmp6 << std::endl;

	// 7--> char* to int
	char* pch7 = "444";
	int tmp7;
	tmp7 = atoi(pch7);
	std::cout << tmp7 << std::endl;

	// 8--> char* to float
	char* pch8 = "55.5";
	float tmp8;
	tmp8 = (float)atof(pch8);
	std::cout << tmp8 << std::endl;

	// 9--> char* to double
	char* pch9 = "66.666";
	double tmp9;
	tmp9 = atof(pch9);
	std::cout << tmp9 << std::endl;

	// 10--> float to char[]
	float tmp10 = 11.11;
	char ch10[20];
	sprintf(ch10, "%f", tmp10);
	std::cout << ch10 << std::endl;

	// 11-> int to char*
	int tmp11 = 777;
	char* pch11;
	char ch11[20];
	sprintf(ch11, "%d", tmp11);
	pch11 = ch11;
	std::cout << pch11 << std::endl;

	// 12--> double to char[]
	double tmp12 = 8.888;
	char arr12[20];
	sprintf(arr12, "%f", tmp12);
	std::cout << arr12 << std::endl;

	// 13--> char* to string
	char* pch13 = "hello, world";
	std::string str13;
	str13 = std::string(pch13);
	std::cout << str13 << std::endl;

	// 14--> string to char[]
	std::string str14 = "dog, cat";
	char arr14[256];
	strncpy(arr14, str14.c_str(), sizeof(arr14));
	arr14[sizeof(arr14)-1] = 0;
	std::cout << arr14 << std::endl;

	char arr14_[256];
	strcpy(arr14_, str14.c_str());
	std::cout << arr14_ << std::endl;

	// 15--> string to const char*
	std::string str15 = "ha ha";
	const char* pch15;
	pch15 = str15.c_str();
	std::cout << pch15 << std::endl;

	// 16--> float to int
	float ftmp16 = 99.99;
	int tmp16;
	tmp16 = static_cast<int>(ftmp16);// static_cast<int>(ftmp16 + 0.5)
	std::cout << tmp16 << std::endl;

	// 17--> vector<float> to float*
	std::vector<float> vec;
	for (int i = 0; i < 10; i++)
		vec.push_back(i * 1.5);
	float *p = &vec[0];
	for (int i = 0; i < 10; i++)
		std::cout << p[i] << std::endl;

	// 18--> int[] to vector<int>
	int x[5] = { 1, 2, 3, 4, 5 };
	std::vector<int> v(x, x + sizeof(x) / sizeof(x[0]));
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;

	return 0;
}
