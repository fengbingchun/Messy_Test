#include "stdafx.h"
#include "vldmfc.h"

/////////////////////////////////////////////////////////////////////////////
// CMFCExampleApp

BEGIN_MESSAGE_MAP(CMFCExampleApp, CWinApp)
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
/// Efficiently searches a module's name pointer table (NPT) for the named
/// procedure.
///
/// @param[in] npt     Address of the NPT to search.
///
/// @param[in] size    Number of entries in the NPT.
///
/// @param[in] base    Base address of the module containing the NPT. This is
///                    used to resolve addresses in the NPT (which are relative
///                    to the module's base address).
///
/// @param[in] proc    String containing the name of the procedure to search
///                    for.
///
/// @return    Returns the index into the NPT of the entry matching the named
///            procedure. If no such matching entry exists, the function returns
///            -1.
///
DWORD FindNptProc (PDWORD npt, DWORD size, PBYTE base, void* proc)
{
    for (DWORD i = 0; i < size; i++)
    {
        void* p = (void*)(npt[i] + base);
        if (p == proc)
            return i;
    }

    return -1;
}

/// Gets a pointer to a module's export directory table (EDT).
///
/// @param[in] module    Handle to the module (as returned by GetModuleHandle).
///
/// @return    Returns a pointer to the module's EDT. If there is an error (e.g.
///            if the module handle is invalid or the module has no EDT) the
///            function will return NULL.
///
PIMAGE_EXPORT_DIRECTORY GetExportDirectoryTable (HMODULE module)
{
    PBYTE                   base; // base address of module
    PIMAGE_FILE_HEADER      cfh;  // COFF file header
    PIMAGE_EXPORT_DIRECTORY edt;  // export directory table (EDT)
    DWORD                   rva;  // relative virtual address of EDT
    PIMAGE_DOS_HEADER       mds;  // MS-DOS stub
    PIMAGE_OPTIONAL_HEADER  oh;   // so-called "optional" header
    PDWORD                  sig;  // PE signature

    // Start at the base of the module. The MS-DOS stub begins there.
    base = (PBYTE)module;
    mds = (PIMAGE_DOS_HEADER)module;

    // Get the PE signature and verify it.
    sig = (DWORD *)(base + mds->e_lfanew);
    if (IMAGE_NT_SIGNATURE != *sig) {
        // Bad signature -- invalid image or module handle
        return NULL;
    }

    // Get the COFF file header.
    cfh = (PIMAGE_FILE_HEADER)(sig + 1);

    // Get the "optional" header (it's not actually optional for executables).
    oh = (PIMAGE_OPTIONAL_HEADER)(cfh + 1);

    // Finally, get the export directory table.
    if (IMAGE_DIRECTORY_ENTRY_EXPORT >= oh->NumberOfRvaAndSizes) {
        // This image doesn't have an export directory table.
        return NULL;
    }
    rva = oh->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    edt = (PIMAGE_EXPORT_DIRECTORY)(base + rva);

    return edt;
}

/// Gets the o of an exported procedure.
///
/// @param[in] module    Handle (as returned by GetModuleHandle) of the module
///                      that exports the procedure.
///
/// @param[in] proc      String containing the name of the procedure.
///
/// @return    Returns the procedure's o. If an o for the procedure
///            could not be located (e.g. if the named procedure is not exported
///            by the specified module) then the function will return -1.
///
DWORD GetProcOrdinal (HMODULE module, void* proc)
{
    PBYTE                   base; // module base address
    PIMAGE_EXPORT_DIRECTORY edt;  // export directory table (EDT)
    DWORD                   i;    // index into NPT and/or EOT
    PDWORD                  npt;  // name pointer table (NPT)

    base = (PBYTE)module;

    // Get the export directory table, from which we can find the name pointer
    // table and export o table.
    edt = GetExportDirectoryTable(module);

    // Get the name pointer table and search it for the named procedure.
    _ASSERT(edt->NumberOfFunctions);
    npt = (DWORD *)(base + edt->AddressOfFunctions);
    i = FindNptProc(npt, edt->NumberOfFunctions, base, proc);
    if (-1 == i) {
        // The procedure was not found in the module's name pointer table.
        return -1;
    }

    // Actual o is o from EOT plus "o base" from EDT.
    return i + edt->Base;
}

