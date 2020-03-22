/* TZipBuilder component v 1.60k by Chris Vleghert
 * a C++ Builder 1, 3 and 4.0 wrapper for the freeware ZIP and UNZIP DLL's
 * from Chris Vleghert.
 *
 * v1.60k  May 21, 1999
 * e-mail: cvleghrt@WorldOnline.nl
 * www:    http://www.geocities.com/SiliconValley/Orchard/8607/ or
 * www:    http://members.tripod.lycos.nl/Vleghert/
 *
 * or
 * www:    http://www.geocities.com/SiliconValley/Network/2114/
 * www:    http://members.tripod.com/englere/
 */

#ifndef ZipMainUnitH
#define ZipMainUnitH

//---------------------------------------------------------------------------
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Messages.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <vcl\ShellApi.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Buttons.hpp>

#include <WinNT.h>

#include "CallBack.h"
#include "UnzipDLL.h"
#include "ZipDLL.h"
#include "ZipMsg.h"

// Needed in ConvertOem2Iso function.
#define FS_FAT_   0
#define FS_HPFS_  6
#define FS_NTFS_ 11

//---------------------------------------------------------------------------
//-------------------------BCB1, BCB3 and BCB4  differences------------------
#if __BORLANDC__ < 1328		// BCB1=0x0520(1312)
#	// BCB_1 doesn't know 'PACKAGE'
#	define PACKAGE
namespace Sysutils {
	extern bool __fastcall DeleteFile( const System::AnsiString aStr );
}
#	define PGBCONV unsigned short int
#	// The old style Out of Memory exception.
#	include <except.h>
#	define MEMEXCEPT	xalloc
#else								// BCB3=0x0530(1328)
#	define PGBCONV unsigned int
#	// xalloc is obsolete and not useed in BCB3.
#	include <new.h>
#	define MEMEXCEPT	std::bad_alloc
#endif
#if __BORLANDC__ == 1344		// BCB4=0x540(1344)
typedef __int64 SeekInt;
#elseif __BORLANDC__ ==	1360    // BCB5=0x0550(1360)
typedef __int64 SeekInt;
#else
typedef int SeekInt;
#endif

// We need a forward declaration.
namespace ZipBuilder {
	class TZipBuilder;
}


namespace ZipShellFormat {

//---SHFormatDrive-----------------------------------------------------------
// Return values:
// Ok=6 NoFormat=-3, Cancel=-2, Error=-1
// Drive:
// 0=A:\ 1=B:\ etc.
// FormatID:
// 0=1,44 and 1,2Mb 3=360Kb 5=720 Kb FFFF=default size
// Options:
// 0=Quick 1=Full 2=SysOnly
typedef long __stdcall (*GetSHFormatAddress)( HWND hwnd, long drive, long Fid, long Opt );

//---------------------------------------------------------------------------
class PACKAGE TSHFormatThread : public TThread {
	protected:
		void __fastcall Execute();
		static int __stdcall CallWndRetProc( int code, WPARAM wp, LPARAM lp );

	public:
		__fastcall TSHFormatThread( ZipBuilder::TZipBuilder *MyParent, bool CreateSuspended );
		__fastcall virtual ~TSHFormatThread( void );
};

} /* EOF namespace ZipShellFormat */

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
	using namespace ZipShellFormat;
#endif

extern ZipBuilder::TZipBuilder *ParentBuilder;
extern HHOOK						  Fhhk;



namespace DiskSpan {
 /*  The zipfile format is defined as below:
 *
 *   [Extra Extended Signature]
 *   NumberOfFiles *{ local header + Filename + [extra data] + [file data] + [data_descriptor] }
 *   NumberOfFiles *{ central directory + Filename + [extra data] + [filecomment] }
 *   End Of Central directory + [ZipFile comment]
 */

#pragma option -a1
struct ZipLocalHeader {
	unsigned long	HeaderSig;			// Should be 0x04034B50
	unsigned short	VersionNeed;
	unsigned short	Flag;
	unsigned short	ComprMethod;
	unsigned short	ModifTime;
	unsigned short	ModifDate;
	unsigned long	CRC32;
	unsigned long	ComprSize;
	unsigned long	UnComprSize;
	unsigned short	FileNameLen;
	unsigned short ExtraLen;
};
//	... and the filename itself,
// ... and the extra data.

struct ZipDataDescriptor {
	unsigned long	DataDescSig;		// Should be 0x08074B50
	unsigned long	CRC32;
	unsigned long	ComprSize;
	unsigned long	UnComprSize;
};


struct ZipCentralHeader {
	unsigned long	HeaderSig;			// Should be 0x02014B50
	unsigned char	VersionMadeBy0;   // Made by version number
	unsigned char	VersionMadeBy1;   // Made by host number
	unsigned short	VersionNeed;
	unsigned short	Flag;
	unsigned short	ComprMethod;
	unsigned short	ModifTime;
	unsigned short	ModifDate;
	unsigned long	CRC32;
	unsigned long	ComprSize;
	unsigned long	UnComprSize;
	unsigned short	FileNameLen;
	unsigned short ExtraLen;
	unsigned short	FileComLen;
	unsigned short	DiskStart;			// The number of the disk on which this file begins.
	unsigned short	IntFileAtt;
	unsigned long	ExtFileAtt;
	unsigned long	RelOffLocal;		// This is the offset from the start of the first disk on
												// which this file appears, to where the local header
												// should be found.
};
//	... and the filename itself,
// ... and the extra data,
// ... and the file comment.

struct ZipEndOfCentral {
	unsigned long	HeaderSig;			// Should be 0x06054B50
	unsigned short	ThisDiskNo;
	unsigned short	CentralDiskNo;
	unsigned short	CentralEntries;	// Total number of entries in the central dir on this disk.
	unsigned short	TotalEntries;		// Total number of entries in the central dir.
	unsigned long	CentralSize;
	unsigned long	CentralOffset;		// Offset of start of central directory with respect to the starting disk number.
	unsigned short	ZipCommentLen;
};
// And the comment itself.
#pragma option -a.

struct MDZipData {                  // MyDirZipData
	unsigned short	DiskStart;			// The number of the disk on which this file begins.
	unsigned long	RelOffLocal;		// This is the offset from the start of the first disk on.
	unsigned short FileNameLen;
	char          *FileName;			// The name of the file we have handled correctly.
	unsigned long	CRC32;				// Used in the unzip code.
	unsigned long	ComprSize;
	unsigned long	UnComprSize;
	unsigned long	DateTime;
};

// Definition for if the datadescriptor record is present.
#define DescUsed( DirRec ) (DirRec.Flag & 0x0008)

}	/* namespace DiskSpan */
#if !defined( NO_IMPLICIT_NAMESPACE_USE )
	using namespace DiskSpan;
