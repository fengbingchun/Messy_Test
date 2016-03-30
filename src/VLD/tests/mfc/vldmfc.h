#if !defined(AFX_VLDMFC_H__9B6C7B98_B322_4E4F_9969_823D500649E9__INCLUDED_)
#define AFX_VLDMFC_H__9B6C7B98_B322_4E4F_9969_823D500649E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCExampleApp:
// See vldmfc.cpp for the implementation of this class
//

class CMFCExampleApp : public CWinApp
{
public:
	CMFCExampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCExampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCExampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VLDMFC_H__9B6C7B98_B322_4E4F_9969_823D500649E9__INCLUDED_)
