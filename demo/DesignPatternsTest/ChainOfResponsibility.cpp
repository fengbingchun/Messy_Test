#include "ChainOfResponsibility.hpp"
#include "Handle.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/37111697

int test_ChainOfResponsibility1()
{
	Manager* common = new CommonManager("张经理");
	Manager* major = new MajorDomo("李总监");

	common->SetSuccessor(major);

	Request* req = new Request();
	req->m_nNumber = 33;
	common->GetRequest(req);

	req->m_nNumber = 3;
	common->GetRequest(req);

	/*result
		李总监处理了33个请求
		张经理处理了3个请求
	*/

	return 0;
}

int test_ChainOfResponsibility2()
{
	Handle* h1 = new ConcreteHandleA();
	Handle* h2 = new ConcreteHandleB();

	h1->SetSuccessor(h2);
	h1->HandleRequest();

	/*result
		ConcreteHandleA 我把处理权给后继节点 ...
		ConcreteHandleB 没有后继了，我必须自己处理 ...
	*/

	return 0;
}
