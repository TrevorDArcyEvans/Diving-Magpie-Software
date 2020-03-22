#include <vcl.h>
#pragma hdrstop

#include <Windows.h>
#include <ObjBase.h>
#include <stdio.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <tchar.h>

#include "about.h"
#include "config.h"
#include "SWutils.h"
#include "unfrag.h"
#include "UnfragFile.h"
#include "utils.h"

//-----------------------------------------------
void	RemovePreview(
                    int         nTimeOut    ,
                    char        *pcFileName )
/* ******************************************
parameters:
    nTimeOut        number of seconds to wait for file to
                    become available
    pcFileName      name of file to unfrag
returns:
    void
notes:
    timestamp is preserved
    file size is not altered
****************************************** */
{
HRESULT             hr;

BSTR                bstrFileName = ::WideString(pcFileName).c_bstr();

// only proceed if the file is an OLE compound doc file
if (FAILED(StgIsStorageFile(bstrFileName))) { return; }


DWORD               dwOldFileAttr;
DWORD               dwNewFileAttr;

// save the file attributes
dwOldFileAttr = GetFileAttributes(pcFileName);
dwNewFileAttr = dwOldFileAttr;

// turn off read-only bit for file
dwNewFileAttr &= ~FILE_ATTRIBUTE_READONLY;
if (false == SetFileAttributes(pcFileName, dwNewFileAttr)) { return; }


// get file info
HANDLE              hFile = NULL;
FILETIME            ftCreationTime, ftLastAccessTime, ftLastWriteTime;
BOOL                bRetVal = FALSE;

// open file
if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcFileName,
                GENERIC_READ, 0, NULL,
                OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL)))
    {
    // get file times & close
    bRetVal = GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    CloseHandle(hFile);
    }
else
    {
    return;
    }


// open file for reading
IStorage            *pRoot = NULL;

int                 nCount = 0;

// loop forever
for (;;)
    {
    hr = ::StgOpenStorage(bstrFileName, NULL,
                    STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                    NULL, 0, &pRoot);

    // until file becomes free or we timeout
    if (FAILED(hr) && nCount < nTimeOut)
        {
        Sleep(1000);
        nCount++;
        }
    else
        {
        break;
        }
    }
if (FAILED(hr)) { return; }

hr = pRoot->DestroyElement(::WideString("Preview").c_bstr());
if (FAILED(hr))
    {
    // Write error to message log?
    //MessageBox(NULL, "failed to remove: Bitmap Preview", "Unstore",
    //     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
    }

pRoot->Release();

// open file
if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcFileName,
                GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
    {
    // set file times to those of original & close
    bRetVal = SetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    CloseHandle(hFile);
    }


// restore the previous file attributes
if (false == SetFileAttributes(pcFileName, dwOldFileAttr)) { return; }
}//RemovePreview
//-----------------------------------------------
void	RemoveGeometry(
                    int         nTimeOut    ,
                    char        *pcFileName )
/* ******************************************
parameters:
    nTimeOut        number of seconds to wait for file to
                    become available
    pcFileName      name of file to unfrag
returns:
    void
notes:
    timestamp is preserved
    file size is not altered
****************************************** */
{
HRESULT             hr;

BSTR                bstrFileName = ::WideString(pcFileName).c_bstr();

// only proceed if the file is an OLE compound doc file
if (FAILED(StgIsStorageFile(bstrFileName))) { return; }


DWORD               dwOldFileAttr;
DWORD               dwNewFileAttr;

// save the file attributes
dwOldFileAttr = GetFileAttributes(pcFileName);
dwNewFileAttr = dwOldFileAttr;

// turn off read-only bit for file
dwNewFileAttr &= ~FILE_ATTRIBUTE_READONLY;


if (false == SetFileAttributes(pcFileName, dwNewFileAttr)) { return; }// get file info
HANDLE              hFile = NULL;
FILETIME            ftCreationTime, ftLastAccessTime, ftLastWriteTime;
BOOL                bRetVal = FALSE;

// open file
if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcFileName,
                GENERIC_READ, 0, NULL,
                OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL)))
    {
    // get file times & close
    bRetVal = GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    CloseHandle(hFile);
    }
else
    {
    return;
    }


// open file for reading & writing
IStorage            *pRoot     = NULL;
IStorage            *pContents = NULL;

int                 nCount = 0;

// loop forever
for (;;)
    {
    hr = ::StgOpenStorage(bstrFileName, NULL,
                    STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                    NULL, 0, &pRoot);

    // until file becomes free or we timeout
    if (FAILED(hr) && nCount < nTimeOut)
        {
        Sleep(1000);
        nCount++;
        }
    else
        {
        break;
        }
    }
