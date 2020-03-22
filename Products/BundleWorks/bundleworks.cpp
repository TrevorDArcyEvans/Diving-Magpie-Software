//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: BundleWorks.cpp
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
#include "BundleWorks.h"
#include "Register.h"
#include "Resource.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "WinUtil.h"
#include "utils.h"
#include <comdef.h>
#include <tchar.h>

#include "BW_Zip.h"

#include "api.h"
#include "structs.h"

/* Defines */
#ifndef MSWIN
#define MSWIN
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
CBundleWorksApp* TheApplication = NULL;

static AFX_EXTENSION_MODULE BundleWorksDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
if (dwReason == DLL_PROCESS_ATTACH)
    {
    TRACE0("BundleWorks.DLL Initializing!\n");

    // Extension DLL one-time initialization
    AfxInitExtensionModule(BundleWorksDLL, hInstance);

    // Insert this DLL into the resource chain
    new CDynLinkLibrary(BundleWorksDLL);
    }
else if (dwReason == DLL_PROCESS_DETACH)
    {
    TRACE0("BundleWorks.DLL Terminating!\n");

    // shut down the sample application
    TheApplication->TerminateApplication();
    delete TheApplication;

    // Terminate the library before destructors are called
    AfxTermExtensionModule(BundleWorksDLL);
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

// start the application
TheApplication = new CBundleWorksApp(pSldWorks);
if (!TheApplication->StartApplication())
    return 0;

// initially set addin to unregistered &
// reset save counter
g_bRegistered = false;
g_nBundleSaveCount = 0;

TCHAR   CodeUStr[_MAX_PATH];
char    CodeStr [_MAX_PATH];

GetPrivateProfileString(
        BUN_WORKS_INI_FILE_SECTION,
        BUN_WORKS_INI_FILE_KEY,
        _T("SolidPartners"), // points to default string
        CodeUStr, // points to destination buffer
        _MAX_PATH,        // size of destination buffer
        BUN_WORKS_INI_FILE_NAME);

wu_strcpy(CodeStr, ::CString(CodeUStr));

char    MachineID[_MAX_PATH];
strcpy(MachineID, GetMachineID());

// if a valid authorisation code
if (CheckCode(MachineID, (char *) LPCTSTR(BUN_WORKS_TITLE_CODE), CodeStr) == true)
    {
    // disable Register menu item
    g_bRegistered = TRUE;
    }

// connected successfully
return 1;
}

// document callbacks

// --------------------------------

void DllExport BunWks_Recurse(void)
{
TheApplication->m_bRecurse = !TheApplication->m_bRecurse;
TheApplication->SavePrefs();
}

// --------------------------------

void DllExport BunWks_DirStruct(void)
{
TheApplication->m_bDirStructure = !TheApplication->m_bDirStructure;
TheApplication->SavePrefs();
}

// --------------------------------

/* --------------------------------
return 0;      // Menu item is unchecked and disabled
return 1;    // Menu item is unchecked and enabled.
            //  This is the default menu state with
            //  if no update function is specified.
return 2;      // Menu item is checked and disabled
return 3;     // Menu item is checked and enabled
-------------------------------- */

int DllExport BunWks_RecurseUpdate(void)
{
return (TRUE == TheApplication->m_bRecurse) ? 3 : 1;
}

// --------------------------------

int DllExport BunWks_DirStructUpdate(void)
{
return (TRUE == TheApplication->m_bDirStructure) ? 3 : 1;
}

// --------------------------------

void DllExport BunWks_SaveAsZip(LPTSTR FileName, LPSLDWORKS pSolidWorks)
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
// only proceed if registered or not exceeded trial limits
if (g_nBundleSaveCount > BUN_WORKS_MAX_UNREG &&
    FALSE == g_bRegistered)
    {
    MessageBox(NULL, _T("Unregistered save limit reached."), BUN_WORKS_TITLE,
        MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);

    return;
    }


// we don't have to check for the file's existence because the user
// has already been asked to confirm overwriting an existing file
// thus we can safely overwrite any existing file
CString     cstrTempZipFileName(FileName),
            cstrZipFileName    (FileName);

// change to upper case since not interested in case of filename
cstrTempZipFileName.MakeUpper();

// if we can't find the zip extension
if (-1 == cstrTempZipFileName.Find(_T(".ZIP")))
    {
    // then add it to end
    cstrZipFileName += _T(".ZIP");
    }


long            posn = cstrTempZipFileName.Find(_T(".ZIP"));

