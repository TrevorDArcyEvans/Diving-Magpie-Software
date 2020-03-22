//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

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
struct OptionType Option[NUM_OPTIONS] =
    {
    //Text                          SW_OleType          SW_OleProcName                  SW_OleNumParam      SW_Param1
    {"Translate Minus X",           TYPE_DOC,           "ViewTranslateminusx",          0,                  0},
    {"Translate Plus X",            TYPE_DOC,           "ViewTranslateplusx",           0,                  0},

    {"Translate Minus Y",           TYPE_DOC,           "ViewTranslateminusy",          0,                  0},
    {"Translate Plus Y",            TYPE_DOC,           "ViewTranslateplusy",           0,                  0},

    {"Rotate Minus X",              TYPE_DOC,           "ViewRotateminusx",             0,                  0},
    {"Rotate Plus X",               TYPE_DOC,           "ViewRotateplusx",              0,                  0},

    {"Rotate Minus Y",              TYPE_DOC,           "ViewRotateminusy",             0,                  0},
    {"Rotate Plus Y",               TYPE_DOC,           "ViewRotateplusy",              0,                  0},

    {"Rotate Minus Z",              TYPE_DOC,           "ViewRotateminusz",             0,                  0},
    {"Rotate Plus Z",               TYPE_DOC,           "ViewRotateplusz",              0,                  0},

    {"Zoom Out",                    TYPE_DOC,           "ViewZoomout",                  0,                  0},
    {"Zoom In",                     TYPE_DOC,           "ViewZoomin",                   0,                  0},
    {"Zoom To Fit",                 TYPE_DOC,           "ViewZoomtofit",                0,                  0},

    {"Display Hidden Greyed",       TYPE_DOC,           "ViewDisplayHiddenGreyed",      0,                  0},
    {"Display Hidden Removed",      TYPE_DOC,           "ViewDisplayHiddenRemoved",     0,                  0},
    {"Display Shaded",              TYPE_DOC,           "ViewDisplayShaded",            0,                  0},
    {"Display Wireframe",           TYPE_DOC,           "ViewDisplayWireframe",         0,                  0},
    {"Display Faceted",             TYPE_DOC,           "ViewDisplayFaceted",           0,                  0},

    {"New Part",                    TYPE_APP,           "NewPart",                      0,                  0},
    {"New Assembly",                TYPE_APP,           "NewAssembly",                  0,                  0},
    {"New Drawing",                 TYPE_APP,           "NewDrawing",                   1,                  1},

    {"Cascade Windows",             TYPE_APP,           "ArrangeWindows",               1,                  0},     // cascade windows
    {"Tile Windows",                TYPE_APP,           "ArrangeWindows",               1,                  1},     // tile windows
    {"New Window",                  TYPE_APP,           "CreateNewWindow",              0,                  0},
    {"Graphics Redraw",             TYPE_DOC,           "GraphicsRedraw",               0,                  0},
    {"Window Redraw",               TYPE_DOC,           "WindowRedraw",                 0,                  0},

    {"Rebuild Part",                TYPE_DOC,           "EditRebuild",                  0,                  0},
    {"Rebuild Assembly",            TYPE_DOC,           "EditRebuild",                  0,                  0},
    {"Rebuild Drawing",             TYPE_DOC,           "EditRebuild",                  0,                  0},

    {"Explode Assembly",            TYPE_ASS,           "ViewExplodeAssembly",          0,                  0},
    {"Collapse Assembly",           TYPE_ASS,           "ViewCollapseAssembly",         0,                  0},
    {"Check Interference",          TYPE_ASS,           "ToolsCheckInterference",       0,                  0},
    {"Edit Part",                   TYPE_ASS,           "EditPart",                     0,                  0},

    {"Disp Ref Axes",               TYPE_DOC,           "ViewDispRefaxes",              0,                  0},
    {"Disp Ref Planes",             TYPE_DOC,           "ViewDispRefplanes",            0,                  0},

    {"Move Component",              TYPE_ASS,           "MoveComponent",                0,                  0},
    {"Rotate Component",            TYPE_ASS,           "RotateComponent",              0,                  0},

    {"Save",                        TYPE_DOC,           "Save",                         0,                  0},

    {"Modifier",                    -1,       			"",                             0,                  0},
    {"No Action",                   -1,       			"",                             0,                  0},
    };

