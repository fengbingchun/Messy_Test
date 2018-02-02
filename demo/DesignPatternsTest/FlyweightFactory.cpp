#include "FlyweightFactory.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/29907359

FlyweightFactory::FlyweightFactory()
{

}

FlyweightFactory::~FlyweightFactory()
{

}

Flyweight* FlyweightFactory::GetFlyweight(const std::string& key)
{
	std::vector<Flyweight*>::iterator it = _fly.begin();

	for (; it != _fly.end(); it ++) {
		if ((*it)->GetIntrinsicState() == key) {
			std::cout << "already created by users ..." << std::endl;
			return *it;
		}
	}

	Flyweight* fn = new ConcreteFlyweight(key);
	_fly.push_back(fn);

	return fn;
}