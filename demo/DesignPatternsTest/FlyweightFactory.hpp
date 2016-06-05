#ifndef FBC_MESSY_TEST_FLYWEIGHT_FACTORY_HPP_
#define FBC_MESSY_TEST_FLYWEIGHT_FACTORY_HPP_

#include <string>
#include <vector>

#include "Flyweight.hpp"


class FlyweightFactory
{
public:
	FlyweightFactory();
	~FlyweightFactory();
	Flyweight* GetFlyweight(const std::string& key);
protected:
private:
	std::vector<Flyweight*> _fly;
};

#endif // FBC_MESSY_TEST_FLYWEIGHT_FACTORY_HPP_
