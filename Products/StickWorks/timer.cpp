// pre-compiled headers
#include "stdafx.h"

#include <mmsystem.h>
#include <math.h>
#include "SldWorks.h"
#include "StickWorks.h"
#include "ExampleApp.h"
#include "HandleEvents.h"
#include "timer.h"
#include <tchar.h>

//-----------------------------------------------------
// local funciton prototypes
int sign(double value);

//-----------------------------------------------------
// local global variables
BOOL    bIs_XYtrans, bIs_XYrot, bIs_Zoom;


//-----------------------------------------------------
int sign(double value)
{
    if (fabs(value) < fabs(1.0 / (g_nThreshold - 0.1)))
        return 0;

    if (value > 0.0)
        return 1;
    else
        return -1;
}
//---------------------------------------------------------------------------
VOID SW_Redraw(LPMODELDOC ActiveDoc)
{
    // move
    // TDE ugly hacks for broken SW API
    long            lDocType = swDocNONE;
    VARIANT_BOOL    bIsViewWireFrame             = false,
                    bIsViewHiddenLinesRemoved    = false,
                    bIsViewHiddenInGrey          = false;

    LPMODELVIEW     ActiveView = NULL;
    LPSELECTIONMGR  SelectionMgr = NULL;
    long            lNumSelected = 0;

    // update active view
    if (S_OK != ActiveDoc->get_IActiveView(&ActiveView) ||
        NULL == ActiveDoc  ||
        NULL == ActiveView )
        {
        return;
        }

    ActiveDoc->GetType(&lDocType);
    ActiveView->GetDisplayState(swIsViewWireFrame           , &bIsViewWireFrame         );
    ActiveView->GetDisplayState(swIsViewHiddenLinesRemoved  , &bIsViewHiddenLinesRemoved);
    ActiveView->GetDisplayState(swIsViewHiddenInGrey        , &bIsViewHiddenInGrey      );

    ActiveDoc->get_ISelectionManager(&SelectionMgr);
    SelectionMgr->GetSelectedObjectCount(&lNumSelected);

    if ((swDocPART == lDocType              &&
        lNumSelected > 0        )           ||
        TRUE == bIsViewWireFrame            ||
        TRUE == bIsViewHiddenLinesRemoved   ||
        TRUE == bIsViewHiddenInGrey         )
        {
        ActiveDoc->GraphicsRedraw2();
        return;
        }
    // end move hacks


    // rotate
    // TDE ugly hacks for broken SW API
    if ((swDocPART == lDocType              &&
        lNumSelected > 0        )           ||
        (swDocASSEMBLY == lDocType          &&
        lNumSelected > 0        )           ||
        TRUE == bIsViewWireFrame            ||
        TRUE == bIsViewHiddenLinesRemoved   ||
        TRUE == bIsViewHiddenInGrey         )
        {
        ActiveDoc->GraphicsRedraw2();
        return;
        }
    // end rotate hacks


    // zoom
    // TDE ugly hacks for broken SW API
    if ((swDocPART == lDocType              &&
        lNumSelected > 0        )           ||
        TRUE == bIsViewWireFrame            ||
        TRUE == bIsViewHiddenLinesRemoved   ||
        TRUE == bIsViewHiddenInGrey         )
        {
        ActiveDoc->GraphicsRedraw2();
        return;
        }
    // end zoom hacks

    return;
}
//---------------------------------------------------------------------------
VOID CALLBACK SW_JoyTimer(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    #define     MAX_VALUE      100.0

    if (true == g_bJoystickPanelShowing)
        {
        return;
        }

    // update active doc
    LPMODELDOC      ActiveDoc = NULL;

    // return if no windows
    if (S_OK != TheApplication->m_pSldWorks->get_IActiveDoc(&ActiveDoc) ||
        NULL == ActiveDoc)
        {
        return;
        }

    // update active view
    LPMODELVIEW     ActiveView = NULL;

    if (S_OK != ActiveDoc->get_IActiveView(&ActiveView) ||
        NULL == ActiveDoc  ||
        NULL == ActiveView )
        {
        return;
        }

    // update active view
    long    h;
    if (S_OK != ActiveView->GetViewHWnd(&h))
        {
        return;
        }

    // return if not the topmost window
    if (GetFocus() != (HWND) h)
        {
        return;
        }

    // update joystick posn & status
    JOYINFOEX           pjiJoyInfo;

    memset(&pjiJoyInfo, 0x00, sizeof(JOYINFOEX));

    pjiJoyInfo.dwSize = (DWORD ) (sizeof(JOYINFOEX));
    pjiJoyInfo.dwFlags = JOY_RETURNALL;

    if (JOYERR_NOERROR != joyGetPosEx(JOYSTICKID1, &pjiJoyInfo))
        {
        return;
        }

    double              AxisValue[6];

    // map joystick axes to array
    AxisValue[0] = pjiJoyInfo.dwXpos;
    AxisValue[1] = pjiJoyInfo.dwYpos;
    AxisValue[2] = pjiJoyInfo.dwZpos;
    AxisValue[3] = pjiJoyInfo.dwRpos;
    AxisValue[4] = pjiJoyInfo.dwUpos;
    AxisValue[5] = pjiJoyInfo.dwVpos;

    // scale values to -100 to +100
    AxisValue[0] -= (g_jcJoyCaps.wXmax - g_jcJoyCaps.wXmin) / 2.0 + g_nThreshold;
    AxisValue[0] /= (g_jcJoyCaps.wXmax - g_jcJoyCaps.wXmin);
    AxisValue[0] *= MAX_VALUE;

    AxisValue[1] -= (g_jcJoyCaps.wYmax - g_jcJoyCaps.wYmin) / 2.0 + g_nThreshold;
    AxisValue[1] /= (g_jcJoyCaps.wYmax - g_jcJoyCaps.wYmin);
    AxisValue[1] *= MAX_VALUE;

    if (g_jcJoyCaps.wCaps & JOYCAPS_HASZ)
        {
        AxisValue[2] -= (g_jcJoyCaps.wZmax - g_jcJoyCaps.wZmin) / 2.0 + g_nThreshold;
        AxisValue[2] /= (g_jcJoyCaps.wZmax - g_jcJoyCaps.wZmin);
        AxisValue[2] *= MAX_VALUE;
        }

    if (g_jcJoyCaps.wCaps & JOYCAPS_HASR)
        {
        AxisValue[3] -= (g_jcJoyCaps.wRmax - g_jcJoyCaps.wRmin) / 2.0 + g_nThreshold;
        AxisValue[3] /= (g_jcJoyCaps.wRmax - g_jcJoyCaps.wRmin);
        AxisValue[3] *= MAX_VALUE;
        }

    if (g_jcJoyCaps.wCaps & JOYCAPS_HASU)
        {
        AxisValue[4] -= (g_jcJoyCaps.wUmax - g_jcJoyCaps.wUmin) / 2.0 + g_nThreshold;
        AxisValue[4] /= (g_jcJoyCaps.wUmax - g_jcJoyCaps.wUmin);
        AxisValue[4] *= MAX_VALUE;
        }

    if (g_jcJoyCaps.wCaps & JOYCAPS_HASV)
        {
        AxisValue[5] -= (g_jcJoyCaps.wVmax - g_jcJoyCaps.wVmin) / 2.0 + g_nThreshold;
        AxisValue[5] /= (g_jcJoyCaps.wVmax - g_jcJoyCaps.wVmin);
        AxisValue[5] *= MAX_VALUE;
        }


    // X-Y translation
    if ((fabs(AxisValue[0]) > g_nThreshold ||       // X
         fabs(AxisValue[1]) > g_nThreshold )  &&    // Y
        !(pjiJoyInfo.dwButtons & JOY_BUTTON1))
        {
        // damp out movement on the other axes
        AxisValue[0] = (fabs(AxisValue[0]) > g_nThreshold) ? AxisValue[0] : 0;
        AxisValue[1] = (fabs(AxisValue[1]) > g_nThreshold) ? AxisValue[1] : 0;

        // higher number = smaller Xmove = slower rotation = more sensitive
        #define     X_MOVE_SCALE_LINEAR            2000.0
        #define     Y_MOVE_SCALE_LINEAR            2000.0
        #define     MOVE_SENSITIVITY               (10.0 * ((float )g_nSensitivity - MAX_VALUE / 2))

        double Xmove, Ymove;

        Xmove =  AxisValue[0] - sign(AxisValue[0]) * g_nThreshold;
        Xmove /= (X_MOVE_SCALE_LINEAR + MOVE_SENSITIVITY);

        Ymove =  AxisValue[1] - sign(AxisValue[1]) * g_nThreshold;
        Ymove /= (Y_MOVE_SCALE_LINEAR + MOVE_SENSITIVITY);

        ActiveView->TranslateBy(Xmove, -Ymove);

        // set SW panning flag
        bIs_XYtrans = true;
        }
    else if (true == bIs_XYtrans)
        {
        SW_Redraw(ActiveDoc);

        // reset flag for SW panning
        bIs_XYtrans = false;
        }



    // X-Y rotation
    if ((fabs(AxisValue[0]) > g_nThreshold ||       // X
         fabs(AxisValue[1]) > g_nThreshold )  &&    // Y
        (pjiJoyInfo.dwButtons & JOY_BUTTON1))
        {
        // damp out movement on the other axes
        AxisValue[0] = (fabs(AxisValue[0]) > g_nThreshold) ? AxisValue[0] : 0;
        AxisValue[1] = (fabs(AxisValue[1]) > g_nThreshold) ? AxisValue[1] : 0;

        // higher number = smaller Xmove = slower rotation = more sensitive
        #define     X_ROT_SCALE_LINEAR          175.0
        #define     Y_ROT_SCALE_LINEAR          175.0
        #define     ROT_SENSITIVITY             (3.0 * ((float ) g_nSensitivity - MAX_VALUE / 2))

        g_nSensitivity;

        double Xmove, Ymove;

        Xmove =  AxisValue[0] - sign(AxisValue[0]) * g_nThreshold;
        Xmove /= (X_ROT_SCALE_LINEAR + ROT_SENSITIVITY);

        Ymove =  AxisValue[1] - sign(AxisValue[1]) * g_nThreshold;
        Ymove /= (Y_ROT_SCALE_LINEAR + ROT_SENSITIVITY);

        ActiveView->RotateAboutCenter(Ymove, Xmove);

        // set SW rotating flag
        bIs_XYrot = true;
        }
    else if (true == bIs_XYrot)
        {
        SW_Redraw(ActiveDoc);

        // reset flag for SW rotating
        bIs_XYrot = false;
        }


    // zooming
    if ((fabs(AxisValue[3]) > g_nThreshold)  &&        // R
         !(pjiJoyInfo.dwButtons & JOY_BUTTON1))
        {
        #define     R_MOVE_SCALE            100.0

        g_nSensitivity;

        double Rmove;

        Rmove =  AxisValue[3] - sign(AxisValue[3]) * g_nThreshold;
        Rmove /= - R_MOVE_SCALE;

        // adjust offset since zoom factor is 1.0 +/- 1.0 ie 0.0 to 2.0
        Rmove += 1.0;

        // restrict increment to between 0.0 and 2.0
        Rmove = Rmove > 2.0 ? 1.85 : Rmove;
        Rmove = Rmove < 0.0 ? 0.25 : Rmove;

        ActiveView->ZoomByFactor(Rmove);

        // set flag for SW zooming
        bIs_Zoom = true;
        }
    else if (bIs_Zoom == true)
        {
        SW_Redraw(ActiveDoc);

        // reset SW zooming flag
        bIs_Zoom = false;
        }


    // Z rotation = spin
    if ((fabs(AxisValue[3]) > g_nThreshold)  &&        // R
         (pjiJoyInfo.dwButtons & JOY_BUTTON1))
        {
        #define     R_ROT_SCALE            100.0

        double Rmove;

        Rmove =  AxisValue[3] - sign(AxisValue[3]) * g_nThreshold;
        Rmove /= R_ROT_SCALE;

        if (Rmove > 0)
            {
            ActiveDoc->ViewRotateminusz();
            }
        else
            {
            ActiveDoc->ViewRotateplusz();
            }
        }


    // button 2 = Zoomtofit
    if (pjiJoyInfo.dwButtons & JOY_BUTTON2)
        {
        ActiveDoc->ViewZoomtofit();
        }


    // button 3 = ctrl
    if (pjiJoyInfo.dwButtons & JOY_BUTTON3 &&
        false == g_bCtrlDown)
        {
        UINT ScanCode = MapVirtualKey(VK_CONTROL, 0);
        keybd_event(VK_CONTROL, (BYTE ) ScanCode, 0, 0);
        g_bCtrlDown = true;
        }

    if (!(pjiJoyInfo.dwButtons & JOY_BUTTON3) &&
        true == g_bCtrlDown)
        {
        UINT ScanCode = MapVirtualKey(VK_CONTROL, 0);
        keybd_event(VK_CONTROL, (BYTE ) ScanCode, KEYEVENTF_KEYUP, 0);
        g_bCtrlDown = false;
        }


    // button 4 = ESCAPE
    if (pjiJoyInfo.dwButtons & JOY_BUTTON4 &&
        false == g_bEscDown)
        {
        UINT ScanCode = MapVirtualKey(VK_ESCAPE, 0);
        keybd_event(VK_ESCAPE, (BYTE ) ScanCode, 0, 0);
        g_bEscDown = true;
        }

    if (!(pjiJoyInfo.dwButtons & JOY_BUTTON4) &&
        true == g_bEscDown)
        {
        UINT ScanCode = MapVirtualKey(VK_ESCAPE, 0);
        keybd_event(VK_ESCAPE, (BYTE ) ScanCode, KEYEVENTF_KEYUP, 0);
        g_bEscDown = false;
        }
}
//-----------------------------------------------------
VOID CALLBACK SW_RegTimer(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    KillTimer(NULL, g_uRegTimerID);

    if (false == g_bRegistered)
        {
        KillTimer(NULL, g_uJoyTimerID);
        AfxMessageBox(_T("StickWorks -\nSorry, your time is up."));
        }
    }

//-----------------------------------------------------
