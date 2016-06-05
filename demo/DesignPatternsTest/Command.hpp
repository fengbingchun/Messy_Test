#ifndef FBC_MESSY_TEST_COMMAND_HPP_
#define FBC_MESSY_TEST_COMMAND_HPP_

#include <iostream>
#include <vector>

//烤肉师傅
class Barbucer
{
public:
	void MakeMutton()
	{
		std::cout << "烤羊肉" << std::endl;
	}

	void MakeChickenWing()
	{
		std::cout << "烤鸡翅膀" << std::endl;
	}
};

//抽象命令类
class Command {
protected:
	Barbucer* receiver;
public:
	Command(Barbucer* temp)
	{
		receiver = temp;
	}

	virtual void ExecuteCmd() = 0;
};

//烤羊肉命令
class BakeMuttonCmd : public Command
{
public:
	BakeMuttonCmd(Barbucer* temp) : Command(temp) {}
	virtual void ExecuteCmd()
	{
		receiver->MakeMutton();
	}
};

//烤鸡翅
class ChickenWingCmd : public Command
{
public:
	ChickenWingCmd(Barbucer* temp) : Command(temp) {}

	virtual void ExecuteCmd()
	{
		receiver->MakeChickenWing();
	}
};

//服务员类
class Waiter
{
protected:
	std::vector<Command*> m_commandList;
public:
	void SetCmd(Command* temp)
	{
		m_commandList.push_back(temp);
		std::cout << "增加定单" << std::endl;
	}

	//通知执行
	void Notify()
	{
		std::vector<Command*>::iterator p = m_commandList.begin();

		while (p != m_commandList.end()) {
			(*p)->ExecuteCmd();
			p++;
		}
	}
};

// =================================================
class Receiver;

class Command_1
{
public:
	virtual ~Command_1();
	virtual void Excute() = 0;
protected:
	Command_1();
private:
};

class ConcreteCommand : public Command_1
{
public:
	ConcreteCommand(Receiver* rev);
	~ConcreteCommand();
	void Excute();
protected:
private:
	Receiver* _rev;
};

int test_Command1();
int test_Command2();

#endif // FBC_MESSY_TEST_COMMAND_HPP_