//---------------------------------------------------------------------------
struct ButtonOptionType ButtonOption[NUM_BUTTON_OPTS] =
    {
    // Option
    {&Option[ 0]},
    {&Option[ 1]},
    {&Option[ 2]},
    {&Option[ 3]},
    {&Option[ 4]},
    {&Option[ 5]},
    {&Option[ 6]},
    {&Option[ 7]},
    {&Option[ 8]},
    {&Option[ 9]},

    {&Option[10]},
    {&Option[11]},
    {&Option[12]},
    {&Option[13]},
    {&Option[14]},
    {&Option[15]},
    {&Option[16]},
    {&Option[17]},
    {&Option[18]},
    {&Option[19]},

    {&Option[20]},
    {&Option[21]},
    {&Option[22]},
    {&Option[23]},
    {&Option[24]},
    {&Option[25]},
    {&Option[26]},
    {&Option[27]},
    {&Option[28]},
    {&Option[29]},

    {&Option[30]},
    {&Option[31]},
    {&Option[32]},
    {&Option[33]},
    {&Option[34]},
    {&Option[35]},
    {&Option[36]},
    {&Option[37]},
    {&Option[38]},
    {&Option[39]},
    };
//---------------------------------------------------------------------------
struct AxisOptionType AxisOption[NUM_AXIS_OPTS] =
    {
    //Text                          OptionMinus            OptionPlus
    {"View Translate X",            {&Option[ 0]},         {&Option[ 1]}},
    {"View Translate Y",            {&Option[ 2]},         {&Option[ 3]}},

    {"View Rotate X",               {&Option[ 4]},         {&Option[ 5]}},
    {"View Rotate Y",               {&Option[ 6]},         {&Option[ 7]}},
    {"View Rotate Z",               {&Option[ 8]},         {&Option[ 9]}},

    {"Zoom",                        {&Option[10]},         {&Option[11]}},
    {"No Action",                	{&Option[39]},         {&Option[39]}},
    };
