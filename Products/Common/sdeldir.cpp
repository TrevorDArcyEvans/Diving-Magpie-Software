// SDelDir.cpp: implementation of the SDelDir class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SDelDir.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SDelDir::SDelDir() :
    m_FileMask(_T("*.*")),
    m_SubDirs(true)
{

}
//------------------------------------------------------------------------
SDelDir::SDelDir
(
    NotMFC::CString         sFileMask,
    bool                    bDeleteSubDirs
)
{
    m_FileMask = sFileMask;
    m_SubDirs  = bDeleteSubDirs;
}
//------------------------------------------------------------------------
SDelDir::SetFileMask
(
    NotMFC::CString         sFileMask
)
{
    m_FileMask = sFileMask;
}
//------------------------------------------------------------------------
NotMFC::CString SDelDir::GetFileMask()
{
    return m_FileMask;
}
//------------------------------------------------------------------------
SDelDir::SetSubDirs
(
    bool            bDeleteSubDirs
)
{
    m_SubDirs  = bDeleteSubDirs;
}
//------------------------------------------------------------------------
bool SDelDir::GetSubDirs()
{
    return m_SubDirs;
}
//------------------------------------------------------------------------
SDelDir::~SDelDir()
{
}
//------------------------------------------------------------------------
// SDelDir::DeleteDirectory
// deletes the specified directory and, optionally, all sub directories
// all files matching the file mask will be deleted, regardless of their
// attributes!
//
// parameters
//      path
//          fully qualified path to top level directory to delete
//          without trailing backslash
//
// notes
//      if m_SubDirs is false, then only files in the top level directory,
//      matching m_FileMask, will be deleted.  No files in the 
//      sub directories will be deleted.
bool SDelDir::DeleteDirectory(NotMFC::CString path)
{
    WIN32_FIND_DATA         FindFileData;
    HANDLE                  hFind;
    NotMFC::CString         name;
    NotMFC::CString         sTempPath;
    DWORD                   status;

    sTempPath  = path;
    sTempPath += _T("\\");
    sTempPath += m_FileMask;

    hFind = FindFirstFile(LPCTSTR(sTempPath), &FindFileData);

    if (INVALID_HANDLE_VALUE == hFind)
        {
        return false;
        }

    do
        {
        name = path + _T("\\") + FindFileData.cFileName;

        if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY   && 
            FindFileData.cFileName[0]     != '.'                        &&
            true                          == m_SubDirs                  )
            {
            DeleteDirectory(name);
            }
        else if (FindFileData.cFileName[0] != '.')
            {
            // clear all attributes which prevent us from
            // deleting the file
            status = GetFileAttributes(LPCTSTR(name));

            status &= ~FILE_ATTRIBUTE_HIDDEN;
            status &= ~FILE_ATTRIBUTE_READONLY;
            status &= ~FILE_ATTRIBUTE_SYSTEM;

            SetFileAttributes(LPCTSTR(name), status);

            DeleteFile(LPCTSTR(name));
            }
        } while (FindNextFile(hFind, &FindFileData));

    FindClose(hFind);

    return RemoveDirectory(path);
}//SDelDir::DeleteDirectory
//------------------------------------------------------------------------
