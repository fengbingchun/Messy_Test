////////////////////////////////////////////////////////////////////////////////
//
//  Visual Leak Detector - CRT and MFC IAT Patch Functions Header
//  Copyright (c) 2005-2014 VLD Team
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  See COPYING.txt for the full terms of the GNU Lesser General Public License.
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef VLDBUILD
#error \
"This header should only be included by Visual Leak Detector when building it from source. \
Applications should never include this header."
#endif

#include "vldint.h"
extern __declspec(dllexport) VisualLeakDetector g_vld;

template<int CRTVersion, bool debug = false>
class CrtMfcPatch
{
public:
    static CrtMfcPatch data;

    static void* __cdecl crtd__calloc_dbg (size_t num, size_t size, int type, char const *file, int line);
    static void* __cdecl crtd__malloc_dbg (size_t size, int type, const char *file, int line);
    static void* __cdecl crtd__realloc_dbg (void *mem, size_t size, int type, char const *file, int line);
    static void* __cdecl crtd__recalloc_dbg (void *mem, size_t num, size_t size, int type, char const *file, int line);
    static void* __cdecl crtd__scalar_new_dbg (size_t size, int type, char const *file, int line);
    static void* __cdecl crtd__vector_new_dbg (size_t size, int type, char const *file, int line);
    static void* __cdecl crtd_calloc (size_t num, size_t size);
    static void* __cdecl crtd_malloc (size_t size);
    static void* __cdecl crtd_realloc (void *mem, size_t size);
    static void* __cdecl crtd__recalloc (void *mem, size_t num, size_t size);

    static char* __cdecl crtd__strdup (const char* src);
    static char* __cdecl crtd__strdup_dbg (const char* src, int type, char const *file, int line);
    static wchar_t* __cdecl crtd__wcsdup (const wchar_t* src);
    static wchar_t* __cdecl crtd__wcsdup_dbg (const wchar_t* src, int type, char const *file, int line);
    
    static void* __cdecl crtd_scalar_new (size_t size);
    static void* __cdecl crtd_vector_new (size_t size);

    static void* __cdecl crtd__aligned_malloc_dbg (size_t size, size_t alignment, int type, const char *file, int line);
    static void* __cdecl crtd__aligned_offset_malloc_dbg (size_t size, size_t alignment, size_t offset, int type, const char *file, int line);
    static void* __cdecl crtd__aligned_realloc_dbg (void *mem, size_t size, size_t alignment, int type, char const *file, int line);
    static void* __cdecl crtd__aligned_offset_realloc_dbg (void *mem, size_t size, size_t alignment, size_t offset, int type, char const *file, int line);
    static void* __cdecl crtd__aligned_recalloc_dbg (void *mem, size_t num, size_t size, size_t alignment, int type, char const *file, int line);
    static void* __cdecl crtd__aligned_offset_recalloc_dbg (void *mem, size_t num, size_t size, size_t alignment, size_t offset, int type, char const *file, int line);
    static void* __cdecl crtd__aligned_malloc (size_t size, size_t alignment);
    static void* __cdecl crtd__aligned_offset_malloc (size_t size, size_t alignment, size_t offset);
    static void* __cdecl crtd__aligned_realloc (void *memblock, size_t size, size_t alignment);
    static void* __cdecl crtd__aligned_offset_realloc (void *memblock, size_t size, size_t alignment, size_t offset);
    static void* __cdecl crtd__aligned_recalloc (void *memblock, size_t num, size_t size, size_t alignment);
    static void* __cdecl crtd__aligned_offset_recalloc (void *memblock, size_t num, size_t size, size_t alignment, size_t offset);
    
