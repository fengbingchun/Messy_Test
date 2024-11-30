#include "calling_convention.hpp"
#include <iostream>

// Blog: https://blog.csdn.net/fengbingchun/article/details/144161486

namespace {

#ifdef _MSC_VER
#define CDECL __cdecl
#define STDCALL __stdcall
#define FASTCALL __fastcall
#define THISCALL __thiscall
#else
#define CDECL __attribute__((cdecl))
#define STDCALL __attribute__((stdcall))
#define FASTCALL __attribute__((fastcall))
#define THISCALL __attribute__((thiscall))
#endif

int CDECL add_cdecl(int a, int b) { return (a + b); }
int STDCALL add_stdcall(int a, int b) { return (a + b); }
int FASTCALL add_fastcall(int a, int b) { return (a + b); }
class Tmp {
public:
	int THISCALL add_thiscall(int a, int b) { return (a + b); }
};

} // namespace

int test_calling_convention()
{
	auto ret1 = add_cdecl(1, 2);
	auto ret2 = add_stdcall(1, 2);
	auto ret3 = add_fastcall(1, 2);
	Tmp tmp;
	auto ret4 = tmp.add_thiscall(1, 2);
	std::cout << "results: " << ret1 << "," << ret2 << "," << ret3 << "," << ret4 << std::endl;

	return 0;
}

