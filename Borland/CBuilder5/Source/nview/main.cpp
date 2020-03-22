//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

#include "nviewlib.h"


TFRM_Main *FRM_Main;
//---------------------------------------------------------------------------
__fastcall TFRM_Main::TFRM_Main(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFRM_Main::BTN_OpenClick(TObject *Sender)
{

  AnsiString szName;

  if( OpenDialog1->Execute())
    {
    szName = OpenDialog1->FileName;
    Image1->Picture->Bitmap->Handle = NViewLibLoad(szName.c_str(), true);
    ScrollBox1->HorzScrollBar->Position = 0;
    ScrollBox1->VertScrollBar->Position = 0;
    }

}
//---------------------------------------------------------------------------
void __fastcall TFRM_Main::BTN_ExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TFRM_Main::FormCreate(TObject *Sender)
{

  AppendMenu(GetSystemMenu(Handle, FALSE), MF_SEPARATOR, 0, "");
  AppendMenu(GetSystemMenu(Handle, FALSE), MF_STRING, (long)MNU_About->Handle, MNU_About->Caption.c_str());

}
//---------------------------------------------------------------------------
void __fastcall TFRM_Main::MNU_AboutClick(TObject *Sender)
{

  MessageBox(Handle, "Written by: Ed Lyk\nelyk@sprynet.com", "NVIEWLIB C++ Builder Demo", MB_OK + MB_ICONINFORMATION);
  	
}
//---------------------------------------------------------------------------
void __fastcall TFRM_Main::WMSysCommand(TMessage& Message)
{
  if(Message.WParam == (long)MNU_About->Handle)
   MNU_AboutClick(NULL);
  TForm::Dispatch(&Message);
}

void __fastcall TFRM_Main::Button1Click(TObject *Sender)
{
//Image1->Picture->SaveToFile("tde.jpg");
NViewLibSaveAsJPG(100, "tde.jpg");
}
//---------------------------------------------------------------------------

