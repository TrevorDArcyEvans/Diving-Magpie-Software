//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("CodeGen.res");
USEFORM("main.cpp", frmMain);
USEUNIT("crc_32.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "Diving Magpie Software Code Generator";
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
