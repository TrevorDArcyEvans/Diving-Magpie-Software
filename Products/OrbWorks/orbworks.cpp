//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmOrb);
USERES("OrbWorks.res");
USEFORM("about.cpp", frmAbout);
USEUNIT("init.cpp");
USEUNIT("process.cpp");
USEUNIT("swOle.cpp");
USEUNIT("enum.cpp");
USEUNIT("orb.cpp");
USEFORM("CodeGen.cpp", frmCodeGen);
USEUNIT("crc_32.cpp");
USEUNIT("utils.cpp");
//---------------------------------------------------------------------------
#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "orb.h"
#include "process.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "OrbWorks v2.0";
        Application->CreateForm(__classid(TfrmOrb), &frmOrb);
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