//---------------------------------------------------------------------------
void     InitAxisDropDownList(
            TComboBox        *ddlAxis)
{
int i = 0;

ddlAxis->Items->Clear();

for(i = 0; i < NUM_AXIS_OPTS; i++)
    {
    ddlAxis->Items->Add(AxisOption[i].Text);
    }

// initialise list to the first item, for the moment
ddlAxis->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void     InitButtonDropDownList(
            TComboBox        *ddlButton)
{
int i = 0;

ddlButton->Items->Clear();

for(i = 0; i < NUM_BUTTON_OPTS; i++)
    {
    ddlButton->Items->Add(ButtonOption[i].Option->Text);
    }

// initialise list to the first item, for the moment
ddlButton->ItemIndex = 0;
}
//---------------------------------------------------------------------------
bool TfrmOrb::ReadSettings(
				AnsiString			IniFileName)
{
bool		bReturn  = false,
            WasError = false;

// stuff here to load settings
regSettings->IniFileName = IniFileName;

struct ButtonType	*TempButton = NULL;
struct AxisType		*TempAxis   = NULL;

char                MachineID[MAX_PATH];
AnsiString          CodeStr;

// allocate some memory to hold the temporary settings as we read them from the file
TempButton = (struct ButtonType *) malloc(NUM_BUTTONS	* sizeof(struct ButtonType));
TempAxis   = (struct AxisType   *) malloc(NUM_AXES		* sizeof(struct AxisType  ));

if ((TempButton != NULL) &&
	(TempAxis	!= NULL))
    {
    // copy old settings into temporary settings
    memcpy(TempButton, Button, NUM_BUTTONS	* sizeof(struct ButtonType));
    memcpy(TempAxis  , Axis	 , NUM_AXES		* sizeof(struct AxisType  ));

    int i;

    for (i = 0; i < NUM_AXES; i++)
    	{
    	TempAxis[i].Enabled         = atoi(regSettings->ReadString(chkAxisName   	[i], "enabled"       ).c_str());     OW_HANDLE_REG_ERROR;
    	TempAxis[i].OppSense        = atoi(regSettings->ReadString(chkAxisSenseName [i], "enabled"       ).c_str());     OW_HANDLE_REG_ERROR;
    	TempAxis[i].OptionNum       = atoi(regSettings->ReadString(ddlAxisName   	[i], "normal"        ).c_str());     OW_HANDLE_REG_ERROR;
    	TempAxis[i].Threshold       = atoi(regSettings->ReadString(sedAxisName   	[i], "threshold"     ).c_str());     OW_HANDLE_REG_ERROR;
    	}

    for (i = 0; i < NUM_BUTTONS; i++)
    	{
    	TempButton[i].Enabled       = atoi(regSettings->ReadString(chkButtonName[i], "enabled"     ).c_str());     OW_HANDLE_REG_ERROR;
        TempButton[i].OptionNum     = atoi(regSettings->ReadString(ddlButtonName[i], "normal"      ).c_str());     OW_HANDLE_REG_ERROR;
	    }

    ddlComPort->ItemIndex = atoi(regSettings->ReadString("ComPort", "port" ).c_str());
    ddlComPortChange(this);

    sedUpdateFreq->Value = atoi(regSettings->ReadString("Update", "freq"        ).c_str());    OW_HANDLE_REG_ERROR;

    chkStartMin->Checked = atoi(regSettings->ReadString("StartMin", "minimised" ).c_str());    OW_HANDLE_REG_ERROR;
	frmOrb->WindowState = (chkStartMin->Checked == true) ? wsMinimized : wsNormal;

    chkAutoSaveInt->Checked = atoi(regSettings->ReadString("AutoSave", "enabled" ).c_str());    OW_HANDLE_REG_ERROR;
    sedAutoSaveInt->Value   = atoi(regSettings->ReadString("AutoSave", "interval").c_str());    OW_HANDLE_REG_ERROR;

    // timer is enabled by default, the only way to disable the timer is
    // to load an *.ini file with a correct security code.  This will generally
    // be OrbWorks.ini
    strcpy(MachineID, GetMachineID());
    CodeStr = regSettings->ReadString("Security", "code");
    if (CheckCode(MachineID, ORB_WORKS_TITLE_CODE, CodeStr.c_str()) == true)
        {
        // security passed, disable timer and menu item
        tmrSecurity->Enabled = false;
        mnuRegister->Enabled = false;
        }

    CLEAN_UP:
    	;

    if (WasError == true)
    	{
        stbOrb->SimpleText = "Error:  " + regSettings->ErrorMessage;
        }
    else
    	{
    	// copy over the new settings
        memcpy(Button, TempButton, NUM_BUTTONS	* sizeof(struct ButtonType));
        memcpy(Axis  , TempAxis	 , NUM_AXES		* sizeof(struct AxisType  ));

		bReturn = true;
        }

    // free the memory we've allocated
    if (TempButton 	!= NULL) { free(TempButton); }
    if (TempAxis 	!= NULL) { free(TempAxis  ); }
    }
else
	{
    Application->MessageBox("Out of memory", "Error", MB_OK);

	bReturn = false;
    }

return bReturn;
}
//---------------------------------------------------------------------------
void	TfrmOrb::InitInterface(void)
{
int				i = 0;

// initialise axes check boxes, drop down lists, thresholds and sense check boxes
for (i = 0; i < NUM_AXES; i++)
   	{
	dynamic_cast<TCheckBox  *>(FindComponent(chkAxisName   	[i]))->Checked 		= Axis[i].Enabled		;
	dynamic_cast<TCheckBox  *>(FindComponent(chkAxisSenseName[i]))->Checked 		= Axis[i].OppSense		;
	dynamic_cast<TComboBox  *>(FindComponent(ddlAxisName   	[i]))->ItemIndex 	= Axis[i].OptionNum		;
	dynamic_cast<TCSpinEdit *>(FindComponent(sedAxisName   	[i]))->Value 		= Axis[i].Threshold		;
    }

// initialise button check boxes and drop down lists
for (i = 0; i < NUM_BUTTONS; i++)
   	{
	dynamic_cast<TCheckBox *>(FindComponent(chkButtonName [i]))->Checked 	= Button[i].Enabled		;
	dynamic_cast<TComboBox *>(FindComponent(ddlButtonName [i]))->ItemIndex  = Button[i].OptionNum	;
    }
}
//---------------------------------------------------------------------------


