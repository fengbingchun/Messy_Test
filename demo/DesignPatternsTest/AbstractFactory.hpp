#ifndef FBC_MESSY_TEST_ABSTRACT_FACTORY_HPP_
#define FBC_MESSY_TEST_ABSTRACT_FACTORY_HPP_

#include <iostream>

// =======================================
//用户抽象接口
class IUser
{
public:
	virtual void GetUser() = 0;
	virtual void InsertUser() = 0;
};

//部门抽象接口
class IDepartment
{
public:
	virtual void GetDepartment() = 0;
	virtual void InsertDepartment() = 0;
};

//ACCESS 用户
class CAccessUser : public IUser
{
public:
	virtual void GetUser()
	{
		std::cout << "Access GetUser" << std::endl;
	}

	virtual void InsertUser()
	{
		std::cout << "Access InsertUser" << std::endl;
	}
};

//ACCESS 部门
class CAccessDepartment : public IDepartment
{
public:
	virtual void GetDepartment()
	{
		std::cout << "Access GetDepartment" << std::endl;
	}

	virtual void InsertDepartment()
	{
		std::cout << "Access InsertDepartment" << std::endl;
	}
};

//SQL 用户
class CSqlUser : public IUser
{
public:
	virtual void GetUser()
	{
		std::cout << "Sql GetUser" << std::endl;
	}

	virtual void InsertUser()
	{
		std::cout << "Sql InsertUser" << std::endl;
	}
};

//SQL 部门
class CSqlDepartment : public IDepartment
{
public:
	virtual void GetDepartment()
	{
		std::cout << "Sql GetDepartment" << std::endl;
	}

	virtual void InsertDepartment()
	{
		std::cout << "Sql InsertDepartment" << std::endl;
	}
};

//抽象工厂
class IFactory
{
public:
	virtual IUser* CreateUser() = 0;
	virtual IDepartment* CreateDepartment() = 0;
};

//ACCESS 工厂
class AccessFactory : public IFactory
{
public:
	virtual IUser* CreateUser()
	{
		return new CAccessUser();
	}

	virtual IDepartment* CreateDepartment()
	{
		return new CAccessDepartment();
	}
};

//SQL 工厂
class SqlFactory : public IFactory
{
public:
	virtual IUser* CreateUser()
	{
		return new CSqlUser();
	}

	virtual IDepartment* CreateDepartment()
	{
		return new CSqlDepartment();
	}
};

// ==================================================
class AbstractProductA;
class AbstractProductB;

class AbstractFactory
{
public:
	virtual ~AbstractFactory();
	virtual AbstractProductA* CreateProductA() = 0;
	virtual AbstractProductB* CreateProductB() = 0;

protected:
	AbstractFactory();

private:
};

class ConcreteFactory1 : public AbstractFactory
{
public:
	ConcreteFactory1();
	~ConcreteFactory1();
	AbstractProductA* CreateProductA();
	AbstractProductB* CreateProductB();

protected:
private:
};

class ConcreteFactory2 : public AbstractFactory
{
public:
	ConcreteFactory2();
	~ConcreteFactory2();
	AbstractProductA* CreateProductA();
	AbstractProductB* CreateProductB();

protected:
private:
};


int test_AbstractFactory1(); // 客户端
int test_AbstractFactory2();

#endif // FBC_MESSY_TEST_ABSTRACT_FACTORY_HPP_
