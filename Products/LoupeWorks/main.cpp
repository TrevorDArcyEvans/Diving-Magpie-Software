//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "configure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "bi_ctrls"
#pragma link "WinRoll"
#pragma link "Placemnt"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
#define    WM_LW_ABOUT      3500
#define    WM_LW_SPACE      3501
#define    WM_LW_CONFIGURE  3502
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
    try
        {
        HRESULT                         hr;

        hr = m_DMS_Comm.CoCreateInstance(CLSID_DMS_Common);

        // info for registration and about box
        hr = m_DMS_Comm->set_ProductName(WideString(LOUPE_WORKS_TITLE));
        hr = m_DMS_Comm->set_ProductCode(WideString(LOUPE_WORKS_TITLE_CODE));
        //hr = m_DMS_Comm->set_IniFileName(WideString(ROSETTA_WORKS_INI_FILE));

        // info for about box
        hr = m_DMS_Comm->set_Commercial(false);
        hr = m_DMS_Comm->set_Icon((long ) Application->Icon->Handle);
        (void ) hr;
        }
    catch (...)
        {
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
HMENU hsysmenu = GetSystemMenu(WindowHandle,FALSE);
if (hsysmenu != NULL)
    {
    AppendMenu(hsysmenu, MF_SEPARATOR, WM_LW_SPACE      , ""                );
    AppendMenu(hsysmenu, MF_STRING   , WM_LW_ABOUT      , "&About..."       );
    AppendMenu(hsysmenu, MF_STRING   , WM_LW_CONFIGURE  , "&Configure..."   );
    }

Application->Title = LOUPE_WORKS_TITLE;
frmMain->Caption = Application->Title;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::WndProc(Messages::TMessage &Message)
{
if ((Message.Msg    == WM_SYSCOMMAND) &&
    (Message.WParam == WM_LW_ABOUT  ) )
    {
    try
        {
        HRESULT                         hr;

        hr = m_DMS_Comm->About();

        (void ) hr;
        }
    catch (...)
        {
        }
    }
else if ((Message.Msg   == WM_SYSCOMMAND  ) &&
        (Message.WParam == WM_LW_CONFIGURE) )
        {
        frmConfigure->ShowModal();
        Message.Result = true;
        }
else
    {
    TForm::WndProc(Message);
    }
}
//---------------------------------------------------------------------------
