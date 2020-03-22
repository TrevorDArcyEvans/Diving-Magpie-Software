/* TZipBuilder component v1.60k by Chris Vleghert
 * a C++ Builder 1, 3 and 4.0 wrapper for the freeware ZIP and UNZIP DLL's
 * from Chris Vleghert.
 *
 * v1.60k  May 20, 1999
 * e-mail: cvleghrt@WorldOnline.nl
 * www:    http://www.geocities.com/SiliconValley/Orchard/8607/ or
 * www:    http://members.tripod.lycos.nl/Vleghert/
 *
 * or
 * www:    http://www.geocities.com/SiliconValley/Network/2114/
 * www:    http://members.tripod.com/englere/
 */

#include <vcl\vcl.h>
#pragma hdrstop

#pragma package(smart_init)	// Used in BCB 3,4 ignored in BCB 1
#pragma resource "*.res"

#include "ZIPBuilder.h"

USEUNIT("CallBack.cpp");
USEUNIT("ZipDLL.cpp");
USEUNIT("UnZipDLL.cpp");

namespace ZipBuilder {
	const String ZIPBUILDERVERSION = "1.60 K";
	// Unfortunately we can't put this line in the resource file.
	const String RESOURCE_ERROR = "ZipMsgxx.res is probably not bound to the executable\nMissing String ID is: ";
}
//----------------------------------------------------------------------------
// DeleteFile with a pure AnsiString wasn't possible in BCB1.
#if __BORLANDC__ < 1328		// BCB1=0x0520(1312)
namespace Sysutils {
	bool __fastcall DeleteFile( const System::AnsiString aStr ) {
		return ::DeleteFile( aStr.c_str() );
	}
}
#endif
//----------------------------------------------------------------------------
static inline TZipBuilder *ValidCtrCheck() {
	return new TZipBuilder( NULL );
}

//----------------------------------------------------------------------------
namespace Zipbuilder {
	void __fastcall PACKAGE Register() {
		TComponentClass classes[ 1 ] = {__classid( TZipBuilder ) };
		RegisterComponents( "Components", classes, 0 );
 	}
}

GetZipExecAddress		ZipDLL::ZipDllExec;
GetZipVersionAddress	ZipDLL::GetZipDllVersion;
GetUnzExecAddress		UnzipDLL::UnzDllExec;
GetUnzVersionAddress	UnzipDLL::GetUnzDllVersion;

HINSTANCE ZipDLL::ZipDllHandle;
HINSTANCE UnzipDLL::UnzDllHandle;

bool DirExists( const System::AnsiString Name ) {
	if ( Name == "" ) return false;
	DWORD Code = ::GetFileAttributes( Name.c_str() );
	return (Code != 0xFFFFFFFF) & ((FILE_ATTRIBUTE_DIRECTORY & Code) != 0);
}


//----------------------------------------------------------------------------
/* Dennis Passmore (Compuserve: 71640,2464) contributed the idea of passing an
 * instance handle to the DLL, and, in turn, getting it back from the callback.
 * This lets us reference variables in the TZipBuilder class from within the
 * callback function.  Way to go Dennis!
 * RCV: But while doing it like this you can only access public data and member
 * functions and we need access to private data (the properties ErrCode and
 * Message are read only).
 * This function is now(v1.5) a static member function of TZipBuilder. */
unsigned long __stdcall TZipBuilder::ZCallback( CallBack::PZCallBackStruct cbr ) {
	TZipBuilder *tzb = (TZipBuilder *)cbr->Caller;
	String		 Msg = tzb->ReplaceForwardSlash( cbr->FileNameOrMsg ).TrimRight(); // Used for UnzDll

	if ( tzb->OnProgress ) {
		switch ( cbr->ActionCode ) {
			// Progress type 1 = starting any ZIP operation on a new file.
			case 1:
				tzb->OnProgress( tzb, NewFile, Msg, cbr->FileSize );
				break;
			// Progress type 2 = increment bar.
			case 2:
				// Changed in v1.5 while zipping:
				// For large files we get: 65536, 32768, 32768, ...,  and the remaining bytes.
				// For small files we get: remaining bytes.
				tzb->OnProgress( tzb, ProgressUpdate, "", cbr->FileSize );
				break;
			// End of a batch of 1 or more files.
			case 3:
				tzb->OnProgress( tzb, EndOfBatch, "", 0 );
            break;
			// The total number of files which will be processed.
			case 5:
				tzb->OnProgress( tzb, TotalFiles2Process, "", cbr->FileSize );
				break;
			// The total size of the files which will be processed.
			case 6:
				tzb->OnProgress( tzb, TotalSize2Process, "", cbr->FileSize );
		}
	}
	switch ( cbr->ActionCode ) {
		case 4:	// Show a routine status message.
			if ( cbr->ErrorCode ) {  // W'll always keep the last ErrorCode
				tzb->FErrCode		= (int)(char)(cbr->ErrorCode & 0xFF);
				tzb->FFullErrCode = cbr->ErrorCode;
			}
			tzb->FMessage = Msg;
			if ( tzb->OnMessage ) tzb->OnMessage( tzb, cbr->ErrorCode, Msg );
			break;

		case 6:
			tzb->FTotalSizeToProcess = cbr->FileSize;
			break;

		case 7:
			if ( tzb->OnSetNewName ) {
				String OldFileName = cbr->FileNameOrMsg;
				bool   IsChanged   = false;

				tzb->OnSetNewName( tzb, OldFileName, IsChanged );
				if ( IsChanged ) StrPLCopy( cbr->FileNameOrMsg, OldFileName, 512 );
				cbr->ErrorCode = IsChanged;
			}
			break;

		case 8:	{	// New or other password needed during Extract().
				String   pwd = "";
				unsigned RptCount = cbr->FileSize;

				tzb->GAssignPassword = false;
				if ( tzb->OnPasswordError )
					tzb->OnPasswordError( tzb, pwd, Msg, RptCount );
				else pwd = (cbr->ErrorCode & 0x1) ? tzb->GetAddPassword() : tzb->GetExtrPassword();

				if ( pwd != "" ) {
					StrPLCopy( cbr->FileNameOrMsg, pwd, PASSWORDLEN + 1);
					cbr->ErrorCode = 1;
				} else RptCount = cbr->ErrorCode = 0;
				cbr->FileSize = min( RptCount, 15U );
				tzb->GAssignPassword = true;
			}
			break;

		case 9: {	// CRC32 error, (default action is extract/test the file).
				bool DoExtract = true;	// This was default for versions <1.6

				if ( tzb->OnCRC32Error )
					tzb->OnCRC32Error( tzb, Msg, cbr->ErrorCode, cbr->FileSize, DoExtract );
				cbr->ErrorCode = DoExtract;
				// This will let the Dll know it should send some warnings.
				if ( !tzb->OnCRC32Error ) cbr->ErrorCode = 2;
         }
			break;

		case 10:	// Extract(UnZip) Overwrite ask.
			if ( tzb->OnExtractOverwrite ) {
				bool DoOverwrite = cbr->FileSize;

				tzb->OnExtractOverwrite( tzb, Msg, (cbr->ErrorCode == 1), DoOverwrite );
				cbr->FileSize = DoOverwrite;
			}
			break;

		case 11:	// Extract(UnZip) and Skipped.
			if ( tzb->OnExtractSkipped )
				tzb->OnExtractSkipped( tzb, Msg, (UnZipSkipTypes)cbr->FileSize, cbr->ErrorCode );
	}
	Application->ProcessMessages();

	// If you return TRUE in the OnMessage event handler, then the DLL will abort
	// it's current batch job as soon as it can.
	return ( (tzb->Cancel) ? true : false );
}

//---------------------------------------------------------------------------
__fastcall TZipBuilder::TZipBuilder( Classes::TComponent *AOwner ) : TComponent( AOwner ) {
	FHandle					= Application->Handle;
	FZipContents 			= new TList();
	FFSpecArgs  			= new TStringList();
	FFSpecArgsExcl			= new TStringList();	//New v1.6
	FZipFileName			= "";
	FSuccessCnt 			=  0;
	FAddCompLevel			=  9;		// Default to tightest compression.
	FPassword				= "";
	FPasswordReqCount 	=  1;		// New v1.6
	GAssignPassword		= true;
	FSFXPath					= "";
	FEncrypt					= false;
	FDLLDirectory			= "";
	FSFXDefaultDir			= "";
	FSFXCommandLine		= "";
	FSFXCaption				= "Self-extracting Archive";
	FSFXOverWriteMode		= OvrConfirm;
	ZipParms1				= NULL;
	FRealFileSize			=  0;
   FSFXOffset				=  0;
	FZipSOC					=  0;
	FZipEOC					=  0;
	FUnattended				= false;
	FFreeOnDisk1			=  0;			// Don't leave anything free.
	FMaxVolumeSize			=  0;			// Use the maximum disk size.
	FMinFreeVolSize		= 65536;		// Reject disks with less bytes than...
	FConfirmErase			= true;
	FCodePage         	= cpAUTO;
	FSFXOptions				= SfxOpts() << SFXCheckSize;
	FIsSpanned        	= false;
	FHowToDelete			= htdAllowUndo;
	FSFXIcon					= new TIcon();
	FAddStoreSuffixes 	= AddStoreExts() << assGIF << assPNG << assZ << assZIP << assZOO << assARC
														<< assLZH << assARJ << assTAZ << assTGZ << assLHA;
	FZipStream				= new TZipStream();
	FVersionInfo			= ZIPBUILDERVERSION;
	FUseDirOnlyEntries	= false;
}

//---------------------------------------------------------------------------
__fastcall TZipBuilder::~TZipBuilder( void ) {
	delete FZipStream;
	delete FSFXIcon;
	FreeZipDirEntryRecords();
	delete FFSpecArgsExcl;
	delete FFSpecArgs;
	delete FZipContents;
}

//---------------------------------------------------------------------------
void __fastcall TPasswordDlg::PwdOkClick( TObject *Sender ) {
	OkClicked = true;
}

//---------------------------------------------------------------------------
String __fastcall TPasswordDlg::ShowModalPwdDlg( String DlgCaption, String MsgTxt ) {
	Caption         = DlgCaption;
	PwdTxt->Caption = MsgTxt;
	ShowModal();
	return OkClicked ? PwdEdit->Text : AnsiString( "" );
}

//---------------------------------------------------------------------------
__fastcall TPasswordDlg::TPasswordDlg( TComponent *Owner, int Dummy ) : TForm( Owner, Dummy ) {
	Parent		 = this;
	Width			 = 344;
	Height		 = 137;
	Font->Name	 = "Arial";
	Font->Height = -12;
	Font->Style	 = Font->Style << fsBold;
	OkClicked	 = false;
	BorderStyle	 = bsDialog;
	Position		 = poScreenCenter;

	PwdTxt			  = new TLabel( this );
	PwdTxt->Parent	  = this;
	PwdTxt->Left	  =  20;
	PwdTxt->Top		  =   8;
	PwdTxt->Width	  = 297;
	PwdTxt->Height	  =  18;
	PwdTxt->AutoSize = false;

	PwdEdit					 = new TEdit( this );
	PwdEdit->Parent		 = this;
	PwdEdit->Left			 =  20;
	PwdEdit->Top			 =  40;
	PwdEdit->Width			 = 297;
	PwdEdit->PasswordChar = '*';
	PwdEdit->MaxLength	 = PASSWORDLEN;

	OkBtn				= new TBitBtn( this );
	OkBtn->Parent	= this;
	OkBtn->Left		=  44;
	OkBtn->Top		=  72;
	OkBtn->Width	=  90;
	OkBtn->Height	=  28;
	OkBtn->Kind		= bkOK;
	OkBtn->Caption	= LoadStr( PW_Ok );
	OkBtn->OnClick	= PwdOkClick;

	CancelBtn			 = new TBitBtn( this );
	CancelBtn->Parent	 = this;
	CancelBtn->Left	 = 205;
	CancelBtn->Top		 =  72;
	CancelBtn->Width	 =  90;
	CancelBtn->Height	 =  28;
	CancelBtn->Kind	 = bkCancel;
	CancelBtn->Caption = LoadStr( PW_Cancel);
}

//---------------------------------------------------------------------------
__fastcall TPasswordDlg::~TPasswordDlg( void ) {
	delete CancelBtn;
	delete OkBtn;
	delete PwdEdit;
	delete PwdTxt;
}

//---------------------------------------------------------------------------
/* Convert filename (and file comment string) into "internal" charset (ISO).
 * This function assumes that Zip entry filenames are coded in OEM (IBM DOS)
 * codepage when made on:
 *  -> DOS (this includes 16-bit Windows 3.1)  (FS_FAT_  {0} )
 *  -> OS/2                                    (FS_HPFS_ {6} )
 *  -> Win95/WinNT with Nico Mak's WinZip      (FS_NTFS_ {11} && hostver == "5.0" {50} )
 *
 * All other ports are assumed to code zip entry filenames in ISO 8859-1.
 * But norton Zip v1.0 sets the host byte as OEM(0) but does use the ISO set,
 * thus archives made by NortonZip are not recognized as being ISO.
 * (In this case you need to set the CodePage property manualy to cpNone.)
 * When ISO is used in the zip archive there is no need for translation
 * and so we call this cpNone.
 */
void __fastcall TZipBuilder::ConvertOem2Iso( char *Source, CodePageDirection Direction ) {
   // ShowMessage( IntToHex( GetUserDefaultLCID(), 4 ) );
	if ( FCodePage == cpAUTO && (FHostNum == FS_FAT_ || FHostNum == FS_HPFS_ || (FHostNum == FS_NTFS_ && FHostVer == 50))
			|| FCodePage == cpOEM ) {
		for( unsigned char *p = (unsigned char *)Source; *p; p++ )
			if ( *p & 0x80 )
				if ( Direction == cpdOEM2ISO )
					::OemToCharBuff( (char *)p, (char *)p, 1 );
				else
					::CharToOemBuff( (char *)p, (char *)p, 1 );
	}
}

//---------------------------------------------------------------------------
int __fastcall TZipBuilder::GetZipVers( void ) {
	bool AutoLoad = false;	// User's pgm did load the DLL, so let him unload it.

	if ( !ZipDllHandle ) {
		AutoLoad = true;		// User's program didn't load the DLL.
		Load_Zip_Dll();		// Load it...
	}
	if ( !ZipDllHandle ) return 0;	// Load failed - error msg was shown to user.

	int Result = GetZipDllVersion();

	if ( AutoLoad ) Unload_Zip_Dll();
	return Result;
}

//---------------------------------------------------------------------------
int  __fastcall TZipBuilder::GetUnzVers( void ) {
	bool AutoLoad = false;	// User's pgm did load the DLL, so let him unload it.

	if ( !UnzDllHandle ) {
		AutoLoad = true;		// User's program didn't load the DLL.
		Load_Unz_Dll();		// Load it...
	}
	if ( !UnzDllHandle ) return 0;	// Load failed - error msg was shown to user.

	int Result = GetUnzDllVersion();

	if ( AutoLoad ) Unload_Unz_Dll();
	return Result;
}

//---------------------------------------------------------------------------
// We'll normally have a TStringList value, since TStrings itself is an abstract class.
void __fastcall TZipBuilder::SetFSpecArgs( Classes::TStrings *Value ) {
	FFSpecArgs->Assign( Value );
}

