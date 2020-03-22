#include "stdafx.h"
#include "SClickableStatusBar.h"

BEGIN_MESSAGE_MAP(SClickableStatusBar, CStatusBar)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void SClickableStatusBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
//	Run through the items and see which one was picked
	for (int i = 0; i < m_nCount; i++)
	{
		CRect Rect;

		GetItemRect (i,&Rect);

		if (Rect.PtInRect (point))
		{
			OnPaneDoubleClicked (i);
			break;
		}//if
	}//for
	
	CStatusBar::OnLButtonDblClk(nFlags, point);
}//SClickableStatusBar::OnLButtonDblClk

