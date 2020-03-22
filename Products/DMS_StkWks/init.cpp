//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "init.h"
#include "main.h"
//---------------------------------------------------------------------------
struct OptionType Option[NUM_OPTIONS] =
    {
    //Text
    {"Translate Minus X"            },
    {"Translate Plus X"             },

    {"Translate Minus Y"            },
    {"Translate Plus Y"             },

    {"Rotate Minus X"               },
    {"Rotate Plus X"                },

    {"Rotate Minus Y"               },
    {"Rotate Plus Y"                },

    {"Rotate Minus Z"               },
    {"Rotate Plus Z"                },

    {"Zoom Out"                     },
    {"Zoom In"                      },
    {"Zoom To Fit"                  },

    {"Display Hidden Greyed"        },
    {"Display Hidden Removed"       },
    {"Display Shaded"               },
    {"Display Wireframe"            },
    {"Display Faceted"              },

    {"New Part"                     },
    {"New Assembly"                 },
    {"New Drawing"                  },

    {"Cascade Windows"              },      // cascade windows
    {"Tile Windows"                 },      // tile windows
    {"New Window"                   },
    {"Graphics Redraw"              },
    {"Window Redraw"                },

    {"Rebuild Part"                 },
    {"Rebuild Assembly"             },
    {"Rebuild Drawing"              },

    {"Explode Assembly"             },
    {"Collapse Assembly"            },
    {"Check Interference"           },
    {"Edit Part"                    },

    {"Disp Ref Axes"                },
    {"Disp Ref Planes"              },

    {"Move Component"               },
    {"Rotate Component"             },

    {"Save"                         },

    {"Modifier"                     },
    {"No Action"                    },
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
    {"No Action",                   {&Option[39]},         {&Option[39]}},
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

for (i = 0; i < NUM_BUTTON_OPTS; i++)
    {
    ddlButton->Items->Add(ButtonOption[i].Option->Text);
    }

// initialise list to the first item, for the moment
ddlButton->ItemIndex = 0;
}
//---------------------------------------------------------------------------
bool TfrmJoystick::ReadSettings(void)
{
bool        bReturn  = false,
            WasError = false;

struct ButtonType   TempButton  [NUM_BUTTONS];
struct ButtonType   TempPOV     [NUM_POV    ];
struct AxisType     TempAxis    [NUM_AXES   ];

bool                bEnabled,
                    bOppSense;
int                 nOptionNum,
                    nModOptionNum,
                    Threshold,
                    Sensitivity;

char                MachineID[MAX_PATH];
AnsiString          CodeStr;
int                 i;

// stuff here to load settings
for (i = 0; i < NUM_AXES; i++)
    {
    bEnabled        = atoi(regSettings->ReadString(chkAxisName      [i], "enabled"       ).c_str());     SW_HANDLE_REG_ERROR;
    bOppSense       = atoi(regSettings->ReadString(chkAxisSenseName [i], "enabled"       ).c_str());     SW_HANDLE_REG_ERROR;
    nOptionNum      = atoi(regSettings->ReadString(ddlAxisName      [i], "normal"        ).c_str());     SW_HANDLE_REG_ERROR;
    nModOptionNum   = atoi(regSettings->ReadString(ddlModAxisName   [i], "normal mod"    ).c_str());     SW_HANDLE_REG_ERROR;
    Threshold       = atoi(regSettings->ReadString(sedAxisName      [i], "threshold"     ).c_str());     SW_HANDLE_REG_ERROR;
    Sensitivity     = atoi(regSettings->ReadString(sedAxisSensName  [i], "sensitivity"   ).c_str());     SW_HANDLE_REG_ERROR;

    TempAxis[i].Enabled         = bEnabled     ;
    TempAxis[i].OppSense        = bOppSense    ;
    TempAxis[i].OptionNum       = nOptionNum   ;
    TempAxis[i].ModOptionNum    = nModOptionNum;
    TempAxis[i].Threshold       = Threshold    ;
    TempAxis[i].Sensitivity     = Sensitivity  ;
    }

for (i = 0; i < NUM_BUTTONS; i++)
    {
    TempButton[i].Enabled       = atoi(regSettings->ReadString(chkButtonName[i], "enabled"     ).c_str());     SW_HANDLE_REG_ERROR;
    TempButton[i].OptionNum     = atoi(regSettings->ReadString(ddlButtonName[i], "normal"      ).c_str());     SW_HANDLE_REG_ERROR;
    }

sedPollFreq->Value = atoi(regSettings->ReadString("Poll", "freq"        ).c_str());         SW_HANDLE_REG_ERROR;

if ((jcJoyCaps.wCaps & JOYCAPS_HASPOV) == JOYCAPS_HASPOV)
    {
    for (i = 0; i < NUM_POV; i++)
        {
        TempPOV[i].Enabled       = atoi(regSettings->ReadString(chkPOVName[i], "enabled"     ).c_str());     SW_HANDLE_REG_ERROR;
        TempPOV[i].OptionNum     = atoi(regSettings->ReadString(ddlPOVName[i], "normal"      ).c_str());     SW_HANDLE_REG_ERROR;
        }
    }

CLEAN_UP:
    ;

if (WasError == true)
    {
    stbJoystick->SimpleText = "Error:  " + regSettings->ErrorMessage;
    }
else
    {
    // copy over the new settings
    memcpy(Button, TempButton, NUM_BUTTONS    * sizeof(struct ButtonType));
    memcpy(POV   , TempPOV   , NUM_POV        * sizeof(struct ButtonType));
    memcpy(Axis  , TempAxis  , NUM_AXES       * sizeof(struct AxisType  ));

    bReturn = true;
    }

return bReturn;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::InitInterface(void)
{
int                i = 0;

// initialise axes check boxes, drop down lists, modified drop down lists and thresholds
for (i = 0; i < NUM_AXES; i++)
       {
    dynamic_cast<TCheckBox  *>(FindComponent(chkAxisName   [i]))->Checked         = Axis[i].Enabled        ;
    dynamic_cast<TComboBox  *>(FindComponent(ddlAxisName   [i]))->ItemIndex     = Axis[i].OptionNum        ;
    dynamic_cast<TComboBox  *>(FindComponent(ddlModAxisName[i]))->ItemIndex     = Axis[i].ModOptionNum    ;
    dynamic_cast<TCSpinEdit *>(FindComponent(sedAxisName   [i]))->Value         = Axis[i].Threshold        ;
    }

// initialise button check boxes and drop down lists
for (i = 0; i < NUM_BUTTONS; i++)
       {
    dynamic_cast<TCheckBox *>(FindComponent(chkButtonName [i]))->Checked     = Button[i].Enabled        ;
    dynamic_cast<TComboBox *>(FindComponent(ddlButtonName [i]))->ItemIndex  = Button[i].OptionNum    ;
    }

// initialise POV check boxes and drop down lists
for (i = 0; i < NUM_POV; i++)
       {
    dynamic_cast<TCheckBox *>(FindComponent(chkPOVName [i]))->Checked      = POV[i].Enabled   ;
    dynamic_cast<TComboBox *>(FindComponent(ddlPOVName [i]))->ItemIndex  = POV[i].OptionNum    ;
    }
}
//---------------------------------------------------------------------------


