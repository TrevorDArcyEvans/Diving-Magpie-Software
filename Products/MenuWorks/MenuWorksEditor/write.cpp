//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "read.h"
#include "write.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
void    TfrmMain :: WriteMainMenu(void)
{
bool	WasError = false;

regMenuWorks->WriteString("Main", "Title", edtMain->Text);  MW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbMenuWorks->SimpleText = "Error:  " + regMenuWorks->ErrorMessage;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: WriteProgram(int Index)
{
bool	WasError = false;

regMenuWorks->WriteString(btnProgNumRegName[Index], "Prog_Name",
    dynamic_cast<TEdit  *>(FindComponent(btnProgName[Index]))->Text );  MW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbMenuWorks->SimpleText = "Error:  " + regMenuWorks->ErrorMessage;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: WriteMenu(int Index)
{
bool	WasError = false;

regMenuWorks->WriteString(btnProgNumRegName[Index], "Menu_Text",
    dynamic_cast<TEdit  *>(FindComponent(btnMenuName[Index]))->Text);  MW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbMenuWorks->SimpleText = "Error:  " + regMenuWorks->ErrorMessage;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: WriteHint(int Index)
{
bool	WasError = false;

regMenuWorks->WriteString(btnProgNumRegName[Index], "Hint_Text",
    dynamic_cast<TEdit  *>(FindComponent(btnHintName[Index]))->Text );  MW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbMenuWorks->SimpleText = "Error:  " + regMenuWorks->ErrorMessage;
    }
}
//---------------------------------------------------------------------------

