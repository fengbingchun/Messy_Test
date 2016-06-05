#include <iostream>

#include "Context_2.hpp"
#include "Strategy.hpp"

using namespace std;

Context_4::Context_4(Strategy_4* stg)
{
	_stg = stg;
}

Context_4::~Context_4()
{
	if (!_stg)
		delete _stg;
}

void Context_4::DoAction()
{
	_stg->AlgrithmInterface();
}
