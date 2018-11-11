#include "constructors_and_destructors.hpp"
#include <iostream>
#include <string>
#include <mutex>
#include <chrono>

// Blog: https://blog.csdn.net/fengbingchun/article/details/83960568

namespace constructors_destructors_ {

// reference: 《提高C++性能的编程技术》:第二章:构造函数和析构函数

class SimpleMutex { // 单独的锁类
public:
	SimpleMutex(std::mutex& mtx) : mymtx(mtx) { acquire(); }
	~SimpleMutex() { release(); }
	
private:
	void acquire() { mymtx.lock(); }
	void release() { mymtx.unlock(); }

	std::mutex& mymtx; 
};

class BaseMutex { // 基类
public:
	BaseMutex(std::mutex& mtx) {}
	virtual ~BaseMutex() {}
};

class DerivedMutex : public BaseMutex {
public:
	DerivedMutex(std::mutex& mtx) : BaseMutex(mtx), mymtx(mtx) { acquire(); }
	~DerivedMutex() { release(); }

private:
	void acquire() { mymtx.lock(); }
	void release() { mymtx.unlock(); }

	std::mutex& mymtx;

};

class Person1 {
public:
	Person1(const char* s) { name = s; } // 隐式初始化和显示赋值

private:
	std::string name; 
};

class Person2 {
public:
	Person2(const char* s) : name(s) {} // 显示初始化

private:
	std::string name;
};

int test_constructors_destructors_1()
{
	// 测试三种互斥锁的实现
	// Note:与书中实验结果有差异，在这里继承对象并不会占用较多的执行时间，在这里这三种所占用时间基本差不多
	using namespace std::chrono;
	high_resolution_clock::time_point time_start, time_end;
	const int cycle_number {100000000};
	int  shared_counter {0};
	

{ // 1.直接调用mutex
	std::mutex mtx;
	shared_counter = 0;
	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		mtx.lock();
		++shared_counter;
		mtx.unlock();
	}
	time_end = high_resolution_clock::now();
	std::cout<< "time spen1: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<< " seconds\n";
}

{ // 2.不从基类继承的独立互斥对象
	std::mutex mtx;
	shared_counter = 0;
	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		SimpleMutex m(mtx);
		++shared_counter;
	}
	time_end = high_resolution_clock::now();
	std::cout<< "time spen2: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<<" seconds\n";
}

{ // 3.从基类派生的互斥对象
	std::mutex mtx;
	shared_counter = 0;
	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		DerivedMutex m(mtx);
		++shared_counter;
	}
	time_end = high_resolution_clock::now();
	std::cout<< "time spen3: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<<" seconds\n";

}

	// 隐式初始化和显示赋值与显示初始化性能对比：使用显示初始化操作要优于使用隐式初始化和显示赋值操作
{ // 1.隐式初始化和显示赋值操作
	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		Person1 p("Pele");	
	}
	time_end = high_resolution_clock::now();
	std::cout<< "隐式初始化, time spen: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<<" seconds\n";
}

{ // 2.显示初始化操作
	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		Person2 p("Pele");
	}
	time_end = high_resolution_clock::now();
	std::cout<<"显示初始化, time spen: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<<" seconds\n";
}

	return 0;
}

} // namespace constructors_destructors_

