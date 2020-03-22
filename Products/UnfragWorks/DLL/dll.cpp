// DLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <Windows.h>
#include <comdef.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <tchar.h>


// --------------------------------

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

// --------------------------------

BOOL APIENTRY   DllMain(
                    HANDLE      hModule             ,
                    DWORD       ul_reason_for_call  ,
                    LPVOID      lpReserved          )
{
    return TRUE;
}

// --------------------------------

int DLL_API     DoUnfrag(
                    int         nTimeOut    ,
                    char        *pcFileName )
{

    BSTR    bstrFileName = _bstr_t(pcFileName);

    if (S_OK == StgIsStorageFile(bstrFileName))
        {
        CHAR    pcPathName      [_MAX_PATH],
                pcTempFileName  [_MAX_PATH];

        // get a temporary file name
        GetTempPath(_MAX_PATH, pcPathName);
        GetTempFileName(pcPathName, "tde", 0, pcTempFileName);

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
        if (FAILED(hr)) { remove(pcTempFileName); return 0; }

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

        if (0 != _stat(pcTempFileName, &sTempFileName)) { remove(pcTempFileName); }
        if (0 != _stat(pcFileName    , &sFileName    )) { remove(pcTempFileName); }

        if (sTempFileName.st_size < sFileName.st_size)
            {
            remove(pcFileName);
            rename(pcTempFileName, pcFileName);
            }
        else
            {
            remove(pcTempFileName);
            }

        return 1;
        }
    
    return 0;
}

// --------------------------------
