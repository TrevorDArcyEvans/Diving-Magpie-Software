//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DMS_PDFWorks_test.res");
USEFORM("Unit1.cpp", Form1);
USEUNIT("DMS_PDFWks_TLB.cpp");
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
