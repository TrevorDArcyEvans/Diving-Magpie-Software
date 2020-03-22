#include "stdafx.h"
#include "SResizeBase.h"

void SSizeItem::SetHorizontalProportions 
(   
    double LeftFraction,
    double RightFraction
)
{
    m_LeftFrac = LeftFraction;
    m_RightFrac = RightFraction;
}

void SSizeItem::SetVerticalProportions   
(   
    double TopFraction,
    double BottomFraction
)
{
    m_TopFrac = TopFraction;
    m_BottomFrac = BottomFraction;
}

RECT SSizeItem::ToParentSystem 
(
	HWND		Control,
	const RECT&	Rect
)
{
	POINT TL;
	POINT BR;

	TL.x = Rect.left;
	TL.y = Rect.top;
	BR.x = Rect.right;
	BR.y = Rect.bottom;

	::ScreenToClient (::GetParent (Control),&TL);
	::ScreenToClient (::GetParent (Control),&BR);

	RECT RetRect;

	RetRect.left   = TL.x;
	RetRect.top    = TL.y;
	RetRect.right  = BR.x;
	RetRect.bottom = BR.y;

	return RetRect;
}//SSizeItem::ToParentSystem

SControlSizer::~SControlSizer ()
{
	for (int i = 0; i < m_Items.size (); i++)
		delete m_Items[i];
	//for
}//SControlSizer::~SControlSizer

SSizeItem* SControlSizer::AddItem 
(
	HWND	Control,
	int		Attachments
)
{
    SSizeItem* Item = new SSizeItem (Control,Attachments);

    m_Items.push_back (Item);

    return Item;
}//SControlSizer::AddItem

void SControlSizer::Resize 
(
	const SIZE& NewSize
)
{
	for (int i = 0; i < m_Items.size (); i++)
		m_Items[i]->Resize (m_InitialSize,NewSize);
	//for

	for (i = 0; i < m_Items.size (); i++)
		m_Items[i]->Redraw ();
	//for
}//SControlSizer::Resize

SSizeItem::SSizeItem 
(
	HWND	Control,
	int		Attachments
)
:m_Control		(Control),
 m_Attachments	(Attachments),
 m_TopFrac      (-1.0),
 m_BottomFrac   (-1.0),
 m_LeftFrac     (-1.0),
 m_RightFrac    (-1.0)
{
	::GetWindowRect (Control,&m_InitialPos);

	m_InitialPos = ToParentSystem (Control,m_InitialPos);
}//SSizeItem::SSizeItem

SSizeItem::EComb SSizeItem::HStretchType () const
{
//	Convert the ORed horizontal rules to a single enum
    if (m_LeftFrac > -1.0)
        return HS_FRACTIONAL;
    else if ((m_Attachments & A_LEFT) && (m_Attachments & A_RIGHT))
		return HS_LEFT_AND_RIGHT;
	else if (m_Attachments & A_H_PROPORTION)
	{
		if (m_Attachments & A_RIGHT)
			return HS_RIGHTPROP;
		else if (m_Attachments & A_LEFT)
			return HS_LEFTPROP;
		//if
	}		
	else if (m_Attachments & A_H_CENT)
	{
		if (m_Attachments & A_RIGHT)
			return HS_RIGHT_AND_CENT;
		else if (m_Attachments & A_LEFT)
			return HS_LEFT_AND_CENT;
		else
			return HS_CENTRE;
		//if
	}
	else if (m_Attachments & A_RIGHT)
		return HS_RIGHT;
	else if (m_Attachments & A_LEFT)
		return HS_LEFT;
	//if

	return C_NONE;
}//SSizeItem::HStretchType