#endif



//---------------------------------------------------------------------------
namespace ZipBuilder {

const long LocalFileHeaderSig   = 0x04034B50; // 'PK34 (in file: 504B0304)'
const long CentralFileHeaderSig = 0x02014B50; // 'PK12'
const long EndCentralDirSig     = 0x06054B50; // 'PK56'
const long ExtLocalSig			  = 0x08074B50; // 'PK78'
const int  LocalDirEntrySize    = 42;         // Fixed size of zip dir entry in local zip directory.
const int  BufSize				  = 8192;		 // Keep under 12K to avoid Winsock problems on Win95.
															 // If chunks are too large, the Winsock stack can
															 // lose bytes being sent or received.

/* From DLL version 151 and up we `use a new ZipDLL parameter structure
 *  and from DLL version 152 and up we use a new UnzZipDLL parameter structure.
 *  These changes were needed to pass extended information to the DLL's.
 *  The DLL's and ZipBuilder can still handle the old parameter structure if neccessary.
 *  This implies we can have the following situations:
 *  Component >=151 and DLL >= 151 New structure will be used and in all other cases
 *  the old structure will be used. */
const short int ZIPVERSION = 160;
const short int UNZIPVERSION = 160;


typedef long __stdcall (*GetSHFormatAddress)( HWND hwnd, long drive, long Fid, long Opt );
// 150199
typedef BOOL __stdcall (*GDiskFreeSpaceEx)( char *RootName, __int64 *FreeForCaller, __int64 *TotNoOfBytes, __int64 *TotNoOfFreeBytes );

#pragma option -a1
struct ZipDirEntry {		// Data from the local header
	unsigned char	MadeByVersion;
	unsigned char	HostVersionNo;
	Word				Version;
	Word				Flag;
	Word				CompressionMethod;
	long				DateTime;
	long				CRC32;
	long				CompressedSize;
	long				UncompressedSize;
	Word				FileNameLength;
	Word				ExtraFieldLength;
	unsigned short	FileCommentLen;
	unsigned short	StartOnDisk;
	unsigned short	IntFileAttrib;
	unsigned long	ExtFileAttrib;
	unsigned long	RelOffLocalHdr;
	String			FileName;
	String			FileComment;
	bool				Encrypted;			// New v1.6
	unsigned char *ExtraData;			// New v1.6, used in CopyZippedFiles()
};
#pragma option -a.

struct ZipRenameRec {
	String			Source;
	String			Dest;
	unsigned long	DateTime;
};

enum ProgressType { NewFile, ProgressUpdate, EndOfBatch, TotalFiles2Process, TotalSize2Process };
enum AddOptsEnum  { AddDirNames, AddRecurseDirs,  AddMove,        AddFreshen,      AddUpdate,
						  AddZipTime,  AddForceDOS,     AddHiddenFiles, AddArchiveOnly,  AddResetArchive,
						  AddEncrypt,  AddSeparateDirs, AddDiskSpan,    AddDiskSpanErase };
typedef Set<AddOptsEnum, AddDirNames, AddDiskSpanErase>  AddOpts;

// When changing this enum also change the pointer array in the function AddSuffix,
// and the initialisation of ZipBuilder. Also keep assGIF as first and assEXE as last value.
enum AddStoreSuffix{ assGIF = 0, assPNG, assZ, assZIP, assZOO, assARC, assLZH, assARJ, assTAZ, assTGZ, assLHA, assEXE };
typedef Set< AddStoreSuffix, assGIF, assEXE> AddStoreExts;

enum ExtrOptsEnum { ExtrDirNames, ExtrOverWrite, ExtrFreshen, ExtrUpdate, ExtrTest };
typedef Set<ExtrOptsEnum, ExtrDirNames, ExtrTest>  ExtrOpts;

enum OvrOpts      { OvrConfirm, OvrAlways, OvrNever };

enum SFXOptsEnum  { SFXAskCmdLine, SFXAskFiles, SFXAutoRun, SFXHideOverWriteBox,
						  SFXCheckSize, SFXNoSuccessMsg };
typedef Set<SFXOptsEnum, SFXAskCmdLine, SFXNoSuccessMsg> SfxOpts;

enum CPOpts            { cpAUTO, cpNone, cpOEM };
enum CodePageDirection { cpdOEM2ISO, cpdISO2OEM };
enum DeleteOpts	     { htdFinal, htdAllowUndo };

enum UnZipSkipTypes	{ stOnFreshen, stNoOverwrite, stFileExists, stBadPassword, stNoEncryptionDLL,
							  stCompressionUnknown, stUnknownZipHost, stZipFileFormatWrong, stGeneralExtractError };

typedef void __fastcall (__closure *TProgressEvent)( System::TObject *Sender, ProgressType ProgrType, String FileName, long FileSize );
typedef void __fastcall (__closure *TMsgEvent)( System::TObject *Sender, int ErrCode, String Message );
typedef void __fastcall (__closure *TSetNewNameEvent)( System::TObject *Sender, String &OldFileName, bool &IsChanged );
// New v1.6
typedef void __fastcall (__closure *TNewNameEvent)( System::TObject *Sender, int SeqNo, ZipDirEntry &ZipEntry );
typedef void __fastcall (__closure *TPasswordErrorEvent)( System::TObject *Sender, String &NewPassword, String ForFile, unsigned &RepeatCount );
typedef void __fastcall (__closure *TCRC32ErrorEvent)( System::TObject *Sender, String ForFile, unsigned FoundCRC, unsigned ExpectedCRC, bool &DoExtract );
typedef void __fastcall (__closure *TExtractOverwriteEvent)( System::TObject *Sender, String ForFile, bool IsOlder, bool &DoOverwrite );
typedef void __fastcall (__closure *TExtractSkippedEvent)( System::TObject *Sender, String ForFile, UnZipSkipTypes SkipType, int ExtError );
typedef void __fastcall (__closure *TCopyZipOverwriteEvent)( System::TObject *Sender, String ForFile, bool &DoOverwrite );

class PACKAGE TPasswordDlg : public TForm {
	private:
		TBitBtn	*OkBtn;
		TBitBtn	*CancelBtn;
		TEdit		*PwdEdit;
		TLabel	*PwdTxt;

