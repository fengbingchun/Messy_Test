#include "FactoryMethod.hpp"
#include "factory.hpp"
#include "product_2.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/21876069

int test_FactoryMethod1()
{
	LeiFangFactory* sf = new LeiFangFactory();
	LeiFeng *s = sf->CreateLeiFeng();
	s->Sweep();

	delete s;
	delete sf;

	/*result:
	À×·æÉ¨µØ
	*/

	return 0;
}

int test_FactoryMethod2()
{
	Factory* fac = new ConcreteFactory();
	Product_2* p = fac->CreateProduct();

	/*result:
		ConcreteFactory ...
		ConcreteProduct ...
	*/

	return 0;
}
