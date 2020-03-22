#ifndef _SClickableStatusBar_h
#define _SClickableStatusBar_h

// Status bar for which a pane can be clicked
class SClickableStatusBar:public CStatusBar
{
protected:

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	virtual void OnPaneDoubleClicked (int PaneNo) {}

public:

    DECLARE_MESSAGE_MAP()
};//SClickableStatusBar

#endif