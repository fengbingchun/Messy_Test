#ifndef FBC_MESSY_TEST_SUBJECT_HPP_
#define FBC_MESSY_TEST_SUBJECT_HPP_

#include <list>
#include <string>

typedef std::string State;

class Observer;

class Subject
{
public:
	virtual ~Subject();
	virtual void Attach(Observer* obv);
	virtual void Detach(Observer* obv);
	virtual void Notify();
	virtual void SetState(const State& st) = 0;
	virtual State GetState() = 0;
protected:
	Subject();
private:
	std::list<Observer*>* _obvs;
};

class ConcreteSubject : public Subject
{
public:
	ConcreteSubject();
	~ConcreteSubject();
	State GetState();
	void SetState(const State& st);
protected:
private:
	State _st;
};


#endif // FBC_MESSY_TEST_SUBJECT_HPP_