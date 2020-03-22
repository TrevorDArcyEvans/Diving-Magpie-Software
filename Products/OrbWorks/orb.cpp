//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "orb.h"
#include "process.h"
//---------------------------------------------------------------------------
MMRESULT orbGetDevCaps(
    UINT 			uJoyID	,
    LPJOYCAPS 		pjc		,
    UINT 			cbjc	)
{
if (bOrbPresent == true)
	{
	pjc->wMid = 0;
	pjc->wPid = 0;

	strcpy(pjc->szPname, "Orb Driver v1.0");

	pjc->wXmin = 0;		pjc->wXmax = 1024;
	pjc->wYmin = 0;		pjc->wYmax = 1024;
	pjc->wZmin = 0;		pjc->wZmax = 1024;

	pjc->wNumButtons = 6;

	pjc->wPeriodMin =   10;
	pjc->wPeriodMax = 1000;

	pjc->wRmin = 0;		pjc->wRmax = 1024;
	pjc->wUmin = 0;		pjc->wUmax = 1024;
	pjc->wVmin = 0;		pjc->wVmax = 1024;

	pjc->wCaps = JOYCAPS_HASZ | JOYCAPS_HASR | JOYCAPS_HASU | JOYCAPS_HASV;

	pjc->wMaxAxes = 6;
	pjc->wNumAxes = 6;
	pjc->wMaxButtons = 6;

	pjc->szRegKey[0] = '\0';
	strcpy(pjc->szOEMVxD, "Trevor D'Arcy-Evans");

	return JOYERR_NOERROR;
    }
else
	{
	return MMSYSERR_NODRIVER;
    }
}
//---------------------------------------------------------------------------