    static void* __cdecl mfcd_vector_new (size_t size);
    static void* __cdecl mfcd__vector_new_dbg_4p (size_t size, int type, char const *file, int line);
    static void* __cdecl mfcd__vector_new_dbg_3p (size_t size, char const *file, int line);
    static void* __cdecl mfcd_scalar_new (size_t size);
    static void* __cdecl mfcd__scalar_new_dbg_4p (size_t size, int type, char const *file, int line);
    static void* __cdecl mfcd__scalar_new_dbg_3p (size_t size, char const *file, int line);
    static void* __cdecl mfcud_vector_new (size_t size);
    static void* __cdecl mfcud__vector_new_dbg_4p (size_t size, int type, char const *file, int line);
    static void* __cdecl mfcud__vector_new_dbg_3p (size_t size, char const *file, int line);
    static void* __cdecl mfcud_scalar_new (size_t size);
    static void* __cdecl mfcud__scalar_new_dbg_4p (size_t size, int type, char const *file, int line);
    static void* __cdecl mfcud__scalar_new_dbg_3p (size_t size, char const *file, int line);

    union
    {
        void* function[40];
        struct  
        {
            void* pcrtd__calloc_dbg;
            void* pcrtd__malloc_dbg;
            void* pcrtd__realloc_dbg;
            void* pcrtd__recalloc_dbg;
            void* pcrtd__strdup_dbg;
            void* pcrtd__wcsdup_dbg;
            void* pcrtd_calloc;
            void* pcrtd_malloc;
            void* pcrtd_realloc;
            void* pcrtd_recalloc;
            void* pcrtd__strdup;
            void* pcrtd__wcsdup;
            void* pcrtd__aligned_malloc_dbg;
            void* pcrtd__aligned_offset_malloc_dbg;
            void* pcrtd__aligned_realloc_dbg;
            void* pcrtd__aligned_offset_realloc_dbg;
            void* pcrtd__aligned_recalloc_dbg;
            void* pcrtd__aligned_offset_recalloc_dbg;
            void* pcrtd_aligned_malloc;
            void* pcrtd_aligned_offset_malloc;
            void* pcrtd_aligned_realloc;
            void* pcrtd_aligned_offset_realloc;
            void* pcrtd_aligned_recalloc;
            void* pcrtd_aligned_offset_recalloc;
            void* pcrtd__scalar_new_dbg;
            void* pcrtd__vector_new_dbg;
            void* pcrtd_scalar_new;
            void* pcrtd_vector_new;

            void* pmfcd_scalar_new;
            void* pmfcd_vector_new;
            void* pmfcd__scalar_new_dbg_4p;
            void* pmfcd__vector_new_dbg_4p;
            void* pmfcd__scalar_new_dbg_3p;
            void* pmfcd__vector_new_dbg_3p;

            void* pmfcud_scalar_new;
            void* pmfcud_vector_new;
            void* pmfcud__scalar_new_dbg_4p;
            void* pmfcud__vector_new_dbg_4p;
            void* pmfcud__scalar_new_dbg_3p;
            void* pmfcud__vector_new_dbg_3p;
        };
    };
};

////////////////////////////////////////////////////////////////////////////////
//
// Visual Studio DLLs
//
////////////////////////////////////////////////////////////////////////////////

// crtd__calloc_dbg - Calls to _calloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - mem (IN): Pointer to the memory block to be reallocated.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The CRT "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _calloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__calloc_dbg (size_t      num,
                                                    size_t      size,
                                                    int         type,
                                                    char const *file,
                                                    int         line)
{
    _calloc_dbg_t pcrtxxd__calloc_dbg = (_calloc_dbg_t)data.pcrtd__calloc_dbg;
    assert(pcrtxxd__calloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__calloc_dbg);

    return g_vld.__calloc_dbg(pcrtxxd__calloc_dbg, context, debug, num, size, type, file, line);
}

// crtd__malloc_dbg - Calls to _malloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The CRT "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _malloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__malloc_dbg (size_t      size,
                                                    int         type,
                                                    char const *file,
                                                    int         line)
{
    _malloc_dbg_t pcrtxxd__malloc_dbg = (_malloc_dbg_t)data.pcrtd__malloc_dbg;
    assert(pcrtxxd__malloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__malloc_dbg);

    return g_vld.__malloc_dbg(pcrtxxd__malloc_dbg, context, debug, size, type, file, line);
}

