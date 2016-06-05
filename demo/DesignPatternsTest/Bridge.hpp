#ifndef FBC_MESSY_TEST_BRIDGE_HPP_
#define FBC_MESSY_TEST_BRIDGE_HPP_

#include <iostream>

// ==================================================
//手机软件
class HandsetSoft
{
public:
	virtual void Run() = 0;
};

//游戏软件
class HandsetGame : public HandsetSoft
{
public:
	virtual void Run()
	{
		std::cout << "运行手机游戏" << std::endl;
	}
};

//通讯录软件
class HandSetAddressList : public HandsetSoft
{
public:
	virtual void Run()
	{
		std::cout << "手机通讯录" << std::endl;
	}
};

//手机品牌
class HandsetBrand
{
protected:
	HandsetSoft* m_soft;
public:
	void SetHandsetSoft(HandsetSoft* temp)
	{
		m_soft = temp;
	}
	virtual void Run() = 0;
};

//M品牌
class HandsetBrandM : public HandsetBrand
{
public:
	virtual void Run()
	{
		m_soft->Run();
	}
};

//N品牌
class HandsetBrandN : public HandsetBrand
{
public:
	virtual void Run()
	{
		m_soft->Run();
	}
};

// ========================================================
class AbstractionImp;

class Abstraction
{
public:
	virtual ~Abstraction();
	virtual void Operation() = 0;
protected:
	Abstraction();
private:
};

class RefinedAbstraction : public Abstraction
{
public:
	RefinedAbstraction(AbstractionImp* imp);
	~RefinedAbstraction();
	void Operation();
protected:
private:
	AbstractionImp* _imp;
};

int test_Bridge1(); // 客户端
int test_Bridge2();

#endif // FBC_MESSY_TEST_BRIDGE_HPP_

