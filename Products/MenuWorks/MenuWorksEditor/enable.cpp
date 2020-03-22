//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "enable.h"
#include "main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
void    TfrmMain :: EnableMainMenu(void)
{
edtMain->ReadOnly = false;
}
//---------------------------------------------------------------------------
void    TfrmMain :: EnableWriteButtons(void)
{
int				i = 0;

// enable write buttons
// NB includes "Write All" and "Main Menu" Write buttons
for (i = 0; i < NUM_WRITE_BUTTONS; i++)
   	{
	dynamic_cast<TButton  *>(FindComponent(btnWriteName[i]))->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: EnableProgramFields(void)
{
int				i = 0;

// enable program name entry fields
for (i = 0; i < NUM_PROG; i++)
   	{
	dynamic_cast<TEdit  *>(FindComponent(btnProgName[i]))->ReadOnly = false;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: EnableMenuFields(void)
{
int				i = 0;

// enable menu entry fields
for (i = 0; i < NUM_MENU; i++)
   	{
	dynamic_cast<TEdit  *>(FindComponent(btnMenuRegName[i]))->ReadOnly = false;
    }
}
//---------------------------------------------------------------------------
void    TfrmMain :: EnableHintFields(void)
{
int				i = 0;

// enable hint entry fields
for (i = 0; i < NUM_HINT; i++)
   	{
	dynamic_cast<TEdit  *>(FindComponent(btnHintRegName[i]))->ReadOnly = false;
    }
}
//---------------------------------------------------------------------------

