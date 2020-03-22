//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmPltWorks);
USERES("PltWorks.res");
USEFORM("about.cpp", frmAbout);
USEFORM("CodeGen.cpp", frmCodeGen);
USEUNIT("crc_32.cpp");
USEUNIT("utils.cpp");
USEUNIT("enum.cpp");
USEFORM("print_sel.cpp", frmPrinters);
USEFORM("errors.cpp", frmError);
USEUNIT("swutils.cpp");
USEFORM("PrintMap.cpp", frmPrintMap);
USEUNIT("print_file.cpp");
USEUNIT("FirstDraw.cpp");
USEUNIT("print_setup.cpp");
USEUNIT("open_file.cpp");
USEUNIT("print_draw.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "PlotWorks v2.0";
		Application->HelpFile = "PltWorks.hlp";
        Application->CreateForm(__classid(TfrmPltWorks), &frmPltWorks);
         Application->CreateForm(__classid(TfrmAbout), &frmAbout);
         Application->CreateForm(__classid(TfrmCodeGen), &frmCodeGen);
         Application->CreateForm(__classid(TfrmPrinters), &frmPrinters);
         Application->CreateForm(__classid(TfrmError), &frmError);
         Application->CreateForm(__classid(TfrmPrintMap), &frmPrintMap);
         Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
