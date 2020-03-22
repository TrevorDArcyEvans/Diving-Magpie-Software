#ifndef Unit1H
#define Unit1H

#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>

#include <stdio.h>

#include "ZIPBuilder.h"
#include "ZipBuilder.h"

//---------------------------------------------------------------------------
class TForm3 : public TForm {
	__published:	// IDE-managed Components
		TPanel		*Panel1;
		TPanel		*Panel2;
		TPanel		*Panel3;
		TButton		*Button2;
		TMemo			*Memo1;
		TButton		*AddBut;
		TButton		*ExtrBut;
		TButton		*ListBut;
		TButton		*DeleteBut;
		TButton		*TestBut;
		TButton		*VersBut;
		TButton		*AddPwdBut;
		TZipBuilder *ZipBuilder1;

		void __fastcall AddButClick( TObject *Sender );
		void __fastcall ZipBuilder1Message( TObject *Sender, int ErrCode, String Message );
		void __fastcall Button2Click( TObject *Sender );
		void __fastcall ExtrButClick( TObject *Sender );
		void __fastcall VersButClick( TObject *Sender );
		void __fastcall ListButClick( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );
		void __fastcall FormDestroy( TObject *Sender );
		void __fastcall TestButClick( TObject *Sender );
		void __fastcall DeleteButClick( TObject *Sender );
		void __fastcall AddPwdButClick( TObject *Sender );

	public:			// User declarations
		__fastcall TForm3( TComponent *Owner ) : TForm( Owner ) { }
};

//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
#endif
