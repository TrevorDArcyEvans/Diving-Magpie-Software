//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ViewWorks.res");
USEFORM("main.cpp", frmViewWorks);
USEUNIT("utils.cpp");
USEFORM("CodeGen.cpp", frmCodeGen);
USEUNIT("crc_32.cpp");
USEFORM("about.cpp", frmAbout);
USEUNIT("SWutils.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->HelpFile = "VWorks.hlp";
         Application->Title = "ViewWorks v1.0";
         Application->CreateForm(__classid(TfrmViewWorks), &frmViewWorks);
         Application->CreateForm(__classid(TfrmCodeGen), &frmCodeGen);
         Application->CreateForm(__classid(TfrmAbout), &frmAbout);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
