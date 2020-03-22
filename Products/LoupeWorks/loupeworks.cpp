//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("LoupeWorks.res");
USEFORM("main.cpp", frmMain);
USEFORM("configure.cpp", frmConfigure);
USEUNIT("DMS_Comm_TLB.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->CreateForm(__classid(TfrmConfigure), &frmConfigure);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
