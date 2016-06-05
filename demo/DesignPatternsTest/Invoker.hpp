#ifndef FBC_MESSY_TEST_INVOKER_HPP_
#define FBC_MESSY_TEST_INVOKER_HPP_

class Command_1;

class Invoker
{
public:
	Invoker(Command_1* cmd);
	~Invoker();
	void Invoke();
protected:
private:
	Command_1* _cmd;
};

#endif // FBC_MESSY_TEST_INVOKER_HPP_
