#include "memory_locking.hpp"
#include <iostream>
#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#endif

// Blog: https://blog.csdn.net/fengbingchun/article/details/135173999

int test_memory_locking()
{
    constexpr size_t size{ 1024 };
#ifdef _MSC_VER
    // 1. allocate memory
    auto p = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (p == nullptr) {
        std::cerr << "Error: VirtualAlloc: " << GetLastError() << "\n";
        return -1;
    }

    // 2. lock memory page
    if (!VirtualLock(p, size)) {
        std::cerr << "Error: VirtualLock: " << GetLastError() << "\n";
        return -1;
    }

    // 3. use lock memory

    // 4. unlock memory page
    if (!VirtualUnlock(p, size)) {
        std::cerr << "Error: VirtualUnlock: " << GetLastError() << "\n";
        return -1;
    }

    // 5. free memory
    if (!VirtualFree(p, 0, MEM_RELEASE)) {
        std::cerr << "Error: VirtualFree: " << GetLastError() << "\n";
        return -1;
    }
#else
    char data[size];

    // 1. get configuration information at run time
    auto page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size == -1) {
        std::cerr << "Error: sysconf: " << strerror(errno) << "\n";
        return -1;
    }
    std::cout << "page size: " << page_size << "\n";

    // 2. lock memory page
    if (mlock(data, size) == -1) {
        std::cerr << "Error: mlock: " << strerror(errno) << "\n";
        return -1;
    }

    // 3. use lock memory

    // 4. unlock memory page
    if (munlock(data, size) == -1) {
        std::cerr << "Error: munlock: " << strerror(errno) << "\n";
        return -1;
    }
#endif

	return 0;
}