// crtd__realloc_dbg - Calls to _realloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - mem (IN): Pointer to the memory block to be reallocated.
//
//  - size (IN): The size of the memory block to reallocate.
//
//  - type (IN): The CRT "use type" of the block to be reallocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _realloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__realloc_dbg (void       *mem,
    size_t     size,
    int        type,
    char const *file,
    int        line)
{
    _realloc_dbg_t pcrtxxd__realloc_dbg = (_realloc_dbg_t)data.pcrtd__realloc_dbg;
    assert(pcrtxxd__realloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__realloc_dbg);

    return g_vld.__realloc_dbg(pcrtxxd__realloc_dbg, context, debug, mem, size, type, file, line);
}

// crtd__recalloc_dbg - Calls to _recalloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - mem (IN): Pointer to the memory block to be reallocated.
//
//  - size (IN): The size of the memory block to reallocate.
//
//  - type (IN): The CRT "use type" of the block to be reallocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _realloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__recalloc_dbg (void       *mem,
                                                      size_t     num,
                                                      size_t     size,
                                                      int        type,
                                                      char const *file,
                                                      int        line)
{
    _recalloc_dbg_t pcrtxxd__recalloc_dbg = (_recalloc_dbg_t)data.pcrtd__recalloc_dbg;
    assert(pcrtxxd__recalloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__recalloc_dbg);

    return g_vld.__recalloc_dbg(pcrtxxd__recalloc_dbg, context, debug, mem, num, size, type, file, line);
}


template<int CRTVersion, bool debug>
char* CrtMfcPatch<CRTVersion, debug>::crtd__strdup_dbg (const char* src,
    int         type,
    char const *file,
    int         line)
{
    _strdup_dbg_t pcrtxxd__strdup_dbg = (_strdup_dbg_t)data.pcrtd__strdup_dbg;
    assert(pcrtxxd__strdup_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__strdup_dbg);

    return g_vld.__strdup_dbg(pcrtxxd__strdup_dbg, context, debug, src, type, file, line);
}


template<int CRTVersion, bool debug>
wchar_t* CrtMfcPatch<CRTVersion, debug>::crtd__wcsdup_dbg (const wchar_t* src,
    int         type,
    char const *file,
    int         line)
{
    _wcsdup_dbg_t pcrtxxd__wcsdup_dbg = (_wcsdup_dbg_t)data.pcrtd__wcsdup_dbg;
    assert(pcrtxxd__wcsdup_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__wcsdup_dbg);

    return g_vld.__wcsdup_dbg(pcrtxxd__wcsdup_dbg, context, debug, src, type, file, line);
}

// crtd__scalar_new_dbg - Calls to the CRT's debug scalar new operator from
//   msvcrXXd.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The CRT "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the CRT debug scalar new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__scalar_new_dbg (size_t      size,
                                                        int         type,
                                                        char const *file,
                                                        int         line)
{
    new_dbg_crt_t pcrtxxd_new_dbg = (new_dbg_crt_t)data.pcrtd__scalar_new_dbg;
    assert(pcrtxxd_new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_new_dbg);

    return g_vld.__new_dbg_crt(pcrtxxd_new_dbg, context, debug, size, type, file, line);
}

// crtd__vector_new_dbg - Calls to the CRT's debug vector new operator from
//   msvcrXXd.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The CRT "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the CRT debug vector new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__vector_new_dbg (size_t      size,
                                                        int         type,
                                                        char const *file,
                                                        int         line)
{
    new_dbg_crt_t pcrtxxd_new_dbg = (new_dbg_crt_t)data.pcrtd__vector_new_dbg;
    assert(pcrtxxd_new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_new_dbg);

    return g_vld.__new_dbg_crt(pcrtxxd_new_dbg, context, debug, size, type, file, line);
}

// crtd_calloc - Calls to calloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - num (IN): The number of blocks, of size 'size', to be allocated.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the valued returned from calloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd_calloc (size_t num, size_t size)
{
    calloc_t pcrtxxd_calloc = (calloc_t)data.pcrtd_calloc;
    assert(pcrtxxd_calloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_calloc);

    return g_vld._calloc(pcrtxxd_calloc, context, debug, num, size);
}

