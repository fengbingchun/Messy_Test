#ifndef FBC_MESSY_TEST_COMPONENT_HPP_
#define FBC_MESSY_TEST_COMPONENT_HPP_

class Component_1
{
public:
	Component_1();
	virtual ~Component_1();
public:
	virtual void Operation() = 0;
	virtual void Add(const Component_1&);
	virtual void Remove(const Component_1&);
	virtual Component_1* GetChild(int);
protected:
private:
};

#endif // FBC_MESSY_TEST_COMPONENT_HPP_
