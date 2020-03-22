#include <vcl\vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Install.h"

//---------------------------------------------------------------------------
#pragma link "SortGrid"
#pragma link "Grids"
#pragma link "ZIPBuilder"

#pragma package(smart_init)
#pragma resource "*.dfm"

TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm( TComponent *Owner ) : TForm( Owner ) {
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActivate( TObject *Sender ) {
	SortGrid1->RowCount     =   2;	// First row is fixed, and used for titles.
	SortGrid1->Cells[0][0]  = "File Name";
	SortGrid1->Cells[1][0]  = "Compr Size";
	SortGrid1->Cells[2][0]  = "Uncmpr Size";
	SortGrid1->Cells[3][0]  = "Date/Time";
	SortGrid1->ColWidths[0] = 306;
	SortGrid1->ColWidths[1] =  94;
	SortGrid1->ColWidths[2] = 100;
	SortGrid1->ColWidths[3] = 120;

	/* Allowable Command Line parameters:
	 * - a zip filename = display it's contents.
	 * - /install = bring up install menu automatically.
	 * - /uninstall = do the uninstall and quit (no menu).
   */
	if ( ParamCount() >= 1 ) {
//		if ( UpperCase( ParamStr( 1 ) ) == "/REMOVE" ) {
//			Application->ShowMainForm = false;
//			KillMySelf();
//		} else {
			if ( UpperCase( ParamStr( 1 ) ) == "/INSTALL" ) {
				AutoUnInstall = false;
				InstButClick( this );		// Show install menu.
			} else {
				if ( UpperCase( ParamStr( 1 ) ) == "/UNINSTALL" ) {
					AutoUnInstall = true;
					InstButClick( this );	// Do the un-install.
				} else {
					// Someone passed us an argument that is most likely
					// the name of a zip file.
					if ( FileExists( ParamStr( 1 ) ) ) {
						ZipFName->Caption = ParamStr( 1 );
						// This assignment causes zipfile to be read:
						ZipDir1->ZipFilename = ZipFName->Caption;
						FillGrid();
					} else ShowMessage( "File not found: " + ParamStr( 1 ) );
				}
			}
//		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FillGrid( void ) {
	// Remove everything from grid except col titles.
	SortGrid1->ClearFrom( 1 );
	SortGrid1->RowCount = 2;
	if ( !ZipDir1->Count ) return;

	SortGrid1->RowCount = ZipDir1->Count + 1;
	for ( int i = 1; i <= ZipDir1->Count; i++ ) {
		ZipDirEntry *zde = (ZipDirEntry *)ZipDir1->ZipContents->Items[i - 1];
		SortGrid1->Cells[0][i] = zde->FileName;
		SortGrid1->Cells[1][i] = IntToStr( zde->CompressedSize );
		SortGrid1->Cells[2][i] = IntToStr( zde->UncompressedSize );
		SortGrid1->Cells[3][i] = FormatDateTime( "ddddd  t", FileDateToDateTime( zde->DateTime ) );
	}
	TSortOptions so;
	so.SortDirection	   = sdAscending;
	so.SortStyle		   = ssAutomatic;
	so.SortCaseSensitive = false;
	SortGrid1->SortByColumn( SortGrid1->SortColumn, so );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenButClick( TObject *Sender ) {
	// Remove everything from grid except col titles.
	SortGrid1->RowCount = 2;
	SortGrid1->Rows[1]->Clear();
	SortGrid1->ColWidths[0] = 306;
	SortGrid1->ColWidths[1] =  94;
	SortGrid1->ColWidths[2] = 100;
	SortGrid1->ColWidths[3] = 120;

	if ( MainForm->OpenDialog1->Execute() ) {
		ZipFName->Caption = OpenDialog1->FileName;
		// This assignment causes zipfile to be read:
		ZipDir1->ZipFilename = ZipFName->Caption;
		FillGrid();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CancelButClick( TObject *Sender ) {
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::InstButClick( TObject *Sender ) {
	TInstForm *InstForm = new TInstForm( this );
	InstForm->ShowModal();
	delete InstForm;
	if ( AutoUnInstall ) Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate( TObject *Sender ) {
	/* The user just uninstalled us: either from the Control Panel, or
	 * from our Install Menu.  Either way, he obviously doesn't want
	 * us to continue running now. */
	if ( AutoUnInstall ) Close();
}

//---------------------------------------------------------------------------
// Prototypes for functions that we explicitly import from Kernel32.DLL
typedef bool (WINAPI *PROCFREELIBRARY)(HINSTANCE);
typedef bool (WINAPI *PROCDELETEFILE)(LPCTSTR);
typedef bool (WINAPI *PROCREMOVEDIRECTORY)(LPCTSTR);
typedef void (WINAPI *PROCEXITPROCESS)(DWORD);

// Data structure containing all the information we need to delete ourself,
// remove our containing directory, and terminate ourself.
typedef struct {
   HINSTANCE       hinstExe;
   PROCFREELIBRARY pfnFreeLibrary;

   PROCDELETEFILE  pfnDeleteFile;
   char            File[MAX_PATH];

   PROCREMOVEDIRECTORY pfnRemoveDirectory;
   char            Dir[MAX_PATH];

   PROCEXITPROCESS pfnExitProcess;
   DWORD           ExitCode;
} DELEXEINFO, *PDELEXEINFO;

typedef void (WINAPI *PROCDELEXE)(PDELEXEINFO);


// Code to be injected into our own address space.
static void WINAPI DelExeInjCode( PDELEXEINFO pdei ) {
	// Remove the EXE file from our address space
	pdei->pfnFreeLibrary( pdei->hinstExe );

	// Delete the EXE file now that it is no longer in use
	pdei->pfnDeleteFile( pdei->File );

	if ( pdei->pfnRemoveDirectory != NULL ) // Remove the directory (which is now empty)
		pdei->pfnRemoveDirectory( pdei->Dir );

	// Terminate our process
	pdei->pfnExitProcess( pdei->ExitCode );
}

// This function just marks the end of the previous function.
static void WINAPI AfterDelExeInjCode( void ) { }

void WINAPI KillMySelf2( DWORD exitcode, bool fRemoveDir ) {
	DELEXEINFO dei;

	HINSTANCE hinstKrnl = ::GetModuleHandle( "KERNEL32" );
	HANDLE	 hheap	  = ::GetProcessHeap();

	// Calculate the number of bytes in the DelExeInjCode function.
	int FuncSize = (LPBYTE)(DWORD)AfterDelExeInjCode - (LPBYTE)(DWORD)DelExeInjCode;

	// From our process's default heap, allocate memory where we can inject our own function.
	PROCDELEXE pfnDelExe = (PROCDELEXE)::HeapAlloc( hheap, HEAP_ZERO_MEMORY, FuncSize );

	// Inject the DelExeInjCode function into the memory block
	memcpy( pfnDelExe, DelExeInjCode, FuncSize );

	// Initialize the DELEXEINFO structure.
	dei.hinstExe = ::GetModuleHandle( NULL );
	dei.pfnFreeLibrary = (PROCFREELIBRARY)::GetProcAddress( hinstKrnl, "FreeLibrary" );

	// Assume that the subdirectory is NOT to be removed.
	dei.pfnRemoveDirectory = NULL;
	dei.pfnDeleteFile = (PROCDELETEFILE)::GetProcAddress( hinstKrnl, "DeleteFileA" );
	::GetModuleFileName( dei.hinstExe, dei.File, MAX_PATH );

   if ( fRemoveDir ) {	// The subdirectory should be removed.
		dei.pfnRemoveDirectory = (PROCREMOVEDIRECTORY)::GetProcAddress( hinstKrnl, "RemoveDirectoryA" );
		strcpy( dei.Dir, dei.File );
      *strrchr( dei.Dir, '\\' ) = 0;
   }

	dei.pfnExitProcess = (PROCEXITPROCESS)::GetProcAddress( hinstKrnl, "ExitProcess" );
	dei.ExitCode = exitcode;

	pfnDelExe( &dei );
	// We never get here because pfnDelExe never returns.
}

