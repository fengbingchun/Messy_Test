#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

class Builder_1;

class Director
{
public:
	Director(Builder_1* bld);
	~Director();
	
	void Construct();

protected:
private:
	Builder_1* _bld;
};

#endif//~_DIRECTOR_H_