	protected:
		virtual void __fastcall PwdOkClick( TObject *Sender );

	public:
		__fastcall TPasswordDlg( TComponent *Owner, int Dummy );
		__fastcall virtual ~TPasswordDlg( void );
		// And just to keep BCB1 happy...
		__fastcall virtual TPasswordDlg( TComponent *Owner ) : TForm( Owner ) { }

		bool OkClicked;

		virtual String __fastcall ShowModalPwdDlg( String Caption, String MsgTxt );
};

class PACKAGE EZipBuilder : public Sysutils::Exception {
	public:
		bool FDisplayMsg;	// We do not always want to see a message after an exception.
		int  FResIdent;	// We also save the Resource ID in case ZipMsg is not linked in the application.

		// Exception.Create
		__fastcall EZipBuilder( const int Ident, bool Display = true );
		__fastcall EZipBuilder( const int Ident, const int DiskNo );
		__fastcall EZipBuilder( const int Ident, const String Drive );
		__fastcall EZipBuilder( const int Ident, const String File1, const String File2 );

		// TObject.Destroy
     inline __fastcall virtual ~EZipBuilder( void ) { }
};

class PACKAGE TZipStream : public TMemoryStream {
	friend class TZipBuilder;

	protected:
		__fastcall virtual ~TZipStream( void ) { }
		__fastcall virtual TZipStream( void ) {
			Clear();
		}
	public:
		void __fastcall virtual SetPointer( void *Ptr, int Size );
};

//----------------Icon resource info--------------------------------------------
#pragma option -a1
struct PEheader {		// Data from the local header
	DWord                 signature;
	IMAGE_FILE_HEADER     _head;
	IMAGE_OPTIONAL_HEADER opt_head;
	IMAGE_SECTION_HEADER  section_header;
};
#pragma option -a.

typedef IMAGE_RESOURCE_DIR_STRING_U          *pIRDSU;
typedef const IMAGE_RESOURCE_DIRECTORY_ENTRY *pIRDirE;
typedef const IMAGE_DATA_DIRECTORY           *pIDD;
typedef const IMAGE_RESOURCE_DIRECTORY       *pIRD;
typedef IMAGE_RESOURCE_DATA_ENTRY            *pIRDatE;
typedef IMAGE_SECTION_HEADER                 *pISH;
//------------------------------------------------------------------------

class PACKAGE TZipBuilder : public Classes::TComponent {
	friend class TSHFormatThread;

