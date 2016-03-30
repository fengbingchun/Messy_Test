#include "stdafx.h"
#include "LoadTests.h"
// Hook in Visual Leak Detector to this application
#include "../../vld.h"
#include <assert.h>

#ifdef _WIN64
    static const TCHAR* sVld_dll = _T("vld_x64.dll");
#else
    static const TCHAR* sVld_dll = _T("vld_x86.dll");
#endif

void CallVLDExportedMethod(const CHAR* function)
{
    HMODULE vld_module =  GetModuleHandle(sVld_dll);
    assert(vld_module);
    typedef void (*VLDAPI_func)();
    if (vld_module != NULL)
    {
        VLDAPI_func func = (VLDAPI_func)GetProcAddress(vld_module, function);
        assert(func);
        if (func)
        {
            func();
        }
    }
}

void CallDynamicMethods(HMODULE module, const CHAR* function) 
{
    typedef void (__cdecl *DYNAPI_FNC)();
    if (module != NULL)
    {
        DYNAPI_FNC func = (DYNAPI_FNC)GetProcAddress(module, function );
        //GetFormattedMessage(GetLastError());
        assert(func);
        if (func)
        {
            func();
        }
    }
}

HMODULE RunLoaderTests(bool resolve)
{
    HMODULE hdyn = LoadLibrary(_T("dynamic.dll"));
    assert(hdyn);
    if (hdyn)
    {
        VLDEnableModule(hdyn);

        // Should leak 18 memory allocations in total
        // These requires ansi, not Unicode strings
        CallDynamicMethods(hdyn, "SimpleLeak_Malloc");    // leaks 6
        CallDynamicMethods(hdyn, "SimpleLeak_New");       // leaks 6
        CallDynamicMethods(hdyn, "SimpleLeak_New_Array"); // leaks 6

        if (resolve)
        {
            CallVLDExportedMethod("VLDResolveCallstacks"); // This requires ansi, not Unicode strings
        }
    }
    return hdyn;
}

void CallLibraryMethods( HMODULE hmfcLib, LPCSTR function ) 
{
    HMODULE dynamic_module = hmfcLib;
    assert(dynamic_module);
    typedef void (__cdecl *DYNAPI_FNC)();
    if (dynamic_module != NULL)
    {
        DYNAPI_FNC func = (DYNAPI_FNC)GetProcAddress(dynamic_module, function );
        //GetFormattedMessage(GetLastError());
        assert(func);
        if (func)
        {
            func();
        }
    }
}


HMODULE RunMFCLoaderTests(bool resolve)
{
    HMODULE hmfcLib = LoadLibrary(_T("test_mfc.dll"));
    assert(hmfcLib);
    if (hmfcLib)
    {
        VLDEnableModule(hmfcLib);
        // Should leak 7 memory allocations in total
        // This requires ansi, not Unicode strings
        CallLibraryMethods(hmfcLib, "MFC_LeakSimple"); // Leaks 4
        CallLibraryMethods(hmfcLib, "MFC_LeakArray");  // leaks 3

        if (resolve)
        {
            CallVLDExportedMethod("VLDResolveCallstacks"); // This requires ansi, not Unicode strings
        }
    }
    return hmfcLib;
}

