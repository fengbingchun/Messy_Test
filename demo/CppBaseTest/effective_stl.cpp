#include "effective_stl.hpp"
#include <cctype>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>
#include <iterator>
#include <memory>
#include <set>
#include <map>
#include <deque>
#include <functional>
#include <iostream>
#include <utility>
#include <string.h>
#include <numeric>

// Blog: https://blog.csdn.net/fengbingchun/article/details/103223914

// reference: 《Effective STL》

namespace effective_stl_ {

/////////////////////////////////////////////////
int test_item_1()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_2()
{
	// 对容器类型和其迭代器类型使用类型定义(typedef)
	typedef std::vector<int> WidgetContainer;
	typedef WidgetContainer::iterator WCIterator;
	WidgetContainer cw;
	int bestWidget;

	WCIterator i = std::find(cw.begin(), cw.end(), bestWidget);

	return 0;
}

/////////////////////////////////////////////////
class Widget {};
class SpecialWidget : public Widget {};

int test_item_3()
{
	std::vector<Widget> vw;
	SpecialWidget sw;
	vw.push_back(sw); // sw作为基类对象被拷贝进vw中，它的派生类特有部分在拷贝时被丢掉了

	return 0;
}

/////////////////////////////////////////////////
int test_item_4()
{
	return 0;
}

/////////////////////////////////////////////////
class Widget5 {};

int test_item_5()
{
	std::vector<Widget5> v1, v2;
	v1.assign(v2.begin() + v2.size() / 2, v2.end()); // 推荐

	v1.clear();
	for (std::vector<Widget5>::const_iterator ci = v2.begin() + v2.size() / 2; ci != v2.end(); ++ci) // 不推荐
		v1.push_back(*ci);

	v1.clear();
	std::copy(v2.begin() + v2.size() / 2, v2.end(), std::back_inserter(v1)); // 效率不如assign

	v1.clear();
	v1.insert(v1.end(), v2.begin() + v2.size() / 2, v2.end()); // 对copy的调用可以被替换为利用区间的insert版本

	const int numValues = 100;
	int data[numValues];

	std::vector<int> v;
	v.insert(v.begin(), data, data + numValues); // 推荐，使用区间成员函数insert

	std::vector<int>::iterator insertLoc(v.begin());
	for (int i = 0; i < numValues; ++i) {
		insertLoc = v.insert(insertLoc, data[i]); // 不推荐，使用单元素成员函数
		++insertLoc;
	}

	return 0;
}

/////////////////////////////////////////////////
// 注意：围绕参数名的括号(比如对f2中d)与独立的括号的区别：围绕参数名的括号被忽略，而独立的括号则表明参数
// 列表的存在：它们说明存在一个函数指针参数
int f1(double d); // 声明了一个带double参数并返回int的函数
int f2(double(d)); // 同上，d两边的括号被忽略,可以给参数名加上圆括号
int f3(double); // 同上，参数名被忽略

int g1(double(*pf)()); // 参数是一个指向不带任何参数的函数的指针，该函数返回double值；g1以指向函数的指针为参数
int g2(double pf()); // 同上，pf为隐式指针
int g3(double()); // 同上，省去参数名

int test_item_6()
{
	// 把一个存有整数(int)的文件ints.dat拷贝到一个list中
	std::ifstream dataFile("ints.dat");
	std::list<int> data1(std::istream_iterator<int>(dataFile), std::istream_iterator<int>()); // 小心，结果不会是你所想象的那样

	std::list<int> data2((std::istream_iterator<int>(dataFile)), std::istream_iterator<int>()); // 正确，注意list构造函数的第一个参数两边的括号

	std::istream_iterator<int> dataBegin(dataFile);
	std::istream_iterator<int> dataEnd;
	std::list<int> data3(dataBegin, dataEnd); // 正确

	return 0;
}

/////////////////////////////////////////////////
class Widget7 {};

struct DeleteObject {
	template<typename T>
	void operator()(const T* ptr) const
	{
		delete ptr;
	}
};

int test_item_7()
{
	const int num = 5;

	std::vector<Widget7*> vwp1, vwp2;
	for (int i = 0; i < num; ++i) {
		vwp1.push_back(new Widget7); // 如果在后面自己不delete，使用vwp在这里发生了Widget7的泄露
		vwp2.push_back(new Widget7);
	}

	for (std::vector<Widget7*>::iterator i = vwp1.begin(); i != vwp1.end(); ++i) {
		delete *i; // 能行，但不是异常安全的
	}

	for_each(vwp2.begin(), vwp2.end(), DeleteObject()); // 正确，类型安全，但仍不是异常安全的

	typedef std::shared_ptr<Widget7> SPW; // SPW"指向Widget7的shared_ptr"
	std::vector<SPW> vwp3;
	for (int i = 0; i < num; ++i) {
		vwp3.push_back(SPW(new Widget7)); // 从Widget7创建SPW,然后对它进行一次push_back使用vwp3,这里不会有Widget7泄露，即使有异常被抛出
	}

	return 0;
}

/////////////////////////////////////////////////
int test_item_8()
{
	return 0;
}

/////////////////////////////////////////////////
bool badValue(int) { return true; } // 返回x是否为"坏值"

int test_item_9()
{
	// 删除c中所有值为1963的元素
	std::vector<int> c1;
	c1.erase(std::remove(c1.begin(), c1.end(), 1963), c1.end()); // 当c1是vector, string或deque时，erase-remove习惯用法是删除特定值的元素的最好办法

	std::list<int> c2;
	c2.remove(1963); // 当c2是list时，remove成员函数是删除特定值的元素的最好办法

	std::set<int> c3;
	c3.erase(1963); // 当c3是标准关联容器时，erase成员函数是删除特定值元素的最好办法

	// 删除判别式(predicate)返回true的每一个对象
	c1.erase(std::remove_if(c1.begin(), c1.end(), badValue), c1.end()); // 当c1是vector, string或deque时，这是删除使badValue返回true的对象的最好办法

	c2.remove_if(badValue); // 当c2是list时，这是删除使badValue返回true的对象的最好办法

	for (std::set<int>::iterator i = c3.begin(); i != c3.end();) {
		if (badValue(*i)) c3.erase(i++); // 对坏值，把当前的i传给erase，递增i是副作用
		else ++i;                        // 对好值，则简单的递增i
	}

	// 每次元素被删除时，都向一个日志(log)文件中写一条信息
	std::ofstream logFile;
	for (std::set<int>::iterator i = c3.begin(); i != c3.end();) {
		if (badValue(*i)) {
			logFile << "Erasing " << *i << '\n'; // 写日志文件
			c3.erase(i++); // 对坏值，把当前的i传给erase，递增i是副作用
		}
		else ++i;              // 对好值，则简单第递增i
	}

	for (std::vector<int>::iterator i = c1.begin(); i != c1.end();) {
		if (badValue(*i)) {
			logFile << "Erasing " << *i << '\n';
			i = c1.erase(i); // 把erase的返回值赋给i，使i的值保持有效
		}
		else ++i;
	}

	return 0;
}

/////////////////////////////////////////////////
int test_item_10()
{
	return 0;
}

/////////////////////////////////////////////////
void* mallocShared(size_t bytesNeeded)
{
	return malloc(bytesNeeded);
}

void freeShared(void* ptr)
{
	free(ptr);
}

template<typename T>
class SharedMemoryAllocator { // 把STL容器的内容放到共享内存(即由mallocShared生成的)中去
public:
	typedef T* pointer; // pointer是个类型定义，它实际上总是T*
	typedef size_t size_type; // 通常情况下,size_type是size_t的一个类型定义
	typedef T value_type;

