//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#define        MAIN    1
#include "init.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma link "Regi1632"
#pragma link "cspin"
#pragma link "WinRoll"
#pragma link "CSPIN"
#pragma link "CSPIN"
#pragma link "WinRoll"
#pragma resource "*.dfm"
TfrmJoystick *frmJoystick;
//---------------------------------------------------------------------------
__fastcall TfrmJoystick::TfrmJoystick(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::mnuExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkXaxisClick(TObject *Sender)
{
CheckAxisClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkYaxisClick(TObject *Sender)
{
CheckAxisClick(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkZaxisClick(TObject *Sender)
{
CheckAxisClick(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkRaxisClick(TObject *Sender)
{
CheckAxisClick(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkUaxisClick(TObject *Sender)
{
CheckAxisClick(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkVaxisClick(TObject *Sender)
{
CheckAxisClick(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton1Click(TObject *Sender)
{
CheckButtonClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton2Click(TObject *Sender)
{
CheckButtonClick(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton3Click(TObject *Sender)
{
CheckButtonClick(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton4Click(TObject *Sender)
{
CheckButtonClick(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton5Click(TObject *Sender)
{
CheckButtonClick(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton6Click(TObject *Sender)
{
CheckButtonClick(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlXaxisChange(TObject *Sender)
{
DDLAxisChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlYaxisChange(TObject *Sender)
{
DDLAxisChange(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlZaxisChange(TObject *Sender)
{
DDLAxisChange(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlRaxisChange(TObject *Sender)
{
DDLAxisChange(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlUaxisChange(TObject *Sender)
{
DDLAxisChange(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlVaxisChange(TObject *Sender)
{
DDLAxisChange(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlXmodaxisChange(TObject *Sender)
{
DDLModAxisChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlYmodaxisChange(TObject *Sender)
{
DDLModAxisChange(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlZmodaxisChange(TObject *Sender)
{
DDLModAxisChange(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlRmodaxisChange(TObject *Sender)
{
DDLModAxisChange(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlUmodaxisChange(TObject *Sender)
{
DDLModAxisChange(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlVmodaxisChange(TObject *Sender)
{
DDLModAxisChange(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton1Change(TObject *Sender)
{
DDLButtonChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton2Change(TObject *Sender)
{
DDLButtonChange(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton3Change(TObject *Sender)
{
DDLButtonChange(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton4Change(TObject *Sender)
{
DDLButtonChange(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton5Change(TObject *Sender)
{
DDLButtonChange(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton6Change(TObject *Sender)
{
DDLButtonChange(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedXaxisChange(TObject *Sender)
{
SEDAxisChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedYaxisChange(TObject *Sender)
{
SEDAxisChange(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedZaxisChange(TObject *Sender)
{
SEDAxisChange(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedRaxisChange(TObject *Sender)
{
SEDAxisChange(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedUaxisChange(TObject *Sender)
{
SEDAxisChange(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedVaxisChange(TObject *Sender)
{
SEDAxisChange(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::btnCalibrateClick(TObject *Sender)
{
WinExec("control joy.cpl", SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkXsenseClick(TObject *Sender)
{
CheckSenseClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkYsenseClick(TObject *Sender)
{
CheckSenseClick(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkZsenseClick(TObject *Sender)
{
CheckSenseClick(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkRsenseClick(TObject *Sender)
{
CheckSenseClick(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkUsenseClick(TObject *Sender)
{
CheckSenseClick(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkVsenseClick(TObject *Sender)
{
CheckSenseClick(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkPOVfrontClick(TObject *Sender)
{
CheckPOVClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkPOVbackClick(TObject *Sender)
{
CheckPOVClick(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkPOVleftClick(TObject *Sender)
{
CheckPOVClick(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkPOVrightClick(TObject *Sender)
{
CheckPOVClick(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlPOVfrontChange(TObject *Sender)
{
DDLPOVChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlPOVbackChange(TObject *Sender)
{
DDLPOVChange(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlPOVleftChange(TObject *Sender)
{
DDLPOVChange(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlPOVrightChange(TObject *Sender)
{
DDLPOVChange(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::FormShow(TObject *Sender)
{
int                 i = 0;

bool                bEnabled = false;

memset(&jcJoyCaps, 0, sizeof(JOYCAPS));

switch (joyGetDevCaps(JOYSTICKID1, &jcJoyCaps, sizeof(JOYCAPS)))
    {
    case JOYERR_NOERROR        :
            bEnabled = true;
            break;

    case MMSYSERR_NODRIVER   :
            stbJoystick->SimpleText = "Can't find a virtual joystick driver.";
            break;

    case MMSYSERR_INVALPARAM:
            stbJoystick->SimpleText = "Bad parameter passed when trying to locate virtual joystick driver.";
            break;

        default                :
            break;
        }

if (true == bEnabled)
    {
    stbJoystick->SimpleText = "Using:  " + AnsiString::AnsiString(jcJoyCaps.szPname);

    sedPollFreq->Enabled = true;

    btnCalibrate   ->Enabled = true;

    // initialise axes
    chkXaxis->Checked = true; chkXaxis->Enabled = true;
    chkYaxis->Checked = true; chkYaxis->Enabled = true;

    // initialise axes in the driver
    for (i = 0; i < NUM_AXES; i++)
        {
        Axis[i].Threshold         = 15;
        Axis[i].OptionNum         =  0;
        Axis[i].ModOptionNum     =  0;
        }

    // initialise buttons
    for (i = 0; i < NUM_BUTTONS; i++)
        {
        Button[i].Pressed         = false;
        Button[i].OptionNum     = 0;
        }

    InitAxisDropDownList(ddlXaxis); InitAxisDropDownList(ddlXmodaxis);
    InitAxisDropDownList(ddlYaxis); InitAxisDropDownList(ddlYmodaxis);

    if ((jcJoyCaps.wCaps & JOYCAPS_HASZ) == JOYCAPS_HASZ) { chkZaxis->Checked = true; chkZaxis->Enabled = true; InitAxisDropDownList(ddlZaxis); InitAxisDropDownList(ddlZmodaxis); }
    if ((jcJoyCaps.wCaps & JOYCAPS_HASR) == JOYCAPS_HASR) { chkRaxis->Checked = true; chkRaxis->Enabled = true; InitAxisDropDownList(ddlRaxis); InitAxisDropDownList(ddlRmodaxis); }
    if ((jcJoyCaps.wCaps & JOYCAPS_HASU) == JOYCAPS_HASU) { chkUaxis->Checked = true; chkUaxis->Enabled = true; InitAxisDropDownList(ddlUaxis); InitAxisDropDownList(ddlUmodaxis); }
    if ((jcJoyCaps.wCaps & JOYCAPS_HASV) == JOYCAPS_HASV) { chkVaxis->Checked = true; chkVaxis->Enabled = true; InitAxisDropDownList(ddlVaxis); InitAxisDropDownList(ddlVmodaxis);}

    // initialise buttons
    switch (jcJoyCaps.wNumButtons)
        {
        case 32    :
        case 31    :
        case 30    :

        case 29    :
        case 28    :
        case 27    :
        case 26    :
        case 25    :
        case 24    :
        case 23    :
        case 22    :
        case 21    :
        case 20    :

        case 19    :
        case 18    :
        case 17    :
        case 16    :
        case 15    :
        case 14    :
        case 13    :
        case 12    :
        case 11    :
        case 10    :
        case  9    :
        case  8    :
        case  7    :
        case  6    :    chkButton6->Checked = true;    chkButton6->Enabled = true; InitButtonDropDownList(ddlButton6);
        case  5    :    chkButton5->Checked = true;    chkButton5->Enabled = true; InitButtonDropDownList(ddlButton5);

        case  4    :    chkButton4->Checked = true;    chkButton4->Enabled = true; InitButtonDropDownList(ddlButton4);
        case  3    :    chkButton3->Checked = true;    chkButton3->Enabled = true; InitButtonDropDownList(ddlButton3);
        case  2    :    chkButton2->Checked = true;    chkButton2->Enabled = true; InitButtonDropDownList(ddlButton2);
        case  1    :    chkButton1->Checked = true;    chkButton1->Enabled = true; InitButtonDropDownList(ddlButton1);
        }

    if ((jcJoyCaps.wCaps & JOYCAPS_HASPOV) == JOYCAPS_HASPOV)
        {
        chkPOVfront ->Checked = true;    chkPOVfront->Enabled = true; InitButtonDropDownList(ddlPOVfront);
        chkPOVback  ->Checked = true;    chkPOVback ->Enabled = true; InitButtonDropDownList(ddlPOVback);
        chkPOVleft  ->Checked = true;    chkPOVleft ->Enabled = true; InitButtonDropDownList(ddlPOVleft);
        chkPOVright ->Checked = true;    chkPOVright->Enabled = true; InitButtonDropDownList(ddlPOVright);
        }

    // after all that hard work, try and load the settings from the .ini file
    if (frmJoystick->ReadSettings() == true)
        {
        frmJoystick->InitInterface();
        }

    // clear dirty flag
    bDirty = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::FormClose(TObject *Sender, TCloseAction &Action)
{
if (true == bDirty)
    {
    int     nRes = MessageBox(NULL, "Save changes?", "Confirm",
                        MB_YESNOCANCEL | MB_DEFBUTTON1 | MB_ICONQUESTION);
    switch (nRes)
        {
        case    IDYES   :
            btnOKClick(Sender);
            Action = caFree;
            break;

        case    IDNO    :
            Action = caFree;
            break;

        default         :
        case    IDCANCEL:
            Action = caNone	;
            break;
        }
    }
else
    {
    Action = caFree;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::btnOKClick(TObject *Sender)
{
int             i = 0;
bool            WasError = false;

// stuff here to save settings
for (i = 0; i < NUM_AXES; i++)
    {
    regSettings->WriteString(chkAxisName           [i], "enabled"     , AnsiString::AnsiString((int ) Axis[i].Enabled           ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(chkAxisSenseName      [i], "enabled"     , AnsiString::AnsiString((int ) Axis[i].OppSense          ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(ddlAxisName           [i], "normal"      , AnsiString::AnsiString((int ) Axis[i].OptionNum         ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(ddlModAxisName        [i], "normal mod"  , AnsiString::AnsiString((int ) Axis[i].ModOptionNum      ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(sedAxisName           [i], "threshold"   , AnsiString::AnsiString((int ) Axis[i].Threshold         ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(sedAxisSensName       [i], "sensitivity" , AnsiString::AnsiString((int ) Axis[i].Sensitivity       ));     SW_HANDLE_REG_ERROR;
    }

for (i = 0; i < NUM_BUTTONS; i++)
    {
    regSettings->WriteString(chkButtonName[i], "enabled", AnsiString::AnsiString((int ) Button[i].Enabled          ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(ddlButtonName[i], "normal" , AnsiString::AnsiString((int ) Button[i].OptionNum        ));     SW_HANDLE_REG_ERROR;
    }

regSettings->WriteString("Poll", "freq", AnsiString::AnsiString((int ) sedPollFreq->Value));    SW_HANDLE_REG_ERROR;

if ((jcJoyCaps.wCaps & JOYCAPS_HASPOV) == JOYCAPS_HASPOV)
    {
    for (i = 0; i < NUM_POV; i++)
        {
        regSettings->WriteString(chkPOVName[i], "enabled", AnsiString::AnsiString((int ) POV[i].Enabled          ));     SW_HANDLE_REG_ERROR;
        regSettings->WriteString(ddlPOVName[i], "normal" , AnsiString::AnsiString((int ) POV[i].OptionNum        ));     SW_HANDLE_REG_ERROR;
        }
    }

// clear dirty flag
bDirty = false;

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbJoystick->SimpleText = "Error:  " + regSettings->ErrorMessage;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedXSensChange(TObject *Sender)
{
SEDAxisSensChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedYSensChange(TObject *Sender)
{
SEDAxisSensChange(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedZSensChange(TObject *Sender)
{
SEDAxisSensChange(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedRSensChange(TObject *Sender)
{
SEDAxisSensChange(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedUSensChange(TObject *Sender)
{
SEDAxisSensChange(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedVSensChange(TObject *Sender)
{
SEDAxisSensChange(5);
}
//---------------------------------------------------------------------------

