#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51114925

#ifdef _DEBUG
	#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
	#define DEBUG_CLIENTBLOCK
#endif

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>

	#define new DEBUG_CLIENTBLOCK
#endif

void test_c()
{
	int* p = (int*)malloc(10 * sizeof(int));

	//free(p);
}

void test_cpp()
{
	int* p = new int[10];

	//delete [] p;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//_CrtDumpMemoryLeaks();
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	test_c();
	test_cpp();

	std::cout << "ok" << std::endl;
}
