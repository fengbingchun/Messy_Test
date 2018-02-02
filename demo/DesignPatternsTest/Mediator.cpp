#include "Mediator.hpp"
#include "Colleague.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/35815763

Mediator_1::Mediator_1()
{

}

Mediator_1::~Mediator_1()
{

}

ConcreteMediator_1::ConcreteMediator_1()
{

}

ConcreteMediator_1::~ConcreteMediator_1()
{

}

ConcreteMediator_1::ConcreteMediator_1(Colleague_1* clgA, Colleague_1* clgB)
{
	this->_clgA = clgA;
	this->_clgB = clgB;
}

void ConcreteMediator_1::DoActionFromAtoB()
{
	_clgB->SetState(_clgA->GetState());
}

void ConcreteMediator_1::SetConcreteColleagueA(Colleague_1* clgA)
{
	this->_clgA = clgA;
}

void ConcreteMediator_1::SetConcreteColleagueB(Colleague_1* clgB)
{
	this->_clgB = clgB;
}

Colleague_1* ConcreteMediator_1::GetConcreteColleagueA()
{
	return _clgA;
}

Colleague_1* ConcreteMediator_1::GetConcreteColleagueB()
{
	return _clgB;
}

void ConcreteMediator_1::IntroColleague(Colleague_1* clgA, Colleague_1* clgB)
{
	this->_clgA = clgA;
	this->_clgB = clgB;
}

void ConcreteMediator_1::DoActionFromBtoA()
{
	_clgA->SetState(_clgB->GetState());
}

int test_Mediator1()
{
	ConcreteMediator* m = new ConcreteMediator();

	//让同事认识中介
	Colleague1* col1 = new Colleague1(m);
	Colleague2* col2 = new Colleague2(m);

	//让中介认识具体的同事类
	m->col1 = col1;
	m->col2 = col2;

	col1->Send("吃饭了吗？");
	col2->Send("还没吃，你请吗？");

	/*result
		同事二获得了消息吃饭了吗？
		同事一获得了消息还没吃，你请吗？
	*/

	return 0;
}

int test_Mediator2()
{
	ConcreteMediator_1* m = new ConcreteMediator_1();
	ConcreteColleagueA_1* c1 = new ConcreteColleagueA_1(m);
	ConcreteColleagueB_1* c2 = new ConcreteColleagueB_1(m);

	m->IntroColleague(c1, c2);

	c1->SetState("old");
	c2->SetState("old");
	c1->Action();
	c2->Action();
	std::cout << std::endl;

	c1->SetState("new");
	c1->Action();
	c2->Action();
	std::cout << std::endl;

	c2->SetState("old");
	c2->Action();
	c1->Action();

	/*result
		State of ConcreteColleagueA:old
		State of ConcreteColleagueB:old

		State of ConcreteColleagueA:new
		State of ConcreteColleagueB:new

		State of ConcreteColleagueB:old
		State of ConcreteColleagueA:old
	*/

	return 0;
}
