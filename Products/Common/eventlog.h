/* EVENTLOG.H - Header file for Eventlog class
Copyright:   (C) Sigmex BV, 2000. All rights reserved.

    Wrapper class for the EventLog API

History:
    [00]    HB  16Jun00 Derived from "Windows NT in Practice"

*/

#ifndef _EVENTLOG_H_
#define _EVENTLOG_H_

class EventLog 
{
public:
      EventLog();
      EventLog(TCHAR *szSourceName, TCHAR *szMessageDLL, 
               BOOL bClearOnExit = FALSE, DWORD *dwStatus = NULL);
      virtual ~EventLog();

      void   UseSource(TCHAR *szSourceName);

      static BOOL RegisterModule(TCHAR *szModuleName);
      static BOOL RegisterSource(TCHAR *szSource, TCHAR *szMessageFile);
      static BOOL UnregisterModule(TCHAR *szModuleName);
      static BOOL UnregisterSource(TCHAR *szSource);

      DWORD  Backup(LPTSTR szBackup);
      DWORD  Clear(LPTSTR szBackup);
      DWORD  Query(DWORD *dwNumRecords, DWORD *dwOldestRecord);
      DWORD  Read(DWORD dwRec, EVENTLOGRECORD *pData, DWORD dwSize);
      DWORD  Write(DWORD dwEventID, WORD wEventType, WORD wStrings,
                  LPCTSTR *pszStrings, DWORD dwData, LPBYTE lpData);
      DWORD  WriteCustom(LPCTSTR szString, WORD wEventType);
	  DWORD  WriteSimple(DWORD dwEventID, CComBSTR ErrorMessage);

private:
      TCHAR szSource[MAX_PATH];
      TCHAR szRegKey[MAX_PATH];
      BOOL  bClearReg;
         // prevent copy by declaring without defining
      EventLog(const EventLog&);
      const EventLog& operator=(const EventLog&);
};
#endif
