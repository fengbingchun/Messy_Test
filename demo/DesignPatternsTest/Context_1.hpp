#ifndef FBC_MESSY_TEST_CONTEXT_HPP_
#define FBC_MESSY_TEST_CONTEXT_HPP_

class State_3;

class Context_3
{
public:
	Context_3();
	Context_3(State_3* state);
	~Context_3();
	void OperationInterface();
	void OperationChangeState();
protected:
private:
	friend class State_3;//表明在State类中可以访问Context类的private字段
	bool ChangeState(State_3* state);
private:
	State_3* _state;
};


#endif // FBC_MESSY_TEST_CONTEXT_HPP_