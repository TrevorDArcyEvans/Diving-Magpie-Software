//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmJoystick);
USEUNIT("process.cpp");
USEFORM("about.cpp", frmAbout);
USEUNIT("swOle.cpp");
USERES("stkworks.res");
USEUNIT("enum.cpp");
USEUNIT("init.cpp");
USEFORM("CodeGen.cpp", frmCodeGen);
USEUNIT("crc_32.cpp");
USEUNIT("utils.cpp");
//---------------------------------------------------------------------------
#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "process.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE hCurInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
		{
		Application->Initialize();
		Application->Title = "StickWorks v2.0";
        Application->CreateForm(__classid(TfrmJoystick), &frmJoystick);
        Application->CreateForm(__classid(TfrmAbout), &frmAbout);
        Application->CreateForm(__classid(TfrmCodeGen), &frmCodeGen);
        Application->Run();
		}
	catch (Exception &exception)
		{
		Application->ShowException(&exception);
		}
	return 0;
}
//---------------------------------------------------------------------------
