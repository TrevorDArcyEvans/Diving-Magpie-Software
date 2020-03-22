//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#define		MAIN	1
#include "about.h"
#include "crc_32.h"
#include "CodeGen.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "process.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma link "Regi1632"
#pragma link "Just1_32"
#pragma link "cspin"
#pragma link "WinRoll"
#pragma link "CSPIN"
#pragma resource "*.dfm"
TfrmJoystick *frmJoystick;
//---------------------------------------------------------------------------
__fastcall TfrmJoystick::TfrmJoystick(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::tmrJoystickTimer(TObject *Sender)
{
if (bSW_Running                 == true     &&
    bJoystick_Running           == false    )
    {
    pjiJoyInfo.dwSize = (DWORD ) (sizeof(JOYINFOEX));
    pjiJoyInfo.dwFlags = JOY_RETURNALL;

    switch (joyGetPosEx(JOYSTICKID1, &pjiJoyInfo))
        {
        case JOYERR_NOERROR            :
                CalculateJoystick(pjiJoyInfo, jcJoyCaps,Button, Axis);
                ProcessJoystick  (pjiJoyInfo, jcJoyCaps,Button, Axis);
                break;

        case MMSYSERR_NODRIVER      :
                stbJoystick->SimpleText = "The joystick driver is not present.";
                break;

        case MMSYSERR_INVALPARAM    :
                stbJoystick->SimpleText = "An invalid parameter was passed.";
                break;

        case MMSYSERR_BADDEVICEID   :
                stbJoystick->SimpleText = "The specified joystick identifier is invalid.";
                break;

        case JOYERR_UNPLUGGED       :
                stbJoystick->SimpleText = "The specified joystick is not connected to the system.";
                break;

        default                        :
                stbJoystick->SimpleText = "Unknown return code from joyGetPosEx().";
                break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::FormCreate(TObject *Sender)
{
int        i = 0;

bool    bEnabled = false;

Application->Title 		= STK_WORKS_TITLE;
Application->HelpFile 	= "stkworks.HLP";

swDateCode = 0;

frmJoystick->Caption 	= Application->Title;

bSW_Running         = false;
bJoystick_Running   = false;

bDoingGraphics      = false;
bGraphicsRedrawReq  = false;

// turn off joystick timer before we check for SW
tmrJoystick->Enabled = false;

// check for SW on entry
swWindow = NULL;

tmrEnumTimer(Sender);

// turn on joystick timer after we've checked for SW
tmrJoystick->Enabled = true;

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

if (bEnabled ==true)
    {
    stbJoystick->SimpleText = "Using:  " + AnsiString::AnsiString(jcJoyCaps.szPname);

    sedPollFreq->Enabled = true;
    frmJoystick->sedPollFreqChange(Sender);

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
        case  6    :	chkButton6->Checked = true;    chkButton6->Enabled = true; InitButtonDropDownList(ddlButton6);
        case  5    :	chkButton5->Checked = true;    chkButton5->Enabled = true; InitButtonDropDownList(ddlButton5);

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
    if (frmJoystick->ReadSettings(regSettings->IniFileName) == true)
        {
        frmJoystick->InitInterface();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::mnuAboutClick(TObject *Sender)
{
frmAbout->Caption 					= Application->Title;
frmAbout->lblProductName->Caption 	= "Product Name:   " + Application->Title;
frmAbout->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::mnuExitClick(TObject *Sender)
{
frmJoystick->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedPollFreqChange(TObject *Sender)
{
tmrJoystick->Interval = sedPollFreq->Value;

tmrJoystick->Interval =  (tmrJoystick->Interval > jcJoyCaps.wPeriodMax)
                            ? jcJoyCaps.wPeriodMax : tmrJoystick->Interval;

tmrJoystick->Interval =  (tmrJoystick->Interval < jcJoyCaps.wPeriodMin)
                            ? jcJoyCaps.wPeriodMin : tmrJoystick->Interval;

sedPollFreq->Value = tmrJoystick->Interval;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkXaxisClick(TObject *Sender)
{
ddlXaxis       ->Enabled = chkXaxis->Checked;
ddlXmodaxis    ->Enabled = chkXaxis->Checked;
sedXaxis       ->Enabled = chkXaxis->Checked;
chkXsense      ->Enabled = chkXaxis->Checked;

Axis[0]         .Enabled = chkXaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkYaxisClick(TObject *Sender)
{
ddlYaxis    ->Enabled = chkYaxis->Checked;
ddlYmodaxis ->Enabled = chkYaxis->Checked;
sedYaxis    ->Enabled = chkYaxis->Checked;
chkYsense   ->Enabled = chkYaxis->Checked;

Axis[1]         .Enabled = chkYaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkZaxisClick(TObject *Sender)
{
ddlZaxis    ->Enabled = chkZaxis->Checked;
ddlZmodaxis ->Enabled = chkZaxis->Checked;
sedZaxis    ->Enabled = chkZaxis->Checked;
chkZsense   ->Enabled = chkZaxis->Checked;

Axis[2]         .Enabled = chkZaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkRaxisClick(TObject *Sender)
{
ddlRaxis    ->Enabled = chkRaxis->Checked;
ddlRmodaxis ->Enabled = chkRaxis->Checked;
sedRaxis    ->Enabled = chkRaxis->Checked;
chkRsense	->Enabled = chkRaxis->Checked;

Axis[3]         .Enabled = chkRaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkUaxisClick(TObject *Sender)
{
ddlUaxis    ->Enabled = chkUaxis->Checked;
ddlUmodaxis ->Enabled = chkUaxis->Checked;
sedUaxis    ->Enabled = chkUaxis->Checked;
chkUsense	->Enabled = chkUaxis->Checked;

Axis[4]         .Enabled = chkUaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkVaxisClick(TObject *Sender)
{
ddlVaxis    ->Enabled = chkVaxis->Checked;
ddlVmodaxis ->Enabled = chkVaxis->Checked;
sedVaxis    ->Enabled = chkVaxis->Checked;
chkVsense	->Enabled = chkVaxis->Checked;

Axis[5]         .Enabled = chkVaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton1Click(TObject *Sender)
{
ddlButton1->Enabled = chkButton1->Checked;
Button[0]  .Enabled = chkButton1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton2Click(TObject *Sender)
{
ddlButton2->Enabled = chkButton2->Checked;
Button[1]  .Enabled = chkButton2->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton3Click(TObject *Sender)
{
ddlButton3->Enabled = chkButton3->Checked;
Button[2]  .Enabled = chkButton3->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkButton4Click(TObject *Sender)
{
ddlButton4->Enabled = chkButton4->Checked;
Button[3]  .Enabled = chkButton4->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkAutoSaveIntClick(TObject *Sender)
{
sedAutoSaveInt->Enabled = chkAutoSaveInt->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlXaxisChange(TObject *Sender)
{
Axis[0].OptionNum = ddlXaxis->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlYaxisChange(TObject *Sender)
{
Axis[1].OptionNum = ddlYaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlZaxisChange(TObject *Sender)
{
Axis[2].OptionNum = ddlZaxis->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlRaxisChange(TObject *Sender)
{
Axis[3].OptionNum = ddlRaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlUaxisChange(TObject *Sender)
{
Axis[4].OptionNum = ddlUaxis->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlVaxisChange(TObject *Sender)
{
Axis[5].OptionNum = ddlVaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlXmodaxisChange(TObject *Sender)
{
Axis[0].ModOptionNum = ddlXmodaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlYmodaxisChange(TObject *Sender)
{
Axis[1].ModOptionNum = ddlYmodaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlZmodaxisChange(TObject *Sender)
{
Axis[2].ModOptionNum = ddlZmodaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlRmodaxisChange(TObject *Sender)
{
Axis[3].ModOptionNum = ddlRmodaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlUmodaxisChange(TObject *Sender)
{
Axis[4].ModOptionNum = ddlUmodaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlVmodaxisChange(TObject *Sender)
{
Axis[5].ModOptionNum = ddlVmodaxis->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton1Change(TObject *Sender)
{
Button[0].OptionNum = ddlButton1->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton2Change(TObject *Sender)
{
Button[1].OptionNum = ddlButton2->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton3Change(TObject *Sender)
{
Button[2].OptionNum = ddlButton3->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::ddlButton4Change(TObject *Sender)
{
Button[3].OptionNum = ddlButton4->ItemIndex;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedXaxisChange(TObject *Sender)
{
Axis[0].Threshold = sedXaxis->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedYaxisChange(TObject *Sender)
{
Axis[1].Threshold = sedYaxis->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedZaxisChange(TObject *Sender)
{
Axis[2].Threshold = sedZaxis->Value;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedRaxisChange(TObject *Sender)
{
Axis[3].Threshold = sedRaxis->Value;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedUaxisChange(TObject *Sender)
{
Axis[4].Threshold = sedUaxis->Value;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedVaxisChange(TObject *Sender)
{
Axis[5].Threshold = sedVaxis->Value;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::sedAutoSaveIntChange(TObject *Sender)
{
// convert from minutes to milliseconds
tmrAutoSave->Interval = sedAutoSaveInt->Value * 1000 * 60;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::mnuOpenClick(TObject *Sender)
{
if (dlgOpen->Execute() == true)
    {
    frmJoystick->ReadSettings(dlgOpen->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::mnuSaveAsClick(TObject *Sender)
{
if (dlgSave->Execute() == true)
    {
    // stuff here to save settings under a different name
    regSettings->IniFileName = dlgSave->FileName;
    frmJoystick->mnuSaveClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::tmrAutoSaveTimer(TObject *Sender)
{
if ((bSW_Running 			 == true) &&
	(chkAutoSaveInt->Checked == true))
	{
    swOleProcedure(
    	Option[SAVE_NUM].SW_OleType        ,
        Option[SAVE_NUM].SW_OleProcName    ,
        Option[SAVE_NUM].SW_OleNumParam    ,
        Option[SAVE_NUM].SW_OleParam1      , 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::btnCalibrateClick(TObject *Sender)
{
WinExec("control joy.cpl", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::mnuSaveClick(TObject *Sender)
{
int     i = 0;
bool	WasError = false;

// stuff here to save settings
for (i = 0; i < NUM_AXES; i++)
    {
    regSettings->WriteString(chkAxisName   		[i], "enabled"   , AnsiString::AnsiString((int ) Axis[i].Enabled           ));     SW_HANDLE_REG_ERROR;
	regSettings->WriteString(chkAxisSenseName 	[i], "enabled"   , AnsiString::AnsiString((int ) Axis[i].OppSense          ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(ddlAxisName   		[i], "normal"    , AnsiString::AnsiString((int ) Axis[i].OptionNum         ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(ddlModAxisName		[i], "normal mod", AnsiString::AnsiString((int ) Axis[i].ModOptionNum      ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(sedAxisName   		[i], "threshold" , AnsiString::AnsiString((int ) Axis[i].Threshold         ));     SW_HANDLE_REG_ERROR;
    }

for (i = 0; i < NUM_BUTTONS; i++)
    {
    regSettings->WriteString(chkButtonName[i], "enabled", AnsiString::AnsiString((int ) Button[i].Enabled          ));     SW_HANDLE_REG_ERROR;
    regSettings->WriteString(ddlButtonName[i], "normal" , AnsiString::AnsiString((int ) Button[i].OptionNum        ));     SW_HANDLE_REG_ERROR;
    }

regSettings->WriteString("Poll", "freq", AnsiString::AnsiString((int ) sedPollFreq->Value));    SW_HANDLE_REG_ERROR;

regSettings->WriteString("StartMin", "minimised", AnsiString::AnsiString((int ) chkStartMin->Checked));    SW_HANDLE_REG_ERROR;

regSettings->WriteString("AutoSave", "enabled" , AnsiString::AnsiString((int ) sedAutoSaveInt->Enabled));    SW_HANDLE_REG_ERROR;
regSettings->WriteString("AutoSave", "interval", AnsiString::AnsiString((int ) sedAutoSaveInt->Value  ));    SW_HANDLE_REG_ERROR;

if ((jcJoyCaps.wCaps & JOYCAPS_HASPOV) == JOYCAPS_HASPOV)
    {
    for (i = 0; i < NUM_POV; i++)
        {
        regSettings->WriteString(chkPOVName[i], "enabled", AnsiString::AnsiString((int ) POV[i].Enabled          ));     SW_HANDLE_REG_ERROR;
        regSettings->WriteString(ddlPOVName[i], "normal" , AnsiString::AnsiString((int ) POV[i].OptionNum        ));     SW_HANDLE_REG_ERROR;
        }
    }

// if the security timer is disabled, then the uers must have a good security
// code, so write this to the current *.ini file
if (tmrSecurity->Enabled == false)
    {
    unsigned long       CRC32;
    long                CharCnt;
    char                TempStr[2 * MAX_PATH];

    // get machine ID
    strcpy(TempStr, frmCodeGen->edtMachineID->Text.c_str());

    // add product name
    strcat(TempStr, STK_WORKS_TITLE_CODE);

    // calculate 32 bit CRC value
    crc32string(&CRC32,&CharCnt, TempStr);

    sprintf(TempStr, "%x", CRC32);

    regSettings->WriteString("Security", "code", TempStr);

    mnuRegister->Enabled = false;
    }

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbJoystick->SimpleText = "Error:  " + regSettings->ErrorMessage;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::mnuContentsClick(TObject *Sender)
{
WinExec(
    AnsiString::AnsiString(
        AnsiString::AnsiString("winhlp32 ") +
        Application->HelpFile).c_str(),
        SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkXsenseClick(TObject *Sender)
{
Axis[0].OppSense = chkXsense->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkYsenseClick(TObject *Sender)
{
Axis[1].OppSense = chkYsense->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkZsenseClick(TObject *Sender)
{
Axis[2].OppSense = chkZsense->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkRsenseClick(TObject *Sender)
{
Axis[3].OppSense = chkRsense->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkUsenseClick(TObject *Sender)
{
Axis[4].OppSense = chkUsense->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmJoystick::chkVsenseClick(TObject *Sender)
{
Axis[5].OppSense = chkVsense->Checked;
}
//---------------------------------------------------------------------------



void __fastcall TfrmJoystick::chkPOVfrontClick(TObject *Sender)
{
ddlPOVfront->Enabled = chkPOVfront->Checked;
POV[0]      .Enabled = chkPOVfront->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::chkPOVbackClick(TObject *Sender)
{
ddlPOVback ->Enabled = chkPOVback->Checked;
POV[1]      .Enabled = chkPOVback->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::chkPOVleftClick(TObject *Sender)
{
ddlPOVleft ->Enabled = chkPOVleft->Checked;
POV[2]      .Enabled = chkPOVleft->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::chkPOVrightClick(TObject *Sender)
{
ddlPOVright->Enabled = chkPOVright->Checked;
POV[3]      .Enabled = chkPOVright->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::ddlPOVfrontChange(TObject *Sender)
{
POV[0].OptionNum = ddlPOVfront->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::ddlPOVbackChange(TObject *Sender)
{
POV[1].OptionNum = ddlPOVback->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::ddlPOVleftChange(TObject *Sender)
{
POV[2].OptionNum = ddlPOVleft->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::ddlPOVrightChange(TObject *Sender)
{
POV[3].OptionNum = ddlPOVright->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::tmrRedrawTimer(TObject *Sender)
{
if (bSW_Running                 == true     &&
    bJoystick_Running           == false    )
    {
    try
	    {
        // first refresh our connection to SolidWorks
	    swApp = CreateOleObject("SldWorks.Application");

    	// refresh the active document
        swModelDoc     = swApp.OleFunction("ActiveDoc");
        swModelView    = swModelDoc.OleFunction("ActiveView");
        swPart         = swModelDoc;
        swAssy         = swModelDoc;
        }
    CATCH_OLE_ERROR;

    if (bDoingGraphics      == false    &&
        bGraphicsRedrawReq  == true     )
        {
        try
	        {
            swModelDoc.OleProcedure("GraphicsRedraw2");
            bGraphicsRedrawReq  = false;
            }
        CATCH_OLE_ERROR;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::mnuRegisterClick(TObject *Sender)
{
frmCodeGen->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::tmrSecurityTimer(TObject *Sender)
{
// if haven't been disabled during initialisation then close the app
Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::tmrWindowTimer(TObject *Sender)
{
if (IsWindow        (swWindow) != 0 &&
    IsWindowVisible (swWindow) != 0 &&
    IsWindowEnabled (swWindow) != 0 &&
    IsIconic        (swWindow) == 0 )       // !=0 means window is NOT iconic
    {
    bSW_Running = true;
    }
else
    {
    bSW_Running = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmJoystick::tmrEnumTimer(TObject *Sender)
{
// reset flags for joystick panel and SW
bJoystick_Running = true;
bSW_Running = false;

// now try and find SW or joystick panel
// primarily joystick panel
EnumWindows((WNDENUMPROC ) StickWorksEnumFunc, (LPARAM ) 1);
}
//---------------------------------------------------------------------------

