//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "browse.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void    TfrmMain :: BrowseProgram(int Index)
{
if (true == dlgOpen->Execute())
    {
    dynamic_cast<TEdit  *>(FindComponent(btnProgName[Index]))->Text = dlgOpen->FileName;
    }
}
//---------------------------------------------------------------------------
