#include "Invoker.hpp"
#include "Command.hpp"
#include <iostream>

Invoker::Invoker(Command_1* cmd)
{
	_cmd = cmd;
}

Invoker::~Invoker()
{
	delete _cmd;
}

void Invoker::Invoke()
{
	_cmd->Excute();
}