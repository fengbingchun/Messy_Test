#include "director.hpp"
#include "Builder.hpp"

Director::Director(Builder_1* bld)
{
	_bld = bld;
}

Director::~Director()
{

}

void Director::Construct()
{
	_bld->BuildPartA("user-defined");
	_bld->BuildPartB("user-defined");
	_bld->BuildPartC("user-defined");
}