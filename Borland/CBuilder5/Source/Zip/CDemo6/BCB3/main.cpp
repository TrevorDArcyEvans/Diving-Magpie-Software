#include <vcl\vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma link "SortGrid"
#pragma link "ZIPBuilder"

#pragma package(smart_init)
#pragma resource "*.dfm"

TMainForm *MainForm;

String ExtractDir;
bool ExpandDirs, OverWr, AllFiles, Canceled;

//---------------------------------------------------------------------------
void __fastcall TMainForm::FillGrid( void ) {
	// Remove everything from grid except col titles.
	StringGrid1->ClearFrom( 1 );
	StringGrid1->RowCount = ZipBuilder1->Count + 2;
	if ( !ZipBuilder1->Count ) return;

	TotUncomp = TotComp   = 0;
	for ( int i = 1; i <= ZipBuilder1->Count; i++ ) {
		ZipDirEntry *zde = (ZipDirEntry *)ZipBuilder1->ZipContents->Items[i - 1];
		StringGrid1->Cells[0][i] = ExtractFileName( zde->FileName );
		StringGrid1->Cells[1][i] = IntToStr( zde->CompressedSize );
		StringGrid1->Cells[2][i] = IntToStr( zde->UncompressedSize );
		StringGrid1->Cells[3][i] = FormatDateTime( "ddddd  t", FileDateToDateTime( zde->DateTime ) );
		unsigned long cs = zde->CompressedSize, us = zde->UncompressedSize;
		if ( us )
			StringGrid1->Cells[4][i] = IntToStr( 100 - cs * 100 / us - ((cs * 100 % us) >= us / 2) ) + "% ";
		else
			StringGrid1->Cells[4][i] = "0% ";
		StringGrid1->Cells[5][i] = ExtractFilePath( zde->FileName );
		TotUncomp += zde->UncompressedSize;
		TotComp   += zde->CompressedSize;
	}
	TSortOptions so;
	so.SortDirection	   = sdAscending;
	so.SortStyle		   = ssAutomatic;
	so.SortCaseSensitive = false;
	StringGrid1->SortByColumn( StringGrid1->SortColumn, so );
	StringGrid1->Row = 1;

	SetZipTotals();
}

