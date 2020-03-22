//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#define		MAIN	1

#include "about.h"
#include "browse.h"
#include "crc_32.h"
#include "enable.h"
#include "main.h"
#include "read.h"
#include "write.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Regi1632"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
char                MachineID[MAX_PATH];
AnsiString          CodeStr;

strcpy(MachineID, GetMachineID());

Application->Title 		= MENU_WORKS_TITLE;
Application->HelpFile 	= "MenuWks.HLP";
frmMain->Caption = MENU_WORKS_TITLE;

strcpy(MachineID, GetMachineID());
CodeStr = regMenuWorks->ReadString("Security", "code");
if (CheckCode(MachineID, MENU_WORKS_TITLE_CODE, CodeStr.c_str()) == true)
    {
    bRegistered = true;

    EnableMainMenu();

    EnableWriteButtons();
    EnableProgramFields();
    EnableMenuFields();
    EnableHintFields();
    }

btnReadAllClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnMainReadClick(TObject *Sender)
{
ReadMainMenu();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead0Click(TObject *Sender)
{
ReadProgram(0);     ReadMenu(0);    ReadHint(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead1Click(TObject *Sender)
{
ReadProgram(1);     ReadMenu(1);    ReadHint(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead2Click(TObject *Sender)
{
ReadProgram(2);     ReadMenu(2);    ReadHint(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead3Click(TObject *Sender)
{
ReadProgram(3);     ReadMenu(3);    ReadHint(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead4Click(TObject *Sender)
{
ReadProgram(4);     ReadMenu(4);    ReadHint(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead5Click(TObject *Sender)
{
ReadProgram(5);     ReadMenu(5);    ReadHint(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead6Click(TObject *Sender)
{
ReadProgram(6);     ReadMenu(6);    ReadHint(6);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead7Click(TObject *Sender)
{
ReadProgram(7);     ReadMenu(7);    ReadHint(7);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead8Click(TObject *Sender)
{
ReadProgram(8);     ReadMenu(8);    ReadHint(8);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRead9Click(TObject *Sender)
{
ReadProgram(9);     ReadMenu(9);    ReadHint(9);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnReadAllClick(TObject *Sender)
{
ReadMainMenu();

for (int i = 0; i < NUM_PROG; i++)
    {
    ReadProgram(i);     ReadMenu(i);    ReadHint(i);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnMainWriteClick(TObject *Sender)
{
WriteMainMenu();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite0Click(TObject *Sender)
{
WriteProgram(0);    WriteMenu(0);   WriteHint(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite1Click(TObject *Sender)
{
WriteProgram(1);    WriteMenu(1);   WriteHint(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite2Click(TObject *Sender)
{
WriteProgram(2);    WriteMenu(2);   WriteHint(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite3Click(TObject *Sender)
{
WriteProgram(3);    WriteMenu(3);   WriteHint(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite4Click(TObject *Sender)
{
WriteProgram(4);    WriteMenu(4);   WriteHint(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite5Click(TObject *Sender)
{
WriteProgram(5);    WriteMenu(5);   WriteHint(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite6Click(TObject *Sender)
{
WriteProgram(6);    WriteMenu(6);   WriteHint(6);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite7Click(TObject *Sender)
{
WriteProgram(7);    WriteMenu(7);   WriteHint(7);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite8Click(TObject *Sender)
{
WriteProgram(8);    WriteMenu(8);   WriteHint(8);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWrite9Click(TObject *Sender)
{
WriteProgram(9);    WriteMenu(9);   WriteHint(9);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWriteAllClick(TObject *Sender)
{
WriteMainMenu();

for (int i = 0; i < NUM_PROG; i++)
    {
    WriteProgram(i);     WriteMenu(i);    WriteHint(i);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse0Click(TObject *Sender)
{
BrowseProgram(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse1Click(TObject *Sender)
{
BrowseProgram(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse2Click(TObject *Sender)
{
BrowseProgram(2);    
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse3Click(TObject *Sender)
{
BrowseProgram(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse4Click(TObject *Sender)
{
BrowseProgram(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse5Click(TObject *Sender)
{
BrowseProgram(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse6Click(TObject *Sender)
{
BrowseProgram(6);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnBrowse7Click(TObject *Sender)
{
BrowseProgram(7);    
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse8Click(TObject *Sender)
{
BrowseProgram(8);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowse9Click(TObject *Sender)
{
BrowseProgram(9);    
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::About1Click(TObject *Sender)
{
frmAbout->Caption 					= Application->Title;
frmAbout->lblProductName->Caption 	= "Product Name:   " + Application->Title;
frmAbout->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Contents1Click(TObject *Sender)
{
WinExec(
    AnsiString::AnsiString(
        AnsiString::AnsiString("winhlp32 ") +
        Application->HelpFile).c_str(),
        SW_NORMAL);
}
//---------------------------------------------------------------------------