	pointer allocate(size_type numObjects, const void* localityHint = 0)
	{
		return static_cast<pointer>(mallocShared(numObjects * sizeof(T)));
	}

	void deallocate(pointer ptrToMemory, size_type numObjects)
	{
		freeShared(ptrToMemory);
	}

	template<typename U>
	struct rebind {
		typedef std::allocator<U> other;
	};
};

int test_item_11()
{
	typedef std::vector<double, SharedMemoryAllocator<double>> SharedDoubleVec;
	// v所分配的用来容纳其元素的内存将来自共享内存
	// 而v自己----包括它所有的数据成员----几乎肯定不会位于共享内存中，v只是普通的基于栈(stack)的对象，所以，像所
	// 有基于栈的对象一样，它将会被运行时系统放在任意可能的位置上。这个位置几乎肯定不是共享内存
#ifdef _MSC_VER
	SharedDoubleVec v; // 创建一个vector,其元素位于共享内存中


	// 为了把v的内容和v自身都放到共享内存中，需要这样做
	void* pVectorMemory = mallocShared(sizeof(SharedDoubleVec)); // 为SharedDoubleVec对象分配足够的内存
	SharedDoubleVec* pv = new (pVectorMemory)SharedDoubleVec; // 使用"placement new"在内存中创建一个SharedDoubleVec对象
	// ... // 使用对象(通过pv)
	pv->~SharedDoubleVec(); // 析构共享内存中的对象
	freeShared(pVectorMemory); // 释放最初分配的那一块共享内存
#endif

	return 0;
}

/////////////////////////////////////////////////
int test_item_12()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_13()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_14()
{
	std::vector<int> v;
	v.reserve(1000); // 如果不使用reserve,下面的循环在进行过程中将导致2到10次重新分配;加上reserve，则在循环过程中,将不会再发生重新分配
	for (int i = 1; i <= 1000; ++i) v.push_back(i);

	return 0;
}

/////////////////////////////////////////////////
int test_item_15()
{
	fprintf(stdout, "string size: %d, char* size: %d\n", sizeof(std::string), sizeof(char*));

	return 0;
}

/////////////////////////////////////////////////
void doSomething(const int* pInts, size_t numInts) {}
void doSomething(const char* pString) {}
size_t fillArray(double* pArray, size_t arraySize) { return (arraySize - 2); }
size_t fillString(char* pArray, size_t arraySize) { return (arraySize - 2); }

int test_item_16()
{
	// vector/string --> C API
	std::vector<int> v{ 1, 2 };
	if (!v.empty()) {
		doSomething(&v[0], v.size());
		doSomething(v.data(), v.size()); // C++11
		// doSomething(v.begin(), v.size()); // 错误的用法
		doSomething(&*v.begin(), v.size()); // 可以，但不易于理解
	}

	std::string s("xxx");
	doSomething(s.c_str());

	// C API 初始化vector
	const int maxNumDoubles = 100;
	std::vector<double> vd(maxNumDoubles); // 创建大小为maxNumDoubles的vector
	vd.resize(fillArray(&vd[0], vd.size())); // 使用fillArray向vd中写入数据，然后把vd的大小改为fillArray所写入的元素的个数

	// C API 初始化string
	const int maxNumChars = 100;
	std::vector<char> vc(maxNumChars); // 创建大小为maxNumChars的vector
	size_t charsWritten = fillString(&vc[0], vc.size()); // 使用fillString向vc中写入数据
	std::string s2(vc.cbegin(), vc.cbegin() + charsWritten); // 通过区间构造函数，把数据从vc拷贝到s2中

	// 先让C API把数据写入到一个vector中，然后把数据拷贝到期望最终写入的STL容器中，这一思想总是可行的
	std::deque<double> d(vd.cbegin(), vd.cend()); // 把数据拷贝到deque中
	std::list<double> l(vd.cbegin(), vd.cend()); // 把数据拷贝到list中
	std::set<double> s22(vd.cbegin(), vd.cend()); // 把数据拷贝到set中

	// 除了vector和string以外的其它STL容器也能把它们的数据传递给C API，你只需要把每个容器的元素拷贝到一个vector中，然后传给该API
	std::set<int> intSet; // 存储要传给API的数据的set
	std::vector<int> v2(intSet.cbegin(), intSet.cend()); // 把set的数据拷贝到vector
	if (!v2.empty()) doSomething(&v2[0], v2.size()); // 把数据传给API

	return 0;
}

/////////////////////////////////////////////////
class Contestant {};

int test_item_17()
{
	// 从contestants矢量中除去多余的容量
	std::vector<Contestant> contestants;
	// ... // 让contestants变大，然后删除它的大部分元素
	// vector<Contestant>(contestants)创建一个临时矢量，vector的拷贝构造函数只为所拷贝的元素分配所需要的内存
	std::vector<Contestant>(contestants).swap(contestants);

	contestants.shrink_to_fit(); // C++11

	std::string s;
	// ... // 让s变大，然后删除它的大部分字符
	std::string(s).swap(s);

	s.shrink_to_fit(); // C++11

	std::vector<Contestant>().swap(contestants); // 清除contestants并把它的容量变为最小

	std::string().swap(s); // 清除s并把它的容量变为最小

	return 0;
}

/////////////////////////////////////////////////
int test_item_18()
{
	std::vector<bool> v;
	// error: cannot convert 'std::vector<bool>::reference* {aka std::_Bit_reference}' to 'bool*' in initialization
	//bool* pb = &v[0]; // 不能被编译，原因：vector<bool>是一个假的容器，它并不真的储存bool，相反，为了节省空间，它储存的是bool的紧凑表示

	return 0;
}

/////////////////////////////////////////////////
int test_item_19()
{
	return 0;
}

/////////////////////////////////////////////////
//struct StringPtrLess : public std::binary_function<const std::string*, const std::string*, bool> { // std::binary_function在C++11中已被废弃 // removed in C++17
//	bool operator()(const std::string* ps1, const std::string* ps2) const
//	{
//		return *ps1 < *ps2;
//	}
//};

struct DereferenceLess {
	template<typename PtrType>
	bool operator()(PtrType pT1, PtrType pT2) const
	{
		return *pT1 < *pT2;
	}
};

int test_item_20()
{
	//std::set<std::string*> ssp; // std::set<std::string*> <==> std::set<std::string*, std::less<std::string*>>, 得不到预期的结果
	//std::set<std::string*, StringPtrLess> ssp;
	std::set<std::string*, DereferenceLess> ssp; // 与std::set<std::string*, StringPtrLess> ssp;的行为相同
	ssp.insert(new std::string("Anteater"));
	ssp.insert(new std::string("Wombat"));
	ssp.insert(new std::string("Lemur"));
	ssp.insert(new std::string("Penguin"));

	for (auto it = ssp.cbegin(); it != ssp.cend(); ++it) {
		fprintf(stdout, "%s\n", (**it).c_str());
	}

	return 0;
}

/////////////////////////////////////////////////
int test_item_21()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_22()
{
	std::map<int, std::string> m{ { 0, "xxx" } };
	//m.begin()->first = 10; // build error, map的键不能修改

	std::multimap<int, std::string> mm{ { 1, "yyy" } };
	//mm.begin()->first = 10; // build error, multimap的键同样不能修改

	std::set<int> s{ 1, 2, 3 };
	//*(s.begin()) = 10; // build error, set的键不能修改
	const_cast<int&>(*s.begin()) = 10; // 强制类型转换

	std::vector<int> v{ 1, 2, 3 };
	*v.begin() = 10;

	return 0;
}

/////////////////////////////////////////////////
int test_item_23()
{
	return 0;
}

/////////////////////////////////////////////////
// 提供高效的添加和更新功能
template<typename MapType, typename KeyArgType, typename ValueArgType>
typename MapType::iterator efficientAddOrUpdate(MapType& m, const KeyArgType& k, const ValueArgType& v)
{
	typename MapType::iterator lb = m.lower_bound(k); // 确定k在什么位置或应在什么位置

	if (lb != m.end() && !(m.key_comp()(k, lb->first))) { // 如果lb指向的pair的健与k等价,
		lb->second = v;				      // 则更新pair的值并返回指向该pair的迭代器
		return lb;
	}
	else {
		typedef typename MapType::value_type MVT;
		return m.insert(lb, MVT(k, v)); // 把pair<k,v>添加到m中，并返回一个指向该新元素的迭代器
	}
}

int test_item_24()
{
	std::map<int, std::string> m;
	m[1] = "xxx"; // m[1]是m.operator[](1)的缩写形式
	m.operator[](1) = "xxx";

	// m[1] = "xxx"; 在功能上等同于
	typedef std::map<int, std::string> IntStrMap;
	std::pair<IntStrMap::iterator, bool> result = m.insert(IntStrMap::value_type(1, std::string()));
	result.first->second = "xxx";
	// 以上方式性能降低的原因：先默认构造了一个string，然后立刻赋给它新的值。如果"直接使用我们所需要的值构造一个
	// string"比"先默认构造一个string再赋值"效率更高，那么，我们最好把对operator[]的使用(包括与之相伴的构造和
	// 赋值)换成对insert的直接调用
	m.insert(IntStrMap::value_type(1, "xxx")); // 它通常会节省三个函数调用：一个用于创建默认构造的临时string对象，
	// 一个用于析构该临时对象，另一个是调用string的赋值操作符

	efficientAddOrUpdate(m, 2, "yyy");

	return 0;
}

/////////////////////////////////////////////////
int test_item_25()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_26()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_27()
{
	typedef std::deque<int> IntDeque;
	typedef IntDeque::iterator Iter;
	typedef IntDeque::const_iterator ConstIter;

	IntDeque d(5, 10);
	ConstIter ci;
	ci = d.cbegin() + 1; // 使ci指向d
	Iter i(d.begin());
	std::advance(i, std::distance<ConstIter>(i, ci));

	return 0;
}

/////////////////////////////////////////////////
int test_item_28()
{
	std::vector<int> v;
	v.reserve(5);

	for (int i = 1; i <= 5; ++i) v.push_back(i);

	std::vector<int>::reverse_iterator ri = std::find(v.rbegin(), v.rend(), 3); // 使ri指向3
	std::vector<int>::iterator i(ri.base());
	fprintf(stdout, "%d\n", (*i)); // 4
	v.insert(i, 99);
	for (auto it = v.cbegin(); it != v.cend(); ++it) fprintf(stdout, "value: %d\n", *it); // 1 2 3 99 4 5

	v.clear(); v.reserve(5);
	for (int i = 1; i <= 5; ++i) v.push_back(i);
	ri = std::find(v.rbegin(), v.rend(), 3);
	v.erase((++ri).base());
	for (auto it = v.cbegin(); it != v.cend(); ++it) fprintf(stdout, "value: %d\n", *it); // 1 2 4 5

	return 0;
}

/////////////////////////////////////////////////
int test_item_29()
{
	// 把一个文本文件的内容拷贝到一个string对象中
	std::ifstream inputFile("interestingData.txt");
	inputFile.unsetf(std::ios::skipws); // 禁止忽略inputFile中的空格
	std::string fileData((std::istream_iterator<char>(inputFile)), std::istream_iterator<char>()); // 速度慢

	std::string fileData2((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>()); // 速度快

	return 0;
}

/////////////////////////////////////////////////
int transmogrify(int x) { return (x + 1); }

int test_item_30()
{
	std::vector<int> values{ 1, 2, 3 };
	std::vector<int> results;
	results.reserve(results.size() + values.size()); // 可避免内存的重新分配
	//std::transform(values.cbegin(), values.cend(), results.end(), transmogrify); // 错误，segmentation fault
	std::transform(values.cbegin(), values.cend(), std::back_inserter(results), transmogrify); // 正确
	// 在内部，std::back_inserter返回的迭代器将使得push_back被调用，所以back_inserter可适用于所有提供了push_back方法的容器

	std::list<int> results2;
	std::transform(values.cbegin(), values.cend(), std::front_inserter(results2), transmogrify);
	// std::front_inserter在内部利用了push_front，所以front_inserter仅适用于那些提供了push_front成员函数的容器


	return 0;
}

/////////////////////////////////////////////////
bool qualityCompare(const std::string& lhs, const std::string& rhs)
{
	return (lhs < rhs);
}

bool hasAcceptableQuality(const std::string& w)
{
	return true; // 判断w的质量值是否为2或者更好
}

int test_item_31()
{
	std::vector<std::string> vec(50, "xxx");
	std::partial_sort(vec.begin(), vec.begin() + 20, vec.end(), qualityCompare); // 将质量最好的20个元素顺序放在vec的前20个位置上

	std::nth_element(vec.begin(), vec.begin() + 19, vec.end(), qualityCompare); // 将最好的20个元素放在vec的前部，但并不关心它们的具体排列顺序

	// std::partia_sort和std::nth_element在效果上唯一不同之处在于：partial_sort对位置1--20中的元素进行了排序，而
	// nth_element没有对它们进行排序。然而，这两个算法都将质量最好的20个vec放到了矢量的前部

	std::vector<std::string>::iterator begin(vec.begin());
	std::vector<std::string>::iterator end(vec.end());
	std::vector<std::string>::iterator goalPosition; // 用于定位感兴趣的元素
	// 找到具有中间质量级别的string
	goalPosition = begin + vec.size() / 2; // 如果全排序的话，待查找的string应该位于中间
	std::nth_element(begin, goalPosition, end, qualityCompare); // 找到vec的中间质量值
	// 现在goalPosition所指的元素具有中间质量

	// 找到区间中具有75%质量的元素
	std::vector<std::string>::size_type goalOffset = 0.25 * vec.size(); // 找出如果全排序的话，待查找的string离起始处有多远
	std::nth_element(begin, begin + goalOffset, end, qualityCompare); // 找到75%处的质量值	

	// 将满足hasAcceptableQuality的所有元素移到前部，然后返回一个迭代器，指向第一个不满足条件的string
	std::vector<std::string>::iterator goodEnd = std::partition(vec.begin(), vec.end(), hasAcceptableQuality);

	return 0;
}

/////////////////////////////////////////////////
int test_item_32()
{
	std::vector<int> v;
	v.reserve(10);
	for (int i = 1; i <= 10; ++i) v.push_back(i);
	fprintf(stdout, "v.size: %d\n", v.size()); // 输出10
	v[3] = v[5] = v[9] = 99;
	std::remove(v.begin(), v.end(), 99); // 删除所有值等于99的元素
	fprintf(stdout, "v.size: %d\n", v.size()); // 仍然输出10, remove不是真正意义上的删除，因为它做不到
	for (auto i : v) fprintf(stdout, "%d\n", i);

	v.erase(std::remove(v.begin(), v.end(), 99), v.end()); // 真正删除所有值等于99的元素	

	return 0;
}

/////////////////////////////////////////////////
class Widget33 {
public:
	bool isCertified() const { return true; }
};

// 如果*pWidget是一个未被验证的Widget33,则删除该指针，并把它置成空
void delAndNullifyUncertified(Widget33*& pWidget)
{
	if (!pWidget->isCertified()) {
		delete pWidget;
		pWidget;
	}
}

int test_item_33()
{
	std::vector<Widget33*> v;
	for (int i = 0; i < 5; ++i) v.push_back(new Widget33);

	// 删除那些指向未被验证过的Widget33对象的指针，会资源泄露
	//v.erase(std::remove_if(v.begin(), v.end(), std::not1(std::mem_fun(&Widget33::isCertified))), v.end()); // std::mem_fun: removed in C++17

	// 一种可以消除资源泄露的做法
	// 将所有指向未被验证的Widget33对象的指针删除并置成空
	std::for_each(v.begin(), v.end(), delAndNullifyUncertified);
	// 删除v中的空指针，必须将0转换成一个指针，这样C++才能正确推断出remove的第三个参数类型
	v.erase(std::remove(v.begin(), v.end(), static_cast<Widget33*>(0)), v.end());

	// 使用智能指针可防止资源泄露
	std::vector<std::shared_ptr<Widget33>> v2;
	for (int i = 0; i < 5; ++i) v2.push_back(std::make_shared<Widget33>());
	// 下面语句需要编译器必须能够把智能指针类型std::shared<Widget33>隐式转换为对应的内置指针类型Widget33*才能通过编译
	//v2.erase(std::remove_if(v2.begin(), v2.end(), std::not1(std::mem_fun(&Widget33::isCertified))), v2.end());

	return 0;
}

/////////////////////////////////////////////////
int test_item_34()
{
	return 0;
}

/////////////////////////////////////////////////
// 忽略大小写地比较字符c1和c2，如果c1<c2,返回-1；如果c1>c2,返回1；如果c1==c2,返回0
int ciCharCompare(char c1, char c2)
{
	int lc1 = std::tolower(static_cast<unsigned char>(c1));
	int lc2 = std::tolower(static_cast<unsigned char>(c2));

	if (lc1 < lc2) return -1;
	if (lc1 > lc2) return 1;
	return 0;
}

int ciStringCompareImpl(const std::string& s1, const std::string& s2)
{
	typedef std::pair<std::string::const_iterator, std::string::const_iterator> PSCI;
	//PSCI p = std::mismatch(s1.begin(), s1.end(), s2.begin(), std::not2(std::ptr_fun(ciCharCompare))); // std::ptr_fun: removed in C++17
	//PSCI p = std::mismatch(s1.begin(), s1.end(), s2.begin(), std::not2(std::function<int(char, char)>(ciCharCompare))); // std::not1(), std::not2(), std::unary_negate, and std::binary_negate are deprecated in C++17
	PSCI p = std::mismatch(s1.begin(), s1.end(), s2.begin(), ciCharCompare);

	if (p.first == s1.end()) { // 如果为true,要么s1和s2相等，或者s1比s2短
		if (p.second == s2.end()) return 0;
		else return -1;
	}

	return ciCharCompare(*p.first, *p.second); // 字符串之间的关系和这两个不匹配的字符之间的关系相同
}

int ciStringCompare(const std::string& s1, const std::string& s2)
{
	// 把短的字符串作为第一个区间传入
	if (s1.size() <= s2.size()) return ciStringCompareImpl(s1, s2);
	else return -ciStringCompareImpl(s2, s1);
}

// 返回在忽略大小写的情况下，c1是否在c2之前
bool ciCharLess(char c1, char c2)
{
	return std::tolower(static_cast<unsigned char>(c1)) <
		std::tolower(static_cast<unsigned char>(c2));
}

bool ciStringCompare2(const std::string& s1, const std::string& s2)
{
	return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharLess);
}

bool ciStringCompare3(const std::string& s1, const std::string& s2)
{
	// 前提：不考虑国际化支持，也确定字符串中不会包含内嵌的空字符
	return strcmp(s1.c_str(), s2.c_str());
}

int test_item_35()
{
	std::string str1{ "xxz" }, str2{ "xxx" };
	fprintf(stdout, "str1:str2: %d\n", ciStringCompare(str1, str2));
	fprintf(stdout, "str1:str2: %d\n", ciStringCompare2(str1, str2));
	fprintf(stdout, "str1:str2: %d\n", ciStringCompare3(str1, str2));

	return 0;
}

/////////////////////////////////////////////////
int test_item_36()
{
	std::vector<int> v1{ 1, 2, 3, 4, 5 }, v2(v1.size());

	auto it = std::copy_if(v1.begin(), v1.end(), v2.begin(), [](int i) { return (i % 2 == 1); });
	v2.resize(std::distance(v2.begin(), it));

	for (const auto& v : v2)
		fprintf(stdout, "%d\n", v); // 1 3 5

	return 0;
}

/////////////////////////////////////////////////
// 接受当前的长度总和值和新的字符串，然后返回更新之后的总和值
std::string::size_type stringLengthSum(std::string::size_type sumSoFar, const std::string& s)
{
	return sumSoFar + s.size();
}

struct Point {
	Point() = default;
	Point(double initX, double initY) : x(initX), y(initY) {}
	double x, y;
};

//class PointAverage : public std::unary_function<Point, void> { // std::unary_function: removed in C++17
class PointAverage : public Point {
public:
	PointAverage() : xSum(0), ySum(0), numPoints(0) {}

