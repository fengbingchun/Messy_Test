#if !defined(AFX_VLDMFCDLG_H__E5AE1FE6_8C7C_4A59_8DC1_2369B5C7B240__INCLUDED_)
#define AFX_VLDMFCDLG_H__E5AE1FE6_8C7C_4A59_8DC1_2369B5C7B240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCExampleDlg dialog

class CMFCExampleDlg : public CDialog
{
// Construction
public:
	CMFCExampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCExampleDlg)
	enum { IDD = IDD_VLDMFC_DIALOG };
	BOOL	m_bLeak;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCExampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCExampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VLDMFCDLG_H__E5AE1FE6_8C7C_4A59_8DC1_2369B5C7B240__INCLUDED_)
