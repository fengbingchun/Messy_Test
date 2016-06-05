#ifndef FBC_MESSY_TEST_STATE1_HPP_
#define FBC_MESSY_TEST_STATE_HPP_

class Context_3;//Ç°ÖÃÉùÃ÷

class State_3
{
public:
	State_3();
	virtual ~State_3();
	virtual void OperationInterface(Context_3*) = 0;
	virtual void OperationChangeState(Context_3*) = 0;
protected:
	bool ChangeState(Context_3* con, State_3* st);
};

class ConcreteStateA_3 : public State_3
{
public:
	ConcreteStateA_3();
	virtual ~ConcreteStateA_3();
	virtual void OperationInterface(Context_3*);
	virtual void OperationChangeState(Context_3*);
protected:
private:
};

class ConcreteStateB_3 : public State_3
{
public:
	ConcreteStateB_3();
	virtual ~ConcreteStateB_3();
	virtual void OperationInterface(Context_3*);
	virtual void OperationChangeState(Context_3*);
protected:
private:
};

#endif // FBC_MESSY_TEST_STATE_HPP_