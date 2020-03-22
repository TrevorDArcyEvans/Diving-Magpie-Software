// pre-compiled headers
#include "stdafx.h"

#include <mmsystem.h>
#include "StickWorks.h"
#include "SldWorks.h"
#include "timer.h"
#include "JoyPanel.h"
#include "ExampleApp.h"
#include <tchar.h>

// -------------------------------------------------------------------

extern BOOL CALLBACK    SW_JoyControlPanelEnumFunc(
                            HWND                hwnd    ,
                            LPARAM              lParam  )
/* -----------------------------------------------------------------
** callback function for enumerating windows when trying to find 
** the joystick control panel.
** PARAMETERS:
**      hwnd        handle to current window being enumerated
**      lParam      application specific parameter
** RETURNS:
**      TRUE        if enumeration of windows is     to continue
**      FALSE       if enumeration of windows is not to continue
** NOTES:
**      1)  lParam is not used here
**      2)  references:
**              g_bJoystickPanelShowing;
----------------------------------------------------------------- */
{
    #define     JOYSTICK_WINDOW     _T("Joystick Properties")

    _TCHAR      buff[128];  

    GetWindowText(hwnd, buff, 127);

    // check for joystick control panel before SW
    if (_tcsstr(buff, JOYSTICK_WINDOW)!= NULL)
        {
        // found joystick panel so stop enumerating
        g_bJoystickPanelShowing = true;
        return FALSE;
        }

    return TRUE;
}

// -------------------------------------------------------------------

VOID CALLBACK SW_JoyControlPanelTimer(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    // reset flags for joystick panel
    g_bJoystickPanelShowing = false;

    // now try and find SW or joystick panel
    // primarily joystick panel
    EnumWindows((WNDENUMPROC ) SW_JoyControlPanelEnumFunc, (LPARAM ) 1);
}

// -------------------------------------------------------------------
