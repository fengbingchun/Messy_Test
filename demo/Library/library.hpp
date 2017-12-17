#ifndef FBC_LIBRARY_LIBRARY_HPP_
#define FBC_LIBRARY_LIBRARY_HPP_

// reference: http://geoffair.net/ms/declspec.htm

#ifdef _MSC_VER
	#ifdef FBC_STATIC
		#define FBC_API
	#elif defined FBC_EXPORT
		#define FBC_API __declspec(dllexport)
	#else
		#define FBC_API __declspec(dllimport)
	#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

FBC_API int library_add(int a, int b);
FBC_API int value;

#ifdef __cplusplus
}
#endif

template<typename T>
class FBC_API Simple {
public:
	Simple() = default;
	void Init(T a, T b);
	T Add() const;

private:
	T a, b;
};


#endif // FBC_LIBRARY_LIBRARY_HPP_
