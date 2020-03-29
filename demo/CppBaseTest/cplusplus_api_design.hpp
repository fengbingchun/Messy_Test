#ifndef FBC_MESSY_TEST_CPLUSPLUS_API_DESIGN_HPP_
#define FBC_MESSY_TEST_CPLUSPLUS_API_DESIGN_HPP_

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace cplusplus_api_design_ {

///////////////////////////////////////////////////////////
// Pimpl惯用法："自动定时器"，当被销毁时打印出其生存时间
class AutoTimer {
public:
	explicit AutoTimer(const std::string& name);
	~AutoTimer();

	AutoTimer(const AutoTimer&) = delete;
	AutoTimer& operator=(const AutoTimer&) = delete;

private:
	class Impl; // 私有内嵌类
	std::unique_ptr<Impl> impl_;
};

// 单例模式
class Singleton {
public:
	static Singleton& GetInstance() // 既可以返回单例类的指针也可以返回引用,当返回指针时，客户可以删除该对象，因此最好返回引用
	{
		static Singleton instance;
		return instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	Singleton() { fprintf(stdout, "constructor\n"); }
	~Singleton() { fprintf(stdout, "destructor\n"); }
};

// 单一状态设计模式
class Monostate {
public:
	int GetTheAnswer() const { return answer_; }

private:
	static int answer_; // 也可以将该静态变量声明为.cpp文件作用域的静态变量，而不是私有的类静态变量
};

// 工厂模式
class IRenderer {
public:
	virtual ~IRenderer() {}
	virtual void Render() = 0;
};

class RendererFactory {
public:
	IRenderer* CreateRenderer(const std::string& type);
};

// 扩展工厂模式：将派生类与工厂方法解耦并支持在运行时添加新的派生类：工厂类维护一个映射，此映射将类型名与创建对象的回调关联起来。
// 然后就可以允许新的派生类通过一对新的方法调用来实现注册和注销。
// 需要注意的问题是，工厂对象必须保持其状态信息。因此，最好强制要求任一时刻都只能创建一个工厂对象，这也是为何多数工厂对象也是单例的原因
class RendererFactory2 {
public:
	typedef IRenderer* (*CreateCallback)();
	static void RegisterRenderer(const std::string& type, CreateCallback cb);
	static void UnRegisterRenderer(const std::string& type);
	static IRenderer* CreateRenderer(const std::string& type);

private:
	typedef std::map<std::string, CreateCallback> callback_map_;
	static callback_map_ renderers_;
};

// 代理模式：尤其适用于Original类是第三方类库
class IOriginal {
public:
	virtual void DoSomething(int value) = 0;
};

class Original : public IOriginal {
public:
	void DoSomething(int value) override { fprintf(stdout, "Original::DoSomething\n"); }
};

class Proxy : public IOriginal {
public:
	Proxy() : orig_(new Original()) {}
	~Proxy() { delete orig_; }

	void DoSomething(int value) override { return orig_->DoSomething(value); }

	Proxy(const Proxy&) = delete;
	Proxy& operator=(const Proxy&) = delete;

private:
	Original* orig_;
};

// 适配器模式
class Rectangle {
public:
	Rectangle() = default;
	~Rectangle() {}

	void setDimensions(float cx, float cy, float w, float h) { fprintf(stdout, "width: %f, height: %f\n", w, h); }
};

class RectangleAdapter {
public:
	RectangleAdapter() : rect_(new Rectangle()) {}
	~RectangleAdapter() { delete rect_; }

	void Set(float x1, float y1, float x2, float y2)
	{
		float w = x2 - x1;
		float h = y2 - y1;
		float cx = w / 2.f + x1;
		float cy = h / 2.f + y1;
		rect_->setDimensions(cx, cy, w, h);
	}

	RectangleAdapter(const RectangleAdapter&) = delete;
	RectangleAdapter& operator=(const RectangleAdapter&) = delete;

private:
	Rectangle* rect_;
};

// 外观模式
class Subsystem1 {
public:
	Subsystem1() = default;
	~Subsystem1() {}
	void Operation() { fprintf(stdout, "subsystem1 operation\n"); }
};

class Subsystem2 {
public:
	Subsystem2() = default;
	~Subsystem2() {}
	void Operation() { fprintf(stdout, "subsystem2 operation\n"); }
};

class Facade {
public:
	Facade() : subs1_(new Subsystem1()), subs2_(new Subsystem2()) {}
	~Facade()
	{
		delete subs1_;
		delete subs2_;
	}

	void OperationWrapper()
	{
		subs1_->Operation();
		subs2_->Operation();
	}

	Facade(const Facade&) = delete;
	Facade& operator=(const Facade&) = delete;

private:
	Subsystem1* subs1_;
	Subsystem2* subs2_;
};

// 观察者模式
class SubjectBase; // 抽象主题
class ObserverBase { // 抽象观察者
public:
	ObserverBase(std::string name, SubjectBase* sub) : name_(name), sub_(sub) {}
	virtual void Update() = 0;

protected:
	std::string name_;
	SubjectBase* sub_;
};

class StockObserver: public ObserverBase { // 具体观察者，看股票的
public:
	StockObserver(std::string name, SubjectBase* sub) : ObserverBase(name, sub) {}
	void Update() override;
};

class NBAObserver : public ObserverBase { // 具体观察者，看NBA的
public:
	NBAObserver(std::string name, SubjectBase* sub) : ObserverBase(name, sub) {}
	void Update() override;
};

class SubjectBase { // 抽象主题
public:
	virtual void Attach(ObserverBase* observer) = 0;
	virtual void Notify() = 0;

public:
	std::string action_;
	std::vector<ObserverBase*> observers_;
};


class SecretarySubject : public SubjectBase { // 具体主题
public:
	void Attach(ObserverBase* ob) { observers_.push_back(ob); }

	void Notify()
	{
		for (auto it = observers_.cbegin(); it != observers_.cend(); ++it) {
			(*it)->Update();
		}
	}
};

int test_api_design_3();
int test_api_design_3_pimpl();
int test_api_design_3_singleton();
int test_api_design_3_monostate();
int test_api_design_3_factory();
int test_api_design_3_factory_expand();
int test_api_design_3_proxy();
int test_api_design_3_adapter();
int test_api_design_3_facade();
int test_api_design_3_observer();

///////////////////////////////////////////////////////////
class Element;

// 访问者模式: 表示一个作用于某对象结构中的各元素的操作. 它使你可以在不改变各元素的类的前提下定义作用于这些元素的新操作
// 访问者模式使得易于增加新的操作: 访问者使得增加依赖于复杂对象结构的构件的操作变得容易. 仅需增加一个新的访问者即可在一个对象结构上定义一个新的操作
class Visitor {
public:
	virtual ~Visitor() = default;
	virtual void VisitConcreteElementA(Element* element) = 0;
	virtual void VisitConcreteElementB(Element* element) = 0;

protected:
	Visitor() = default;
};

class ConcreteVisitorA : public Visitor {
public:
	ConcreteVisitorA() = default;
	~ConcreteVisitorA() = default;

	void VisitConcreteElementA(Element* element) override
	{
		fprintf(stdout, "I will visit ConcreteElementA ...\n");
	}

	void VisitConcreteElementB(Element* element) override
	{
		fprintf(stdout, "I will visit ConcreteElementB ...\n");
	}
};

class ConcreteVisitorB : public Visitor
{
public:
	ConcreteVisitorB() = default;
	~ConcreteVisitorB() = default;

	void VisitConcreteElementA(Element* element) override
	{
		fprintf(stdout, "I will visit ConcreteElementA ...\n");
	}

	void VisitConcreteElementB(Element* element) override
	{
		fprintf(stdout, "I will visit ConcreteElementB ...\n");
	}
};

class Element {
public:
	virtual ~Element() = default;
	virtual void Accept(Visitor* visit) = 0;

protected:
	Element() = default;
};

class ConcreteElementA : public Element {
public:
	ConcreteElementA() = default;
	~ConcreteElementA() = default;

	void Accept(Visitor* visit) override
	{
		fprintf(stdout, "visiting ConcreteElementA ...\n");
		visit->VisitConcreteElementA(this);
	}
};

class ConcreteElementB : public Element {
public:
	ConcreteElementB() = default;
	~ConcreteElementB() = default;

	void Accept(Visitor* visit) override
	{
		fprintf(stdout, "visiting ConcreteElementB ...\n");
		visit->VisitConcreteElementB(this);
	}
};

int test_api_design_12_vistor();
int test_api_design_12();

} // cplusplus_api_design_

#endif // FBC_MESSY_TEST_CPLUSPLUS_API_DESIGN_HPP_