SSizeItem::EComb SSizeItem::VStretchType () const
{
//	Convert the ORed vertical rules to a single enum
	if ((m_Attachments & A_TOP) && (m_Attachments & A_BOTTOM))
		return VS_TOP_AND_BOTTOM;
	else if (m_Attachments & A_V_PROPORTION)
	{
		if (m_Attachments & A_TOP)
			return VS_TOPPROP;
		else if (m_Attachments & A_BOTTOM)
			return VS_BOTTOMPROP;
		//if
	}
	else if (m_Attachments & A_V_CENT)
	{
		if (m_Attachments & A_TOP)
			return VS_TOP_AND_CENT;
		else if (m_Attachments & A_BOTTOM)
			return VS_BOTTOM_AND_CENT;
		else
			return VS_CENTRE;
		//if
	}
	else if (m_Attachments & A_TOP)
		return VS_TOP;
	else if (m_Attachments & A_BOTTOM)
		return VS_BOTTOM;
	//if

	return C_NONE;
}//SSizeItem::VStretchType

void SSizeItem::Resize 
(
	const SIZE& OldSize,
	const SIZE& NewSize
)
{
	int TLX = m_InitialPos.left;
	int TLY = m_InitialPos.top;
	int Wid = m_InitialPos.right -  m_InitialPos.left;
	int Hei = m_InitialPos.bottom - m_InitialPos.top;

	if ((m_Attachments & A_MANUAL_H) || (m_Attachments & A_MANUAL_V))
	{
		RECT RectNow;

		::GetWindowRect (m_Control,&RectNow);
		RectNow = ToParentSystem (m_Control,RectNow);

		if (m_Attachments & A_MANUAL_H) 
		{
			TLX = RectNow.left;
			Wid = RectNow.right - RectNow.left;
		}//if

		if (m_Attachments & A_MANUAL_V)
		{
			TLY = RectNow.top;
			Hei = RectNow.bottom - RectNow.top;
		}//if
	}//if

	int OldWid = m_InitialPos.right - m_InitialPos.left;

	switch (HStretchType ())
	{
		default:		break;
		case HS_LEFT:	break;
		case HS_CENTRE:	
			TLX = NewSize.cx/2 - (OldSize.cx/2 - m_InitialPos.left);
			break;
		case HS_LEFT_AND_RIGHT:
			Wid = NewSize.cx - OldSize.cx + OldWid;
			break;
		case HS_RIGHT:
			TLX = NewSize.cx - OldSize.cx + m_InitialPos.left;
			break;
		case HS_LEFTPROP:
			Wid = (NewSize.cx * OldWid)/OldSize.cx;
			break;
		case HS_RIGHTPROP:
			Wid = (NewSize.cx * OldWid)/OldSize.cx;
			TLX = m_InitialPos.left + OldWid - Wid - OldSize.cx + NewSize.cx;
			break;	
		case HS_LEFT_AND_CENT:
			Wid = (NewSize.cx - OldSize.cx)/2 + OldWid;
			break;
		case HS_RIGHT_AND_CENT:
			TLX = (NewSize.cx - OldSize.cx)/2 + m_InitialPos.left;
			Wid = (NewSize.cx - OldSize.cx)/2 + OldWid;
			break;
        case HS_FRACTIONAL:
            TLX = ((NewSize.cx - OldSize.cx) * m_LeftFrac) + m_InitialPos.left;
            Wid = ((NewSize.cx - OldSize.cx) * (m_RightFrac - m_LeftFrac)) + OldWid;
            break;
	}//switch

	int OldHei = m_InitialPos.bottom - m_InitialPos.top;

	switch (VStretchType ())
	{
		default:		break;
		case VS_TOP:	break;
		case VS_CENTRE:	
			TLY = NewSize.cy/2 - (OldSize.cy/2 - m_InitialPos.top);
			break;
		case VS_TOP_AND_BOTTOM:
			Hei = NewSize.cy - OldSize.cy + OldHei;
			break;
		case VS_BOTTOM:
			TLY = NewSize.cy - OldSize.cy + m_InitialPos.top;
			break;
		case VS_TOPPROP:
			Hei = (NewSize.cy * OldHei)/OldSize.cy;
			break;
		case VS_BOTTOMPROP:
			Hei = (NewSize.cy * OldHei)/OldSize.cy;
			TLY = m_InitialPos.top + OldHei - Hei - OldSize.cy + NewSize.cy;
			break;
		case VS_TOP_AND_CENT:
			Hei = (NewSize.cy - OldSize.cy)/2 + OldHei;
			break;
		case VS_BOTTOM_AND_CENT:
			TLY = (NewSize.cy - OldSize.cy)/2 + m_InitialPos.top;
			Hei = (NewSize.cy - OldSize.cy)/2 + OldHei;
			break;
        case VS_FRACTIONAL:
            TLY = ((NewSize.cy - OldSize.cy) * m_TopFrac) + m_InitialPos.top;
            Hei = ((NewSize.cy - OldSize.cy) * (m_BottomFrac - m_TopFrac)) + OldHei;
            break;
	}//switch

	::MoveWindow (m_Control,TLX,TLY,Wid,Hei,TRUE);
}//SSizeItem::Resize

