//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Loupe.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("bi_install.pas");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
//---------------------------------------------------------------------------
