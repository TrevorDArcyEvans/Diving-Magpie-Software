//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DMS_Comm_Test.res");
USEFORM("main.cpp", Form1);
USEUNIT("DMS_Comm_TLB.cpp");
USEUNIT("DMS_Comm_OCX.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TForm1), &Form1);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
