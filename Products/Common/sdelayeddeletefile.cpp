// SDelayedDeleteFile.cpp: implementation of the SDelayedDeleteFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SDelayedDeleteFile.h"
#include "shlwapi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//--------------------------------------------------------
// local function prototype
DWORD WINAPI DelayedDeleteFile(LPVOID lpParameter);
//--------------------------------------------------------

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------
// SDelayedDeleteFile::DelayedDelete
// static method to delete a file after a specified timeout
//
// the deletion is done is a separate thread so a call to this function
// does not block
//
// parameters
//      FileName
//          fully qualified path to file to delete
//
//      Seconds
//          time in seconds to wait before deleting file
//
//          default value is 30 seconds
//
//      ForceDelete
//          true if we want to override any read-only attributes
//
//          default value is false ie don't delete read-only,
//          hidden or system files
//
// notes
//      no error is communicated back to the caller if deletion of the file
//      was not successful - beware!
void SDelayedDeleteFile::DelayedDeleteFile
(
    CString             FileName,
    int                 Seconds,
    bool                ForceDelete
)
{
    HANDLE                  hProc;
    DWORD                   dwThreadID;
    DelayedDeleteInfo*      Info = new DelayedDeleteInfo;

    Info->FileName      = FileName;
    Info->Seconds       = Seconds;
    Info->ForceDelete   = ForceDelete;

    hProc = CreateThread(
                NULL,
                0,
                ::DelayedDeleteFile,
                (LPVOID) Info,
                0, // run immediately
                &dwThreadID);

    CloseHandle(hProc);
}
//--------------------------------------------------------
DWORD WINAPI DelayedDeleteFile(LPVOID lpParameter)
{
    try
        {
        SDelayedDeleteFile::DelayedDeleteInfo*      Info;

        CString                     FileName;
        int                         Seconds;
        bool                        ForceDelete;
        DWORD                       FileAttributes;

        // reconstitute data
        Info = (SDelayedDeleteFile::DelayedDeleteInfo *) lpParameter;

        FileName    = Info->FileName;
        Seconds     = Info->Seconds;
        ForceDelete = Info->ForceDelete ;

        // no longer needed, so get rid of memory allocated by our creator
        delete Info;

        if (PathFileExists(FileName))
            {
            Sleep(1000 * Seconds);

            if (ForceDelete)
                {
                FileAttributes = GetFileAttributes(FileName);

                // clear all attributes which prevent us from
                // deleting the file
                FileAttributes &= ~FILE_ATTRIBUTE_HIDDEN;
                FileAttributes &= ~FILE_ATTRIBUTE_READONLY;
                FileAttributes &= ~FILE_ATTRIBUTE_SYSTEM;

                SetFileAttributes(FileName, FileAttributes);
                }

            DeleteFile(FileName);
            }
        }
    catch (...)
        {
        }
    return 0;
}
//--------------------------------------------------------
