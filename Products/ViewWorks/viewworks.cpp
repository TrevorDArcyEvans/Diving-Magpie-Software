//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: ViewWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#define     MAIN        1

#include "About.h"
#include "ExampleApp.h"
#include "StripInfo.h"
#include "Register.h"
#include "SldWorks.h"
#include "ViewWorks.h"
#include "unfrag.h"
#include "WinUtil.h"
#include "utils.h"
#include <comdef.h>
#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
CViewWorksApp* TheApplication = NULL;

static AFX_EXTENSION_MODULE ViewWorksDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
if (dwReason == DLL_PROCESS_ATTACH)
    {
    TRACE0("ViewWorks.DLL Initializing!\n");

    // Extension DLL one-time initialization
    AfxInitExtensionModule(ViewWorksDLL, hInstance);

    // Insert this DLL into the resource chain
    new CDynLinkLibrary(ViewWorksDLL);

    }
else if (dwReason == DLL_PROCESS_DETACH)
    {
    TRACE0("ViewWorks.DLL Terminating!\n");

    // shut down the sample application
    TheApplication->TerminateApplication();
    delete TheApplication;

    // Terminate the library before destructors are called
    AfxTermExtensionModule(ViewWorksDLL);
    }
return 1;   // ok
}

// --------------------------------
//  connections to SolidWorks
// --------------------------------

#define DllExport __declspec( dllexport )

// this is the function SolidWorks calls to connect
// to the add-in application

