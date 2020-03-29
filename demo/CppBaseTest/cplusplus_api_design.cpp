#include "cplusplus_api_design.hpp"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

// Blog: https://blog.csdn.net/fengbingchun/article/details/105178753

// reference: 《C++ API设计》

namespace cplusplus_api_design_ {

///////////////////////////////////////////////////////////
class AutoTimer::Impl {
public:
	double GetElapsed() const
	{
#ifdef _WIN32
		return (GetTickCount() - start_time_) / 1e3;
#else
		struct timeval end_time;
		gettimeofday(&end_time, nullptr);
		double t1 = start_time_.tv_usec / 1e6 + start_time_.tv_sec;
		double t2 = end_time.tv_usec / 1e6 + end_time.tv_sec;
		return t2 - t1;
#endif
	}

	std::string name_;
#ifdef _WIN32
	DWORD start_time_;
#else
	struct timeval start_time_;
#endif
};

AutoTimer::AutoTimer(const std::string& name) : impl_(std::make_unique<Impl>())
{
	impl_->name_ = name;
#ifdef _WIN32
	impl_->start_time_ = GetTickCount();
#else
	gettimeofday(&impl_->start_time_, nullptr);
#endif
}

AutoTimer::~AutoTimer()
{
	fprintf(stdout, "%s : took %f secs\n", impl_->name_.c_str(), impl_->GetElapsed());
}

int test_api_design_3_pimpl()
{
	AutoTimer auto_timer("Take");

	return 0;
}

int test_api_design_3_singleton()
{
	Singleton& singleton1 = Singleton::GetInstance();
	Singleton& singleton2 = Singleton::GetInstance();

	return 0;
}

int Monostate::answer_ = 42;
int test_api_design_3_monostate()
{
	Monostate m1, m2;
	fprintf(stdout, "answer1: %d, answer2: %d\n", m1.GetTheAnswer(), m2.GetTheAnswer());

	return 0;
}

class OpenGLRenderer : public IRenderer {
public:
	OpenGLRenderer() { fprintf(stdout, "constructor OpenGLRenderer\n"); }
	void Render() override { fprintf(stdout, "OpenGLRenderer::Render\n"); }
	~OpenGLRenderer() { fprintf(stdout, "destructor OpenGLRenderer\n"); }
};

class DirectXRenderer : public IRenderer {
public:
	DirectXRenderer() { fprintf(stdout, "constructor DirectXRenderer\n"); }
	void Render() override { fprintf(stdout, "DirectXRenderer::Render\n"); }
	~DirectXRenderer() { fprintf(stdout, "destructor DirectXRenderer\n"); }
};

IRenderer* RendererFactory::CreateRenderer(const std::string& type)
{
	if (type == "opengl")
		return new OpenGLRenderer();
	if (type == "directx")
		return new DirectXRenderer();

	return nullptr;
}

int test_api_design_3_factory()
{
	RendererFactory factory;

	IRenderer* renderer1 = factory.CreateRenderer("opengl");
	IRenderer* renderer2 = factory.CreateRenderer("directx");

	if (renderer1) {
		renderer1->Render();
		delete renderer1;
	}

	if (renderer2) {
		renderer2->Render();
		delete renderer2;
	}

	return 0;
}

RendererFactory2::callback_map_ RendererFactory2::renderers_;

void RendererFactory2::RegisterRenderer(const std::string& type, CreateCallback cb)
{
	renderers_[type] = cb;
}

void RendererFactory2::UnRegisterRenderer(const std::string& type)
{
	renderers_.erase(type);
}

IRenderer* RendererFactory2::CreateRenderer(const std::string& type)
{
	callback_map_::iterator it = renderers_.find(type);
	if (it != renderers_.end()) {
		// 调用回调以构造此派生类的对象
		return (it->second)();
	}

	return nullptr;
}

// API用户现在可以在系统中注册(以及注销)新的渲染器
class UserRenderer : public IRenderer {
public:
	UserRenderer() { fprintf(stdout, "constructor UserRenderer\n"); }
	void Render() override { fprintf(stdout, "UserRenderer::Render\n"); }
	~UserRenderer() { fprintf(stdout, "destructor UserRenderer\n"); }
	static IRenderer* Create() { return new UserRenderer(); }
};

int test_api_design_3_factory_expand()
{
	// 注册一个新的渲染器
	RendererFactory2::RegisterRenderer("user", UserRenderer::Create);
	// 为新的渲染器创建一个实例
	IRenderer* r = RendererFactory2::CreateRenderer("user");
	if (r) {
		r->Render();
		delete r;
	}

	return 0;
}

int test_api_design_3_proxy()
{
	Proxy proxy;
	proxy.DoSomething(3);

	return 0;
}

int test_api_design_3_adapter()
{
	RectangleAdapter rect;
	rect.Set(10.f, 5.f, 20.f, 25.f);

	return 0;
}

int test_api_design_3_facade()
{
	Facade facade;
	facade.OperationWrapper();

	return 0;
}

void StockObserver::Update()
{
	fprintf(stdout, "%s: %s, can't play stock\n", name_.c_str(), sub_->action_.c_str());
}

void NBAObserver::Update()
{
	fprintf(stdout, "%s: %s, can't watch NBA\n", name_.c_str(), sub_->action_.c_str());
}

int test_api_design_3_observer()
{
	SubjectBase* subject = new SecretarySubject();

	ObserverBase* observer1 = new NBAObserver("Jack", subject);
	ObserverBase* observer2 = new StockObserver("Tom", subject);

	subject->Attach(observer1);
	subject->Attach(observer2);

	subject->action_ = "boss comes";
	subject->Notify();

	delete subject;
	delete observer1;
	delete observer2;

	return 0;
}


int test_api_design_3()
{
	//return test_api_design_3_pimpl();
	//return test_api_design_3_singleton();
	//return test_api_design_3_monostate();
	//return test_api_design_3_factory();
	//return test_api_design_3_factory_expand();
	//return test_api_design_3_proxy();
	//return test_api_design_3_adapter();
	//return test_api_design_3_facade();
	return test_api_design_3_observer();
}

///////////////////////////////////////////////////////////
int test_api_design_12_vistor()
{
	Visitor* visit = new ConcreteVisitorA();
	Element* element = new ConcreteElementA();
	element->Accept(visit);

	delete visit;
	delete element;

	return 0;
}

int test_api_design_12()
{
	return test_api_design_12_vistor();
}

} // cplusplus_api_design_
