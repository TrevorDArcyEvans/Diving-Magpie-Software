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
#include <shlobj.h>

#include "SortGrid.hpp"

#include "ZIPBuilder.h"

#include "Message.h"
#include "ExtractFiles.h"
#include "AddFiles.h"
#include <ImgList.hpp>

class TMainForm : public TForm {
	__published:	// IDE-managed Components
		TBevel			*Bevel1;
		TButton			*AddBut;
		TButton			*ExtractBut;
		TButton			*WriteBttn;
		TButton			*ReadBttn;
		TButton			*NewZipBut;
		TLabel			*ZipFName;
		TLabel			*Label1;
		TLabel			*Label2;
		TLabel			*Label4;
		TLabel			*Label5;
		TLabel			*Label6;
		TLabel			*FilesLabel;
		TPanel			*Panel2;
		TPanel			*Panel4;
		TPanel			*Panel3;
		TSortGrid		*StringGrid1;
		TOpenDialog		*OpenDialog1;
		TImageList		*ImageList1;
		TEdit				*MaxVolSizeEdit;
		TEdit				*FreeDisk1Edit;
		TEdit				*MinFreeVolEdit;
		TCheckBox		*FormatCB;
		TMainMenu		*MainMenu1;
		TMenuItem		*Project1;
		TMenuItem		*Showlasterror1;
		TMenuItem		*File1;
		TMenuItem		*Exit1;
		TMenuItem		*DLLversioninfo1;
		TMenuItem		*Messages1;
		TZipBuilder		*ZipBuilder1;

		void __fastcall NewZipButClick( TObject *Sender );
		void __fastcall ExtractButClick( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );
		void __fastcall AddButClick( TObject *Sender );
		void __fastcall ZipBuilder1DirUpdate( TObject *Sender );
		void __fastcall ZipBuilder1Message( TObject *Sender, int ErrCode, String Message );
		void __fastcall ZipBuilder1Progress( TObject *Sender, ProgressType ProgrType, String Filename, long FileSize );
		void __fastcall FormDestroy( TObject *Sender );
		void __fastcall Showlasterror1Click( TObject *Sender );
		void __fastcall Exit1Click( TObject *Sender );
		void __fastcall WriteBttnClick( TObject *Sender );
		void __fastcall ReadBttnClick( TObject *Sender );
		void __fastcall StringGrid1GetCellFormat( TObject *Sender, int Col, int Row, TGridDrawState State, TFormatOptions &FormatOptions );
		void __fastcall DLLversioninfo1Click( TObject *Sender );
		void __fastcall FormResize( TObject *Sender );
		void __fastcall StringGrid1EndSort( TObject *Sender, int Col );
		void __fastcall Messages1Click( TObject *Sender );
		void __fastcall MaxVolSizeEditChange( TObject *Sender );
		void __fastcall FreeDisk1EditChange( TObject *Sender );
		void __fastcall MinFreeVolEditChange( TObject *Sender );

	public:		// User declarations
		bool		DoIt;
		int		TotUncomp, TotComp;
		String	ZipOpenDir;
      
		__fastcall TMainForm( TComponent *Owner ) :  TForm( Owner ) { }

		void __fastcall SetZipFName( String aCaption );
		void __fastcall FillGrid( void );
		bool __fastcall AskDirDialog( const HWND FormHandle, String &DirPath );
		long __fastcall GetSpecialFolder( int aFolder, String &Location );
		void __fastcall SetZipTotals( void );
		bool __fastcall ZipOpenArchive( void );
		void __fastcall TMainForm::AddSpan( void );
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TMainForm *MainForm;

extern String ExtractDir;

extern bool	ExpandDirs;
extern bool	OverWr;
extern bool	AllFiles;
extern bool	Canceled;

#endif

