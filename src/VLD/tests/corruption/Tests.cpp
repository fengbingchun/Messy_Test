#include "StdAfx.h"
#include "Tests.h"
#include "stdlib.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void TestAllocationMismatch_malloc_delete()
{
	int* pint = (int*)malloc(56);
	// use the wrong function to deallocate
	delete pint;
}

void TestAllocationMismatch_malloc_deleteVec()
{
	int* pint = (int*)malloc(56);
	// use the wrong function to deallocate
	delete [] pint;
}

void TestAllocationMismatch_new_free()
{
	int* pint = new int(45); // scalar new
	// use the wrong function to deallocate
	free(pint);
}

void TestAllocationMismatch_newVec_free()
{
	int* pint = new int[3]; // vector new
	// use the wrong function to deallocate
	free(pint);
}

void TestHeapMismatch()
{
	HANDLE test_heap = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_CREATE_ENABLE_EXECUTE, 
									0, // initialize reserved size;
									0); // maximum size can grow
	HANDLE default_heap = GetProcessHeap();
	// Have to initialize vld with something, so it doesn't dismiss
	// the default heap as having no memory allocs in it.
	void* aptr = HeapAlloc(default_heap, 0, 42);
	// Allocate it in the new heap
	void* vptr = HeapAlloc(test_heap, 0, 56);
	// Free this using the WRONG heap!
	HeapFree( default_heap, 0, vptr);
	
	HeapDestroy(test_heap);
}
