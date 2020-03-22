#include <vcl\vcl.h>
#pragma hdrstop

#include "Install.h"
#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TInstForm *InstForm;
String     EXEName, EXETitle;

//---------------------------------------------------------------------------
__fastcall TInstForm::TInstForm( TComponent *Owner ) : TForm( Owner ) {
}

//---------------------------------------------------------------------------
void __fastcall TInstForm::FormCreate( TObject *Sender ) {
	EXEName  = ExtractFileName( ParamStr( 0 ) );
	EXETitle = "ViewZip - Auto Install Application Example";
	ProgramNameLabel->Caption = ParamStr( 0 );

	StartMenuCB->Checked	= true;
	DesktopCB->Checked	= true;
	SendToCB->Checked		= true;
	RegistryCB->Checked	= true;
	AssocCB->Checked		= true;
	KillCB->Checked		= false;

	if ( MainForm->AutoUnInstall ) {
		ShowMessage( "Now beginning ViewZip auto uninstall" );
		UnInstButClick( this );
	}
}

//---------------------------------------------------------------------------
void __fastcall TInstForm::FormActivate( TObject *Sender ) {
	if ( MainForm->AutoUnInstall )
		PostMessage( Handle, WM_CLOSE, 0, 0 );
}

//---------------------------------------------------------------------------
void __fastcall TInstForm::InstButClick( TObject *Sender ) {
	String path;

   Screen->Cursor = crHourGlass;
	if ( StartMenuCB->Checked ) {
		GetSpecialFolder( (StartMenuRB->Checked) ? CSIDL_STARTMENU : CSIDL_PROGRAMS, path );
		MakeLink( ParamStr( 0 ),	// The full pathname of this executable program.
				"",						// No arguments.
				path + EXETitle + ".lnk",
				"Sample Self-install Program" );
	}
	if ( DesktopCB->Checked ) {
		GetSpecialFolder( CSIDL_DESKTOPDIRECTORY, path );
		MakeLink( ParamStr( 0 ),	// The full pathname of this executable program.
				"",						// No arguments.
				path + EXETitle + ".lnk",
				"Sample Install Program" );
	}
	if ( SendToCB->Checked ) {
		GetSpecialFolder( CSIDL_SENDTO, path );
		MakeLink( ParamStr( 0 ),	// The full pathname of this executable program.
				"",						// No arguments.
				path + EXETitle + ".lnk",
				"Sample Install Program" );
	}
	if ( RegistryCB->Checked ) {
		// Define the application path.
		SetValInReg( HKEY_LOCAL_MACHINE,
					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\" + EXEName,
					"",					// Specify the default data item.
					ParamStr( 0 ) );	// Full pathname with program name.
		path = ExtractFilePath( ParamStr( 0 ) );
		SetValInReg( HKEY_LOCAL_MACHINE,
					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\" + EXEName,
					"Path",				// Specify the Path data item.
					path.SubString( 1, path.Length() - 1 ) );	// Full pathname without end slash.

		// Define the un-install command line.
		SetValInReg( HKEY_LOCAL_MACHINE,
					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + EXEName,
					"DisplayName",
					EXETitle );			// Show user this name in control panel.
		SetValInReg( HKEY_LOCAL_MACHINE,
					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + EXEName,
					"UninstallString",
					ParamStr( 0 ) + " /UNINSTALL" ); // Program name and parameter.

		// Define the main application program settings key.
		SetValInReg( HKEY_LOCAL_MACHINE, "SOFTWARE\\" + EXEName, "InstalledVersion", "1.40" );

		// These are settings that only apply to the current logged-in user.
		SetValInReg( HKEY_CURRENT_USER, "SOFTWARE\\" + EXEName, "InstalledVersion", "1.40" );
		SetValInReg( HKEY_CURRENT_USER, "SOFTWARE\\" + EXEName, "Setting1", "y" );
		SetValInReg( HKEY_CURRENT_USER, "SOFTWARE\\" + EXEName, "Setting2", "n" );
	}
	if ( AssocCB->Checked ) MakeAssociation( "zip", ParamStr( 0 ) );

	Screen->Cursor = crDefault;

	if ( KillCB->Checked ) KillMySelf2( 0, false );
	Close();
}

//---------------------------------------------------------------------------
/* Create a Win95 file association in the registry.  This uses the Quick-and-
 * Dirty method used by Explorer when you right click on a file and choose
 * "Open With...".  Basically, the file extension is created as a class, and
 * a dummy file type is created for that class to tell Win95 which program to
 * run.  Once this is done, you can easily test it from a DOS Shell by typing:
 * START FILENAME.EXT
 * Be advised: This is where I expected file associations to be (because
 * there are already some associations there), but they seem to have no effect:
 * HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Extensions"
 */