void SSizeItem::Redraw ()
{	
	::RedrawWindow (m_Control,0,0,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE);
}//SSizeItem::Redraw

void SResizeBase::InnerOnSize (UINT Type, int cx, int cy)
{
	if (m_FirstTime)
	{
		InitializeNow ();
		m_FirstTime = false;
	}//if

//  Funtion needs a SIZE
    SIZE Size;

    Size.cx = cx;
    Size.cy = cy;

	m_Sizer.Resize (Size);

	if (::IsWindow (GetHWND ()))
		DoDeferSize (cx,cy);
	//if
}

SIZE SResizeBase::GetDesiredExtent () const
{
//  Just use the current size by default
    RECT Rect;

    ::GetClientRect (GetHWND (),&Rect);

    SIZE RetSize;

    RetSize.cx = Rect.right - Rect.left;
    RetSize.cy = Rect.bottom - Rect.top;

    return RetSize;
}//SResizeBase::GetDesiredExtent

void SResizeBase::InitializeNow ()
{
    SIZE Size = GetDesiredExtent ();

	m_Sizer.Initialize (Size.cx,Size.cy);
}//SResizeBase::InitializeNow

void SResizeBase::InnerGetMinMax 
(
	MINMAXINFO* Info
)const
{
	if (m_MinMaxDeferral)
	{
//		Can't someone else do it?
		::SendMessage (m_MinMaxDeferral,WM_GETMINMAXINFO,0,(LPARAM)Info);

//		Add our own border width
		if (m_MinWid >= 0)
			Info->ptMinTrackSize.x += m_MinWid;
		//if

		if (m_MinHei >= 0)
			Info->ptMinTrackSize.y += m_MinHei;
		//if

		if (m_MaxWid >= 0)
			Info->ptMaxTrackSize.x += m_MaxWid;
		//if

		if (m_MaxHei >= 0)
			Info->ptMaxTrackSize.y += m_MaxHei;
		//if
	}
	else
	{
//		Have to do it ourselves
		if (m_MinWid >= 0)
			Info->ptMinTrackSize.x = m_MinWid;
		//if

		if (m_MinHei >= 0)
			Info->ptMinTrackSize.y = m_MinHei;
		//if

		if (m_MaxWid >= 0)
			Info->ptMaxTrackSize.x = m_MaxWid;
		//if

		if (m_MaxHei >= 0)
			Info->ptMaxTrackSize.y = m_MaxHei;
		//if
	}//if
}//SResizeBase::InnerGetMinMax

void SResizeBase::AddBordersToMinMax ()
{
	int CapHei = ::GetSystemMetrics (SM_CYCAPTION);

	m_MinHei += CapHei;
	m_MaxHei += CapHei;
}//SResizeBase::AddBordersToMinMax

void SResizeBase::SetMinSize 
(
	int MinWid,
	int MinHeight
)
{
	m_MinWid = MinWid;
	m_MinHei = MinHeight;
}//SResizeBase::SetMinSize

void SResizeBase::SetMaxSize 
(
	int MaxWid,
	int MaxHeight
)
{
	m_MaxWid = MaxWid;
	m_MaxHei = MaxHeight;
}//SResizeBase::SetMaxSize
