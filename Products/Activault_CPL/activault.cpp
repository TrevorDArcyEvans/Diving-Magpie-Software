//---------------------------------------------------------------------------
#include <vcl.h>
#include <cpl.h> // Control Panel applet definitions
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
USERES("Activault.res");
//---------------------------------------------------------------------------
HINSTANCE       OurInstance;
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
// Remember our instance, so we can get to our DLL resources
if (reason == DLL_PROCESS_ATTACH)
    {
    OurInstance = hinst;
    }
return 1;
}
//---------------------------------------------------------------------------
// The Control Panel will do all calling through this function
extern "C" int __stdcall __declspec(dllexport)
    CPlApplet(
        HWND        HwControlPanel,
        int         Msg,
        int         lParam1,
        int         lParam2)
{
// have to put this here to get around BCB compiler error/bug
NEWCPLINFO       *Info = (NEWCPLINFO *) lParam2;

switch (Msg)
    {
    case CPL_INIT:
        // Return "succesful initialization"
        return true;

    case CPL_GETCOUNT:
        // This DLL contains 1 applet
        return 1;

    case CPL_NEWINQUIRE:
       // Control Panel asks for display information
       ZeroMemory(Info, sizeof(NEWCPLINFO));
       Info->dwSize = sizeof(NEWCPLINFO);

       // Icon is specified under Options/Project/Applications, as usual
       Info->hIcon = LoadIcon(HInstance, "MAINICON");
       strcpy(Info->szName, "Activault");
       strcpy(Info->szInfo, "Activault control panel");
       return 0;

    case CPL_DBLCLK:
        // Time to show our form!!!
        try
            {
            Application->Initialize();
            Application->CreateForm(__classid(TfrmMain), &frmMain);
            Application->Run();
            }
        catch (Exception &exception)
            {
            Application->ShowException(&exception);
            }
        return 0;

    default :
        return 0;
    }
}
//---------------------------------------------------------------------------