void __fastcall TInstForm::MakeAssociation( String Ext, String PgmToLinkTo ) {
	// ALL extensions must be in lowercase to avoid trouble!
	Ext = LowerCase( Ext );
	if ( FileExists( PgmToLinkTo ) ) {
		SetValInReg( HKEY_CLASSES_ROOT,
				"." + Ext,					// Extension we want to define.
				"",							// Specify the default data item.
				Ext + "_auto_file" );	// This is the value of the default data item -
												// this references our new type to be defined.
		SetValInReg( HKEY_CLASSES_ROOT,
            Ext + "_auto_file",		// this is the type we want to define
				"",							// Specify the default data item.
				Ext + " Files" );			// This is the value of the default data item -
												// this is the English description of the file type.

		SetValInReg( HKEY_CLASSES_ROOT,
				Ext + "_auto_file\\DefaultIcon",				// Create a file...DefaultIcon.
				"",							// Specify the default data item.
				PgmToLinkTo + ",0");		// Executable where icon is in and it's Sequence number.
		::SHChangeNotify( SHCNE_ASSOCCHANGED, SHCNF_FLUSH	, (void *)NULL, (void *)NULL );

		// SetValInReg( HKEY_CLASSES_ROOT,
		//          Ext + "_auto_file\\QuickView",	 	// Create a key for QuickView compat.
		//          "",					// Specify the default data item.
		//          "*" );				// Flag to tell Explorer that QuickView is OK.
		SetValInReg( HKEY_CLASSES_ROOT,
				Ext + "_auto_file\\shell\\open\\command",	// Create a file...open key.
				"",							// Specify the default data item.
				PgmToLinkTo + " %1");	// Command line to open file with.
	} else
		ShowMessage( "Error: Program not found: " + PgmToLinkTo );
}

//---------------------------------------------------------------------------
void __fastcall TInstForm::RemoveAssociation( String Ext ) {
	Ext = LowerCase( Ext );
	RegDeleteKey( HKEY_CLASSES_ROOT, "." + Ext );	// Extension we want to undefine.
	RegDeleteKey( HKEY_CLASSES_ROOT, Ext + "_auto_file\\DefaultIcon" );
	RegDeleteKey( HKEY_CLASSES_ROOT, Ext + "_auto_file\\shell\\open\\command" );
	RegDeleteKey( HKEY_CLASSES_ROOT, Ext + "_auto_file" );
	::SHChangeNotify( SHCNE_ASSOCCHANGED, SHCNF_FLUSH	, (void *)NULL, (void *)NULL );
}

//---------------------------------------------------------------------------
void __fastcall TInstForm::RegDeleteKey( HKEY RKey, String KeyPath ) {
	TRegistry *rg = new TRegistry();

	rg->RootKey = RKey;	// Set to the 'new' rootkey.
	// Under Win95, all keys under this one are auto. deleted also.
	// But, under WinNT, the keys under this one will be left alone.
	rg->DeleteKey( KeyPath );
	delete rg;
}

//---------------------------------------------------------------------------
/* Set a value in the registry. This is NOT related to the .LNK code.
 * This will create a new registry key if it doesn't already exist. */
void __fastcall TInstForm::SetValInReg( HKEY RKey, String KeyPath, String ValName, String NewVal ) {
	TRegistry *rg = new TRegistry();

	rg->RootKey = RKey;	// Set to the 'new' rootkey.
	rg->OpenKey( KeyPath, true );
	try {
		rg->WriteString( ValName, NewVal );
	} catch ( ... ) { }
	delete rg;
}

//---------------------------------------------------------------------------
/* Make a Shell Link, also called a "shortcut".
 * MakeLink - uses the shell's IShellLink and IPersistFile interfaces
 * to create and store a shortcut to the specified object.
 * Returns the result of calling the member functions of the interfaces.

 * PgmPath  - address of a buffer containing the path of the object.
 * LinkPath - address of a buffer containing the path where the shell link is to be stored.
 * Descr    - address of a buffer containing the description of the shell link.
 * PgmArgs  - address of a buffer containing the arguments for the shell link.
 */
