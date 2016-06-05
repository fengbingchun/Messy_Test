#ifndef FBC_MESSY_TEST_ITERATOR_HPP_
#define FBC_MESSY_TEST_ITERATOR_HPP_

class Aggregate;
typedef int Object;

class Iterator
{
public:
	virtual ~Iterator();
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual Object CurrentItem() = 0;
protected:
	Iterator();
private:
};

class ConcreteIterator : public Iterator
{
public:
	ConcreteIterator(Aggregate* ag, int idx = 0);
	~ConcreteIterator();
	void First();
	void Next();
	bool IsDone();
	Object CurrentItem();
protected:
private:
	Aggregate* _ag;
	int _idx;
};

int test_Iterator1();

#endif // FBC_MESSY_TEST_ITERATOR_HPP_