	private:
		bool							FVerbose;
		bool							FCancel;
		bool							FTrace;
		bool  						FZipBusy;
		bool							FUnzBusy;
		bool							FEncrypt;
		HWND							FHandle;				// set to 0 if you don't need DLL-generated dialog msgs
		int   						FErrCode;
		int  							FSuccessCnt;
		int							FAddCompLevel;
		int							FSFXOffset;
		AddOpts						FAddOptions;
		ExtrOpts						FExtrOptions;
		SfxOpts						FSFXOptions;
		String 						FMessage;
		String						FPassword;
		String						FSFXPath;
		Classes::TList			  *FZipContents;
		String						FExtrBaseDir;
		Classes::TStrings		  *FFSpecArgs;
		String						FZipFileName;
		union {
			ZipDLL::ZipParms1	  *ZipParms1;
			ZipDLL::ZipParms2	  *ZipParms2;
		};
      union {
			UnzipDLL::UnZipParms1 *UnZipParms1;
			UnzipDLL::UnZipParms2 *UnZipParms2;
		};
		String						FDLLDirectory;
		OvrOpts						FSFXOverWriteMode;	// OvrConfirm  (others: OvrAlways, OvrNever)
      String						FSFXCaption;			// dflt = "Self-extracting Archive"
		String						FSFXDefaultDir;		// dflt = ""
		String						FSFXCommandLine;		// dflt = ""
		String						FTempDir;
		String						FZipComment;
		bool							FUnattended;
		bool							FConfirmErase;
		long							FMinFreeVolSize;
		unsigned long				FZipSOC;
		unsigned long				FZipEOC;
		CPOpts						FCodePage;
		DeleteOpts					FHowToDelete;
		long							FFileSize;
		long							FRealFileSize;
		__int64						FMaxVolumeSize;	// RCV150199
		__int64						FSizeOfDisk;		// RCV150199
		__int64						FFreeOnDisk1;		// RCV150199
		__int64						FFreeOnDisk;		// RCV150199
		String						FInFileName;
		String						FOutFileName;
		String						FDrive;
		String						FVolumeName;
		int							FInFileHandle;
		int							FOutFileHandle;
		int							FDiskNr;
		int							FDiskWritten;
		int							FDateStamp;
		unsigned short				FTotalDisks;
		unsigned long				FDiskSerial;
		bool							FNewDisk;
		bool							FShowProgress;
		bool							FWrongZipStruct;
		bool							FIsSpanned;
		unsigned long				FTotalSizeToProcess;
		int							FFullErrCode;
		unsigned char				FHostNum;
		unsigned char				FHostVer;
		HWND							Fhwnd;
		int							FFound;
		bool							FBeginFormat;
		long							FFormatResult;
		int							FDriveNr;
		String						FVersionInfo;	//v1.52L
		// New v1.6
		unsigned int				FPasswordReqCount;
		bool							GAssignPassword;
		String						FSFXMessage;
		TIcon						  *FSFXIcon;
		AddStoreExts				FAddStoreSuffixes;
		Classes::TStrings		  *FFSpecArgsExcl;
		class TZipStream		  *FZipStream;
		bool							FUseDirOnlyEntries;

		class TSHFormatThread *Fft;

		// Event variables
		Classes::TNotifyEvent	FOnDirUpdate;
		TProgressEvent				FOnProgress;
		TMsgEvent					FOnMessage;
		// New v1.6
		TSetNewNameEvent			FOnSetNewName;
		TNewNameEvent				FOnNewName;
		TPasswordErrorEvent		FOnPasswordError;
		TCRC32ErrorEvent			FOnCRC32Error;
		TExtractOverwriteEvent	FOnExtractOverwrite;
		TExtractSkippedEvent		FOnExtractSkipped;
		TCopyZipOverwriteEvent	FOnCopyZipOverwrite;

		// Property get/set functions
		int    __fastcall GetCount( void );
		int    __fastcall GetZipVers( void );
		int    __fastcall GetUnzVers( void );
		String __fastcall GetZipComment( void );
		void	 __fastcall SetZipComment( String Value );
		void   __fastcall SetFSpecArgs( Classes::TStrings *Value );
		void   __fastcall SetFileName( String Value );
		void   __fastcall SetDLLDirectory( String Value );
		void   __fastcall SetMaxVolumeSize( long Value );
		long   __fastcall GetMaxVolumeSize( void );
		void   __fastcall SetFreeOnDisk1( long Value );
		long   __fastcall GetFreeOnDisk1( void );
		void   __fastcall SetMinFreeVolSize( long Value );
		void   __fastcall SetSFXIcon( TIcon *aIcon );
		void   __fastcall SetPasswordReqCount( unsigned int Value );
		void   __fastcall SetFSpecArgsExcl( Classes::TStrings *Value );
		void	 __fastcall SetVersionInfo( String Value );

