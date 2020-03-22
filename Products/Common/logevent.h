/* LogEvent.h - Header for inline function LogEvent.h

   LogEvent is a global, inline function for writing to the event log.
   The reported event does not have an associated resource with an 
   formatted text in a specific language, and this "error" will be reported
   by the standard NT Event Log viewer. Therefore, the use 
   of this function should be restricted to real exceptions or
   debugging/internal use only (but it's better than nothing !)

History:
    [01]    TDE     18Jul00     added includes for <stdio.h> & <stdarg.h>
                                to fix build errors in some configurations

$History: LogEvent.h $
 * 
 * *****************  Version 2  *****************
 * User: Hans         Date: 18-07-00   Time: 10:14
 * Updated in $/METCOM/Projects/FileDumperServer
 * comments added
*/

#ifndef _LogEvent_h
#define _LogEvent_h

#include <stdio.h>      // [01]
#include <stdarg.h>     // [01]

inline void LogEvent (LPCTSTR pFormat, ...)
{
    //  Log an event. Copied from ATL Wizard generated code
    TCHAR               chMsg[256];
    HANDLE              hEventSource;
    LPTSTR              lpszStrings[1];
    va_list             pArg;

    va_start(pArg, pFormat);
    _vstprintf(chMsg, pFormat, pArg);
    va_end(pArg);

    lpszStrings[0] = chMsg;

    //  Get a handle to use with ReportEvent(). 
    // TDE  this has been commented out for the CMIDS project
    //hEventSource = RegisterEventSource(NULL, _T ("Diving Magpie Software Application"));
    hEventSource = RegisterEventSource(NULL, _T ("DMS"));
    if (hEventSource != NULL)
        {
        //  Write to event log.
        ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR *) &lpszStrings[0], NULL);
        DeregisterEventSource(hEventSource);
        }
}

#endif