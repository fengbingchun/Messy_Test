#include "Observer.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/34933089

void StockObserver::Update()
{
	std::cout << name << ":" << sub->action << "，不要玩股票了，要开始工作了" << std::endl;
}

void StockObserver_1::Update()
{
	std::cout << name << ":" << sub->action << "不要玩股票了，要开始工作了" << std::endl;
}

void NBAObserver::Update()
{
	std::cout << name << ":" << sub->action << "不要看NBA了，老板来了" << std::endl;
}

Observer::Observer()
{
	_st = '\0';
}

Observer::~Observer()
{

}

ConcreteObserverA::ConcreteObserverA(Subject* sub)
{
	_sub = sub;
	_sub->Attach(this);
}

ConcreteObserverA::~ConcreteObserverA()
{
	_sub->Detach(this);

	if (_sub != 0)
		delete _sub;
}

Subject* ConcreteObserverA::GetSubject()
{
	return _sub;
}

void ConcreteObserverA::PrintInfo()
{
	std::cout << "ConcreteObserverA observer ..." << _sub->GetState() << std::endl;
}

void ConcreteObserverA::Update(Subject* sub)
{
	_st = sub->GetState();
	PrintInfo();
}

ConcreteObserverB::ConcreteObserverB(Subject* sub)
{
	_sub = sub;
	_sub->Attach(this);
}

ConcreteObserverB::~ConcreteObserverB()
{
	_sub->Detach(this);

	if (_sub != 0)
		delete _sub;
}

Subject* ConcreteObserverB::GetSubject()
{
	return _sub;
}

void ConcreteObserverB::PrintInfo()
{
	std::cout << "ConcreteObserverB observer ..." << _sub->GetState() << std::endl;
}

void ConcreteObserverB::Update(Subject* sub)
{
	_st = sub->GetState();
	PrintInfo();
}


int test_Observer1()
{
	Secretary* p = new Secretary();//创建通知者

	//观察者
	StockObserver* s1 = new StockObserver("小李", p);
	StockObserver* s2 = new StockObserver("小赵", p);

	//加入通知队列
	p->Add(*s1);
	p->Add(*s2);

	//事件
	p->action = "老板来了";

	//通知
	p->Notify();

	/*result
		小李：老板来了，不要玩股票了，要开始工作了
		小赵：老板来了，不要玩股票了，要开始工作了
	*/

	return 0;
}

int test_Observer2()
{
	SecretaryBase* p = new Secretary_1();//创建观察者

	//被观察的对象
	CObserverBase* s1 = new NBAObserver("小李", p);
	CObserverBase* s2 = new StockObserver_1("小赵", p);
	//加入观察队列
	p->Attach(s1);
	p->Attach(s2);
	//事件
	p->action = "老板来了";
	//通知
	p->Notify();

	/*result
		小李：老板来了不要看NBA了，老板来了
		小赵：老板来了不要玩股票了，要开始工作了
	*/

	return 0;
}

int test_Observer3()
{
	ConcreteSubject* sub = new ConcreteSubject();
	Observer* o1 = new ConcreteObserverA(sub);
	Observer* o2 = new ConcreteObserverB(sub);
	sub->SetState("old");
	sub->Notify();
	sub->SetState("new");//也可以由Observer调用
	sub->Notify();

	/*result
		ConcreteObserverB observer ...old
		ConcreteObserverA observer ...old
		ConcreteObserverB observer ...new
		ConcreteObserverA observer ...new
	*/

	return 0;
}
