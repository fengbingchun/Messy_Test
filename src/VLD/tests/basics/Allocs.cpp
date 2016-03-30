#include "stdafx.h"
#include "Allocs.h"

#include <new> // for placement new
#include <crtdbg.h>
#include <ObjBase.h>

void AllocF(LeakOption type, bool bFree)
{
    int* leaked_memory = NULL;
    int* leaked_memory_dbg = NULL;
    if (type == eMalloc)
    {
        leaked_memory     = (int*)malloc(78);
        leaked_memory_dbg = (int*)_malloc_dbg(80, _NORMAL_BLOCK,__FILE__,__LINE__);
        if (bFree)
        {
            free(leaked_memory);
            _free_dbg(leaked_memory_dbg,_NORMAL_BLOCK);
        }
    } 
    else if (type == eNew)
    {
        leaked_memory = new int(4);
        leaked_memory_dbg = new (_NORMAL_BLOCK, __FILE__, __LINE__) int(7);
        if (bFree)
        {
            delete leaked_memory;
            delete leaked_memory_dbg;
        }
    }
    else if (type == eNewArray)
    {
        leaked_memory = new int[3];
        leaked_memory_dbg = new (_NORMAL_BLOCK,__FILE__,__LINE__) int[4];

        // placement new operator
        int temp[3];
        void* place = temp;
        float* placed_mem = new (place) float[3]; // doesn't work. Nothing gets patched by vld
        if (bFree)
        {
            delete [] leaked_memory;
            delete [] leaked_memory_dbg;
        }
    }
    else if (type == eCalloc)
    {
        leaked_memory     = (int*)calloc(47,sizeof(int));
        leaked_memory_dbg = (int*)_calloc_dbg(39, sizeof(int), _NORMAL_BLOCK, __FILE__, __LINE__);
        if (bFree)
        {
            free(leaked_memory);
            _free_dbg(leaked_memory_dbg,_NORMAL_BLOCK);
        }
    }
    else if (type == eRealloc)
    {
        int* temp = (int*)malloc(17);
        leaked_memory = (int*)realloc(temp, 23);
        leaked_memory = (int*)_recalloc(leaked_memory, 1, 31);
        int* temp_dbg = (int*)malloc(9);
        leaked_memory_dbg = (int*)_realloc_dbg(temp_dbg, 21, _NORMAL_BLOCK, __FILE__, __LINE__);
        if (bFree)
        {
            free(leaked_memory);
            _free_dbg(leaked_memory_dbg,_NORMAL_BLOCK);
        }
    }
    else if (type == eCoTaskMem)
    {
        void* leaked = CoTaskMemAlloc(7);
        if (bFree)
        {
            CoTaskMemFree(leaked);
        }
        void* leaked2 = CoTaskMemAlloc(7);
        void* realloced = CoTaskMemRealloc(leaked2, 29);
        if (bFree)
        {
            CoTaskMemFree(realloced);
        }
    }
    else if (type == eAlignedMalloc)
    {
        void* leaked = _aligned_offset_malloc(64, 16, 1);
        leaked_memory = (int*)_aligned_malloc(64, 16);
        leaked_memory_dbg = (int*)_aligned_malloc_dbg(32, 16, __FILE__, __LINE__);
        if (bFree)
        {
            _aligned_free(leaked);
            _aligned_free(leaked_memory);
            _aligned_free_dbg(leaked_memory_dbg);
        }
    } 
    else if (type == eAlignedRealloc)
    {
        void* leaked = _aligned_offset_malloc(64, 16, 1);
        leaked_memory = (int*)_aligned_malloc(64, 16);
        leaked_memory_dbg = (int*)_aligned_malloc_dbg(32, 16, __FILE__, __LINE__);
        leaked = (int*)_aligned_offset_realloc(leaked, 48, 16, 2);
        leaked_memory = (int*)_aligned_realloc(leaked_memory, 128, 16);
        leaked_memory_dbg = (int*)_aligned_realloc_dbg(leaked_memory_dbg, 48, 16, __FILE__, __LINE__);
        leaked = (int*)_aligned_offset_recalloc(leaked, 1, 52, 16, 2);
        leaked_memory = (int*)_aligned_recalloc(leaked_memory, 1, 132, 16);
        leaked_memory_dbg = (int*)_aligned_recalloc_dbg(leaked_memory_dbg, 1, 64, 16, __FILE__, __LINE__);
        if (bFree)
        {
            _aligned_free(leaked);
            _aligned_free(leaked_memory);
            _aligned_free_dbg(leaked_memory_dbg);
        }
    }
    else if (type == eStrdup)
    {
        leaked_memory     = (int*)strdup("strdup() leaks!");
        leaked_memory_dbg = (int*)_strdup_dbg("_strdup_dbg() leaks!", _NORMAL_BLOCK,__FILE__,__LINE__);
        void* leaked_wmemory = (int*)wcsdup(L"wcsdup() leaks!");
        void* leaked_wmemory_dbg = (int*)_wcsdup_dbg(L"_wcsdup_dbg() leaks!", _NORMAL_BLOCK,__FILE__,__LINE__);
        if (bFree)
        {
            free(leaked_memory);
            _free_dbg(leaked_memory_dbg,_NORMAL_BLOCK);
            free(leaked_wmemory);
            _free_dbg(leaked_wmemory_dbg,_NORMAL_BLOCK);
        }
    }

}

void AllocE(LeakOption type, bool bFree)
{
    AllocF(type, bFree);
}

void AllocD(LeakOption type, bool bFree)
{
    AllocE(type, bFree);
}

void AllocC(LeakOption type, bool bFree)
{
    AllocD(type, bFree);
}

void AllocB(LeakOption type, bool bFree)
{
    AllocC(type, bFree);
}

void AllocA(LeakOption type, bool bFree)
{
    AllocB(type, bFree);
}

void Alloc(LeakOption type, bool bFree)
{
    AllocA(type, bFree);
}