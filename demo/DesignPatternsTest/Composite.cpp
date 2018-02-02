#include "Composite.hpp"
#include "Component.hpp"
#include "Leaf.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/29401213

Composite_1::Composite_1()
{
	//vector<Component*>::iterator itend = comVec.begin();
}

Composite_1::~Composite_1()
{

}

void Composite_1::Operation()
{
	std::vector<Component_1*>::iterator comIter = comVec.begin();

	for (; comIter != comVec.end(); comIter++)
		(*comIter)->Operation();
}

void Composite_1::Add(Component_1* com)
{
	comVec.push_back(com);
}

void Composite_1::Remove(Component_1* com)
{
	//comVec.erase(&com);
}

Component_1* Composite_1::GetChild(int index)
{
	return comVec[index];
}

int test_Composite1()
{
	Composite* p = new Composite("小王");
	p->Add(new Leaf("小李"));
	p->Add(new Leaf("小赵"));

	Composite* p1 = new Composite("小小五");
	p1->Add(new Leaf("大三"));

	p->Add(p1);
	p->Display(1);

	/*result
		-小王
		---小李
		---小赵
		---小小五
		-----大三
	*/

	return 0;
}

int test_Composite2()
{
	ConcreteCompany* p = new ConcreteCompany("清华大学");
	p->Add(new HrDepartment("清华大学人才部"));

	ConcreteCompany* p1 = new ConcreteCompany("数学系");;
	p1->Add(new HrDepartment("数学系人才部"));

	ConcreteCompany* p2 = new ConcreteCompany("物理系");
	p2->Add(new HrDepartment("物理系人才部"));

	p->Add(p1);
	p->Add(p2);

	p->Display(1);
	p->LineOfDuty();

	/*result
		-清华大学
		--清华大学人才部
		--数学系
		---数学系人才部
		--物理系
		---物理系人才部
		清华大学人才部：招聘人才
		数学系人才部：招聘人才
		物理系人才部：招聘人才
	*/

	return 0;
}

int test_Composite3()
{
	Leaf_1* l = new Leaf_1();
	l->Operation();

	Composite_1* com = new Composite_1();
	com->Add(l);
	com->Operation();

	Component_1* ll = com->GetChild(0);
	ll->Operation();

	/*result
		Leaf Operation ...
		Leaf Operation ...
		Leaf Operation ...
	*/

	return 0;
}
