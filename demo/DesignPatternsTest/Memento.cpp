#include "Memento.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/35802321

Memo_1* Originator_1::CreateMemo()
{
	return new Memo_1(state);
}

void Originator_1::SetMemo(Memo_1* memo)
{
	state = memo->state;
}

typedef std::string State;

Originator_2::Originator_2()
{
	_sdt = "";
	_mt = 0;
}

Originator_2::Originator_2(const State& sdt)
{
	_sdt = sdt;
	_mt = 0;
}

Originator_2::~Originator_2()
{

}

Memento* Originator_2::CreateMemento()
{
	return new Memento(_sdt);
}

State Originator_2::GetState()
{
	return _sdt;
}

void Originator_2::SetState(const State& sdt)
{
	_sdt = sdt;
}

void Originator_2::PrintState()
{
	std::cout << this->_sdt << "... ..." << std::endl;
}

void Originator_2::SetMemento(Memento* men)
{

}

void Originator_2::RestoreToMemento(Memento* mt)
{
	this->_sdt = mt->GetState();
}

//class Memento
Memento::Memento()
{

}

Memento::Memento(const State& sdt)
{
	_sdt = sdt;
}

State Memento::GetState()
{
	return _sdt;
}

void Memento::SetState(const State& sdt)
{
	_sdt = sdt;
}

int test_Memento1()
{
	Originator_1* on = new Originator_1();
	on->state = "on";
	on->Show();

	Caretaker_1* c = new Caretaker_1();
	c->memo = on->CreateMemo();

	on->state = "off";
	on->Show();

	on->SetMemo(c->memo);
	on->Show();

	/*result
		×´Ì¬on
		×´Ì¬off
		×´Ì¬on
	*/

	return 0;
}

int test_Memento2()
{
	Originator_2* o = new Originator_2();
	o->SetState("old");//±¸ÍüÇ°×´Ì¬
	o->PrintState();

	Memento* m = o->CreateMemento();//½«×´Ì¬±¸Íü
	o->SetState("new");//ÐÞ¸Ä×´Ì¬
	o->PrintState();
	o->RestoreToMemento(m);//»Ö¸´ÐÞ¸ÄÇ°×´Ì¬
	o->PrintState();

	/*result
		old... ...
		new... ...
		old... ...
	*/

	return 0;
}
