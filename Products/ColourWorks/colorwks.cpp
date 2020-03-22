//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("ColorWks.res");
USEFORM("main.cpp", frmMain);
USEUNIT("DMS_Comm_TLB.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
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
}
//---------------------------------------------------------------------------
