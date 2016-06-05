#ifndef FBC_MESSY_TEST_STATE_HPP_
#define FBC_MESSY_TEST_STATE_HPP_

#include <iostream>

class Work;
class ForenoonState;
class NoonState;

class State_
{
public:
	virtual void WriteProgram(Work* w) = 0;
};

class Work
{
private:
	State_* current;
public:
	double hour;
public:
	Work();
	void SetState(State_* temp)
	{
		current = temp;
	}

	void Writeprogram()
	{
		current->WriteProgram(this);
	}
};

class NoonState : public State_
{
public:
	virtual void WriteProgram(Work* w)
	{
		std::cout << "execute" << std::endl;

		if ((w->hour) < 13)
			std::cout << "还不错啦" << std::endl;
		else
			std::cout << "不行了，还是睡觉吧" << std::endl;
	}
};

class ForenoonState : public State_
{
public:
	virtual void WriteProgram(Work* w)
	{
		if ((w->hour) < 12)
			std::cout << "现在的精神无敌好" << std::endl;
		else {
			w->SetState(new NoonState());
			w->Writeprogram();//注意加上这句
		}

	}
};


int test_State1();
int test_State2();

#endif // FBC_MESSY_TEST_STATE_HPP_
