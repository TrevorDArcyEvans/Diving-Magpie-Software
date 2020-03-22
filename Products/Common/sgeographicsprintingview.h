#ifndef _SGeoGraphicsPrintingView_h
#define _SGeoGraphicsPrintingView_h

#include <afxwin.h>
#include "GeoGraphics.h"

// Base class for any view that wants to print a GeoGraphics control
class SGeoGraphicsPrintingView:public CView
{
private:

  	CSize		                m_PrintSize;

protected:

    BOOL OnPreparePrinting(CPrintInfo* pInfo);
    void OnPrint(CDC* pDC, CPrintInfo* pInfo,IGeoGraphicsCtrl* MapControl);
    void OnFilePrint();
    void OnFilePrintPreview();
};//SGeoGraphicsPrintingView

#endif

