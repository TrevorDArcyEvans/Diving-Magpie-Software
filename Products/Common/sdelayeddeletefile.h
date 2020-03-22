// SDelayedDeleteFile.h: interface for the SDelayedDeleteFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDELAYEDDELETEFILE_H__F4F5C73F_AB3C_11D4_83E2_00104BB2580C__INCLUDED_)
#define AFX_SDELAYEDDELETEFILE_H__F4F5C73F_AB3C_11D4_83E2_00104BB2580C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SDelayedDeleteFile
{
public:
    struct DelayedDeleteInfo
        {
        CString             FileName;
        int                 Seconds;
        bool                ForceDelete;
        };

    static void DelayedDeleteFile
        (
            CString             FileName,
            int                 Seconds = 30,
            bool                ForceDelete = false
        );
};

#endif // !defined(AFX_SDELAYEDDELETEFILE_H__F4F5C73F_AB3C_11D4_83E2_00104BB2580C__INCLUDED_)
