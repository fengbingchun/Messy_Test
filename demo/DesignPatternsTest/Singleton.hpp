#ifndef FBC_MESSY_TEST_SINGLETON_HPP_
#define FBC_MESSY_TEST_SINGLETON_HPP_

class Singleton
{
private:
	Singleton() {}
	static Singleton* single;

public:
	static Singleton* GetInstance()
	{
		if (single == NULL) {
			single = new Singleton();
		}

		return single;
	}
};

// ===========================================
class Singleton_1
{
public:
	static Singleton_1* Instance();
protected:
	Singleton_1();//Singleton不可以被实例化，因此将其构造函数声明为protected或者直接声明为private
private:
	static Singleton_1* _instance;
};

int test_Singleton1();
int test_Singleton2();

#endif // FBC_MESSY_TEST_SINGLETON_HPP_
