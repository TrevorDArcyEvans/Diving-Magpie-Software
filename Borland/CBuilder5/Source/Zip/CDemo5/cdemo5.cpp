#include <vcl\vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USERES("CDemo5.res");
USEFORM("Main5.cpp", MainForm);
USEFORM("AddFiles.cpp", AddForm);
USERC("ZipMsgUS.rc");

//---------------------------------------------------------------------------
WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	try {
		Application->Initialize();
		Application->CreateForm( __classid( TMainForm ), &MainForm );
		Application->CreateForm( __classid( TAddForm ), &AddForm );
		Application->Run();
	} catch (Exception &exception) {
		Application->ShowException( &exception );
	}
	return 0;
}
//---------------------------------------------------------------------------

