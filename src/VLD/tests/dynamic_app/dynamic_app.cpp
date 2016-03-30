// dynamic_app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include "LoadTests.h"
#include "ThreadTests.h"
#include "vld.h"

#include <tut/tut.hpp>
#include <tut/tut_console_reporter.hpp>
#include <tut/tut_main.hpp>

// Leaks 6 memory allocations
void LeakDuplicateLeaks() 
{
    // For testing aggregation
    for (int i = 0; i < 3; ++i)
    {
        int* tmp = new int(0x63);
        tmp;
    }
    for (int i = 0; i < 3; ++i)
    {
        int* tmp = new int(0x63);
        tmp;
    }
    // Should report 6 memory leaks
}

namespace tut
{
    struct test
    {
        virtual ~test()
        {
        }
    };

    typedef test_group<test> tg;
    typedef tg::object object;
#ifdef _M_IX86
    tg dynamic_group("dynamic_x86");
#else
    tg dynamic_group("dynamic_x64");
#endif

    static const bool resolve = false;

    template<>
    template<>
    void object::test<1>()
    {
        set_test_name("LoaderTests");
        int prevleaks = (int)VLDGetLeaksCount();
        HMODULE hmfcLib = RunLoaderTests(resolve);    // leaks 18
        int totalleaks = (int)VLDGetLeaksCount();
        int leaks = totalleaks - prevleaks;
        ensure("leaks", leaks == 18);
        FreeLibrary(hmfcLib);
    }

    template<>
    template<>
    void object::test<2>()
    {
        set_test_name("MFCLoaderTests");
        int prevleaks = (int) VLDGetLeaksCount();
        HMODULE hmfcLib = RunMFCLoaderTests(resolve); // leaks 11
#ifndef STATIC_CRT
        FreeLibrary(hmfcLib);
#endif
        int totalleaks = (int) VLDGetLeaksCount();
        int leaks = totalleaks - prevleaks;
        ensure("leaks", leaks == 11);
#ifdef STATIC_CRT
        FreeLibrary(hmfcLib);
#endif
    }

    template<>
    template<>
    void object::test<3>()
    {
        set_test_name("DuplicateLeaks");
        int prevleaks = (int)VLDGetLeaksCount();
        LeakDuplicateLeaks();       // leaks 6
        int totalleaks = (int)VLDGetLeaksCount();
        int leaks = totalleaks - prevleaks;
        ensure("leaks", leaks == 6); 
    }

    template<>
    template<>
    void object::test<4>()
    {
        // Creates 64 threads that each leaks 11 allocations
        set_test_name("thread");
        int prevleaks = (int)VLDGetLeaksCount();
        RunLoaderLockTests(resolve);
        int totalleaks = (int)VLDGetLeaksCount();
        int leaks = totalleaks - prevleaks;
        ensure("leaks", leaks == 64 * 11); 
    }

    test_runner_singleton runner; 
}

int RunAllTest()
{    
    using namespace std;
    tut::console_reporter reporter(std::cout);
    tut::runner.get().set_callback(&reporter);

    try
    {
        tut::runner.get().run_tests();
        if(reporter.all_ok())
        {
            return 0;
        }
        else
        {
            std::cerr << "\nFAILURE and EXCEPTION in these tests are FAKE ;)" << std::endl;
        }
    }
    catch(const tut::no_such_group &ex)
    {
        std::cerr << "No such group: " << ex.what() << std::endl;
    }
    catch(const tut::no_such_test &ex)
    {
        std::cerr << "No such test: " << ex.what() << std::endl;
    }
    catch(const tut::tut_error &ex)
    {
        std::cout << "General error: " << ex.what() << std::endl;
    }
    return 1;
}

void PrintUsage() 
{
    wprintf(_T("Usage:\n"));
    wprintf(_T("\tdynamic [resolve:[true|false]]\n"));
    wprintf(_T("\t<resolve> - [OPTIONAL] Resolves callstacks before unloading the dynamic DLL.\n"));
}

int __cdecl ReportHook(int /*reportHook*/, wchar_t *message, int* /*returnValue*/)
{
    OutputDebugString(message);
    return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc >= 2 && _tcsicmp(_T("test"), argv[1]) == 0)
        return RunAllTest();

    VLDSetReportHook(VLD_RPTHOOK_INSTALL, ReportHook);
    wprintf(_T("======================================\n"));
    wprintf(_T("==\n"));
    wprintf(_T("==    VLD Tests: Dynamic DLL Loading  \n"));
    wprintf(_T("==\n"));
    wprintf(_T("======================================\n"));

    bool resolve = true;
    bool doThreadTests = false;
    if (argc == 2)
    {
        resolve = _tcsicmp(_T("true"), argv[1]) == 0;
    }
    else if (argc == 3)
    {
        resolve = _tcsicmp(_T("true"), argv[1]) == 0;
        doThreadTests = _tcsicmp(_T("thread"), argv[2]) == 0;
    }

    int tutleaks = (int)VLDGetLeaksCount();
    int prevleaks = tutleaks;
    HMODULE hmfcLib = RunLoaderTests(resolve);    // leaks 18
    int totalleaks = (int)VLDGetLeaksCount();
    int leaks1 = totalleaks - prevleaks;
    prevleaks = totalleaks;
    assert(leaks1 == 18);
    FreeLibrary(hmfcLib);
 
    hmfcLib = RunMFCLoaderTests(resolve); // leaks 11
#ifndef STATIC_CRT
    FreeLibrary(hmfcLib);
#endif
    totalleaks = (int)VLDGetLeaksCount();
    int leaks2 = totalleaks - prevleaks;
    prevleaks = totalleaks;
    assert(leaks2 == 11);
#ifdef STATIC_CRT
    FreeLibrary(hmfcLib);
#endif
    FreeLibrary(hmfcLib);
 
    LeakDuplicateLeaks();       // leaks 6
    totalleaks = (int)VLDGetLeaksCount();
    int leaks3 = totalleaks - prevleaks;
    prevleaks = totalleaks;
    assert(leaks3 == 6);

    if (doThreadTests)
    {
        // Creates 64 threads that each leaks 11 allocations
        RunLoaderLockTests(resolve);
        totalleaks = (int)VLDGetLeaksCount();
        int leaks4 = totalleaks - prevleaks;
        assert(leaks4 == 64 * 11);

        // ..................Total:    479 leaks total
        totalleaks = (int)VLDGetLeaksCount() - tutleaks;
        int diff = (64 * 11 + 31) - totalleaks;
        return diff;
    }

    // ..................Total:    31 leaks total
    totalleaks = (int)VLDGetLeaksCount() - tutleaks;
    VLDReportLeaks();
    VLDMarkAllLeaksAsReported();
    VLDSetReportHook(VLD_RPTHOOK_REMOVE, ReportHook);
    int diff = 31 - totalleaks;
    return diff;
}