		// Private "helper" functions
		void   __fastcall FreeZipDirEntryRecords( void );
		void   __fastcall SetZipSwitches( String &NameOfZipFile, int zpVersion );
		void   __fastcall SetUnZipSwitches( String &NameOfZipFile, int UzpVersion );
		int    __fastcall CopyBuffer( int &InFile, int &OutFile, int ReadLen );
		String __fastcall ReplaceForwardSlash( char *aStr );
		int    __fastcall ConvertSFX( bool AutoExeViaAdd );
		void   __fastcall ConvertOem2Iso( char *Source, CodePageDirection Direction );
		struct MDZipData ** __fastcall AllocSpanMem( int TotalEntries );
		void   __fastcall DeleteSpanMem( struct MDZipData **MDZD, int TotalEntries );
		int    __fastcall FindZipEntry( int Entries, struct MDZipData **MDZD, int HFileLen, char *HFilename );
		void   __fastcall WriteSplit( const void *Buffer, int Len, int MinSize );
		void   __fastcall WriteJoin( void *Buffer, int BufSize, int DSErrIdent );
		void   __fastcall RWSplitData( char *Buffer, int ReadLen, int DSErrIdent );
		void   __fastcall RWJoinData( char *Buffer, int ReadLen, int DSErrIdent );
		bool   __fastcall IsDiskPresent( void );
		void   __fastcall GetNewDisk( int DiskSeq );
		bool   __fastcall CheckIfLastDisk( struct ZipEndOfCentral &EOC, bool DoExcept );
		bool   __fastcall IsRightDisk( unsigned int drt );
		unsigned int __fastcall CheckForDisk( void );
		String __fastcall LoadZipStr( const int Ident, const String DefaultStr = "" );
		void   __fastcall ShowExceptionError( const EZipBuilder &ZBExcept );
		int    __fastcall RWCentralDir( int &OutFile, struct ZipEndOfCentral &EOC, int OffsetChange );
		int  __fastcall ZipFormat( void );
		static bool __stdcall EnumThreadWndProc( HWND winh, TZipBuilder *mythis );
		void   __fastcall DiskFreeAndSize( int Action );   // RCV150199
		// New v1.60
		DWord  __fastcall SearchResDirEntry( pIRD ResStart, pIRDirE entry, int Depth );
		DWord  __fastcall BrowseResDir( pIRD ResStart, pIRD dir, int Depth );
		DWord  __fastcall LookForDirs( const void *SectionData, const DWord SectionVirtualStart,
															const int SectionLen, pIDD directories );
		int    __fastcall ReplaceIcon( int SFXFile, int SFXSize );
		void   __fastcall AddSuffix( const AddStoreSuffix SufOption, String &sStr, int sPos );
		void   __fastcall ExtExtract( bool UseStream );

	public:
		__fastcall TZipBuilder( Classes::TComponent *AOwner );
		__fastcall virtual ~TZipBuilder( void );

		__property HWND            Handle             = {read=FHandle, write=FHandle, nodefault};
		__property int             ErrCode            = {read=FErrCode,        nodefault};
		__property int					FullErrCode			 = {read=FFullErrCode,	  nodefault};
		__property int             Count              = {read=GetCount,        nodefault};
		__property int             SuccessCnt         = {read=FSuccessCnt,     nodefault};
		__property int             ZipVers            = {read=GetZipVers,      nodefault};
		__property int             UnzVers            = {read=GetUnzVers,      nodefault};
		__property unsigned long   TotalSizeToProcess = {read=FTotalSizeToProcess,    nodefault};
		__property bool            Cancel             = {read=FCancel, write=FCancel, nodefault};
		__property bool            ZipBusy            = {read=FZipBusy,        nodefault};
		__property bool            UnzBusy            = {read=FUnzBusy,        nodefault};
		__property bool				IsSpanned			 = {read=FIsSpanned,		  default=false};
		__property String          Message            = {read=FMessage,	     nodefault};
		__property String          ZipComment         = {read=GetZipComment,   write=SetZipComment, nodefault}; // Changed v1.6
		__property Classes::TList *ZipContents        = {read=FZipContents,    nodefault};
		__property long				ZipFileSize			 = {read=FRealFileSize,	  default=0};
		__property int					SFXOffset			 = {read=FSFXOffset,		  default=0};
		__property unsigned long	ZipSOC				 = {read=FZipSOC,			  default=0};
		__property unsigned long	ZipEOC				 = {read=FZipEOC,			  default=0};
		// Just to be compatible with older versions (notice the small 'n').
		__property String			   ZipFilename			 = {read=FZipFileName,	  write=SetFileName,   nodefault};
		// New v1.6
		__property TZipStream	  *ZipStream			 = {read=FZipStream,		  nodefault};

		static unsigned long __stdcall ZCallback( CallBack::PZCallBackStruct cbr );

		void   __fastcall Add( void );
		void   __fastcall Delete( void );
		void   __fastcall Extract( void );
		void   __fastcall List( void );
		void   __fastcall Load_Zip_Dll( void );
		void   __fastcall Load_Unz_Dll( void );
		void   __fastcall Unload_Zip_Dll( void );
		void   __fastcall Unload_Unz_Dll( void );
		int    __fastcall CopyFile( const String src, const String dest );
		int    __fastcall EraseFile( const String Fname, DeleteOpts How );

		int    __fastcall ConvertSFX( void );
		int    __fastcall ConvertZIP( void );
		String __fastcall GetAddPassword( void );
		String __fastcall GetExtrPassword( void );
		String __fastcall AppendSlash( String sDir );
		void   __fastcall ShowZipMessage( const int Ident, const String UserStr = "" );
		int    __fastcall WriteSpan( const String InFileName, const String OutFileName );
		int    __fastcall ReadSpan( const String InFileName, String &OutFilePath );
      // New v1.60
		int    __fastcall Rename( TList &RenameList, unsigned long DateTime );
		TZipStream * __fastcall ExtractFileToStream( String Filename );
		bool __fastcall GetPassword( String DialogCaption, String MsgTxt, String &ResultStr );
		int  __fastcall CopyZippedFiles( TZipBuilder *DestZipBuilder, bool DeleteFromSource, OvrOpts OverwriteDest );

