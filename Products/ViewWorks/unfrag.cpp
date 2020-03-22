// Exe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <comdef.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <tchar.h>

#include "crc_32.h"
#include "unfrag.h"
#include "ViewWorks.h"
#include "WinUtil.h"
#include "utils.h"

// --------------------------------

int VW_Unfrag(
        int     nTimeOut,
        char    *pcFileName)
{
#if 0
    _TCHAR      CodeUStr[_MAX_PATH];
    char        CodeStr [_MAX_PATH];

    GetPrivateProfileString( 
            VIEW_WORKS_INI_FILE_SECTION,
            VIEW_WORKS_INI_FILE_KEY,
            _T("SolidPartners"), // points to default string 
            CodeUStr, // points to destination buffer 
            _MAX_PATH,        // size of destination buffer 
            VIEW_WORKS_INI_FILE_NAME); 

    wu_strcpy(CodeStr, ::CString(CodeUStr));

    char    MachineID[_MAX_PATH];
    strcpy(MachineID, GetMachineID());

    if (false == CheckCode(MachineID, (char *) VIEW_WORKS_TITLE_CODE, CodeStr))
        {
        return 0;
        }
#endif

    BSTR    bstrFileName = _bstr_t(pcFileName);

    if (S_OK == StgIsStorageFile(bstrFileName))
        {
        TCHAR   pcPathName      [_MAX_PATH],
                pcTempFileName  [_MAX_PATH];

        // get a temporary file name
        GetTempPath(_MAX_PATH, pcPathName);
        GetTempFileName(pcPathName, _T("tde"), 0, pcTempFileName);

        // open file for reading
        IStorage* pIn;

        HRESULT hr;

        int nCount = 0;

        // loop forever
        for(;;)
            {
            hr = ::StgOpenStorage(bstrFileName, NULL,
                            STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                            NULL, 0, &pIn);

            // until file becomes free or we timeout 
            if (hr != S_OK && nCount < nTimeOut)
                {
                Sleep(1000);
                nCount++;
                }
            else
                {
                break;
                }
            }
        if (FAILED(hr)) { _tremove(pcTempFileName); return 0; }

        IStorage* pOut;

        hr = ::StgCreateDocfile(_bstr_t(pcTempFileName),
                    STGM_DIRECT | STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
                    0, &pOut);
        if (FAILED(hr)) { pIn->Release(); return 0; }

        hr = pIn->CopyTo(0, NULL, NULL, pOut);
        if (FAILED(hr)) { pIn->Release(); pOut->Release(); return 0; }

        pIn ->Release();
        pOut->Release();

        struct _stat    sTempFileName, sFileName;

        if (0 != _tstat(pcTempFileName, &sTempFileName)) { _tremove(pcTempFileName); }
        if (0 != _stat (pcFileName    , &sFileName    )) { _tremove(pcTempFileName); }

        if (sTempFileName.st_size < sFileName.st_size)
            {
            HANDLE          hFile = NULL;
            FILETIME        ftCreationTime, ftLastAccessTime, ftLastWriteTime;
            BOOL            bRetVal = FALSE;

            if (INVALID_HANDLE_VALUE != (hFile = CreateFile(_bstr_t(pcFileName),
                            GENERIC_READ, 0, NULL,
                            OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL)))
                {
                bRetVal = GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
                CloseHandle(hFile);
                }

            remove(pcFileName);
            rename(_bstr_t(pcTempFileName), pcFileName);

            if (INVALID_HANDLE_VALUE != (hFile = CreateFile(_bstr_t(pcFileName),
                            GENERIC_WRITE, 0, NULL,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
                {
                bRetVal = SetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
                CloseHandle(hFile);
                }
            }
        else
            {
            _tremove(pcTempFileName);
            }

        return 1;
        }
    
    return 0;
}

// --------------------------------
