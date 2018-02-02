#include <iostream>

#include "Iterator.hpp"
#include "Aggregate.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/37314531


Iterator::Iterator()
{

}

Iterator::~Iterator()
{

}

ConcreteIterator::ConcreteIterator(Aggregate* ag, int idx)
{
	this->_ag = ag;
	this->_idx = idx;
}

ConcreteIterator::~ConcreteIterator()
{

}

Object ConcreteIterator::CurrentItem()
{
	return _ag->GetItem(_idx);
}

void ConcreteIterator::First()
{
	_idx = 0;
}

void ConcreteIterator::Next()
{
	if (_idx < _ag->GetSize())
		_idx++;
}

bool ConcreteIterator::IsDone()
{
	return (_idx == _ag->GetSize());
}

int test_Iterator1()
{
	Aggregate* ag = new ConcreteAggregate();
	Iterator* it = new ConcreteIterator(ag);

	for (; !(it->IsDone()); it->Next())
		std::cout << it->CurrentItem() << std::endl;

	/*result
		0
		1
		2
	*/

	return 0;
}
