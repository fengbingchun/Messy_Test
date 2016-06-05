#ifndef FBC_MESSY_TEST_ELEMENT_HPP_
#define FBC_MESSY_TEST_ELEMENT_HPP_

class Visitor;

class Element
{
public:
	virtual ~Element();
	virtual void Accept(Visitor* vis) = 0;
protected:
	Element();
private:
};

class ConcreteElementA : public Element
{
public:
	ConcreteElementA();
	~ConcreteElementA();
	void Accept(Visitor* vis);
protected:
private:
};

class ConcreteElementB : public Element
{
public:
	ConcreteElementB();
	~ConcreteElementB();
	void Accept(Visitor* vis);
protected:
private:
};

#endif // FBC_MESSY_TEST_ELEMENT_HPP_