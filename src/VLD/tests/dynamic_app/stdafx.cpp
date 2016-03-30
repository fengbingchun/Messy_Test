// stdafx.cpp : source file that includes just the standard includes
// dynamic_app.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// Formats a message string using the specified message and variable
// list of arguments.
void GetFormattedMessage(DWORD last_error)
{
    // Retrieve the system error message for the last-error code
    WCHAR lpMsgBuf[MAX_PATH] = {0};

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        last_error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        lpMsgBuf,
        MAX_PATH,
        NULL );

    // Display the error message.
    wprintf(_T("%s\n"), lpMsgBuf);
}