	void operator()(const Point& p)
	{
		++numPoints;
		xSum += p.x;
		ySum += p.y;
	}

	Point result() const
	{
		return Point(xSum / numPoints, ySum / numPoints);
	}

private:
	size_t numPoints;
	double xSum, ySum;
};

int test_item_37()
{
	std::vector<double> v{ 1.0f, 2.2f, 3.3f, 4.5f };
	double sum = std::accumulate(v.cbegin(), v.cend(), 0.0); // 注意：初始值被指定为0.0,而不是简单的0
	fprintf(stdout, "vaule: %f\n", sum); // 11.000000

	fprintf(stdout, "sum of the ints: %d\n", std::accumulate(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), 0)); // 输入非整数值结束,如字母

	std::set<std::string> ss{ "abc", "cde", "xyzw" };
	// 计算一个容器中字符串的长度总和
	std::string::size_type lengthSum = std::accumulate(ss.cbegin(), ss.cend(),
		static_cast<std::string::size_type>(0), stringLengthSum);
	fprintf(stdout, "length sum: %d\n", lengthSum); // 10

	// 计算一个区间中数值的乘积
	std::vector<float> vf{ 1.f, 2.f, 3.f, 1.5f };
	float product = std::accumulate(vf.cbegin(), vf.cend(), 1.f, std::multiplies<float>());
	fprintf(stdout, "product: %f\n", product); // 9.000000

