//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\registry.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be perfomring new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmMain);
USERES("WinWks.res");
//---------------------------------------------------------------------------
#include "main.h"
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
//---------------------------------------------------------------------------
#define DllExport __declspec( dllexport )

#define WIN_WKS_REG_KEY     "SOFTWARE\\SolidPartners\\WinWks"
//---------------------------------------------------------------------------
void FormLoadSize(TfrmMain *frmMain)
{
TRegistry       *AppReg = new TRegistry;
int             iLeft   ,
                iTop    ,
                iHeight ,
                iWidth  ;

AppReg->RootKey = HKEY_LOCAL_MACHINE;
if (AppReg->OpenKey(WIN_WKS_REG_KEY, false) == true)
	{
	try
		{
		iLeft   = AppReg->ReadInteger("Left"    );
		iTop    = AppReg->ReadInteger("Top"     );
		iHeight = AppReg->ReadInteger("Height"  );
		iWidth  = AppReg->ReadInteger("Width"   );

		frmMain->Left   = iLeft;
		frmMain->Top    = iTop;
		frmMain->Height = iHeight;
		frmMain->Width  = iWidth;
		}
	catch(...)
		{
		MessageBox(NULL, "Error reading from registry",
            WINDOW_WORKS_TITLE, MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
		}
	}
delete AppReg;
}
//---------------------------------------------------------------------------
void FormSaveSize(TfrmMain *frmMain)
{
TRegistry       *AppReg = new TRegistry;

AppReg->RootKey = HKEY_LOCAL_MACHINE;
AppReg->OpenKey(WIN_WKS_REG_KEY, true);

AppReg->WriteInteger("Left"     , frmMain->Left     );
AppReg->WriteInteger("Top"      , frmMain->Top      );
AppReg->WriteInteger("Height"   , frmMain->Height   );
AppReg->WriteInteger("Width"    , frmMain->Width    );

delete AppReg;
}
//---------------------------------------------------------------------------
extern "C"  bool WINAPI __declspec(dllexport) WW_CloseAll(void)
{
int         nRetVal;
TfrmMain    *WW_CloseAllDialog = new TfrmMain(NULL);
TIcon       *WinWksIcon = new TIcon();

WinWksIcon->Handle = LoadIcon(HInstance, "WINWKS");
WW_CloseAllDialog->Icon = WinWksIcon;

FormLoadSize(WW_CloseAllDialog);

WW_CloseAllDialog->ShowModal();

FormSaveSize(WW_CloseAllDialog);

nRetVal = WW_CloseAllDialog->ModalResult;

delete WW_CloseAllDialog;
delete WinWksIcon;

return ((mrOk == nRetVal) ? true : false);
}

//---------------------------------------------------------------------------

