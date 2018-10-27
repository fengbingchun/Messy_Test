#include "the_tracing_war_story.hpp"
#include <string>
#include <iostream>
#include <chrono>

// Blog: https://blog.csdn.net/fengbingchun/article/details/83449625

namespace tracing_war_story_ {
//////////////////////////////////////////////////
// 较差的Trace1类设计
class Trace1 {
public:
	Trace1(const std::string& name);
	~Trace1();
	void debug(const std::string& msg);

	static bool traceIsActive;
private:
	std::string theFunctionName;
};

inline Trace1::Trace1(const std::string& name) : theFunctionName(name)
{
	if (traceIsActive) {
		std::cout << "Enter function: " << name << std::endl;
	}
}

inline Trace1::~Trace1()
{
	if (traceIsActive) {
		std::cout <<"Exit function: " << theFunctionName << std::endl;
	}
}

inline void Trace1::debug(const std::string& msg)
{
	if (traceIsActive) {
		std::cout << msg << std::endl;
	}
}

bool Trace1::traceIsActive = false; // 默认设置为false关闭跟踪;可以在test_tracing_war_story中设置是否开启还是关闭跟踪

int addOne0(int x)
{
	return x+1;
}

int addOne1(int x)
{
	std::string name = "addOne1";
	Trace1 t(name);

	return x+1;
}

///////////////////////////////////////////////////
// Trace2类是对Trace1类的改进：将函数参数string类型调整为const char*
class Trace2 {
public:
	Trace2(const char* name);
	~Trace2();
	void debug(const char* msg);

	static bool traceIsActive;
private:
	std::string theFunctionName;
};

inline Trace2::Trace2(const char* name) : theFunctionName(name)
{
	if (traceIsActive) {
		std::cout << "Enter function: " << name << std::endl;
	}
}

inline Trace2::~Trace2()
{
	if (traceIsActive) {
		std::cout <<"Exit function: " << theFunctionName << std::endl;
	}
}

inline void Trace2::debug(const char* msg)
{
	if (traceIsActive) {
		std::cout << msg << std::endl;
	}
}

bool Trace2::traceIsActive = false; // 默认设置为false关闭跟踪;可以在test_tracing_war_story中设置是否开启还是关闭跟踪

int addOne2(int x)
{
	char* name = "addOne2";
	Trace2 t(name);

	return x+1;
}

/////////////////////////////////////////////////////
// Trace3类是对Trace2类的改进：消除包含在Trace2类内的string成员对象的无条件的创建
class Trace3 {
public:
	Trace3(const char* name);
	~Trace3();
	void debug(const char* msg);

	static bool traceIsActive;
private:
	// string指针可以把string对象的创建推迟到确定跟踪处于打开状态以后
	std::string* theFunctionName;
};

inline Trace3::Trace3(const char* name) : theFunctionName(nullptr)
{
	if (traceIsActive) {
		std::cout << "Enter function: " << name << std::endl;
		theFunctionName = new std::string(name);
	}
}

inline Trace3::~Trace3()
{
	if (traceIsActive) {
		std::cout <<"Exit function: " << theFunctionName << std::endl;
		delete theFunctionName;
	}
}

inline void Trace3::debug(const char* msg)
{
	if (traceIsActive) {
		std::cout << msg << std::endl;
	}
}

bool Trace3::traceIsActive = false; // 默认设置为false关闭跟踪;可以在test_tracing_war_story中设置是否开启还是关闭跟踪

int addOne3(int x)
{
	char* name = "addOne3";
	Trace3 t(name);

	return x+1;
}

int test_tracing_war_story()
{
	Trace1::traceIsActive = false;

	/*
	  Trace1实现就是一个无用对象对性能带来破坏性影响的实例：即创建和后面的销毁预计要使用却没有使用的不必要的对象
	  在关闭跟踪情况下产生的开销:
	  引发一系列计算:
	    (1). 创建一个作用域为test_tracing_war_story的string型变量name
	    (2). 调用Trace1的构造函数
	    (3). Trace1的构造函数调用string的构造函数来创建一个string
	  在此函数的结尾,Trace1对象和两个string对象被销毁：
	    (1). 销毁string型变量name
	    (2). 调用Trace1的析构函数
	    (3). Trace1的析构函数为成员string调用string的析构函数
	  在跟踪被关闭的情况下，string的成员对象从未被使用,Trace1对象本身也未被使用,所有这些用于对象的创建和销毁的计算都是纯碎的浪费
	*/
	std::string name = "test_tracing_war_story";
	Trace1 t(name);
	std::string moreInfo = "more interesting info";
	t.debug(moreInfo);

	using namespace std::chrono;
	high_resolution_clock::time_point timeStart, timeEnd;
	int count = 1000000;
	
	// 通过addOne0和addOne1测试Trace1对象的性能开销
	timeStart = high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		addOne0(i);
	}
	timeEnd = high_resolution_clock::now();
	std::cout<< "addOne0 time spen: " <<(duration_cast<duration<double>>(timeEnd-timeStart)).count()<<" seconds"<<std::endl;
	
	timeStart = high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		addOne1(i);
	}
	timeEnd = high_resolution_clock::now();
	std::cout<< "addOne1 time spen: " <<(duration_cast<duration<double>>(timeEnd-timeStart)).count()<<" seconds"<<std::endl;

	Trace2::traceIsActive = false;

	// 通过addOne2测试Trace2对象的性能开销
	timeStart = high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		addOne2(i);
	}
	timeEnd = high_resolution_clock::now();
	std::cout<< "addOne2 time spen: " <<(duration_cast<duration<double>>(timeEnd-timeStart)).count()<<" seconds"<<std::endl;
	
	Trace3::traceIsActive = false;

	// 通过addOne3测试Trace3对象的性能开销
	timeStart = high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		addOne3(i);
	}
	timeEnd = high_resolution_clock::now();
	std::cout<< "addOne3 time spen: " <<(duration_cast<duration<double>>(timeEnd-timeStart)).count()<<" seconds"<<std::endl;
	
	return 0;
}

} // namespace tracing_war_story


