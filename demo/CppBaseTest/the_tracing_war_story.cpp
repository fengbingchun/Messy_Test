#include "the_tracing_war_story.hpp"
#include <string>
#include <iostream>

namespace tracing_war_story_ {

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

bool Trace1::traceIsActive = false; // 关闭跟踪

int test_tracing_war_story_1()
{
	/*
	  在关闭跟踪情况下产生的开销:
	  引发一系列计算:
	    (1). 创建一个作用域为test_tracing_war_story_1的string型变量name
	    (2). 调用Trace1的构造函数
	    (3). Trace1的构造函数调用string的构造函数来创建一个string
	  在此函数的结尾,Trace1对象和两个string对象被销毁：
	    (1). 销毁string型变量name
	    (2). 调用Trace1的析构函数
	    (3). Trace1的析构函数为成员string调用string的析构函数
	*/
	std::string name = "test_tracing_war_story_1";
	Trace1 t(name);
	std::string moreInfo = "more interesting info";
	t.debug(moreInfo);	

	return 0;
}

int test_tracing_war_story_2()
{
	return 0;
}

} // namespace tracing_war_story


