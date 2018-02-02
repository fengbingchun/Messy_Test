#include "Flyweight.hpp"
#include "FlyweightFactory.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/29907359

Flyweight::Flyweight(std::string intrinsicState)
{
	this->_intrinsicState = intrinsicState;
}

Flyweight::~Flyweight()
{

}

void Flyweight::Operation(const std::string& extrinsicState)
{

}

std::string Flyweight::GetIntrinsicState()
{
	return this->_intrinsicState;
}

ConcreteFlyweight::ConcreteFlyweight(std::string intrinsicState) : Flyweight(intrinsicState)
{
	std::cout << "ConcreteFlyweight Build ..." << intrinsicState << std::endl;
}

ConcreteFlyweight::~ConcreteFlyweight()
{

}

void ConcreteFlyweight::Operation(const std::string& extrinsicState)
{
	std::cout << "ConcreteFlyweight: [" << this->GetIntrinsicState() << "] [" << extrinsicState << "]" << std::endl;
}

int test_Flyweight1()
{
	WebFactory* f = new WebFactory();
	WebSite* ws = f->GetWeb();
	ws->Use();

	WebSite* ws2 = f->GetWeb();
	ws2->Use();

	/*result
		ÍøÕ¾·ÖÀà:²âÊÔ
		ÍøÕ¾·ÖÀà:²âÊÔ
	*/

	return 0;
}

int test_Flyweight2()
{
	FlyweightFactory* fc = new FlyweightFactory();
	Flyweight* fw1 = fc->GetFlyweight("hello");
	Flyweight* fw2 = fc->GetFlyweight("world!");
	Flyweight* fw3 = fc->GetFlyweight("hello");

	/*result
		ConcreteFlyweight Build ...hello
		ConcreteFlyweihgt Build ...world!
		already created by users ...
	*/

	return 0;
}
