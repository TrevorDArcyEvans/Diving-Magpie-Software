#include <afx.h>

#ifndef _SBetterThanMFC_hpp
#define _SBetterThanMFC_hpp

namespace SBetterThanMFC
{
	void	SaveWindowState		(const CWnd* Window,const CString& Name);
	bool	RestoreWindowState	(CWnd* Window,const CString& Name);
	CMenu*	GetSubMenuByName	(CMenu* Menu,const CString& Name);
    int     GetMenuIndexFromID  (const CMenu* Menu,unsigned ID);
	CString	AddTrailSlash		(const CString& Path);
	bool	IsAnyOf				(const CString& Text,const CString& From);
	CString	TruncText			(CDC* pDC,int Width,const CString& Text);
	CRect   GetTextRect			(CDC* pDC,const CPoint& Point,const CString& Text,bool CentreVert = false);
	void	FitInRect			(CRect& Rect,const CPoint& Point);
};//SBetterThanMFC

CString operator ^ (const CString& L,const CString& R);
const CString& operator ^= (CString& L,const CString& R);

class SWaitCursorSwitch
{
private:

	CCmdTarget*	m_Wnd;
	bool		m_On;

public:

	SWaitCursorSwitch (CCmdTarget* Wnd,bool HoldOff = false):m_Wnd (Wnd) 
	{
		if (!HoldOff) 
		{
			m_Wnd->BeginWaitCursor ();
			m_On = true;
		} 
		else 
			m_On = false;
		//if
	}

	void Now () {m_Wnd->BeginWaitCursor (); m_On = true;}
	~SWaitCursorSwitch () {if (m_On) m_Wnd->EndWaitCursor ();}
};//SWaitCursorSwitch

#endif
