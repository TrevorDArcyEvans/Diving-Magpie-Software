//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <mapi.hpp>
#include <shellapi.h>
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnCheckClick(TObject *Sender)
{
JOYCAPS         	jcJoyCaps;

btnResetClick(this);

memset(&jcJoyCaps, 0, sizeof(JOYCAPS));

switch (joyGetDevCaps(JOYSTICKID1, &jcJoyCaps, sizeof(JOYCAPS)))
    {
    case JOYERR_NOERROR        :
            memJoystick->Lines->Add("wMid = " + AnsiString::AnsiString(jcJoyCaps.wMid));
            memJoystick->Lines->Add("wPid = " + AnsiString::AnsiString(jcJoyCaps.wPid));

            memJoystick->Lines->Add("szPname = " + AnsiString::AnsiString(jcJoyCaps.szPname));

            memJoystick->Lines->Add("wXmin = " + AnsiString::AnsiString(jcJoyCaps.wXmin));
            memJoystick->Lines->Add("wXmax = " + AnsiString::AnsiString(jcJoyCaps.wXmax));
            memJoystick->Lines->Add("wYmin = " + AnsiString::AnsiString(jcJoyCaps.wYmin));
            memJoystick->Lines->Add("wYmax = " + AnsiString::AnsiString(jcJoyCaps.wYmax));
            memJoystick->Lines->Add("wZmin = " + AnsiString::AnsiString(jcJoyCaps.wZmin));
            memJoystick->Lines->Add("wZmax = " + AnsiString::AnsiString(jcJoyCaps.wZmax));

            memJoystick->Lines->Add("wNumButtons = " + AnsiString::AnsiString(jcJoyCaps.wNumButtons));

            memJoystick->Lines->Add("wPeriodMin = " + AnsiString::AnsiString(jcJoyCaps.wPeriodMin));
            memJoystick->Lines->Add("wPeriodMax = " + AnsiString::AnsiString(jcJoyCaps.wPeriodMax));

            memJoystick->Lines->Add("wRmin = " + AnsiString::AnsiString(jcJoyCaps.wRmin));
            memJoystick->Lines->Add("wRmax = " + AnsiString::AnsiString(jcJoyCaps.wRmax));
            memJoystick->Lines->Add("wUmin = " + AnsiString::AnsiString(jcJoyCaps.wUmin));
            memJoystick->Lines->Add("wUmax = " + AnsiString::AnsiString(jcJoyCaps.wUmax));
            memJoystick->Lines->Add("wVmin = " + AnsiString::AnsiString(jcJoyCaps.wVmin));
            memJoystick->Lines->Add("wVmax = " + AnsiString::AnsiString(jcJoyCaps.wVmax));

            memJoystick->Lines->Add("wCaps = "       + AnsiString::AnsiString(jcJoyCaps.wCaps));

            memJoystick->Lines->Add("wMaxAxes = "    + AnsiString::AnsiString(jcJoyCaps.wMaxAxes));
            memJoystick->Lines->Add("wNumAxes = "    + AnsiString::AnsiString(jcJoyCaps.wNumAxes));

            memJoystick->Lines->Add("wMaxButtons = " + AnsiString::AnsiString(jcJoyCaps.wMaxButtons));

            memJoystick->Lines->Add("szRegKey = "    + AnsiString::AnsiString(jcJoyCaps.szRegKey));

            memJoystick->Lines->Add("szOEMVxD = "    + AnsiString::AnsiString(jcJoyCaps.szOEMVxD));

            memJoystick->Lines->Add("");

            // stuff for Windows NT
            if ((jcJoyCaps.wCaps & JOYCAPS_HASZ) == JOYCAPS_HASZ)
                {
                lblHASZ->Font->Color = clWindowText; 
                memJoystick->Lines->Add("HASZ");
                }

            if ((jcJoyCaps.wCaps & JOYCAPS_HASR) == JOYCAPS_HASR)
                {
                lblHASR->Font->Color = clWindowText;
                memJoystick->Lines->Add("HASR");
                }

            if ((jcJoyCaps.wCaps & JOYCAPS_HASU) == JOYCAPS_HASU)
                {
                lblHASU->Font->Color = clWindowText;
                memJoystick->Lines->Add("HASU");
                }

            if ((jcJoyCaps.wCaps & JOYCAPS_HASV) == JOYCAPS_HASV)
                {
                lblHASV->Font->Color = clWindowText;
                memJoystick->Lines->Add("HASV");
                }


            if ((jcJoyCaps.wCaps & JOYCAPS_HASPOV) == JOYCAPS_HASPOV)
                {
                lblHASPOV->Font->Color = clWindowText;
                memJoystick->Lines->Add("HASPOV");
                }

            if ((jcJoyCaps.wCaps & JOYCAPS_POV4DIR) == JOYCAPS_POV4DIR)
                {
                lblHASPOV4DIR->Font->Color = clWindowText;
                memJoystick->Lines->Add("HASPOV4DIR");
                }

            if ((jcJoyCaps.wCaps & JOYCAPS_POVCTS ) == JOYCAPS_POVCTS )
                {
                lblHASPOVCTS->Font->Color = clWindowText;
                memJoystick->Lines->Add("HASPOVCTS");
                }

            break;

    case MMSYSERR_NODRIVER   :
            memJoystick->Lines->Add("Can't find a virtual joystick driver.");
            break;

    case MMSYSERR_INVALPARAM:
            memJoystick->Lines->Add("Bad parameter passed when trying to locate virtual joystick driver.");
            break;

        default                :
            break;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnResetClick(TObject *Sender)
{
memJoystick->Lines->Clear();

lblHASZ->Font->Color        = clInactiveCaption;
lblHASR->Font->Color        = clInactiveCaption;
lblHASU->Font->Color        = clInactiveCaption;
lblHASV->Font->Color        = clInactiveCaption;
lblHASPOV->Font->Color      = clInactiveCaption;
lblHASPOV4DIR->Font->Color  = clInactiveCaption;
lblHASPOVCTS->Font->Color   = clInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnEmailClick(TObject *Sender)
{
MapiRecipDesc       mrdReceiver;
TMapiMessage        MapiMessage;
Cardinal            MError;

// receiver info
mrdReceiver.ulReserved      = 0;
mrdReceiver.ulRecipClass    = MAPI_TO;
mrdReceiver.lpszName        = "sales@SolidPartners.com";
mrdReceiver.lpszAddress     = "sales@SolidPartners.com";
mrdReceiver.ulEIDSize       = 0;
mrdReceiver.lpEntryID       = 0;

MapiMessage.ulReserved          = 0;
MapiMessage.lpszSubject         = "Joystick Information";
MapiMessage.lpszNoteText        = memJoystick->Lines->Text.c_str();
MapiMessage.lpszMessageType     = NULL;
MapiMessage.lpszDateReceived    = NULL;
MapiMessage.lpszConversationID  = NULL;
MapiMessage.flFlags             = 0;
MapiMessage.lpOriginator        = NULL;
MapiMessage.nRecipCount         = 1;
MapiMessage.lpRecips            = &mrdReceiver;
MapiMessage.nFileCount          = 0;
MapiMessage.lpFiles             = NULL;

MError = MapiSendMail(0, 0, MapiMessage,
                MAPI_DIALOG | MAPI_LOGON_UI | MAPI_NEW_SESSION, 0);

if (MError)
    {
	MessageDlg("Error sending mail", mtError, TMsgDlgButtons() << mbOK, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnWebClick(TObject *Sender)
{
ShellExecute(Handle, "open",
    "http://www.SolidPartners.com",
    NULL, NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
Application->Title = frmMain->Caption;    
}
//---------------------------------------------------------------------------

