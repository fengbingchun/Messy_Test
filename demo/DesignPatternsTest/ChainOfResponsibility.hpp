#ifndef FBC_MESSY_TEST_CHAIN_OF_RESPONSIBILITY_HPP_
#define FBC_MESSY_TEST_CHAIN_OF_RESPONSIBILITY_HPP_

#include <iostream>
#include <string>

//请求
class Request
{
public:
	std::string m_strContent;
	int m_nNumber;
};

//管理者
class Manager
{
protected:
	Manager* manager;
	std::string name;
public:
	Manager(std::string temp)
	{
		name = temp;
	}

	void SetSuccessor(Manager* temp)
	{
		manager = temp;
	}

	virtual void GetRequest(Request* request) = 0;
};

//经理
class CommonManager : public Manager
{
public:
	CommonManager(std::string strTemp) : Manager(strTemp) {}

	virtual void GetRequest(Request* request)
	{
		if (request->m_nNumber >= 0 && request->m_nNumber < 10)
			std::cout << name << "处理了" << request->m_nNumber << "个请求" << std::endl;
		else
			manager->GetRequest(request);
	}
};

//总监
class MajorDomo : public Manager
{
public:
	MajorDomo(std::string name) : Manager(name) {}

	virtual void GetRequest(Request* request)
	{
		if (request->m_nNumber >= 10)
			std::cout << name << "处理了" << request->m_nNumber << "个请求" << std::endl;
	}
};

int test_ChainOfResponsibility1();
int test_ChainOfResponsibility2();

#endif // FBC_MESSY_TEST_CHAIN_OF_RESPONSIBILITY_HPP_