#include "stdafx.h"
#include "SLandscapePrintingApp.h"
#include <winspool.h>

void SLandscapePrintingApp::SetPrinterLandscape 
(
	bool Landscape
)
{
//	Get default printer settings.
    PRINTDLG   pd;

    pd.lStructSize = (DWORD) sizeof(PRINTDLG);

    if (GetPrinterDeviceDefaults(&pd))
    {
//		Lock memory handle.
        DEVMODE FAR* pDevMode = (DEVMODE FAR*)::GlobalLock(m_hDevMode);
        LPDEVNAMES lpDevNames;
        LPTSTR lpszDriverName, lpszDeviceName, lpszPortName;
        HANDLE hPrinter;

        if (pDevMode)
        {
//			Change printer settings in here.
            pDevMode->dmOrientation = Landscape?DMORIENT_LANDSCAPE:DMORIENT_PORTRAIT;

//			Unlock memory handle.
			lpDevNames = (LPDEVNAMES)GlobalLock(pd.hDevNames);
			lpszDriverName = (LPTSTR )lpDevNames + lpDevNames->wDriverOffset;
			lpszDeviceName = (LPTSTR )lpDevNames + lpDevNames->wDeviceOffset;
			lpszPortName   = (LPTSTR )lpDevNames + lpDevNames->wOutputOffset;

			::OpenPrinter(lpszDeviceName, &hPrinter, NULL);
			::DocumentProperties(NULL,hPrinter,lpszDeviceName,pDevMode,
							   pDevMode, DM_IN_BUFFER|DM_OUT_BUFFER);

//			Sync the pDevMode.
//			See SDK help for DocumentProperties for more info.
			::ClosePrinter(hPrinter);
			::GlobalUnlock(m_hDevNames);
			::GlobalUnlock(m_hDevMode);
       }//if
    }//if
}//SLandscapePrintingApp::SetPrinterLandscape

