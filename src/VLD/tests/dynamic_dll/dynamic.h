// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DYNAMIC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DYNAMIC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DYNAMIC_EXPORTS
#define DYNAMIC_API __declspec(dllexport)
#else
#define DYNAMIC_API __declspec(dllimport)
#endif

extern "C" {
// This class is exported from the dynamic.dll
class DYNAMIC_API Cdynamic {
public:
	Cdynamic(void);
	// TODO: add your methods here.
};

extern DYNAMIC_API int ndynamic;

// Leaks 2*3=6 allocations
DYNAMIC_API void SimpleLeak_Malloc(void);
// Leaks 2*3=6 allocations
DYNAMIC_API void SimpleLeak_New(void);
// Leaks 2*3=6 allocations
DYNAMIC_API void SimpleLeak_New_Array(void);

}

