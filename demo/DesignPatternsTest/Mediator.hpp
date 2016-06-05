#ifndef FBC_MESSY_TEST_MEDIATOR_HPP_
#define FBC_MESSY_TEST_MEDIATOR_HPP_

#include <iostream>
#include <string>

class Colleague;

//中介者类
class Mediator
{
public:
	virtual void Send(std::string message, Colleague* col) = 0;
};

//抽象同事类
class Colleague
{
protected:
	Mediator* mediator;
public:
	Colleague(Mediator* temp)
	{
		mediator = temp;
	}
};

//同事一
class Colleague1 : public Colleague
{
public:
	Colleague1(Mediator* media) : Colleague(media) {}

	void Send(std::string strMessage)
	{
		mediator->Send(strMessage, this);
	}

	void Notify(std::string strMessage)
	{
		std::cout << "同事一获得了消息" << strMessage << std::endl;
	}
};

//同事二
class Colleague2 : public Colleague
{
public:
	Colleague2(Mediator* media) : Colleague(media) {}

	void Send(std::string strMessage)
	{
		mediator->Send(strMessage, this);
	}

	void Notify(std::string strMessage)
	{
		std::cout << "同事二获得了消息" << strMessage << std::endl;
	}
};

//具体中介者类
class ConcreteMediator : public Mediator
{
public:
	Colleague1* col1;
	Colleague2* col2;

	virtual void Send(std::string message, Colleague* col)
	{
		if (col == col1)
			col2->Notify(message);
		else
			col1->Notify(message);
	}
};

// =========================================================
class Colleague_1;

class Mediator_1
{
public:
	virtual ~Mediator_1();
	virtual void DoActionFromAtoB() = 0;
	virtual void DoActionFromBtoA() = 0;
protected:
	Mediator_1();
private:
};

class ConcreteMediator_1 : public Mediator_1
{
public:
	ConcreteMediator_1();
	ConcreteMediator_1(Colleague_1* clgA, Colleague_1* clgB);
	~ConcreteMediator_1();
	void SetConcreteColleagueA(Colleague_1* clgA);
	void SetConcreteColleagueB(Colleague_1* clgB);
	Colleague_1* GetConcreteColleagueA();
	Colleague_1* GetConcreteColleagueB();
	void IntroColleague(Colleague_1* clgA, Colleague_1* clgB);
	void DoActionFromAtoB();
	void DoActionFromBtoA();
protected:
private:
	Colleague_1* _clgA;
	Colleague_1* _clgB;
};

int test_Mediator1();
int test_Mediator2();

#endif // FBC_MESSY_TEST_MEDIATOR_HPP_
