//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "process.h"
//---------------------------------------------------------------------------
DWORD    ButtonFlag[NUM_BUTTONS] =
    {
    JOY_BUTTON1,
    JOY_BUTTON2,
    JOY_BUTTON3,
    JOY_BUTTON4,
    JOY_BUTTON5,
    JOY_BUTTON6,
    };

DWORD    AxisFlag[NUM_AXES] =
    {
    JOY_RETURNX,
    JOY_RETURNY,
    JOY_RETURNZ,
    JOY_RETURNR,
    JOY_RETURNU,
    JOY_RETURNV,
    };

DWORD    POVFlag[NUM_POV] =
    {
    JOY_POVFORWARD  ,
    JOY_POVBACKWARD ,
    JOY_POVLEFT     ,
    JOY_POVRIGHT    ,
    };
//---------------------------------------------------------------------------
void    TfrmJoystick :: CalculateJoystick(
                JOYINFOEX               &pji_ex,
                JOYCAPS                 &pjc_jc,
                struct ButtonType       *Button,
                struct AxisType        *Axis)
{
DWORD           i = 0;

float           Value = 0,
                Max =  100,
                Min = -100;

// if there is valid button information
if ((pji_ex.dwFlags & JOY_RETURNBUTTONS) == JOY_RETURNBUTTONS)
    {
    // then for each button
    for (i = 0; i < NUM_BUTTONS; i++)
        {
        // if it is enabled
        if (Button[i].Enabled == true)
            {
            // and if it is pressed
            if ((pji_ex.dwButtons & ButtonFlag[i]) == ButtonFlag[i])
                {
                // set the button pressed flag for that button
                Button[i].Pressed = true;
                }
            else
                {
                // otherwise clear the button pressed flag for that button
                Button[i].Pressed = false;
                }
            }
        }
    }

// if there is valid hat information
// and a hat
if ((pji_ex.dwFlags  & JOY_RETURNPOV ) == JOY_RETURNPOV  &&
    (jcJoyCaps.wCaps & JOYCAPS_HASPOV) == JOYCAPS_HASPOV )
    {
    // then for each POV direction
    for (i = 0; i < NUM_POV; i++)
        {
        // if it is enabled
        if (POV[i].Enabled == true)
            {
            // and if it is pressed
            if (pji_ex.dwPOV == POVFlag[i])
                {
                // set the POV pressed flag for that direction
                POV[i].Pressed = true;
                }
            else
                {
                // otherwise clear the POV pressed flag for that direction
                POV[i].Pressed = false;
                }
            }
        }
    }

// for each joystick axis
for (i = 0; i < NUM_AXES; i++)
    {
    // if it is enabled
    if (Axis[i].Enabled == true)
        {
        // and if there is valid axis information
        if ((pji_ex.dwFlags & AxisFlag[i]) == AxisFlag[i])
            {
            // get the raw axis position, min and max values
            // based on which axis we're considering
            switch (i)
                {
                case 0    :  Value = pji_ex.dwXpos; Min = pjc_jc.wXmin; Max = pjc_jc.wXmax; break;
                case 1    :  Value = pji_ex.dwYpos; Min = pjc_jc.wYmin; Max = pjc_jc.wYmax; break;
                case 2    :  Value = pji_ex.dwZpos; Min = pjc_jc.wZmin; Max = pjc_jc.wZmax; break;
                case 3    :  Value = pji_ex.dwRpos; Min = pjc_jc.wRmin; Max = pjc_jc.wRmax; break;
                case 4    :  Value = pji_ex.dwUpos; Min = pjc_jc.wUmin; Max = pjc_jc.wUmax; break;
                case 5    :  Value = pji_ex.dwVpos; Min = pjc_jc.wVmin; Max = pjc_jc.wVmax; break;
                }
            // normalise axis value to the range +/- MAX_AXIS_VALUE
            Axis[i].Value = - MAX_AXIS_VALUE * (Value - (Max - Min) / 2) / (Max - Min);

            // adjust for sense of axis
            Axis[i].Value *= (Axis[i].OppSense == true) ? -1 : 1 ;
            }
        else
            {
            // otherwise reset the axis value
            Axis[i].Value = 0;
            }
        }
    }
}
//---------------------------------------------------------------------------
void    TfrmJoystick :: ProcessJoystick(
                JOYINFOEX             &pji_ex    ,
                JOYCAPS             &pjc_jc    ,
                struct ButtonType    *Button    ,
                struct AxisType        *Axis    )
{
int            i = 0;
bool        bModPressed = false;

// for each button
for (i = 0; i < NUM_BUTTONS; i++)
    {
    // if it is enabled
    if (Button[i].Enabled == true)
        {
        // and if it is pressed
        if ((pji_ex.dwButtons & ButtonFlag[i]) == ButtonFlag[i])
            {
            // if it is the modifier button
            if (Button[i].OptionNum == MODIFIER_NUM)
                {
                // then set the modifier flag
                bModPressed = true;
                }
            else
                {
                // otherwise process as normal
                // only if an item has been selected from the list
                if (Button[i].OptionNum >= 0)
                    {
                    swOleProcedure(
                        ButtonOption[Button[i].OptionNum].Option->SW_OleType    ,
                        ButtonOption[Button[i].OptionNum].Option->SW_OleProcName,
                        ButtonOption[Button[i].OptionNum].Option->SW_OleNumParam,
                        ButtonOption[Button[i].OptionNum].Option->SW_OleParam1    , 0);
                    }
                }
            }
        }
    }

// if there is valid hat information
// and a hat
if ((pji_ex.dwFlags  & JOY_RETURNPOV ) == JOY_RETURNPOV  &&
    (jcJoyCaps.wCaps & JOYCAPS_HASPOV) == JOYCAPS_HASPOV )
    {
    // for each POV direction
    for (i = 0; i < NUM_POV; i++)
        {
        // if it is enabled
        if (POV[i].Enabled == true)
            {
            // and if it is pressed
            if (pji_ex.dwPOV == POVFlag[i])
                {
                // if it is the modifier button
                if (POV[i].OptionNum == MODIFIER_NUM)
                    {
                    // then set the modifier flag
                    bModPressed = true;
                    }
                else
                    {
                    // otherwise process as normal
                    // only if an item has been selected from the list
                    if (POV[i].OptionNum >= 0)
                        {
                        swOleProcedure(
                            ButtonOption[POV[i].OptionNum].Option->SW_OleType        ,
                            ButtonOption[POV[i].OptionNum].Option->SW_OleProcName   ,
                            ButtonOption[POV[i].OptionNum].Option->SW_OleNumParam   ,
                            ButtonOption[POV[i].OptionNum].Option->SW_OleParam1        , 0);
                        }
                    }
                }
            }
        }
    }
// get date code the first time we go through here
if (swDateCode == 0)
    {
    try
        {
        // first refresh our connection to SolidWorks
        swApp = CreateOleObject("SldWorks.Application");
        swDateCode = swApp.OleFunction("DateCode");
        }
    CATCH_OLE_ERROR;
    }

#define SW_DATE_DYN     97001

#define PRE_VIEW        \
            if (swDateCode >= SW_DATE_DYN)                      \
                {                                               \
                try                                             \
                    {                                           \
                    swModelView.OleProcedure("StartDynamics");  \
                    }                                           \
                CATCH_OLE_ERROR;                                \
                }                                               \

#define POST_VIEW       \
            if (swDateCode >= SW_DATE_DYN)                      \
                {                                               \
                try                                             \
                    {                                           \
                    swModelView.OleProcedure("StopDynamics");   \
                    }                                           \
                CATCH_OLE_ERROR;                                \
                }                                               \

/* ----------------------------------------------------------
need to debounce call to "GraphicsRedraw2" until after _all_ graphics
manipulation has occurred.  This is especially noticeable when using
wireframe since the call to "GraphicsRedraw2" seems to be very expensive.
---------------------------------------------------------- */

// reset flags for doing graphics
bDoingGraphics = false;

// for each joystick axis
for (i = 0; i < NUM_AXES; i++)
    {
    // if it is enabled
    if (Axis[i].Enabled == true)
        {
        // and if the value is over the threshold
        if (abs(Axis[i].Value) > Axis[i].Threshold)
            {
            // set flags for doing graphics and redrawing
            bDoingGraphics = true;
            bGraphicsRedrawReq = true;

            // if the modifier button has been pressed
            if (bModPressed == true)
                {
                // if the value is positive
                if (Axis[i].Value > 0)
                    {
                    // run the ModOptionPlus procedure
                    // only if an item has been selected from the list
                    if (Axis[i].ModOptionNum >= 0)
                        {
                        PRE_VIEW;
                        swOleProcedure(
                            AxisOption[Axis[i].ModOptionNum].OptionPlus->SW_OleType        ,
                            AxisOption[Axis[i].ModOptionNum].OptionPlus->SW_OleProcName    ,
                            AxisOption[Axis[i].ModOptionNum].OptionPlus->SW_OleNumParam    ,
                            AxisOption[Axis[i].ModOptionNum].OptionPlus->SW_OleParam1    ,
                            Axis[i].Value);
                        POST_VIEW;
                        }
                    }
                else
                    {
                    // otherwise run the ModOptionMinus procedure
                    // only if an item has been selected from the list
                    if (Axis[i].ModOptionNum >= 0)
                        {
                        PRE_VIEW;
                        swOleProcedure(
                            AxisOption[Axis[i].ModOptionNum].OptionMinus->SW_OleType    ,
                            AxisOption[Axis[i].ModOptionNum].OptionMinus->SW_OleProcName,
                            AxisOption[Axis[i].ModOptionNum].OptionMinus->SW_OleNumParam,
                            AxisOption[Axis[i].ModOptionNum].OptionMinus->SW_OleParam1    ,
                            Axis[i].Value);
                        POST_VIEW;
                        }
                    }
                }
            else
                {
                // otherwise if the value is negative
                if (Axis[i].Value < 0)
                    {
                    // run the OptionPlus procedure
                    // only if an item has been selected from the list
                    if (Axis[i].OptionNum >= 0)
                        {
                        PRE_VIEW;
                        swOleProcedure(
                            AxisOption[Axis[i].OptionNum].OptionPlus->SW_OleType        ,
                            AxisOption[Axis[i].OptionNum].OptionPlus->SW_OleProcName    ,
                            AxisOption[Axis[i].OptionNum].OptionPlus->SW_OleNumParam    ,
                            AxisOption[Axis[i].OptionNum].OptionPlus->SW_OleParam1        ,
                            Axis[i].Value);
                        POST_VIEW;
                        }
                    }
                else
                    {
                    // otherwise run the OptionMinus procedure
                    // only if an item has been selected from the list
                    if (Axis[i].OptionNum >= 0)
                        {
                        PRE_VIEW;
                        swOleProcedure(
                            AxisOption[Axis[i].OptionNum].OptionMinus->SW_OleType        ,
                            AxisOption[Axis[i].OptionNum].OptionMinus->SW_OleProcName    ,
                            AxisOption[Axis[i].OptionNum].OptionMinus->SW_OleNumParam    ,
                            AxisOption[Axis[i].OptionNum].OptionMinus->SW_OleParam1        ,
                            Axis[i].Value);
                        POST_VIEW;
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