// crtd_malloc - Calls to malloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the valued returned from malloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd_malloc (size_t size)
{
    malloc_t pcrtxxd_malloc = (malloc_t)data.pcrtd_malloc;
    assert(pcrtxxd_malloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_malloc);

    return g_vld._malloc(pcrtxxd_malloc, context, debug, size);
}

// crtd_realloc - Calls to realloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - mem (IN): Pointer to the memory block to reallocate.
//
//  - size (IN): Size of the memory block to reallocate.
//
//  Return Value:
//
//    Returns the value returned from realloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd_realloc (void *mem, size_t size)
{
    realloc_t pcrtxxd_realloc = (realloc_t)data.pcrtd_realloc;
    assert(pcrtxxd_realloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_realloc);

    return g_vld._realloc(pcrtxxd_realloc, context, debug, mem, size);
}

// crtd__recalloc - Calls to _recalloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - mem (IN): Pointer to the memory block to reallocate.
//
//  - size (IN): Size of the memory block to reallocate.
//
//  Return Value:
//
//    Returns the value returned from realloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__recalloc (void *mem, size_t num, size_t size)
{
    _recalloc_t pcrtxxd_recalloc = (_recalloc_t)data.pcrtd_recalloc;
    assert(pcrtxxd_recalloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_recalloc);

    return g_vld.__recalloc(pcrtxxd_recalloc, context, debug, mem, num, size);
}


template<int CRTVersion, bool debug>
char* CrtMfcPatch<CRTVersion, debug>::crtd__strdup (const char* src)
{
    _strdup_t pcrtxxd_strdup = (_strdup_t)data.pcrtd__strdup;
    assert(pcrtxxd_strdup);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_strdup);

    return g_vld.__strdup(pcrtxxd_strdup, context, debug, src);
}

template<int CRTVersion, bool debug>
wchar_t* CrtMfcPatch<CRTVersion, debug>::crtd__wcsdup (const wchar_t* src)
{
    _wcsdup_t pcrtxxd_wcsdup = (_wcsdup_t)data.pcrtd__wcsdup;
    assert(pcrtxxd_wcsdup);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_wcsdup);

    return g_vld.__wcsdup(pcrtxxd_wcsdup, context, debug, src);
}

// crtd__aligned_malloc_dbg - Calls to _aligned_malloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The CRT "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _aligned_malloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_malloc_dbg (size_t      size,
    size_t      alignment,
    int         type,
    char const *file,
    int         line)
{
    _aligned_malloc_dbg_t pcrtxxd__aligned_malloc_dbg = (_aligned_malloc_dbg_t)data.pcrtd__aligned_malloc_dbg;
    assert(pcrtxxd__aligned_malloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__aligned_malloc_dbg);

    return g_vld.__aligned_malloc_dbg(pcrtxxd__aligned_malloc_dbg, context, debug, size, alignment, type, file, line);
}

// crtd__aligned_offset_malloc_dbg - Calls to _aligned_offset_malloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The CRT "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _aligned_offset_malloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_offset_malloc_dbg (size_t      size,
    size_t      alignment,
    size_t      offset,
    int         type,
    char const *file,
    int         line)
{
    _aligned_offset_malloc_dbg_t pcrtxxd__malloc_dbg = (_aligned_offset_malloc_dbg_t)data.pcrtd__aligned_offset_malloc_dbg;
    assert(pcrtxxd__malloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__malloc_dbg);

    return g_vld.__aligned_offset_malloc_dbg(pcrtxxd__malloc_dbg, context, debug, size, alignment, offset, type, file, line);
}

// crtd__aligned_realloc_dbg - Calls to _aligned_realloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - mem (IN): Pointer to the memory block to be reallocated.
//
//  - size (IN): The size of the memory block to reallocate.
//
//  - type (IN): The CRT "use type" of the block to be reallocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _aligned_realloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_realloc_dbg (void       *mem,
    size_t     size,
    size_t     alignment,
    int        type,
    char const *file,
    int        line)
{
    _aligned_realloc_dbg_t pcrtxxd__realloc_dbg = (_aligned_realloc_dbg_t)data.pcrtd__aligned_realloc_dbg;
    assert(pcrtxxd__realloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__realloc_dbg);

    return g_vld.__aligned_realloc_dbg(pcrtxxd__realloc_dbg, context, debug, mem, size, alignment, type, file, line);
}

