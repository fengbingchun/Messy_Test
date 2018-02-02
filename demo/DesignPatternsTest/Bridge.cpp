#include "Bridge.hpp"
#include "abstractionImp.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/24177569

Abstraction::Abstraction()
{

}

Abstraction::~Abstraction()
{

}

RefinedAbstraction::RefinedAbstraction(AbstractionImp* imp)
{
	_imp = imp;
}

RefinedAbstraction::~RefinedAbstraction()
{

}

void RefinedAbstraction::Operation()
{
	_imp->Operation();
}

int test_Bridge1()
{
	HandsetBrand* brand;
	brand = new HandsetBrandM();
	brand->SetHandsetSoft(new HandsetGame());
	brand->Run();
	brand->SetHandsetSoft(new HandSetAddressList());
	brand->Run();
	/* result:
		运行手机游戏
		手机通讯录
	*/

	return 0;
}

int test_Bridge2()
{
	AbstractionImp* imp = new ConcreteAbstractionImpA();
	Abstraction* abs = new RefinedAbstraction(imp);
	abs->Operation();
	/* result:
		ConcreteAbstractionImpA ....
	*/

	return 0;
}