// extract full path name from FileName parameter
cstrZipFileName.Delete(posn + 4, cstrZipFileName.GetLength() - posn - 4);


HRESULT     hres;
long        nNumDepends = 0;

LPMODELDOC  pModelDoc = NULL;
hres = pSolidWorks->get_IActiveDoc(&pModelDoc);

if (NULL == pModelDoc)
    {
    return;
    }


// get full path to current/active file
BSTR        bstrDocName;
hres = pModelDoc->GetPathName(&bstrDocName);

// get the document type
long        doctype;
hres = pModelDoc->GetType(&doctype);

// set document recurse dependencies flag based on document type
// recursions is not relevant for parts, thus only allow recursion
// for assemblies and drawings
BOOL        bRecurse = FALSE;
switch (doctype)
    {
    default                 :
    case    swDocPART       :
        bRecurse = FALSE;
        break;

    case    swDocASSEMBLY   :
    case    swDocDRAWING    :
        bRecurse = TRUE  && (TRUE == TheApplication->m_bRecurse);
        break;
    }

// first get number of dependencies
// note that recurse flag will be false for parts
hres = pModelDoc->IGetNumDependencies(bRecurse, true, &nNumDepends);

// then allocate the memory for the dependencies
BSTR        *bstrDocDepends = new BSTR[nNumDepends];

// now actually get the dependencies
hres = pModelDoc->IGetDependencies(bRecurse, true, bstrDocDepends);


// make the current document the first in our list
CString     cstrFileToAdd(bstrDocName);
char        cZipFileName[MAX_PATH],
            cFileToAdd  [MAX_PATH];

wu_strcpy(cZipFileName, cstrZipFileName);
wu_strcpy(cFileToAdd  , cstrFileToAdd  );

// we are only interested in every second file in the list since this will
// contain the full path to the file
int i = 0;

// for each file in the list of dependencies
// IMDFWI
while (2 * i + 1 <= nNumDepends + 1)
    {
    // add it to the zip archive
    // note that cFileToAdd will be the full path name to the file
    // first time through, this will be the root file
    BunWks_ZipFile(cZipFileName, cFileToAdd,
        TRUE == TheApplication->m_bDirStructure);

    // if we want to add the dependents
    // the root is the first file which has already been added,
    // the dependents are every second file after this
    if (TRUE == bRecurse)
        {
        // add each dependent file to the list to be zipped
        cstrFileToAdd = bstrDocDepends[2 * i + 1];
        wu_strcpy(cFileToAdd  , cstrFileToAdd  );

        i++;
        }
    else
        {
        break;
        }
    }

// cleanup
pModelDoc->Release();
delete bstrDocDepends;

// finally increment usage counter!
g_nBundleSaveCount++;

return;
}

// --------------------------------

void DllExport BunWks_OpenZip(LPTSTR FileName, LPSLDWORKS pSolidWorks)
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
// only proceed if registered or not exceeded trial limits
if (g_nBundleSaveCount > BUN_WORKS_MAX_UNREG &&
    FALSE == g_bRegistered)
    {
    MessageBox(NULL, _T("Unregistered save limit reached."), BUN_WORKS_TITLE,
        MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);

    return;
    }


CString         cstrTempZipFileName(FileName),
                cstrZipFileName    (FileName);

// change to upper case since not interested in case of filename
cstrTempZipFileName.MakeUpper();

// if we can't find the zip extension
if (-1 == cstrTempZipFileName.Find(_T(".ZIP")))
    {
    // so not a zip file and we return early
    return;
    }

long            posn = cstrTempZipFileName.Find(_T(".ZIP"));

// extract full path name from FileName parameter
cstrZipFileName.Delete(posn + 4, cstrZipFileName.GetLength() - posn - 4);




#define     BUN_WORKS_BCB_DLL_NAME         _T("BunWks.dll")

typedef bool (WINAPI * BUN_WKS_UNZIP)(
        char    *cZipFileName   ,
        bool    bDirStruct      ,
        char    *cFileToOpen    );


BUN_WKS_UNZIP       lpfnBun_Wks_Unzip = NULL;
HINSTANCE           hBunWksLib = NULL;