if (FAILED(hr)) { return; }

hr = pRoot->OpenStorage(::WideString("Contents").c_bstr(), NULL,
        STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
        NULL, 0, &pContents);
if (SUCCEEDED(hr))
    {
    if (NULL != pContents)
        {
        hr = pContents->DestroyElement(::WideString("DisplayLists__Zip").c_bstr());
        if (FAILED(hr))
            {
            // Write error to message log?
            //MessageBox(NULL, "failed to remove: Geometry Display List", "Unstore",
            //     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
            }
        pContents->Release();
        }
    }

pRoot->Release();

// open file
if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcFileName,
                GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
    {
    // set file times to those of original & close
    bRetVal = SetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    CloseHandle(hFile);
    }

// restore the previous file attributes
if (false == SetFileAttributes(pcFileName, dwOldFileAttr)) { return; }
}//RemoveGeometry
//-----------------------------------------------
int 	UnfragFile(
                    int         nTimeOut    ,
                    char        *pcFileName )
/* ******************************************
parameters:
    nTimeOut        number of seconds to wait for file to
                    become available
    pcFileName      name of file to unfrag
returns:
    int             number of bytes saved for this file
notes:
    timestamp is preserved
****************************************** */
{
HRESULT             hr;

BSTR                bstrFileName = ::WideString(pcFileName).c_bstr();

// only proceed if the file is an OLE compound doc file
if (FAILED(StgIsStorageFile(bstrFileName))) { return 0; }

DWORD               dwOldFileAttr;
DWORD               dwNewFileAttr;

// save the file attributes
dwOldFileAttr = GetFileAttributes(pcFileName);
dwNewFileAttr = dwOldFileAttr;

// turn off read-only bit for file
dwNewFileAttr &= ~FILE_ATTRIBUTE_READONLY;
if (false == SetFileAttributes(pcFileName, dwNewFileAttr)) { return 0; }

CHAR                pcPathName      [_MAX_PATH],
                    pcTempFileName  [_MAX_PATH];

// get a temporary file name
GetTempPath(_MAX_PATH, pcPathName);
GetTempFileName(pcPathName, "tde", 0, pcTempFileName);

// open file for reading & writing
IStorage            *pIn = NULL;
IStorage            *pOut = NULL;

int                 nCount = 0;

// loop forever
for (;;)
    {
    // open existing file
    hr = ::StgOpenStorage(bstrFileName, NULL,
                    STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                    NULL, 0, &pIn);

    // until file becomes free or we timeout
    if (FAILED(hr)&& nCount < nTimeOut)
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

// open new (temporary) file
hr = ::StgCreateDocfile(
            ::WideString(pcTempFileName).c_bstr(),
            STGM_DIRECT | STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
            0, &pOut);
if (FAILED(hr)) { pIn->Release(); return 0; }

// copy over the storages to the temporary file
hr = pIn->CopyTo(0, NULL, NULL, pOut);
if (FAILED(hr)) { pIn->Release(); pOut->Release(); return 0; }

// close both existing and temporary files
pIn ->Release();
pOut->Release();

struct stat    sTempFileName, sFileName;

// get file info on existing and temporary files
if (0 != stat(pcTempFileName, &sTempFileName)) { remove(pcTempFileName); }
if (0 != stat(pcFileName    , &sFileName    )) { remove(pcTempFileName); }

int                 nBytesSaved = 0;

// if we've saved some space
if (sTempFileName.st_size < sFileName.st_size)
    {
    HANDLE          hFile = NULL;
    FILETIME        ftCreationTime, ftLastAccessTime, ftLastWriteTime;
    BOOL            bRetVal = FALSE;

    // open original file
    if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcFileName,
                    GENERIC_READ, 0, NULL,
                    OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL)))
        {
        // get file times of original file
        bRetVal = GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
        CloseHandle(hFile);
        }
    else
        {
        return 0;
        }


    // delete original file
    remove(pcFileName);

    // move temporary file to original file
    rename(pcTempFileName, pcFileName);

    // open (new) original file ie temporary file
    if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcFileName,
                    GENERIC_WRITE, 0, NULL,
                    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
        {
        // set file times to those of original
        bRetVal = SetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
        CloseHandle(hFile);

        // finally calculate our savings
        nBytesSaved = sFileName.st_size - sTempFileName.st_size;
        }
    else
        {
        return 0;
        }
    }
else
    {
    // no space saved, so remove temporary file
    remove(pcTempFileName);
    }

// restore the previous file attributes
if (false == SetFileAttributes(pcFileName, dwOldFileAttr)) { return 0; }

return nBytesSaved;
}//UnfragFile
// --------------------------------

