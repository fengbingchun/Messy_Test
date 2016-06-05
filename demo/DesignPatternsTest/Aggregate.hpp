#ifndef FBC_MESSY_TEST_AGGREGATE_HPP_
#define FBC_MESSY_TEST_AGGREGATE_HPP_

class Iterator;
typedef int Object;
class Interator;

class Aggregate
{
public:
	virtual ~Aggregate();
	virtual Iterator* CreateIterator() = 0;
	virtual Object GetItem(int idx) = 0;
	virtual int GetSize() = 0;
protected:
	Aggregate();
private:
};

class ConcreteAggregate : public Aggregate
{
public:
	enum {SIZE = 3};
	ConcreteAggregate();
	~ConcreteAggregate();
	Iterator* CreateIterator();
	Object GetItem(int idx);
	int GetSize();
protected:
private:
	Object _objs[SIZE];
};


#endif // FBC_MESSY_TEST_AGGREGATE_HPP_