	__published:
		__property bool Verbose         = {read=FVerbose,      write=FVerbose,      nodefault};
		__property bool Trace           = {read=FTrace,        write=FTrace,        nodefault};
		__property int AddCompLevel     = {read=FAddCompLevel, write=FAddCompLevel, default=9};
		__property AddOpts  AddOptions  = {read=FAddOptions,   write=FAddOptions,   nodefault};
		__property ExtrOpts ExtrOptions = {read=FExtrOptions,  write=FExtrOptions,  nodefault};
		__property SfxOpts  SFXOptions  = {read=FSFXOptions,   write=FSFXOptions,   default=SFXCheckSize};
		__property String   ExtrBaseDir = {read=FExtrBaseDir,  write=FExtrBaseDir,  nodefault};
		__property Classes::TStrings    *FSpecArgs   = {read=FFSpecArgs,   write=SetFSpecArgs, nodefault};
		__property String   ZipFileName = {read=FZipFileName,  write=SetFileName,   nodefault};
		__property String	  Password	  = {read=FPassword,	    write=FPassword,		 nodefault};
		__property String	  SFXPath	  = {read=FSFXPath,		 write=FSFXPath,		 nodefault};
		__property String	  DLLDirectory  = {read=FDLLDirectory,	write=SetDLLDirectory, nodefault};
		__property OvrOpts  SFXOverWriteMode  = {read=FSFXOverWriteMode,    write=FSFXOverWriteMode, default=OvrConfirm};
		__property String	  SFXCaption	 = {read=FSFXCaption,      write=FSFXCaption,     nodefault};
		__property String	  SFXDefaultDir = {read=FSFXDefaultDir,	write=FSFXDefaultDir,  nodefault};
		__property String	  SFXCommandLine= {read=FSFXCommandLine,	write=FSFXCommandLine, nodefault};
		__property String   SFXMessage    = {read=FSFXMessage,      write=FSFXMessage,     nodefault};	// New v1.6
		__property String	  TempDir		 = {read=FTempDir,		   write=FTempDir,		  nodefault};
		__property long KeepFreeOnDisk1   = {read=GetFreeOnDisk1,   write=SetFreeOnDisk1,   default=0};
		__property long MaxVolumeSize     = {read=GetMaxVolumeSize, write=SetMaxVolumeSize, default=0};
		__property long MinFreeVolumeSize = {read=FMinFreeVolSize,write=SetMinFreeVolSize,default=65536};
		__property bool ConfirmErase      = {read=FConfirmErase,  write=FConfirmErase,    default=true};
		__property bool Unattended        = {read=FUnattended,    write=FUnattended,      default=false};
		__property CPOpts CodePage        = {read=FCodePage,      write=FCodePage,        default=cpAUTO};
		__property DeleteOpts HowToDelete = {read=FHowToDelete,   write=FHowToDelete,     default=htdAllowUndo};
		__property String VersionInfo		 = {read=FVersionInfo,   write=SetVersionInfo };	//v1.52L
		// New v1.6
		__property TIcon   *SFXIcon       = {read=FSFXIcon,       write=SetSFXIcon,        nodefault};
		__property AddStoreExts AddStoreSuffixes = {read=FAddStoreSuffixes, write=FAddStoreSuffixes,   nodefault};
		__property unsigned int PasswordReqCount = {read=FPasswordReqCount, write=SetPasswordReqCount, default=1};
		__property Classes::TStrings    *FSpecArgsExcl   = {read=FFSpecArgsExcl,    write=SetFSpecArgsExcl, nodefault};
		__property bool UseDirOnlyEntries = {read=FUseDirOnlyEntries, write = FUseDirOnlyEntries, default=false };

		__property TProgressEvent			 OnProgress			  = { read=FOnProgress,			  write=FOnProgress			 };
		__property TMsgEvent					 OnMessage			  = { read=FOnMessage,			  write=FOnMessage			 };
		__property Classes::TNotifyEvent	 OnDirUpdate		  = { read=FOnDirUpdate,		  write=FOnDirUpdate			 };
		// New v1.6
		__property TSetNewNameEvent		 OnSetNewName		  = { read=FOnSetNewName,		  write=FOnSetNewName		 };
		__property TNewNameEvent			 OnNewName			  = { read=FOnNewName,			  write=FOnNewName			 };
		__property TPasswordErrorEvent	 OnPasswordError	  = { read=FOnPasswordError,	  write=FOnPasswordError	 };
		__property TCRC32ErrorEvent		 OnCRC32Error		  = { read=FOnCRC32Error,		  write=FOnCRC32Error		 };
		__property TExtractOverwriteEvent OnExtractOverwrite = { read=FOnExtractOverwrite, write=FOnExtractOverwrite };
		__property TExtractSkippedEvent	 OnExtractSkipped	  = { read=FOnExtractSkipped,	  write=FOnExtractSkipped	 };
		__property TCopyZipOverwriteEvent OnCopyZipOverwrite = { read=FOnCopyZipOverwrite, write=FOnCopyZipOverwrite };
};

#if __BORLANDC__ < 1344		// BCB4=0x540(1344)
 //-- template instantiations -------------------------------------------------
 template class ExtrOpts;
 template class AddOpts;
 template class SfxOpts;
 template class AddStoreExts;
#endif
}	/* EOF namespace ZipBuilder */

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
	using namespace ZipBuilder;
