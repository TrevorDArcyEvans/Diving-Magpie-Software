//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "read.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void    TfrmMain :: ReadMainMenu(void)
{
bool	WasError = false;

edtMain->Text = regMenuWorks->ReadString("Main", "Title");  MW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbMenuWorks->SimpleText = "Error:  " + regMenuWorks->ErrorMessage;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: ReadProgram(int Index)
{
bool	WasError = false;

dynamic_cast<TEdit  *>(FindComponent(btnProgName[Index]))->Text =
        regMenuWorks->ReadString(btnProgNumRegName[Index], "Prog_Name");  MW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbMenuWorks->SimpleText = "Error:  " + regMenuWorks->ErrorMessage;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: ReadMenu(int Index)
{
bool	WasError = false;

dynamic_cast<TEdit  *>(FindComponent(btnMenuName[Index]))->Text =
        regMenuWorks->ReadString(btnProgNumRegName[Index], "Menu_Text");  MW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbMenuWorks->SimpleText = "Error:  " + regMenuWorks->ErrorMessage;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: ReadHint(int Index)
{
bool	WasError = false;

dynamic_cast<TEdit  *>(FindComponent(btnHintName[Index]))->Text =
        regMenuWorks->ReadString(btnProgNumRegName[Index], "Hint_Text");  MW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbMenuWorks->SimpleText = "Error:  " + regMenuWorks->ErrorMessage;
    }
}
//---------------------------------------------------------------------------

