// FI_View.cpp : implementation of the CFI_View class
//

#include "stdafx.h"
#include "FI_Demo.h"

#include "FI_Doc.h"
#include "FI_View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFI_View

IMPLEMENT_DYNCREATE(CFI_View, CScrollView)

BEGIN_MESSAGE_MAP(CFI_View, CScrollView)
	//{{AFX_MSG_MAP(CFI_View)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFI_View construction/destruction

CFI_View::CFI_View()
{
	m_pPalette = NULL;
	m_hDrawDib = NULL;
}

CFI_View::~CFI_View()
{
	if(m_pPalette)
	{
		m_pPalette->DeleteObject();
		delete m_pPalette;
		m_pPalette = NULL;
	}
	if(m_hDrawDib)
	{
		DrawDibClose(m_hDrawDib);
		m_hDrawDib = NULL;
	}
}

BOOL CFI_View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFI_View drawing

/*************************************************************************
 *
 * CreatePalette()
 *
 * Return Value:
 *
 * TRUE if succesfull, FALSE otherwise
 *
 * Description:
 *
 * This function creates a palette from a DIB by allocating memory for the
 * logical palette, reading and storing the colors from the DIB's color table
 * into the logical palette, creating a palette from this logical palette,
 * and then returning the palette's handle. This allows the DIB to be
 * displayed using the best possible colors (important for DIBs with 256 or
 * more colors).
 *
 ************************************************************************/

#define PALVERSION 0x300	// magic number for LOGPALETTE

BOOL CFI_View::CreatePalette(void *dib)
{
	if(!dib)
		return FALSE;

	//get the number of colors in the DIB
	unsigned int NumColors = FreeImage_GetColorsUsed(dib);
	
	if (NumColors != 0)
	{
		// allocate memory block for logical palette
		HANDLE hLogPal = ::GlobalAlloc(GHND, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY)*NumColors);

		// if not enough memory, clean up and return NULL
		if (hLogPal == 0)
			return FALSE;

		LPLOGPALETTE lpPal = (LPLOGPALETTE)::GlobalLock((HGLOBAL)hLogPal);

		// set version and number of palette entries
		lpPal->palVersion = PALVERSION;
		lpPal->palNumEntries = (WORD)NumColors;

		RGBQUAD *pRgb = FreeImage_GetPalette(dib);
		for(unsigned int i = 0; i < NumColors; i++)
		{
			lpPal->palPalEntry[i].peRed		= pRgb[i].rgbRed;
			lpPal->palPalEntry[i].peGreen	= pRgb[i].rgbGreen;
			lpPal->palPalEntry[i].peBlue	= pRgb[i].rgbBlue;
			lpPal->palPalEntry[i].peFlags	= 0;
		}

		// create the palette and get handle to it 
		if (m_pPalette)
		{
			m_pPalette->DeleteObject();
			delete m_pPalette;
		}
		m_pPalette = new CPalette;
		BOOL bResult = m_pPalette->CreatePalette(lpPal);
		::GlobalUnlock((HGLOBAL) hLogPal);
		::GlobalFree((HGLOBAL) hLogPal);
		return bResult;
	}

	return TRUE;
}

void CFI_View::OnDraw(CDC* pDC)
{
	CFI_Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->m_dib)
	{
		int cxDIB = (int)FreeImage_GetWidth(pDoc->m_dib);         // Size of DIB - x
		int cyDIB = (int)FreeImage_GetHeight(pDoc->m_dib);        // Size of DIB - y
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest;
		if (pDC->IsPrinting())   // printer DC
		{
			// get size of printer page (in pixels)
			int cxPage = pDC->GetDeviceCaps(HORZRES);
			int cyPage = pDC->GetDeviceCaps(VERTRES);
			// get printer pixels per inch
			int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

			//
			// Best Fit case -- create a rectangle which preserves
			// the DIB's aspect ratio, and fills the page horizontally.
			//
			// The formula in the "->bottom" field below calculates the Y
			// position of the printed bitmap, based on the size of the
			// bitmap, the width of the page, and the relative size of
			// a printed pixel (cyInch / cxInch).
			//
			rcDest.top = rcDest.left = 0;
			rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch)
					/ ((double)cxDIB * cxInch));
			rcDest.right = cxPage;
		}
		else   // not printer DC
		{
			rcDest = rcDIB;
		}

		// Draw the dib
		CreatePalette(pDoc->m_dib);
		if (m_hDrawDib == NULL)
			m_hDrawDib = DrawDibOpen();
		if (m_hDrawDib)
		{
			DrawDibSetPalette(m_hDrawDib, (HPALETTE)m_pPalette);
			DrawDibRealize( m_hDrawDib,  pDC->GetSafeHdc(),  FALSE);
			DrawDibDraw(m_hDrawDib, pDC->GetSafeHdc(), 0, 0, rcDest.Width(),rcDest.Height(), 
				FreeImage_GetInfoHeader(pDoc->m_dib), FreeImage_GetBits(pDoc->m_dib),
				0, 0, FreeImage_GetWidth(pDoc->m_dib), FreeImage_GetHeight(pDoc->m_dib), 0);
		}
	}
}

void CFI_View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();	
	CFI_Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int Width = FreeImage_GetWidth(pDoc->m_dib);
	int Height = FreeImage_GetHeight(pDoc->m_dib);
	SetScrollSizes(MM_TEXT, CSize(Width, Height));
	// Fit window size to picture size on load
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}

/////////////////////////////////////////////////////////////////////////////
// CFI_View printing

BOOL CFI_View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFI_View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFI_View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFI_View diagnostics

#ifdef _DEBUG
void CFI_View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFI_View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFI_Doc* CFI_View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFI_Doc)));
	return (CFI_Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFI_View message handlers

BOOL CFI_View::OnEraseBkgnd(CDC* pDC) 
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 128, 128));
	FillOutsideRect(pDC, &brush);
	return TRUE;
}

void CFI_View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CFI_Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int Width = FreeImage_GetWidth(pDoc->m_dib);
	int Height = FreeImage_GetHeight(pDoc->m_dib);
	SetScrollSizes(MM_TEXT, CSize(Width, Height));
	Invalidate();	
}

void CFI_View::OnEditCopy() 
{
	CFI_Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->m_dib != NULL)
	{
		OpenClipboard();
		EmptyClipboard();
		void *dib = FreeImage_Clone(pDoc->m_dib);
		SetClipboardData(CF_DIB, dib);
		CloseClipboard();
		FreeImage_Free(dib);
	}	
}

void CFI_View::OnEditPaste() 
{
	if (OpenClipboard())
	{
		void *dib = GetClipboardData(CF_DIB);
		if(dib)
		{
			CFI_Doc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			FreeImage_Free(pDoc->m_dib);
			pDoc->m_dib = FreeImage_Clone(dib);
			CloseClipboard();
			pDoc->SetModifiedFlag(TRUE);
			int Width = FreeImage_GetWidth(pDoc->m_dib);
			int Height = FreeImage_GetHeight(pDoc->m_dib);
			SetScrollSizes(MM_TEXT, CSize(Width, Height));
			// Fit window size to picture size on load
			GetParentFrame()->RecalcLayout();
			ResizeParentToFit(FALSE);
			pDoc->UpdateAllViews(NULL);
		}
	}
}

void CFI_View::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( IsClipboardFormatAvailable(CF_DIB) );
}
