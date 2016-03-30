// corruption.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tests.h"
// This hooks vld into this app
#include "../../vld.h"

enum CorruptionType
{
	eAllocMismatch,
	eHeapMismatch,
	eCount
};

void TestCorruption( CorruptionType check )
{
	if (check == eAllocMismatch)
	{
		TestAllocationMismatch_malloc_delete();
		TestAllocationMismatch_malloc_deleteVec();
		TestAllocationMismatch_new_free();
		TestAllocationMismatch_newVec_free();
	}
	else if (check == eHeapMismatch)
	{
		TestHeapMismatch();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	wprintf(_T("======================================\n"));
	wprintf(_T("==\n"));
	wprintf(_T("==    VLD Tests: Memory Corruption\n"));
	wprintf(_T("==\n"));
	wprintf(_T("======================================\n"));

	UINT vld_options = VLDGetOptions();
	vld_options |= VLD_OPT_VALIDATE_HEAPFREE;
	VLDSetOptions(vld_options, 15, 25);

	CorruptionType check = (CorruptionType)-1;

	if (argc == 2)
	{
		// Pick up options to determine which type of test to execute
		if (_tcsicmp(_T("allocmismatch"), argv[1]) == 0)
			check = eAllocMismatch;
		else if (_tcsicmp(_T("heapmismatch"), argv[1]) == 0)
			check = eHeapMismatch;
		TestCorruption(check);
	}

	if (check == -1)
	{
		for (int i = 0; i < eCount; i++)
		{
			TestCorruption((CorruptionType)i);
		}
	}
	else
	{
		TestCorruption(check);
	}

	return 0;
}

