#include <vcl\vcl.h>
#pragma hdrstop

USEFORM("uViewZip.cpp", fViewZip);
USERES("ViewZip.res");
USERC("ZipMsgUS.rc");

//---------------------------------------------------------------------------
WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	try {
		Application->Initialize();
		Application->CreateForm( __classid( TfViewZip ), &fViewZip );
		Application->Run();
	} catch ( Exception &exception ) {
		Application->ShowException( &exception );
	}
	return 0;
}

