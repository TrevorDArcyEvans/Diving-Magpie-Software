#include "stdafx.h"
#include "SBetterThanMFC.hpp"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void SBetterThanMFC::SaveWindowState
(
	const CWnd*		Window,
	const CString&	Name
)
{
	CString Key = Name + "Placement";

	WINDOWPLACEMENT Placement;

	Placement.length = sizeof (WINDOWPLACEMENT);

	Window->GetWindowPlacement (&Placement);

	AfxGetApp ()->WriteProfileInt (Key,Name + "Flags",Placement.flags);
	AfxGetApp ()->WriteProfileInt (Key,Name + "Show" ,Placement.showCmd);
	AfxGetApp ()->WriteProfileInt (Key,Name + "Left" ,Placement.rcNormalPosition.left);
	AfxGetApp ()->WriteProfileInt (Key,Name + "Top" ,Placement.rcNormalPosition.top);
	AfxGetApp ()->WriteProfileInt (Key,Name + "Right" ,Placement.rcNormalPosition.right);
	AfxGetApp ()->WriteProfileInt (Key,Name + "Bottom" ,Placement.rcNormalPosition.bottom);
}//SBetterThanMFC::SaveWindowState

bool SBetterThanMFC::RestoreWindowState 
(
	CWnd*			Window,
	const CString&	Name
)
{
	CString Key = Name + "Placement";

	WINDOWPLACEMENT Placement;

	Placement.length = sizeof (WINDOWPLACEMENT);

	Window->GetWindowPlacement (&Placement);

	Placement.flags					  = AfxGetApp ()->GetProfileInt (Key,Name + "Flags",-1);
	Placement.showCmd				  = AfxGetApp ()->GetProfileInt (Key,Name + "Show" ,-1);
	Placement.rcNormalPosition.left   = AfxGetApp ()->GetProfileInt (Key,Name + "Left" ,-1);
	Placement.rcNormalPosition.top    = AfxGetApp ()->GetProfileInt (Key,Name + "Top" ,-1);
	Placement.rcNormalPosition.right  = AfxGetApp ()->GetProfileInt (Key,Name + "Right" ,-1);
	Placement.rcNormalPosition.bottom = AfxGetApp ()->GetProfileInt (Key,Name + "Bottom" ,-1);

	if ((Placement.flags == -1)
	 || (Placement.rcNormalPosition.left == -1)
	 || (Placement.rcNormalPosition.top == -1)
	 || (Placement.rcNormalPosition.right == -1)
	 || (Placement.rcNormalPosition.bottom == -1)
	 || (Placement.showCmd == -1))
		return false;
	//if

	Window->SetWindowPlacement (&Placement);

	return true;
}//SBetterThanMFC::RestoreWindowState

// Given a menu item ID, return the position in the menu. Return -1 if not there
int SBetterThanMFC::GetMenuIndexFromID  
(
    const CMenu*    Menu,
    unsigned        ID
)
{
    for (unsigned i = 0; i < Menu->GetMenuItemCount (); i++)
    {
        if (Menu->GetMenuItemID (i) == ID)
            return i;
        //if
    }//for

    return -1;
}//SBetterThanMFC::GetMenuIndexFromID

CMenu* SBetterThanMFC::GetSubMenuByName 
(
	CMenu*			Menu,
	const CString&	Name
)
{
	CString Label;
	unsigned SubCount = 0;

	while (SubCount < Menu->GetMenuItemCount () && Label != Name)
	{
		Menu->GetMenuString (SubCount,Label,MF_BYPOSITION);
		SubCount++;
	}//while

	if (Label != Name)
		return 0;
	else
		return Menu->GetSubMenu (SubCount - 1);
	//if
}//SBetterThanMFC::GetSubMenuByName

CString SBetterThanMFC::AddTrailSlash 
(
	const CString& Path
)
{
	if (Path[Path.GetLength () - 1] == '\\')
		return Path;
	else
		return Path + "\\";
	//if
}//SBetterThanMFC::AddTrailSlash

bool SBetterThanMFC::IsAnyOf				
(
	const CString&	Text,
	const CString&	From
)
{
	int TotLen = From.GetLength ();
	int Len    = Text.GetLength ();

	for (int i = 0; i < TotLen; i += Len)
	{
		if (Text == From.Mid (i,Len))
			return true;
		//if
	}//for

	return false;
}//SBetterThanMFC::IsAnyOf

CString SBetterThanMFC::TruncText 
(
	CDC*			pDC,
	int				Width,
	const CString&	Text
)
{
	CString TruncText = Text;

	int Pos = Text.GetLength ();

	while ((Pos >= 0) && (pDC->GetTextExtent (TruncText + "  ").cx > Width))
		TruncText = Text.Left (Pos--) + "...";
	//while

	return TruncText;
}//SBetterThanMFC::TruncText

CString operator ^ 
(
	const CString& L,
	const CString& R
)
{
	bool LTrails = (L.GetLength () > 0) && (L[L.GetLength () - 1] == '\\');
	bool RLeads  = (R.GetLength () > 0) && (R[0] == '\\');

	if (LTrails && RLeads)
		return L.Left (L.GetLength () - 1) + R;
	else if (!LTrails && !RLeads)
		return L + '\\' + R;
	else
		return L + R;
	//if
}//operator ^

const CString& operator ^= 
(
	CString&		L,
	const CString&	R
)
{
	L = L ^ R;

	return L;
}//operator ^= 


CRect SBetterThanMFC::GetTextRect			
(
	CDC*			pDC,
	const CPoint&	Point,
	const CString&	Text,
	bool			CentreVert
)
{
	CSize Size = pDC->GetTextExtent (Text);

	UINT Align = pDC->GetTextAlign ();

	static XGroup = TA_RIGHT|TA_CENTER|TA_LEFT;
	static YGroup = TA_BOTTOM|TA_BASELINE|TA_TOP;

	UINT XAlign = Align & XGroup;
	UINT YAlign = Align & YGroup;

	long dx = 0;
	long dy = 0;

	if (XAlign == TA_RIGHT)
		dx = Size.cx;
	else if (XAlign == TA_CENTER)
		dx = Size.cx/2;
	else
		dx = 0;
	//if

	if (CentreVert)
		dy = Size.cy/2;
	else if (YAlign == TA_BOTTOM)
		dy = Size.cy;
	else if (YAlign == TA_BASELINE)
		dy = Size.cy;
	else
		dy = 0;
	//if

	CRect RetVal;

	RetVal.SetRect (Point.x - dx,
					Point.y - dy,
					Point.x + Size.cx - dx,
					Point.y + Size.cy - dy);

	return RetVal;
}//SBetterThanMFC::GetTextRect

void SBetterThanMFC::FitInRect			
(
	CRect&			Rect,
	const CPoint&	Point
)
{
	if (Point.y < Rect.top)
		Rect.top = Point.y;
	else if (Point.y > Rect.bottom)
		Rect.bottom = Point.y;
	//if

	if (Point.x < Rect.left)
		Rect.left = Point.x;
	else if (Point.x > Rect.right)
		Rect.right = Point.x;
	//if
}//SBetterThanMFC::FitInRect
