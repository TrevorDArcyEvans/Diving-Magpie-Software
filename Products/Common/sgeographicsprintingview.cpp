#include "stdafx.h"
#include "SGeoGraphicsPrintingView.h"
#include "SLandscapePrintingApp.h"

#pragma warning (disable:4244)

BOOL SGeoGraphicsPrintingView::OnPreparePrinting
(
    CPrintInfo* pInfo
)
{
	BOOL RetVal = DoPreparePrinting(pInfo);

	pInfo->SetMinPage (1);
	pInfo->SetMaxPage (1);

	return RetVal;
}//SGeoGraphicsPrintingView::OnPreparePrinting

void SGeoGraphicsPrintingView::OnPrint
(
    CDC*                pDC, 
    CPrintInfo*         pInfo,
    IGeoGraphicsCtrl*   MapControl
) 
{
	CRect Rect = pInfo->m_rectDraw;

	if (m_PrintSize.cx == 0)
	{
		CRect ScreenRect;

		GetClientRect (ScreenRect);

		m_PrintSize = ScreenRect.Size ();
	}//if

	MapControl->PrintControl  ((long)pDC->m_hDC,
		                       (long)pDC->m_hAttribDC,
							   Rect.TopLeft ().x,
							   Rect.TopLeft ().y,
							   Rect.BottomRight ().x,
							   Rect.BottomRight ().y,
							   m_PrintSize.cx,
							   m_PrintSize.cy);
}//SGeoGraphicsPrintingView::OnPrint

void SGeoGraphicsPrintingView::OnFilePrint() 
{
    SLandscapePrintingApp* App = dynamic_cast <SLandscapePrintingApp*> (AfxGetApp ());

    if (App)
    {
	    CRect ScreenRect;

	    GetClientRect (ScreenRect);

	    m_PrintSize = ScreenRect.Size ();

	    App->SetPrinterLandscape (m_PrintSize.cx > m_PrintSize.cy);
    }//if

    CView::OnFilePrint();	
}//SGeoGraphicsPrintingView::OnFilePrint

void SGeoGraphicsPrintingView::OnFilePrintPreview() 
{
    SLandscapePrintingApp* App = dynamic_cast <SLandscapePrintingApp*> (AfxGetApp ());

    if (App)
    {
	    CRect ScreenRect;

	    GetClientRect (ScreenRect);

	    m_PrintSize = ScreenRect.Size ();

	    App->SetPrinterLandscape (m_PrintSize.cx > m_PrintSize.cy);
    }//if

	CView::OnFilePrintPreview();	
}//SGeoGraphicsPrintingView::OnFilePrintPreview
