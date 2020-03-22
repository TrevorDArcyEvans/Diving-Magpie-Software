// Unstore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <comdef.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <tchar.h>

//------------------------------------------

HWND 	g_hWnd = NULL;

int     UnStore(TCHAR   *pcFileName);

//------------------------------------------

BOOL CALLBACK UW_EnumWindows(
                    HWND        hWnd,
                    LPARAM      lParam)
{
CHAR    cBuffer[MAX_PATH];

GetWindowText(hWnd, cBuffer, sizeof(cBuffer));

if (strstr(_strlwr(cBuffer), _strlwr("unstore.exe")))
    {
    g_hWnd = hWnd;
    return FALSE;
    }

return TRUE;
}

//------------------------------------------

int     UnStore(TCHAR   *pcFileName)
{
HRESULT         hr;
IStorage*       pRoot;
IStorage*       pContents;

if (S_OK == (hr = ::StgOpenStorage(_bstr_t(pcFileName), NULL,
                STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                NULL, 0, &pRoot)))
    {
    if (S_OK != pRoot->DestroyElement(_bstr_t("Preview")))
        {
        MessageBox(NULL, "failed to remove: Bitmap Preview", "Unstore",
             MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
        }

    if (S_OK == pRoot->OpenStorage(_bstr_t("Contents"), NULL,
        STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, NULL, 0, &pContents))
        {
        if (NULL != pContents)
            {
            if (S_OK != pContents->DestroyElement(_bstr_t("DisplayLists__Zip")))
                {
                MessageBox(NULL, "failed to remove: Geometry Display List", "Unstore",
                     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                }
            pContents->Release();
            }
        }

    pRoot->Release();
    }

return 0;
}

//------------------------------------------

int main(int argc, char* argv[])
{
EnumWindows(UW_EnumWindows, 0);
if (NULL != g_hWnd)
    {
    SetWindowPos(g_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_HIDEWINDOW);
    }

if (2 == argc)
    {
    UnStore(argv[1]);
    }

return 0;
}

// --------------------------------