// crtd__aligned_offset_realloc_dbg - Calls to _aligned_offset_realloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - mem (IN): Pointer to the memory block to be reallocated.
//
//  - size (IN): The size of the memory block to reallocate.
//
//  - type (IN): The CRT "use type" of the block to be reallocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _aligned_offset_realloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_offset_realloc_dbg (void       *mem,
    size_t     size,
    size_t     alignment,
    size_t     offset,
    int        type,
    char const *file,
    int        line)
{
    _aligned_offset_realloc_dbg_t pcrtxxd__realloc_dbg = (_aligned_offset_realloc_dbg_t)data.pcrtd__aligned_offset_realloc_dbg;
    assert(pcrtxxd__realloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__realloc_dbg);

    return g_vld.__aligned_offset_realloc_dbg(pcrtxxd__realloc_dbg, context, debug, mem, size, alignment, offset, type, file, line);
}

// crtd__aligned_recalloc_dbg - Calls to _aligned_recalloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - mem (IN): Pointer to the memory block to be reallocated.
//
//  - num (IN): The count of the memory block to reallocate.
//
//  - size (IN): The size of the memory block to reallocate.
//
//  - type (IN): The CRT "use type" of the block to be reallocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _aligned_realloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_recalloc_dbg (void       *mem,
    size_t     num,
    size_t     size,
    size_t     alignment,
    int        type,
    char const *file,
    int        line)
{
    _aligned_recalloc_dbg_t pcrtxxd__recalloc_dbg = (_aligned_recalloc_dbg_t)data.pcrtd__aligned_recalloc_dbg;
    assert(pcrtxxd__recalloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__recalloc_dbg);

    return g_vld.__aligned_recalloc_dbg(pcrtxxd__recalloc_dbg, context, debug, mem, num, size, alignment, type, file, line);
}

// crtd__aligned_offset_recalloc_dbg - Calls to _aligned_offset_realloc_dbg from msvcrXXd.dll are patched
//   through to this function.
//
//  - mem (IN): Pointer to the memory block to be reallocated.
//
//  - num (IN): The count of the memory block to reallocate.
//
//  - size (IN): The size of the memory block to reallocate.
//
//  - type (IN): The CRT "use type" of the block to be reallocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by _aligned_offset_realloc_dbg.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_offset_recalloc_dbg (void       *mem,
    size_t     num,
    size_t     size,
    size_t     alignment,
    size_t     offset,
    int        type,
    char const *file,
    int        line)
{
    _aligned_offset_recalloc_dbg_t pcrtxxd__recalloc_dbg = (_aligned_offset_recalloc_dbg_t)data.pcrtd__aligned_offset_recalloc_dbg;
    assert(pcrtxxd__recalloc_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd__recalloc_dbg);

    return g_vld.__aligned_offset_recalloc_dbg(pcrtxxd__recalloc_dbg, context, debug, mem, num, size, alignment, offset, type, file, line);
}

// crtd__aligned_malloc - Calls to malloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the valued returned from malloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_malloc (size_t size, size_t alignment)
{
    _aligned_malloc_t pcrtxxd_malloc = (_aligned_malloc_t)data.pcrtd_aligned_malloc;
    assert(pcrtxxd_malloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_malloc);

    return g_vld.__aligned_malloc(pcrtxxd_malloc, context, debug, size, alignment);
}

// crtd__aligned_offset_malloc - Calls to malloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the valued returned from malloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_offset_malloc (size_t size, size_t alignment, size_t offset)
{
    _aligned_offset_malloc_t pcrtxxd_malloc = (_aligned_offset_malloc_t)data.pcrtd_aligned_offset_malloc;
    assert(pcrtxxd_malloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_malloc);

    return g_vld.__aligned_offset_malloc(pcrtxxd_malloc, context, debug, size, alignment, offset);
}

