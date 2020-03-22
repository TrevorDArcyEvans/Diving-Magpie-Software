#ifndef mainH
#define mainH

//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Classes.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Grids.hpp>
#include <vcl\Buttons.hpp>
#include <Menus.hpp>

#include "SortGrid.hpp"

#include "ZIPBuilder.h"

#include "Message.h"
#include "ExtractFiles.h"
#include "AddFiles.h"
#include "SFX.h"
#include "Rename.h"

class TMainForm : public TForm {
	__published:	// IDE-managed Components
		TBevel			*Bevel2;
		TBevel			*Bevel1;
		TButton			*CloseBut;
		TButton			*DeleteZipBut;
		TButton			*NewZipBut;
		TButton			*ZipOpenBut;
		TButton			*MsgBut;
		TButton			*ConvertBut;
		TButton			*DeleteBut;
		TButton			*AddBut;
		TButton			*ExtractBut;
		TButton			*TestBut;
		TCheckBox		*VerboseCB;
		TCheckBox		*TraceCB;
		TCheckBox		*UnattendedCB;
		TLabel			*FilesLabel;
		TLabel			*ZipFName;
		TLabel			*Label1;
		TLabel			*Label2;
		TLabel			*TimeLabel;
		TLabel			*Label4;
		TPanel			*Panel2;
		TPanel			*Panel4;
		TPanel			*Panel3;
		TPanel			*Panel1;
		TSortGrid		*StringGrid1;
		TOpenDialog		*OpenDialog1;
		TImageList		*ImageList1;
		TMainMenu		*MainMenu1;
		TMenuItem		*Project1;
		TMenuItem		*Showlasterror1;
		TMenuItem		*File1;
		TMenuItem		*Exit1;
		TMenuItem		*Zipcomment1;
		TMenuItem		*DLLversioninfo1;
		TZipBuilder 	*ZipBuilder1;

	TButton *RenBut;
		void __fastcall CloseButClick( TObject *Sender );
		void __fastcall ZipOpenButClick( TObject *Sender );
		void __fastcall NewZipButClick( TObject *Sender );
		void __fastcall DeleteZipButClick( TObject *Sender );
		void __fastcall ExtractButClick( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );
		void __fastcall AddButClick( TObject *Sender );
		void __fastcall ZipBuilder1DirUpdate( TObject *Sender );
		void __fastcall ZipBuilder1Message( TObject *Sender, int ErrCode, String Message );
		void __fastcall ZipBuilder1Progress( TObject *Sender, ProgressType ProgrType, String Filename, long FileSize );
		void __fastcall DeleteButClick( TObject *Sender );
		void __fastcall FormDestroy( TObject *Sender );
		void __fastcall TestButClick( TObject *Sender );
		void __fastcall MsgButClick( TObject *Sender );
		void __fastcall ConvertButClick(TObject *Sender );
		void __fastcall StringGrid1ClickSort( TObject *Sender, int Col, int Row, TSortOptions &SortOptions );
		void __fastcall StringGrid1DrawCell( TObject *Sender, int Col, int Row, TRect &Rect, TGridDrawState State );
		void __fastcall Showlasterror1Click( TObject *Sender );
		void __fastcall Exit1Click( TObject *Sender );
		void __fastcall UnattendedCBClick( TObject *Sender );
		void __fastcall StringGrid1GetCellFormat( TObject *Sender, int Col, int Row, TGridDrawState State, TFormatOptions &FormatOptions );
		void __fastcall Zipcomment1Click( TObject *Sender );
		void __fastcall DLLversioninfo1Click( TObject *Sender );
		void __fastcall FormResize( TObject *Sender );
		void __fastcall StringGrid1BeginSort( TObject *Sender, int Col, TSortOptions &SortOptions );
		void __fastcall StringGrid1EndSort( TObject *Sender, int Col );
		void __fastcall VerboseCBClick( TObject *Sender );
		void __fastcall TraceCBClick( TObject *Sender );

	void __fastcall RenButClick(TObject *Sender);
	public:		// User declarations
		bool					DoIt;
		long					GSortCol, s, f;
		unsigned __int64	TotUncomp, TotComp;
      TSortOptions GSortOptions;

		__fastcall TMainForm( TComponent *Owner ) :  TForm( Owner ) { }

		String ShowLTime( long s, long f );
		void __fastcall SetZipFName( String aCaption, bool AssignName );
		void __fastcall FillGrid( void );
		bool __fastcall AskDirDialog( const HWND FormHandle, String &DirPath );
		long __fastcall GetSpecialFolder( int aFolder, String &Location );
		void __fastcall SetZipTotals( void );
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TMainForm *MainForm;

extern String ExtractDir;

extern bool	ExpandDirs;
extern bool	OverWr;
extern bool	AllFiles;
extern bool	Canceled;

#endif

