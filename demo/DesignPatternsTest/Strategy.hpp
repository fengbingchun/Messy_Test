#ifndef FBC_MESSY_TEST_STRATEGY_HPP_
#define FBC_MESSY_TEST_STRATEGY_HPP_

//策略基类
class COperation_2
{
public:
	int m_nFirst;
	int m_nSecond;
	virtual double GetResult()
	{
		double dResult = 0;
		return dResult;
	}
};

//策略具体类----加法类
class AddOperation : public COperation_2
{
public:
	AddOperation(int a, int b)
	{
		m_nFirst = a;
		m_nSecond = b;
	}

	virtual double GetResult()
	{
		return m_nFirst + m_nSecond;
	}
};

class Context_2
{
private:
	COperation_2* op;
public:
	Context_2(COperation_2* temp)
	{
		op = temp;
	}

	double GetResult()
	{
		return op->GetResult();
	}
};

// ============================================
// 策略与工厂结合：客户端只需访问Context类，而不用知道其它任何类信息，实现了低耦合。
//策略基类
class COperation_3
{
public:
	int m_nFirst;
	int m_nSecond;
	virtual double GetResult()
	{
		double dResult = 0;
		return dResult;
	}
};

//策略具体类----加法类
class AddOperation_3 : public COperation_3
{
public:
	AddOperation_3(int a, int b)
	{
		m_nFirst = a;
		m_nSecond = b;
	}

	virtual double GetResult()
	{
		return m_nFirst + m_nSecond;
	}
};

class Context_3
{
private:
	COperation_3* op;
public:
	Context_3(char cType)
	{
		switch (cType)
		{
		case '+':
			op = new AddOperation_3(5, 8);
			break;
		default:
			break;
		}
	}

	double GetResult()
	{
		return op->GetResult();
	}
};

// =====================================
class Strategy_4
{
public:
	Strategy_4();
	virtual ~Strategy_4();
	virtual void AlgrithmInterface() = 0;
protected:
private:
};

class ConcreteStrategyA_4 : public Strategy_4
{
public:
	ConcreteStrategyA_4();
	virtual ~ConcreteStrategyA_4();
	void AlgrithmInterface();
protected:
private:
};

class ConcreteStrategyB_4 : public Strategy_4
{
public:
	ConcreteStrategyB_4();
	virtual ~ConcreteStrategyB_4();
	void AlgrithmInterface();
protected:
private:
};

int test_Strategy1();
int test_Strategy2();
int test_Strategy3();

#endif // FBC_MESSY_TEST_STRATEGY_HPP_
