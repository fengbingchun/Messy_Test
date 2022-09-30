#define __STDC_WANT_LIB_EXT1__ 1
#include "cplusplus_secure_coding.hpp"
#ifdef _MSC_VER
#include <windows.h>
#else
#include <sys/stat.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <setjmp.h>
#include <limits.h>
#include <fenv.h>
#include <stdarg.h>
#include <signal.h>
#include <cstddef>
#include <cmath>
#include <string>
#include <memory>
#include <iostream>
#include <exception>
#include <algorithm>
#include <climits>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <fstream>

// reference: 《C和C++安全编码(原书第2版)》

namespace cplusplus_secure_coding_ {

///////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/105325508

namespace {

void calculate_array_size(int arr1[], char arr3[])
{
	int arr2[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	fprintf(stdout, "arr2 element count: %d\n", sizeof(arr2) / sizeof(arr2[0])); // 8

	// 此处arr1是一个参数,所以它的类型是指针,在x64中,sizeof(int*)=8,在x86中,sizeof(int*)=4
	// 数组名作为函数参数会被C语言转换为指针,而不是sizeof的"参数",因为sizeof不是函数而是运算符
	// sizeof运算符在应用于声明为数组或函数类型的参数时,它产生调整后的(即指针)类型大小
	fprintf(stdout, "arr1 element count: %d\n", sizeof(arr1) / sizeof(arr1[0])); // 2, error
	fprintf(stdout, "sizeof(int*): %d\n", sizeof(int*)); // 8 // note: x64, not x86

	fprintf(stdout, "arr3 byte count: %d\n", strlen(arr3)); // 10
}

void string_literal()
{
	const char s1[4] = "abc"; // 不推荐,任何随后将数组作为一个空字节结尾的字符串的使用都会导致漏洞,因为s1没有正确地以空字符结尾
	const char s2[] = "abc";  // 推荐,对于一个用字符串字面值初始化的字符串,不指定它的界限,因为编译器会自动为整个字符串字面值分配足够的空间,包括终止的空字符
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
	std::cin >> buf; // 如果用户输入多于11个字符,会导致写越界
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
	strcpy(c, a); // 若a并未以空字符结尾,那么c也未以空字符结尾,而且c可能写得远远超出了数组界限,导致无法正常打印c
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
		// fgets成功,扫描查找换行符
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
	//r3 = strncpy_s(dst3, sizeof(dst3), src1, sizeof(src1)); // crash, r3并没有返回非零值,原因应该是没有开启运行时约束
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

static int GLOBAL_INIT = 1; // 数据段,全局
static int global_uninit; // BSS段,全局
int test_secure_coding_3_1() // 栈,局部
{
	int local_init = 1; // 栈,局部
	int local_uninit; // 栈,局部
	static int local_static_init = 1; // 数据段,局部
	static int local_static_uninit; // BSS段,局部
	// buff_ptr的存储空间是栈,局部；分配的内存是堆,局部
	int* buff_ptr = (int*)malloc(32);
	free(buff_ptr);

	return 0;
}

void good_function(const char* str) {} // 栈
// 一个有漏洞的程序,其BSS段中的函数指针可以被覆写
void test_secure_coding_3_2(int argc, char* argv[]) // 栈
{
	const int BUFFSIZE = 10; // 栈
	static char buff[BUFFSIZE]; // BSS段
	static void(*funPtr)(const char* str); // BSS段
	funPtr = &good_function;
	// 当argv[1]的长度大于BUFFSIZE的时候,就会发生缓冲区溢出,这个缓冲区溢出漏洞
	// 可以被利用来将函数指针值覆写为外壳代码的地址,从而将程序的控制权转移到任意的代码
	// 当执行由funPtr标识的函数时,外壳代码将会取代good_function()得以执行
	strncpy(buff, argv[1], strlen(argv[1])); 
	(void)(*funPtr)(argv[2]);
}

// 一个有漏洞的程序,可以被利用来实现任意内存写,修改对象指针
void test_secure_coding_3_3(void* arg, size_t len)
{
	char buff[100];
	long val = 1;
	long* ptr = &val;
	// 一个无界内存复制,在溢出缓冲区后,攻击者可以覆写ptr和val
	// 当执行*ptr=val时,就会发生任意内存写
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
	// 如果不能分配请求的空间,那么C内存分配函数将返回一个空指针
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
	// 写入已经被释放的内存位置,也不大可能导致内存故障,但可能会导致一些严重的问题
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

	// 就地new没有实际分配内存,所以该内存不应该被释放
	int* i3 = new (i1) int;
	fprintf(stdout, "i3: %d\n", *i3);

	delete i1;
	delete i2;

	// 通常情况下,分配函数无法分配存储时抛出一个异常表示失败
	int* p1 = nullptr;
	try {
		p1 = new int;
	} catch (std::bad_alloc) {
		fprintf(stderr, "fail to new\n");
		return;
	}
	delete p1;

	// 用std::nothrow参数调用new,当分配失败时,分配函数不会抛出一个异常,它将返回一个空指针
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

	// 使用std::unique_ptr能完成同样的事情,而且更简单
	std::unique_ptr<int> ip(new int);
	*ip = 5;
	fprintf(stdout, "value: %d\n", *ip.get());
}

// 抛出std::bad_array_new_length的三种情况
void test_memory_bad_array_new_length()
{
#ifdef _MSC_VER
#undef small
#endif
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
	// new表达式,要么成功,要么抛出一个异常
	// 意味着,if条件永远为真,而else子句永远不会被执行
	int* ip = new int;
	if (ip) { // 条件总是为真
		
	} else {
		// 将永远不执行
	}
	delete ip;

	// new操作符的nothrow形式在失败时返回一个空指针,而不是抛出一个异常
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
	free(ip); // 错误,应使用delete ip

	int* ip2 = static_cast<int*>(malloc(sizeof(int)));
	*ip2 = 12;
	delete ip2; // 错误,应使用free(ip2)

	// new和delete操作符用于分配和释放单个对象
	Widget* w = new Widget();
	delete w;

	// new[]和delete[]操作符用于分配和释放数组
	Widget* w2 = new Widget[10];
	delete [] w2;

	// operator new()分配原始内存,但不调用构造函数
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
// Blog: https://blog.csdn.net/fengbingchun/article/details/106444980
namespace {

// 回绕:涉及无符号操作数的计算永远不会溢出
void test_integer_security_wrap_around()
{
	unsigned int ui = UINT_MAX; fprintf(stdout, "ui value 1: %u\n", ui); // 4294967295
	ui++; fprintf(stdout, "ui value 2: %u\n", ui); // 0
	ui = 0; fprintf(stdout, "ui value 3: %u\n", ui); // 0
	ui--; fprintf(stdout, "ui value 4: %u\n", ui); // 4294967295

	//for (unsigned i = n; --i >= 0; ) // 此循环将永远不会终止

	unsigned int i = 0, j = 0, sum = 0;
	// ... 对i, j, sum进行一些赋值运算操作
	if (sum + i > UINT_MAX) { } // 不会发生,因为sum+i回绕了
	if (i > UINT_MAX - sum) { } // 好很多

	if (sum - j < 0) { } // 不会发生,因为sum-j回绕了
	if (j > sum) { } // 正确
}

// 有符号整数溢出
void test_integer_security_overflow()
{
	int i = INT_MAX; // 2147483647, int最大值
	i++; fprintf(stdout, "i = %d\n", i); // -2147483648, int最小值

	i = INT_MIN; // -2147483648, int最小值
	i--; fprintf(stdout, "i = %d\n", i); // 2147483647, int最大值

	std::cout << "abs(INT_MIN): " << std::abs(INT_MIN) << std::endl; // -2147483648
	// 因为二进制补码表示是不对称的,数值0被表示为”正”数,所以用补码表示的一个给定类型最小负值的相反数不能以那种类型表示
	// 对最小的负值而言,结果是未定义的或错误的
	#define abs(n) ((n) < 0 ? -(n) : (n))
	#undef abs
}

// 字符类型
void test_integer_security_char()
{
{
	// char类型的变量c可能是有符号或无符号的
	// 初始值200(它具有signed char类型)无法在(有符号的)char类型中表示(这是未定义的行为)
	// 许多编译器将用标准的由无符号转换到有符号的模字大小(modulo-word-size)规则把200转换为-56
	char c = 200;
	int i = 1000;
	fprintf(stdout, "i/c = %d\n", i / c); // 在windows/linux上会输出-17, 1000/-56=-17
}

{
	// 声明unsigned char型变量c,使后面的除法操作与char的符号性无关,因此它有一个可预见的结果
	unsigned char c = 200;
	int i = 1000;
	fprintf(stdout, "i/c = %d\n", i / c); // 5
}
}

void test_integer_security_ptrdiff_t()
{
	int i = 5, j = 6;
	typedef int T;
	T *p = &i, *q = &j;
	ptrdiff_t d = p - q;
	fprintf(stdout, "pointer diff: %lld\n", d);
	fprintf(stdout, "sizeof(ptrdiff_t): %d\n", sizeof(ptrdiff_t)); // 8
}

void test_integer_security_intmax_t()
{
	typedef unsigned long long mytypedef_t; // 假设mytypedef_t是个128位的无符号整数,其实它并不是
	fprintf(stdout, "mytypedef_t length: %d\n", sizeof(mytypedef_t));

	mytypedef_t x = 0xffff;
	uintmax_t temp;
	temp = x; // 始终是安全的

	mytypedef_t x2 = 0xffffffffffffffff;
	fprintf(stdout, "x2: %ju\n", (uintmax_t)x2); // 将保证打印正确的x2值,无论它的长度是多少
}

int test_secure_coding_5_2()
{
	//test_integer_security_wrap_around();
	//test_integer_security_overflow();
	//test_integer_security_char();
	test_integer_security_ptrdiff_t();
	//test_integer_security_intmax_t();
	return 0;
}

void test_integer_security_promotion()
{
{
	int sum = 0;
	char c1 = 'a', c2 = 'b';
	// 整数类型提升规则要求把c1和c2都提升到int类型
	// 然后把这两个int类型的数据相加,得到一个int类型的值,并且该结果被保存在整数类型变量sum中
	sum = c1 + c2;
	fprintf(stdout, "sum: %d\n", sum); // 195
}

{
	signed char cresult, c1, c2, c3;
	c1 = 100; c2 = 3; c3 = 4;
	// 在用8位补码表示signed char的平台上,c1与c2相乘的结果可能会因超过这些平台上signed char类型的最大值(+127)
	// 而引起signed char类型的溢出.然而,由于发生了整数类型提升,c1, c2和c3都被转换为int,因此整个表达式的结果
	// 能够被成功地计算出来.该结果随后被截断,并被存储在cresult中.由于结果位于signed char类型的取值范围内,因
	// 此该截断操作并不会导致数据丢失或数据解释错误 
	cresult = c1 * c2 / c3;
	fprintf(stdout, "cresult: %d\n", cresult); // 75
}

{
	unsigned char uc = UCHAR_MAX; // 0xFF
	// 当uc用作求反运算符"~"的操作数时,通过使用零扩展把它扩展为32位,它被提升为signed int类型,因此,在
	// x86-32架构平台中,该操作始终产生一个类型为signed int的负值
	int i = ~uc;
	fprintf(stdout, "i: %0x\n", i); // 0xffffff00
}
}

void test_integer_security_unsigned_conversion()
{
{ // 无符号,损失精度
	unsigned int ui = 300;
	// 当uc被赋予存储在ui中的值时,值300以模2^8取余,或300-256=44
	unsigned char uc = ui;
	fprintf(stdout, "uc: %u\n", uc); // 44
}

{ // 无符号值转换成有符号值
	unsigned long int ul = ULONG_MAX;
	signed char sc;
	sc = ul; // 可能会导致截断错误
	fprintf(stdout, "sc: %d\n", sc); // -1
}

{ // 当从一个无符号类型转换为有符号类型时,应验证范围
	unsigned long int ul = ULONG_MAX;
	signed char sc;
	if (ul <= SCHAR_MAX) {
		sc = (signed char)ul; // 使用强制转换来消除警告
	} else { // 处理错误情况
		fprintf(stderr, "fail\n");
	}
}
}

void test_integer_security_signed_conversion()
{
{ // 有符号,损失精度
	signed long int sl = LONG_MAX;
	signed char sc = (signed char)sl; // 强制转换消除了警告
	fprintf(stdout, "sc: %d\n", sc); // -1
}

{ // 当从一个有符号类型转换到精度较低的有符号类型时,应验证范围
	signed long int sl = LONG_MAX;
	signed char sc;
	if ((sl < SCHAR_MIN) || (sl > SCHAR_MAX)) { // 处理错误情况
		fprintf(stderr, "fail\n");
	} else {
		sc = (signed char)sl; // 使用强制转换来消除警告
		fprintf(stdout, "sc: %d\n", sc);
	}
}

{ // 负值和无符号值的比较固有问题
	unsigned int ui = UINT_MAX;
	signed char c = -1;
	// 由于整数提升,c被转换为unsigned int类型的值0xFFFFFFFF,即4294967295
	if (c == ui) {
	      fprintf(stderr, "why is -1 = 4294967295\n");
	}
}

{ // 从有符号类型转换为无符号类型时,可能发生类型范围错误,包括数据丢失(截断)和损失符号(符号错误)
	signed int si = INT_MIN;
	// 导致损失符号
	unsigned int ui = (unsigned int)si; // 强制转换消除了警告
	fprintf(stderr, "ui: %u\n", ui); // 2147483648
}

{ // 从有符号类型转换为无符号类型时,应验证取值范围
	signed int si = INT_MIN;
	unsigned int ui;
	if (si < 0) { // 处理错误情况
		fprintf(stderr, "fail\n");
	} else {
		ui = (unsigned int)si; // 强制转换消除了警告
		fprintf(stdout, "ui: %u\n", ui);
	}
}
}

int test_secure_coding_5_3()
{
	//test_integer_security_promotion();
	//test_integer_security_unsigned_conversion();
	test_integer_security_signed_conversion();
	return 0;
}

int f_5_4(void) { return 66; }
void test_integer_security_assignment()
{
{
	char c;
	// 函数f_5_4返回的int值可能在存储到char时被截断,然后在比较之前将其转换回int宽度
	// 在"普通"char具有与unsigned char相同的取值范围的实现中,转换的结果不能为负,所以下面比较的操作数
	// 永远无法比较为相等,因此,为了有充分的可移植性,变量c应声明为int类型
	if ((c = f_5_4()) == -1) {}
}

{
	char c = 'a';
	int i = 1;
	long l;
	// i的值被转换为c=i赋值表达式的类型,那就是char类型,然后包含在括号中的表达式的值被转换为括号外的赋值
	// 表达式的类型,即long int型.如果i的值不在char的取值范围内,那么在这一系列的分配后,比较表达式
	// l == i是不会为真的
	l = (c = i);
}

{
	// 用一个有符号整数为一个无符号整数赋值,或者用一个无符号整数为一个宽度相等的有符号整数赋值,
	// 都可能导致所产生的值被误解
	int si = -3;
	// 因为新的类型是无符号的,那么通过反复增加或减去比新的类型可以表示的最大值大1的数,该值可以被转换,
	// 直到该值落在新的类型的取值范围内.如果作为无符号值访问,结果值会被误解为一个大的正值
	unsigned int ui = si;
	fprintf(stdout, "ui = %u\n", ui); // 4294967293
	fprintf(stdout, "ui = %d\n", ui); // -3
	// 在大多数实现中,通过逆向操作可以轻易地恢复原来的值
	si = ui;
	fprintf(stdout, "si = %d\n", si); // -3
}

{
	unsigned char sum, c1, c2;
	c1 = 200; c2 = 90;
	// c1和c2相加产生的值在unsigned char的取值范围之外,把结果赋值给sum时会被截断
	sum = c1 + c2;
	fprintf(stdout, "sum = %u\n", sum); // 34
}
}

void test_integer_security_add()
{
{ // 先验条件测试,补码表示: 用来检测有符号溢出,该解决方案只适用于使用补码表示的架构
	signed int si1, si2, sum;
	si1 = -40; si2 = 30;
	unsigned int usum = (unsigned int)si1 + si2;
	fprintf(stdout, "usm = %x, si1 = %x, si2 = %x, int_min = %x\n", usum, si1, si2, INT_MIN);
	// 异或可以被当作一个按位的"不等"操作,由于只关心符号位置,因此把表达式用INT_MIN进行掩码,
	// 这使得只有符号位被设置
	if ((usum ^ si1) & (usum ^ si2) & INT_MIN) { // 处理错误情况
		fprintf(stderr, "fail\n");
	} else {
		sum = si1 + si2;
		fprintf(stdout, "sum = %d\n", sum);
	}
}

{ // 一般的先验条件测试
	signed int si1, si2, sum;
	si1 = -40; si2 = 30;
	if ((si2 > 0 && si1 > INT_MAX - si2) || (si2 < 0 && si1 < INT_MIN - si2)) { // 处理错误情况
		fprintf(stderr, "fail\n");
	} else {
		sum = si1 + si2;
		fprintf(stdout, "sum = %d\n", sum);	
	}
}

{ // 先验条件测试:保证没有回绕的可能性
	unsigned int ui1, ui2, usum;
	ui1 = 10; ui2 = 20;
	if (UINT_MAX - ui1 < ui2) { // 处理错误情况
		fprintf(stderr, "fail\n");
	} else {
		usum = ui1 + ui2;
		fprintf(stdout, "usum = %u\n", usum);
	}
}

{ // 后验条件测试
	unsigned int ui1, ui2, usum;
	ui1 = 10; ui2 = 20;
	usum = ui1 + ui2;
	if (usum < ui1) { // 处理错误情况
		fprintf(stderr, "fail\n");
	}
}
}

void test_integer_security_substruction()
{
{ // 先验条件测试:两个正数相减或两个负数相减都不会发生溢出
	signed int si1, si2, result;
	si1 = 10; si2 = -20;
	// 如果两个操作数异号,并且结果的符号与第一个操作数不同,则已发生减法溢出
	// 异或用作一个按位的"不等"操作.要测试符号位置,表达式用INT_MIN进行掩码,这使得只有符号位被设置
	// 该解决方案只适用于适用补码表示的架构
	if ((si1 ^ si2) & (((unsigned int)si1 - si2) ^ si1) & INT_MIN) { // 处理错误条件
		fprintf(stderr, "fail\n");
	} else {
		result = si1 - si2;
		fprintf(stdout, "result = %d\n", result);
	}

	// 可移植的先验条件测试
	if ((si2 > 0 && si1 < INT_MIN + si2) || (si2 < 0 && si1 > INT_MAX + si2)) { // 处理错误条件
		fprintf(stderr, "fail\n");
	} else {
		result = si1 - si2;
		fprintf(stdout, "result = %d\n", result);	
	}
}

{ // 无符号操作数的减法操作的先验条件测试,以保证不存在无符号回绕现象
	unsigned int ui1, ui2, udiff;
	ui1 = 10; ui2 = 20;
	if (ui1 < ui2) { // 处理错误条件
		fprintf(stderr, "fail\n");
	} else {
		udiff = ui1 - ui2;
		fprintf(stdout, "udiff = %u\n", udiff);
	}
}

{ // 后验条件测试
	unsigned int ui1, ui2, udiff;
	ui1 = 10; ui2 = 20;
	udiff = ui1 - ui2;
	if (udiff > ui1) { // 处理错误情况
		fprintf(stderr, "fail\n");
	}
}
}

void test_integer_security_multiplication()
{
{ // 在无符号乘法的情况下,如果需要高位来表示两个操作数的积,那么结果以及回绕了
	unsigned int ui1 = 10;
	unsigned int ui2 = 20;
	unsigned int product;

	static_assert(sizeof(unsigned long long) >= 2 * sizeof(unsigned int), 
		"Unable to detect wrapping after multiplication");

	unsigned long long tmp = (unsigned long long)ui1 * (unsigned long long)ui2;
	if (tmp > UINT_MAX) { // 处理无符号回绕
		fprintf(stderr, "fail\n");
	} else {
		product = (unsigned int)tmp;
		fprintf(stdout, "product = %u\n", product);
	}
}

{ // 保证在long long宽度至少是int宽度两倍的系统上,不可能产生符号溢出
	signed int si1 = 20, si2 = 10;
	signed int result;
	static_assert(sizeof(long long) >= 2 * sizeof(int),
		"Unable to detect overflow after multiplication");
	long long tmp = (long long)si1 * (long long)si2;
	if ((tmp > INT_MAX) || (tmp < INT_MIN)) { // 处理有符号溢出
		fprintf(stderr, "fail\n");
	} else {
		result = (int)tmp;
		fprintf(stdout, "result = %d\n", result);
	}
}

{ // 一般的先验调试测试
	unsigned int ui1 = 10, ui2 = 20;
	unsigned int product;

	if (ui1 > UINT_MAX / ui2) { // 处理无符号回绕
		fprintf(stderr, "fail\n");
	} else {
		product = ui1 * ui2;
		fprintf(stdout, "product = %u\n", product);
	}
}

{ // 可以防止有符号溢出,而不需要向上强制类型转换到现有位数的两倍的整数类型
	signed int si1 = 10, si2 = 20;
	signed int product;

	if (si1 > 0) { // si1是正数
		if (si2 > 0) { // si1和si2都是正数
			if (si1 > (INT_MAX / si2)) { // 处理错误情况
				fprintf(stderr, "fail\n");
			}
		} // end if si1和si2都是正数
		else { // si1是正数,si2不是正数
			if (si2 < (INT_MIN / si1)) { // 处理错误情况
				fprintf(stderr, "fail\n");
			}
		} // end if si1是正数,si2不是正数
	} // end fif si1是正数
	else { // si1不是正数
		if (si2 > 0) { // si1不是正数,si2是正数
			if (si1 < (INT_MIN / si2)) { // 处理错误情况
				fprintf(stderr, "fail\n");
			}
		} // end if si1不是正数,si2是正数
		else { // si1和si2都不是正数
			if ((si1 != 0) && (si2 < (INT_MAX / si1))) { // 处理错误情况
				fprintf(stderr, "fail\n");
			}
		} // end if si1和si2都不是正数
	} // end if si1不是正数

	product = si1 * si2;
	fprintf(stdout, "product = %d\n", product);
}
}

void test_integer_security_division_remainder()
{
	// 先验条件:可以通过检查分子是否为整数类型的最小值以及检查分母是否为-1来防止有符号整数除法溢出的发生
	// 只要确保除数不为0,就可以保证不发生除以零错误
	signed long sl1 = 100, sl2 = 5;
	signed long quotient, result;

	// 此先验条件也可测试余数操作数,以保证不可能有一个除以零错误或(内部)溢出错误
	if ((sl2 == 0) || ((sl1 == LONG_MIN) && (sl2 == -1))) { // 处理错误情况
		fprintf(stderr, "fail\n");
	} else {
		quotient = sl1 / sl2;
		result = sl1 % sl2;
		fprintf(stdout, "quotient = %ld, result = %ld\n", quotient, result);
	}
}

void test_integer_security_shift()
{
{ // 消除了无符号整数左移位操作造成的未定义行为的可能性
	unsigned int ui1 = 1, ui2 = 31;
	unsigned int uresult;

	if (ui2 >= sizeof(unsigned int) * CHAR_BIT) { // 处理错误情况
		fprintf(stderr, "fail\n");
	} else {
		uresult = ui1 << ui2;
		fprintf(stdout, "uresult = %u\n", uresult);
	}
}

{
	int rc = 0;
	//int stringify = 0x80000000; // windows/liunx will crash in sprintf function
	unsigned int stringify = 0x80000000;
	char buf[sizeof("256")] = {0};
	rc = sprintf(buf, "%u", stringify >> 24);
	if (rc == -1 || rc >= sizeof(buf)) { // 处理错误
		fprintf(stderr, "fail\n");
	} else {
		fprintf(stdout, "value: %s\n", buf); // 128
	}
}
}

int test_secure_coding_5_4()
{
	//test_integer_security_assignment();
	//test_integer_security_add();
	//test_integer_security_substruction();
	//test_integer_security_multiplication();
	//test_integer_security_division_remainder();
	test_integer_security_shift();
	return 0;
}

void test_integer_security_wrap_around2()
{
{ // 展示了一个无符号整数回绕导致的实际漏洞的例子
	size_t len = 1;
	char* src = "comment";

	size_t size;
	size = len - 2;
	fprintf(stderr, "size = %u, %x, %x, %d\n", size, size, size+1, size+1); // 4294967295, ffffffff, 0, 0
	char* comment = (char*)malloc(size + 1);
	//memcpy(comment, src, size); // crash
	free(comment);
}

{
	int element_t;
	int count = 10;
	// 库函数calloc接受两个参数：存储元素类型所需要的空间和元素的个数.为了求出所需内存的大小,使用元素个数
	// 乘以该元素类型所需的单位空间来计算.如果计算所得结果无法用类型为size_t的无符号整数表示,那么,尽管分
	// 配程序看上去能够成功地执行,但实际上它只会分配非常小的内存空间.结果,应用程序对分配的缓冲区的写操作
	// 可能会越界,从而导致基于堆的缓冲区溢出
	char* p = (char*)calloc(sizeof(element_t), count);
	free(p);
}

{
	int off = 1, len = 2;
	int type_name;
	// 这里的off和len都声明为signed int.因为根据C标准的定义,sizeof运算符返回的是一个无符号整数类型(size_t),
	// 整数转换规则要求在那些signed int的宽度等于size_t的宽度的实现上,len - sizeof(type_name)被计算为无符号
	// 的值,如果len比sizeof运算符返回的值小,那么减法操作会回绕并产生一个巨大的正值
	std::cout<<"len - sizeof(type_name): "<<len - sizeof(type_name)<<std::endl; // 18446744073709551614
	if (off > len - sizeof(type_name)) return;
	// 要消除以上问题,可以把整数范围检查编写为下列替代形式
	// 程序员仍然必须保证这里的加法操作不会导致回绕,这是通过保证off的值在一个已定义的范围内实现的.为了消除
	// 潜在的转换错误,在本例中也应当把off和len都声明为size_t类型
	if ((off + sizeof(type_name)) > len) return;
}
}

void test_integer_security_conversion_truncation()
{
{ // 由转换错误导致的安全漏洞
	int size = 5;
	int MAX_ARRAY_SIZE = 10;
	// 如果size为负数,此检查将通过,而malloc()函数将被传入一个为负的大小.因为malloc()需要size_t类型的参数,
	// 所以size会被转换成一个巨大的无符号数.当有符号整数类型被转换为一个无符号的整数类型时,会重复加上或减去
	// 新类型的宽度(2^N),以使结果落在可表示的范围之内.因此,这种转换可能会导致大于MAX_ARRAY_SIZE的值.这种
	// 错误可以通过把size声明为size_t而不是int来消除
	if (size < MAX_ARRAY_SIZE) { // 初始化数组
		char* array = (char*)malloc(size);
		free(array);
	} else { // 处理错误
		fprintf(stderr, "fail\n");
	}
}

{ // 由整数截断错误导致的缓冲区溢出漏洞
	char* argv[3] = {"", "abc", "123"};
	unsigned short int total;
	// 攻击者可能会提供两个总长度无法用unsigned short整数total表示的字符做参数,这样,总长度值将会用比结果
	// 类型所能表示的最大值大1的数取模截断,函数strlen返回一个无符号整数类型size_t的结果,对于大多数实现而言,
	// size_t的宽度大于unsigned short的宽度,必然要进行降级操作,strcpy和strcat的执行将导致缓冲区溢出
	total = strlen(argv[1]) + strlen(argv[2]) + 1;
	char* buff = (char*)malloc(total);
	strcpy(buff, argv[1]);
	strcat(buff, argv[2]);
	fprintf(stdout, "buff: %s\n", buff);
	free(buff);
}
}

void test_integer_security_integer_logic()
{
	int* table = nullptr;
	int pos = 50, value = 10;
	if (!table) {
		table = (int*)malloc(sizeof(int) * 100);
	}
	// 由于对插入位置pos缺乏必要的范围检查,因此将会导致一个漏洞.因为pos开始时被声明为有符号整数,即传递
	// 到函数中的值既可正又可负
	if (pos > 99) return;
	// 如果pos是一个负值,那么value将会被写入实际缓冲区起始地址pos*sizeof(int)字节之前的位置
	// 消除安全缺陷：将形式参数pos声明为无符号整数类型,或者把同时检查上届和下界作为范围检查的一部分
	table[pos] = value; // 等价于: *(int*)((char*)table+(pos*sizeof(int))) = value;
	free(table);
}

int test_secure_coding_5_5()
{
	//test_integer_security_wrap_around2();
	//test_integer_security_conversion_truncation();
	test_integer_security_integer_logic();
	return 0;
}

void test_integer_security_type_selection()
{
	char* argv = "";
	// 次优的:首先,大小不会是负值,因此,没有必要使用一个有符号整数类型;其次,short整数类型对于可能的对象
	// 大小可能不具有足够的范围
	short total1 = strlen(argv) + 1;
	// 无符号size_t类型,是C标准委员会为了表示对象大小而引入的,此类型的变量都保证有足够的精度来表示一个对象的大小
	size_t total2 = strlen(argv) + 1;
	// C11附录K引入一个新类型rsize_t,它被定义为size_t,但明确地用于保存单个对象的大小
#ifdef _MSC_VER
	rsize_t total3 = strlen(argv) + 1;
#endif
}

void test_integer_security_conditions_test()
{
{ // 两个无符号整数加法是否回绕的先验条件测试
	unsigned int ui1, ui2, usum;
	ui1 = 10; ui2 = 20;
	if (UINT_MAX - ui1 < ui2) { // 处理错误情况
		fprintf(stderr, "fail\n");
	} else {
		usum = ui1 + ui2;
	}
}

{ // 确保有符号的乘法运算不会导致溢出的严格的符合性测试
	signed int si1, si2, result;
	si1 = 10; si2 = -20;
	if (si1 > 0) {
		if (si2 > 0) {
			if (si1 > (INT_MAX / si2)) { // 处理错误情况
				fprintf(stderr, "fail\n");
			}
		} else {
			if (si2 < (INT_MIN / si1)) { // 处理错误情况
				fprintf(stderr, "fail\n");
			}
		}
	} else {
		if (si2 > 0) {
			if (si1 < (INT_MAX / si2)) { // 处理错误情况
				fprintf(stderr, "fail\n");
			}
		} else {
			if ((si1 != 0) && (si2 < (INT_MAX / si1))) { // 处理错误情况
				fprintf(stderr, "fail\n");
			}
		}
	}
	result = si1 * si2;
}

{ // 后验条件测试可用于检测无符号整数回绕,因为这些操作被定义为取模操作
	unsigned int ui1, ui2, usum;
	ui1 = 10; ui2 = 20;
	usum = ui1 + ui2;
	// 用这种方式检测范围错误代价可能相对较高
	if (usum < ui1) { // 处理错误情况
		fprintf(stderr, "fail\n");
	}
}
}

int test_secure_coding_5_6()
{
	//test_integer_security_type_selection();
	test_integer_security_conditions_test();
	return 0;
}

} // namespace

int test_secure_coding_5()
{
	return test_secure_coding_5_2();
	//return test_secure_coding_5_3();
	//return test_secure_coding_5_4();
	//return test_secure_coding_5_5();
	//return test_secure_coding_5_6();
}

///////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/106728792

namespace {

int average(int first, ...)
{
	va_list marker;
	// 在使用变量marker之前,首先必须调用va_start()对参数列表进行初始化
	// 定参first允许vs_start()决定第一个变参的位置
	va_start(marker, first);

	int count = 0, sum = 0, i = first;
	while (i != -1) {
		sum += i;
		count++;
		// va_arg()需要一个已初始化的va_list和下一个参数的类型.
		// 这个宏可以根据类型的大小返回下一个参数,并且相应地递增参数指针
		i = va_arg(marker, int);
	}

	// 在函数返回之前,调用va_end()来执行任何必要的清理工作
	// 若在返回前未调用va_end()宏,则行为是未定义的
	va_end(marker);
	return (sum ? (sum / count) : 0);
}

void test_format_output_variable_parameter_function()
{
	int ret = average(3, 5, 8, -1);
	fprintf(stdout, "average: %d\n", ret);
}

int test_secure_coding_6_1()
{
	test_format_output_variable_parameter_function();
	return 0;
}

void test_format_output_buffer_overflow()
{
{
	char* user = "abcd"; // 用户提供的字符串(可能是恶意的数据)
	char buffer[512];
	// 用户提供的字符串写入一个固定长度的缓冲区
	// 任何长度大于495字节的字符串都会导致越界写(512字节-16个字符字节-1个空字节)
	sprintf(buffer, "Wrong command: %s\n", user);
	fprintf(stdout, "buffer: %s\n", buffer);
}

{
	char* user = "%497d\x3c\xd3\xff\xbf<nops><shellcode>";
	fprintf(stdout, "user: %s\n", user);
	char outbuf[512], buffer[512];

	sprintf(buffer, "ERR Wrong command: %.400s", user);
	fprintf(stdout, "buffer: %s\n", buffer);
	// 格式规范%497d指示函数sprintf()从栈中读出一个假的参数并向缓冲区中写入497个字符,包括格式字符串中的普通字符
	// 在内,现在写入的字符总数已经超过了outbuf的长度4个字节
	// 用户输入可被操纵用于覆写返回地址,也就是拿恶意格式字符串参数中提供的利用代码的地址(0xbfffd33c)去覆写该
	// 地址.在当前函数退出时,控制权将以与栈溢出攻击相同的方式转移给漏洞利用代码
	sprintf(outbuf, buffer);
	fprintf(stdout, "outbuf: %s\n", outbuf);
}
}

void test_format_output_overwrite_memory()
{
{ // 向各种类型和大小的整数变量写入输出的字符数
	char c;
	short s;
	int i;
	long l;
	long long ll;

	// 最初转换指示符%n是用来帮助排列格式化输出字符串的. 它将字符数目成功地输出到以参数的形式
	// 提供的整数地址中
	printf("hello %hhn.", &c);
	printf("hello %hn.", &s);
	printf("hello %n.", &i);
	printf("hello %ln.", &l);
	printf("hello %lln.", &ll);
	fprintf(stdout, "c: %d, s: %d, i: %d, l: %ld, ll: %lld\n", c, s, i, l, ll); // 6
}

{
	// 格式化输出函数写入的字符个数是由格式字符串决定的.如果攻击者能够控制格式字符串,那么他就能通过使用
	// 具有具体的宽度或精度的转换规范来控制写入的字符个数
	// 每一个格式字符串都耗用两个参数,第一个参数是转换指示符%u所使用的整数值,输出的字符个数(一个整数值)
	// 则被写入由第二个参数指定的地址中
	int i;
	printf("%10u%n", 1, &i); fprintf(stdout, "i: %d\n", i); // 10
	printf("%100u%n", 1, &i); fprintf(stdout, "i: %d\n", i); // 100
}

{
	// 在对格式化输出函数的单次调用中,还可以执行多次写
	int i, j, m, n;
	// 第一个%16u%n字符序列向指定地址中写入的值是16,但第二个%16u%n则写32字节,因为计数器没有被重置
	printf("%16u%n%16u%n%32u%n%64u%n", 1, &i, 1, &j, 1, &m, 1, &n);
	fprintf(stdout, "i: %d, j: %d, m: %d, n: %d\n", i, j, m, n); // 16, 32, 64, 128
}
}

int test_secure_coding_6_3()
{
	//test_format_output_buffer_overflow();
	test_format_output_overwrite_memory();
	return 0;
}

void test_format_output_direct_parameter_access()
{
	// 在包含%n$形式的转换规范的格式字符串中,参数列表中的数字式参数可视需要被从格式字符串中引用多次, 其中n是一个
	// 1～{NL_ARGMAX}范围内的十进制整数,它指定了参数的位置
	// 展示了%n$形式的规范转换是如果被用于格式字符串漏洞利用的
	int i, j, k;
	// 第一个转换规范%4$5u获得第四个参数(即常量5),并将输出格式为无符号的十进制整数,宽度为5.第二个转换规范%3$n,
	// 将当前输出计数器的值(5)写到第三个参数(&i)所指定的地址
	printf("%4$5u%3$n%5$5u%2$n%6$5u%1$n\n", &k, &j, &i, 5, 6, 7);
	fprintf(stdout, "i = %d, j = %d, k = %d\n", i, j, k); // i=5, j=10, k=15
}

int test_secure_coding_6_4()
{
	test_format_output_direct_parameter_access();
	return 0;
}

void test_format_output_dynamic_format_string()
{
	int x = 2, y = 3;
	static char format[256] = "%d * %d = ";

	strcat(format, "%d\n");
	printf(format, x, y, x * y); // 2 * 3 = 6
}

void test_format_output_limit_bytes_number()
{
	char buffer[512];
	char* user = "abc";
	sprintf(buffer, "Wrong command: %s\n", user); // 不推荐
	// 精度域指定了针对%s转换所要写入的最大字节数
	sprintf(buffer, "Wrong command: %.495s\n", user); // 推荐
}

int test_secure_coding_6_5()
{
	//test_format_output_dynamic_format_string();
	test_format_output_limit_bytes_number();
	return 0;
}

} // namespace

int test_secure_coding_6()
{
	//return test_secure_coding_6_1();
	//return test_secure_coding_6_3();
	//return test_secure_coding_6_4();
	return test_secure_coding_6_5();
}

///////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/106962487
namespace {

char* err_msg;
#define MAX_MSG_SIZE 24

void handler(int signum)
{
	strcpy(err_msg, "SIGINT encountered.");
}

int test_secure_coding_7_1()
{
	// 即使是单线程程序也可能有并发问题
	// 虽然此程序只使用了一个线程,但它采用了两个控制流:一个使用test_secure_coding_7_1函数,另一个使用handler函数
	// 如果在调用malloc()的过程中调用信号处理程序,该程序可能奔溃,如在程序执行5秒内,按Ctrl+C键
	// 在信号处理函数中只调用异步安全的函数
	signal(SIGINT, handler);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	err_msg = (char*)malloc(MAX_MSG_SIZE);
	if (err_msg == nullptr) { // 处理错误条件
		fprintf(stderr, "fail to malloc\n");
		return -1;
	}

	strcpy(err_msg, "No errors yet.");
	// 主代码循环
	fprintf(stdout, "err_msg: %s\n", err_msg);
	return 0;
}

volatile sig_atomic_t interrupted; // 应声明为volatile

void sigint_handler(int signum)
{
	interrupted = 1; // 赋值可能是在test_secure_coding_7_4不可见的
	fprintf(stdout, "interrupted'value is changed\n");
}

int test_secure_coding_7_4()
{
	signal(SIGINT, sigint_handler);

	// 执行后可同时按下ctrl+c键停止
	while (!interrupted) { // interrupted若不声明为volatile的,循环可能永远不会终止
		// do something
	}

	return 0;
}

std::mutex shared_lock;
int shared_data = 0;
void thread_function(int id)
{
	// 当对已经锁定的互斥量执行lock操作时,该函数会被阻塞直到当前持有该锁的线程释放它
	shared_lock.lock();
	shared_data = id; // shared_data的竞争窗口开始
	fprintf(stdout, "thread: %d, set shared value to: %d\n", id, shared_data);
	std::this_thread::sleep_for(std::chrono::milliseconds(id) * 100);
	fprintf(stdout, "thread: %d, has shared value to: %d\n", id, shared_data); // shared_data的竞争窗口结束	
	shared_lock.unlock();
}

void test_concurrency_mutex()
{
	const size_t thread_size = 10;
	std::thread threads[thread_size];

	for (size_t i = 0; i < thread_size; ++i)
	      threads[i] = std::thread(thread_function, i);

	for (size_t i = 0; i < thread_size; ++i)
	      threads[i].join();

	// test_concurrency_mutex()继续之前,等待直到线程完成
	fprintf(stdout, "Done\n");
}

std::mutex shared_lock2;
int shared_data2 = 0;
void thread_function2(int id)
{
	std::lock_guard<std::mutex> lg(shared_lock2);
	shared_data2 = id; // shared_data2的竞争窗口开始
	fprintf(stdout, "thread: %d, set shared value to: %d\n", id, shared_data2);
	std::this_thread::sleep_for(std::chrono::milliseconds(id) * 100);
	fprintf(stdout, "thread: %d, has shared value to: %d\n", id, shared_data2); // shared_data2的竞争窗口结束	
	// lg被销毁,且互斥量在这里被隐式地解锁
}

void test_concurrency_mutex_guard()
{
	const size_t thread_size = 10;
	std::thread threads[thread_size];

	for (size_t i = 0; i < thread_size; ++i)
	      threads[i] = std::thread(thread_function2, i);

	for (size_t i = 0; i < thread_size; ++i)
	      threads[i].join();

	// test_concurrency_mutex_guard()继续之前,等待直到线程完成
	fprintf(stdout, "Done\n");
}

volatile std::atomic_flag shared_lock3;
int shared_data3 = 0;
void thread_function3(int id)
{
	// 只有当标志在之前未设置时,atomic_flag对象的test_and_set方法才会设置标志.当标志设置成功时,test_and_set
	// 方法返回false,当标志已经设置时,它返回true.只有当整数锁以前是0时,这才与设置整数锁为1效果相同.但是,
	// 因为test_and_set方法是原子的,它缺乏这样的竞争窗口,即该窗口中的其它地方可以篡改标志.因此共享锁可以防止
	// 多个线程进入临界区,所以代码是线程安全的
	while (shared_lock3.test_and_set()) std::this_thread::sleep_for(std::chrono::seconds(1));
	shared_data3 = id; // shared_data3的竞争窗口开始
	fprintf(stdout, "thread: %d, set shared value to: %d\n", id, shared_data3);
	std::this_thread::sleep_for(std::chrono::milliseconds(id) * 100);
	fprintf(stdout, "thread: %d, has shared value to: %d\n", id, shared_data3); // shared_data3的竞争窗口结束	
	shared_lock3.clear();
}

void test_concurrency_atomic()
{
	const size_t thread_size = 10;
	std::thread threads[thread_size];

	for (size_t i = 0; i < thread_size; ++i)
	      threads[i] = std::thread(thread_function3, i);

	for (size_t i = 0; i < thread_size; ++i)
	      threads[i].join();

	// test_concurrency_atomic()继续之前,等待直到线程完成
	fprintf(stdout, "Done\n");
}

std::atomic<int> shared_lock4;
int shared_data4 = 0;
void thread_function4(int id)
{
	// 锁定对象是一个可赋值为数值的原子整数.atomic_compare_exchange_weak函数安全地将锁设置为1,此函数允许意外失败.
	// 也就是说,即使当原子整数的预期值为0,它也可能没有设置为1. 出于这个原因,必须始终在一个循环内调用此函数,
	// 以便它在遇到意外失败时可以重试
	int zero = 0;
	while (!std::atomic_compare_exchange_weak(&shared_lock4, &zero, 1))
	      std::this_thread::sleep_for(std::chrono::seconds(1));
	shared_data4 = id; // shared_data4的竞争窗口开始
	fprintf(stdout, "thread: %d, set shared value to: %d\n", id, shared_data4);
	std::this_thread::sleep_for(std::chrono::milliseconds(id) * 100);
	fprintf(stdout, "thread: %d, has shared value to: %d\n", id, shared_data4); // shared_data4的竞争窗口结束	
	shared_lock4 = 0;
}

void test_concurrency_atomic2()
{
	const size_t thread_size = 10;
	std::thread threads[thread_size];

	for (size_t i = 0; i < thread_size; ++i)
	      threads[i] = std::thread(thread_function4, i);

	for (size_t i = 0; i < thread_size; ++i)
	      threads[i].join();

	// test_concurrency_atomic2()继续之前,等待直到线程完成
	fprintf(stdout, "Done\n");
}

int test_secure_coding_7_5()
{
	//test_concurrency_mutex();
	//test_concurrency_mutex_guard();
	//test_concurrency_atomic();
	test_concurrency_atomic2();
	return 0;
}

int shared_data5 = 0;
std::mutex* locks5 = nullptr;
int thread_size5;
void thread_function5(int id)
{
	if (0) { // 产生死锁
		// 此代码将产生一个固定数量的线程,每个线程都修改一个值,然后读取它.虽然通常一个锁就足够了,但是每个
		// 线程(thread_size5)都用一个锁守卫共享数据值.每个线程都必须获得两个锁,然后才能再访问该值.如果
		// 一个线程首先获得锁0,第二个线程获得锁1,那么程序将会出现死锁
		if (id % 2)
			for (int i = 0; i < thread_size5; ++i)
				locks5[i].lock();
		else
			for (int i = thread_size5; i >= 0; --i)
				locks5[i].lock();

		shared_data5 = id;
		fprintf(stdout, "thread: %d, set shared value to: %d\n", id, shared_data5);

		if (id % 2)
			for (int i = thread_size5; i >= 0; --i)
				locks5[i].unlock();
		else
			for (int i = 0; i < thread_size5; ++i)
				locks5[i].unlock();
	}
	else { // 不会产生死锁
		// 每个线程都以同一顺序获取锁,可以消除潜在的死锁.下面的程序无论创建多少线程都不会出现死锁
		for (int i = 0; i < thread_size5; ++i)
			locks5[i].lock();

		shared_data5 = id;
		fprintf(stdout, "thread: %d, set shared value to: %d\n", id, shared_data5);

		for (int i = 0; i < thread_size5; ++i)
			locks5[i].unlock();
	}
}

void test_concurrency_deadlock()
{
	thread_size5 = 5;
	std::thread* threads = new std::thread[thread_size5];
	locks5 = new std::mutex[thread_size5];

	for (size_t i = 0; i < thread_size5; ++i)
		threads[i] = std::thread(thread_function5, i);

	for (size_t i = 0; i < thread_size5; ++i)
		threads[i].join();

	// test_concurrency_deadlock()继续之前,等待直到线程完成
	delete[] locks5;
	delete[] threads;
	fprintf(stdout, "Done\n");
}

std::mutex shared_lock6;
int shared_data6 = 0;
void thread_function6(int id)
{
	// 每个线程都把一个共享变量设置为它的线程编号,然后打印出共享变量的值.为了防止数据竞争,每个线程都
	// 锁定一个互斥量,以使变量被正确地设置
	if (0) { // 过早地释放锁
		// 当共享变量的每一个写操作都由互斥量所保护时,随后的读取是不受保护的
		shared_lock6.lock();
		shared_data6 = id;
		fprintf(stdout, "thread: %d, set shared value to: %d\n", id, shared_data6);
		shared_lock6.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(id) * 100);
		fprintf(stdout, "thread: %d, has shared value to: %d\n", id, shared_data6);
	}
	else {
		// 读取和写入共享数据都必须受到保护,以确保每一个线程读取到它写入的相同的值.将临界区扩展为包括读取值,此代码就呈现为线程安全的
		// 需要注意的是,线程的顺序仍然可以有所不同,但每个线程都正确地打印出线程编号
		shared_lock6.lock();
		shared_data6 = id;
		fprintf(stdout, "thread: %d, set shared value to: %d\n", id, shared_data6);
		std::this_thread::sleep_for(std::chrono::milliseconds(id) * 100);
		fprintf(stdout, "thread: %d, has shared value to: %d\n", id, shared_data6);
		shared_lock6.unlock();
	}
}

void test_concurrency_prematurely_release_lock()
{
	const size_t thread_size = 10;
	std::thread threads[thread_size];

	for (size_t i = 0; i < thread_size; ++i)
		threads[i] = std::thread(thread_function6, i);

	for (size_t i = 0; i < thread_size; ++i)
		threads[i].join();

	// test_concurrency_prematurely_release_lock()继续之前,等待直到线程完成
	fprintf(stdout, "Done\n");
}

int test_secure_coding_7_6()
{
	//test_concurrency_deadlock();
	test_concurrency_prematurely_release_lock();
	return 0;
}

} // namespace

int test_secure_coding_7()
{
	//return test_secure_coding_7_1();
	//return test_secure_coding_7_4();
	//return test_secure_coding_7_5();
	return test_secure_coding_7_6();
}

///////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/107138261
namespace {

int test_secure_coding_8_2()
{
	// 从一个文件list.txt中读取字符数据，并将其写入到标准输出
#ifdef  _MSC_VER
	const char* name = "../../../testdata/list.txt";
#else
	const char* name = "testdata/list.txt";
#endif

	std::ifstream infile;
	infile.open(name, std::ifstream::in);
	if (!infile.is_open()) {
		std::cerr << "fail to open file: " << name << std::endl; //fprintf(stderr, "fail to open file: %s\n", name);
		return -1;
	}

	char c;
	while (infile >> c)
		std::cout << c; //fprintf(stdout, "%c", c);
	std::cout << std::endl; //fprintf(stdout, "\n");

	infile.close();
	return 0;
}

int test_file_io_getfiletype()
{
#ifdef _MSC_VER
	const char* file_name = "../../../README.md";
	HANDLE handle = CreateFile(file_name, 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);
	if (handle == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "fail to CreateFile: %s\n", file_name);
		return -1;
	}

	if (GetFileType(handle) != FILE_TYPE_DISK) {
		fprintf(stderr, "it's not a disk file: %s\n", file_name);
	}

	CloseHandle(handle);
#endif
	return 0;
}

int test_file_io_stat()
{
#ifdef _MSC_VER
	const char* file_name = "../../../testdata/list.txt";
#else
	const char* file_name = "testdata/list.txt";
#endif
	struct stat st;
	if (stat(file_name, &st) == -1) {
		fprintf(stderr, "fail to stat:\n");
		return -1;
	}

	return 0;
}


int test_secure_coding_8_4()
{
	//return test_file_io_getfiletype();
	return test_file_io_stat();
}

} // namespace

int test_secure_coding_8()
{
	return test_secure_coding_8_2();
	//return test_secure_coding_8_4();
}

///////////////////////////////////////////////////////////
int test_secure_coding_9()
{
	return 0;
}

} // namespace cplusplus_secure_coding_
