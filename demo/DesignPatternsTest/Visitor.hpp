#ifndef FBC_MESSY_TEST_VISITOR_HPP_
#define FBC_MESSY_TEST_VISITOR_HPP_

#include <iostream>
#include <vector>

class Man;
class Woman;

//行为
class Action
{
public:
	virtual void GetManConclusion(Man* concreteElementA) = 0;
	virtual void GetWomanConclusion(Woman* concreteElementB) = 0;
};

//成功
class Success : public Action
{
public:
	virtual void GetManConclusion(Man* concreteElementA)
	{
		std::cout << "男人成功时，背后有个伟大的女人" << std::endl;
	}

	virtual void GetWomanConclusion(Woman* concreteElementB)
	{
		std::cout << "女人成功时，背后有个没用的男人" << std::endl;
	}
};

//失败
class Failure : public Action
{
public:
	virtual void GetManConclusion(Man* concreteElementA)
	{
		std::cout << "男人失败时，背后有个伟大的女人" << std::endl;
	}

	virtual void GetWomanConclusion(Woman* concreteElementB)
	{
		std::cout << "女人失败时，背后有个没用的男人" << std::endl;
	}
};

//抽象人类
class Person_2
{
public:
	virtual void Accept(Action* visitor) = 0;
};

//男人
class Man : public Person_2
{
public:
	virtual void Accept(Action* visitor)
	{
		visitor->GetManConclusion(this);
	}
};

//女人
class Woman : public Person_2
{
public:
	virtual void Accept(Action* visitor)
	{
		visitor->GetWomanConclusion(this);
	}
};

//对象结构类
class ObjectStructure
{
private:
	std::vector<Person_2*> m_personList;
public:
	void Add(Person_2* p)
	{
		m_personList.push_back(p);
	}

	void Display(Action* a)
	{
		std::vector<Person_2*>::iterator p = m_personList.begin();

		while (p != m_personList.end()) {
			(*p)->Accept(a);
			p++;
		}
	}
};

// =============================================
class ConcreteElementA;
class ConcreteElementB;
class Element;

class Visitor
{
public:
	virtual ~Visitor();
	virtual void VisitConcreteElementA(Element* elm) = 0;
	virtual void VisitConcreteElementB(Element* elm) = 0;
protected:
	Visitor();
private:
};

class ConcreteVisitorA : public Visitor
{
public:
	ConcreteVisitorA();
	virtual ~ConcreteVisitorA();
	virtual void VisitConcreteElementA(Element* elm);
	virtual void VisitConcreteElementB(Element* elm);
protected:
private:
};

class ConcreteVisitorB : public Visitor
{
public:
	ConcreteVisitorB();
	virtual ~ConcreteVisitorB();
	virtual void VisitConcreteElementA(Element* elm);
	virtual void VisitConcreteElementB(Element* elm);
protected:
private:
};

int test_Visitor1();
int test_Visitor2();

#endif // FBC_MESSY_TEST_VISITOR_HPP_
