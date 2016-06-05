#ifndef FBC_MESSY_TEST_MEMENTO_HPP_
#define FBC_MESSY_TEST_MEMENTO_HPP_

#include <string>
#include <iostream>

class Memo_1;

//发起人类
class Originator_1
{
public:
	std::string state;
	Memo_1* CreateMemo();
	void SetMemo(Memo_1* memo);
	void Show()
	{
		std::cout << "状态" << state << std::endl;
	}
};

//备忘录类
class Memo_1
{
public:
	std::string state;
	Memo_1(std::string strState)
	{
		state = strState;
	}
};

//管理者类
class Caretaker_1
{
public:
	Memo_1* memo;
};

// =================================================
class Memento;

class Originator_2
{
public:
	typedef std::string State;
	Originator_2();
	Originator_2(const State& sdt);
	~Originator_2();
	Memento* CreateMemento();
	void SetMemento(Memento* men);
	void RestoreToMemento(Memento* mt);
	State GetState();
	void SetState(const State& sdt);
	void PrintState();
protected:
private:
	State _sdt;
	Memento* _mt;
};

class Memento
{
public:
protected:
private:
	//这是最关键的地方，将Originator为friend类，可以访问内部信息，但是其他类不能访问
	friend class Originator_2;
	typedef std::string State;
	Memento();
	Memento(const State& sdt);
	~Memento();
	void SetState(const State& sdt);
	State GetState();
private:
	State _sdt;
};

int test_Memento1();
int test_Memento2();

#endif // FBC_MESSY_TEST_MEMENTO_HPP_
