#include <vcl\vcl.h>
#pragma hdrstop

#include "SFX.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMakeSFX *MakeSFX;

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::ExecButClick( TObject *Sender ) {
	TZipBuilder *zb = MainForm->ZipBuilder1;

	if ( CmdLineCB->Checked )
		  zb->SFXOptions = zb->SFXOptions << SFXAskCmdLine;
	else zb->SFXOptions = zb->SFXOptions >> SFXAskCmdLine;
	if ( FileListCB->Checked )
		  zb->SFXOptions = zb->SFXOptions << SFXAskFiles;
	else zb->SFXOptions = zb->SFXOptions >> SFXAskFiles;
	if ( HideOverWriteCB->Checked )
		  zb->SFXOptions = zb->SFXOptions << SFXHideOverWriteBox;
	else zb->SFXOptions = zb->SFXOptions >> SFXHideOverWriteBox;
	if ( AutoRunCB->Checked )
		  zb->SFXOptions = zb->SFXOptions << SFXAutoRun;
	else zb->SFXOptions = zb->SFXOptions >> SFXAutoRun;
	if ( NoMsgShowCB->Checked )
		  zb->SFXOptions = zb->SFXOptions << SFXNoSuccessMsg;
	else zb->SFXOptions = zb->SFXOptions >> SFXNoSuccessMsg;

	if ( !DfltOverWriteGrp->ItemIndex )
		zb->SFXOverWriteMode = OvrConfirm;
	if ( DfltOverWriteGrp->ItemIndex == 1 )
		zb->SFXOverWriteMode = OvrAlways;
	if ( DfltOverWriteGrp->ItemIndex == 2 )
		zb->SFXOverWriteMode = OvrNever;

	zb->SFXCaption		 = CaptionEdit->Text;
	zb->SFXDefaultDir  = DirectoryEdit->Text;
	zb->SFXCommandLine = CommandEdit->Text;

	zb->SFXMessage     = "";
	if ( OkCancelRB->Checked )
		zb->SFXMessage = "\1";
	if ( YesNoRB->Checked )
		zb->SFXMessage = "\2";
	zb->SFXMessage += MsgEdit->Text;

	MainForm->DoIt = true;
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::CancelButClick( TObject *Sender ) {
	MainForm->DoIt = false;
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::BitBtn1Click( TObject *Sender ) {
	String SelDir = DirectoryEdit->Text;

	MainForm->AskDirDialog( MakeSFX->Handle, SelDir );
	DirectoryEdit->Text = SelDir;
}

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::FormShow( TObject *Sender ) {
	TZipBuilder *zb = MainForm->ZipBuilder1;

	CmdLineCB->Checked  = (zb->SFXOptions.Contains( SFXAskCmdLine ) ) ? true : false;
	FileListCB->Checked = (zb->SFXOptions.Contains( SFXAskFiles ) )   ? true : false;
	AutoRunCB->Checked  = (zb->SFXOptions.Contains( SFXAutoRun ) )    ? true : false;
	HideOverWriteCB->Checked = (zb->SFXOptions.Contains( SFXHideOverWriteBox ) ) ? true : false;
	NoMsgShowCB->Checked = (zb->SFXOptions.Contains( SFXNoSuccessMsg ) ) ? true : false;

	switch ( zb->SFXOverWriteMode ) {
		case OvrConfirm: DfltOverWriteGrp->ItemIndex = 0; break;
		case OvrAlways:  DfltOverWriteGrp->ItemIndex = 1; break;
		case OvrNever:   DfltOverWriteGrp->ItemIndex = 2;
	}

	CaptionEdit->Text   = zb->SFXCaption;
	DirectoryEdit->Text = zb->SFXDefaultDir;
	CommandEdit->Text   = zb->SFXCommandLine;

	if ( zb->SFXMessage.Length() > 0 && (zb->SFXMessage[1] == 0x1 || zb->SFXMessage[1] == 0x2) ) {
		if ( zb->SFXMessage[1] == 0x1 )
			OkCancelRB->Checked = true;
		else
			YesNoRB->Checked = true;
			MsgEdit->Text = zb->SFXMessage.SubString( 2, zb->SFXMessage.Length()- 1 );
	} else {
		MsgEdit->Text     = zb->SFXMessage;
		OkBttnRB->Checked = true;
	}

	if ( ImageList1->Count == 3 ) ImageList1->Delete( 2 );
	if ( IconEdit->Text == "" ) {
		if ( zb->SFXIcon->Empty ) {
			ImageList1->GetIcon( (int)AutoRunCB->Checked, Image1->Picture->Icon );
			zb->SFXIcon = Image1->Picture->Icon;
		} else {
			ImageList1->AddIcon( zb->SFXIcon );
			OrigIconRB->Checked = true;
		}
	}
	OrigIconRB->Enabled = (ImageList1->Count == 3) ? true : false;
}


//---------------------------------------------------------------------------
void __fastcall TMakeSFX::IconIndexUDClick( TObject *Sender, TUDBtnType Button ) {
	LoadCustomIcon( IconEdit->Text, StrToIntDef( IconIndexEdit->Text, 0) );
}

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::IconEditKeyPress( TObject *Sender, char &Key ) {
	if ( FileExists ( IconEdit->Text ) )
		LoadCustomIcon( IconEdit->Text, StrToIntDef( IconIndexEdit->Text, 0 ) );
}

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::DefIconRBClick( TObject *Sender ) {
	ImageList1->GetIcon( ( (TRadioButton *)Sender )->Tag, Image1->Picture->Icon );
	MainForm->ZipBuilder1->SFXIcon = Image1->Picture->Icon;
	IconEdit->Text          = "";
	IconIndexEdit->Text     = "0";
	IconIndexLabel->Enabled = false;
	IconIndexEdit->Enabled  = false;
	IconIndexUD->Enabled    = false;
	IconIndexEdit->Color    = clBtnFace;
}

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::BitBtn2Click( TObject *Sender ) {
	if ( IconDir == "" )
		MainForm->GetSpecialFolder( CSIDL_DESKTOPDIRECTORY, IconDir );
	OpenDialog1->InitialDir = IconDir;
	if ( OpenDialog1->Execute() ) {
		IconDir        = ExtractFilePath( OpenDialog1->FileName );
		IconEdit->Text = OpenDialog1->FileName;
		DefIconRB->Checked  = false;
		AutoIconRB->Checked = false;
		if ( UpperCase( ExtractFileExt( OpenDialog1->FileName ) ) != "ICO" ) {
			LoadCustomIcon( OpenDialog1->FileName, StrToIntDef( IconIndexEdit->Text, 0) );
			IconIndexLabel->Enabled = true;
			IconIndexEdit->Enabled  = true;
			IconIndexUD->Enabled    = true;
			IconIndexEdit->Color    = clWindow;
		} else {
			Image1->Picture->Icon->LoadFromFile( OpenDialog1->FileName );
			IconIndexEdit->Text     = "0";
			IconIndexLabel->Enabled = false;
			IconIndexEdit->Enabled  = false;
			IconIndexUD->Enabled    = false;
			IconIndexEdit->Color    = clBtnFace;
			MainForm->ZipBuilder1->SFXIcon = Image1->Picture->Icon;
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::LoadCustomIcon( String IconPath, int IconIndex ) {
	HICON IconHandle;

	Image1->Picture->Icon->ReleaseHandle();
	MainForm->ZipBuilder1->SFXIcon->ReleaseHandle();
	IconHandle = ExtractIcon( HInstance, IconPath.c_str(), IconIndex );
	if ( IconHandle && (int)IconHandle != 1 ) {
		Image1->Picture->Icon->Handle = IconHandle;
		MainForm->ZipBuilder1->SFXIcon->Handle = IconHandle;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMakeSFX::AutoRunCBClick( TObject *Sender ) {
	if ( IconEdit->Text == "" ) {
		ImageList1->GetIcon( (int)AutoRunCB->Checked, Image1->Picture->Icon );
		MainForm->ZipBuilder1->SFXIcon = Image1->Picture->Icon;
	}
}

