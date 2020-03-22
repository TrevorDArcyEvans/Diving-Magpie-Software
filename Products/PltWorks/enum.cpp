//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "about.h"
#include "enum.h"
#include "main.h"
//---------------------------------------------------------------------------
/* *********************************************************************** */
extern BOOL CALLBACK    PlotWorksEnumFunc(
                            HWND                hwnd    ,
                            LPARAM              lParam  )
/* -----------------------------------------------------------------
** callback function for enumerating windows when trying to find SolidWorks.
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
extern bool    g_bSW_Running;

----------------------------------------------------------------- */
{
#define     SW_WINDOW           "SolidWorks"

char    buff[128];

GetWindowText(hwnd, buff, 127);

if (strstr(buff, SW_WINDOW)!= NULL)
    {
    // found SW so stop enumerating
    g_bSW_Running = true;
    return FALSE;
    }
else
    {
    // not SW so keep on enumerating
    g_bSW_Running = false;
    }

return TRUE;
}   /* of PlotWorksEnumFunc */

/* *********************************************************************** */


