#define __STDC_WANT_LIB_EXT1__ 1
#include "cplusplus_secure_coding.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cstddef>
#include <string>
#include <memory>
#include <iostream>
#include <exception>
#include <algorithm>
#include <climits>

// reference: 《C和C++安全编码(原书第2版)》

namespace cplusplus_secure_coding_ {

///////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/105325508

namespace {

void calculate_array_size(int arr1[], char arr3[])
{
	int arr2[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	fprintf(stdout, "arr2 element count: %d\n", sizeof(arr2) / sizeof(arr2[0])); // 8

	// 此处arr1是一个参数，所以它的类型是指针，在x64中，sizeof(int*)=8，在x86中,sizeof(int*)=4
	// 数组名作为函数参数会被C语言转换为指针，而不是sizeof的"参数"，因为sizeof不是函数而是运算符
	// sizeof运算符在应用于声明为数组或函数类型的参数时，它产生调整后的(即指针)类型大小
	fprintf(stdout, "arr1 element count: %d\n", sizeof(arr1) / sizeof(arr1[0])); // 2, error
	fprintf(stdout, "sizeof(int*): %d\n", sizeof(int*)); // 8 // note: x64, not x86

	fprintf(stdout, "arr3 byte count: %d\n", strlen(arr3)); // 10
}

void string_literal()
{
	const char s1[4] = "abc"; // 不推荐,任何随后将数组作为一个空字节结尾的字符串的使用都会导致漏洞，因为s1没有正确地以空字符结尾
	const char s2[] = "abc";  // 推荐,对于一个用字符串字面值初始化的字符串，不指定它的界限,因为编译器会自动为整个字符串字面值分配足够的空间，包括终止的空字符
	fprintf(stdout, "s1 length: %d, s2 length: %d\n", strlen(s1), strlen(s2)); // 3, 3
}

void string_size()
{
	wchar_t wide_str1[] = L"0123456789";
	// 计算容纳宽字符串的一个副本所需的字节数(包括终止字符)
	wchar_t* wide_str2 = (wchar_t*)malloc((wcslen(wide_str1) + 1) * sizeof(wchar_t));
	free(wide_str2);
}

int test_secure_coding_2_1()
{
	int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	char arr3[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0' };
	calculate_array_size(arr1, arr3);

	string_literal();

	char x = 'a';
	fprintf(stdout, "sizeof('a'): %d, sizeof(x): %d\n", sizeof('a'), sizeof(x)); // 1, 1

	string_size();

	return 0;
}

void test_unbounded_string_copy()
{
	char buf[12];
	std::cin >> buf; // 如果用户输入多于11个字符，会导致写越界
	std::cout << "echo: " << buf << std::endl;

	std::cin.width(12); // 通过将域宽成员设置为字符数组的长度消除了溢出
	std::cin >> buf;
	std::cout << "echo: " << buf << std::endl;
}

void test_off_by_one_error()
{
#ifdef _MSC_VER
	char s1[] = "012345678";
	char s2[] = "0123456789";

	strcpy_s(s1, sizeof(s2), s2); // error
	//char* s3 = (char*)malloc(strlen(s2) + 1); // note: when free, it will crash
	char s4[20];
	int r = strcpy_s(s4, _countof(s4), s2); // gcc version > 5.0
	fprintf(stdout, "s4: %s\n", s4);

	//char* dest = (char*)malloc(strlen(s1)); // error
	char* dest = (char*)malloc(strlen(s1) + 1);
	int i = 0;
	//for (i = 1; i <= 11; i++) // error
	for (i = 0; i < strlen(s1); ++i) {
		dest[i] = s1[i];
	}
	dest[i] = '\0';

	fprintf(stdout, "dest: %s\n", dest);
	free(dest);
#endif
}

void test_null_termination_error()
{
	char a[16], b[16], c[16];
	// No null-character is implicitly appended at the end of destination if source is longer than num.
	// Thus, in this case, destination shall not be considered a null terminated C string (reading it as such would overflow)
	//strncpy(a, "0123456789abcdef", sizeof(a)); // error, a并未以空字符结尾
	//fprintf(stdout, "a: %s\n", a); // a并未以空字符结尾,导致无法正常打印a
	strncpy(a, "0123456789abcde", sizeof(a));
	//strncpy(b, "0123456789abcdef", sizeof(b)); // error, b并未以空字符结尾
	//fprintf(stdout, "b: %s\n", b); // b并未以空字符结尾,导致无法正常打印b
	strncpy(b, "0123456789abcde", sizeof(b));
	// To avoid overflows, the size of the array pointed by destination shall be long enough to contain the 
	// same C string as source (including the terminating null character)
	strcpy(c, a); // 若a并未以空字符结尾,那么c也未以空字符结尾，而且c可能写得远远超出了数组界限，导致无法正常打印c
	fprintf(stdout, "a: %s, b: %s, c: %s\n", a, b, c);

	char d[16];
	strncpy(d, "0123456789abcdefghijk", sizeof(d) - 1);
	d[sizeof(d) - 1] = '\0';
	fprintf(stdout, "d: %s\n", d);
}

int test_secure_coding_2_2()
{
	//test_unbounded_string_copy();
	//test_off_by_one_error();
	test_null_termination_error();

	return 0;
}

void test_basic_string()
{
	std::string str;
	std::cin >> str;
	std::cout << "str: " << str << std::endl;

	// 使用迭代器编译一个字符串的内容
	for (std::string::const_iterator it = str.cbegin(); it != str.cend(); ++it) {
		std::cout << *it;
	}
	std::cout << std::endl;
}

void test_string_reference_invalid()
{
	char input[] = "feng;bing;chun;email";
	std::string email;
	std::string::iterator loc = email.begin();
	for (int i = 0; i < strlen(input); ++i) {
		if (input[i] != ';') {
			//email.insert(loc++, input[i]); // 非法迭代器
			loc = email.insert(loc, input[i]);
		} else {
			//email.insert(loc++, ' '); // 非法迭代器
			loc = email.insert(loc, ' ');
		}
		++loc;
	}
	fprintf(stdout, "email: %s\n", email.c_str());
}

int test_secure_coding_2_4()
{
	//test_basic_string();
	test_string_reference_invalid();

	return 0;
}

void test_fgets()
{
	char buf[10];

	if (fgets(buf, sizeof(buf), stdin)) {
		// fgets成功，扫描查找换行符
		char* p = strchr(buf, '\n');
		if (p) {
			*p = '\0';
		} else {
			// 未找到换行符,刷新stdin到行尾
			int ch;
			while (((ch = getchar()) != '\n') && !feof(stdin) && !ferror(stdin));
		}
	} else { // fgets失败
		fprintf(stderr, "fail to fgets\n");
	}

	fprintf(stdout, "buf: %s\n", buf);
}

void test_getchar()
{
	const int BUFSIZE = 10;
	char buf[BUFSIZE];
	int ch;
	int index = 0;
	int chars_read = 0;

	while (((ch = getchar()) != '\n') && !feof(stdin) && !ferror(stdin)) {
		if (index < BUFSIZE - 1) {
			buf[index++] = (unsigned char)ch;
		}
		++chars_read;
	}

	buf[index] = '\0'; // 空终结符

	if (feof(stdin)) { fprintf(stderr, "EOF\n"); } // 处理EOF
	if (ferror(stdin)) { fprintf(stderr, "ERROR\n"); } // 处理错误
	if (chars_read > index) { fprintf(stderr, "truncated\n"); } // 处理截断

	fprintf(stdout, "buf: %s\n", buf);
}

void test_gets_s()
{
#ifdef _MSC_VER
	char buf[10];
	if (gets_s(buf, sizeof(buf)) == NULL) { // 处理错误
		fprintf(stderr, "fail to gets_s\n");
	}

	fprintf(stdout, "buf: %s\n", buf);
#endif
}

void test_strncpy()
{
	char source[] = "http://blog.csdn.net/fengbingchun";
	char* dest = (char*)malloc(sizeof(source) + 1);
	size_t dest_size = strlen(dest);
	strncpy(dest, source, dest_size - 1);
	dest[dest_size - 1] = '\0';
	fprintf(stdout, "dest: %s\n", dest);
	free(dest);
}

void test_strncpy_s()
{
#ifdef _MSC_VER
	char src1[100] = "hello";
	char src2[7] = { 'g', 'o', 'o', 'd', 'b', 'y', 'e' };
	char dst1[6], dst2[5], dst3[5];
	errno_t r1, r2, r3;

	r1 = strncpy_s(dst1, sizeof(dst1), src1, sizeof(src1));
	fprintf(stdout, "dst1: %s, r1: %d\n", dst1, r1); // hello\0
	r2 = strncpy_s(dst2, sizeof(dst2), src2, 4);
	fprintf(stdout, "dst2: %s, r2: %d\n", dst2, r2); // good\0
	//r3 = strncpy_s(dst3, sizeof(dst3), src1, sizeof(src1)); // crash, r3并没有返回非零值，原因应该是没有开启运行时约束
	//fprintf(stdout, "dst3: %s, r3: %d\n", dst3, r3);
#endif
}

int test_secure_coding_2_5()
{
	//test_fgets();
	//test_getchar();
	//test_gets_s();
	//test_strncpy();
	test_strncpy_s();

	return 0;
}

} // namespace

int test_secure_coding_2()
{
	//return test_secure_coding_2_1();
	//return test_secure_coding_2_2();
	//return test_secure_coding_2_4();
	return test_secure_coding_2_5();
}

///////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/105458861

namespace {

static int GLOBAL_INIT = 1; // 数据段，全局
static int global_uninit; // BSS段，全局
int test_secure_coding_3_1() // 栈，局部
{
	int local_init = 1; // 栈，局部
	int local_uninit; // 栈，局部
	static int local_static_init = 1; // 数据段，局部
	static int local_static_uninit; // BSS段，局部
	// buff_ptr的存储空间是栈，局部；分配的内存是堆，局部
	int* buff_ptr = (int*)malloc(32);
	free(buff_ptr);

	return 0;
}

void good_function(const char* str) {} // 栈
// 一个有漏洞的程序，其BSS段中的函数指针可以被覆写
void test_secure_coding_3_2(int argc, char* argv[]) // 栈
{
	const int BUFFSIZE = 10; // 栈
	static char buff[BUFFSIZE]; // BSS段
	static void(*funPtr)(const char* str); // BSS段
	funPtr = &good_function;
	// 当argv[1]的长度大于BUFFSIZE的时候，就会发生缓冲区溢出,这个缓冲区溢出漏洞
	// 可以被利用来将函数指针值覆写为外壳代码的地址，从而将程序的控制权转移到任意的代码
	// 当执行由funPtr标识的函数时，外壳代码将会取代good_function()得以执行
	strncpy(buff, argv[1], strlen(argv[1])); 
	(void)(*funPtr)(argv[2]);
}

// 一个有漏洞的程序，可以被利用来实现任意内存写,修改对象指针
void test_secure_coding_3_3(void* arg, size_t len)
{
	char buff[100];
	long val = 1;
	long* ptr = &val;
	// 一个无界内存复制，在溢出缓冲区后，攻击者可以覆写ptr和val
	// 当执行*ptr=val时，就会发生任意内存写
	memcpy(buff, arg, len);
	*ptr = val;
}

#ifndef _MSC_VER
static void create(void) ; //__attribute__((constructor)); // 测试test_secure_coding_3_6()时再打开
static void destroy(void); // __attribute__((destructor));

static void create(void)
{
	fprintf(stdout, "create called.\n");
}

static void destroy(void)
{
	fprintf(stdout, "destructor called.\n");
}
#endif

void test_secure_coding_3_6()
{
#ifndef _MSC_VER
	fprintf(stdout, "create: %p.\n", create);
	fprintf(stdout, "destroy: %p.\n", destroy);
	exit(0);
#endif
}

char* glob;

void test(void)
{
	fprintf(stdout, "%s", glob);
}

int test_secure_coding_3_8()
{
	atexit(test);
	glob = "Exiting.\n";

	return 0;
}

int test_secure_coding_3_9()
{
	jmp_buf env;
	int val;

	val = setjmp(env);

	fprintf(stdout, "val is %d\n", val);

	if (!val) longjmp(env, 1);

	return 0;
}

int test_secure_coding_3_10()
{
	try {
		//throw 10;
		throw "overflow";
	}
	catch(int x) {
		fprintf(stderr, "exception value: %d\n", x);
	}
	catch (const char* str) {
		fprintf(stderr, "exception value: %s\n", str);
	}

	return 0;
}

} // namespace


int test_secure_coding_3()
{
	//return test_secure_coding_3_1();
	//test_secure_coding_3_6(); return 0;
	//return test_secure_coding_3_8();
	//return test_secure_coding_3_9();
	return test_secure_coding_3_10();

}

///////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/105921174

namespace {
void test_aligned_alloc()
{
	const int arr_size = 11;
	// 分配16字节对齐的数据
#ifdef _MSC_VER
	float* array = (float*)_aligned_malloc(16, arr_size * sizeof(float));
#else
	float* array = (float*)aligned_alloc(16, arr_size * sizeof(float));
#endif
	auto addr = std::addressof(array);
	fprintf(stdout, "pointer addr: %p\n", addr);

	fprintf(stdout, "char alignment: %d, float alignment: %d, max_align_t alignment: %d\n",
		alignof(char), alignof(float), alignof(max_align_t));
}

int test_secure_coding_4_1()
{
	test_aligned_alloc();
	return 0;
}

// 读取未初始化的内存
void test_memory_init_error()
{
	// 初始化大的内存块可能会降低性能并且不总是必要的.
	// C标准委员会决定不需要malloc来初始化这个内存,而把这个决定留给程序员
	int n = 5;
	int* y = static_cast<int*>(malloc(n * sizeof(int)));
	int A[] = {1, 2, 3, 4, 5};

	for (int i = 0; i < n; ++i) {
		y[i] += A[i];
	}

	std::for_each(y, y+n, [](int v) { fprintf(stdout, "value: %d\n", v); });
	free(y);
}

// 检查malloc的返回值
int* test_memory_return_value()
{
	// 如果不能分配请求的空间，那么C内存分配函数将返回一个空指针
	int n = 5;
	int* ptr = static_cast<int*>(malloc(sizeof(int) * n));
	if (ptr != nullptr) {
		memset(ptr, 0, sizeof(int) * n);
	} else {
		fprintf(stderr, "fail to malloc\n");
		return nullptr;
	}

	return ptr;
}

// 引用已释放内存
void test_memory_reference_free()
{
	int* x = static_cast<int*>(malloc(sizeof(int)));
	*x = 100;
	free(x);
	// 从已被释放的内存读取是未定义的行为
	fprintf(stderr, "x: %d\n", *x);
	// 写入已经被释放的内存位置，也不大可能导致内存故障，但可能会导致一些严重的问题
	*x = -100;
	fprintf(stderr, "x: %d\n", *x);
}

// 多次释放内存
void test_memory_multi_free()
{
	int* x = static_cast<int*>(malloc(sizeof(int)));
	free(x);
	// 多次释放相同的内存会导致可以利用的漏洞
	free(x);
}

// 零长度分配：不要执行零长度分配
void test_memory_0_byte_malloc()
{
	char* p1 = static_cast<char*>(malloc(0));
	fprintf(stderr, "p1 pointer: %p\n", std::addressof(p1)); // 是不确定的
	free(p1);

	p1 = nullptr;
	char* p2 = static_cast<char*>(realloc(p1, 0));
	fprintf(stderr, "p2 pointer: %p\n", std::addressof(p2)); // 是不确定的
	free(p2);
	
	int nsize = 10;
	char* p3 = static_cast<char*>(malloc(nsize));
	char* p4 = nullptr;
	// 永远不要分配0个字节
	if ((nsize == 0) || (p4 = static_cast<char*>(realloc(p3, nsize))) == nullptr) {
		free(p3);
		p3 = nullptr;
		return;
	}

	p3 = p4;
	free(p3);
}

int test_secure_coding_4_2()
{
	//test_memory_init_error();
	//free(test_memory_return_value());
	//test_memory_reference_free();
	//test_memory_multi_free();
	test_memory_0_byte_malloc();
	return 0;
}

void test_memory_new_init()
{
	// 包括所有的内置类型
	int* i1 = new int(); // 已初始化
	int* i2 = new int; // 未初始化
	fprintf(stdout, "i1: %d, i2: %d\n", *i1, *i2);

	// 就地new没有实际分配内存，所以该内存不应该被释放
	int* i3 = new (i1) int;
	fprintf(stdout, "i3: %d\n", *i3);

	delete i1;
	delete i2;

	// 通常情况下，分配函数无法分配存储时抛出一个异常表示失败
	int* p1 = nullptr;
	try {
		p1 = new int;
	} catch (std::bad_alloc) {
		fprintf(stderr, "fail to new\n");
		return;
	}
	delete p1;

	// 用std::nothrow参数调用new，当分配失败时，分配函数不会抛出一个异常，它将返回一个空指针
	int* p2 = new(std::nothrow) int;
	if (p2 == nullptr) {
		fprintf(stderr, "fail to new\n");
		return;
	}
	delete p2;
}

class intHandle {
public:
	explicit intHandle(int* anInt) : i_(anInt) {} // 获取资源
	~intHandle() { delete i_; } // 释放资源

	intHandle& operator=(const int i)
	{
		*i_ = i;
		return *this;
	}

	int* get() { return i_; } // 访问资源

private:
	intHandle(const intHandle&) = delete;
	intHandle& operator=(const intHandle&) = delete;
	int* i_;
};

// 资源获取初始化(Resource Acquisition Is Initialization, RAII)
void test_memory_arii()
{
	intHandle ih(new int);
	ih = 5;
	fprintf(stdout, "value: %d\n", *ih.get());

	// 使用std::unique_ptr能完成同样的事情，而且更简单
	std::unique_ptr<int> ip(new int);
	*ip = 5;
	fprintf(stdout, "value: %d\n", *ip.get());
}

// 抛出std::bad_array_new_length的三种情况
void test_memory_bad_array_new_length()
{
	try {
		int negative = -1;
		new int[negative]; // 大小为负
	} catch(const std::bad_array_new_length& e) {
		fprintf(stderr, "1: %s\n", e.what());
	}

	try {
		int small = 1;
		new int[small]{1, 2, 3}; // 过多的初始化值设定
	} catch(const std::bad_array_new_length& e) {
		fprintf(stderr, "2: %s\n", e.what());
	}

	try {
		int large = INT_MAX;
		new int[large][1000000]; // 过大
	} catch(const std::bad_alloc& e) {
		fprintf(stderr, "3: %s\n", e.what());
	}
}

int test_secure_coding_4_3()
{
	//test_memory_new_init();
	//test_memory_arii();
	test_memory_bad_array_new_length();
	return 0;
}

// 未能正确检查分配失败
void test_memory_new_wrong_usage()
{
	// new表达式，要么成功，要么抛出一个异常
	// 意味着，if条件永远为真，而else子句永远不会被执行
	int* ip = new int;
	if (ip) { // 条件总是为真
		
	} else {
		// 将永远不执行
	}
	delete ip;

	// new操作符的nothrow形式在失败时返回一个空指针，而不是抛出一个异常
	int* p2 = new(std::nothrow)int;
	if (p2) {
		delete p2;
	} else {
		fprintf(stderr, "fail to new\n");
	}
}

class Widget {};

// 不正确配对的内存管理函数
void test_memory_new_delete_unpaired()
{
	int* ip = new int(12);
	free(ip); // 错误，应使用delete ip

	int* ip2 = static_cast<int*>(malloc(sizeof(int)));
	*ip2 = 12;
	delete ip2; // 错误，应使用free(ip2)

	// new和delete操作符用于分配和释放单个对象
	Widget* w = new Widget();
	delete w;

	// new[]和delete[]操作符用于分配和释放数组
	Widget* w2 = new Widget[10];
	delete [] w2;

	// operator new()分配原始内存，但不调用构造函数
	std::string* sp = static_cast<std::string*>(operator new(sizeof(std::string)));
	//delete sp; // 错误
	operator delete (sp); // 正确
}

int test_secure_coding_4_4()
{
	//test_memory_new_wrong_usage();
	test_memory_new_delete_unpaired();
	return 0;
}

} // namespace

int test_secure_coding_4()
{
	//return test_secure_coding_4_1();
	//return test_secure_coding_4_2();
	//return test_secure_coding_4_3();
	return test_secure_coding_4_4();
}

///////////////////////////////////////////////////////////
int test_secure_coding_5()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_6()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_7()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_8()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_9()
{
	return 0;
}

} // namespace cplusplus_secure_coding_
