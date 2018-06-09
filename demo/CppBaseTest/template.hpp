#ifndef FBC_MESSY_TEST_TEMPLATE_HPP_
#define FBC_MESSY_TEST_TEMPLATE_HPP_

#include <vector>

// reference: https://zh.wikipedia.org/wiki/%E6%A8%A1%E6%9D%BF_(C%2B%2B)
// 函数模板，此函数在编译时会自动产生对应参数类型的代码，而不用显式声明
template <typename T>
inline const T& maximum(const T& x, const T& y)
{
	if (y > x){
		return y;
	} else{
		return x;
	}
}

// 类模板
template <typename Ty>
class ComPtr
{
protected:
	Ty* m_ptr;
public:
	ComPtr() {
		m_ptr = NULL;
	}
	ComPtr(const ComPtr& rhs) {
		m_ptr = NULL;
		SetComPtr(rhs.m_ptr);
	}
	ComPtr(Ty* p) {
		m_ptr = NULL;
		SetComPtr(p);
	}

	~ComPtr() {
		Release();
	}

	const ComPtr& operator=(const ComPtr& rhs) {
		SetComPtr(rhs.m_ptr);
		return *this;
	}

	Ty* operator=(Ty* p) {
		SetComPtr(p);
		return p;
	}

	operator Ty* () {
		return m_ptr;
	}

	Ty* operator->() {
		return m_ptr;
	}

	operator Ty** () {
		Release();
		return &m_ptr;
	}

	operator void** () {
		Release();
		return (void**)&m_ptr;
	}

	bool IsEmpty() {
		return (m_ptr == NULL);
	}

	void SetComPtr(Ty* p) {
		Release();

		m_ptr = p;
		if (m_ptr) {
			m_ptr->AddRef();
		}
	}

	void Release() {
		if (m_ptr) {
			m_ptr->Release();
			m_ptr = NULL;
		}
	}
};

// 模板的嵌套：成员模板
template <typename C> class myc{
public:
	template <typename S> C foo(S s);
};

//下行需要给出外部类与内部嵌套类的模板形参列表：
template<typename C> template <typename S> C myc<C>::foo(S s){
	C var;
	return var;
}

// reference: http://www.tutorialspoint.com/cplusplus/cpp_templates.htm
// function template
template <typename T>
inline T const& Max(T const& a, T const& b)
{
	return a < b ? b : a;
}

// class template
template <class T>
class Stack {
private:
	std::vector<T> elems; // elements 

public:
	void push(T const&); // push element 
	void pop(); // pop element 
	T top() const; // return top element 
	bool empty() const{ // return true if empty.
		return elems.empty();
	}
};

template <class T>
void Stack<T>::push(T const& elem)
{
	// append copy of passed element 
	elems.push_back(elem);
}

template <class T>
void Stack<T>::pop()
{
	if (elems.empty()) {
		throw fprintf(stderr, "Stack<>::pop(): empty stack\n");
	}
	// remove last element 
	elems.pop_back();
}

template <class T>
T Stack<T>::top() const
{
	if (elems.empty()) {
		throw fprintf(stderr, "Stack<>::top(): empty stack\n");
	}
	// return copy of last element 
	return elems.back();
}

// reference: http://www.prglab.com/cms/pages/c-tutorial/advanced-concepts/templates.php
// 模板特殊化(特例化，Template specialization)
template <class T> class pair {
private:
	T value1, value2;
public:
	pair(T first, T second){
		value1 = first;
		value2 = second;
	}
	T module() { return 0; }
};

template <>
class pair <int> {
private:
	int value1, value2;
public:
	pair(int first, int second){
		value1 = first;
		value2 = second;
	}
	int module() { return value1 % value2; }
};

template <class T> struct PrintType {

};

template<> struct PrintType <int> {
	const std::string type()
	{
		return "int type";
	}
};

template<> struct PrintType <float> {
	const std::string type()
	{
		return "float type";
	}
};

template<> struct PrintType <std::string> {
	const std::string type()
	{
		return "string type";
	}
};

// 函数模板声明与定义分开
template <typename T>
inline const T& max_mum(const T& x, const T& y);

// 类模板声明与定义分开
template<class T>
class A {
public:
	void f();
};

void test_template1();
void test_template2();
void test_template3();
void test_template4();
void test_template5();
void test_template6();
void test_template7();

#endif // FBC_MESSY_TEST_TEMPLATE_HPP_
