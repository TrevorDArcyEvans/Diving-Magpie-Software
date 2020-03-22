//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#define		MAIN	1
#include "about.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "orb.h"
#include "process.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma link "Regi1632"
#pragma link "Just1_32"
#pragma link "async32"
#pragma link "cspin"
#pragma link "WinRoll"
#pragma resource "*.dfm"
TfrmOrb *frmOrb;
//---------------------------------------------------------------------------
__fastcall TfrmOrb::TfrmOrb(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::FormCreate(TObject *Sender)
{
int        i = 0;

bool    bEnabled = false;

Application->Title 		= ORB_WORKS_TITLE;
Application->HelpFile 	= "orbworks.HLP";

swDateCode = 0;

frmOrb->Caption 	= Application->Title;

bSW_Running         = false;

bDoingGraphics      = false;
bGraphicsRedrawReq  = false;

// turn off joystick timer before we check for SW
tmrOrb->Enabled = false;

// check for SW on entry
swWindow = NULL;

tmrEnumTimer(Sender);

// turn on joystick timer after we've checked for SW
tmrOrb->Enabled = true;

// assume Orb is present...
bOrbPresent = true;

// first read settings to get com port
if (frmOrb->ReadSettings(regSettings->IniFileName) == true)
	{
    Comm32->Open();
    }

memset(&jcJoyCaps, 0, sizeof(JOYCAPS));

switch (orbGetDevCaps(JOYSTICKID1, &jcJoyCaps, sizeof(JOYCAPS)))
    {
    case JOYERR_NOERROR        :
            bEnabled = true;
            break;

    case MMSYSERR_NODRIVER   :
            stbOrb->SimpleText = "Can't find a SpaceOrb.";
            break;

    case MMSYSERR_INVALPARAM:
            stbOrb->SimpleText = "Bad parameter passed when trying to locate SpaceOrb.";
            break;

        default                :
            break;
        }

if (bEnabled ==true)
    {
    stbOrb->SimpleText = "Using:  " + AnsiString::AnsiString(jcJoyCaps.szPname);
    sedUpdateFreq->Enabled = true;
    frmOrb->sedUpdateFreqChange(Sender);

    // initialise X & Y axes
    chkXaxis->Checked = true; chkXaxis->Enabled = true;
    chkYaxis->Checked = true; chkYaxis->Enabled = true;

    // initialise axes
    for (i = 0; i < NUM_AXES; i++)
        {
        Axis[i].Threshold        = 30;
        Axis[i].OptionNum        =  0;
        }

    // initialise buttons
    for (i = 0; i < NUM_BUTTONS; i++)
        {
        Button[i].Pressed       = false;
        Button[i].OptionNum     = 0;
        }

    InitAxisDropDownList(ddlXaxis);
    InitAxisDropDownList(ddlYaxis);

    if ((jcJoyCaps.wCaps & JOYCAPS_HASZ) == JOYCAPS_HASZ) { chkZaxis->Checked = true; chkZaxis->Enabled = true; InitAxisDropDownList(ddlZaxis); }
    if ((jcJoyCaps.wCaps & JOYCAPS_HASR) == JOYCAPS_HASR) { chkRaxis->Checked = true; chkRaxis->Enabled = true; InitAxisDropDownList(ddlRaxis); }
    if ((jcJoyCaps.wCaps & JOYCAPS_HASU) == JOYCAPS_HASU) { chkUaxis->Checked = true; chkUaxis->Enabled = true; InitAxisDropDownList(ddlUaxis); }
    if ((jcJoyCaps.wCaps & JOYCAPS_HASV) == JOYCAPS_HASV) { chkVaxis->Checked = true; chkVaxis->Enabled = true; InitAxisDropDownList(ddlVaxis);	}

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

    // after all that hard work, try and load the settings from the .ini file
    if (frmOrb->ReadSettings(regSettings->IniFileName) == true)
        {
        frmOrb->InitInterface();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::mnuSaveClick(TObject *Sender)
{
int     i = 0;
bool	WasError = false;

// stuff here to save settings
for (i = 0; i < NUM_AXES; i++)
    {
    regSettings->WriteString(chkAxisName   		[i], "enabled"   , AnsiString::AnsiString((int ) Axis[i].Enabled           ));     OW_HANDLE_REG_ERROR;
	regSettings->WriteString(chkAxisSenseName 	[i], "enabled"   , AnsiString::AnsiString((int ) Axis[i].OppSense          ));     OW_HANDLE_REG_ERROR;
    regSettings->WriteString(ddlAxisName   		[i], "normal"    , AnsiString::AnsiString((int ) Axis[i].OptionNum         ));     OW_HANDLE_REG_ERROR;
    regSettings->WriteString(sedAxisName   		[i], "threshold" , AnsiString::AnsiString((int ) Axis[i].Threshold         ));     OW_HANDLE_REG_ERROR;
    }

for (i = 0; i < NUM_BUTTONS; i++)
    {
    regSettings->WriteString(chkButtonName[i], "enabled", AnsiString::AnsiString((int ) Button[i].Enabled          ));     OW_HANDLE_REG_ERROR;
    regSettings->WriteString(ddlButtonName[i], "normal" , AnsiString::AnsiString((int ) Button[i].OptionNum        ));     OW_HANDLE_REG_ERROR;
    }

regSettings->WriteString("ComPort", "port", AnsiString::AnsiString((int ) ddlComPort->ItemIndex));    OW_HANDLE_REG_ERROR;

regSettings->WriteString("Update", "freq", AnsiString::AnsiString((int ) sedUpdateFreq->Value));    OW_HANDLE_REG_ERROR;

regSettings->WriteString("StartMin", "minimised", AnsiString::AnsiString((int ) chkStartMin->Checked));    OW_HANDLE_REG_ERROR;

regSettings->WriteString("AutoSave", "enabled" , AnsiString::AnsiString((int ) sedAutoSaveInt->Enabled));    OW_HANDLE_REG_ERROR;
regSettings->WriteString("AutoSave", "interval", AnsiString::AnsiString((int ) sedAutoSaveInt->Value  ));    OW_HANDLE_REG_ERROR;

CLEAN_UP:
    ;

if (WasError == true)
    {
    Application->MessageBox(regSettings->ErrorMessage.c_str(), "Error", MB_OK);
    }

}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::mnuContentsClick(TObject *Sender)
{
WinExec(
    AnsiString::AnsiString(
        AnsiString::AnsiString("winhlp32 ") +
        Application->HelpFile).c_str(),
        SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::mnuAboutClick(TObject *Sender)
{
frmAbout->Caption 					= Application->Title;
frmAbout->lblProductName->Caption 	= "Product Name:   " + Application->Title;
frmAbout->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::mnuExitClick(TObject *Sender)
{
frmOrb->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkXaxisClick(TObject *Sender)
{
ddlXaxis       ->Enabled = chkXaxis->Checked;
sedXaxis       ->Enabled = chkXaxis->Checked;
chkXsense      ->Enabled = chkXaxis->Checked;

Axis[0]        . Enabled = chkXaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkYaxisClick(TObject *Sender)
{
ddlYaxis    ->Enabled = chkYaxis->Checked;
sedYaxis    ->Enabled = chkYaxis->Checked;
chkYsense   ->Enabled = chkYaxis->Checked;

Axis[1]		. Enabled = chkYaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkZaxisClick(TObject *Sender)
{
ddlZaxis    ->Enabled = chkZaxis->Checked;
sedZaxis    ->Enabled = chkZaxis->Checked;
chkZsense   ->Enabled = chkZaxis->Checked;

Axis[2]		. Enabled = chkZaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkRaxisClick(TObject *Sender)
{
ddlRaxis       ->Enabled = chkRaxis->Checked;
sedRaxis       ->Enabled = chkRaxis->Checked;
chkRsense      ->Enabled = chkRaxis->Checked;

Axis[3]        . Enabled = chkRaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkUaxisClick(TObject *Sender)
{
ddlUaxis       ->Enabled = chkUaxis->Checked;
sedUaxis       ->Enabled = chkUaxis->Checked;
chkUsense      ->Enabled = chkUaxis->Checked;

Axis[4]        . Enabled = chkUaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkVaxisClick(TObject *Sender)
{
ddlVaxis       ->Enabled = chkVaxis->Checked;
sedVaxis       ->Enabled = chkVaxis->Checked;
chkVsense      ->Enabled = chkVaxis->Checked;

Axis[5]        . Enabled = chkVaxis->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkButton1Click(TObject *Sender)
{
ddlButton1->Enabled = chkButton1->Checked;
Button[0]  .Enabled = chkButton1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkButton2Click(TObject *Sender)
{
ddlButton2->Enabled = chkButton2->Checked;
Button[1]  .Enabled = chkButton2->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkButton3Click(TObject *Sender)
{
ddlButton3->Enabled = chkButton3->Checked;
Button[2]  .Enabled = chkButton3->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkButton4Click(TObject *Sender)
{
ddlButton4->Enabled = chkButton4->Checked;
Button[3]  .Enabled = chkButton4->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkButton5Click(TObject *Sender)
{
ddlButton5->Enabled = chkButton5->Checked;
Button[4]  .Enabled = chkButton5->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkButton6Click(TObject *Sender)
{
ddlButton6->Enabled = chkButton6->Checked;
Button[5]  .Enabled = chkButton6->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlXaxisChange(TObject *Sender)
{
Axis[0].OptionNum = ddlXaxis->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlYaxisChange(TObject *Sender)
{
Axis[1].OptionNum = ddlYaxis->ItemIndex;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlZaxisChange(TObject *Sender)
{
Axis[2].OptionNum = ddlZaxis->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlRaxisChange(TObject *Sender)
{
Axis[3].OptionNum = ddlRaxis->ItemIndex;   

}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlUaxisChange(TObject *Sender)
{
Axis[4].OptionNum = ddlUaxis->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlVaxisChange(TObject *Sender)
{
Axis[5].OptionNum = ddlVaxis->ItemIndex;   

}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlButton1Change(TObject *Sender)
{
Button[0].OptionNum = ddlButton1->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlButton2Change(TObject *Sender)
{
Button[1].OptionNum = ddlButton2->ItemIndex;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlButton3Change(TObject *Sender)
{
Button[2].OptionNum = ddlButton3->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlButton4Change(TObject *Sender)
{
Button[3].OptionNum = ddlButton4->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlButton5Change(TObject *Sender)
{
Button[4].OptionNum = ddlButton5->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlButton6Change(TObject *Sender)
{
Button[5].OptionNum = ddlButton6->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::sedXaxisChange(TObject *Sender)
{
Axis[0].Threshold = sedXaxis->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::sedYaxisChange(TObject *Sender)
{
Axis[1].Threshold = sedYaxis->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::sedZaxisChange(TObject *Sender)
{
Axis[2].Threshold = sedZaxis->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::sedRaxisChange(TObject *Sender)
{
Axis[3].Threshold = sedRaxis->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::sedUaxisChange(TObject *Sender)
{
Axis[4].Threshold = sedUaxis->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::sedVaxisChange(TObject *Sender)
{
Axis[5].Threshold = sedVaxis->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::mnuOpenClick(TObject *Sender)
{
if (dlgOpen->Execute() == true)
    {
    frmOrb->ReadSettings(dlgOpen->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::mnuSaveAsClick(TObject *Sender)
{
if (dlgSave->Execute() == true)
    {
    // stuff here to save settings under a different name
    regSettings->IniFileName = dlgSave->FileName;
    frmOrb->mnuSaveClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::Comm32RxCharSignal(TObject *Sender, int Count)
{
char	Data[1024],
		SpaceWare[] = "SpaceWare!";
        
int		R, i, t[3], r[3];

memset(Data, 0, sizeof(Data));
R = Comm32->Read(Data, Count);

if (Data[0] == '\r')
	{
	//R packet
    R += Comm32->Read(Data + R, 52 - R);

    for (i = 0; i < R; ++i)
        {
    	Data[i] &= 0177;
    	if (Data[i] == '\r')
    		Data[i] = '\n';
        }
	Data[R] = '\0';

    // if Orb detected
	bOrbPresent = true;
    }

if (Data[0] == 'K')
	{
	//K packet

	// check out buttons first
	switch (Data[2] & 0177)
		{
    	case	 1:		/*Button A*/ pjiJoyInfo.dwFlags |= JOY_RETURNBUTTONS; pjiJoyInfo.dwButtons |= JOY_BUTTON1; break;
    	case	 2:		/*Button B*/ pjiJoyInfo.dwFlags |= JOY_RETURNBUTTONS; pjiJoyInfo.dwButtons |= JOY_BUTTON2; break;
    	case	 4:		/*Button C*/ pjiJoyInfo.dwFlags |= JOY_RETURNBUTTONS; pjiJoyInfo.dwButtons |= JOY_BUTTON3; break;
    	case	 8:		/*Button D*/ pjiJoyInfo.dwFlags |= JOY_RETURNBUTTONS; pjiJoyInfo.dwButtons |= JOY_BUTTON4; break;
    	case	16:		/*Button E*/ pjiJoyInfo.dwFlags |= JOY_RETURNBUTTONS; pjiJoyInfo.dwButtons |= JOY_BUTTON5; break;
    	case	32:		/*Button F*/ pjiJoyInfo.dwFlags |= JOY_RETURNBUTTONS; pjiJoyInfo.dwButtons |= JOY_BUTTON6; break;
    	case	64:		/*Button R*/ pjiJoyInfo.dwFlags |= JOY_RETURNBUTTONS; pjiJoyInfo.dwButtons |= JOY_BUTTON7; break;
    	}
    }

if (R == 8)
	{
	//D packet
	/* Strip the MSB, which is a parity bit */
	for (i = 0; i < 8; i++)
		{
    	Data[i] &= 0177;           /* Make sure everything is 7 bit */
    	Data[i] ^= SpaceWare[i];   /* What's this doing in the data? */
    	}

	/* Turn chars into 10 bit integers */
	t[0] = ((Data[0] & 0177) << 3) | ((Data[1] & 0160) >> 4);
	t[1] = ((Data[1] & 0017) << 6) | ((Data[2] & 0176) >> 1);
	t[2] = ((Data[2] & 0001) << 9) | ((Data[3] & 0177) << 2) | ((Data[4] & 0140) >> 5);
	r[0] = ((Data[4] & 0037) << 5) | ((Data[5] & 0174) >> 2);
	r[1] = ((Data[5] & 0003) << 8) | ((Data[6] & 0177) << 1) | ((Data[7] & 0100) >> 6);
	r[2] = ((Data[7] & 0077) << 4) | ((Data[8] & 0170) >> 3);

	/* Get the sign right. */
	for(i = 0; i < 3; i ++)
		{
	    if (t[i] > 511)
    		t[i] -= 1024;
    	}

	for (i = 0; i < 3; i ++)
		{
	    if (r[i] > 511)
    		r[i] -= 1024;
	    }

    // convert SpaceOrb axes info to equivalent joystick info
    pjiJoyInfo.dwXpos = -t[0] + 512;	pjiJoyInfo.dwFlags |= JOY_RETURNX;
    pjiJoyInfo.dwYpos = -t[1] + 512;	pjiJoyInfo.dwFlags |= JOY_RETURNY;
    pjiJoyInfo.dwZpos = -t[2] + 512;	pjiJoyInfo.dwFlags |= JOY_RETURNZ;

    pjiJoyInfo.dwRpos = -r[0] + 512;	pjiJoyInfo.dwFlags |= JOY_RETURNR;
    pjiJoyInfo.dwUpos = -r[1] + 512;	pjiJoyInfo.dwFlags |= JOY_RETURNU;
    pjiJoyInfo.dwVpos = -r[2] + 512;	pjiJoyInfo.dwFlags |= JOY_RETURNV;
    }

// flush serial buffer
Comm32->PurgeIn();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::ddlComPortChange(TObject *Sender)
{
Comm32->Close();
Comm32->DeviceName = ddlComPort->Items->Strings[ddlComPort->ItemIndex];
Comm32->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkAutoSaveIntClick(TObject *Sender)
{
sedAutoSaveInt->Enabled = chkAutoSaveInt->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::FormDestroy(TObject *Sender)
{
Comm32->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::sedUpdateFreqChange(TObject *Sender)
{
tmrOrb->Interval = sedUpdateFreq->Value;

tmrOrb->Interval =  (tmrOrb->Interval > jcJoyCaps.wPeriodMax)
                            ? jcJoyCaps.wPeriodMax : tmrOrb->Interval;

tmrOrb->Interval =  (tmrOrb->Interval < jcJoyCaps.wPeriodMin)
                            ? jcJoyCaps.wPeriodMin : tmrOrb->Interval;

sedUpdateFreq->Value = tmrOrb->Interval;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::tmrOrbTimer(TObject *Sender)
{
EnumWindows((WNDENUMPROC ) OrbWorksEnumFunc, (LPARAM ) 1);
if (bSW_Running == true)
	{
    JOYINFOEX 			pjiTempJoyInfo;

    memcpy(&pjiTempJoyInfo, &pjiJoyInfo, sizeof(JOYINFOEX));
    CalculateOrb(pjiTempJoyInfo, jcJoyCaps, Button, Axis);
    ProcessOrb  (pjiTempJoyInfo, jcJoyCaps, Button, Axis);
    }

// reset joystick info
memset(&pjiJoyInfo, 0, sizeof(JOYINFOEX));
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrb::chkXsenseClick(TObject *Sender)
{
Axis[0].OppSense = chkXsense->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkYsenseClick(TObject *Sender)
{
Axis[1].OppSense = chkYsense->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkZsenseClick(TObject *Sender)
{
Axis[2].OppSense = chkZsense->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkRsenseClick(TObject *Sender)
{
Axis[3].OppSense = chkRsense->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkUsenseClick(TObject *Sender)
{
Axis[4].OppSense = chkUsense->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::chkVsenseClick(TObject *Sender)
{
Axis[5].OppSense = chkVsense->Checked;	
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrb::mnuRegisterClick(TObject *Sender)
{
frmCodeGen->ShowModal();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrb::tmrSecurityTimer(TObject *Sender)
{
// if haven't been disabled during initialisation then close the app
Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrb::tmrRedrawTimer(TObject *Sender)
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

void __fastcall TfrmOrb::tmrWindowTimer(TObject *Sender)
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

void __fastcall TfrmOrb::tmrEnumTimer(TObject *Sender)
{
// reset flags for joystick panel and SW
bJoystick_Running = true;
bSW_Running = false;

// now try and find SW
EnumWindows((WNDENUMPROC ) OrbWorksEnumFunc, (LPARAM ) 1);
}
//---------------------------------------------------------------------------

