// dynamic.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dynamic.h"
#include "../basics/Allocs.h"
#include "../basics/LeakOption.h"

extern "C" {
// This is an example of an exported variable
DYNAMIC_API int ndynamic = 0;

void LeakMemory(LeakOption type, int repeat)
{
	for (int i = 0; i < repeat; i++)
	{
		Alloc(type);
	}
}

// This is an example of an exported function.

void SimpleLeak_Malloc(void)
{
	LeakMemory(eMalloc, 3); // leaks 6
}

void SimpleLeak_New(void)
{
	LeakMemory(eNew, 3); // leaks 6
}

void SimpleLeak_New_Array(void)
{
	LeakMemory(eNewArray, 3); // leaks 6
}

// This is the constructor of a class that has been exported.
// see dynamic.h for the class definition
Cdynamic::Cdynamic()
{
	return;
}

}