//---------------------------------------------------------------------------
bool __fastcall TMainForm::ZipOpenArchive() {
	if ( ZipOpenDir == "" ) GetSpecialFolder( CSIDL_DESKTOPDIRECTORY, ZipOpenDir );
	OpenDialog1->InitialDir = ZipOpenDir;
	OpenDialog1->Title      = "Open Existing ZIP File";
	OpenDialog1->Filter     = "ZIP Files (*.ZIP)|*.zip";
	OpenDialog1->FileName   = "";
	OpenDialog1->Options << ofHideReadOnly << ofShareAware << ofPathMustExist << ofFileMustExist;
	if ( OpenDialog1->Execute() ) {
		ZipOpenDir = ExtractFilePath( OpenDialog1->FileName );
		// Assigning the filename will cause the table of contents to be read.
		ZipBuilder1->ZipFilename = OpenDialog1->FileName;
		/* Set the caption after assigning the filename. This
		   way, the filename will be null if the open failed. */
		SetZipFName( ZipBuilder1->ZipFilename );
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NewZipButClick( TObject *Sender ) {
	static String FirstDir = "";

	if ( FirstDir == "" ) GetSpecialFolder( CSIDL_DESKTOPDIRECTORY, FirstDir );
	OpenDialog1->InitialDir = FirstDir;
	OpenDialog1->Title      = "Create New ZIP File";
	OpenDialog1->FileName   = "";
	OpenDialog1->Filter     = "ZIP Files (*.ZIP)|*.zip";
	OpenDialog1->DefaultExt = "Zip";
	OpenDialog1->Options << ofHideReadOnly << ofShareAware;
	OpenDialog1->Options >> ofPathMustExist >> ofFileMustExist;
	if ( OpenDialog1->Execute() ) {
		FirstDir = ExtractFilePath( OpenDialog1->FileName );
		if ( UpperCase( ExtractFileExt( OpenDialog1->FileName ) ) != ".ZIP" ) {
			ShowMessage( "Error: your new archive must end in .ZIP" );
			return;
		}
		if ( FileExists( OpenDialog1->FileName ) ) {
			bool Ans = MessageDlg( "Overwrite Existing File: " + OpenDialog1->FileName + "?",
                          mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) == mrYes;
			if ( Ans )
				DeleteFile( OpenDialog1->FileName );
			else return;  // Don't use the new name.
		}
		ZipBuilder1->ZipFileName = OpenDialog1->FileName;
		SetZipFName( ZipBuilder1->ZipFileName );
	} else return;
	if ( ZipBuilder1->ZipFilename != "" ) AddSpan();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ExtractButClick( TObject *Sender ) {
	static String FirstDir = "";

	ZipOpenDir = FirstDir;
	if ( !ZipOpenArchive() ) return;
	FirstDir = ZipOpenDir;

	if ( ZipBuilder1->ZipFilename == "" ) return;

	Extract->ShowModal();
	if ( ( ExtractDir == "" ) || Canceled ) return;

	if ( ZipBuilder1->Count < 1 ) {
		ShowMessage( "Error - no files to extract" );
		return;
	}
	ZipBuilder1->FSpecArgs->Clear();
	// Get fspecs of selected files, unless user wants all files extracted.
	if ( !AllFiles ) {
		for ( int i = StringGrid1->Selection.Top; i <= StringGrid1->Selection.Bottom; i++ ) {
			if ( i != StringGrid1->RowCount - 1 ) {
				ZipBuilder1->FSpecArgs->Add( StringGrid1->Cells[5][i] + StringGrid1->Cells[0][i] );
			}
		}
		if ( ZipBuilder1->FSpecArgs->Count < 1 ) {
			ShowMessage( "Error - no files selected" );
			return;
		}
	}
	MsgForm->RichEdit1->Clear();
	MsgForm->Show();
	// Put this message into the message form.
	ZipBuilder1Message( this, 0, "Beginning Extract from " + ZipBuilder1->ZipFilename );

	ZipBuilder1->ExtrBaseDir = ExtractDir;
	ZipBuilder1->ExtrOptions.Clear();
	if ( ExpandDirs )
		ZipBuilder1->ExtrOptions << ExtrDirNames;
	if ( OverWr )
		ZipBuilder1->ExtrOptions << ExtrOverWrite;
	try {
		ZipBuilder1->Extract();
	} catch ( ... ) {
		ShowMessage( "Error in Extract; Fatal DLL Exception in Main" );
		return;
	}
	String IsOne = (ZipBuilder1->SuccessCnt == 1) ? " was" : "s were";
	ShowMessage( IntToStr( ZipBuilder1->SuccessCnt ) + " file" + IsOne + " extracted" );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ZipBuilder1DirUpdate( TObject *Sender ) {
	FillGrid();
	FilesLabel->Caption = IntToStr( ZipBuilder1->Count );
	SetZipFName( ZipBuilder1->ZipFilename );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate( TObject *Sender ) {
	/* Make sure "goColMoving" is false in object inspector. This lets the
      TSortGrid use Mouse Clicks on the col headers. */
	StringGrid1->RowCount     =   2;  // First row is fixed, and used for column headers.
	StringGrid1->Cells[0][0]  = "File Name";
	StringGrid1->Cells[1][0]  = "Compr. Size";
	StringGrid1->Cells[2][0]  = "Uncompr. Size";
	StringGrid1->Cells[3][0]  = "Date Time";
	StringGrid1->Cells[4][0]  = "Ratio";
	StringGrid1->Cells[5][0]  = "Path";

	ZipBuilder1->Load_Zip_Dll();
	ZipBuilder1->Load_Unz_Dll();
	/* If we had args on the cmd line, then try to open the first one
		as a zip/exe file.  This is most useful in case user has an association
		to ".zip" that causes this program to run when user double clicks on a zip
		file in Explorer. */
	if ( ParamCount > 0 ) ZipBuilder1->ZipFilename = ParamStr( 1 );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddButClick( TObject *Sender ) {
	static String FirstDir = "";

	ZipOpenDir = FirstDir;
	if ( !ZipOpenArchive() ) return;
	FirstDir = ZipOpenDir;

	if ( ZipBuilder1->ZipFilename == "" ) return;
	AddSpan();
}

void __fastcall TMainForm::AddSpan() {
	Canceled = false;
	AddFile->ShowModal();  // Let user pick filenames to add.
	if ( Canceled ) return;

	if ( !AddFile->SelectedList->Items->Count ) {
		ShowMessage( "No files selected" );
		return;
	}
	MsgForm->RichEdit1->Clear();
	MsgForm->Show();
	// Put this message into the message form.
	ZipBuilder1Message( this, 0, "Beginning Add to " + ZipBuilder1->ZipFilename );

	ZipBuilder1->AddOptions.Clear();
	if ( AddFile->RecurseCB->Checked )					// We want recursion.
		ZipBuilder1->AddOptions = ZipBuilder1->AddOptions << AddRecurseDirs;
	if ( AddFile->DirNameCB->Checked )					// We want dirnames.
		ZipBuilder1->AddOptions = ZipBuilder1->AddOptions << AddDirNames;
	if ( FormatCB->Checked )								// We want disk spanning with formatting
		ZipBuilder1->AddOptions  = ZipBuilder1->AddOptions << AddDiskSpanErase;
	else															// We want normal disk spanning
		ZipBuilder1->AddOptions  = ZipBuilder1->AddOptions << AddDiskSpan;
	if ( AddFile->EncryptCB->Checked )					// We want a password.
		ZipBuilder1->AddOptions = ZipBuilder1->AddOptions << AddEncrypt;

	ZipBuilder1->FSpecArgs->Clear();
	ZipBuilder1->FSpecArgs->Assign( AddFile->SelectedList->Items ); // Specify filenames.
	AddFile->SelectedList->Clear();

	try {
		ZipBuilder1->Add();
	} catch ( ... ) {
		ShowMessage( "Error in Add; Fatal DLL Exception in Main" );
		return;
	}
	String IsOne = (ZipBuilder1->SuccessCnt == 1) ? " was" : "s were";
	ShowMessage( IntToStr( ZipBuilder1->SuccessCnt ) + " file" + IsOne + " added" );
}

//---------------------------------------------------------------------------
// This is the "OnMessage" event handler.
void __fastcall TMainForm::ZipBuilder1Message( TObject *Sender, int ErrCode, String Message ) {
	MsgForm->RichEdit1->Lines->Append( Message );
	::PostMessage( MsgForm->RichEdit1->Handle, EM_SCROLLCARET, 0L, 0L );
	Application->ProcessMessages();
	if ( ErrCode > 0 ) ShowMessage( "Error Msg: " + Message );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ZipBuilder1Progress( TObject *Sender, ProgressType ProgrType, String Filename, long FileSize ) {
	static long	TotalSize1, TotalProgress1, TotalSize2, TotalProgress2;
	int			Step;

	switch ( ProgrType ) {
		case TotalSize2Process:
			// ZipBuilder1Message( this, 0, "in OnProgress type TotalBytes, size= " + IntToStr( FileSize ) );
			MsgForm->StatusBar1->Panels->Items[0]->Text = "Total size: " + IntToStr( FileSize / 1024 ) + " Kb";
			MsgForm->ProgressBar2->Position = 1;
			TotalSize2     = FileSize;
			TotalProgress2 = 0;
			break;

		case TotalFiles2Process:
			// ZipBuilder1Message( this, 0, "in OnProgress type TotalFiles, files= " + IntToStr( FileSize ) );
			MsgForm->StatusBar1->Panels->Items[1]->Text = IntToStr( FileSize ) + " files";
			break;

		case NewFile:
			// ZipBuilder1Message( this, 0, "in OnProgress type NewFile, size= " + IntToStr( FileSize ) );
			MsgForm->FileBeingZipped->Caption = Filename;
			MsgForm->ProgressBar1->Position = 1;		// Current position of bar.
			TotalSize1		 = FileSize;
			TotalProgress1	 = 0;
			break;

		case ProgressUpdate:
			// ZipBuilder1Message( this, 0, "in OnProgress type Update, size= " + IntToStr( FileSize ) );
			// FileSize gives now the bytes processed since the last call.
			TotalProgress1 += FileSize;
			TotalProgress2 += FileSize;
			if ( TotalSize1 ) {
				Step = (int)( (unsigned __int64)TotalProgress1 * 10000ui64 / (unsigned __int64)TotalSize1 );
				MsgForm->ProgressBar1->Position = (PGBCONV)(1 + Step);
			} else MsgForm->ProgressBar1->Position = 10001;
			if ( TotalSize2 ) {
				Step = (int)( (unsigned __int64)TotalProgress2 * 10000ui64 / (unsigned __int64)TotalSize2 );
				MsgForm->ProgressBar2->Position = (PGBCONV)(1 + Step);
			}
			break;

		case EndOfBatch:
			// Reset the progress bar and filename.
			// ZipBuilder1Message( this, 0, "in OnProgress type EndOfBatch" );
			MsgForm->FileBeingZipped->Caption = "";
			MsgForm->ProgressBar1->Position = 1;
			MsgForm->StatusBar1->Panels->Items[0]->Text = "";
			MsgForm->StatusBar1->Panels->Items[1]->Text = "";
			MsgForm->ProgressBar2->Position = 1;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy( TObject *Sender ) {
	ZipBuilder1->Unload_Zip_Dll();
	ZipBuilder1->Unload_Unz_Dll();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SetZipFName( String aCaption ) {
	ZipFName->Caption = MinimizeName( aCaption, ZipFName->Canvas, ZipFName->Width );
	if ( ZipFName->Caption == "" ) ZipFName->Caption = "<none>";
	if ( ZipFName->Canvas->TextWidth( aCaption ) > ZipFName->Width ) {
		ZipFName->Hint = aCaption;
		ZipFName->ShowHint = true;
	} else ZipFName->ShowHint = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::WriteBttnClick( TObject *Sender ) {
	static String FirstDir = "";
	String InFile, OutFile;

	ZipOpenDir = FirstDir;
	if ( !ZipOpenArchive() ) return;
	FirstDir = ZipOpenDir;

	InFile = ZipBuilder1->ZipFilename;
	if ( InFile == "" ) return;

	if ( AskDirDialog( MainForm->Handle, OutFile ) ) {
		OutFile += ExtractFileName( InFile );
		MsgForm->RichEdit1->Clear();
		MsgForm->Show();
		ZipBuilder1->WriteSpan( InFile, OutFile );
		MsgForm->Hide();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ReadBttnClick( TObject *Sender ) {
	String InFile, OutPath, ext;
	long   len = 3;

	OpenDialog1->Options << ofHideReadOnly << ofShareAware << ofPathMustExist << ofFileMustExist;
	OpenDialog1->Title      = "Open spanned ZIP archive on last disk";
	OpenDialog1->Filter     = "ZIP Files (*.ZIP)|*.zip";
	OpenDialog1->FileName   = "";
	OpenDialog1->InitialDir = "A:\\";
	OpenDialog1->DefaultExt = "zip";
	if ( OpenDialog1->Execute() ) {
		String fd = ExtractFileDrive ( InFile = OpenDialog1->FileName ) + "\\";
		unsigned int drivetype = ::GetDriveType( fd.c_str() );

		if ( drivetype == DRIVE_FIXED || drivetype == DRIVE_REMOTE ) {
			ext = ExtractFileExt( InFile );
			len = InFile.Length() - ext.Length();
			if ( StrToIntDef( InFile.SubString( len - 2, 3 ), -1 ) == -1 ) {
				ShowMessage( "This is not a valid (last)part of a spanned archive" );
				return;
			}
		}
		if ( AskDirDialog( MainForm->Handle, OutPath ) ) {
			if ( drivetype == DRIVE_FIXED || drivetype == DRIVE_REMOTE )
				OutPath += ExtractFileName( InFile.SubString( 1, len - 3 ) + ext );
			else
				OutPath += ExtractFileName( InFile );
			MsgForm->RichEdit1->Clear();
			MsgForm->Show();
			if ( !ZipBuilder1->ReadSpan( InFile, OutPath ) ) {
				ZipBuilder1->ZipFilename = OutPath;
				SetZipFName( ZipBuilder1->ZipFilename );
			}
			MsgForm->Hide();
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Showlasterror1Click( TObject *Sender ) {
	if ( ZipBuilder1->ErrCode )
		ShowMessage( IntToStr( ZipBuilder1->ErrCode ) + " " + ZipBuilder1->Message );
	else
		ShowMessage( "No last error present" );
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click( TObject *Sender ) {
	Close();
}

//---------------------------------------------------------------------------
bool __fastcall TMainForm::AskDirDialog( const HWND FormHandle, String &DirPath ) {
	BROWSEINFO  bi;
	LPSTR		   lpBuffer;
	ITEMIDLIST *pidl;          // PIDL selected by user
	LPMALLOC    g_pMalloc;
	bool			Result = false;

	// Get the shell's allocator.
	if ( (SHGetMalloc( &g_pMalloc ) )== E_FAIL ) return false;

	// Allocate a buffer to receive browse information.
	if ( (lpBuffer = (LPSTR)g_pMalloc->Alloc( MAX_PATH)) != 0 ) {
		bi.hwndOwner		= FormHandle;
		bi.pidlRoot			= NULL;
		bi.pszDisplayName	= lpBuffer;
		bi.lpszTitle		= "";
		bi.ulFlags			= 0;
		bi.lpfn				= NULL;
		bi.lParam			= 0;

		// if pidl = 0 then cancel is used.
		if ( (pidl = SHBrowseForFolder( &bi )) != 0 ) {
			// if 0 then pidl not part of namespace
			if ( SHGetPathFromIDList( pidl, lpBuffer ) ) {
				DirPath = lpBuffer;
				if ( DirPath[DirPath.Length()] != '\\' ) DirPath += '\\';
				Result  = true;
			}
			// Free the PIDL returned by SHBrowseForFolder.
			g_pMalloc->Free( pidl );
		}
		// Free the string buffer used for the name
		g_pMalloc->Free( lpBuffer );
	}
	// Release the shell's allocator.
	g_pMalloc->Release();
	return Result;
}

//---------------------------------------------------------------------------
/* Folder types are a.o.
 *	CSIDL_DESKTOPDIRECTORY, CSIDL_STARTMENU, CSIDL_SENDTO,
 * CSIDL_PROGRAMS, CSIDL_STARTUP
 */
long __fastcall TMainForm::GetSpecialFolder( int aFolder, String &Location ) {
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
void __fastcall TMainForm::StringGrid1GetCellFormat( TObject *Sender, int Col, int Row, TGridDrawState State, TFormatOptions &FormatOptions ) {
	if ( Row && Col && Col != 5 ) FormatOptions.AlignmentHorz = taRightJustify;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DLLversioninfo1Click( TObject *Sender ) {
	ShowMessage( "UnZip Dll version: " + IntToStr( ZipBuilder1->UnzVers ) + "\n" +
					 "  Zip Dll version: " + IntToStr( ZipBuilder1->ZipVers ) );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize( TObject *Sender ) {
	ZipFName->Width = max( 0, Width - 291 );
	SetZipFName( ZipBuilder1->ZipFilename );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::StringGrid1EndSort( TObject *Sender, int Col ) {
	SetZipTotals();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SetZipTotals( void ) {
	StringGrid1->Cells[0][ZipBuilder1->Count + 1] = "Total";
	StringGrid1->Cells[1][ZipBuilder1->Count + 1] = IntToStr( TotComp );
	StringGrid1->Cells[2][ZipBuilder1->Count + 1] = IntToStr( TotUncomp );
	unsigned long cs = TotComp, us = TotUncomp;
	if ( us )
		StringGrid1->Cells[4][ZipBuilder1->Count + 1] = IntToStr( 100 - cs * 100 / us - ((cs * 100 % us) >= us / 2) ) + " % ";
	else
		StringGrid1->Cells[4][ZipBuilder1->Count + 1] = "0 % ";
	StringGrid1->Cells[5][ZipBuilder1->Count + 1] = "";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Messages1Click( TObject *Sender ) {
	MsgForm->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::MaxVolSizeEditChange( TObject *Sender ) {
	ZipBuilder1->MaxVolumeSize = StrToIntDef(  MaxVolSizeEdit->Text, 0 );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FreeDisk1EditChange( TObject *Sender ) {
	ZipBuilder1->KeepFreeOnDisk1 = StrToIntDef( FreeDisk1Edit->Text, 0 );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::MinFreeVolEditChange( TObject *Sender ) {
	ZipBuilder1->MinFreeVolumeSize = StrToIntDef( MinFreeVolEdit->Text, 65536 );
}

