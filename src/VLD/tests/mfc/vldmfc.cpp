#include "stdafx.h"
#include "vldmfc.h"
#include "vldmfcdlg.h"

// Include Visual Leak Detector
#include <vld.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCExampleApp

BEGIN_MESSAGE_MAP(CMFCExampleApp, CWinApp)
    //{{AFX_MSG_MAP(CMFCExampleApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCExampleApp construction

CMFCExampleApp::CMFCExampleApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMFCExampleApp object

CMFCExampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMFCExampleApp initialization

BOOL CMFCExampleApp::InitInstance()
{
    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

    CMFCExampleDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
        CString *s = new CString("Hello World!\n");

        if (!dlg.m_bLeak) {
            delete s;
        }
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
    }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
