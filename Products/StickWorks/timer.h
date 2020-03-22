#if !defined(TIMER_H_INCLUDED)
#define TIMER_H_INCLUDED
// pre-compiled headers
#include "stdafx.h"

#include <tchar.h>

VOID CALLBACK SW_JoyTimer(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK SW_RegTimer(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);

#endif