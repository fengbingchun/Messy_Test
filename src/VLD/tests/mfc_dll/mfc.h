// mfc.h : main header file for the mfc DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CmfcApp
// See mfc.cpp for the implementation of this class
//

class CmfcApp : public CWinApp
{
public:
	CmfcApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int  ExitInstance(); // return app exit code
	DECLARE_MESSAGE_MAP()
};
