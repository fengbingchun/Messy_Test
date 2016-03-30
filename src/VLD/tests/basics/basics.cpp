// basics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vld.h"
#include "Allocs.h"

#include <tut/tut.hpp>
#include <tut/tut_console_reporter.hpp>
#include <tut/tut_main.hpp>

void LeakMemory(LeakOption type, int repeat, bool bFree)
{
    for (int i = 0; i < repeat; i++)
    {
        Alloc(type, bFree);
    }
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
    tg basic_group("basic_x86");
#else
    tg basic_group("basic_x64");
#endif

    static const int repeat = 10;

    template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Malloc");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eMalloc,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 2)); 
    }

    template<>
    template<>
    void object::test<2>()
    {
        set_test_name("New");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eNew,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 2)); 
    }

    template<>
    template<>
    void object::test<3>()
    {
        set_test_name("NewArray");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eNewArray,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 2)); 
    }

    template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Calloc");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eCalloc,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 2)); 
    }

    template<>
    template<>
    void object::test<5>()
    {
        set_test_name("Realloc");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eRealloc,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 2)); 
    }

    template<>
    template<>
    void object::test<6>()
    {
        set_test_name("CoTaskMem");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eCoTaskMem,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 2)); 
    }

    template<>
    template<>
    void object::test<7>()
    {
        set_test_name("AlignedMalloc");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eAlignedMalloc,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 3)); 
    }

    template<>
    template<>
    void object::test<8>()
    {
        set_test_name("AlignedRealloc");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eAlignedRealloc,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 3)); 
    }

    template<>
    template<>
    void object::test<9>()
    {
        set_test_name("Strdup");
        int prev = (int)VLDGetLeaksCount();
        LeakMemory(eStrdup,repeat,false);
        int leaks = (int)VLDGetLeaksCount() - prev;
        ensure("leaks", leaks == (repeat * 4)); 
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
    wprintf(_T("\ttest_basics <type> <repeat>\n"));
    wprintf(_T("\t<type>   - The type of memory allocation to test with. This can be one of the following:\n"));
    wprintf(_T("\t           [malloc,new,new_array,calloc,realloc,CoTaskMem,AlignedMalloc,AlignedRealloc,strdup,all]\n"));
    wprintf(_T("\t<repeat> - The number of times to repeat each unique memory leak.\n\n"));
}

int _tmain(int argc, _TCHAR* argv[])
{   
    if (argc >= 2 && _tcsicmp(_T("test"), argv[1]) == 0)
        return RunAllTest();

    wprintf(_T("======================================\n"));
    wprintf(_T("==\n"));
    wprintf(_T("==    VLD Tests: basics\n"));
    wprintf(_T("==\n"));
    wprintf(_T("======================================\n"));
    bool bFree = false;
    if (argc >= 3)
    {
        bool checkAll = false;
        LeakOption leak_type = eMalloc; // default
        int multiplayer = 2;
        
        // Pick up options to determine which type of memory allocator
        // to test with
        if (_tcsicmp(_T("malloc"), argv[1]) == 0)
        {
            leak_type = eMalloc;
        }
        else if (_tcsicmp(_T("new"), argv[1]) == 0)
        {
            leak_type = eNew;
        }
        else if (_tcsicmp(_T("new_array"), argv[1]) == 0)
        {
            leak_type = eNewArray;
        }
        else if (_tcsicmp(_T("calloc"), argv[1]) == 0)
        {
            leak_type = eCalloc;
        }
        else if (_tcsicmp(_T("realloc"), argv[1]) == 0)
        {
            leak_type = eRealloc;
        }
        else if (_tcsicmp(_T("CoTaskMem"), argv[1]) == 0)
        {
            leak_type = eCoTaskMem;
            multiplayer = 2;
        }
        else if (_tcsicmp(_T("AlignedMalloc"), argv[1]) == 0)
        {
            leak_type = eAlignedMalloc;
            multiplayer = 3;
        }
        else if (_tcsicmp(_T("AlignedRealloc"), argv[1]) == 0)
        {
            leak_type = eAlignedRealloc;
            multiplayer = 3;
        }
        else if (_tcsicmp(_T("strdup"), argv[1]) == 0)
        {
            leak_type = eStrdup;
            multiplayer = 4;
        }
        else if (_tcsicmp(_T("all"), argv[1]) == 0)
        {
            checkAll = true;
            multiplayer = 22;
        }
        else
        {
            wprintf(_T("Error!: Invalid arguments\n"));
            PrintUsage();
            return -1;
        }

        if (argc >= 4 && _tcsicmp(_T("free"), argv[3]) == 0)
            bFree = true;

        wprintf(_T("Options: %s \nNumber of Leaks: %s\n"), argv[1], argv[2]);
        // Convert the string into it's integer equivalent
        int prevleaks = (int)VLDGetLeaksCount();
        int repeat = _tstoi(argv[2]);
        if (!checkAll)
            LeakMemory(leak_type,repeat,bFree);
        else
        {
            for (int leak_type = 0; leak_type < eCount; leak_type++)
                LeakMemory((LeakOption)leak_type,repeat,bFree);
        }
        int leaks = (int)VLDGetLeaksCount() - prevleaks;
        wprintf(_T("End of test app...\n\n"));
        int diff = repeat * multiplayer - leaks;
        return bFree ? leaks : diff;
    } 
    else
    {
        wprintf(_T("Error!: Invalid arguments\n"));
        PrintUsage();
        wprintf(_T("End of test app...\n\n"));
        return -1;
    }
}

