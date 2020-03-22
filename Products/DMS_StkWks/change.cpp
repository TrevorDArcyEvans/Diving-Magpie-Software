//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "init.h"
#include "main.h"
//---------------------------------------------------------------------------
void    TfrmJoystick::CheckAxisClick      (int  nIndex)
{
TCheckBox       *pchkAxis       = dynamic_cast<TCheckBox  *>(FindComponent(chkAxisName      [nIndex]));
TComboBox       *pddlAxis       = dynamic_cast<TComboBox  *>(FindComponent(ddlAxisName      [nIndex]));
TComboBox       *pddlModAxis    = dynamic_cast<TComboBox  *>(FindComponent(ddlModAxisName   [nIndex]));
TCSpinEdit      *psedAxis       = dynamic_cast<TCSpinEdit *>(FindComponent(sedAxisName      [nIndex]));
TCheckBox       *pchkSense      = dynamic_cast<TCheckBox  *>(FindComponent(chkAxisSenseName [nIndex]));
TCSpinEdit      *psedAxisSens   = dynamic_cast<TCSpinEdit *>(FindComponent(sedAxisSensName  [nIndex]));

bool            bEnabled        = pchkAxis->Checked;

pddlAxis    ->Enabled = bEnabled;
pddlModAxis ->Enabled = bEnabled;
psedAxis    ->Enabled = bEnabled;
pchkSense   ->Enabled = bEnabled;
psedAxisSens->Enabled = bEnabled;

Axis[nIndex].Enabled = pchkAxis->Checked;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::CheckSenseClick (int  nIndex)
{
TCheckBox       *pchkAxisSense  = dynamic_cast<TCheckBox  *>(FindComponent(chkAxisSenseName [nIndex]));

bool            bEnabled        = pchkAxisSense->Checked;

Axis[nIndex].OppSense = pchkAxisSense->Checked;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::CheckButtonClick    (int  nIndex)
{
TCheckBox       *pchkButton      = dynamic_cast<TCheckBox  *>(FindComponent(chkButtonName   [nIndex]));
TComboBox       *pddlButton      = dynamic_cast<TComboBox  *>(FindComponent(ddlButtonName   [nIndex]));

bool            bEnabled        = pchkButton->Checked;

pddlButton   ->Enabled = bEnabled;
Button[nIndex].Enabled = bEnabled;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::DDLAxisChange       (int  nIndex)
{
TComboBox       *pddlAxis       = dynamic_cast<TComboBox  *>(FindComponent(ddlAxisName      [nIndex]));

Axis[nIndex].OptionNum = pddlAxis->ItemIndex;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::DDLModAxisChange    (int  nIndex)
{
TComboBox       *pddlModAxis    = dynamic_cast<TComboBox  *>(FindComponent(ddlModAxisName   [nIndex]));

Axis[nIndex].ModOptionNum = pddlModAxis->ItemIndex;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::DDLButtonChange     (int  nIndex)
{
TComboBox       *pddlButton      = dynamic_cast<TComboBox  *>(FindComponent(ddlButtonName   [nIndex]));

Button[nIndex].OptionNum = pddlButton->ItemIndex;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::SEDAxisChange       (int  nIndex)
{
TCSpinEdit      *psedAxis       = dynamic_cast<TCSpinEdit *>(FindComponent(sedAxisName      [nIndex]));

Axis[nIndex].Threshold = psedAxis->Value;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::CheckPOVClick       (int  nIndex)
{
TCheckBox       *pchkPOV        = dynamic_cast<TCheckBox  *>(FindComponent(chkPOVName       [nIndex]));
TComboBox       *pddlPOV        = dynamic_cast<TComboBox  *>(FindComponent(ddlPOVName       [nIndex]));

bool            bEnabled        = pchkPOV->Checked;

pddlPOV         ->Enabled = bEnabled;
POV[nIndex]      .Enabled = bEnabled;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::DDLPOVChange        (int  nIndex)
{
TComboBox       *pddlPOV        = dynamic_cast<TComboBox  *>(FindComponent(ddlPOVName       [nIndex]));

POV[nIndex].OptionNum = pddlPOV->ItemIndex;

bDirty = true;
}
//---------------------------------------------------------------------------
void    TfrmJoystick::SEDAxisSensChange   (int  nIndex)
{
TCSpinEdit      *psedAxisSens   = dynamic_cast<TCSpinEdit *>(FindComponent(sedAxisSensName  [nIndex]));

Axis[nIndex].Sensitivity = psedAxisSens->Value;

bDirty = true;
}
//---------------------------------------------------------------------------