LPVOID FindRealCode(LPVOID pCode)
{
    LPVOID result = pCode;
    if (pCode != NULL)
    {
        if (*(WORD *) pCode == 0x25ff)
        {
            DWORD addr = *((DWORD *) ((ULONG_PTR) pCode + 2));
#ifdef _WIN64
            // RIP relative addressing
            PBYTE pNextInst = (PBYTE) ((ULONG_PTR) pCode + 6);
            pCode = *(LPVOID*) (pNextInst + addr);
            return pCode;
#else
            pCode = *(LPVOID*) (addr);
            return FindRealCode(pCode);
#endif
        }
        else if (*(BYTE *) pCode == 0xE9)
        {
            // Relative next instruction
            PBYTE	pNextInst = (PBYTE) ((ULONG_PTR) pCode + 5);
            LONG	offset = *((LONG *) ((ULONG_PTR) pCode + 1));
            pCode = (LPVOID*)(pNextInst + offset);
            return FindRealCode(pCode);
        }
    }
    return result;
}

void SetClipboardText(LPCTSTR pszText)
{
    const size_t len = (_tcslen(pszText) + 1) * sizeof(pszText[0]);
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), pszText, len);
    GlobalUnlock(hMem);
    if(OpenClipboard(NULL))
    {
        EmptyClipboard();
#ifndef _UNICODE
        HANDLE handle = SetClipboardData(CF_TEXT, hMem);
#else
        HANDLE handle = SetClipboardData(CF_UNICODETEXT, hMem);
#endif
        CloseClipboard();
    }
}

#pragma optimize("", off)

typedef void* (__cdecl *new_t) (size_t);
typedef void* (__cdecl *new_dbg_crt_t) (size_t, int, const char *, int);
typedef void* (__cdecl *new_dbg_mfc_t) (size_t, const char *, int);

