#ifndef FBC_MESSY_TEST_BUILDER_HPP_
#define FBC_MESSY_TEST_BUILDER_HPP_

#include <vector>
#include <string>
#include <iostream>

//最终的产品类
class Product
{
private:
	std::vector<std::string> m_product;
public:
	void Add(std::string strtemp)
	{
		m_product.push_back(strtemp);
	}

	void Show()
	{
		std::vector<std::string>::iterator p = m_product.begin();

		while (p != m_product.end()) {
			std::cout << *p << std::endl;
			p++;
		}
	}
};

//建造者基类
class Builder
{
public:
	virtual void BuilderA() = 0;
	virtual void BuilderB() = 0;
	virtual Product* GetResult() = 0;
};

//第一种建造方式
class ConCreteBuilder1 : public Builder
{
private:
	Product* m_product;
public:
	ConCreteBuilder1()
	{
		m_product = new Product();
	}

	virtual void BuilderA()
	{
		m_product->Add("one");
	}

	virtual void BuilderB()
	{
		m_product->Add("two");
	}

	virtual Product* GetResult()
	{
		return m_product;
	}
};

//第二种建造方式
class ConcreteBuilder2 : public Builder
{
private:
	Product* m_product;
public:
	ConcreteBuilder2()
	{
		m_product = new Product();
	}

	virtual void BuilderA()
	{
		m_product->Add("A");
	}

	virtual void BuilderB()
	{
		m_product->Add("B");
	}

	virtual Product* GetResult()
	{
		return m_product;
	}
};

//指挥者类
class Direct
{
public:
	void Construct(Builder* temp)
	{
		temp->BuilderA();
		temp->BuilderB();
	}
};

// =============================================
class Person
{
public:
	virtual void CreateHead() = 0;
	virtual void CreateHand() = 0;
	virtual void CreateBody() = 0;
	virtual void CreateFoot() = 0;
};

class ThinPerson : public Person
{
public:
	virtual void CreateHead()
	{
		std::cout << "thin head" << std::endl;
	}

	virtual void CreateHand()
	{
		std::cout << "thin hand" << std::endl;
	}

	virtual void CreateBody()
	{
		std::cout << "thin body" << std::endl;
	}

	virtual void CreateFoot()
	{
		std::cout << "thin foot" << std::endl;
	}
};

class ThickPerson : public Person
{
public:
	virtual void CreateHead()
	{
		std::cout << "ThickPerson head" << std::endl;
	}

	virtual void CreateHand()
	{
		std::cout << "ThickPerson hand" << std::endl;
	}

	virtual void CreateBody()
	{
		std::cout << "ThickPerson body" << std::endl;
	}

	virtual void CreateFoot()
	{
		std::cout << "ThickPerson foot" << std::endl;
	}
};

//指挥者类
class Direct_
{
private:
	Person* p;
public:
	Direct_(Person* temp) { p = temp; }
	void Create()
	{
		p->CreateHead();
		p->CreateHand();
		p->CreateBody();
		p->CreateFoot();
	}
};

// ==============================================
class Product_1;

class Builder_1
{
public:
	virtual ~Builder_1();
	virtual void BuildPartA(const std::string& buildPara) = 0;
	virtual void BuildPartB(const std::string& buildPara) = 0;
	virtual void BuildPartC(const std::string& buildPara) = 0;
	virtual Product* GetProduct() = 0;
protected:
	Builder_1();
private:
};

class ConcreteBuilder : public Builder_1
{
public:
	ConcreteBuilder();
	~ConcreteBuilder();

	void BuildPartA(const std::string& buildPara);
	void BuildPartB(const std::string& buildPara);
	void BuildPartC(const std::string& buildPara);

	Product* GetProduct();
protected:
private:
};


int test_Builder1(); // 客户端
int test_Builder2(); // 客户端代码
int test_Builder3();


#endif // FBC_MESSY_TEST_BUILDER_HPP_
