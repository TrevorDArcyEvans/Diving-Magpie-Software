#include <vcl.h>
#pragma hdrstop

USERES("DiskSpanDemo.res");
USERC("ZipMsgUS.rc");

USEFORM("Message.cpp", MsgForm);
USEFORM("AddFiles.cpp", AddFile);
USEFORM("Main.cpp", MainForm);
USEFORM("ExtractFiles.cpp", Extract);

//---------------------------------------------------------------------------
WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	try {
		Application->Initialize();
		Application->Title = "Diskspan demo 6";
		Application->HintHidePause = 4000;
		Application->CreateForm( __classid( TMainForm ), &MainForm );
		Application->CreateForm( __classid( TMsgForm ), &MsgForm );
		Application->CreateForm( __classid( TAddFile ), &AddFile );
		Application->CreateForm( __classid( TExtract ), &Extract );
		Application->Run();
	}
	catch ( Exception &exception ) {
		Application->ShowException( &exception );
	}
	return 0;
}