BOOL CMFCExampleApp::InitInstance()
{
    new_t new_array_f = &(::operator new[]);
    new_dbg_crt_t new_dbg_crt_array_f = &(::operator new[]);
#ifdef _DEBUG
    new_dbg_mfc_t new_dbg_mfc_array_f = &(::operator new[]);
#endif
    new_t new_f = &(::operator new);
    new_dbg_crt_t new_dbg_crt_f = &(::operator new);
#ifdef _DEBUG
    new_dbg_mfc_t new_dbg_mfc_f = &(::operator new);
#endif

    void* p1 = FindRealCode(new_array_f);
    void* p2 = FindRealCode(new_dbg_crt_array_f);
#ifdef _DEBUG
    void* p3 = FindRealCode(new_dbg_mfc_array_f);
#endif
    void* p4 = FindRealCode(new_f);
    void* p5 = FindRealCode(new_dbg_crt_f);
#ifdef _DEBUG
    void* p6 = FindRealCode(new_dbg_mfc_f);
#endif

#ifdef _DEBUG
#ifndef _UNICODE
#if _MFC_VER == 0x0700		// VS 2003
#define MFCDLLNAME   _T("mfc70d.dll")
#elif _MFC_VER == 0x0800	// VS 2005
#define MFCDLLNAME   _T("mfc80d.dll")
#elif _MFC_VER == 0x0900	// VS 2008
#define MFCDLLNAME   _T("mfc90d.dll")
#elif _MFC_VER == 0x0A00	// VS 2010
#define MFCDLLNAME   _T("mfc100d.dll")
#elif _MFC_VER == 0x0B00	// VS 2012
#define MFCDLLNAME   _T("mfc110d.dll")
#elif _MFC_VER == 0x0C00	// VS 2013
#define MFCDLLNAME   _T("mfc120d.dll")
#elif _MFC_VER == 0x0D00	// VS 2015
#define MFCDLLNAME   _T("mfc130d.dll")
#endif
#else
#if _MFC_VER == 0x0700		// VS 2003
#define MFCDLLNAME   _T("mfc70ud.dll")
#elif _MFC_VER == 0x0800	// VS 2005
#define MFCDLLNAME   _T("mfc80ud.dll")
#elif _MFC_VER == 0x0900	// VS 2008
#define MFCDLLNAME   _T("mfc90ud.dll")
#elif _MFC_VER == 0x0A00	// VS 2010
#define MFCDLLNAME   _T("mfc100ud.dll")
#elif _MFC_VER == 0x0B00	// VS 2012
#define MFCDLLNAME   _T("mfc110ud.dll")
#elif _MFC_VER == 0x0C00	// VS 2013
#define MFCDLLNAME   _T("mfc120ud.dll")
#elif _MFC_VER == 0x0D00	// VS 2015
#define MFCDLLNAME   _T("mfc130ud.dll")
#endif
#endif
#else
#ifndef _UNICODE
#if _MFC_VER == 0x0700		// VS 2003
#define MFCDLLNAME   _T("mfc70.dll")
#elif _MFC_VER == 0x0800	// VS 2005
#define MFCDLLNAME   _T("mfc80.dll")
#elif _MFC_VER == 0x0900	// VS 2008
#define MFCDLLNAME   _T("mfc90.dll")
#elif _MFC_VER == 0x0A00	// VS 2010
#define MFCDLLNAME   _T("mfc100.dll")
#elif _MFC_VER == 0x0B00	// VS 2012
#define MFCDLLNAME   _T("mfc110.dll")
#elif _MFC_VER == 0x0C00	// VS 2013
#define MFCDLLNAME   _T("mfc120.dll")
#elif _MFC_VER == 0x0D00	// VS 2015
#define MFCDLLNAME   _T("mfc130.dll")
#endif
#else
#if _MFC_VER == 0x0700		// VS 2003
#define MFCDLLNAME   _T("mfc70u.dll")
#elif _MFC_VER == 0x0800	// VS 2005
#define MFCDLLNAME   _T("mfc80u.dll")
#elif _MFC_VER == 0x0900	// VS 2008
#define MFCDLLNAME   _T("mfc90u.dll")
#elif _MFC_VER == 0x0A00	// VS 2010
#define MFCDLLNAME   _T("mfc100u.dll")
#elif _MFC_VER == 0x0B00	// VS 2012
#define MFCDLLNAME   _T("mfc110u.dll")
#elif _MFC_VER == 0x0C00	// VS 2013
#define MFCDLLNAME   _T("mfc120u.dll")
#elif _MFC_VER == 0x0D00	// VS 2015
#define MFCDLLNAME   _T("mfc130u.dll")
#endif
#endif
#endif

    HMODULE module = GetModuleHandle(MFCDLLNAME);
    if (NULL == module)
        return FALSE;

    int   o1 = GetProcOrdinal(module, p1);
    int   o2 = GetProcOrdinal(module, p2);
#ifdef _DEBUG
    int   o3 = GetProcOrdinal(module, p3);
#else
    int   o3 = -2;
#endif
    int   o4 = GetProcOrdinal(module, p4);
    int   o5 = GetProcOrdinal(module, p5);
#ifdef _DEBUG
    int   o6 = GetProcOrdinal(module, p6);
#else
    int   o6 = -2;
#endif

    TCHAR msg[256];
    _stprintf(msg, _T("%d, %d, %d, %d, %d, %d"),
        o1, o2, o3, o4, o5, o6);
    SetClipboardText(msg);
    MessageBox(NULL, msg, _T("MFC ordinals"),
        MB_ICONINFORMATION | MB_OK);

    return FALSE;
}
