/* thread.h (pthread emulation for Windows) */

/***********************************************************************
*  This code is part of GLPK (GNU Linear Programming Kit).
*
*  Copyright (C) 2011-2017, Heinrich Schuchardt <xypron.glpk@gmx.de>
*
*  Permission to use, copy, modify, and/or distribute this software for
*  any purpose with or without fee is hereby granted.
*
*  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
*  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
*  AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
*  DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
*  OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
*  TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
*  PERFORMANCE OF THIS SOFTWARE.
***********************************************************************/

#ifndef THREAD_H

#define THREAD_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#ifdef __WOE__
#include <windows.h>
typedef CRITICAL_SECTION pthread_mutex_t;
typedef HANDLE pthread_t;
// @todo The return type of routine C is "DWORD" for Windows and
//       "void *" for Posix.
#define pthread_create(A,B,C,D) \
  (int)((*A = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&C,D,0,NULL))==NULL)
#define pthread_exit(A)          ExitThread(0)
#define pthread_mutex_destroy(A) DeleteCriticalSection(A)
#define pthread_mutex_init(A,B)  (InitializeCriticalSection(A),0)
#define pthread_mutex_lock(A)    (EnterCriticalSection(A),0)
#define pthread_mutex_unlock(A)  (LeaveCriticalSection(A),0)
#define pthread_self()           GetCurrentThreadId()
#define pthread_join(A, B) \
  (WaitForSingleObject(A, INFINITE),CloseHandle(A),0)
#else
#include <pthread.h>
#endif

#endif // THREAD_H
