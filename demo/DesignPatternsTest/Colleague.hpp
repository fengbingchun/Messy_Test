#ifndef FBC_MESSY_TEST_COLLEAGUE_HPP_
#define FBC_MESSY_TEST_COLLEAGUE_HPP_

#include <string>

class Mediator_1;

class Colleague_1
{
public:
	virtual ~Colleague_1();
	virtual void Action() = 0;
	virtual void SetState(const std::string& sdt) = 0;
	virtual std::string GetState() = 0;
protected:
	Colleague_1();
	Colleague_1(Mediator_1* mdt);
	Mediator_1* _mdt;
private:
};

class ConcreteColleagueA_1 : public Colleague_1
{
public:
	ConcreteColleagueA_1();
	ConcreteColleagueA_1(Mediator_1* mdt);
	~ConcreteColleagueA_1();
	void Action();
	void SetState(const std::string& std);
	std::string GetState();
protected:
private:
	std::string _sdt;
};

class ConcreteColleagueB_1 : public Colleague_1
{
public:
	ConcreteColleagueB_1();
	ConcreteColleagueB_1(Mediator_1* mdt);
	~ConcreteColleagueB_1();
	void Action();
	void SetState(const std::string& sdt);
	std::string GetState();
protected:
private:
	std::string _sdt;
};

#endif // FBC_MESSY_TEST_COLLEAGUE_HPP_
