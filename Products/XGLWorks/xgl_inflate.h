// XGL_InflateDlg.h : header file
//

#if !defined(AFX_XGL_INFLATEDLG_H__A739AE2C_D98B_11D4_8EA0_0020AFCC5695__INCLUDED_)
#define AFX_XGL_INFLATEDLG_H__A739AE2C_D98B_11D4_8EA0_0020AFCC5695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------------------------
int
Inflate_Zlib_File
(
    const TCHAR*            Input_FileName,
    const TCHAR*            Output_FileName,
    TCHAR*                  ErrorString
);
//------------------------------------------------------------------------

#endif // !defined(AFX_XGL_INFLATEDLG_H__A739AE2C_D98B_11D4_8EA0_0020AFCC5695__INCLUDED_)
