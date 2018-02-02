#include <iostream>
#include "../../src/VLD/vld.h"

// Blog: http://blog.csdn.net/fengbingchun/article/details/44195959

void fun()
{
	char* tmp = new char[10];
	memset(tmp, 0, 10);
}

int main(int argc, char* argv[])
{
	fun();

	std::cout<<"ok!"<<std::endl;

	return 0;
}