// crtd__aligned_realloc - Calls to realloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - mem (IN): Pointer to the memory block to reallocate.
//
//  - size (IN): Size of the memory block to reallocate.
//
//  Return Value:
//
//    Returns the value returned from realloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_realloc (void *mem, size_t size, size_t alignment)
{
    _aligned_realloc_t pcrtxxd_realloc = (_aligned_realloc_t)data.pcrtd_aligned_realloc;
    assert(pcrtxxd_realloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_realloc);

    return g_vld.__aligned_realloc(pcrtxxd_realloc, context, debug, mem, size, alignment);
}

// crtd__aligned_offset_realloc - Calls to realloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - mem (IN): Pointer to the memory block to reallocate.
//
//  - size (IN): Size of the memory block to reallocate.
//
//  Return Value:
//
//    Returns the value returned from realloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_offset_realloc (void *mem, size_t size, size_t alignment, size_t offset)
{
    _aligned_offset_realloc_t pcrtxxd_realloc = (_aligned_offset_realloc_t)data.pcrtd_aligned_offset_realloc;
    assert(pcrtxxd_realloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_realloc);

    return g_vld.__aligned_offset_realloc(pcrtxxd_realloc, context, debug, mem, size, alignment, offset);
}

// crtd__aligned_recalloc - Calls to realloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - num (IN): Count of the memory block to reallocate.
//
//  - mem (IN): Pointer to the memory block to reallocate.
//
//  - size (IN): Size of the memory block to reallocate.
//
//  Return Value:
//
//    Returns the value returned from realloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_recalloc (void *mem, size_t num, size_t size, size_t alignment)
{
    _aligned_recalloc_t pcrtxxd_recalloc = (_aligned_recalloc_t)data.pcrtd_aligned_recalloc;
    assert(pcrtxxd_recalloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_recalloc);

    return g_vld.__aligned_recalloc(pcrtxxd_recalloc, context, debug, mem, num, size, alignment);
}

// crtd__aligned_offset_recalloc - Calls to realloc from msvcrXXd.dll are patched through to
//   this function.
//
//  - dll (IN): The name of the dll
//
//  - mem (IN): Pointer to the memory block to reallocate.
//
//  - num (IN): Count of the memory block to reallocate.
//
//  - size (IN): Size of the memory block to reallocate.
//
//  Return Value:
//
//    Returns the value returned from realloc.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd__aligned_offset_recalloc (void *mem, size_t num, size_t size, size_t alignment, size_t offset)
{
    _aligned_offset_recalloc_t pcrtxxd_recalloc = (_aligned_offset_recalloc_t)data.pcrtd_aligned_offset_recalloc;
    assert(pcrtxxd_recalloc);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_recalloc);

    return g_vld.__aligned_offset_recalloc(pcrtxxd_recalloc, context, debug, mem, num, size, alignment, offset);
}

// crtd_scalar_new - Calls to the CRT's scalar new operator from msvcrXXd.dll
//   are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the value returned by the CRT scalar new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd_scalar_new (size_t size)
{
    new_t pcrtxxd_scalar_new = (new_t)data.pcrtd_scalar_new;
    assert(pcrtxxd_scalar_new);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_scalar_new);

    return g_vld._new(pcrtxxd_scalar_new, context, debug, size);
}

// crtd_vector_new - Calls to the CRT's vector new operator from msvcrXXd.dll
//   are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the value returned by the CRT vector new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::crtd_vector_new (size_t size)
{
    new_t pcrtxxd_scalar_new = (new_t)data.pcrtd_vector_new;
    assert(pcrtxxd_scalar_new);

    context_t context;
    CAPTURE_CONTEXT(context, pcrtxxd_scalar_new);

    return g_vld._new(pcrtxxd_scalar_new, context, debug, size);
}

////////////////////////////////////////////////////////////////////////////////
//
// MFC DLLs
//
////////////////////////////////////////////////////////////////////////////////

