#include <vcl\vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("Install.cpp", InstForm);
USERES("InstallZip.res");
USERC("ZipMsgUS.rc");

//---------------------------------------------------------------------------
WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	try {
		Application->Initialize();
		Application->CreateForm( __classid( TMainForm ), &MainForm );
		Application->Run();
	} catch ( Exception &exception ) {
		Application->ShowException( &exception );
	}
	return 0;
}
//---------------------------------------------------------------------------

