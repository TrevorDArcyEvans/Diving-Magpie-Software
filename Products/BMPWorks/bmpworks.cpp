// BMPWorks.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "BMPWorks.h"
#include "Dlg_Files.h"
#include "Resource.h"

#include <comdef.h>
#include <assert.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CBMPWorksApp

BEGIN_MESSAGE_MAP(CBMPWorksApp, CWinApp)
	//{{AFX_MSG_MAP(CBMPWorksApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBMPWorksApp construction

CBMPWorksApp::CBMPWorksApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBMPWorksApp object

CBMPWorksApp theApp;



//---------------------------------------------------------------------

#ifndef DllExport
#define DllExport __declspec( dllexport )
#endif

//---------------------------------------------------------------------

DllExport   void    CALLBACK
Copy_SW_Bitmap_to_Clipboard(
    HWND        hwnd            ,
    HINSTANCE   hinst           ,
    LPTSTR      *strFileName    ,
    int         nCmdShow        )
{
///////////////////////////////////////////////////////
/* ---------------------------------
NOTE:   this only seems to occure _without_ MFC
        when using MFC, everything is OK...

ugly hacks to get around Windows shell problem:

when the dll is run from a command line:

    rundll32 bmpworks.dll,Copy_SW_Bitmap_to_Clipboard v:\sprinkler.slddrw

everything works perfectly.  In particular, the strFileName parameter
is passed in as:

    v:\sprinkler.slddrw

Note the long filename is preserved and there are no quotes around the
filename.

The following registry entry puts this functionality on the
RMB of Windows explorer:

----------------- 8< -----------------

REGEDIT4

[HKEY_CLASSES_ROOT\SldDraw.Document\shell\Copy &bitmap]

[HKEY_CLASSES_ROOT\SldDraw.Document\shell\Copy &bitmap\command]
@="rundll32.exe BMPWorks,Copy_SW_Bitmap_to_Clipboard \"%1\""

----------------- 8< -----------------

However, when trying to run from the RMB of Windows explorer,
the strFileName parameter is passed in as:

    "v:\sprink~1.sld"

Note that the filename is now in 8.3 format and is enclosed in quotes!
As a result, the file cannot be opened.

It is not correct to use FindFirstFile() because, when
wildcards are added, this will not result in a unique file eg

    press.sldprt
    press.slddrw
    press2.sldprt
    press2.slddrw
    etc

The only solution would appear to be to use GetLongPathName()
but this is only available in NT5 or W98.

Thus, for the moment, we a snookered by MS :-((

--------------------------------- */

// end ugly hacks
///////////////////////////////////////////////////////


AFX_MANAGE_STATE(AfxGetStaticModuleState());

IStorage*       pRoot;
IStream*        pPreview;

char    pcFileName[_MAX_PATH];

strcpy(pcFileName, (const char *) strFileName);

CDlg_Files  dlg;

dlg.m_cstrFileName = pcFileName;
if (IDOK == dlg.DoModal())
    {
    strcpy(pcFileName, dlg.m_cstrFileName);
    }
else
    {
    return;
    }

if (S_OK == StgOpenStorage(_bstr_t(pcFileName), NULL,
                STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                NULL, 0, &pRoot))
    {
    if (S_OK == pRoot->OpenStream(_bstr_t("Preview"),
                    NULL,
                    STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                    0, &pPreview))
        {
        DWORD DataSize = 0;
        DWORD numRead = 0;
        pPreview->Read(&DataSize, sizeof(DWORD), &numRead);
        if (DataSize > 0)
            {
            char* dibData = new char[DataSize];
            pPreview->Read(dibData, DataSize, &numRead);
            assert(numRead == DataSize);

            LPBITMAPINFOHEADER DIBData = (LPBITMAPINFOHEADER ) dibData;

            DWORD dwLen = DIBData->biSize + (1 << DIBData->biBitCount) * sizeof(RGBQUAD);

            HBITMAP     hBitmap;
            hBitmap = CreateDIBitmap(
                        GetDC(NULL),
                        DIBData,
                        CBM_INIT,
                        DIBData,      // pointer to initialization data
                        (LPBITMAPINFO ) DIBData,  // pointer to bitmap color-format data
                        DIB_RGB_COLORS);

            if (OpenClipboard(NULL))
                {
                EmptyClipboard();
                SetClipboardData(CF_BITMAP, hBitmap);
                CloseClipboard();
                }

            #if 0
            int numLines = StretchDIBits(
                    (HDC ) hDisplay,
                    0, 0, DIBData->biWidth, DIBData->biHeight,
                    0, 0, DIBData->biWidth, DIBData->biHeight,
                    (LPSTR ) DIBData + dwLen,   // address of bitmap bits
                    (LPBITMAPINFO ) DIBData,    // address of bitmap data
                    DIB_RGB_COLORS, SRCCOPY);
            #endif

            delete dibData;
            }

        pPreview->Release();
        }
    pRoot->Release();
    }
#if 0
else
    {
    char    pcError[2 * _MAX_PATH];
    sprintf(pcError, "Couldn't find file: %s", pcFileName);
    MessageBox(NULL, pcError, "Error!", MB_OK | MB_ICONERROR);
    }
#endif
}

//---------------------------------------------------------------------