long DllExport InitUserDLL3(LPSLDWORKS pSldWorks)
{
// this function should be called once per session
if ( TheApplication != NULL )
    {
    ASSERT ( FALSE );
    return 0;
    }

long        DateCode;

pSldWorks->DateCode(&DateCode);
// need > 1999250 for SldWorks::OpenDoc2
if (DateCode < 1999250)
    {
    MessageBox(NULL, _T("Sorry -\nthis requires SolidWorks 1999250 or higher."),
        VIEW_WORKS_TITLE, MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
    return -1;
    }

// start the application
TheApplication = new CViewWorksApp(pSldWorks);
if (!TheApplication->StartApplication())
    return 0;

// initially set addin to unregistered &
// reset save counter
g_bRegistered = false;
g_nViewSaveCount = 0;

TCHAR   CodeUStr[_MAX_PATH];
char    CodeStr [_MAX_PATH];

GetPrivateProfileString(
        VIEW_WORKS_INI_FILE_SECTION,
        VIEW_WORKS_INI_FILE_KEY,
        _T("SolidPartners"), // points to default string
        CodeUStr, // points to destination buffer
        _MAX_PATH,        // size of destination buffer
        VIEW_WORKS_INI_FILE_NAME);

wu_strcpy(CodeStr, ::CString(CodeUStr));

char    MachineID[_MAX_PATH];
strcpy(MachineID, GetMachineID());

if (CheckCode(MachineID, (char *) LPCTSTR(VIEW_WORKS_TITLE_CODE), CodeStr) == true)
    {
    // disable menu item
    g_bRegistered = TRUE;
    }

// connected successfully
return 1;
}

// --------------------------------

// document callbacks

void DllExport VW_SaveAsView(LPTSTR FileName, LPSLDWORKS pSolidWorks)
/* -----------------------------------------------
SldWorks::AddFileSaveAsItem
The format of the FileName argument is:

	<FullPath > <FileName> <AccessType>

where:

FullPath is the file name with full path information,
FileName is the file name and extension (without separator),
AccessType is w or r

TDE
NB: the FileName argument appears to be all in upper case
----------------------------------------------- */
{
g_nViewSaveCount++;

if (g_nViewSaveCount > MAX_UNREG_VIEW_SAVES &&
    FALSE == g_bRegistered)
    {
    MessageBox(NULL, _T("Unregistered save limit reached."), VIEW_WORKS_TITLE,
        MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);

    return;
    }

HRESULT     res;
long        retval;

LPMODELDOC  pModelDoc = NULL;
res = pSolidWorks->get_IActiveDoc(&pModelDoc);

if (pModelDoc != NULL)
    {
    CString         cstrViewFileName(FileName);

    TCHAR           strViewFileExt[MAX_PATH],
                    strSWFileExt  [MAX_PATH];

    cstrViewFileName.MakeUpper();

    // get the document type
	long    doctype;
	res = pModelDoc->GetType(&doctype);

    switch (doctype)
        {
        case    swDocPART       :
            _tcscpy(strViewFileExt, _T(".VEWPRT"));
            _tcscpy(strSWFileExt  , _T(".sldprt"));
            break;

        case    swDocASSEMBLY   :
            _tcscpy(strViewFileExt, _T(".VEWASM"));

            break;

        case    swDocDRAWING    :
            _tcscpy(strViewFileExt, _T(".VEWDRW"));
            _tcscpy(strSWFileExt  , _T(".slddrw"));
            break;

        default                 :
            break;
        }

    // truncate string at full path including extn
    int         nExtLoc = cstrViewFileName.Find(strViewFileExt);
    cstrViewFileName.Delete(nExtLoc + _tcslen(strViewFileExt),
        cstrViewFileName.GetLength() - nExtLoc - _tcslen(strViewFileExt));

    // get temporary directory & file
    TCHAR   strTempFileDir  [MAX_PATH],
            strTempFileName [MAX_PATH];

    GetTempPath(sizeof(strTempFileDir), strTempFileDir);
    GetTempFileName(strTempFileDir, _T("ViewWks"), 1, strTempFileName);

    // strip off .tmp extension
    strTempFileName[_tcslen(strTempFileName) - 4] = '\0';

    CString cstrTempFileName = CString(strTempFileName);

    // add SolidWorks extension for document type
    cstrTempFileName += strSWFileExt;

    // if view file already exists
    WIN32_FIND_DATA         FindFileData;
    if (INVALID_HANDLE_VALUE != FindFirstFile(cstrViewFileName, &FindFileData))
        {
        CString    cstrMsg;

        cstrMsg.Format(_T("File %s already exists.\nChoose another name."), cstrViewFileName);
        MessageBox(NULL, cstrMsg, _T("Error!"),
            MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
        }
    else
        {
        // save document into the temporary file
        pModelDoc->SaveAs2(_bstr_t(strTempFileName), 0, TRUE, TRUE, &retval);

        _trename(cstrTempFileName, cstrViewFileName);

        VW_MakeViewFile(_bstr_t(cstrViewFileName));
        VW_Unfrag(1, _bstr_t(cstrViewFileName));
        }

    // cleanup
    pModelDoc->Release();
    }

return;
}
// --------------------------------
void DllExport VW_OpenView(LPTSTR FileName, LPSLDWORKS pSolidWorks)
/* -----------------------------------------------
SldWorks::AddFileOpenItem
The format of the FileName argument is:

	<FullPath > <FileName> <AccessType>

where:

FullPath is the file name with full path information,
FileName is the file name and extension (without separator),
AccessType is w or r

----------------------------------------------- */
{
CString         cstrFileName(FileName);
TCHAR           strTempFileDir  [MAX_PATH],
                strTempFileName [MAX_PATH];

char            strSWFileExt    [MAX_PATH],
                strFileName     [MAX_PATH];

long            posn = 0,
                doctype = swDocNONE;

cstrFileName.MakeUpper();

// determine filetype based on extension
if (-1 != cstrFileName.Find(_T(".VEWPRT")))
    {
    posn = cstrFileName.Find(_T(".VEWPRT"));
    strcpy(strSWFileExt  , (".sldprt"));
    doctype = swDocPART;
    }

if (-1 != cstrFileName.Find(_T(".VEWASM")))
    {
    posn = cstrFileName.Find(_T(".VEWASM"));
    strcpy(strSWFileExt  , (".sldasm"));
    doctype = swDocASSEMBLY;
    }

if (-1 != cstrFileName.Find(_T(".VEWDRW")))
    {
    posn = cstrFileName.Find(_T(".VEWDRW"));
    strcpy(strSWFileExt  , (".slddrw"));
    doctype = swDocDRAWING;
    }

// abort if we can't determine the document type
if (0 == posn)
    {
    return;
    }

cstrFileName.Delete(posn + 7, cstrFileName.GetLength() - posn - 7);
wu_strcpy(strFileName, cstrFileName);

// get temporary directory & file
GetTempPath(MAX_PATH, strTempFileDir);
GetTempFileName(strTempFileDir, _T("ViewWks"), 1, strTempFileName);

// strip off .tmp extension
strTempFileName[_tcslen(strTempFileName) - 4] = '\0';

CString cstrTempFileName = CString(strTempFileName);

// add SolidWorks extension for document type
cstrTempFileName += strSWFileExt;

CopyFile(::CString(strFileName), cstrTempFileName, false);
// TDE  remember to delete temporary file when this one is closed

LPMODELDOC      pModelDoc = NULL;
long            errors = 0;
char            cViewFileName[MAX_PATH];

wu_strcpy(cViewFileName, cstrTempFileName);

TheApplication->GetSWApp()->IOpenDoc2(_bstr_t(cViewFileName), doctype,
    true, true, true, &errors, &pModelDoc);
if (pModelDoc)
    {
    pModelDoc->Release();
    }
}
// --------------------------------
void DllExport VW_Help(void)
{
WinExec("winhlp32 C:\\Program Files\\SolidPartners\\ViewWorks\\ViewWorks.hlp"
    , SW_NORMAL);
}
// --------------------------------
void DllExport VW_Register(void)
{
// Save the current resource handle
HINSTANCE hSaveResource = AfxGetResourceHandle();

HINSTANCE VW_ResourceHandle = GetModuleHandle(VW_DLL_NAME);

// Switch to the Application resources
AfxSetResourceHandle(VW_ResourceHandle);

CRegister   dlg;

dlg.DoModal();

// Reset to previous resource handle
AfxSetResourceHandle(hSaveResource);

return;
}
// --------------------------------
int DllExport VW_RegisterUpdate(void)
{
#if 0
return 0;  	// If you want the menu item to be unchecked and disabled (grayed out)
return 1;  	// If you want the menu item to be unchecked and enabled
return 2;  	// If you want the menu item to be checked and disabled (grayed out)
return 3; 	// If you want the menu item to be checked and enabled
#endif

return (TRUE == g_bRegistered) ? 0 : 1;
}
// --------------------------------
void DllExport VW_About(void)
{
// Save the current resource handle
HINSTANCE   hSaveResource = AfxGetResourceHandle();

HINSTANCE   VW_ResourceHandle = GetModuleHandle(VW_DLL_NAME);

// Switch to the Application resources
AfxSetResourceHandle(VW_ResourceHandle);

CAbout      dlg;

dlg.DoModal();

// Reset to previous resource handle
AfxSetResourceHandle(hSaveResource);

return;
}
// --------------------------------
//  End of ViewWorks.cpp
// --------------------------------

