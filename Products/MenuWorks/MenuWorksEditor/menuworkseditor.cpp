//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("MenuWorksEditor.res");
USEFORM("main.cpp", frmMain);
USEUNIT("utils.cpp");
USEUNIT("crc_32.cpp");
USEUNIT("enable.cpp");
USEUNIT("read.cpp");
USEUNIT("write.cpp");
USEUNIT("browse.cpp");
USEFORM("about.cpp", frmAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "MenuWorks Editor";
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



