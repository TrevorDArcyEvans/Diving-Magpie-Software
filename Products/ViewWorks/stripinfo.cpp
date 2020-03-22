#include <stdafx.h>
#include <comdef.h>
#include "StripInfo.h"

//---------------------------------------------

void VW_MakeViewFile(char     *pcSWFileName)
{
// save time stamp of file
HANDLE          hFile = NULL;
FILETIME        ftCreationTime, ftLastAccessTime, ftLastWriteTime;
BOOL            bRetVal = FALSE;

if (INVALID_HANDLE_VALUE != (hFile = CreateFile(_bstr_t(pcSWFileName),
                GENERIC_READ, 0, NULL,
                OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL)))
    {
    bRetVal = GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    CloseHandle(hFile);
    }


HRESULT         hr;
IStorage*       pRoot;
IStorage*       pContents;

if (S_OK == (hr = ::StgOpenStorage(_bstr_t(pcSWFileName), NULL,
                STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                NULL, 0, &pRoot)))
    {
    if (S_OK != pRoot->DestroyElement(_bstr_t("Header")))
        {
        #if 0
        MessageBox(NULL, _T("failed to remove: Header"), _T("Error!"),
             MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
        #endif
        }

    if (S_OK != pRoot->DestroyElement(_bstr_t("ThirdPty")))
        {
        #if 0
        MessageBox(NULL, _T("failed to remove: ThirdPty"), _T("Error!"),
             MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
        #endif
        }

    if (S_OK != pRoot->DestroyElement(_bstr_t("Embedding 1")))
        {
        #if 0
        MessageBox(NULL, _T("failed to remove: Embedding 1"), _T("Error!"),
             MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
        #endif
        }


    // ugly hack to remove the "SummaryInformation" and
    // "DocumentSummaryInformation" elements
    // I think these element names are in Unicode :-(
    IEnumSTATSTG*   pEnum;
    IMalloc*        pMalloc;
    STATSTG         statstg;

    CoGetMalloc(MEMCTX_TASK, &pMalloc);
    pRoot->EnumElements(0, NULL, 0, &pEnum);

    while (pEnum->Next(1, &statstg, NULL) == NOERROR)
        {
        if (statstg.type == STGTY_STREAM)
            {
            if (NULL != _tcsstr(::CString(statstg.pwcsName), _T("SummaryInformation")))
                {
                if (S_OK != pRoot->DestroyElement(statstg.pwcsName))
                    {
                    #if 0
                    CString     cstrMsg;
                    cstrMsg.Format(_T("failed to remove: %s"), statstg.pwcsName);
                    MessageBox(NULL, cstrMsg, _T("Error!"),
                        MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                    #endif
                    }
                }
            }
        pMalloc->Free(statstg.pwcsName);
        }
    pMalloc->Release();
    pEnum->Release();


    if (S_OK == pRoot->OpenStorage(_bstr_t("Contents"), NULL,
        STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, NULL, 0, &pContents))
        {
        if (NULL != pContents)
            {
            if (S_OK != pContents->DestroyElement(_bstr_t("Config-0")))
                {
                #if 0
                MessageBox(NULL, _T("failed to remove: Config-0"), _T("Error!"),
                     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                #endif
                }

            if (S_OK != pContents->DestroyElement(_bstr_t("CMgr")))
                {
                #if 0
                MessageBox(NULL, _T("failed to remove: CMgr"), _T("Error!"),
                     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                #endif
                }

            if (S_OK != pContents->DestroyElement(_bstr_t("OleItems")))
                {
                #if 0
                MessageBox(NULL, _T("failed to remove: OleItems"), _T("Error!"),
                     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                #endif
                }

            if (S_OK != pContents->DestroyElement(_bstr_t("Config-33")))
                {
                #if 0
                MessageBox(NULL, _T("failed to remove: Config-33"), _T("Error!"),
                     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                #endif
                }

            if (S_OK != pContents->DestroyElement(_bstr_t("Definition")))
                {
                #if 0
                MessageBox(NULL, _T("failed to remove: Definition"), _T("Error!"),
                     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                #endif
                }

            if (S_OK != pContents->DestroyElement(_bstr_t("Config-33-Body__Zip")))
                {
                #if 0
                MessageBox(NULL, _T("failed to remove: Config-33-Body__Zip"), _T("Error!"),
                     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                #endif
                }

            pContents->Release();
            }
        }

    pRoot->Release();
    }


// restore time stamp of file
if (INVALID_HANDLE_VALUE != (hFile = CreateFile(_bstr_t(pcSWFileName),
                GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
    {
    bRetVal = SetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    CloseHandle(hFile);
    }

return;
}

//---------------------------------------------