// mfcd__scalar_new_dbg_3p - Calls to the MFC debug scalar new operator from
//   mfcXXd.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the MFC debug scalar new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcd__scalar_new_dbg_4p (size_t       size,
                                                           int          type,
                                                           char const  *file,
                                                           int          line)
{
    new_dbg_crt_t pmfcxxd__new_dbg = (new_dbg_crt_t)data.pmfcd__scalar_new_dbg_4p;
    assert(pmfcxxd__new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd__new_dbg);

    return g_vld.__new_dbg_mfc(pmfcxxd__new_dbg, context, size, type, file, line);
}

// mfcd__scalar_new_dbg_3p - Calls to the MFC debug scalar new operator from
//   mfcXXd.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the MFC debug scalar new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcd__scalar_new_dbg_3p (size_t       size,
                                                           char const  *file,
                                                           int          line)
{
    new_dbg_mfc_t pmfcxxd__new_dbg = (new_dbg_mfc_t)data.pmfcd__scalar_new_dbg_3p;
    assert(pmfcxxd__new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd__new_dbg);

    return g_vld.__new_dbg_mfc(pmfcxxd__new_dbg, context, size, file, line);
}

// mfcd__vector_new_dbg_4p - Calls to the MFC debug vector new operator from
//   mfcXXd.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the MFC debug vector new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcd__vector_new_dbg_4p (size_t       size,
                                                           int          type,
                                                           char const  *file,
                                                           int          line)
{
    new_dbg_crt_t pmfcxxd__new_dbg = (new_dbg_crt_t)data.pmfcd__scalar_new_dbg_4p;
    assert(pmfcxxd__new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd__new_dbg);

    return g_vld.__new_dbg_mfc(pmfcxxd__new_dbg, context, size, type, file, line);
}

// mfcd__vector_new_dbg_3p - Calls to the MFC debug vector new operator from
//   mfcXXd.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the MFC debug vector new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcd__vector_new_dbg_3p (size_t       size,
                                                           char const  *file,
                                                           int          line)
{
    new_dbg_mfc_t pmfcxxd__new_dbg = (new_dbg_mfc_t)data.pmfcd__vector_new_dbg_3p;
    assert(pmfcxxd__new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd__new_dbg);

    return g_vld.__new_dbg_mfc(pmfcxxd__new_dbg, context, size, file, line);
}

// mfcd_scalar_new - Calls to the MFC scalar new operator from mfcXXd.dll are
//   patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the value returned by the MFC scalar new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcd_scalar_new (size_t size)
{
    new_t pmfcxxd_new = (new_t)data.pmfcd_scalar_new;
    assert(pmfcxxd_new);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd_new);

    return g_vld._new(pmfcxxd_new, context, debug, size);
}

// mfcd_vector_new - Calls to the MFC vector new operator from mfcXXd.dll are
//   patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the value returned by the MFC vector new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcd_vector_new (size_t size)
{
    new_t pmfcxxd_new = (new_t)data.pmfcd_vector_new;
    assert(pmfcxxd_new);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd_new);

    return g_vld._new(pmfcxxd_new, context, debug, size);
}

// mfcud__scalar_new_dbg_4p - Calls to the MFC debug scalar new operator from
//   mfcXXud.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the MFC debug scalar new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcud__scalar_new_dbg_4p (size_t      size,
                                                            int         type,
                                                            char const *file,
                                                            int         line)
{
    new_dbg_crt_t pmfcxxd__new_dbg = (new_dbg_crt_t)data.pmfcud__scalar_new_dbg_4p;
    assert(pmfcxxd__new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd__new_dbg);

    return g_vld.__new_dbg_mfc(pmfcxxd__new_dbg, context, size, type, file, line);
}

// mfcud__scalar_new_dbg_3p - Calls to the MFC debug scalar new operator from
//   mfcXXud.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the MFC debug scalar new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcud__scalar_new_dbg_3p (size_t      size,
                                                            char const *file,
                                                            int         line)
{
    new_dbg_mfc_t pmfcxxd__new_dbg = (new_dbg_mfc_t)data.pmfcud__scalar_new_dbg_3p;
    assert(pmfcxxd__new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd__new_dbg);

    return g_vld.__new_dbg_mfc(pmfcxxd__new_dbg, context, size, file, line);
}

