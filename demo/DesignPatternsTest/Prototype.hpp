#ifndef FBC_MESSY_TEST_PROTOTYPE_HPP_
#define FBC_MESSY_TEST_PROTOTYPE_HPP_

#include <string>
#include <iostream>

class Prototype//抽象基类
{
private:
	std::string m_strName;
public:
	Prototype(std::string strName) { m_strName = strName; }
	Prototype() { m_strName = ""; }
	void Show()
	{
		std::cout << m_strName << std::endl;
	}
	virtual Prototype* Clone() = 0;
};

//class ConcretePrototype1
class ConcretePrototype1 : public Prototype
{
public:
	ConcretePrototype1(std::string strName) : Prototype(strName) {}
	ConcretePrototype1() {}

	virtual Prototype* Clone()
	{
		ConcretePrototype1* p = new ConcretePrototype1();
		*p = *this;//复制对象
		return p;
	}
};

//class ConcretePrototype2
class ConcretePrototype2 : public Prototype
{
public:
	ConcretePrototype2(std::string strName) : Prototype(strName) {}
	ConcretePrototype2() {}

	virtual Prototype* Clone()
	{
		ConcretePrototype2* p = new ConcretePrototype2();
		*p = *this;//复制对象

		return p;
	}
};

// ===========================================
class Prototype_1
{
public:
	virtual ~Prototype_1();
	virtual Prototype_1* Clone() const = 0;
protected:
	Prototype_1();
private:
};

class ConcretePrototype_1 : public Prototype_1
{
public:
	ConcretePrototype_1();
	ConcretePrototype_1(const ConcretePrototype_1& cp);
	~ConcretePrototype_1();
	Prototype_1* Clone() const;
protected:
private:
};

int test_Prototype1();
int test_Prototype2();

#endif // FBC_MESSY_TEST_PROTOTYPE_HPP_