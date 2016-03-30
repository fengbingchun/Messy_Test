////////////////////////////////////////////////////////////////////////////////
//
//  Visual Leak Detector - Internal C++ Heap Management Definitions
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
#include <memory>
#include "vldheap.h"     // Provides internal new and delete operators.

#pragma push_macro("new")
#undef new
template <typename T>
class vldallocator: public std::allocator<T>
{
public:
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;

    template<typename _Tp1>
    struct rebind
    {
        typedef vldallocator<_Tp1> other;
    };

    pointer allocate(size_type n, const void * /*hint*/ = 0)
    {
        return (pointer)::operator new(sizeof(T)*n, __FILE__, __LINE__);
    }

    void deallocate(pointer p, size_type /*n*/)
    {
        return ::operator delete(p);
    }

    vldallocator() throw() : std::allocator<T>() { }
    vldallocator(const vldallocator &a) throw() : std::allocator<T>(a) { }
    template<class Other>
    vldallocator(const vldallocator<Other> &a) throw() : std::allocator<T>(a) { }
    ~vldallocator() throw() { }
};
#pragma pop_macro("new")