// mfcud__vector_new_dbg_4p - Calls to the MFC debug vector new operator from
//   mfcXXud.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - type (IN): The "use type" of the block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the MFC debug vector new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcud__vector_new_dbg_4p (size_t      size,
                                                            int         type,
                                                            char const *file,
                                                            int         line)
{
    new_dbg_crt_t pmfcxxd__new_dbg = (new_dbg_crt_t)data.pmfcud__scalar_new_dbg_4p;
    assert(pmfcxxd__new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd__new_dbg);

    return g_vld.__new_dbg_mfc(pmfcxxd__new_dbg, context, size, type, file, line);
}

// mfcud__vector_new_dbg_3p - Calls to the MFC debug vector new operator from
//   mfcXXud.dll are patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  - file (IN): The name of the file from which this function is being called.
//
//  - line (IN): The line number, in the above file, at which this function is
//      being called.
//
//  Return Value:
//
//    Returns the value returned by the MFC debug vector new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcud__vector_new_dbg_3p (size_t      size,
                                                            char const *file,
                                                            int         line)
{
    new_dbg_mfc_t pmfcxxd__new_dbg = (new_dbg_mfc_t)data.pmfcud__vector_new_dbg_3p;
    assert(pmfcxxd__new_dbg);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd__new_dbg);

    return g_vld.__new_dbg_mfc(pmfcxxd__new_dbg, context, size, file, line);
}

// mfcud_scalar_new - Calls to the MFC scalar new operator from mfcXXud.dll are
//   patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the value returned by the MFC scalar new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcud_scalar_new (size_t size)
{
    new_t pmfcxxd_new = (new_t)data.pmfcud_scalar_new;
    assert(pmfcxxd_new);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd_new);

    return g_vld._new(pmfcxxd_new, context, debug, size);
}

// mfcud_vector_new - Calls to the MFC vector new operator from mfcXXud.dll are
//   patched through to this function.
//
//  - size (IN): The size, in bytes, of the memory block to be allocated.
//
//  Return Value:
//
//    Returns the value returned by the MFC vector new operator.
//
template<int CRTVersion, bool debug>
void* CrtMfcPatch<CRTVersion, debug>::mfcud_vector_new (size_t size)
{
    new_t pmfcxxd_new = (new_t)data.pmfcud_vector_new;
    assert(pmfcxxd_new);

    context_t context;
    CAPTURE_CONTEXT(context, pmfcxxd_new);

    return g_vld._new(pmfcxxd_new, context, debug, size);
}

// Visual Studio 6.0
typedef CrtMfcPatch<60>
    VS60;
typedef CrtMfcPatch<60, true>
    VS60d;
// Visual Studio .NET 2002
typedef CrtMfcPatch<70>
    VS70;
typedef CrtMfcPatch<70, true>
    VS70d;
// Visual Studio .NET 2003
typedef CrtMfcPatch<71>
    VS71;
typedef CrtMfcPatch<71, true>
    VS71d;
// Visual Studio 2005
typedef CrtMfcPatch<80>
    VS80;
typedef CrtMfcPatch<80, true>
    VS80d;
// Visual Studio 2008
typedef CrtMfcPatch<90>
    VS90;
typedef CrtMfcPatch<90, true>
    VS90d;
// Visual Studio 2010
typedef CrtMfcPatch<100>
    VS100;
typedef CrtMfcPatch<100, true>
    VS100d;
// Visual Studio 2012
typedef CrtMfcPatch<110>
    VS110;
typedef CrtMfcPatch<110, true>
    VS110d;
// Visual Studio 2013
typedef CrtMfcPatch<120>
    VS120;
typedef CrtMfcPatch<120, true>
    VS120d;

VS60    VS60::data;
VS60d   VS60d::data;
VS70    VS70::data;
VS70d   VS70d::data;
VS71    VS71::data;
VS71d   VS71d::data;
VS80    VS80::data;
VS80d   VS80d::data;
VS90    VS90::data;
VS90d   VS90d::data;
VS100   VS100::data;
VS100d  VS100d::data;
VS110   VS110::data;
VS110d  VS110d::data;
VS120   VS120::data;
VS120d  VS120d::data;
