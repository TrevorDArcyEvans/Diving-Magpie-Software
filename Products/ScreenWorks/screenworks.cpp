#include "lupch.h"
#pragma hdrstop
#include "scrb4_SysDefs.h"
USERES("ScreenWorks.res");
USEFILE("lupch.h");
USEFORM("main.cpp", MainForm); /* TDataModule: DesignClass */
USEFORM("about.cpp", AboutForm);
USEFORM("config.cpp", ConfigForm);
USEFORM("preview.cpp", PreviewForm);
USEFORM("saver.cpp", SaverForm);
USEUNIT("SWutils.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------





