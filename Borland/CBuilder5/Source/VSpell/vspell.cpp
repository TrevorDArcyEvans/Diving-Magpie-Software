//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("VSpell.res");
USEPACKAGE("vcl40.bpi");
USEUNIT("..\..\Imports\VSpell\VspelocxLib_OCX.cpp");
USERES("..\..\imports\vspell\VspelocxLib_OCX.dcr");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Package source.
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
//---------------------------------------------------------------------------
