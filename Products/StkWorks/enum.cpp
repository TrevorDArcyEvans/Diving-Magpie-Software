//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "process.h"
//---------------------------------------------------------------------------
/* *********************************************************************** */

extern BOOL CALLBACK    StickWorksEnumFunc(
                            HWND                hwnd    ,
                            LPARAM              lParam  )
/* -----------------------------------------------------------------
** callback function for enumerating windows when trying to find SolidWorks
** or the joystick control panel.
** Will stop enumerating when the _first_ window with "SolidWorks" in it is
** found.  This is presumably SolidWorks...
** PARAMETERS:
**      hwnd        handle to current window being enumerated
**      lParam      application specific parameter
** RETURNS:
**      TRUE        if enumeration of windows is     to continue
**      FALSE       if enumeration of windows is not to continue
** NOTES:
**      1)  lParam is not used here
extern bool    bSW_Running;
extern bool    bJoystick_Running;

----------------------------------------------------------------- */
{
#define     SW_WINDOW           "SolidWorks"
#define     JOYSTICK_WINDOW     "Joystick Properties"

char    buff[128];

GetWindowText(hwnd, buff, 127);

// check for joystick control panel before SW
if (strstr(buff, JOYSTICK_WINDOW)!= NULL)
    {
    // found joystick panel so stop enumerating
    bJoystick_Running = true;
    return FALSE;
    }
else
    {
    // not joystick panel so keep on enumerating
    bJoystick_Running = false;
    }

if (strstr(buff, SW_WINDOW)!= NULL)
    {
    // found SW so stop enumerating
    bSW_Running = true;
    swWindow = hwnd;
    return FALSE;
    }
else
    {
    // not SW so keep on enumerating
    bSW_Running = false;
    }

return TRUE;
}   /* of StickWorksEnumFunc */

/* *********************************************************************** */


