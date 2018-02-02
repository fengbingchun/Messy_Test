#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51626705

void test1(); // 内存泄露
void test2(); // 非法访问
void test3(); // 未初始化读
void test4(); // Heap 操作参数错误(Invalid Heap Argument)

int main()
{
	// reference: http://www.ibm.com/developerworks/cn/linux/1309_liuming_drmemory/
	test4();

	std::cout << "ok" << std::endl;
	return 0;
}

void test1()
{
	char *ptr;
	for (int i = 0; i<100; i++) {
		ptr = (char*)malloc(i);

		if (i % 2) free(ptr);
	}
}

void test2()
{
	char *x = (char*)malloc(8);
	char c = *(x + 8); // buffer overlow
	free(x);
	c = *x; // read free memory
}

typedef struct T_ {
	char a;
	char b;
}T;

void test3()
{
	T a, b;
	char x;
	a.a = 'a';
	a.b = 'b';
	b.a = x; // error C4700:使用了未初始化的局部变量x,若使vs2013能够正常编译，需将配置属性中的C/C++ SDL检查关闭
	if (b.a == 10)
		memcpy(&b, &a, sizeof(T));
}

void test4()
{
	char * ptr = NULL;
	ptr = new char;
	free(ptr);
	free(ptr); //
}

