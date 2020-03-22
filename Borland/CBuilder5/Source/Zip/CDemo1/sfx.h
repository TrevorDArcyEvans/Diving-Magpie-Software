#ifndef Unit1H
#define Unit1H

//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>

#include <shlobj.h>

#include "Main.h"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>

//---------------------------------------------------------------------------
class TMakeSFX : public TForm {
	__published:	// IDE-managed Components
		TPanel			*Panel1;
		TPanel			*Panel2;
		TCheckBox		*CmdLineCB;
		TCheckBox		*FileListCB;
		TCheckBox		*HideOverWriteCB;
		TCheckBox		*AutoRunCB;
		TEdit				*CaptionEdit;
		TEdit				*MsgEdit;
		TEdit				*IconEdit;
		TEdit				*IconIndexEdit;
		TEdit				*CommandEdit;
		TImage			*Image1;
		TComboBox		*DirectoryEdit;
		TButton			*ExecBut;
		TButton			*CancelBut;
		TLabel			*Label1;
		TLabel			*Label2;
		TLabel			*Label9;
		TLabel			*Label12;
		TLabel			*IconIndexLabel;
		TBitBtn			*BitBtn1;
		TBitBtn			*BitBtn2;
		TCheckBox		*NoMsgShowCB;
		TImageList		*ImageList1;
		TOpenDialog		*OpenDialog1;
		TRadioGroup		*DfltOverWriteGrp;
		TRadioButton	*OkCancelRB;
		TRadioButton	*YesNoRB;
		TRadioButton	*DefIconRB;
		TRadioButton	*AutoIconRB;
		TRadioButton	*OkBttnRB;
		TRadioButton	*OrigIconRB;
		TUpDown			*IconIndexUD;
		TPageControl	*SFXPage;
		TTabSheet		*TabSheet1;
		TTabSheet		*TabSheet2;
		TTabSheet		*TabSheet3;
		TTabSheet		*TabSheet4;
		TTabSheet		*TabSheet5;
		TMemo				*Memo1;
		TMemo				*Memo2;
		TMemo				*Memo3;
		TMemo				*Memo4;
		TGroupBox		*GroupBox1;
		TGroupBox		*GroupBox2;

		void __fastcall FormShow( TObject *Sender );
		void __fastcall BitBtn2Click( TObject *Sender );
		void __fastcall ExecButClick( TObject *Sender );
		void __fastcall BitBtn1Click( TObject *Sender );
		void __fastcall DefIconRBClick( TObject *Sender );
		void __fastcall CancelButClick( TObject *Sender );
		void __fastcall AutoRunCBClick( TObject *Sender );
		void __fastcall IconEditKeyPress( TObject *Sender, char &Key );
		void __fastcall IconIndexUDClick( TObject *Sender, TUDBtnType Button );

	public:		// User declarations
		String IconDir;

		__fastcall TMakeSFX( TComponent *Owner ) : TForm( Owner ) { }
		void __fastcall LoadCustomIcon( String IconPath, int IconIndex );
};

//---------------------------------------------------------------------------
extern TMakeSFX *MakeSFX;

#endif

