#include "Builder.hpp"
#include "director.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/22593157

Builder_1::Builder_1()
{

}

Builder_1::~Builder_1()
{

}

ConcreteBuilder::ConcreteBuilder()
{

}

ConcreteBuilder::~ConcreteBuilder()
{

}

void ConcreteBuilder::BuildPartA(const std::string& buildPara)
{
	std::cout << "Step1:Build PartA ..." << buildPara << std::endl;
}

void ConcreteBuilder::BuildPartB(const std::string& buildPara)
{
	std::cout << "Step1:Build PartB ..." << buildPara << std::endl;
}

void ConcreteBuilder::BuildPartC(const std::string& buildPara)
{
	std::cout << "Step1:Build PartC ..." << buildPara << std::endl;
}

Product* ConcreteBuilder::GetProduct()
{
	BuildPartA("pre-defined");
	BuildPartB("pre-defined");
	BuildPartC("pre-defined");

	return new Product();
}

int test_Builder1()
{
	Direct* p = new Direct();
	Builder* b1 = new ConCreteBuilder1();
	Builder* b2 = new ConcreteBuilder2();

	p->Construct(b1);//调用第一种方式
	Product* pb1 = b1->GetResult();
	pb1->Show();

	p->Construct(b2);//调用第二种方式
	Product* pb2 = b2->GetResult();
	pb2->Show();

	/* result:
		one
		two
		A
		B
	*/

	return 0;
}

int test_Builder2()
{
	Person* p = new ThickPerson();
	Direct_* d = new Direct_(p);
	d->Create();

	delete d;
	delete p;
	/*result:
		ThickPerson head
		ThickPerson hand
		ThickPerson body
		ThickPerson foot
	*/

	return 0;
}

int test_Builder3()
{
	Director* d = new Director(new ConcreteBuilder());
	d->Construct();

	/*result:
		Step1:Build PartA ...user-defined
		Step1:Build PartB ...user-defined
		Step1:Build PartC ...user-defined
	*/

	return 0;
}
