#include "stdafx.h"

#include "UnfragFile.h"
//-----------------------------------------------
void    RemovePreview
(
    int         nTimeOut    ,
    char        *pcFileName 
)
{
    USES_CONVERSION;

    CComBSTR                bstrFileName(A2OLE(pcFileName));

    // only proceed if the file is an OLE compound doc file
    if (S_OK != StgIsStorageFile(bstrFileName))
        {
        return;
        }

    // open file for reading
    CComPtr <IStorage>      pRoot;

    HRESULT                 hr;

    // loop forever
    for (int nCount = 0;;)
        {
        hr = ::StgOpenStorage(bstrFileName, NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                        NULL, 0, &pRoot);

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
    if (FAILED(hr)) { return; }

    if (S_OK != pRoot->DestroyElement(A2OLE("Preview")))
        {
        // Write error to message log?
        //MessageBox(NULL, "failed to remove: Bitmap Preview", "Unstore",
        //     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
        }
}
//-----------------------------------------------
void    RemoveGeometry
(
    int         nTimeOut    ,
    char        *pcFileName 
)
{
    USES_CONVERSION;

    CComBSTR                bstrFileName(A2OLE(pcFileName));

    // only proceed if the file is an OLE compound doc file
    if (S_OK != StgIsStorageFile(bstrFileName))
        {
        return;
        }

    // open file for reading
    CComPtr <IStorage>      pRoot     = NULL;
    CComPtr <IStorage>      pContents = NULL;

    HRESULT                 hr;

    // loop forever
    for (int nCount = 0;;)
        {
        hr = ::StgOpenStorage(bstrFileName, NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                        NULL, 0, &pRoot);

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
    if (FAILED(hr)) { return; }

    if (S_OK == pRoot->OpenStorage(A2OLE("Contents"), NULL,
        STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, NULL, 0, &pContents))
        {
        if (pContents != NULL)
            {
            if (S_OK != pContents->DestroyElement(A2OLE("DisplayLists__Zip")))
                {
                // Write error to message log?
                //MessageBox(NULL, "failed to remove: Geometry Display List", "Unstore",
                //     MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
                }
            }
        }
}
//-----------------------------------------------
int     UnfragFile
(
    int         nTimeOut    ,
    char        *pcFileName 
)
/* ******************************************
parameters:
    nTimeOut        number of seconds to wait for file to
                    become available
    pcFileName      name of file to unfrag
returns:
    int             number of bytes saved for this file
****************************************** */
{
    USES_CONVERSION;

    CComBSTR                bstrFileName(A2OLE(pcFileName));

    // only proceed if the file is an OLE compound doc file
    // only proceed if the file is an OLE compound doc file
    if (S_OK != StgIsStorageFile(bstrFileName))
        {
        return 0;
        }


    DWORD                   dwOldFileAttrib,
                            dwNewFileAttrib;
    CHAR                    pcPathName      [_MAX_PATH],
                            pcTempFileName  [_MAX_PATH];

    dwOldFileAttrib = GetFileAttributes(pcFileName);
    dwNewFileAttrib = dwOldFileAttrib;

    dwNewFileAttrib &= ~FILE_ATTRIBUTE_READONLY;
    SetFileAttributes(pcFileName, dwNewFileAttrib);


    // get a temporary file name
    GetTempPath(_MAX_PATH, pcPathName);
    GetTempFileName(pcPathName, "tde", 0, pcTempFileName);

    // open file for reading
    CComPtr <IStorage>      pIn  = NULL;
    CComPtr <IStorage>      pOut = NULL;

    HRESULT                 hr;

    // loop forever
    for (int nCount = 0;;)
        {
        // open existing file
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

    // open new (temporary) file
    hr = ::StgCreateDocfile(
                A2OLE(pcTempFileName),
                STGM_DIRECT | STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
                0, &pOut);
    if (FAILED(hr)) { return 0; }

    // copy over the storages to the temporary file
    hr = pIn->CopyTo(0, NULL, NULL, pOut);
    if (FAILED(hr)) { return 0; }

    // close both existing and temporary files
    pIn .Release();
    pOut.Release();


    struct stat             sTempFileName, 
                            sFileName;

    // get file info on existing and temporary files
    if (0 != stat(pcTempFileName, &sTempFileName)) { remove(pcTempFileName); }
    if (0 != stat(pcFileName    , &sFileName    )) { remove(pcTempFileName); }

    int                     nBytesSaved = 0;

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
        }
    else
        {
        // no space saved, so remove temporary file
        remove(pcTempFileName);
        }

    SetFileAttributes(pcFileName, dwOldFileAttrib);

    return nBytesSaved;
}
// --------------------------------

