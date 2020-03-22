//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("PwrWorks.res");
USEFORM("main.cpp", frmMain);
USEFORM("about.cpp", frmAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "PowerWorks v1.0";
        Application->CreateForm(__classid(TfrmMain), &frmMain);
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