	// 计算出一个区间中所有点的平均值
	std::list<Point> lp{ { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 } };
	Point avg = std::for_each(lp.cbegin(), lp.cend(), PointAverage()).result();

	return 0;
}

/////////////////////////////////////////////////
class Widget38 {};
template<typename T> class BPFC;

template<typename T>
//class BPFCImpl : public std::unary_function<T, void> { // std::unary_function: removed in C++17
class BPFCImpl {
private:
	Widget38 w; // 原来BPFC中所有数据现在都放在这里
	int x;
	virtual ~BPFCImpl(); // 多态类需要虚析构函数
	virtual void operator()(const T& val) const;

	friend class BPFC<T>; // 允许BPFC访问内部数据
};

template<typename T>
//class BPFC : public std::unary_function<T, void> { // 新的BPFC类:短小、单态 // // std::unary_function: removed in C++17
class BPFC {
private:
	BPFCImpl<T>* pImpl; // BPFC唯一的数据成员
public:
	void operator()(const T& val) const // 现在这是一个非虚函数，将调用转到BPFCImpl中
	{
		pImpl->operator()(val);
	}
};

int test_item_38()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_39()
{
	return 0;
}

/////////////////////////////////////////////////
bool isInteresting(const std::string* pw) { return true; }

int test_item_40()
{
	std::list<std::string*> strs{ new std::string("xxx"), new std::string("yyy"), new std::string("zzz") };
	std::list<std::string*>::iterator it = std::find_if(strs.begin(), strs.end(), isInteresting);
	//std::list<std::string*>::iterator it2 = std::find_if(strs.begin(), strs.end(), std::not1(std::ptr_fun(isInteresting))); // std::ptr_fun: removed in C++17
	std::list<std::string*>::iterator it2 = std::find_if(strs.begin(), strs.end(), isInteresting);

	return 0;
}

