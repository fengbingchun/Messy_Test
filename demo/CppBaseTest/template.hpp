#ifndef FBC_MESSY_TEST_TEMPLATE_HPP_
#define FBC_MESSY_TEST_TEMPLATE_HPP_

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

void test_template1();

#endif // FBC_MESSY_TEST_TEMPLATE_HPP_