//---------------------------------------------------------------------------
// We'll normally have a TStringList value, since TStrings itself is an abstract class.
void __fastcall TZipBuilder::SetFSpecArgsExcl( Classes::TStrings *Value ) {
	FFSpecArgsExcl->Assign( Value );
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::SetFileName( String Value ) {
	FZipFileName = Value;
	// Automatically build a new TList of contents in "ZipContents".
	if ( !ComponentState.Contains( csDesigning ) ) List();
}

//---------------------------------------------------------------------------
// NOTE: we will allow a dir to be specified that doesn't exist,
// since this is not the only way to locate the DLLs.
void __fastcall TZipBuilder::SetDLLDirectory( String Value ) {
	if ( Value != FDLLDirectory ) {
		int ValLen = Value.Length();

		// If there is a trailing '\' in dirname, cut it off:
		if ( ValLen > 0 )	 // Shorten the dirname by one.
			if ( Value[ ValLen ] == '\\' ) Value.SetLength( ValLen - 1 );
		FDLLDirectory = Value;
	}
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::SetMaxVolumeSize( long Value ) {
	if ( Value >= 0 ) FMaxVolumeSize = Value;
}
long __fastcall TZipBuilder::GetMaxVolumeSize( void ) {
	return (long)FMaxVolumeSize;
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::SetFreeOnDisk1( long Value ) {
	if ( Value >= 0 ) FFreeOnDisk1 = Value;
}
long __fastcall TZipBuilder::GetFreeOnDisk1( void ) {
	return (long)FFreeOnDisk1;
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::SetMinFreeVolSize( long Value ) {
	if ( Value > 0 ) FMinFreeVolSize = Value;
}

//---------------------------------------------------------------------------
int __fastcall TZipBuilder::GetCount( void ) {
	return ( FZipFileName != "" ) ? FZipContents->Count : 0;
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::SetPasswordReqCount( unsigned int prc ) {
	if ( prc != FPasswordReqCount )
		FPasswordReqCount = min( prc, 15U );
}

//---------------------------------------------------------------------------
String __fastcall TZipBuilder::GetZipComment( void ) {
	String  Result;
   char   *buf = new char[ FZipComment.Length() + 1 ];

	StrPLCopy( buf, FZipComment, FZipComment.Length() + 1 );
	ConvertOem2Iso( buf, cpdOEM2ISO );
   Result = buf;
	delete[] buf;
   return Result;
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::SetZipComment( String zComment ) {
	char						  *CommentBuf = NULL;
	struct ZipEndOfCentral  EOC;
	unsigned short				len;
	bool							Fatal = false;

	FInFileHandle = -1;
	try {
		len        = (unsigned short)zComment.Length();
		CommentBuf = new char[ len + 1 ];
		StrPLCopy( CommentBuf, zComment, len + 1 ); //v1.52k

		if ( len ) ConvertOem2Iso( CommentBuf, cpdISO2OEM );
		FZipComment = CommentBuf;

		if ( !FZipFileName.Length() )
			throw EZipBuilder( DS_NoInFile );

		FInFileHandle = FileOpen( FZipFileName, fmShareDenyWrite | fmOpenReadWrite );
		if ( FInFileHandle == -1 )
			throw EZipBuilder( DS_FileOpen );
		if ( FileSeek( FInFileHandle, (SeekInt)FZipEOC, 0 ) == -1 )
			throw EZipBuilder(  DS_FailedSeek );
		if ( FileRead( FInFileHandle, &EOC, sizeof( EOC ) ) != sizeof( EOC ) || EOC.HeaderSig != EndCentralDirSig )
			throw EZipBuilder( DS_EOCBadRead );
		EOC.ZipCommentLen = len;
		if ( FileSeek( FInFileHandle, -(SeekInt)(signed)sizeof( EOC ), 1 ) == -1 )
			throw EZipBuilder( DS_FailedSeek );
		Fatal = true;
		if ( FileWrite( FInFileHandle, &EOC, sizeof( EOC ) ) != sizeof( EOC ) )
			throw EZipBuilder( DS_EOCBadWrite );
		if ( FileWrite( FInFileHandle, CommentBuf, len ) != len )
			throw EZipBuilder( DS_NoWrite );
		Fatal = false;
		// if SetEOF fails we get garbage at the end of the file, not nice but
		// also not important.
		SetEndOfFile( (HANDLE)FInFileHandle );
   }
	catch ( const EZipBuilder &ezl ) {
		ShowExceptionError( ezl );
		FZipComment = "";
	}
	catch ( const MEMEXCEPT &me ) {
		ShowZipMessage( GE_NoMem );
		FZipComment = "";
   }
	delete[] CommentBuf;
	if ( FInFileHandle != -1 )
		FileClose( FInFileHandle );
	if ( Fatal )	// Try to read the zipfile, maybe it still works.
		List();
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::SetSFXIcon( TIcon *aIcon ) {
	FSFXIcon->Assign( aIcon );
}

//---------------------------------------------------------------------------
// We do not want that this can be changed, but we do want to see it in the OI.
void __fastcall TZipBuilder::SetVersionInfo( String Value ) {
}


//---------------------------------------------------------------------------
// Free the storage used for dir entries and Empty FZipContents.
void __fastcall TZipBuilder::FreeZipDirEntryRecords( void ) {
	// Dispose of the memory pointed-to by all entries.
	for( int i = 0; i < FZipContents->Count; i++ ) if ( FZipContents->Items[ i ] ) {
		delete[] (reinterpret_cast<ZipDirEntry *>(FZipContents->Items[ i ]))->ExtraData;
		delete reinterpret_cast<ZipDirEntry *>(FZipContents->Items[ i ]);
	}
	// Delete all pointers from the TList itself.
	FZipContents->Clear();
	// The FZipContents TList will be deleted when the component destructor is called.
}

//---------------------------------------------------------------------------
// RCV: Changed in V1.5. This new version of this function looks at the central
// dir and not as before in all the local dirs in the archive.
// This should be faster, specifically on diskettes and does work in case of
// Disk Spanning.
// The length of a SFX block and the alignment of this block don't matter.
// Also SFX code that contains a false local signature isn't important.
void __fastcall TZipBuilder::List( void ) { // All work is local - no DLL calls.
	struct ZipEndOfCentral  EOC;
	struct ZipCentralHeader CEH;
	ZipDirEntry				  *pzd;
	unsigned long				OffsetDiff;
	char							Name[ MAX_PATH ], *fc = NULL;

	// Can't do LIST at design time.
	if ( ComponentState.Contains( csDesigning ) ) return;

	// Zero out any previous entries.
	FreeZipDirEntryRecords();

	FRealFileSize = 0;
	FZipSOC		  = 0;
	FSFXOffset	  = 0;
	FIsSpanned    = False;

	// Don't complain - this may intentionally be a new zip file.
	if ( !FileExists( FZipFileName ) ) {
		if ( FOnDirUpdate ) FOnDirUpdate( this );
		return;
	}
	Screen->Cursor = crHourGlass;
	try {
		FInFileName	= FZipFileName;
		FDrive		= ExtractFileDrive( ExpandFileName( FInFileName ) ) + "\\";

		if ( !IsDiskPresent() )	// Not present, raise an exception!
			throw EZipBuilder( DS_DriveNoMount, FDrive );

		CheckIfLastDisk( EOC, true );
		FTotalDisks = EOC.ThisDiskNo;	// Needed if GetNewDisk() is called.

		// This could also be set to True if it's the first and only disk.
		if ( EOC.ThisDiskNo > 0 ) FIsSpanned = true;

		// Do we have to request for a previous disk first?
		if ( EOC.ThisDiskNo != EOC.CentralDiskNo ) {
			GetNewDisk( EOC.CentralDiskNo );
			FFileSize = FileSeek( FInFileHandle, 0, 2 );	//v1.52j
			OffsetDiff = EOC.CentralOffset;	//v1.52j
		} else	//v1.52j
			// Due to the fact that v1.3, v1.4 and v1.45 programs do not change the archives
			// EOC and CEH records in case of a SFX conversion (and back) we have to
			// make this extra check.
			OffsetDiff = FFileSize - EOC.CentralSize - sizeof( EOC ) - EOC.ZipCommentLen;
		FWrongZipStruct = false;
		if ( EOC.CentralOffset != OffsetDiff )	{	// Issue a warning only.
			FWrongZipStruct = true;		// We need this in the ConvertXxx functions.
			ShowZipMessage( LI_WrongZipStruct );
		}
		// Now we can go to the start of the Central directory.
		if ( FileSeek( FInFileHandle, (SeekInt)OffsetDiff, 0 ) == -1 )
			throw EZipBuilder( LI_ReadZipError );

		FZipSOC    = OffsetDiff;
		FSFXOffset = FFileSize;
		if ( FFileSize == 22 ) FSFXOffset = 0; //v1.52L

		// Read every entry: The central header and save the information.
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// Read a central header.
			while( FileRead( FInFileHandle, &CEH, sizeof( CEH ) ) != sizeof( CEH ) ) {	//v1.52j
				// It's possible that we have the central header split up.
				if ( FDiskNr >= EOC.ThisDiskNo )
					throw EZipBuilder( DS_CEHBadRead );
				// We need the next disk with central header info.
				GetNewDisk( FDiskNr + 1 );
			}
			if ( CEH.HeaderSig != CentralFileHeaderSig ) throw EZipBuilder( DS_CEHWrongSig );

			// Now the filename.
			if ( FileRead( FInFileHandle, Name, CEH.FileNameLen ) != CEH.FileNameLen )
				throw EZipBuilder( DS_CENameLen );
			FHostNum = CEH.VersionMadeBy1;
			FHostVer = CEH.VersionMadeBy0;
			Name[ CEH.FileNameLen ] = '\0';
			ConvertOem2Iso( Name, cpdOEM2ISO );

			// Create a new ZipDirEntry record
			pzd = new ZipDirEntry;	// These will be deleted in: FreeZipDirEntryRecords().
			// Copy the information from the central header.
			memcpy( pzd, &CEH.VersionMadeBy0, LocalDirEntrySize );
			pzd->FileName  = ReplaceForwardSlash( Name );
			pzd->Encrypted = pzd->Flag & 0x01;

			// Read the extra data if present new v1.6
			if ( pzd->ExtraFieldLength ) {
				pzd->ExtraData = new unsigned char[ CEH.ExtraLen ];
				if ( FileRead( FInFileHandle, pzd->ExtraData, CEH.ExtraLen ) != CEH.ExtraLen )
					throw EZipBuilder( LI_ReadZipError );
			} else pzd->ExtraData = NULL;

			// Read the FileComment if present and save.
			if ( CEH.FileComLen ) {
				fc = new char[ CEH.FileComLen + 1 ];
				if ( FileRead( FInFileHandle, fc, CEH.FileComLen ) != CEH.FileComLen )
					throw EZipBuilder( DS_CECommentLen );
				fc[ CEH.FileComLen ] = '\0';
				ConvertOem2Iso( fc, cpdOEM2ISO );
				pzd->FileComment = AnsiString( fc );
				delete[] fc;
				fc = NULL;
			}
			if ( FUseDirOnlyEntries || ExtractFileName( pzd->FileName ) != "" ) {
				// Add it to our contents tabel.
				FZipContents->Add( pzd );
				// Notify user of the next entry in the ZipDir.
				if ( FOnNewName ) FOnNewName( this, i + 1, *pzd );
			} else {
				delete[] pzd->ExtraData;
				delete pzd;
			}
			// Calculate the earliest Local Header start.
			if ( FSFXOffset > (int)CEH.RelOffLocal ) FSFXOffset = (int)CEH.RelOffLocal;
		}
		FTotalDisks = EOC.ThisDiskNo;			// We need this when we are going to extract.
   }
	catch ( const EZipBuilder &ezl ) {		// Catch all Zip List specific errors.
		ShowExceptionError( ezl );
		FZipFileName = "";
		FSFXOffset = 0;
	}
	catch ( const MEMEXCEPT &me ) {
		ShowZipMessage( GE_NoMem );
		FZipFileName = "";
		FSFXOffset = 0;
   }
	catch( const Exception &E ) {
		ShowZipMessage( LI_ErrorUnknown, "\n" + E.Message );
		FZipFileName = "";
		FSFXOffset = 0;
	}
	catch ( ... ) {
		ShowZipMessage( LI_ErrorUnknown );
		FZipFileName = "";
		FSFXOffset = 0;
	}
	delete[] fc;
	FSFXOffset += (OffsetDiff - EOC.CentralOffset);	// Correct the offset for v1.3, 1.4 and 1.45
	Screen->Cursor = crDefault;
	if ( FInFileHandle != -1 ) FileClose( FInFileHandle );
	// Let user's program know we just refreshed the zip dir contents.
	if ( FOnDirUpdate ) FOnDirUpdate( this );
}

//---------------------------------------------------------------------------
// Add a new suffix to the suffix string if contained in the set 'FAddStoreSuffixes'
void __fastcall TZipBuilder::AddSuffix( const AddStoreSuffix SufOption, String &sStr, int sPos ) {
	static char *SuffixStrings[] = { "gif", "png", "z", "zip", "zoo","arc", "lzh", "arj", "taz", "tgz", "lha", "exe" };

	if ( FAddStoreSuffixes.Contains( SufOption ) )
		sStr += ("." + AnsiString( SuffixStrings[ sPos ] ) + ":");
}

//---------------------------------------------------------------------------
// zp1 could actually be a ZipParms2 structure but the members used here are the same.
void __fastcall TZipBuilder::SetZipSwitches( String &NameOfZipFile, int zpVersion ) {
	ZipDLL::ZipParms1 *zp1 = ZipParms1;

	switch ( zpVersion ) {
		case 160:
			if ( FZipComment.Length() ) {		// New v1.6 write of ZipComment
				ZipParms2->fArchComment = new char[ FZipComment.Length() + 1 ];
				StrPLCopy( ZipParms2->fArchComment, FZipComment, FZipComment.Length() + 1 );
			}
			ZipParms2->fArchiveFilesOnly = ( FAddOptions.Contains(AddArchiveOnly) )  ? true : false;
			ZipParms2->fResetArchiveBit  = ( FAddOptions.Contains(AddResetArchive) ) ? true : false;
			// Copy the list of file specs. to exclude to a char pointer array.
			if ( FFSpecArgsExcl->Count ) {
				ZipParms2->fTotExFileSpecs = FFSpecArgsExcl->Count;
				ZipParms2->fExFiles = new ExcludedFileSpec[ FFSpecArgsExcl->Count ];
				for( int i = 0; i < FFSpecArgsExcl->Count; i++ ) {
					memset( ZipParms2->fExFiles + i, 0, sizeof( ExcludedFileSpec ) );
					ZipParms2->fExFiles[ i ].fFileSpec = new char[ FFSpecArgsExcl->Strings[ i ].Length() + 1 ];
					StrPLCopy( ZipParms2->fExFiles[ i ].fFileSpec, FFSpecArgsExcl->Strings[ i ], FFSpecArgsExcl->Strings[ i ].Length() + 1 );
				}
			}
		case 151:
			if ( FTempDir.Length() ) {			// Name of temp directory.
				ZipParms2->fTempPath = new char[ FTempDir.Length() + 1 ];
				StrPLCopy( ZipParms2->fTempPath, FTempDir, FTempDir.Length() + 1 );
			}
		default:		// For all versions
			zp1->fVersion = ZIPVERSION;		// Version of the component and we expect the DLL to be.
			zp1->fCaller  = this;				// point to our VCL instance; returned in callback.

			/* Since we don't want the DLL's to generate their own dialog boxes
				for error reporting, we'll set the window handle. Since we
				are doing this, we must also set fQuiet to true. */
			zp1->fHandle = FHandle;				// Used for DLL dialogs - esp: password.
			zp1->fQuiet  = true;				   // We'll report errors upon notification in our callback.

			zp1->ZCallbackFunc  = ZCallback;	// Pass addr of function to be called from DLL.

			zp1->fJunkSFX = false;				// if True, Convert input .EXE file to .ZIP.

			String SufStr = "";
			for( int i = 0; i < 1 + (int)assEXE; i++ ) AddSuffix( (AddStoreSuffix)i, SufStr, i );
			if ( SufStr.Length() ) {
				SufStr.Delete( SufStr.Length(), 1 );
				zp1->pSuffix = new char[ SufStr.Length() + 1 ];
				StrPLCopy( zp1->pSuffix, SufStr, SufStr.Length() + 1 );
			}
			zp1->fVolume        = false;		// if True, Include volume label from root dir.
			zp1->fExtra         = false;		// if True, Include extended file attributes.

			//  fUseDate and fDate are not yet supported
			zp1->fUseDate		  = false;		// if True, Exclude files earlier than specified date.
			//  Date = "100592";					// Date to include files after; only used if fDate=TRUE.

			zp1->fLevel = FAddCompLevel;		// Compression level (0 - 9, 0=none and 9=best).
			zp1->fCRLF_LF       = false;		// if True, Translate text file CRLF to LF (if dest Unix).
			zp1->fGrow          = true;		// if True, Allow appending to a zip file (-g).

			zp1->fDeleteEntries = false;		// distinguish between Add and Delete

			zp1->fTraceEnabled	= (FTrace)	 ? true : false;
			zp1->fVerboseEnabled = (FVerbose) ? true : false;
			if ( zp1->fTraceEnabled && !FVerbose )
				zp1->fVerboseEnabled = true;	// If tracing, we want verbose also.

			// Convert all filenames to 8x3 format.
			zp1->fForce      = ( FAddOptions.Contains(AddForceDOS) ) ? true : false;
			// Make zipfile's timestamp same as newest file.
			zp1->fLatestTime = ( FAddOptions.Contains(AddZipTime) )  ? true : false;
			// Dangerous, beware!
			zp1->fMove       = ( FAddOptions.Contains(AddMove) )     ? true : false;
			zp1->fFreshen    = ( FAddOptions.Contains(AddFreshen) )  ? true : false;
			zp1->fUpdate     = ( FAddOptions.Contains(AddUpdate) )   ? true : false;
			if ( zp1->fFreshen && zp1->fUpdate )
				zp1->fFreshen = false;  	// Update has precedence over freshen.
			zp1->fEncrypt	  = ( FAddOptions.Contains(AddEncrypt) )	? true : false;

			/* NOTE: If user wants recursion, then he probably also wants
				AddDirNames, but we won't demand it. */
			zp1->fRecurse	  = ( FAddOptions.Contains(AddRecurseDirs) ) ? true : false;
			//zp1->fNoRecurseFiles = 0x02;

			// Don't store dirnames by themselves is the default.
			zp1->fNoDirEntries = ( FAddOptions.Contains(AddSeparateDirs) ) ? false : true;

			zp1->fJunkDir    = (!FAddOptions.Contains(AddDirNames) )    ? true : false;
			zp1->fSystem	  = ( FAddOptions.Contains(AddHiddenFiles) ) ? true : false;

			zp1->pZipFN = new char[ NameOfZipFile.Length() + 1 ];
			StrPLCopy( zp1->pZipFN, NameOfZipFile, NameOfZipFile.Length() + 1 );	// Name of zip file.
			zp1->pZipPassword = new char[ FPassword.Length() + 1 ];
			StrPLCopy( zp1->pZipPassword, FPassword, PASSWORDLEN + 1 );				// Password for encryption.
	}
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::SetUnZipSwitches( String &NameOfZipFile, int UzpVersion ) {
	UnzipDLL::UnZipParms1 *uz1 = UnZipParms1;

	uz1->fVersion = UNZIPVERSION;		// Version we expect the DLL to be
	uz1->fCaller  = this;				// point to our VCL instance; returned in callback.

	/* Since we don't want the DLLs to generate their own dialog boxes
		for error reporting, we'll set the window handle. Since we
		are doing this, we must also set fQuiet to true.					*/
	uz1->fHandle = FHandle;				// Used for DLL dialogs - esp: password.
	uz1->fQuiet  = true;  				// We'll report errors upon notification in our callback.

	uz1->ZCallbackFunc = ZCallback;	// Pass addr of function to be called from DLL.

   uz1->fWantedCodePage = FCodePage;
	uz1->fTraceEnabled   = (FTrace)   ? true : false;
	uz1->fVerboseEnabled = (FVerbose) ? true : false;
	if ( uz1->fTraceEnabled && !uz1->fVerboseEnabled )
		uz1->fVerboseEnabled = true;	// If tracing, we want verbose also.

	uz1->fQuiet    = true;				// No DLL error reporting.
	uz1->fComments = false;				// Zipfile comments - not supported.
	uz1->fConvert  = false;				// ASCII/EBCDIC conversion - not supported.

	uz1->fDirectories = ( FExtrOptions.Contains( ExtrDirNames ) )	? true : false;
	uz1->fOverwrite   = ( FExtrOptions.Contains( ExtrOverWrite ) )	? true : false;
	uz1->fFreshen     = ( FExtrOptions.Contains( ExtrFreshen ) )	? true : false;
	uz1->fUpdate      = ( FExtrOptions.Contains( ExtrUpdate ) )		? true : false;
	uz1->fTest	      = ( FExtrOptions.Contains( ExtrTest ) )		? true : false;

	// Update has precedence over freshen.
	if ( uz1->fFreshen && uz1->fUpdate ) uz1->fFreshen = false;

	uz1->pZipFN = new char[ NameOfZipFile.Length() + 1 ];	// Allocate room for null terminated string.
	StrPLCopy( uz1->pZipFN, NameOfZipFile, NameOfZipFile.Length() + 1 );		// Name of zip file.

	if ( UzpVersion >= 160 ) UnZipParms2->fPwdReqCount = FPasswordReqCount;
	// We have to be carefull doing an unattended Extract when a password is needed
	// for some file in the archive. We set it to an unlikely password, this way
	// encrypted files won't be extracted.
	// From verion 1.60 and up the event OnPasswordError is called in this case.
	if ( UzpVersion < 160 && FUnattended && FAddOptions.Contains( AddEncrypt ) && FPassword == "" ) {
		uz1->pZipPassword = new char[ PASSWORDLEN + 1 ];
		memset( uz1->pZipPassword, '~', PASSWORDLEN );
		uz1->pZipPassword[ PASSWORDLEN ] = 0;
	} else {
		uz1->pZipPassword = new char[ FPassword.Length() + 1 ];	// Allocate room for null terminated string.
		StrPLCopy( uz1->pZipPassword, FPassword, PASSWORDLEN + 1 );	// Password for encryption/decryption.
	}
}

//---------------------------------------------------------------------------
String __fastcall TZipBuilder::GetAddPassword( void ) {
	String p1, p2 = "";

   if ( FUnattended ) ShowZipMessage( PW_UnatAddPWMiss );
	else {
		if ( GetPassword( LoadZipStr( PW_Caption, RESOURCE_ERROR ), LoadStr( PW_MessageEnter ), p1 ) && p1 != "" ) {
			if ( GetPassword( LoadZipStr( PW_Caption, RESOURCE_ERROR ), LoadStr( PW_MessageConfirm ), p2 ) && p2 != "" ) {
				if ( AnsiCompareStr( p1, p2 ) )
					ShowZipMessage( GE_WrongPassword );
	   		else
					if ( GAssignPassword ) FPassword = p2;
			}
		}
	}
	return p2;
}

//---------------------------------------------------------------------------
// Same as GetAddPassword, but does NOT verify
String __fastcall TZipBuilder::GetExtrPassword( void ) {
	String p1 = "";

	if ( FUnattended ) ShowZipMessage( PW_UnatExtPWMiss );
	else if ( GetPassword( LoadZipStr( PW_Caption, RESOURCE_ERROR ), LoadStr( PW_MessageEnter ), p1 ) && p1 != "" )
		if ( GAssignPassword ) FPassword = p1;
	return p1;
}

//---------------------------------------------------------------------------
bool __fastcall TZipBuilder::GetPassword( String DialogCaption, String MsgTxt, String &ResultStr ) {
	bool OkClicked;

	TPasswordDlg *Pdlg = new TPasswordDlg( this, 0 );
	ResultStr = Pdlg->ShowModalPwdDlg( DialogCaption, MsgTxt );
	OkClicked = Pdlg->OkClicked;
	delete Pdlg;
	return OkClicked;
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::Add( void ) {
	String TmpZipName;
	bool   AutoLoad = false;
	int    SFXResult;

	FSuccessCnt = FErrCode = 0;
	FMessage    = "";
	if ( !FFSpecArgs->Count ) {
		ShowZipMessage( AD_NothingToZip );
		return;
	}
	/* We must allow a zipfile to be specified that doesn't already exist,
	 * so don't check here for existence. */
	if ( FZipFileName == "" ) {   // Make sure we have a zip filename.
		ShowZipMessage( GE_NoZipSpecified );
		return;
	}
	// We can not do an Unattended Add if we don't have a password.
	if ( FUnattended && FAddOptions.Contains( AddEncrypt ) && FPassword == "" ) {
		ShowZipMessage( AD_UnattPassword );
		return;
	}
	if ( FZipBusy ) return;
	// Make sure we can't get back in here while work is going on.
	FCancel = false;

	if ( UpperCase( ExtractFileExt( FZipFileName ) ) == ".EXE" && !FSFXOffset ) {
		if ( !FileExists( FZipFileName ) ) {
			try {
				// This is the first 'Add' operation following creation of a new
				// .EXE archive.  We need to add the SFX code now, before we add
				// the files.
				if ( (SFXResult = ConvertSFX( true )) != 0 )
					throw EZipBuilder( AD_AutoSFXWrong, SFXResult );
			} catch ( const EZipBuilder &ers ) {
				// All SFX creation errors will be catched and returned in this one message.
				ShowExceptionError( ers );
				return;
			}
		}
	}
	if ( !ZipDllHandle ) {
		AutoLoad = true;				// User's program didn't load the DLL.
		Load_Zip_Dll();				// Load it...
	}
	if ( !ZipDllHandle ) return;	// Load failed - error msg was shown to user.

	// If we are using disk spanning, first create a temporary file to do the Add.
	if ( FAddOptions.Contains( AddDiskSpan ) || FAddOptions.Contains( AddDiskSpanErase ) ) {
		// We can't do this type of Add() on a spanned archive.
		if ( FAddOptions.Contains( AddFreshen ) || FAddOptions.Contains( AddUpdate ) ) {
			ShowZipMessage( AD_NoFreshenUpdate );
			return;
		}
      // We can't Add and copy a SFX archive as spanned.
		if ( UpperCase( ExtractFileExt( FZipFileName ) ) == ".EXE" ) {
			ShowZipMessage( DS_NoSFXSpan );
			return;
		}
		char NewName[ MAX_PATH ];
		if ( FTempDir == "" ) {
			::GetTempPath( MAX_PATH, NewName );
			::GetTempFileName( NewName, "zip", 0, NewName );
		} else {
			FTempDir = AppendSlash( FTempDir );
			::GetTempFileName( FTempDir.c_str(), "zip", 0, NewName );
		}
		TmpZipName = NewName;
		DeleteFile( TmpZipName );
      if ( FVerbose && FOnMessage )
			OnMessage( this, 0, "Temporary zipfile: " + TmpZipName );
	} else TmpZipName = FZipFileName;

	FZipBusy = true;

	int DLLVers = ZipVers;	// If DLL version < 151 we use the old ZipParams.
	try {  // Pass in a ptr to parms.
		if ( DLLVers < 151 ) {
			ZipParms1 = new ZipDLL::ZipParms1;
			memset( ZipParms1, 0, sizeof( *ZipParms1 ) );
			SetZipSwitches( TmpZipName, DLLVers );

			/* Copy filenames from the Stringlist to new var's we will alloc
			 * storage for.  This lets us append the null needed by the DLL. */
			for( int i = 0; i < FFSpecArgs->Count; i++ ) {
				ZipParms1->pFileNames[ i ] = new char[ FFSpecArgs->Strings[ i ].Length() + 1 ];
				StrPLCopy( ZipParms1->pFileNames[ i ], FFSpecArgs->Strings[ i ], FFSpecArgs->Strings[ i ].Length() + 1 );
			}
			ZipParms1->fSeven = 7;	// used to QC the data structure passed to DLL
		} else {	// We have at least dll version 1.51
			ZipParms2 = new ZipDLL::ZipParms2;
			memset( ZipParms2, 0, sizeof( *ZipParms2 ) );
			SetZipSwitches( TmpZipName, DLLVers );

			ZipParms2->fFDS = new FileData[ FFSpecArgs->Count ];
			for( int i = 0; i < FFSpecArgs->Count; i++ ) {
				memset( ZipParms2->fFDS + i, 0, sizeof( FileData ) );
				ZipParms2->fFDS[ i ].fFileSpec = new char[ FFSpecArgs->Strings[ i ].Length() + 1 ];
				StrPLCopy( ZipParms2->fFDS[ i ].fFileSpec, FFSpecArgs->Strings[ i ], FFSpecArgs->Strings[ i ].Length() + 1 );
			}
			ZipParms2->fSeven = 7;
		}
		ZipParms1->fArgc = FFSpecArgs->Count;
		FSuccessCnt = ZipDllExec( ZipParms1 );
		// If Add was successfull and we want spanning copy the temporary file to the destination.
		if ( FSuccessCnt && (FAddOptions.Contains( AddDiskSpan ) || FAddOptions.Contains( AddDiskSpanErase )) ) {
			if ( WriteSpan( TmpZipName, FZipFileName ) ) FSuccessCnt = 0;
			DeleteFile( TmpZipName );
		}
	} catch ( ... ) {
		ShowZipMessage( GE_FatalZip );
	}
	FFSpecArgs->Clear();
	FFSpecArgsExcl->Clear();
	/* Free the memory for the zipfilename and parameters
	 * we know we had a filename, so we'll dispose it's space. */
	delete[]	ZipParms1->pSuffix;
	delete[] ZipParms1->pZipFN;
	delete[] ZipParms1->pZipPassword;
	if ( DLLVers < 151 ) {
		// Loop thru each parameter filename and dispose it's space.
		for( int i = ZipParms1->fArgc - 1; i >= 0; i-- )
			delete[] ZipParms1->pFileNames[ i ];
		delete ZipParms1;
	} else {
		delete[] ZipParms2->fTempPath;
		delete[] ZipParms2->fArchComment;
		for( int i = ZipParms2->fArgc - 1; i >= 0; i-- )
			delete[] ZipParms2->fFDS[ i ].fFileSpec;
		delete[] ZipParms2->fFDS;
		for( int i = ZipParms2->fTotExFileSpecs - 1; i >= 0; i-- )
			delete[] ZipParms2->fExFiles[ i ].fFileSpec;
		delete[] ZipParms2->fExFiles;
		delete ZipParms2;
	}
	ZipParms1 = NULL;

	if ( AutoLoad ) Unload_Zip_Dll();

	FCancel	= false;
	FZipBusy	= false;
	if ( FSuccessCnt > 0 ) List();  // Update the Zip Directory by calling List() function.
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::Delete( void ) {
	bool AutoLoad = false;

	FSuccessCnt = FErrCode = 0;
	FMessage = "";
	if ( !FFSpecArgs->Count ) {
		ShowZipMessage( DL_NothingToDel );
		return;
	}
	if ( !FileExists( FZipFileName ) ) {
		ShowZipMessage( GE_NoZipSpecified );
		return;
	}
	if ( FZipBusy ) return;
	FCancel  = false;

	if ( !ZipDllHandle ) {
		AutoLoad = true;				// User's program didn't load the DLL.
		Load_Zip_Dll();				// Load it...
	}
	if ( !ZipDllHandle ) return;	// Load failed - error msg was shown to user.
	FZipBusy = true;					// Delete uses the ZIPDLL, so it shares the FZipBusy flag.

	int DLLVers = ZipVers;
	try {  // Pass in a ptr to parms.
		if ( DLLVers < 151 ) {
			ZipParms1 = new ZipDLL::ZipParms1;
			memset( ZipParms1, 0, sizeof( *ZipParms1 ) );
		} else {
			ZipParms2 = new ZipDLL::ZipParms2;
			memset( ZipParms2, 0, sizeof( *ZipParms2 ) );
		}
		SetZipSwitches( FZipFileName, DLLVers );

		// Override "Add" behavior assumed by SetZipSwitches.
		ZipParms1->fDeleteEntries = true;
		ZipParms1->fGrow			  = false;
		ZipParms1->fJunkDir		  = false;
		ZipParms1->fMove			  = false;
		ZipParms1->fFreshen		  = false;
		ZipParms1->fUpdate		  = false;
		ZipParms1->fRecurse		  = false;	 // Bug fix per Angus Johnson.
		ZipParms1->fEncrypt		  = false;   // You don't need the password to delete a file.

		if ( DLLVers < 151 ) {
			/* Copy filenames from the Stringlist to new var's we will allow
				storage for.  This lets us append the null needed by the DLL. */
			for( int i = 0; i < FFSpecArgs->Count; i++ ) {
				ZipParms1->pFileNames[ i ] = new char[ FFSpecArgs->Strings[ i ].Length() + 1 ];
				// ShowZipMessage( fFSpecArgs[ i ] ); // for debugging.
				// File to delete from archive.
				StrPLCopy( ZipParms1->pFileNames[ i ], FFSpecArgs->Strings[ i ], FFSpecArgs->Strings[ i ].Length() + 1 );
			}
			ZipParms1->fSeven = 7;	// used to QC the data structure passed to DLL
		} else {
			ZipParms2->fFDS = new FileData[ FFSpecArgs->Count ];
			for( int i = 0; i < FFSpecArgs->Count; i++ ) {
				memset( ZipParms2->fFDS + i, 0, sizeof( FileData ) );
				ZipParms2->fFDS[ i ].fFileSpec = new char[ FFSpecArgs->Strings[ i ].Length() + 1 ];
				StrPLCopy( ZipParms2->fFDS[ i ].fFileSpec, FFSpecArgs->Strings[ i ], FFSpecArgs->Strings[ i ].Length() + 1 );
			}
			ZipParms2->fSeven = 7;	// used to QC the data structure passed to DLL
		}
		// argc is now the no. of filespecs we want deleted.
		ZipParms1->fArgc = FFSpecArgs->Count;
		FSuccessCnt = ZipDllExec( ZipParms1 );
	} catch ( ... ) {
		ShowZipMessage( GE_FatalZip );
	}
	FFSpecArgs->Clear();
	FFSpecArgsExcl->Clear();
	delete[]	ZipParms1->pSuffix;
	delete[] ZipParms1->pZipFN;
	delete[] ZipParms1->pZipPassword;
	if ( DLLVers < 151 ) {
		for( int i = ZipParms1->fArgc - 1; i >= 0; i-- )
			delete[] ZipParms1->pFileNames[ i ];
		delete ZipParms1;
	} else {
		delete[] ZipParms2->fTempPath;
		delete[] ZipParms2->fArchComment;

		for( int i = ZipParms2->fArgc - 1; i >= 0; i-- )
			delete[] ZipParms2->fFDS[ i ].fFileSpec;
		delete[] ZipParms2->fFDS;
		for( int i = ZipParms2->fTotExFileSpecs - 1; i >= 0; i-- )
			delete[] ZipParms2->fExFiles[ i ].fFileSpec;
		delete[] ZipParms2->fExFiles;
		delete ZipParms2;
	}
	ZipParms1 = NULL;

	if ( AutoLoad ) Unload_Zip_Dll();

	FZipBusy = false;
	if ( FSuccessCnt > 0 ) List();  // Update the Zip Directory by calling List() function.
}


//---------------------------------------------------------------------------
TZipStream * __fastcall TZipBuilder::ExtractFileToStream( String FileName ) {
	// Use FileName if set, if not expect the filename in the FFSpecArgs.
	if ( FileName != "" ) {
		FFSpecArgs->Clear();
		FFSpecArgs->Add( FileName );
	}
	FZipStream->Clear();
//	ExtExtract( 1, (TStream *)NULL, false );
	ExtExtract( true );
	return ( FSuccessCnt != 1 ) ? NULL : FZipStream;
}

//---------------------------------------------------------------------------
void __fastcall TZipStream::SetPointer( void *Ptr, int Size ) {
	TMemoryStream::SetPointer( Ptr, Size );
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::Extract( void ) {
	ExtExtract( false );
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::ExtExtract( bool UseStream ) {
	String TmpZipName;
	bool   AutoLoad = false;
	int	 OldPRC = FPasswordReqCount;

	FSuccessCnt = FErrCode = 0;
	FMessage = "";
	if ( !FileExists( FZipFileName ) ) {
		ShowZipMessage( GE_NoZipSpecified );
		return;
	}
	FCancel  = false;
	if ( FUnzBusy ) return;

	// We have to be carefull doing an unattended Extract when a password is needed
	// for some file in the archive.
	if ( FUnattended && FPassword == "" && !FOnPasswordError ) {
		FPasswordReqCount = 0;
		ShowZipMessage( EX_UnAttPassword, "" );
	}

	if ( !UnzDllHandle ) {
		AutoLoad = true;				// user's program didn't load the DLL.
		Load_Unz_Dll();				// Load it...
	}
	if ( !UnzDllHandle ) return;	// Load failed - error msg was shown to user.

	// We do a check if we need UnSpanning first, this depends on
	// The number of the disk the EOC record was found on. ( provided by List() )
	// If we have a spanned set consisting of only one disk we don't use ReadSpan().
	if ( FTotalDisks ) {
		if ( FTempDir == "" ) {
			char NewName[ MAX_PATH ];
			::GetTempPath( MAX_PATH, NewName );
			TmpZipName = NewName;
		} else TmpZipName = AppendSlash( FTempDir );
		if ( ReadSpan( FZipFileName, TmpZipName ) ) {
			if ( AutoLoad ) Unload_Unz_Dll();
			return;
		}
		// We returned without an error, now  TmpZipName contains a real name.
	} else TmpZipName = FZipFileName;

	// Select the extract directory.
	if ( !UseStream && DirExists( FExtrBaseDir ) ) SetCurrentDir( FExtrBaseDir );

	int UnzDLLVers = UnzVers;	// If DLL version < 152 we use the old ZipParams.
	if ( UseStream && UnzDLLVers < 160 ) {
		if ( AutoLoad ) Unload_Unz_Dll();
		ShowZipMessage( EX_NoStreamDLL );
		return;
	}
	// Make sure we can't get back in here while work is going on.
	FUnzBusy = true;

	try {  // Pass in a ptr to parms.
		if ( UnzDLLVers < 152 ) {
			UnzipDLL::UnZipParms1 *uz1 = UnZipParms1 = new UnzipDLL::UnZipParms1;
			memset( uz1, 0, sizeof( *uz1 ) );
			SetUnZipSwitches( TmpZipName, UnzDLLVers );

			/* Copy filenames from the Stringlist to new var's we will alloc
			 * storage for.  This lets us append the null needed by the DLL. */
			for( int i = 0; i < FFSpecArgs->Count; i++ ) {
				uz1->pFileNames[ i ] = new char[ FFSpecArgs->Strings[ i ].Length() + 1 ];
				StrPLCopy( uz1->pFileNames[ i ], FFSpecArgs->Strings[ i ], FFSpecArgs->Strings[ i ].Length() + 1 );
			}
			uz1->fArgc  = FFSpecArgs->Count;
			uz1->fSeven = 7;
		} else {
			UnzipDLL::UnZipParms2 *uz2 = UnZipParms2 = new UnzipDLL::UnZipParms2;
			memset( uz2, 0, sizeof( *uz2 ) );
			SetUnZipSwitches( TmpZipName, UnzDLLVers );

			uz2->fUFDS = new UnzFileData[ FFSpecArgs->Count ];
			memset( uz2->fUFDS, 0, sizeof( UnzFileData ) * FFSpecArgs->Count );
			for( int i = 0; i < FFSpecArgs->Count; i++ ) {
				uz2->fUFDS[ i ].fFileSpec = new char[ FFSpecArgs->Strings[ i ].Length() + 1 ];
				StrPLCopy( uz2->fUFDS[ i ].fFileSpec, FFSpecArgs->Strings[ i ], FFSpecArgs->Strings[ i ].Length() + 1 );
			}
			uz2->fArgc = FFSpecArgs->Count;
			if ( UseStream ) for( int i = 0; i < Count; i++ ) {	// Find the wanted file in the ZipDirEntry list.
				ZipDirEntry *zde = (ZipDirEntry *)ZipContents->Items[ i ];
				if ( !AnsiStrIComp( FFSpecArgs->Strings[ 0 ].c_str(), zde->FileName.c_str() ) ) {	// Found?
					FZipStream->SetSize( zde->UncompressedSize );
					uz2->fUseOutStream  = true;
					uz2->fOutStream     = FZipStream->Memory;
					uz2->fOutStreamSize = zde->UncompressedSize;
					uz2->fArgc          = 1;
					break;
				}
			}
			uz2->fSeven = 7;
		}
		// fArgc is now the no. of filespecs we want extracted.
		if ( !UseStream || (UseStream && UnZipParms2->fUseOutStream) )
			FSuccessCnt = UnzDllExec( UnZipParms1 );
		// Remove from memory if stream is not Ok.
		if ( UseStream && FSuccessCnt != 1 ) FZipStream->Clear();
		// If UnSpanned we still have this temporary file hanging around.
		if ( FTotalDisks > 0 ) DeleteFile( TmpZipName );
	} catch ( ... ) {
		ShowZipMessage( EX_FatalUnZip );
	}
	FFSpecArgs->Clear();

	// Free all allocated memory.
	delete[] UnZipParms1->pZipFN;
	delete[] UnZipParms1->pZipPassword;
	if ( UnzDLLVers < 152 ) {
		for( int i = UnZipParms1->fArgc - 1; i >= 0; i-- )
			delete[] UnZipParms1->pFileNames[ i ];
		delete UnZipParms1;
	} else {
		for( int i = UnZipParms2->fArgc - 1; i >= 0; i-- )
			delete[] UnZipParms2->fUFDS[ i ].fFileSpec;
		delete[] UnZipParms2->fUFDS;
		delete UnZipParms2;
	}
	UnZipParms1 = NULL;

	if ( FUnattended && FPassword == "" && !FOnPasswordError )
		PasswordReqCount = OldPRC;

	if ( AutoLoad ) Unload_Unz_Dll();

	FCancel  = false;
	FUnzBusy = false;
	// No need to call the List() function; contents unchanged.
}

//---------------------------------------------------------------------------
// This code tries to locate the DLL before loading it.
// The user can specify a dir in the DLLDirectory property.
// The user's dir is our first choice, but we'll still try the
// standard Windows DLL dirs (App. start dir, Current dir, Windows System, Windows, Path).
void __fastcall TZipBuilder::Load_Zip_Dll( void ) {
	String FullPath = "ZIPDLL.DLL";

	if ( FDLLDirectory != "" && FileExists( FDLLDirectory + "\\ZIPDLL.DLL" ) )
			FullPath = FDLLDirectory + "\\ZIPDLL.DLL";

	long OldMode = ::SetErrorMode( SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX );

	try {
		if ( ( ZipDllHandle = ::LoadLibrary( FullPath.c_str() )) != NULL ) {
			if ( FTrace ) ShowZipMessage( LZ_ZipDllLoaded );
			ZipDllExec			= (GetZipExecAddress)::GetProcAddress( ZipDllHandle, "ZipDllExec" );
			GetZipDllVersion	= (GetZipVersionAddress)::GetProcAddress( ZipDllHandle, "GetZipDllVersion" );
			if ( !ZipDllExec )
				ShowZipMessage( LZ_NoZipDllExec );
			if ( !GetZipDllVersion )
				ShowZipMessage( LZ_NoZipDllVers );
		} else ShowZipMessage( LZ_NoZipDll );
	} catch ( ... ) { }
	::SetErrorMode( OldMode );
}

//---------------------------------------------------------------------------
// This code tries to locate the DLL before loading it.
// The user can specify a dir in the DLLDirectory property.
// The user's dir is our first choice, but we'll still try the
// standard Windows DLL dirs (App. start dir, Current dir, Windows System, Windows, Path).
void __fastcall TZipBuilder::Load_Unz_Dll( void ) {
	String FullPath = "UNZDLL.DLL";

	if ( FDLLDirectory != "" && FileExists( FDLLDirectory + "\\UNZDLL.DLL" ) )
		FullPath = FDLLDirectory + "\\UNZDLL.DLL";

	long OldMode = ::SetErrorMode( SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX );

	try {
		if ( ( UnzDllHandle = ::LoadLibrary( FullPath.c_str() )) != NULL ) {
			if ( FTrace ) ShowZipMessage( LU_UnzDllLoaded );
			UnzDllExec			= (GetUnzExecAddress)::GetProcAddress( UnzDllHandle, "UnzDllExec" );
			GetUnzDllVersion	= (GetUnzVersionAddress)::GetProcAddress( UnzDllHandle, "GetUnzDllVersion" );
			if ( !UnzDllExec )
				ShowZipMessage( LU_NoUnzDllExec );
			if ( !GetUnzDllVersion )
				ShowZipMessage( LU_NoUnzDllVers );
		} else ShowZipMessage( LU_NoUnzDll );
	} catch ( ... ) {	}
	::SetErrorMode( OldMode );
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::Unload_Zip_Dll( void ) {
	if ( ZipDllHandle ) ::FreeLibrary( ZipDllHandle );
	ZipDllHandle = NULL;
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::Unload_Unz_Dll( void ) {
	if ( UnzDllHandle ) ::FreeLibrary( UnzDllHandle );
	UnzDllHandle = NULL;
}

//---------------------------------------------------------------------------
String __fastcall TZipBuilder::AppendSlash( String sDir ) {
	return ( (sDir.Length() > 0) && (sDir[ sDir.Length() ] != '\\') ) ? ( sDir + '\\' ) : sDir;
}

//---------------------------------------------------------------------------
//char * __fastcall TZipBuilder::ReplaceForwardSlash( char *aStr ) {
//	while( char *aPtr = StrScan( aStr, '/' ) ) *aPtr = '\\';
//	return aStr;
//}
String __fastcall TZipBuilder::ReplaceForwardSlash( char *aStr ) {
	String RetStr = aStr;

	while( int aPos = RetStr.Pos( "/" ) ) RetStr[ aPos ] = '\\';
	return RetStr;
}

//---------------------------------------------------------------------------
// Used by CopyFile, ConvertSFX, ConvertZip and CopyZippedFiles.
// If ReadLen == -1 the remaining part of InFile is copied.
// If ReadLen >= 0 than ReadLen bytes are copied.
int __fastcall TZipBuilder::CopyBuffer( int &InFile, int &OutFile, int ReadLen ) {
	const	SE_CopyError = -2;	// Write error or no memory during copy.
	int   SizeR, ToRead = BufSize, Result = SE_CopyError;
	char *Buffer = NULL;

	try {
		Buffer = new char[ BufSize ];
		Result = 0;					// No memory error!
		do {
			if ( ReadLen >= 0 ) ToRead = min( ReadLen, BufSize );
			SizeR = FileRead( InFile, Buffer, ToRead );
			if ( FileWrite( OutFile, Buffer, SizeR ) != SizeR ) {
				Result = SE_CopyError;
				break;
			}
			if ( FOnProgress && FShowProgress )
				FOnProgress( this, ProgressUpdate, "", SizeR );
			if ( ReadLen > 0 ) ReadLen -= SizeR;
			Application->ProcessMessages();	// Mostly for winsock.
		} while( SizeR == ToRead && ReadLen );
	} catch ( ... ) { }
	delete[] Buffer;
	return Result;
}

//---------------------------------------------------------------------------
// Returns 0 if good copy, or a negative error code.
int __fastcall TZipBuilder::CopyFile( const String InFileName, const String OutFileName ) {
	const
		SE_CreateError   = -1,	// Error in open or creation of OutFile.
		SE_OpenReadError = -3,	// Error in open or Seek of InFile.
		SE_SetDateError  = -4,	// Error setting date/time of OutFile.
		SE_GeneralError  = -9;
	int InFile, OutFile, InSize = -1, OutSize = -1, Result = SE_OpenReadError;
	FShowProgress = false;

	if ( !FileExists( InFileName ) ) return Result;
	Screen->Cursor = crHourGlass;
	if ( (InFile = FileOpen( InFileName, fmOpenRead | fmShareDenyWrite )) != -1 ) {
		if ( FileExists( OutFileName ) ) EraseFile( OutFileName, FHowToDelete );
		if ( (OutFile = FileCreate( OutFileName )) != -1 ) {
			Result = CopyBuffer( InFile, OutFile, -1 );
			if ( !Result && FileSetDate( OutFile, FileGetDate( InFile ) ) != 0 )
				Result = SE_SetDateError;
			OutSize = FileSeek( OutFile, 0, 2 );
			FileClose( OutFile );
		} else Result = SE_CreateError;
		InSize = FileSeek( InFile, 0, 2 );
		FileClose( InFile );
	}
	// An extra check if the filesizes are the same.
	if ( !Result && (InSize == -1 || OutSize == -1 || InSize != OutSize) )
		Result = SE_GeneralError;
	// Don't leave a corrupted outfile lying around. (SetDateError is not fatal!)
	if ( Result && Result != SE_SetDateError )
		DeleteFile( OutFileName );

	Screen->Cursor = crDefault;
	return Result;
}

//---------------------------------------------------------------------------
int __fastcall TZipBuilder::EraseFile( const String Fname, DeleteOpts How ) {
	TSHFileOpStruct  SHF;
	char				 *FromStr = NULL;
	int				  Result  = -1;
	String			  DelFileName = Fname;

	// If we do not have a full path then FOF_ALLOWUNDO does not work!?
	if ( ExtractFilePath( Fname ) == "" )
		DelFileName = GetCurrentDir() + '\\' + Fname;

	if ( !FileExists( DelFileName ) ) return Result;
	try {
		int dfnLen = DelFileName.Length() + 2;
		FromStr    = new char[ dfnLen ];
		SHF.hwnd   = Application->Handle;
		SHF.wFunc  = FO_DELETE;
		SHF.pFrom  = FromStr;
		SHF.pTo    = NULL;
		SHF.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;
		if ( How == htdAllowUndo ) SHF.fFlags |= FOF_ALLOWUNDO;
		StrPLCopy( FromStr, DelFileName, dfnLen );
		FromStr[ dfnLen - 1 ] = '\0';
		Result = SHFileOperation( &SHF );
	} catch( ... ) { }
	delete[] FromStr;
	return Result;
}

// Search for the right(with our icon) resource directory entry.
DWord __fastcall TZipBuilder::SearchResDirEntry( pIRD ResStart, pIRDirE entry, int Depth ) {
	pIRDatE data;

#  if __BORLANDC__ < 1328		// BCB1=0x0520(1312)
	if ( entry->u.s.NameIsString ) return 0;			// No named resources.
	if ( !Depth && entry->u.Id != 3 ) return 0;			// Only icon resources.
	if ( Depth == 1 && entry->u.Id != 1 ) return 0;	// Only icon with ID 0x1.
	if ( !entry->u2.s.DataIsDirectory ) {
		data = (pIRDatE)( (char *)ResStart + entry->u2.OffsetToData );
		if ( data->Size == 744 )
			return data->OffsetToData;
	} else
		return BrowseResDir( ResStart, (pIRD)( (char *)ResStart + entry->u2.s.OffsetToDirectory ), Depth + 1 );
#  endif
#  if __BORLANDC__ == 1328		// BCB3=0x0530(1328)
	if ( entry->_s1.NameIsString ) return 0;			// No named resources.
	if ( !Depth && entry->Id != 3 ) return 0;			// Only icon resources.
	if ( Depth == 1 && entry->Id != 1 ) return 0;	// Only icon with ID 0x1.
	if ( !entry->_s2.DataIsDirectory ) {
		data = (pIRDatE)( (char *)ResStart + entry->OffsetToData );
		if ( data->Size == 744 )
			return data->OffsetToData;
	} else
		return BrowseResDir( ResStart, (pIRD)( (char *)ResStart + entry->_s2.OffsetToDirectory ), Depth + 1 );
#  endif
// And again! changed because unnamed unions are now possible.
#  if __BORLANDC__ == 1344		// BCB3=0x0540(1344)
	if ( entry->NameIsString ) return 0;				// No named resources.
	if ( !Depth && entry->Id != 3 ) return 0;			// Only icon resources.
	if ( Depth == 1 && entry->Id != 1 ) return 0;	// Only icon with ID 0x1.
	if ( !entry->DataIsDirectory ) {
		data = (pIRDatE)( (char *)ResStart + entry->OffsetToData );
		if ( data->Size == 744 )
			return data->OffsetToData;
	} else
		return BrowseResDir( ResStart, (pIRD)( (char *)ResStart + entry->OffsetToDirectory ), Depth + 1 );
#  endif
	return 0;
}

// Browse through all resource Directories.
DWord __fastcall TZipBuilder::BrowseResDir( pIRD ResStart, pIRD dir, int Depth ) {
	pIRDirE SingleRes = (pIRDirE)( (char *)dir + sizeof( IMAGE_RESOURCE_DIRECTORY ) );
	DWord	Result = 0;

	for( int i = 0; i < dir->NumberOfNamedEntries + dir->NumberOfIdEntries; i++ ) {
		Result = SearchResDirEntry( ResStart, SingleRes, Depth );
		if ( Result ) break;   // Found the one w're looking for.
		SingleRes++;
	}
	return Result;
}

// Find Resource directory entry.
DWord __fastcall TZipBuilder::LookForDirs( const void *SectionData, const DWord SectionVirtualStart,
															const int SectionLen, pIDD directories ) {
	pIRD  ResStart;
	DWord Result = 0;
	pIDD  dirs = directories;

	dirs += IMAGE_DIRECTORY_ENTRY_RESOURCE;
	if ( dirs->VirtualAddress && ( (char *)dirs->VirtualAddress >= (char *)SectionVirtualStart ) &&
		(char *)dirs->VirtualAddress < ( (char *)SectionVirtualStart + SectionLen) ) {
		ResStart = (pIRD)( (char *)SectionData + (dirs->VirtualAddress - SectionVirtualStart) );
		Result = BrowseResDir( ResStart, ResStart, 0 );
	}
	return Result;
}

// Replace the icon resource in the copied ZipSFX.bin
// Return values: All ok: =0   Error: <0
int __fastcall TZipBuilder::ReplaceIcon( int SFXFile, int SFXSize ) {
const
	SE_NoFoundError   = -10,
	SE_MemStreamError = -11,
	SE_IconSizeError  = -12;

	char             *SFXBuffer = NULL;
	TMemoryStream    *IconStream = NULL;
	IMAGE_DOS_HEADER *DOSHead;
	PEheader         *Header;
	DWord             FoundAddr = 0;
	pISH              SectionHeader;
	int               Result = SE_NoFoundError;

	for( ;; ) {
		try {
			// Put the SFX file into a buffer.
			SFXBuffer = new char[ SFXSize ];
			FileSeek( SFXFile, 0, soFromBeginning );
			FileRead( SFXFile, SFXBuffer, SFXSize );
			// Read and check the ZipSFX.bin file for an icon resource.
			DOSHead = (IMAGE_DOS_HEADER *)SFXBuffer;
			if ( DOSHead->e_magic != IMAGE_DOS_SIGNATURE ) break;
			Header = (PEheader *)( (char *)DOSHead + DOSHead->e_lfanew );
			if ( Header->signature != IMAGE_NT_SIGNATURE ) break;
			SectionHeader = &Header->section_header;
			for( int Section = 0; Section < Header->_head.NumberOfSections; Section++ ) {	// Walk through sections.
				if ( !StrComp( (char *)&SectionHeader->Name[ 0 ], ".rsrc" ) ) {	// Found the resource section.
					FoundAddr = LookForDirs( SFXBuffer + SectionHeader->PointerToRawData, SectionHeader->VirtualAddress,
							SectionHeader->SizeOfRawData, &Header->opt_head.DataDirectory[ 0 ] );
					if ( !FoundAddr ) break;
					// Change memory offset to file offset.
					FoundAddr = FoundAddr - SectionHeader->VirtualAddress + SectionHeader->PointerToRawData;
					break;
				}
				SectionHeader++;
			}
			if ( !FoundAddr ) break;
			// Save the icon data to a stream.
			IconStream = new TMemoryStream();
			FSFXIcon->SaveToStream( IconStream );
			// Only handle icons with this size.
			if ( IconStream->Size == 766 ) {
				// Reposition to the actual data and put it into a buffer.
				IconStream->Seek( 22, soFromBeginning );
				IconStream->ReadBuffer( SFXBuffer, 744 );
				// Go to start of the icon resource in the new created file.
				FileSeek( SFXFile, (SeekInt)FoundAddr, soFromBeginning );
				// And write the changed icon data from the buffer.
				FileWrite( SFXFile, SFXBuffer, 744 );
				Result = 0;
			} else
				Result = SE_IconSizeError;
		} catch( ... ) {
			Result = SE_MemStreamError;
		}
		break;
	}
	delete[] SFXBuffer;
	delete IconStream;
	FileSeek( SFXFile, 0, soFromEnd );
	return Result;
}

//---------------------------------------------------------------------------
// Convert an .ZIP archive to a .EXE archive.
// Returns 0 if good, or else a negative error code.
// Because we want backward compatible we keep this function.
int __fastcall TZipBuilder::ConvertSFX( void ) {
	// Call the new ConvertSFX() function.
	return ConvertSFX( false );
}

//---------------------------------------------------------------------------
int __fastcall TZipBuilder::ConvertSFX( bool AutoExeViaAdd ) {
	const
		SE_CreateError   = -1,  // Error in open of OutFile.
		SE_CopyError     = -2,  // Read or write error during copy.
		SE_OpenReadError = -3,  // Error in open of InFile.
		SE_GeneralError  = -9;
	int InFile, OutFile, Result = SE_GeneralError;
	int SFXSize = -1, ZipSize = -1, OutSize = -1, SFXBlkSize;
	char dirbuf[ MAX_PATH ], *sfxblk, cll = 0;

	FShowProgress = false;
	if ( !FileExists( FZipFileName ) && !AutoExeViaAdd ) {
		ShowZipMessage( GE_NoZipSpecified );
		return Result;
	}
	int L = FSFXCaption.Length() + FSFXDefaultDir.Length() + FSFXCommandLine.Length() + FSFXMessage.Length();
	SFXBlkSize = ((12 + L + 3) / 4)* 4;	// DWord Alignment.

	/* Do a simple validation to ensure that the 4 variable length text
	 * fields are small enough to fit inside the SFX control block. */
	if ( FSFXCaption.Length() > 255 || FSFXDefaultDir.Length() > 255 ||
		  FSFXCommandLine.Length() > 255 || FSFXMessage.Length() > 255 ) {
		ShowZipMessage( SF_StringToLong, "\r\nSFXCaption + SFXDefaultDir + SFXCommandLine + SFXMessage = " + IntToStr( SFXBlkSize + 1 ) );
		return Result;
	}
	// Try to find the SFX binary file: ZIPSFX.BIN
	// Look in the location given by the SFXPath property first.
	do {
		if ( FileExists( FSFXPath ) ) break;
		// Try the current directory.
		if ( FileExists( FSFXPath = "ZipSFX.bin" ) ) break;
		// Try the application directory.
		if ( FileExists( FSFXPath = ExtractFilePath( ParamStr( 0 ) ) + "\\ZipSFX.bin" ) ) break;
		// Try the Windows System dir.
		::GetSystemDirectory( dirbuf, MAX_PATH );
		if ( FileExists( FSFXPath = AnsiString( dirbuf ) + "\\ZipSFX.bin" ) ) break;
		// Try the Windows dir.
		::GetWindowsDirectory( dirbuf, MAX_PATH );
		if ( FileExists( FSFXPath = AnsiString( dirbuf ) + "\\ZipSFX.bin" ) ) break;
		// Try the dir specified in the DLLDirectory property.
		if ( FDLLDirectory != "" && FileExists( FSFXPath = FDLLDirectory + "\\ZipSFX.bin" ) ) break;
		ShowZipMessage( SF_NoZipSFXBin );
		FSFXPath = "";
		return Result;
	} while( true );

	try {
		sfxblk = new char[ SFXBlkSize + 1 ];
	} catch( ... ) {
		ShowZipMessage( GE_NoMem );
		return Result;
	}
	Screen->Cursor = crHourGlass;

	// Create a packed byte with various 1 bit settings.
	memset( sfxblk, '\0', SFXBlkSize );
   strncpy( sfxblk, "MPV", 3 );
	if ( FSFXOptions.Contains( SFXAskCmdLine ) ) cll  = 1;			// Don't ask user if he wants to run cmd line.
	if ( FSFXOptions.Contains( SFXAskFiles ) )	cll |= 2;			// Allow user to edit files in selection box.
	if ( FSFXOptions.Contains( SFXHideOverWriteBox ) ) cll |= 4;	// Hide overwrite mode box at runtime.
	if ( FSFXOverWriteMode == OvrAlways ) cll |= 8;						// Default = ovrConfirm.
	if ( FSFXOverWriteMode == OvrNever  ) cll |= 16;
	if ( !SFXOptions.Contains( SFXCheckSize ) ) cll |= 32;			// No size checking if false.
	if ( FSFXOptions.Contains( SFXAutoRun ) ) cll |= 64;				// Use AutoRun if file starts with '!'.
	// New v1.6
	if ( FSFXOptions.Contains( SFXNoSuccessMsg ) ) cll |= 128;		// Don't show success message after extraction.
	sfxblk[ 3 ] = cll;
	sfxblk[ 5 ] = 1;
	sfxblk[ 6 ] = Char( LOBYTE( LOWORD( SFXBlkSize ) ) );
	sfxblk[ 7 ] = Char( HIBYTE( LOWORD( SFXBlkSize ) ) );

	int j = FSFXCaption.Length();
	sfxblk[ 8 ] = (BYTE)j;
	StrPCopy( &sfxblk[ 9 ], FSFXCaption );

	sfxblk[ j + 9 ] = (BYTE)FSFXDefaultDir.Length();
	StrPCopy( &sfxblk[ j + 10 ], FSFXDefaultDir );
	j += FSFXDefaultDir.Length();

	sfxblk[ j + 10 ] = (BYTE)FSFXCommandLine.Length();
	StrPCopy( &sfxblk[ j + 11 ], FSFXCommandLine );
	j += FSFXCommandLine.Length();

	sfxblk[ j + 11 ] = (BYTE)FSFXMessage.Length();
	StrPLCopy( &sfxblk[ j + 12 ], FSFXMessage, FSFXMessage.Length() );

	// Create the destination.
	String OutFileName;
	// SFX code will be added to a new archive we are
	// going to create with an extension of .EXE
	if ( AutoExeViaAdd ) OutFileName = FZipFileName;
   else {
		if ( UpperCase( ExtractFileExt( FZipFileName ) ) != ".ZIP" ) {
			ShowZipMessage( SF_InputIsNoZip );
			return Result;
		}
		OutFileName = ChangeFileExt( FZipFileName, ".exe" );
	}

	if ( FileExists( OutFileName ) ) EraseFile( OutFileName, FHowToDelete );
	if ( (OutFile = FileCreate( OutFileName )) != -1 ) {
		// Copy the SFX code to destination .EXE file.
		if ( (InFile = FileOpen( SFXPath, fmOpenRead | fmShareDenyWrite )) != -1 ) {
			Result = CopyBuffer( InFile, OutFile, -1 );
			SFXSize = FileSeek( InFile, 0, 2 );
			FileClose( InFile );
			// Copy the SFX code to destination .EXE file.
			if ( !Result && !FSFXIcon->Empty )
				Result = ReplaceIcon( OutFile, SFXSize );
		} else Result = SE_OpenReadError;
		// Copy the special SFX block to the destination.
		if ( !Result ) {
			if ( FileWrite( OutFile, sfxblk, SFXBlkSize ) != SFXBlkSize ) Result = SE_CopyError;
			if ( !Result ) {
				struct ZipEndOfCentral EOC;	// We need to create a End-of-central-dir header.
				if ( AutoExeViaAdd ) {
					memset( &EOC, '\0', sizeof( EOC ) );
					EOC.HeaderSig     = EndCentralDirSig;
					EOC.CentralOffset = SFXSize + SFXBlkSize;	// Central offset=EOC offset=end of SFX code.
					// Copy the EOC header to the .exe file.
					if ( FileWrite( OutFile, &EOC, sizeof( EOC ) ) != sizeof( EOC ) )
						Result = SE_CopyError;
					// Let's close the file and get out - we don't
					// have a zipfile to append in this case.
				} else {
					// Copy the ZIP file to the destination (BUG fix)
					try {
						CheckIfLastDisk( EOC, true );	// Read the EOC or we get an exception.
						FileSeek( FInFileHandle, 0, 0 );
						// If we got a warning in List() we assume it's a pre v1.5 .ZIP.
						// (converted back from a .EXE ) and we will not change the offsets.
						if ( FWrongZipStruct ) {
							Result = CopyBuffer( FInFileHandle, OutFile, -1 );
							ZipSize = FRealFileSize;
						} else {
							// Copy until we get at the start of the central header.
							if ( (Result = CopyBuffer( FInFileHandle, OutFile, EOC.CentralOffset )) == 0 )
								// Now read all headers and change the offsets.
								Result = RWCentralDir( OutFile, EOC, SFXSize + SFXBlkSize );
							ZipSize = FFileSize;
						}
					} catch ( ... ) {
						Result = SE_OpenReadError;
					}
					if ( FInFileHandle != -1 ) FileClose(  FInFileHandle );
				}
			}
		}
		OutSize = FileSeek( OutFile, 0, 2 );
		FileClose( OutFile );
	} else Result = SE_CreateError;

	if ( Result || !AutoExeViaAdd ) {
		// An extra check if file is ok.
		if ( !Result && (SFXSize == -1 || ZipSize == -1 || OutSize == -1 || OutSize != SFXSize + ZipSize + SFXBlkSize ) )
			Result = SE_GeneralError;

		if ( !Result ) {
			EraseFile( FZipFileName, FHowToDelete );
			ZipFileName = OutFileName;	// The .EXE file is now the default archive and invoke List().
		} else DeleteFile( OutFileName );
	}
	if ( sfxblk ) delete[] sfxblk;
	Screen->Cursor = crDefault;
	return Result;
}

//---------------------------------------------------------------------------
// Convert an .EXE archive to a .ZIP archive.
// Returns 0 if good, or else a negative error code.
int __fastcall TZipBuilder::ConvertZIP( void ) {
	const
		 SE_CreateError   = -1,  // Error in creation of OutFile.
		 SE_CopyError     = -2,  // Seek error in InFile.
		 SE_OpenReadError = -3,  // Error in open of InFile.
		 SE_GeneralError  = -9,
		 SE_OutOfMemError = -10;
	int OutFile, InSize = -1, OutSize = -1, SFXBlkSize, Result = SE_GeneralError;
	char *sfxblk = NULL, *sfxstr, cll;
	struct ZipEndOfCentral EOC;

	FShowProgress = false;
	if ( !FileExists( FZipFileName ) ) {
		ShowZipMessage( CZ_NoExeSpecified );
		return SE_OpenReadError;
	}
	if ( UpperCase( ExtractFileExt( FZipFileName ) ) != ".EXE" )  {
		ShowZipMessage( CZ_InputNotExe );
		return SE_OpenReadError;
	}

	// The FSFXOffset is the location where the zip file starts inside
	// the .EXE archive.  It is calculated during a ZipBuilder List operation.
	// Since a LIST is done when a filename is assigned, we know that
	// a LIST has already been done on the correct archive.
	if ( !FSFXOffset ) {
		ShowZipMessage( CZ_SFXTypeUnknown );
		return Result;
	}

	// Create the destination.
	Screen->Cursor = crHourGlass;
	Result = SE_CopyError;
	String OutFileName = ChangeFileExt( FZipFileName, ".zip" );

	if ( FileExists( OutFileName ) ) EraseFile( OutFileName, FHowToDelete );
	if ( (OutFile = FileCreate( OutFileName )) != -1 ) {
		try {
			SFXBlkSize = min( 1032, FSFXOffset );
			sfxblk     = new char[ SFXBlkSize ];
			CheckIfLastDisk( EOC, true );		// Read the EOC record or we get an exception.
			// Step over SFX code at the begin of the .EXE file
			// and read the SFX MPU or MPV block.
			if ( FileSeek( FInFileHandle, (SeekInt)(FSFXOffset - SFXBlkSize), 0 ) != -1 && FileRead( FInFileHandle, sfxblk, SFXBlkSize ) == SFXBlkSize ) {
				// Find the start of the MPV or MPU block.
				for( int i = 0; i <= SFXBlkSize - 3; i++ ) {
					if ( (sfxblk[ i ] == 'M') && (sfxblk[ i + 1 ] == 'P') && ((sfxblk[ i + 2 ] == 'U') || (sfxblk[ i + 2 ] == 'V')) ) {
						// Read the 'custom' icon back from the executable.
						HICON IconHandle = ExtractIcon( HInstance, FZipFileName.c_str(), 0 );
						if ( IconHandle && (int)IconHandle != 1 ) {
							if ( SFXIcon->Handle ) SFXIcon->ReleaseHandle();
							SFXIcon->Handle = IconHandle;
						}
						// Read back the original values from the MPU block.
						FSFXOptions.Clear();
						FSFXOverWriteMode = OvrConfirm;
						cll = sfxblk[ i + 3 ];
						if ( cll &  1 )	 FSFXOptions = FSFXOptions << SFXAskCmdLine;
						if ( cll &  2 )	 FSFXOptions = FSFXOptions << SFXAskFiles;
						if ( cll &  4 )	 FSFXOptions = FSFXOptions << SFXHideOverWriteBox;
						if ( cll &  8 )	 FSFXOverWriteMode = OvrAlways;
						if ( cll & 16 )	 FSFXOverWriteMode = OvrNever;
						if ( !(cll & 32) ) FSFXOptions = FSFXOptions << SFXCheckSize;
						if ( cll & 64 )	 FSFXOptions = FSFXOptions << SFXAutoRun;
                  if ( sfxblk[ i + 2 ] == 'U' ) {
							FSFXCaption     = AnsiString( &sfxblk[ 7 ], sfxblk[ 4 ] );
							FSFXDefaultDir  = AnsiString( &sfxblk[ sfxblk[ 4 ] + 7 ], sfxblk[ 5 ] );
							FSFXCommandLine = AnsiString( &sfxblk[ sfxblk[ 4 ] + sfxblk[ 5 ] + 7 ], sfxblk[ 6 ] );
						} else {
							if (cll & 128)	 FSFXOptions = FSFXOptions << SFXNoSuccessMsg;
							sfxstr = &sfxblk[ i + 8 ];
							FSFXCaption = AnsiString( &sfxstr[ 1 ], sfxstr[ 0 ] );
							sfxstr = sfxstr + sfxstr[ 0 ] + 1;
							FSFXDefaultDir = AnsiString( &sfxstr[ 1 ], sfxstr[ 0 ] );
							sfxstr = sfxstr + sfxstr[ 0 ] + 1;
							FSFXCommandLine = AnsiString( &sfxstr[ 1 ], sfxstr[ 0 ] );
							sfxstr = sfxstr + sfxstr[ 0 ] + 1;
							FSFXMessage = AnsiString( &sfxstr[ 1 ], sfxstr[ 0 ] );
						}
						break;
					}
				}
				// If we got a warning in List() we assume it's a pre v1.5 .EXE.
				// and we will not change the offsets.
				if ( FWrongZipStruct ) {
					Result = CopyBuffer( FInFileHandle, OutFile, -1 );
					InSize = FRealFileSize;
				} else {
					// Copy until the start of the first Central header.
					if ( (Result = CopyBuffer( FInFileHandle, OutFile, EOC.CentralOffset - FSFXOffset )) == 0 )
						// Now read all headers and change the offsets.
						Result = RWCentralDir( OutFile, EOC, -FSFXOffset );
					InSize = FFileSize;
				}
			}
		}
		catch ( const MEMEXCEPT &me ) {		// All memory allocation errors.
			Result = SE_OutOfMemError;
		}
		catch( ... ) {
			Result = SE_OpenReadError;
		}
		if ( FInFileHandle != -1 ) FileClose( FInFileHandle );
		OutSize = FileSeek( OutFile, 0, 2 );
		FileClose( OutFile );
	} else Result = SE_CreateError;

	if ( !Result && ( InSize == -1 || OutSize == -1 || OutSize != InSize - FSFXOffset ) )
		Result = SE_GeneralError;

	if ( !Result ) {
		EraseFile( FZipFileName, FHowToDelete );
		ZipFileName = OutFileName;	// The .ZIP file is now the default archive and invoke List().
	} else DeleteFile( OutFileName );

	if ( sfxblk ) delete[] sfxblk;
	Screen->Cursor = crDefault;
   return Result;
}

//---------------------------------------------------------------------------
// A wrapper function for ShowMessage() needed for the implementation
// of the Unattended property.
void __fastcall TZipBuilder::ShowZipMessage( const int Ident, const String UserStr ) {
	String msg = LoadZipStr( Ident, RESOURCE_ERROR + IntToStr( Ident ) ) + UserStr;

	FErrCode = Ident;
	FMessage = msg;
	if ( !Unattended ) ShowMessage( msg );
	if ( OnMessage ) OnMessage( this, 0, msg );
}

//---------------------------------------------------------------------------
// Somewhat different from ShowZipMessage() because the loading of the resource
// string is done in the base constructor of the exception class.
void __fastcall TZipBuilder::ShowExceptionError( const EZipBuilder &ZBExcept ) {
	if ( ZBExcept.FDisplayMsg && !Unattended ) ShowMessage( ZBExcept.Message );
	FErrCode = ZBExcept.FResIdent;
	FMessage = ZBExcept.Message;
	if ( OnMessage ) OnMessage( this, 0, ZBExcept.Message );
}

//---------------------------------------------------------------------------
String __fastcall TZipBuilder::LoadZipStr( const int Ident, const String DefaultStr ) {
	String msg = LoadStr( Ident );

	if ( msg.IsEmpty() ) msg = DefaultStr;
	return msg;
}

//---------------------------------------------------------------------------
bool __stdcall TZipBuilder::EnumThreadWndProc( HWND winh, TZipBuilder *mythis ) {
	if ( ::GetParent( winh ) == Application->Handle ) {
		mythis->Fhwnd  = winh;
		mythis->FFound = 1;
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
int __fastcall TZipBuilder::ZipFormat( void ) {
	FFound        =  0;
	FFormatResult = -3;	// No format
	Fft           = new TSHFormatThread( this, false );

	if ( Fft ) {
		do {
			Application->ProcessMessages();
			::EnumThreadWindows( Fft->ThreadID, (WNDENUMPROC)EnumThreadWndProc, (long)this );
		} while( !FFound );
		// W'll have to wait for formatting to finish (1)
		// or in case of an error (2) don't wait at all.
		// (It's possible that the thread is already gone.)
		if ( FFound == 1 ) Fft->WaitFor();
	}
	return FFormatResult;
}

//---------------------------------------------------------------------------
// Function to read a Zip source file and write it back to one or more disks.
// Return values:
// 0			All Ok.
// -7			WriteSpan errors. See ZipMsgXX.rc and ZipMsg.h
// -8			Memory allocation error.
// -9			General unknown WriteSpan error.
int __fastcall TZipBuilder::WriteSpan( const String InFileName, const String OutFileName ) {
	char   *Buffer = NULL;
	int     Result = 0;
	struct  ZipEndOfCentral    EOC;
	struct  ZipLocalHeader     LOH;
	struct  ZipDataDescriptor  DD;
	struct  ZipCentralHeader   CEH;
	struct  MDZipData        **MDZD = NULL;

	FZipBusy			= true;
	FDrive			= ExtractFileDrive( OutFileName ) + "\\";
	FDiskNr		   = 0;
	FFreeOnDisk	   = 0;
	FNewDisk	      = true;
	FDiskWritten	= 0;
	FInFileName		= InFileName;
	FOutFileName   = OutFileName;
	FOutFileHandle = -1;
	FShowProgress  = false;
	Screen->Cursor	= crHourGlass;

	try {
		if ( !FileExists( InFileName ) ) throw EZipBuilder( DS_NoInFile );
		CheckIfLastDisk( EOC, true );

		// Get the date-time stamp and save for later.
		FDateStamp = FileGetDate( FInFileHandle );

		// Now we now the number of zipped entries in the zip archive.
		// And we go back to the start the zip archive.
		if ( FileSeek( FInFileHandle, 0, 0 ) == -1 ) throw EZipBuilder( DS_FailedSeek );

		// Allocate the read/write buffer.
		Buffer = new char[ BufSize ];
		MDZD = AllocSpanMem( EOC.TotalEntries );		// Allocate other memory.
		// Write extended local Sig. needed for a spanned archive.
		WriteSplit( &ExtLocalSig, 4, 0 );

		// Read for every zipped entry: The local header, variable data, fixed data
		// and if present the Data decriptor area.
		FShowProgress = true;
		if ( OnProgress ) {
			OnProgress( this, TotalFiles2Process, "", EOC.TotalEntries );
			OnProgress( this, TotalSize2Process,  "", FFileSize );
		}
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// First the local header.
			if ( FileRead( FInFileHandle, &LOH, sizeof( LOH ) ) != sizeof( LOH ) )
				throw EZipBuilder( DS_LOHBadRead );
			if ( LOH.HeaderSig != LocalFileHeaderSig ) throw EZipBuilder( DS_LOHWrongSig );

			// Now the filename.
			if ( FileRead( FInFileHandle, Buffer, LOH.FileNameLen ) != LOH.FileNameLen )
				throw EZipBuilder( DS_LONameLen );

			// Save some information for later. ( on the last disk(s) ).
			MDZD[ i ]->DiskStart   = (unsigned short)FDiskNr;
			MDZD[ i ]->FileName    = new char[ LOH.FileNameLen + 1 ];
			MDZD[ i ]->FileNameLen = LOH.FileNameLen;
			strncpy( MDZD[ i ]->FileName, Buffer, LOH.FileNameLen );
			MDZD[ i ]->FileName[ LOH.FileNameLen ] = 0;

			// Give message and progress info on the start of this new file read.
			if ( OnMessage ) {
				String MsgStr = LoadZipStr( GE_CopyFile, "Copying: " ) + ReplaceForwardSlash( MDZD[ i ]->FileName );
				OnMessage( this, 0, MsgStr );
			}
			long TotalBytesWrite = sizeof( LOH ) + LOH.FileNameLen + LOH.ExtraLen + LOH.ComprSize;
			if ( DescUsed( LOH ) )
				TotalBytesWrite += sizeof( DD );
			if ( OnProgress )
				OnProgress( this, NewFile, ReplaceForwardSlash( MDZD[ i ]->FileName ), TotalBytesWrite );

			// Write the local header to the destination.
			WriteSplit( &LOH, sizeof( LOH ), sizeof( LOH ) + LOH.FileNameLen + LOH.ExtraLen );

			// Save the offset of the LOH on this disk for later.
			MDZD[ i ]->RelOffLocal = FDiskWritten - sizeof( LOH );

			// Write the filename.
			WriteSplit( Buffer, LOH.FileNameLen, 0 );

			// And the extra field
			RWSplitData( Buffer, LOH.ExtraLen, DS_LOExtraLen );

			// Read Zipped data !!!For now assume we know the size!!!
			RWSplitData( Buffer, LOH.ComprSize, DS_ZipData );

			// Read DataDescriptor if present.
			if ( DescUsed( LOH ) )
         	RWSplitData( (char *)&DD, sizeof( DD ), DS_DataDesc );
		}	// Ready, we have written al entries to disk.

		if ( OnMessage ) OnMessage( this, 0, LoadZipStr( GE_CopyFile, "Copying: " ) + LoadZipStr( DS_CopyCentral, "central directory" ) ); //v1.52j
		if ( OnProgress ) OnProgress( this, NewFile, LoadZipStr( DS_CopyCentral, "central directory" ), EOC.CentralSize + sizeof( EOC ) + EOC.ZipCommentLen ); //v1.52j

		// Now write the central directory with changed offsets.
		unsigned short StartCentral = (unsigned short)FDiskNr;
		unsigned long  CentralOffset;
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// Read a central header.
			if ( FileRead( FInFileHandle, &CEH, sizeof( CEH ) ) != sizeof( CEH ) )
				throw EZipBuilder( DS_CEHBadRead );
			if ( CEH.HeaderSig != CentralFileHeaderSig ) throw EZipBuilder( DS_CEHWrongSig );

			// Now the filename.
			if ( FileRead( FInFileHandle, Buffer, CEH.FileNameLen ) != CEH.FileNameLen )
				throw EZipBuilder( DS_CENameLen );

			// Change the central directory with information stored previously in MDZD.
			int k = FindZipEntry( EOC.TotalEntries, MDZD, CEH.FileNameLen, Buffer );
			CEH.DiskStart   = MDZD[ k ]->DiskStart;
			CEH.RelOffLocal = MDZD[ k ]->RelOffLocal;

			// Write this changed central header to disk
			// and make sure it fit's on one and the same disk.
			WriteSplit( &CEH, sizeof( CEH ), sizeof( CEH ) + CEH.FileNameLen + CEH.ExtraLen + CEH.FileComLen );

			// Save the first Central directory offset for use in EOC record.
			if ( !i ) CentralOffset = FDiskWritten - sizeof( CEH );

			// Write to destination the central filename and the extra field.
			WriteSplit( Buffer, CEH.FileNameLen, 0 );

			// And the extra field
			RWSplitData( Buffer, CEH.ExtraLen, DS_CEExtraLen );

			// And the file comment.
			RWSplitData( Buffer, CEH.FileComLen, DS_CECommentLen );
		}
		// Write the changed EndOfCentral directory record.
		EOC.CentralDiskNo = StartCentral;
		EOC.ThisDiskNo    = (unsigned short)FDiskNr;
		EOC.CentralOffset = CentralOffset;
		WriteSplit( &EOC, sizeof( EOC ), sizeof( EOC ) + EOC.ZipCommentLen );

		// Skip past the original EOC to get to the ZipComment if present. v1.52k
		if ( FileSeek( FInFileHandle, (int)sizeof( EOC ), 1 ) == -1 )
			throw EZipBuilder( DS_FailedSeek );

		// And finally the archive comment itself.
		RWSplitData( Buffer, EOC.ZipCommentLen, DS_EOArchComLen );
		FShowProgress = false;
	}
	catch ( const EZipBuilder &ews ) {	// All WriteSpan specific errors.
		ShowExceptionError( ews );
		Result = -7;
	}
	catch ( const MEMEXCEPT &me ) {		// All memory allocation errors.
		ShowZipMessage( GE_NoMem );
		Result = -8;
	}
	catch( const Exception &E ) {
		ShowZipMessage( DS_ErrorUnknown, "\n" + E.Message );
		Result = -9;
	}
	catch ( ... ) {							// The remaining errors, should not occur.
		ShowZipMessage( DS_ErrorUnknown );
		Result = -9;
	}
	// Give the last progress info on the end of this file read.
	if ( OnProgress ) OnProgress( this, EndOfBatch, "", 0 );

	delete[] Buffer;
	DeleteSpanMem( MDZD, EOC.TotalEntries );

	FileSetDate( FOutFileHandle, FDateStamp );
	if ( FOutFileHandle != -1 ) FileClose( FOutFileHandle );
	if ( FInFileHandle != -1 )  FileClose( FInFileHandle );

	FZipBusy = false;
	Screen->Cursor = crDefault;
	return Result;
}

//---------------------------------------------------------------------------
// This function actually writes the zipped file to the destination while taking care
// of disk changes and disk boundary crossings.
// In case of an write error or user abort an EZipBuilder Exception is thrown.
void __fastcall TZipBuilder::WriteSplit( const void *Buffer, int Len, int MinSize ) {
	int   Res, MaxLen;
	char *Buf = (char *)Buffer;  // Used if Buffer doesn't fit on the present disk.

	Application->ProcessMessages();
	if ( Cancel ) throw EZipBuilder( DS_Canceled, false );
	while( true ) {	// Keep writing until error or buffer is empty.
		// Check if we have an output file already opened, if not: create one, do checks gather info.
		if ( FOutFileHandle == -1 ) {
			String       DiskFile = FOutFileName, MsgQ;
			unsigned int drt      = CheckForDisk();

			// If we write on a fixed disk the filename must change.
			// We will get something like: FileNamexxx.zip where xxx is 001,002 etc.
			if (  drt == DRIVE_FIXED || drt == DRIVE_REMOTE ) {
				DiskFile = DiskFile.SubString( 1, DiskFile.Length() - ExtractFileExt( DiskFile ).Length() ) +
						IntToStr( 1001 + FDiskNr ).SubString( 2, 3 ) + ExtractFileExt( DiskFile );
			} else if ( FAddOptions.Contains( AddDiskSpanErase ) ) {
				// Do we want a format first? To be save we don't do this on a harddisk.
				FDriveNr    = FDrive.UpperCase()[ 1 ] - 'A';
				FVolumeName = "PKBACK# " + IntToStr( 1001 + FDiskNr ).SubString( 2, 3 );
				// Ok=6, NoFormat=-3
				switch ( ZipFormat() ) {   // Start the format and wait until finished...
					case -1:  throw EZipBuilder( DS_Canceled );			// Error
					case -2:  throw EZipBuilder( DS_Canceled, false );	// Canceled
				}
			}
			// Do we want to overwrite an existing file.
			if ( FileExists( DiskFile ) ) {
				int DiskSeq = StrToIntDef( FVolumeName.SubString( 9, 3 ), 1 );

				if ( Unattended ) throw EZipBuilder( DS_NoUnattSpan );	// we assume we don't.
				// A more specific check if we have a previous disk from this set. Not too smart but...
				if ( FileAge( DiskFile ) == FDateStamp &&  DiskSeq - 1 < FDiskNr )
					MsgQ = Format( LoadZipStr( DS_AskPrevFile, "Overwrite previous disk no %d" ), ARRAYOFCONST(( DiskSeq )) );
				else
					MsgQ = Format( LoadZipStr( DS_AskDeleteFile, "Overwrite previous file %s" ), ARRAYOFCONST(( DiskFile )) );
				Res = ::MessageBox( FHandle, MsgQ.c_str(), "Confirm", MB_YESNOCANCEL | MB_DEFBUTTON2 | MB_ICONWARNING );
				if ( !Res || Res == IDCANCEL ) throw EZipBuilder( DS_Canceled, false );
				if ( Res == IDNO ) {		// we will try again...
					FDiskWritten = 0;
					FNewDisk     = true;
					continue;
				}
			}
			// Create the output file.
			if ( (FOutFileHandle = FileCreate( DiskFile )) == -1 )
				throw EZipBuilder( DS_NoOutFile );				// File not created.

			// Get the free space on this disk, correct later if neccessary.
			DiskFreeAndSize( 1 );  // RCV150199

			// Set the maximum number of bytes that can be written to this disk(file).
			if ( FMaxVolumeSize ) FFreeOnDisk = min( FMaxVolumeSize, FFreeOnDisk );

			// Reserve space on/in the first disk(file).
			if ( !FDiskNr ) FFreeOnDisk -= KeepFreeOnDisk1;

			// Do we still have enough free space on this disk.
			if ( FFreeOnDisk < MinFreeVolumeSize ) {	// No, too bad...
				FileClose( FOutFileHandle );
				DeleteFile( DiskFile );
				FOutFileHandle = -1;
				if ( Unattended ) throw EZipBuilder( DS_NoUnattSpan );
				MsgQ = LoadZipStr( DS_NoDiskSpace, "This disk has not enough free space available" );
				Res = ::MessageBox( FHandle, MsgQ.c_str(), Application->Title.c_str(), MB_RETRYCANCEL | MB_ICONERROR );
				if ( !Res )            throw EZipBuilder( DS_NoMem );
				if (  Res != IDRETRY ) throw EZipBuilder( DS_Canceled, false );
				FDiskWritten = 0;
				FNewDisk     = true;
				continue;
			}
			// Set the volume label of this disk if it is not a fixed one.
			if ( drt != DRIVE_FIXED && drt != DRIVE_REMOTE ) {
				FVolumeName = "PKBACK# " + IntToStr( 1001 + FDiskNr ).SubString( 2, 3 );

				if ( !::SetVolumeLabel( FDrive.c_str(), FVolumeName.c_str() ) )
					throw EZipBuilder( DS_NoVolume );
			}
		}
		// Check if we have at least MinSize available on this disk,
		// headers are not allowed to cross disk boundaries. ( if zero than don't care.)
		if ( MinSize && MinSize > FFreeOnDisk ) {
			FileSetDate( FOutFileHandle, FDateStamp );
			FileClose( FOutFileHandle );
			FOutFileHandle = -1;
			FDiskWritten   = 0;
			FDiskNr++;	//RCV270299
			FNewDisk       = true;
			continue;
		}
		// Don't try to write more bytes than allowed on this disk.
		MaxLen = min( Len, (int)FFreeOnDisk );	//RCV150199
		Res    = FileWrite( FOutFileHandle, Buf, MaxLen );
		// ::Sleep( 250 );	// This will keep the progress events more synchronised, but it's slower.
		// Give some progress info while writing.
		// While processing the central header we don't want messages.
		if ( OnProgress && FShowProgress ) OnProgress( this, ProgressUpdate, "", MaxLen );
		if ( Res == -1 ) throw EZipBuilder( DS_NoWrite );	// A write error (disk removed?).
      FDiskWritten += Res;
		FFreeOnDisk  -= MaxLen;
		if ( MaxLen == Len ) break;

		// We still have some data left, we need a new disk.
		FileSetDate( FOutFileHandle, FDateStamp );
		FileClose( FOutFileHandle );
		FOutFileHandle = -1;
		FFreeOnDisk = FDiskWritten = 0;
		FDiskNr++;
		FNewDisk = true;
		Buf += MaxLen;
		Len -= MaxLen;
	}
}

//---------------------------------------------------------------------------
// Function to read a split up Zip source file from multiple disks and write it to one destination file.
// Return values:
// 0			All Ok.
// -7			ReadSpan errors. See ZipMsgXX.rc and ZipMsg.h
// -8			Memory allocation error.
// -9			General unknown ReadSpan error.
int __fastcall TZipBuilder::ReadSpan( const String InFileName, String &OutFilePath ) {
	char   *Buffer = NULL;
	int     Result = 0, TotalBytesToRead = 0;
	struct  ZipEndOfCentral    EOC;
	struct  ZipLocalHeader     LOH;
	struct  ZipDataDescriptor  DD;
	struct  ZipCentralHeader   CEH;
	struct  MDZipData        **MDZD = NULL;

	FUnzBusy			= true;
	FDrive			= ExtractFileDrive( InFileName ) + "\\";
	FDiskNr		   = -1;
	FNewDisk       = false;
	FShowProgress  = false;
	FInFileName    = InFileName;
	FInFileHandle  = -1;
	Screen->Cursor	= crHourGlass;

	try {
		Buffer = new char[ BufSize ];

		// If we don't have a filename we make one first.
		if ( ExtractFileName( OutFilePath ) == "" ) {
			// Make a temporary file name like: C:\...\Zipxxxx.zip
			if ( !::GetTempFileName( OutFilePath.c_str(), "zip", 0, Buffer ) )
				throw EZipBuilder( DS_NoTempFile );
			OutFilePath = Buffer;
			DeleteFile( OutFilePath );
		} else EraseFile( OutFilePath, FHowToDelete );
		OutFilePath = ChangeFileExt( OutFilePath, ".zip" );

		// Create the output file.
		if ( (FOutFileHandle = FileCreate( OutFilePath )) == -1 )
			throw EZipBuilder( DS_NoOutFile );

		// Try to get the last disk from the user.
		unsigned int drt = DRIVE_REMOVABLE;
		do {
			if ( drt == DRIVE_FIXED || drt == DRIVE_REMOTE ) {
				int DiskNo = StrToIntDef( FInFileName.SubString( FInFileName.Length() - 2 - ExtractFileExt( FInFileName ).Length() ,3) ,0 );
				if ( DiskNo == 1 ) throw EZipBuilder( DS_FirstInSet );
				if ( DiskNo != 1 ) throw EZipBuilder( DS_NotLastInSet, DiskNo );
			}
			drt = CheckForDisk();
			FNewDisk = true;
		} while( !CheckIfLastDisk( EOC, false ) );

		// Get the date-time stamp and save for later.
		FDateStamp = FileGetDate( FInFileHandle );

		// Now we now the number of zipped entries in the zip archive
		// and the starting disk number of the central directory.
		FTotalDisks = EOC.ThisDiskNo;
		if ( EOC.ThisDiskNo != EOC.CentralDiskNo )
			GetNewDisk( EOC.CentralDiskNo );	// We have to request a previous disk first.
		// We go to the start of the Central directory. v1.52j
		if ( FileSeek( FInFileHandle, (SeekInt)EOC.CentralOffset, 0 ) == -1 )
			throw EZipBuilder( DS_FailedSeek );

		MDZD = AllocSpanMem( EOC.TotalEntries );		// Allocate memory.
		// Read for every entry: The central header and save information for later use.
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// Read a central header.
			while( FileRead( FInFileHandle, &CEH, sizeof( CEH ) ) != sizeof( CEH ) ) {	//v1.52j
				// It's possible that we have the central header split up.
				if ( FDiskNr >= EOC.ThisDiskNo )
					throw EZipBuilder( DS_CEHBadRead );
				// We need the next disk with central header info.
				GetNewDisk( FDiskNr + 1 );
			}
			if ( CEH.HeaderSig != CentralFileHeaderSig )
				throw EZipBuilder( DS_CEHWrongSig );

			// Now the filename.
			if ( FileRead( FInFileHandle, Buffer, CEH.FileNameLen ) != CEH.FileNameLen )
				throw EZipBuilder( DS_CENameLen );

			// Save the file name info in the MDZD structure.
			MDZD[ i ]->FileNameLen	= CEH.FileNameLen;
			MDZD[ i ]->FileName    = new char[ CEH.FileNameLen + 1 ];
			strncpy( MDZD[ i ]->FileName, Buffer, CEH.FileNameLen );
			MDZD[ i ]->FileName[ CEH.FileNameLen ] = '\0';

			// Save the compressed size, we need this because WinZip sets this
			// sometimes to zero in the local header. New v1.52d
			MDZD[ i ]->ComprSize = CEH.ComprSize;

			// We need the total number of bytes we are going to read for the progress event.
			TotalBytesToRead += (CEH.ComprSize + CEH.FileNameLen + CEH.ExtraLen + CEH.FileComLen);

			// Seek past the extra field and the file comment.
			if ( FileSeek( FInFileHandle, (SeekInt)(CEH.ExtraLen + CEH.FileComLen), 1 ) == -1 )
				throw EZipBuilder( DS_FailedSeek );
		}
		// Now we need the first disk and start reading.
		GetNewDisk( 0 );

		FShowProgress = true;
		if ( OnProgress ) {
			OnProgress( this, TotalFiles2Process, "", EOC.TotalEntries );
			OnProgress( this, TotalSize2Process,  "", TotalBytesToRead );
		}
		// Read extended local Sig. first; is only present if it's a spanned archive.
		unsigned long ExtendedSig;
		if ( FileRead( FInFileHandle, &ExtendedSig, 4 ) != 4 || ExtendedSig != ExtLocalSig )
			throw EZipBuilder( DS_ExtWrongSig );

		// Read for every zipped entry: The local header, variable data, fixed data
		// and if present the Data decriptor area.
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// First the local header.
			while( FileRead( FInFileHandle, &LOH, sizeof( LOH ) ) != sizeof( LOH ) ) {
				// Check if we are at the end of a input disk not very likely but...
				if ( FileSeek( FInFileHandle, 0, 1 ) != FileSeek( FInFileHandle, 0, 2 ) )
					throw EZipBuilder( DS_LOHBadRead );
				// Well, it seems we are at the end, so get a next disk.
				GetNewDisk( FDiskNr + 1 );
			}
			if ( LOH.HeaderSig != LocalFileHeaderSig )
				throw EZipBuilder( DS_LOHWrongSig );

			// Now the filename, should be on the same disk as the LOH record.
			if ( FileRead( FInFileHandle, Buffer, LOH.FileNameLen ) != LOH.FileNameLen )
				throw EZipBuilder( DS_LONameLen );

			// Change some info for later while writing the central dir.
			int k = FindZipEntry( EOC.TotalEntries, MDZD, LOH.FileNameLen, Buffer );
			MDZD[ k ]->DiskStart   = 0;
			MDZD[ k ]->RelOffLocal = FileSeek( FOutFileHandle, 0, 1 );

			// Give message and progress info on the start of this new file read.
			if ( OnMessage ) {
				String MsgStr = LoadZipStr( GE_CopyFile, "Copying: " ) + ReplaceForwardSlash( MDZD[ k ]->FileName );
				OnMessage( this, 0, MsgStr );
			}
			long TotalBytesWrite = sizeof( LOH ) + LOH.FileNameLen + LOH.ExtraLen + LOH.ComprSize;
			if ( DescUsed( LOH ) ) TotalBytesWrite += sizeof( DD );
			if ( OnProgress ) OnProgress( this, NewFile, ReplaceForwardSlash( MDZD[ k ]->FileName ), TotalBytesWrite );

			// Write the local header to the destination.
			WriteJoin( &LOH, sizeof( LOH ), DS_LOHBadWrite );

			// Write the filename.
			WriteJoin( Buffer, LOH.FileNameLen, DS_LOHBadWrite );

			// And the extra field
			RWJoinData( Buffer, LOH.ExtraLen, DS_LOExtraLen );

			// Read Zipped data, if the size is not known use the size from the central header.
			if ( !LOH.ComprSize ) LOH.ComprSize = MDZD[ k ]->ComprSize;	// New v1.52d
			RWJoinData( Buffer, LOH.ComprSize, DS_ZipData );

			// Read DataDescriptor if present.
			if ( DescUsed( LOH ) ) RWJoinData( (char *)&DD, sizeof( DD ), DS_DataDesc );
		}	// Now we have written al entries to the (hard)disk.

		// Now write the central directory with changed offsets.
		FShowProgress = false;
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// Read a central header which can be span more than one disk.
			while( FileRead( FInFileHandle, &CEH, sizeof( CEH ) ) != sizeof( CEH ) ) {
				// Check if we are at the end of a input disk.
				if ( FileSeek( FInFileHandle, 0, 1 ) != FileSeek( FInFileHandle, 0, 2 ) )
					throw EZipBuilder( DS_CEHBadRead );
				// Well, it seems we are at the end, so get a next disk.
				GetNewDisk( FDiskNr + 1 );
			}
			if ( CEH.HeaderSig != CentralFileHeaderSig )
				throw EZipBuilder( DS_CEHWrongSig );

			// Now the filename.
			if ( FileRead( FInFileHandle, Buffer, CEH.FileNameLen ) != CEH.FileNameLen )
				throw EZipBuilder( DS_CENameLen );

			// Save the first Central directory offset for use in EOC record.
			if ( !i ) EOC.CentralOffset = FileSeek( FOutFileHandle, 0, 1 );

			// Change the central header info with our saved information.
			int k = FindZipEntry( EOC.TotalEntries, MDZD, CEH.FileNameLen, Buffer );
			CEH.RelOffLocal = MDZD[ k ]->RelOffLocal;
         CEH.DiskStart   = 0;

			// Write this changed central header to disk
			// and make sure it fit's on one and the same disk.
			WriteJoin( &CEH, sizeof( CEH ), DS_CEHBadWrite );

			// Write to destination the central filename and the extra field.
			WriteJoin( Buffer, CEH.FileNameLen, DS_CEHBadWrite );

			// And the extra field
			RWJoinData( Buffer, CEH.ExtraLen, DS_CEExtraLen );

			// And the file comment.
			RWJoinData( Buffer, CEH.FileComLen, DS_CECommentLen );
		}
		// Write the changed EndOfCentral directory record.
		EOC.CentralDiskNo = 0;
		EOC.ThisDiskNo    = 0;
		WriteJoin( &EOC, sizeof( EOC ), DS_EOCBadWrite );

		// And finally the archive comment itself.
		RWJoinData( Buffer, EOC.ZipCommentLen, DS_EOArchComLen );
	}
	catch ( const EZipBuilder &ers ) {	// All ReadSpan specific errors.
		ShowExceptionError( ers );
		Result = -7;
	}
	catch ( const MEMEXCEPT &me ) {		// All memory allocation errors.
		ShowZipMessage( GE_NoMem );
		Result = -8;
	}
	catch( const Exception &E ) {
		ShowZipMessage( DS_ErrorUnknown, "\n" + E.Message );
		Result = -9;
	}
	catch ( ... ) {							// The remaining errors, should not occur.
		ShowZipMessage( DS_ErrorUnknown );
		Result = -9;
	}
	// Give final progress info at the end.
	if ( OnProgress ) OnProgress( this, EndOfBatch, "", 0 );

	delete[] Buffer;
	DeleteSpanMem( MDZD, EOC.TotalEntries );

	if ( FInFileHandle != -1 )  FileClose( FInFileHandle );
	if ( FOutFileHandle != -1 ) {
		FileSetDate( FOutFileHandle, FDateStamp );
	   FileClose( FOutFileHandle );
		if ( Result ) {
			DeleteFile( OutFilePath );
			OutFilePath = "";
		}
	}
	FUnzBusy			= false;
	Screen->Cursor = crDefault;
	return Result;
}

//---------------------------------------------------------------------------
struct MDZipData ** __fastcall TZipBuilder::AllocSpanMem( int TotalEntries ) {
	struct MDZipData **MDZD = new struct MDZipData*[ TotalEntries ];

	for( int i = 0; i < TotalEntries; ) MDZD[ i++ ] = NULL;
	for( int i = 0; i < TotalEntries; i++ ) {
		MDZD[ i ] = new struct MDZipData;
		MDZD[ i ]->FileName = NULL;
	}
	return MDZD;
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::DeleteSpanMem( struct MDZipData **MDZD, int TotalEntries ) {
	if ( MDZD ) {		// We have to check in case of an exception before we allocated this.
		for( int i = 0; i < TotalEntries; i++ ) {
			// Delete the filename space if present, could be NULL which is also save to delete.
			if ( MDZD[ i ] ) delete[] MDZD[ i ]->FileName;
			delete MDZD[ i ];					// Delete the structure.
		}
		delete MDZD;							// Delete the pointers to the structures.
	}
}

//---------------------------------------------------------------------------
// Find a local dir entry in the internal MDZD structure.
// Needed because the central and local header info is not always in sync.
int __fastcall TZipBuilder::FindZipEntry( int Entries, struct MDZipData **MDZD, int HFileLen, char *HFilename ) {
	int k = 0;

	for( ; k < Entries; k++ ) {
		// Filename could be the same but have a different length, (like 'name' and 'nameextra')
		// strnicmp alone doesnn't handle this right.
		if ( HFileLen != MDZD[ k ]->FileNameLen ) continue;
		if ( !strnicmp( HFilename, MDZD[ k ]->FileName, HFileLen ) ) break;
	}
	// Should not happen, but maybe in a bad archive...
	if ( k == Entries ) throw EZipBuilder( DS_EntryLost );
	return k;
}

// Replacement for the functions DiskFree and DiskSize.
// This should solve problems with drives > 2Gb and UNC filenames.
// Path FDrive ends with a backslash.
// Action=1 FreeOnDisk, 2=SizeOfDisk, 3=Both
void __fastcall TZipBuilder::DiskFreeAndSize( int Action ) {	// RCV150199
	DWORD					SectorsPCluster, BytesPSector, FreeClusters, TotalClusters;
	__int64				LDiskFree = -1, LSizeOfDisk = -1;
	HMODULE				Lib = ::GetModuleHandle( "kernel32" );
	GDiskFreeSpaceEx	GetDiskFreeSpaceEx;

	if ( Lib ) {
		GetDiskFreeSpaceEx = (GDiskFreeSpaceEx)::GetProcAddress( Lib, "GetDiskFreeSpaceExA" );
		if ( GetDiskFreeSpaceEx )	// We probably have W95+OSR2 or better.
			if ( GetDiskFreeSpaceEx( FDrive.c_str(), &LDiskFree, &LSizeOfDisk, NULL ) )
				LDiskFree = LSizeOfDisk = -1;
		::FreeLibrary( Lib );	//v1.52j
	}
	// Do we have W95 original or W95+OSR1 or an error?
	if ( LDiskFree == -1 ) {	// We use this because DiskFree/Size don't support UNC drive names.
		if ( ::GetDiskFreeSpace( FDrive.c_str(), &SectorsPCluster, &BytesPSector, &FreeClusters, &TotalClusters ) ) {
			LDiskFree   = (__int64)BytesPSector * SectorsPCluster * FreeClusters;
			LSizeOfDisk = (__int64)BytesPSector * SectorsPCluster * TotalClusters;
		}
	}
	if ( Action & 1 ) FFreeOnDisk = LDiskFree;
	if ( Action & 2 ) FSizeOfDisk = LSizeOfDisk;
}

//---------------------------------------------------------------------------
// Function to check if a disk is present in the requested drive. Changed RCV150199
bool __fastcall TZipBuilder::IsDiskPresent( void ) {
	unsigned long Dummy1, Dummy2;
	char DriveLetter = FDrive.UpperCase()[ 1 ], VolName[ MAX_PATH ];

	if ( DriveLetter != '\\' ) {	// Only for local drives
		if ( DriveLetter < 'A' || DriveLetter > 'Z' )
			throw EZipBuilder( DS_NotaDrive, FDrive );
		if ( !(::GetLogicalDrives() & (1 << (DriveLetter - 'A'))) )
			throw EZipBuilder( DS_DriveNoMount, FDrive );
	}
	// Turn off critical errors.
	unsigned int OldMode = ::SetErrorMode( SEM_FAILCRITICALERRORS );

	// Get free disk space and size.
	DiskFreeAndSize( 3 );	// RCV150199

	if ( !::GetVolumeInformation( FDrive.c_str(), VolName, MAX_PATH, &FDiskSerial, &Dummy1, &Dummy2, NULL, 0 ) ) {
		// W'll get this if there is a disk but it is not or wrong formatted
		// so this disk can only be used when we also want formatting.
		::SetErrorMode( OldMode );	// v1.52j
		return (GetLastError() == 31 && FAddOptions.Contains( AddDiskSpanErase ) ) ? true : false;
	}
	FVolumeName = VolName;

	// Restore old error mode.
	::SetErrorMode( OldMode );

	// -1 is not very likely to happen since GetVolumeInformation catches errors.
	// But on W95(+OSR1) and a UNC filename w'll get also -1, this would prevent
	// opening the file. !!!Potential error while using spanning with a UNC filename!!!
	return ( DriveLetter == '\\' || ( DriveLetter != '\\' && FSizeOfDisk != -1 ) ) ? true : false;
}

//---------------------------------------------------------------------------
unsigned int __fastcall TZipBuilder::CheckForDisk( void ) {
	unsigned int drt = ::GetDriveType( FDrive.c_str() );
	int          Res = IDOK, MsgFlag = MB_OKCANCEL;
	String		 MsgStr;

	Application->ProcessMessages();
	// First check if we want a new one or if there is a disk (still) present.
	while( (Res == IDOK && !IsDiskPresent() ) || FNewDisk ) { //v1.52j
		if ( drt == DRIVE_FIXED || drt == DRIVE_REMOTE ) {		// If it is a fixed disk we don't want a new one.
			FNewDisk = false;
			break;
		}
		if ( FUnattended ) throw EZipBuilder( DS_NoUnattSpan );
		if ( FDiskNr < 0 ) {		// -1=ReadSpan(), 0=WriteSpan()
			MsgStr = LoadZipStr( DS_InsertDisk, "Please insert last disk in set" );
			MsgFlag |= MB_ICONERROR;
		} else {
			if ( FZipBusy ) {		// Are we from ReadSpan() or WriteSpan()?
				// This is an estimate, we can't know if every future disk has the same space available and
				// if there is no disk present we can't determine the size unless it's set by MaxVolumeSize.
				__int64 SizeOfDisk = (FMaxVolumeSize) ? min( FSizeOfDisk, FMaxVolumeSize ) : FSizeOfDisk;	//RCV150199
				if ( SizeOfDisk > 0 ) {
					FTotalDisks = (unsigned short)max( (__int64)FDiskNr, (FFileSize + 4 + FFreeOnDisk1) / SizeOfDisk );	//v1.52j
					MsgStr = Format( LoadZipStr( DS_InsertVolume, "Please insert disk volume %.1d of %.1d"), ARRAYOFCONST(( FDiskNr + 1, FTotalDisks + 1 )) );
				} else
					MsgStr = Format( LoadZipStr( DS_InsertAVolume, "Please insert disk volume %.1d"), ARRAYOFCONST(( FDiskNr + 1 )) );
			} else
				MsgStr = Format( LoadZipStr( DS_InsertVolume, "Please insert disk volume %.1d of %.1d"), ARRAYOFCONST(( FDiskNr + 1, FTotalDisks + 1 )) );
		}
		MsgStr += Format( LoadZipStr( DS_InDrive, "\nin drive: %s" ), ARRAYOFCONST(( FDrive.SubString( 1, 1 ) )) );
		Res = MessageBox( FHandle, MsgStr.c_str(), Application->Title.c_str(), MsgFlag );
		FNewDisk = false;
	}
	// Check if user pressed Cancel or Mem is running out.
	if (  Res != IDOK ) throw EZipBuilder( DS_Canceled, false );
	if ( !Res )         throw EZipBuilder( DS_NoMem );
	return drt;
}

//---------------------------------------------------------------------------
// Function to find the EOC record at the end of the archive (on the last disk.)
// We can get a return value( true::Found, false::Not Found ) or an exception if not found.
bool __fastcall TZipBuilder::CheckIfLastDisk( struct ZipEndOfCentral &EOC, bool DoExcept ) {
	unsigned long  Sig;
	int			   DiskNo = 0;
	bool			   First = false;
	char			  *ZipBuf;

	FZipComment = "";
	FZipEOC     =  0;

	// Open the input archive, presumably the last disk.
	if ( (FInFileHandle = FileOpen( FInFileName, fmShareDenyWrite | fmOpenRead )) == -1 ) {
		if ( DoExcept ) throw EZipBuilder( DS_NoInFile );
		ShowZipMessage( DS_FileOpen );
		return false;
	}
	// Get the volume number if it's disk from a set.
	if ( FVolumeName.SubString( 1, 8 ) == "PKBACK# " )
		DiskNo = StrToIntDef( FVolumeName.SubString( 9, 3 ), 0 );

	// First a check for the first disk of a spanned archive,
	// could also be the last so we don't issue a warning yet.
	if ( FileRead( FInFileHandle, &Sig, 4 ) == 4 && Sig == ExtLocalSig &&
		  FileRead( FInFileHandle, &Sig, 4 ) == 4 && Sig == LocalFileHeaderSig ) {
		First = true;
		FIsSpanned = true;
	}
	// Next we do a check at the end of the file to speed things up if
	// there isn't a Zip archive comment.
	if ( (FFileSize = (long)FileSeek( FInFileHandle, -(SeekInt)(signed)sizeof( EOC ), 2 )) != -1 ) {
		FFileSize += sizeof( EOC );	// Save the archive size as a side effect.
		FRealFileSize = FFileSize;		// There could follow a correction on FFileSize.
		if ( FileRead( FInFileHandle, &EOC, sizeof( EOC ) ) == sizeof( EOC ) &&
				EOC.HeaderSig == EndCentralDirSig ) {
				FZipEOC = FFileSize - sizeof( EOC );
            return true;
		}
	}
	// Now we try to find the EOC record within the last 65535 + sizeof( EOC ) bytes
	// of this file because we don't know the Zip archive comment length at this time.
	try {
		int Size = min( FFileSize, (long)(65535 + sizeof( EOC )) );
		ZipBuf = new char[ Size + 1 ];
		if ( FileSeek( FInFileHandle, (SeekInt)(-Size), 2 ) == -1 ) throw EZipBuilder( DS_FailedSeek );
		if ( FileRead( FInFileHandle, ZipBuf, Size ) != Size ) throw EZipBuilder( DS_EOCBadRead );
		for( int i = Size - sizeof( EOC )- 1; i >= 0; i-- )
			if ( ZipBuf[ i ] == 'P' && ZipBuf[ i + 1 ] == 'K' && ZipBuf[ i + 2 ] == '\x05' && ZipBuf[ i + 3 ] == '\x06' ) {
				FZipEOC = FFileSize - Size + i;
				memcpy( &EOC, ZipBuf + i, sizeof( EOC ) );
				// Check if we really are at the end of the file, if not correct the filesize
				// and give a warning. (It should be an error but we are nice.)
				if ( i + sizeof( EOC ) + EOC.ZipCommentLen - Size ) {
					FFileSize += (i + sizeof( EOC ) + EOC.ZipCommentLen - Size );
					// Now we need a check for WinZip Self Extractor which makes SFX files which
					// allmost always have garbage at the end (Zero filled at 512 byte boundary!)
					// In this special case 'we' don't give a warning.
					bool ShowGarbageMsg = true;
					if (FRealFileSize - FFileSize < 512 && (FRealFileSize % 512) == 0) {
						int j = i + sizeof( EOC ) + EOC.ZipCommentLen;
						while( ZipBuf[ j ] == '\0' && j <= Size ) j++;
						if ( j == Size + 1 ) ShowGarbageMsg = false;
					}
					if ( ShowGarbageMsg ) ShowZipMessage( LI_GarbageAtEOF );
				}
				// If we have a ZipComment save it, must be after Garbage check because a '\0' is set!
				if ( EOC.ZipCommentLen ) {
					ZipBuf[ i + sizeof( EOC ) + EOC.ZipCommentLen ] = '\0';
					FZipComment = AnsiString( ZipBuf + i + sizeof( EOC ) );  // No codepage translation yet, wait for CEH read.
				}
				delete[] ZipBuf;
				return true;
		}
		delete[] ZipBuf;
	} catch ( ... ) {
		delete[] ZipBuf;
		if ( DoExcept ) throw;
	}
	if ( DoExcept ) {
		if ( !First && DiskNo ) throw EZipBuilder( DS_NotLastInSet, DiskNo );
		throw EZipBuilder( (First) ? ((DiskNo == 1) ? DS_FirstInSet : DS_FirstFileOnHD) : DS_NoValidZip );
	}
	return false;
}

//---------------------------------------------------------------------------
bool __fastcall TZipBuilder::IsRightDisk( unsigned int drt ) {
	// For fixed disks the disk is always right, we only need to change the filename.
	if ( drt == DRIVE_FIXED || drt == DRIVE_REMOTE ) {
		// Get and strip the file extension.
		String ext = ExtractFileExt( FInFileName );
		// Strip file extension and the last 3 numbers.
		FInFileName.SetLength( FInFileName.Length() - 3 - ext.Length() );
		// Set the filename to the diskfile number we want now.
		FInFileName += (IntToStr( 1001 + FDiskNr ).SubString( 2, 3 ) + ext);
		return true;
	}
	if ( FVolumeName == "PKBACK# " + IntToStr( 1001 + FDiskNr ).SubString( 2, 3 ) ) return true;
	return false;
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::GetNewDisk( int DiskSeq ) {
	unsigned int drt = DRIVE_REMOVABLE;

	FileClose( FInFileHandle );	// Close the file on the old disk first.
	FDiskNr = DiskSeq;
	do {
		if ( FInFileHandle == -1 ) {
			if ( drt != DRIVE_FIXED && drt != DRIVE_REMOTE ) ShowZipMessage( DS_NoInFile );
			// This prevents and endless loop if for some reason spanned parts on harddisk are missing.
			else throw EZipBuilder ( DS_NoInFile );
		}
		do {
			FNewDisk = true;
			drt = CheckForDisk();
		} while( !IsRightDisk( drt ) );
		// Open the the input archive on this disk.
	} while( (FInFileHandle = FileOpen( FInFileName, fmShareDenyWrite | fmOpenRead )) == -1 );
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::WriteJoin( void *Buffer, int BufferSize, int DSErrIdent ) {
	if ( FileWrite( FOutFileHandle, Buffer, BufferSize ) != BufferSize )
		throw EZipBuilder( DSErrIdent );

	// Give some progress info while writing.
	// While processing the central header we don't want messages.
	if ( OnProgress && FShowProgress ) OnProgress( this, ProgressUpdate, "", BufferSize );
}

//---------------------------------------------------------------------------
// Read data from the input file with a maximum of 8192(BufSize) bytes per read
// and write this to the output file.
// In case of an error an EZipBuilder Exception is thrown and this will
// be caught in WriteSpan.
void __fastcall TZipBuilder::RWSplitData( char *Buffer, int ReadLen, int ZSErrVal ) {
	int SizeR, ToRead;

	while( ReadLen > 0 ) {
		ToRead = min( ReadLen, BufSize );
		if ( (SizeR = FileRead( FInFileHandle, Buffer, ToRead )) != ToRead )
			throw EZipBuilder( ZSErrVal );
		WriteSplit( Buffer, SizeR, 0 );
		ReadLen -= SizeR;
	}
}

//---------------------------------------------------------------------------
void __fastcall TZipBuilder::RWJoinData( char *Buffer, int ReadLen, int DSErrIdent ) {
	int SizeR, ToRead;

	while( ReadLen > 0 ) {
		ToRead = min( ReadLen, BufSize );
		if ( (SizeR = FileRead( FInFileHandle, Buffer, ToRead )) != ToRead ) {
			// Check if we are at the end of a input disk.
			if ( FileSeek( FInFileHandle, 0, 1 ) != FileSeek( FInFileHandle, 0, 2 ) )
				throw EZipBuilder( DSErrIdent );
			// It seems we are at the end, so get a next disk.
			GetNewDisk( FDiskNr + 1 );
		}
		WriteJoin( Buffer, SizeR, DSErrIdent );
		ReadLen -= SizeR;
	}
}

//---------------------------------------------------------------------------
// Function to copy the central header of an archive and change while copying
// the Local Header offsets and finally the Central Header offset.
// We return 0 if no error or -2 (SE_CopyError) in case something goes wrong.
int __fastcall TZipBuilder::RWCentralDir( int &OutFile, struct ZipEndOfCentral &EOC, int OffsetChange ) {
	struct ZipCentralHeader CEH;
	int							Result = 0;

	try {
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// Read a central header.
			if ( FileRead( FInFileHandle, &CEH, sizeof( CEH ) ) != sizeof( CEH ) )
				throw EZipBuilder( DS_CEHBadRead );
			if ( CEH.HeaderSig != CentralFileHeaderSig ) throw EZipBuilder( DS_CEHWrongSig );
			// Change the offset.
			CEH.RelOffLocal += OffsetChange;
			// Write this changed central header to disk
			if ( FileWrite( OutFile, &CEH, sizeof( CEH ) ) != sizeof( CEH ) )
				throw EZipBuilder( DS_CEHBadWrite );
			// And the remaining bytes of the central header.
			if ( CopyBuffer( FInFileHandle, OutFile, CEH.FileNameLen + CEH.ExtraLen + CEH.FileComLen ) )
				throw EZipBuilder( DS_CEHBadCopy );
		}
		// Skip the EOC record (we already have read it.)
		if ( FileSeek( FInFileHandle, (SeekInt)sizeof( EOC ), 1 ) == -1 ) throw EZipBuilder( DS_EOCBadSeek );
		// Write the changed EndOfCentral directory record.
		EOC.CentralOffset += OffsetChange;
		if ( FileWrite( OutFile, &EOC, sizeof( EOC ) ) != sizeof( EOC ) )
			throw EZipBuilder( DS_EOCBadWrite );
		// And finally the archive comment itself.
		if ( CopyBuffer( FInFileHandle, OutFile, EOC.ZipCommentLen ) )
			throw EZipBuilder( DS_EOCBadCopy );
	} catch( ... ) {
		Result = -2;
	}
	return Result;
}

//----------------------------------------------------------------------------------------------------------------------
// We need to call Sysutils::Exception() with an extra (unwanted!) parameter.
// If we don't, the resource ID is transformed in an AnsiString as a number???
__fastcall EZipBuilder::EZipBuilder( const int Ident, bool Display ) : Sysutils::Exception( Ident, 0 ) {
	if ( Message.IsEmpty() ) Message = RESOURCE_ERROR + IntToStr( Ident );
	FDisplayMsg = Display;
	FResIdent   = Ident;
}

//---------------------------------------------------------------------------
__fastcall EZipBuilder::EZipBuilder( const int Ident, const int DiskNo ) : Sysutils::Exception( Ident, 0 ) {
	if ( Message.IsEmpty() ) Message = RESOURCE_ERROR + IntToStr( Ident );
	else Message = Format( Message, ARRAYOFCONST(( DiskNo )) );
	FDisplayMsg = true;
	FResIdent   = Ident;
}

//---------------------------------------------------------------------------
__fastcall EZipBuilder::EZipBuilder( const int Ident, const String Drive ) : Sysutils::Exception( Ident, 0 ) {
	if ( Message.IsEmpty() ) Message = RESOURCE_ERROR + IntToStr( Ident );
	else Message = Format( Message, ARRAYOFCONST(( Drive )) );
	FDisplayMsg = true;
	FResIdent   = Ident;
}

//---------------------------------------------------------------------------
__fastcall EZipBuilder::EZipBuilder( const int Ident, const String File1, const String File2 ) : Sysutils::Exception( Ident, 0 ) {
	if ( Message.IsEmpty() ) Message = RESOURCE_ERROR + IntToStr( Ident );
	else Message = Format( Message, ARRAYOFCONST(( File1, File2 )) );
	FDisplayMsg = true;
	FResIdent   = Ident;
}

//---------------------------------------------------------------------------
//***************************ZipShellFormat**********************************
ZipBuilder::TZipBuilder *ParentBuilder = NULL;
HHOOK							 Fhhk;

//---------------------------------------------------------------------------
__fastcall TSHFormatThread::TSHFormatThread( ZipBuilder::TZipBuilder *MyParent, bool CreateSuspended ) : TThread( CreateSuspended ) {
	if ( !ParentBuilder ) {
		ParentBuilder   = MyParent;
		FreeOnTerminate = true;
		Priority			 = tpNormal;
		ParentBuilder->FBeginFormat = true;
	} else Terminate();	// We can't have two or more ZipBuilders do a format simultaniously.
}

//---------------------------------------------------------------------------
__fastcall TSHFormatThread::~TSHFormatThread( void ) {
	ParentBuilder = NULL;
}

//---------------------------------------------------------------------------
void __fastcall TSHFormatThread::Execute() {
	long					 OldMode = ::SetErrorMode( SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX );
	HINSTANCE			 SHFormatHandle;
	GetSHFormatAddress SHFormatDrive;

	if ( !Terminated )  {
		if ( ( SHFormatHandle = ::LoadLibrary( "Shell32.dll" )) != NULL ) {
			if ( (SHFormatDrive = (GetSHFormatAddress)::GetProcAddress( SHFormatHandle, "SHFormatDrive" )) != NULL ) {
				if ( (Fhhk = ::SetWindowsHookEx( WH_CALLWNDPROCRET, (HOOKPROC)CallWndRetProc, NULL, ThreadID ) ) != NULL ) {
					// The next call is a modal one, when we continue either format is ready, canceled by user or there is an error.
					ParentBuilder->FFormatResult = SHFormatDrive( Application->Handle, ParentBuilder->FDriveNr, 0xFFFF, 0 );
					::UnhookWindowsHookEx( Fhhk );
				}	// else no hook
			}	// else no function???
			::FreeLibrary( SHFormatHandle );
		}	// else no library???
	} else ParentBuilder->FFormatResult = -1;	// Error.
	ParentBuilder->FFound = 2;	// Always stop no matter what.
	::SetErrorMode( OldMode );
}

//---------------------------------------------------------------------------
// This works for W95 english and dutch version; No garantees for any other OS.
int __stdcall TSHFormatThread::CallWndRetProc( int code, WPARAM wp, LPARAM lp ) {
	CWPRETSTRUCT *msg = (CWPRETSTRUCT *)lp;
	HWND          th;
	if ( code >= 0 ) {
		Sleep( 1 );
		// First thing we do when the format window gets created.
		if ( msg->message == WM_SHOWWINDOW || msg->message == WM_ENABLE ) {
			if ( (th = ::GetDlgItem( ParentBuilder->Fhwnd, 35 )) == msg->hwnd )
				::EnableWindow( th, false );		// Disable copy system files.
			if ( (th = ::GetDlgItem( ParentBuilder->Fhwnd, 39 )) == msg->hwnd ) {
				::CheckDlgButton( ParentBuilder->Fhwnd, 39, BST_CHECKED );		// We always want a label.
				::EnableWindow( th, false );		// Disable the use of the label.
			}
			if ( (th = ::GetDlgItem( ParentBuilder->Fhwnd, 38 )) == msg->hwnd )
				::EnableWindow( th, false );		// Disable the edit of the label.
			if ( (th = ::GetDlgItem( ParentBuilder->Fhwnd, 41 )) == msg->hwnd )
				::PostMessage( th, BM_SETCHECK, BST_UNCHECKED, 0 );	// No summary by default.
		}
		// Click the Ok button.
		if ( msg->message == 0x402 && !ParentBuilder->ConfirmErase && ParentBuilder->FBeginFormat ) {
			::PostMessage( ::GetDlgItem( ParentBuilder->Fhwnd, 1 ), BM_CLICK, 0, 0 );
			ParentBuilder->FBeginFormat = false;
		}
		// And reset the label to what it was.
		if ( msg->message == WM_SETTEXT && ::GetDlgItem( ParentBuilder->Fhwnd, 38 ) == msg->hwnd ) {
			char itemstr[ 12 ];
			::GetDlgItemText( ParentBuilder->Fhwnd, 38, itemstr, 12 );
			if ( strcmp( itemstr, ParentBuilder->FVolumeName.c_str() ) )
				::SetDlgItemText( ParentBuilder->Fhwnd, 38, ParentBuilder->FVolumeName.c_str() );
		}
		// Close the format window.
		if ( msg->message == BM_SETSTYLE && !ParentBuilder->ConfirmErase && msg->wParam == BS_PUSHBUTTON ) {
			th = ::GetDlgItem( ParentBuilder->Fhwnd, 2 );
			if ( th == msg->hwnd ) ::PostMessage( th, BM_CLICK, 0, 0 );
		}
	}
	return ::CallNextHookEx( Fhhk, code, wp, lp );
}

// Function to read a Zip archive and change one or more file specifications.
// Source and Destination should be of the same type. (path or file)
// If NewDateTime is 0 then no change is made in the date/time fields.
// Return values:
// 0            All Ok.
// -7           Rename errors. See ZipMsgXX.rc
// -8           Memory allocation error.
// -9           General unknown Rename error.
// -10          Dest should also be a filename.
int __fastcall TZipBuilder::Rename( TList &RenameList, unsigned long DateTime ) {
	ZipEndOfCentral    EOC;
	ZipCentralHeader   CEH;
	ZipLocalHeader     LOH;
	String             OrigFileName;
	String             MsgStr;
	String             OutFilePath;
	struct MDZipData **MDZD = NULL;
	char				   *Buffer = NULL;
	int				    TotalBytesToRead = 0;
	int				    TotalBytesWrite;
	int				    Result = 0;
	ZipRenameRec		*RenRec;

	FZipBusy      = true;
	FShowProgress = false;
	FInFileName   = FZipFileName;
	FInFileHandle = -1;
	Screen->Cursor = crHourGlass;

	// If we only have a source path make sure the destination is also a path.
	for( int i = 0; i < RenameList.Count; i++ ) {
		RenRec = (ZipRenameRec *)RenameList.Items[ i ];
		RenRec->Source = ReplaceForwardSlash( RenRec->Source.c_str() );
		RenRec->Dest   = ReplaceForwardSlash( RenRec->Dest.c_str() );
		if ( !ExtractFileName( RenRec->Source ).Length() ) {	// Assume it's a path.
			// Make sure destination is a path also.
			RenRec->Dest   = AppendSlash( ExtractFilePath( RenRec->Dest ) );
			RenRec->Source = AppendSlash( RenRec->Source );
		} else if ( !ExtractFileName( RenRec->Dest ).Length() )
			return -10;  // Dest should also be a filename.
	}
	try {
		Buffer = new char[ BufSize ];
		// Check the input file.
		if ( !FileExists( FZipFileName ) )
			throw EZipBuilder( DS_NoInFile );
		// Make a temporary filename like: C:\...\zipxxxx.zip
		if ( !FTempDir.Length() )
			GetTempPath( MAX_PATH, Buffer );
		else
			StrPLCopy( Buffer, FTempDir, BufSize );
		if ( !GetTempFileName( Buffer, "zip", 0, Buffer ) )
			throw EZipBuilder( DS_NoTempFile );
		OutFilePath = Buffer;
		DeleteFile( OutFilePath );
		OutFilePath = ChangeFileExt( OutFilePath, ".zip" );

		// Create the output file.
		FOutFileHandle = FileCreate( OutFilePath );
		if ( FOutFileHandle == -1 )
			throw EZipBuilder( DS_NoOutFile );

		// The following function will read the EOC and some other stuff:
		CheckIfLastDisk( EOC, true );

		// Get the date-time stamp and save for later.
		FDateStamp = FileGetDate( FInFileHandle );

		// Now we now the number of zipped entries in the zip archive
		FTotalDisks = EOC.ThisDiskNo;
		if ( EOC.ThisDiskNo )
			throw EZipBuilder( RN_NoRenOnSpan );

		// Go to the start of the input file.
		if ( FileSeek( FInFileHandle, 0, 0 ) == -1 )
			throw EZipBuilder( DS_FailedSeek );

		// Write the SFX header if present.
		if ( CopyBuffer( FInFileHandle, FOutFileHandle, FSFXOffset ) )
			throw EZipBuilder( RN_ZipSFXData );

		// Go to the start of the Central directory.
		if ( FileSeek( FInFileHandle, (SeekInt)EOC.CentralOffset, 0 ) == -1 )
			throw EZipBuilder( DS_FailedSeek );

		MDZD = AllocSpanMem( EOC.TotalEntries );		// Allocate memory.

		// Read for every entry: The central header and save information for later use.
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// Read a central header.
			if ( FileRead( FInFileHandle, &CEH, sizeof( CEH ) ) != sizeof( CEH ) )
				throw EZipBuilder( DS_CEHBadRead );

			if ( CEH.HeaderSig != CentralFileHeaderSig )
				throw EZipBuilder( DS_CEHWrongSig );

			// Now the filename.
			if ( FileRead( FInFileHandle, Buffer, CEH.FileNameLen ) != CEH.FileNameLen )
				throw EZipBuilder( DS_CENameLen );

			// Save the file name info in the MDZD structure.
			MDZD[ i ]->FileNameLen = CEH.FileNameLen;
			MDZD[ i ]->FileName    = new char[ CEH.FileNameLen + 1 ];
			StrLCopy( MDZD[ i ]->FileName, Buffer, CEH.FileNameLen );
			MDZD[ i ]->RelOffLocal = CEH.RelOffLocal;
			MDZD[ i ]->DateTime    = DateTime;

			// We need the total number of bytes we are going to read for the progress event.
			TotalBytesToRead += (int)(CEH.ComprSize + CEH.FileNameLen + CEH.ExtraLen);

			// Seek past the extra field and the file comment.
			if ( FileSeek( FInFileHandle, (SeekInt)(CEH.ExtraLen + CEH.FileComLen), 1 ) == -1 )
				throw EZipBuilder( DS_FailedSeek );
		}
		FShowProgress = true;
		if ( FOnProgress ) {
			FOnProgress( this, TotalFiles2Process, "", EOC.TotalEntries );
			FOnProgress( this, TotalSize2Process,  "", TotalBytesToRead );
		}
		// Read for every zipped entry: The local header, variable data, fixed data
		// and if present the Data descriptor area.
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// Seek to the first/next entry.
			FileSeek( FInFileHandle, (SeekInt)MDZD[ i ]->RelOffLocal, 0 );

			// First the local header.
			if ( FileRead( FInFileHandle, &LOH, sizeof( LOH ) ) != sizeof( LOH ) )
				throw EZipBuilder( DS_LOHBadRead );
			if ( LOH.HeaderSig != LocalFileHeaderSig )
				throw EZipBuilder( DS_LOHWrongSig );

			// Now the filename.
			if ( FileRead( FInFileHandle, Buffer, LOH.FileNameLen ) != LOH.FileNameLen )
				throw EZipBuilder( DS_LONameLen );

			// Set message info on the start of this new fileread now we still have the old filename.
			MsgStr = LoadZipStr( RN_ProcessFile, "Processing: " ) + MDZD[ i ]->FileName;

			// Calculate the bytes we are going to write; we 'forget' the difference
			// between the old and new filespecification length.
			TotalBytesWrite = LOH.FileNameLen + LOH.ExtraLen + LOH.ComprSize;

			// Check if the original path and/or filename needs to be changed.
			OrigFileName = ReplaceForwardSlash( MDZD[ i ]->FileName );
			for( int m = 0; m < RenameList.Count; m++ ) {
				RenRec = (ZipRenameRec *)RenameList.Items[ m ];
				int k = UpperCase( OrigFileName ).Pos( UpperCase( RenRec->Source ) );
				if ( k ) {
					OrigFileName.Delete( k, RenRec->Source.Length() );
					OrigFileName.Insert( RenRec->Dest, k );
					LOH.FileNameLen = MDZD[ i ]->FileNameLen = (unsigned short)OrigFileName.Length();
					for( k = 1; k <= OrigFileName.Length(); k++ )
						if ( OrigFileName[ k ] == '\\' ) OrigFileName[ k ] = '/';
					MsgStr += LoadZipStr( RN_RenameTo, " renamed to: " ) + OrigFileName;
					delete[] MDZD[ i ]->FileName;
					MDZD[ i ]->FileName = new char[ LOH.FileNameLen + 1 ];
					StrPLCopy( MDZD[ i ]->FileName, OrigFileName, LOH.FileNameLen + 1 );
					// Change Date and Time if needed.
					if ( RenRec->DateTime ) MDZD[ i ]->DateTime = RenRec->DateTime;
				}
			}
			if ( FOnMessage ) FOnMessage( this, 0, MsgStr );

			// Change Date and/or Time if needed.
			if ( MDZD[ i ]->DateTime ) {
				LOH.ModifDate = HIWORD( MDZD[ i ]->DateTime );
				LOH.ModifTime = LOWORD( MDZD[ i ]->DateTime );
			}
			// Change info for later while writing the central dir.
			MDZD[ i ]->RelOffLocal = FileSeek( FOutFileHandle, 0, 1 );

			if ( FOnProgress )
				FOnProgress( this, NewFile, ReplaceForwardSlash( MDZD[ i ]->FileName ), TotalBytesWrite );

			// Write the local header to the destination.
			WriteJoin( &LOH, sizeof( LOH ), DS_LOHBadWrite );

			// Write the filename.
			WriteJoin( MDZD[ i ]->FileName, LOH.FileNameLen, DS_LOHBadWrite );

			// And the extra field
			if ( CopyBuffer( FInFileHandle, FOutFileHandle, LOH.ExtraLen ) )
				throw EZipBuilder( DS_LOExtraLen );

			// Read and write Zipped data
			if ( CopyBuffer( FInFileHandle, FOutFileHandle, LOH.ComprSize ) )
				throw EZipBuilder( DS_ZipData );

			// Read DataDescriptor if present.
			if ( LOH.Flag & 0x0008 )
				if ( CopyBuffer( FInFileHandle, FOutFileHandle, sizeof( ZipDataDescriptor ) ) )
					throw EZipBuilder( DS_DataDesc );
		}	// Now we have written al entries.

		// Now write the central directory with possibly changed offsets and filename(s).
		FShowProgress = false;
		for( int i = 0; i < EOC.TotalEntries; i++ ) {
			// Read a central header.
			if ( FileRead( FInFileHandle, &CEH, sizeof( CEH ) ) != sizeof( CEH ) )
				throw EZipBuilder( DS_CEHBadRead );
			if ( CEH.HeaderSig != CentralFileHeaderSig )
				throw EZipBuilder( DS_CEHWrongSig );

			// Change Date and/or Time if needed.
			if ( MDZD[ i ]->DateTime ) {
				CEH.ModifDate = HIWORD( MDZD[ i ]->DateTime );
				CEH.ModifTime = LOWORD( MDZD[ i ]->DateTime );
			}
			// Now the filename.
			if ( FileRead( FInFileHandle, Buffer, CEH.FileNameLen ) != CEH.FileNameLen  )
				throw EZipBuilder( DS_CENameLen );

			// Save the first Central directory offset for use in EOC record.
			if ( !i )
				EOC.CentralOffset = FileSeek( FOutFileHandle, 0, 1 );

			// Change the central header info with our saved information.
			CEH.RelOffLocal = MDZD[ i ]->RelOffLocal;
			EOC.CentralSize = EOC.CentralSize - CEH.FileNameLen + MDZD[ i ]->FileNameLen;
			CEH.FileNameLen = MDZD[ i ]->FileNameLen;

			// Write this changed central header to disk
			WriteJoin( &CEH, sizeof( CEH ), DS_CEHBadWrite );

			// Write to destination the central filename.
			WriteJoin( MDZD[ i ]->FileName, CEH.FileNameLen, DS_CEHBadWrite );

			// And the extra field
			if ( CopyBuffer( FInFileHandle, FOutFileHandle, CEH.ExtraLen ) )
				throw EZipBuilder( DS_CEExtraLen );

			// And the file comment.
			if ( CopyBuffer( FInFileHandle, FOutFileHandle, CEH.FileComLen ) )
				throw EZipBuilder( DS_CECommentLen );
		}
		// Write the changed EndOfCentral directory record.
		WriteJoin( &EOC, sizeof( EOC ), DS_EOCBadWrite );

		// And finally the archive comment
		if ( CopyBuffer( FInFileHandle, FOutFileHandle, EOC.ZipCommentLen ) )
			throw EZipBuilder( DS_EOArchComLen );
	}
	catch ( const EZipBuilder &ers ) {	// All Rename specific errors..
		ShowExceptionError( ers );
		Result = -7;
	}
	catch ( const MEMEXCEPT &me ) {		// All memory allocation errors.
		ShowZipMessage( GE_NoMem );
		Result = -8;
	}
	catch( const Exception &E ) {
		ShowZipMessage( DS_ErrorUnknown, "\n" + E.Message );
		Result = -9;
	}
	catch ( ... ) {							// The remaining errors, should not occur.
		ShowZipMessage( DS_ErrorUnknown );
		Result = -9;
	}
	delete[] Buffer;
	DeleteSpanMem( MDZD, EOC.TotalEntries );

	// Give final progress info at the end.
	if ( FOnProgress ) FOnProgress( this, EndOfBatch, "", 0 );

	if ( FInFileHandle != -1 ) FileClose( FInFileHandle );
	if ( FOutFileHandle != -1 ) {
		FileSetDate( FOutFileHandle, FDateStamp );
		FileClose( FOutFileHandle );
		if ( Result )   // An error somewhere, OutFile is not reliable.
			DeleteFile( OutFilePath );
		else {
			EraseFile( FZipFileName, FHowToDelete );
			RenameFile( OutFilePath, FZipFileName );
			List();
		}
	}
	FZipBusy = False;
	Screen->Cursor = crDefault;
	return Result;
}

// Function to copy one or more zipped files from the zip archive to another zip archive
// FSpecArgs in source is used to hold the filename(s) to be copied.
// When this function is ready FSpecArgs contains the file(s) that where not copied.
// Return values:
// 0            All Ok.
// -7           CopyZippedFiles errors. See ZipMsgXX.rc
// -8           Memory allocation error.
// -9           General unknown CopyZippedFiles error.
int __fastcall TZipBuilder::CopyZippedFiles( TZipBuilder *DestZipBuilder, bool DeleteFromSource, OvrOpts OverwriteDest ) {
	ZipEndOfCentral    EOC;
	ZipCentralHeader   CEH;
	ZipDirEntry			*zde, *pzd;
	String             OutFilePath;
	struct MDZipData **MDZD = NULL;
	char				   *Buffer = NULL;
	int				    Result = 0;
	int					 In2FileHandle;
	TStringList			*NotCopiedFiles = NULL;
	bool					 Found;
	int					 DestMemCount;

	FZipBusy = true;
	Screen->Cursor = crHourGlass;
	FShowProgress = false;
	try {
		// Are source and destination different?
		if ( DestZipBuilder == this || !AnsiStrIComp( ZipFileName.c_str(), DestZipBuilder->ZipFileName.c_str() ) )
			throw EZipBuilder( CF_SourceIsDest );
		Buffer = new char[ BufSize ];

		// Now check for every source file if it is in the destination archive and determine what to do.
		// we use the three most significant bits from the Flag field from ZipDirEntry to specify the action
		// None           = 000xxxxx, Destination no change. Action: Copy old Dest to New Dest
		// Add            = 001xxxxx (New).                  Action: Copy Source to New Dest
		// Overwrite      = 010xxxxx (OvrAlways)             Action: Copy Source to New Dest
		// AskToOverwrite = 011xxxxx (OvrConfirm)	Action to perform: Overwrite or NeverOverwrite
		// NeverOverwrite = 100xxxxx (OvrNever)				  Action: Copy old Dest to New Dest
		for( int s = 0; s < FSpecArgs->Count; s++ ) {
			Found = false;
			for( int d = 0; d < DestZipBuilder->Count; d++ ) {
				zde = (ZipDirEntry *)DestZipBuilder->ZipContents->Items[ d ];
				if ( !AnsiStrIComp( FSpecArgs->Strings[ s ].c_str(), zde->FileName.c_str() ) ) {
					Found = true;
					zde->Flag &= 0x1FFF;	// Clear the three upper bits.
					zde->Flag |= (OverwriteDest == OvrAlways) ? 0x4000ui16 : (OverwriteDest == OvrNever) ? 0x8000ui16 : 0x6000ui16;
					break;
				}
			}
			if ( !Found ) {	// Add the Filename to the list and set flag
				zde = new ZipDirEntry;
				DestZipBuilder->FZipContents->Add( zde );
				zde->FileName       = FSpecArgs->Strings[ s ];
				zde->FileName.Unique();
				zde->FileNameLength = (Word)FSpecArgs->Strings[ s ].Length();
				zde->Flag |= 0x2000;		// (a new entry)
				zde->ExtraData = NULL;	//Needed when deleting zde
			}
		}
		// Make a temporary filename like: C:\...\zipxxxx.zip for the new destination
		if ( !FTempDir.Length() )
			GetTempPath( MAX_PATH, Buffer );
		else
			StrPLCopy( Buffer, FTempDir, BufSize );
		if ( !GetTempFileName( Buffer, "zip", 0, Buffer ) )
			throw EZipBuilder( DS_NoTempFile );
		DeleteFile( OutFilePath = Buffer );
		OutFilePath = ChangeFileExt( OutFilePath, ".zip" );

		// Create the output file.
		FOutFileHandle = FileCreate( OutFilePath );
		if ( FOutFileHandle == -1 )
			throw EZipBuilder( DS_NoOutFile );

		// The following function a.o. open the input file no. 1.
		CheckIfLastDisk( EOC, true );

		// Open the second input archive, i.e. the original destination.
		if ( (In2FileHandle = FileOpen( DestZipBuilder->ZipFileName, fmShareDenyWrite | fmOpenRead )) == -1 )
			throw EZipBuilder( CF_DestFileNoOpen );

		// Get the date-time stamp and save for later.
		FDateStamp = FileGetDate( In2FileHandle );

		// Write the SFX header if present.
		if ( CopyBuffer( In2FileHandle, FOutFileHandle, DestZipBuilder->SFXOffset ) )
			throw EZipBuilder( CF_SFXCopyError );

		NotCopiedFiles = new TStringList();
		// Now walk trough the destination, copying and replacing
		DestMemCount = DestZipBuilder->FZipContents->Count;
		MDZD = AllocSpanMem( DestMemCount );	// Allocate memory.

		// Copy the local data and save central header info for later use.
		for( int d = 0; d < DestMemCount; d++ ) {
			zde = (ZipDirEntry *)DestZipBuilder->ZipContents->Items[ d ];
			if ( (zde->Flag & 0xE000) == 0x6000 ) {	// Ask first if we may overwrite.
				bool Overwrite = false;
				// Do we have a event assigned for this then don't ask.
				if ( FOnCopyZipOverwrite )
					FOnCopyZipOverwrite( DestZipBuilder, zde->FileName, Overwrite );
				else Overwrite = (::MessageBox( FHandle,
											Format( LoadZipStr( CF_OverwriteYN, "Overwrite %s in %s ?" ), ARRAYOFCONST(( zde->FileName, DestZipBuilder->ZipFileName )) ).c_str(),
											Application->Title.c_str(),
											MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 )== IDYES) ? true : false;
				zde->Flag &= 0x1FFF;	// Clear the three upper bits.
				zde->Flag |= (Overwrite) ? 0x4000ui16 : 0x8000ui16;
			}
			// Change info for later while writing the central dir in new Dest.
			MDZD[ d ]->RelOffLocal = FileSeek( FOutFileHandle, 0, 1 );

			if ( (zde->Flag & 0x6000) == 0x0000 ) {	// Copy from original dest to new dest.
				// Set the file pointer to the start of the local header.
				FileSeek( In2FileHandle, (SeekInt)zde->RelOffLocalHdr, 0 );
				if ( CopyBuffer( In2FileHandle, FOutFileHandle, sizeof( ZipLocalHeader ) + zde->FileNameLength + zde->ExtraFieldLength + zde->CompressedSize ) )
					throw EZipBuilder( CF_CopyFailed, DestZipBuilder->ZipFileName, DestZipBuilder->ZipFileName );
				if ( zde->Flag & 0x8000 ) {
					NotCopiedFiles->Add( zde->FileName );
					// Delete also from FSpecArgs, should not be deleted from source later.
					FSpecArgs->Delete( FSpecArgs->IndexOf( zde->FileName ) );
				}
			} else {	// Copy from source to new dest.
				// Find the filename in the source archive and position the file pointer.
				for( int s = 0; s < Count; s++ ) {
					pzd = (ZipDirEntry *)ZipContents->Items[ s ];
					if ( !AnsiStrIComp( pzd->FileName.c_str(), zde->FileName.c_str() ) ) {
						FileSeek( FInFileHandle, (SeekInt)pzd->RelOffLocalHdr, 0 );
						if ( CopyBuffer( FInFileHandle, FOutFileHandle, sizeof( ZipLocalHeader ) + pzd->FileNameLength + pzd->ExtraFieldLength + pzd->CompressedSize ) )
							throw EZipBuilder( CF_CopyFailed, ZipFileName, DestZipBuilder->ZipFileName );
						break;
					}
				}
			}
			// Save the file name info in the MDZD structure.
			MDZD[ d ]->FileNameLen = zde->FileNameLength;
			MDZD[ d ]->FileName    = new char[ zde->FileNameLength + 1 ];
			StrPLCopy( MDZD[ d ]->FileName, zde->FileName, zde->FileNameLength );
		}	// Now we have written al entries.

		// Now write the central directory with possibly changed offsets.
		// Remember the EOC we are going to use is from the wrong input file!
		EOC.CentralSize = 0;
		for( int d = 0; d < DestMemCount; d++ ) {
			zde = (ZipDirEntry *)DestZipBuilder->ZipContents->Items[ d ];
			Found = false;
			// Rebuild the CEH structure.
			if ( (zde->Flag & 0x6000) == 0x0000 ) {	// Copy from original dest to new dest.
				pzd = (ZipDirEntry *)DestZipBuilder->ZipContents->Items[ d ];
				Found = true;
			} else {	// Copy from source to new dest.
				// Find the filename in the source archive and position the file pointer.
				for( int s = 0; s < Count; s++ ) {
					pzd = (ZipDirEntry *)ZipContents->Items[ s ];
					if ( !AnsiStrIComp( pzd->FileName.c_str(), zde->FileName.c_str() ) ) {
						Found = true;
						break;
					}
				}
			}
			if ( !Found )
				throw EZipBuilder( CF_SourceNotFound, zde->FileName, ZipFileName );
			memcpy( &CEH.VersionMadeBy0, pzd, sizeof( ZipCentralHeader )- 4 );
			CEH.HeaderSig = CentralFileHeaderSig;
			CEH.Flag &= 0x1FFF;
			CEH.RelOffLocal = MDZD[ d ]->RelOffLocal;
			// Save the first Central directory offset for use in EOC record.
			if ( !d )
				EOC.CentralOffset = FileSeek( FOutFileHandle, 0, 1 );
			EOC.CentralSize += (sizeof( CEH ) + CEH.FileNameLen + CEH.ExtraLen + CEH.FileComLen);

			// Write this changed central header to disk
			WriteJoin( &CEH, sizeof( CEH ), DS_CEHBadWrite );

			// Write to destination the central filename.
			WriteJoin( MDZD[ d ]->FileName, CEH.FileNameLen, DS_CEHBadWrite );

			// And the extra field from zde or pzd.
			if ( CEH.ExtraLen )
				WriteJoin( pzd->ExtraData, CEH.ExtraLen, DS_CEExtraLen );

			// And the file comment.
         if ( CEH.FileComLen )
				WriteJoin( pzd->FileComment.c_str(), CEH.FileComLen, DS_CECommentLen );
		}
		EOC.TotalEntries = EOC.CentralEntries = (unsigned short)DestMemCount;
		EOC.ZipCommentLen = (unsigned short)DestZipBuilder->ZipComment.Length();

		// Write the changed EndOfCentral directory record.
		WriteJoin( &EOC, sizeof( EOC ), DS_EOCBadWrite );

		// And finally the archive comment
        #if __BORLANDC__ ==	1360    // BCB5=0x0550(1360)
		FileSeek( In2FileHandle, (__int64)DestZipBuilder->ZipEOC + sizeof( EOC ), 0 );
        #else
		FileSeek( In2FileHandle, (SeekInt)DestZipBuilder->ZipEOC + sizeof( EOC ), 0 );
        #endif
		if ( CopyBuffer( In2FileHandle, FOutFileHandle, DestZipBuilder->ZipComment.Length() ) )
			throw EZipBuilder( DS_EOArchComLen );

		if ( FInFileHandle != -1 ) FileClose( FInFileHandle );
		// Now delete all copied files from the source when deletion is wanted.
		if ( DeleteFromSource && FSpecArgs->Count > 0 ) {
			FZipBusy = False;
			Delete();	// Delete files specified in FSpecArgs and update the contents.
		}
		FSpecArgs->Assign( NotCopiedFiles );	// Info for the caller.
	}
	catch( const EZipBuilder &ers ) {	// All CopyZippedFiles specific errors..
		ShowExceptionError( ers );
		Result = -7;
	}
	catch( const MEMEXCEPT &me ) {		// All memory allocation errors.
		ShowZipMessage( GE_NoMem );
		Result = -8;
	}
	catch( const Exception &E ) {
		ShowZipMessage( DS_ErrorUnknown, "\n" + E.Message );
		Result = -9;
	}
	catch( ... ) {								// The remaining errors, should not occur.
		ShowZipMessage( DS_ErrorUnknown );
		Result = -9;
	}
	DeleteSpanMem( MDZD, DestMemCount );
	delete NotCopiedFiles;
	delete[] Buffer;

	if ( In2FileHandle != -1 ) FileClose( In2FileHandle );
	if ( FOutFileHandle != -1 ) {
		FileSetDate( FOutFileHandle, FDateStamp );
		FileClose( FOutFileHandle );
		if ( Result )			// An error somewhere, OutFile is not reliable.
			DeleteFile( OutFilePath );
		else {
			EraseFile( DestZipBuilder->FZipFileName, DestZipBuilder->HowToDelete );
			if ( !RenameFile( OutFilePath, DestZipBuilder->FZipFileName ) )
				EraseFile( OutFilePath, DestZipBuilder->HowToDelete );
		}
	}
	DestZipBuilder->List();	// Update the old(possibly some entries were added temporarily) or new destination.
	Screen->Cursor = crDefault;
	FZipBusy = False;
	return Result;
}

