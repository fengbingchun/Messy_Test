#ifndef FBC_MESSY_TEST_COMPOSITE_HPP_
#define FBC_MESSY_TEST_COMPOSITE_HPP_

#include <string>
#include <vector>
#include <iostream>

#include "Component.hpp"

class Component
{
public:
	std::string m_strName;
	Component(std::string strName)
	{
		m_strName = strName;
	}

	virtual void Add(Component* com) = 0;
	virtual void Display(int nDepth) = 0;
};

class Leaf : public Component
{
public:
	Leaf(std::string strName) : Component(strName) {}
	virtual void Add(Component* com)
	{
		std::cout << "leaf can't add" << std::endl;
	}

	virtual void Display(int nDepth)
	{
		std::string strtemp;

		for (int i = 0; i < nDepth; i++)
			strtemp += "-";

		strtemp += m_strName;
		std::cout << strtemp << std::endl;
	}
};

class Composite : public Component
{
private:
	std::vector<Component*> m_component;
public:
	Composite(std::string strName) : Component(strName) {}

	virtual void Add(Component* com)
	{
		m_component.push_back(com);
	}

	virtual void Display(int nDepth)
	{
		std::string strtemp;

		for (int i = 0; i < nDepth; i++)
			strtemp += "-";

		strtemp += m_strName;
		std::cout << strtemp << std::endl;

		std::vector<Component*>::iterator p = m_component.begin();

		while (p != m_component.end()) {
			(*p)->Display(nDepth + 2);
			p++;
		}
	}
};

// ==============================================
class Company
{
protected:
	std::string m_strName;
public:
	Company(std::string strName)
	{
		m_strName = strName;
	}

	virtual void Add(Company* c) = 0;
	virtual void Display(int nDepth) = 0;
	virtual void LineOfDuty() = 0;
};

class ConcreteCompany : public Company
{
private:
	std::vector<Company*> m_company;
public:
	ConcreteCompany(std::string strName) : Company(strName) {}

	virtual void Add(Company* c)
	{
		m_company.push_back(c);
	}

	virtual void Display(int nDepth)
	{
		std::string strtemp;

		for (int i = 0; i < nDepth; i++)
			strtemp += "-";

		strtemp += m_strName;
		std::cout << strtemp << std::endl;

		std::vector<Company*>::iterator p = m_company.begin();
		while (p != m_company.end()) {
			(*p)->Display(nDepth + 1);
			p++;
		}
	}

	virtual void LineOfDuty()
	{
		std::vector<Company*>::iterator p = m_company.begin();

		while (p != m_company.end()) {
			(*p)->LineOfDuty();
			p++;
		}
	}
};

class HrDepartment : public Company
{
public:
	HrDepartment(std::string strname) : Company(strname) {}

	virtual void Display(int nDepth)
	{
		std::string strtemp;

		for (int i = 0; i < nDepth; i++)
			strtemp += "-";

		strtemp += m_strName;
		std::cout << strtemp << std::endl;
	}

	virtual void Add(Company* c)
	{
		std::cout << "error" << std::endl;
	}

	virtual void LineOfDuty()
	{
		std::cout << m_strName << ":ÕÐÆ¸ÈË²Å" << std::endl;
	}
};

// =========================================================
class Composite_1 : public Component_1
{
public:
	Composite_1();
	~Composite_1();
public:
	void Operation();
	void Add(Component_1* com);
	void Remove(Component_1* com);
	Component_1* GetChild(int index);
protected:
private:
	std::vector<Component_1*> comVec;
};

int test_Composite1();
int test_Composite2();
int test_Composite3();

#endif // FBC_MESSY_TEST_COMPOSITE_HPP_
