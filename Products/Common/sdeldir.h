// SDelDir.h: interface for the SDelDir class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDELDIR_H__B4F3E380_5D49_11D4_83C9_00104BB2580C__INCLUDED_)
#define AFX_SDELDIR_H__B4F3E380_5D49_11D4_83C9_00104BB2580C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MFCString.h"
#include "MFCStringImpl.h"

class SDelDir  
{
private:
    // file mask to delete files in dirs which match the filemask
    // defaults to *.* ie delete everything
    NotMFC::CString         m_FileMask;

    // whether to delete sub directories
    // defaults to true ie delete sub dirs
    bool                    m_SubDirs;

public:
    SDelDir();
    SDelDir
        (
            NotMFC::CString         sFileMask,
            bool                    bDeleteSubDirs
        );

    virtual ~SDelDir();

// helper functions
    SetFileMask
        (
            NotMFC::CString         sFileMask
        );
    NotMFC::CString GetFileMask();

    SetSubDirs
        (
            bool            bDeleteSubDirs
        );
    bool GetSubDirs();

// main function to do all the work
    bool DeleteDirectory(NotMFC::CString path);

};

#endif // !defined(AFX_SDELDIR_H__B4F3E380_5D49_11D4_83C9_00104BB2580C__INCLUDED_)