HRESULT __fastcall TInstForm::MakeLink( String PgmPath, String PgmArgs, String LinkPath, String Descr ) {
	IShellLink *ShLink;

	if ( UpperCase( ExtractFileExt( LinkPath ) ) != ".LNK" ) {
		ShowMessage( "Error: link path extension must be .LNK" );
		return 0;
	}
	HRESULT hRes = CoInitialize( NULL );
	if ( hRes == S_OK || hRes == S_FALSE ) {
		if ( hRes == S_OK ) {
			// Get a pointer to the IShellLink interface.
			hRes = CoCreateInstance( CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&ShLink );
			if ( SUCCEEDED( hRes ) ) {
				IPersistFile *PFile;

				// Set the path to the shortcut target, and add the description.
				ShLink->SetPath( PgmPath.c_str() );
				ShLink->SetDescription( Descr.c_str() );
				ShLink->SetArguments( PgmArgs.c_str() );
				ShLink->SetIconLocation( PgmPath.c_str(), 0 );
				ShLink->SetWorkingDirectory( ExtractFilePath( PgmPath ).c_str() );


				// Query IShellLink for the IPersistFile interface for saving the
				// shortcut in persistent storage.
				hRes = ShLink->QueryInterface( IID_IPersistFile, (void **)&PFile );
				if ( SUCCEEDED( hRes ) ) {
					WideChar WFileName[MAX_PATH];

					// Ensure that the string is ANSI.
					MultiByteToWideChar( CP_ACP, 0, LinkPath.c_str(), -1, WFileName, MAX_PATH );

					// Save the link by calling IPersistFile::Save.
					PFile->Save( WFileName, false );
					hRes = PFile->SaveCompleted( WFileName );
					PFile->Release();
				}
				ShLink->Release();
			}
		} else ShowMessage( "COM already initialized" );
		CoUninitialize();
	} else 		// E_INVALIDARG, E_OUTOFMEMORY, o E_UNEXPECTED.
		ShowMessage( "COM library could not initialize" );
	return hRes;
}

//---------------------------------------------------------------------------
void __fastcall TInstForm::CancelButClick( TObject *Sender ) {
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TInstForm::UnInstButClick( TObject *Sender ) {
	String path;

	Screen->Cursor = crHourGlass;
	if ( StartMenuCB->Checked ) {
		GetSpecialFolder( (StartMenuRB->Checked) ? CSIDL_STARTMENU : CSIDL_PROGRAMS, path );
		String Temp = path + EXETitle + ".lnk";
		DeleteFile( Temp );
	}
	if ( DesktopCB->Checked ) {
		GetSpecialFolder( CSIDL_DESKTOPDIRECTORY, path );
		String Temp = path + EXETitle + ".lnk";
		DeleteFile( Temp );
	}
	if ( SendToCB->Checked ) {
		GetSpecialFolder( CSIDL_SENDTO, path );
		String Temp = path + EXETitle + ".lnk";
		DeleteFile( Temp );
	}
	if ( RegistryCB->Checked ) {
		RegDeleteKey( HKEY_LOCAL_MACHINE,
					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\" + EXEName );
		RegDeleteKey( HKEY_LOCAL_MACHINE,
					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + EXEName );
		RegDeleteKey( HKEY_LOCAL_MACHINE, "SOFTWARE\\" + EXEName );
		RegDeleteKey( HKEY_CURRENT_USER, "SOFTWARE\\" + EXEName );
	}

	if ( AssocCB->Checked ) RemoveAssociation( "zip" );

	Screen->Cursor = crDefault;

	/* If we are auto-uninstalling, then we are still in OnCreate,
	 * so we can't close this form yet. */
	if ( !MainForm->AutoUnInstall ) Close();
}

//---------------------------------------------------------------------------
/* Folder types are a.o.
 *	CSIDL_DESKTOPDIRECTORY, CSIDL_STARTMENU, CSIDL_SENDTO,
 * CSIDL_PROGRAMS, CSIDL_STARTUP etc.
 */
long __fastcall TInstForm::GetSpecialFolder( int aFolder, String &Location ) {
	long		   FolderErr = 0;   // No error.
	char		  *RealPath;
	ITEMIDLIST *pidl;
	LPMALLOC    g_pMalloc;

	// Get the shell's allocator.
	if ( ::SHGetMalloc( &g_pMalloc ) == E_FAIL ) return E_FAIL;

	// Allocate a buffer to receive the path information.
	if ( (RealPath = (char *)g_pMalloc->Alloc( MAX_PATH )) != NULL ) {
		HRESULT hRes = ::SHGetSpecialFolderLocation( Handle, aFolder, &pidl );
		if ( hRes == NOERROR ) {
			bool Success = ::SHGetPathFromIDList( pidl, RealPath );
			if ( Success ) {
				Location = RealPath;
				Location += "\\";
			} else FolderErr = E_UNEXPECTED;
			// Free the PIDL allocated by SHGetSpecialFolderLocation.
			g_pMalloc->Free( pidl );
		} else FolderErr = hRes;
		// Free the string buffer used for the name
		g_pMalloc->Free( RealPath );
	} else FolderErr = E_OUTOFMEMORY;
	// Release the shell's allocator.
	g_pMalloc->Release();
	return FolderErr;
}

//---------------------------------------------------------------------------
void __fastcall TInstForm::StartMenuCBClick( TObject *Sender ) {
	StartMenuRB->Enabled = StartMenuCB->Checked;
	ProgramRB->Enabled   = StartMenuCB->Checked;
}

