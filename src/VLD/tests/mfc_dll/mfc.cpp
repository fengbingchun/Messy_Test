// mfc.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "mfc.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CmfcApp

BEGIN_MESSAGE_MAP(CmfcApp, CWinApp)
END_MESSAGE_MAP()


// CmfcApp construction

CmfcApp::CmfcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CmfcApp object

CmfcApp theApp;


// CmfcApp initialization

BOOL CmfcApp::InitInstance()
{
	CWinApp::InitInstance();
	
	return TRUE;
}

int CmfcApp::ExitInstance()
{
	// Without this, Dynamically unloading the MFC dll will crash
#ifdef _DEBUG   // entire file
	AfxEnableMemoryLeakDump(FALSE);
#endif
	return 0;
}

// Leaks 4 memory allocations
extern "C" void __declspec(dllexport) MFC_LeakSimple()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	// Attempt to allocate and leak some form of memory
	CString* str_a = new CString(_T("I am a string in MFC"));
	CString* str_b = new CString(_T("Another string in MFC"));
	CString* str_c = DEBUG_NEW CString(_T("Another string in MFC"));
	CString* str_d = new (_NORMAL_BLOCK, __FILE__, __LINE__) CString(_T("4 parameter new for mfc"));
}

// Leaks 3 memory allocations
extern "C" void __declspec(dllexport) MFC_LeakArray()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	// Attempt to allocate and leak an array of CStrings
	CString* mystr = new CString[3];

	CString* strArray = DEBUG_NEW CString[3];

	CString* another  = new (_NORMAL_BLOCK, __FILE__, __LINE__) CString[3];
}