/////////////////////////////////////////////////
class Widget41 {
public:
	void test() {}
};

void test(Widget41& w) {}

int test_item_41()
{
	std::vector<Widget41> vw;

	std::for_each(vw.begin(), vw.end(), test);
	//std::for_each(vw.begin(), vw.end(), std::ptr_fun(test)); // std::ptr_fun: removed in C++17
	//std::for_each(vw.begin(), vw.end(), std::mem_fun_ref(&Widget41::test)); // std::mem_fun_ref: removed in C++17

	std::list<Widget41*> lpw;
	//std::for_each(lpw.begin(), lpw.end(), std::mem_fun(&Widget41::test)); // std::mem_fun: removed in C++17

	return 0;
}

/////////////////////////////////////////////////
int test_item_42()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_43()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_44()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_45()
{
	return 0;
}

/////////////////////////////////////////////////
//struct StringSize : public std::unary_function<std::string, std::string::size_type> { // std::unary_function: removed in C++17
struct StringSize {
	std::string::size_type operator()(const std::string& s) const
	{
		return s.size();
	}
};

int test_item_46()
{
	std::set<std::string> s{ "abc", "cde", "xyzw" };
	//std::transform(s.begin(), s.end(), std::ostream_iterator<std::string::size_type>(std::cout, "\n"), std::mem_fun_ref(&std::string::size)); // 3 3 4，普通函数 // std::mem_fun_ref: removed in C++17

	std::transform(s.begin(), s.end(), std::ostream_iterator<std::string::size_type>(std::cout, "\n"), StringSize()); // 3 3 4, 函数对象

	return 0;
}

/////////////////////////////////////////////////
int test_item_47()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_48()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_49()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_50()
{
	return 0;
}

} // namespace more_effective_cplusplus_