#endif


/* TZipBuilder component v1.60k by Chris Vleghert cvleghrt@WorldOnline.nl a
	C++ Builder 1, 3 and 4.0 wrapper for the freeware ZIP and UNZIP DLL's
	from Chris Vleghert and Eric W. Engler.
	v1.60k  May 21, 1999

	THIS IS A BETA RELEASE! DO NOT USE THIS SOFTWARE EXCEPT IN TESTING!

	Changes:
	-Added Encrypted boolean to ZipDirEntry structure. (part of ZipContents)
	 (Also added info to the help text regarding the value of 'Flag'
	-Writing of zipfile comments is now possible.
	 (ZipDll changed also, now v1.60)
	-Added Renaming of one or more zip entries in a zip archive.
	 (also with the possibility to change the datetime field)
	 (progress events are supported)
	-Changed ConvertSFX to support the new MPV header.
	 (The old ZipSFX.bin is no longer supported!!!)
	-Changed ConvertZIP to support the new MPV header.
	 (old header can still be read)
	-New SFX option: SFXNoSuccessMsg, bypasses the final message when extracting is done.
	-New SFX property: SFXMessage, a startup message before the SFX dialog is shown.
	-New SFX property: SFXIcon, the icon that is shown as executable image.
	-SFXCaption, SFXCommandLine, SFXDefaultDir and all other options are
	 read back when converting from sfx to zip.
	-Changed Demo1 SfxUnit.
	-Added a rename unit to Demo1.
	-The Zip Dll is now reentrant; multiple threads can use it at the same time
	 (This requires multiple ZipBuilder components.)
	-New property: AddStoreSuffixes Files with one of these extensions will be stored
	 in the zip archive others will be deflated.
	 default: assGIF+assPNG+assZ+assZIP+assZOO+assARC+assLZH+assARJ+assTAZ+assTGZ+assLHA
	-New AddOptions: AddArchiveOnly and AddResetArchive, used to handle the archive bit of a file.
	-Added a new event: OnSetNewName, While adding to a archive the path/name can be changed.
	-Added ExtractFileToStream function, Extract to a Memory stream without making an intermediate file.
	 ( Now position in the stream is reset.)
	-Fixed Auto SFX Create via Add, went wrong when SFXConvert returned an error.
	-Fixed ZipDll.dll Add with Update did not work on an empty zip archive.
	-Fixed a bug in ConvertSFX while working with sfxblksize.
	-Changed the writing of the zip archive comment, now also without using the zip dll.
	-Added a new Event OnNewName this will be called when reading the Zip's directory
	 and gives you the opportunity to fill for example a ListView. In previous versions
	 you had to wait for the OnDirUpdate event, which is still supported.
	-Added new property PasswordReqCount, used to set the number of times a password will be
	 requested through the OnPasswordError event.
	-Added a new Event OnPasswordError, this will be called when the given Password is wrong or
	 not given at all.
	 The UnZip dll itself will not ask for a password anymore when the components version
	 number >= 1.6!!!
	-Added a new public method GetPassword which replaces the InputBox function used earlier.
	 Uses now language dependent Resource text as output and while typing the password, a '*'
	 will be shown.
	-Checked for and fixed a few memory leaks in the dll's and component.
	-Added the new event OnCRC32Error. On a CRC error it is now possible to skip the extraction of
	 that file
	-Added the new property FSpecArgsExcl, used to specify file arguments which should be excluded
	 (i.e. not zipped) during a zip operation. (like *.tmp)
	-Added the new event OnExtractOverwrite, is complementary to the Extract Option ExtrOverwrite.
	-Added the new event OnExtractSkipped, called when a file is skipped during extraction with the
	 reason why it is skipped.
	-Added property UseDirOnlyEntries bool, Do not include Directory only entries from the zip contents
	 list. (See also AddOption AddSeparateDirs ) Default false;
	-Added function CopyZippedFiles, to copy files from one archive into another without re-zipping.
	-Added new event OnCopyZipOverwrite used in the function CopyZippedFiles().
	-Added unsigned char *ExtraData member (from the central header) to the ZipDirEntry structure.
	-EraseFile() now prepends the full path from the current drive/dir if filename did not have one.
	 (FOF_ALLOWUNDO does not seem to work when there is no full path!?)


	To change:
	-Translation of the new Resource Messages.
	-Stream support to a file and memory streams in/out.
	-Direct zip of UNC file names (Change in ZipDLL)
	-Remove the Exclamation-Mark necessity in the Filename for SFXAutorun when the name is Setup.exe
	-An new event used while diskspanning when a new disk is needed.

	And ideas for changing/adding in version 1.7:
	-Warning/skipping a file when it is opened by an other application for writing while adding.
	 new event OnAddInUse.
	-Writing of file comments in the archive (new event OnFileComment).
	-A more direct support for relative paths. (new property RootDir)
	-Zip repair, switching between local and central dir
	-UNC support everywhere.
	-SFX diskspan reading.
	-SFX codepage support? Ansi compare functions? Portuguese change?
	-SFX extract path from registry or temp dir change into user defined if regkey is missing.
	-Multi select with CTRL, SHIFT in the SortGrid.
	-A new event for some errors/warnings in the zipdll like:
		name in zip file repeated: : INSTALL.TXT
		first full name: C:\TestMap1\TestMap2\INSTALL.TXT
		second full name: C:\TestMap1\INSTALL.TXT
		bad zip options specified

	Changes in v1.52l:
		-Fixed a bug in the ZipDll that prevented the use of the Add option AddForceDOS.
		-Fixed a bug in the ZipDll that prevented the use of the Add option AddZipTime.
		-Fixed a bug in the ZipDll that gave a Fatal Dll error when using delete or Add-Freshen
		 with wildcard(s).
		-Fixed a bug in the SFX source code, re-compilation always resulted in the message
		 Error reading Archive File. Found thanks to Patrick Gentemann.
		-Added a new Read Only property VersionInfo.
		-Fixed the message: 'Error reading ZipBuilder1->AddStoresSuffixes: Property does not exist.'
		 when opening the demo projects.
		-Fixed the AddFile->CreateOrder property not being supported (in BCB < 4).
		-Moved the assignment of the FErrCode and FMessage one line up in the function ShowExceptionError
		 This way the property ErrCode can be used inside the OnMessage event handling. (The parameter
		 ErrCode in this event is sometimes 0 while ErrCode is not.)

	Changes in v1.52k:
		-Changed most StrPCopy functions to StrPLCopy because of a bug in BCB1, Delphi2 and
		 Delphi3 in these environments max. 255 characters are copied, reported by Tim Borman.
		-Added a line to WriteSpan to correctly read and write an existing archive comment.
		 Found by Tim Borman.
		-Added some catch statements to functions which could give an unknown error as result,
		 now extended to give the exception message in case the exception originated from a
		 VCL Exception class.

	Changes in v1.52j:
		-BCB4: New typedef for use in FileSeek functions (Ambiguity int, __int64)
		-BCB4: Some template classes not wanted anymore.
		-BCB4: Unnamed unions are now possible (and used) and so the union member names from
		 IMAGE_RESOURCE_DATA_ENTRY had to be removed.
		-Bug fix in List, ReadSpan to read to correct data when a disk change was neccessary.
		 This prevented to open and read a spanned archive which had it's header data split
		 across multiple disk(files). Found thanks to Alexander Hofmann.
		-Moved FreeLibrary which wasn't always called in DiskFreeAndSize.
		-Added a SetErrorMode because it wasn't always reset in IsDiskPresent.
		-Changed the function DirExists a little in case the given dir was an empty string.
      -Added some properties to the SortGrid VC and as result removed some code from the demos.
      -A new #define UNZIPVERSION 160, now Zip and Unzip dll may have different version numbers.
		-Added the new resource message: DS_CopyCentral "Central directory" used in WriteSpan.
		-Bug fix CheckForDisk, Division by zero error could occur under certain circumstances.
		 Found thanks to J.A. Bijsterbosch

	Bug Fix in v1.52i:
		-In the function WriteSplit a statement was missing that incremented the disk to use.
		 This was most likely to happen when zipping to a large spanned archive, but also smaller
		 archives could suffer from this problem.
		 thanks to Jim Hoops, Alexander Hofmann.

	Bug Fix in v1.52h:
		-Fixed a memory leak in CheckIfLastDisk thanks to Greg Lorriman.

	Version g Added Russian language support.

	Bug Fix and change in v1.52f:
		-Some throw's did not have EZipBuilder as exception class.
		-Better support for harddisks > 2Gb and UNC names.
		 (Replacement function for DiskFree and DiskSize functions this also
		 prevented opening files given with an UNC name.)

	Bug in archive distribution (v.152e):
		-vcl directory did not contain ZipMsg.h

   Bug Fix in v1.52d:
		-Reading of spanned disks written by WinZip did not work.

   Bug Fixes in v1.52c:
		-The messages DS_NotaDrive and DS_DriveNoMount expects a string as
		 parameter but did in fact get an Integer and as result you would get
		 a message: UnKnown error in function ReadSpan() or WriteSpan()
		 Now there is an new exception constructor for these messages.
		 Found by Tim Borman
		-When there was no disk in the drive no question was asked to put
		 one in, instead an exception was raised an the spanning was aborted.
		 Found by Tim Borman
		-If the size of the disk is not yet known there was still a question
		 to put disk X of Y in the drive. Now this is changed in just Disk X.
		 Not really a bug but annoying, Found by Tim Borman
		-The copy stage of the diskspan process is now a little faster.
		 Thanks to Tim Borman
		-Fixed a bug in the zip dll while handling slashes, this sometimes
       lead to a Fatal Error in ZipDLL.DLL: abort exception.
       Thanks to Sebastian Hildebrandt and Matthew Kent.

	Bug fixes v1.52b:
		-Changed the search direction for the EOC structure.
		 (If there was a zip file stored in a ziparchive within the last 64K
		  the wrong archive directory was shown.)
	   -Diskspanning with formatting with ConfirmErase = True did not work.

	Bug fix v1.52a:
		-Changed ReplaceForwardSlash() in returning a new string in stead of changing
		 the old one this because of a 'local header not found in internal structure'
		 error in WriteSpan() and ReadSpan().
*/
#endif

