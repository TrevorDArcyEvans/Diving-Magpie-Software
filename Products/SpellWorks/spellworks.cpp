//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("SpellWorks.res");
USEFORM("main.cpp", frmMain);
USEUNIT("utils.cpp");
USEFORM("CodeGen.cpp", frmCodeGen);
USEUNIT("crc_32.cpp");
USEUNIT("enum.cpp");
USEFORM("about.cpp", frmAbout);
//---------------------------------------------------------------------------
#include "main.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "SpellWorks";
         Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->CreateForm(__classid(TfrmCodeGen), &frmCodeGen);
         Application->CreateForm(__classid(TfrmAbout), &frmAbout);
         Application->OnActivate = frmMain->FormActivate;
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
