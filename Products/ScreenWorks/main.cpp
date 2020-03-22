#include "lupch.h"
#pragma hdrstop

#define        MAIN    1

#include "about.h"
#include "config.h"
#include "main.h"
#include "preview.h"
#include "saver.h"
#include "SWutils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "scrb4_values"
#pragma link "Regi1632"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MainFormCreate(TObject *Sender)
{
// load VAR info from ini file
g_strVarBanner    = MainForm->regVar->ReadString("VAR", "banner"    );
g_strVarWebSite   = MainForm->regVar->ReadString("VAR", "website"   );
g_strVarName      = MainForm->regVar->ReadString("VAR", "name"      );

g_strVarBanner    = g_strVarBanner .IsEmpty() ? ::String(SP_MARQUEE_TEXT1) : g_strVarBanner ;
g_strVarWebSite   = g_strVarWebSite.IsEmpty() ? ::String(SP_MARQUEE_TEXT2) : g_strVarWebSite;

String      strFileFilter;
TCHAR       szModuleName[MAX_PATH];
String      strModuleName;

GetModuleFileName(NULL, szModuleName, sizeof (szModuleName) / sizeof (TCHAR));
strModuleName = szModuleName;

/* split the string to separate elems */
char        drive   [_MAX_DRIVE ],
            dir     [_MAX_DIR   ],
            file    [_MAX_FNAME ],
            ext     [_MAX_EXT   ];

_splitpath(szModuleName, drive, dir, file, ext);

// note that we have to scan for "Screen" here because GetModuleFileName
// returns the short file name (8.3) "Screen~1.scr" when it runs in the
// WinNT\system32 directory but returns the long file name when run in the
// development directory - very odd...
if ((strstr(::String(file).LowerCase().c_str(), "screen") != NULL))
    {
    g_bIsSolidPartners = true;
    }
else
    {
    g_bIsSolidPartners = false;
    }
}
//---------------------------------------------------------------------------

