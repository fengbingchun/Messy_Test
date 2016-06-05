#include <iostream>
#include "AbstractFactory.hpp"
#include "Adapter.hpp"
#include "Bridge.hpp"
#include "Builder.hpp"
#include "ChainOfResponsibility.hpp"
#include "Command.hpp"
#include "Composite.hpp"
#include "Decorator.hpp"
#include "Facade.hpp"
#include "FactoryMethod.hpp"
#include "Flyweight.hpp"
#include "Interpreter.hpp"
#include "Iterator.hpp"
#include "Mediator.hpp"
#include "Memento.hpp"
#include "Observer.hpp"
#include "Prototype.hpp"
#include "Proxy.hpp"
#include "SimplyFactory.hpp"
#include "Singleton.hpp"
#include "State.hpp"
#include "Strategy.hpp"
#include "TemplateMethod.hpp"
#include "Visitor.hpp"

int main()
{
	test_Visitor2();

	std::cout << "ok" << std::endl;
	return 0;
}