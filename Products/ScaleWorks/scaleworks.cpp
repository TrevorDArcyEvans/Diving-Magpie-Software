//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("ScaleWorks.res");
USEFORM("main.cpp", frmScaleWorks);
USEFORM("scale.cpp", frmScale);
USEUNIT("DMS_Comm_TLB.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "ScaleWorks v1.0";
         Application->HelpFile = "ScaleWks.hlp";
         Application->CreateForm(__classid(TfrmScaleWorks), &frmScaleWorks);
         Application->CreateForm(__classid(TfrmScale), &frmScale);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