// load BCB DLL
hBunWksLib = LoadLibrary(BUN_WORKS_BCB_DLL_NAME);
if (NULL == hBunWksLib)
    {
    TCHAR       cTempStr[MAX_PATH];

    _stprintf(cTempStr, _T("Could not load %s"), BUN_WORKS_BCB_DLL_NAME);
    MessageBox(NULL, cTempStr, BUN_WORKS_TITLE,
        MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
    return;
    }

char        cZipFileName[MAX_PATH],
            cFileToOpen [MAX_PATH];
bool        bRet = false;

cFileToOpen[0] = '\0';

// load unzipper function in BCB DLL
lpfnBun_Wks_Unzip = (BUN_WKS_UNZIP ) GetProcAddress(hBunWksLib, "BunWks_Unzip");
if (NULL != lpfnBun_Wks_Unzip)
    {
    // only proceed if not exceeded trial limit or registered
    if (g_nBundleSaveCount++ <= MAX_UNREG_BUNDLE_SAVES  ||
        TRUE == g_bRegistered           )
        {
        // run BCB unzipper function to get whether to unzip and, if so,
        // which file to open
        wu_strcpy(cZipFileName, cstrZipFileName);
        bRet = lpfnBun_Wks_Unzip(cZipFileName,
                    TheApplication->m_bDirStructure,
                    cFileToOpen);
        }

    if ((MAX_UNREG_BUNDLE_SAVES + 1) == g_nBundleSaveCount  &&
        FALSE == g_bRegistered              )
        {
        TCHAR        cstrCmdLine[_MAX_PATH];

        _stprintf(cstrCmdLine, _T("BundleWorks -\nSorry, already used %d times."),
            MAX_UNREG_BUNDLE_SAVES);
        AfxMessageBox(cstrCmdLine);
        }
    }

// finished with BCB DLL, so get rid of it
FreeLibrary(hBunWksLib);

// if user decided not to unzip files
if (false == bRet)
    {
    // no more to do, so we can exit
    return;
    }

long        doctype = swDocNONE;
CString     cstrSWFileName(cFileToOpen);

// change to upper case since not interested in case of filename
cstrSWFileName.MakeUpper();

// first determine type of file to open based on extension
if (-1 != cstrSWFileName.Find(_T(".SLDPRT")))
    {
    doctype = swDocPART;
    }

if (-1 != cstrSWFileName.Find(_T(".SLDASM")))
    {
    doctype = swDocASSEMBLY;
    }

if (-1 != cstrSWFileName.Find(_T(".SLDDRW")))
    {
    doctype = swDocDRAWING;
    }

// abort if we can't determine the document type
if (swDocNONE == doctype)
    {
    return;
    }

LPMODELDOC      pModelDoc = NULL;
long            errors = 0;

// open the selected file in 'normal' mode ie as if a std SW file and
// not in ViewWorks format
TheApplication->GetSWApp()->IOpenDoc2(_bstr_t(cFileToOpen), doctype,
    false, false, true, &errors, &pModelDoc);

// cleanup
if (pModelDoc)
    {
    pModelDoc->Release();
    }

return;
}

// --------------------------------

void DllExport BunWks_Help(void)
{
WinExec("winhlp32 C:\\Program Files\\SolidPartners\\BundleWorks\\BunWorks.hlp"
    , SW_NORMAL);
}

// --------------------------------

void DllExport BunWks_Register(void)
{
// Save the current resource handle
HINSTANCE hSaveResource = AfxGetResourceHandle();

HINSTANCE VW_ResourceHandle = GetModuleHandle(_T(BUN_WORKS_DLL_NAME));

// Switch to the Application resources
AfxSetResourceHandle(VW_ResourceHandle);

CRegister   dlg;

dlg.DoModal();

// Reset to previous resource handle
AfxSetResourceHandle(hSaveResource);

return;
}

// --------------------------------

int DllExport BunWks_RegisterUpdate(void)
{
#if 0
return 0;      // If you want the menu item to be unchecked and disabled (grayed out)
return 1;      // If you want the menu item to be unchecked and enabled
return 2;      // If you want the menu item to be checked and disabled (grayed out)
return 3;      // If you want the menu item to be checked and enabled
#endif

return (TRUE == g_bRegistered) ? 0 : 1;
}

// --------------------------------

void DllExport BunWks_About(void)
{
// Save the current resource handle
HINSTANCE hSaveResource = AfxGetResourceHandle();

HINSTANCE VW_ResourceHandle = GetModuleHandle(_T(BUN_WORKS_DLL_NAME));

// Switch to the Application resources
AfxSetResourceHandle(VW_ResourceHandle);

CAbout      dlg;

dlg.DoModal();

// Reset to previous resource handle
AfxSetResourceHandle(hSaveResource);

return;
}

// --------------------------------
//  End of BundleWorks.cpp
// --------------------------------

