#include "stdafx.h"
#include "SDialogSizer.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SDialogSizer::~SDialogSizer ()
{
	for (int i = 0; i < m_Items.GetSize (); i++)
		delete m_Items[i];
	//for
}//SDialogSizer::~SDialogSizer

void SDialogSizer::AddItem 
(
	CWnd*	Control,
	int		Attachments
)
{
	m_Items.Add (new SSizeableItem (Control,Attachments));
}//SDialogSizer::AddItem

void SDialogSizer::Resize 
(
	const CSize& NewSize
)
{
	for (int i = 0; i < m_Items.GetSize (); i++)
		m_Items[i]->Resize (m_InitialSize,NewSize);
	//for

	for (i = 0; i < m_Items.GetSize (); i++)
		m_Items[i]->Redraw ();
	//for
}//SDialogSizer::Resize

SSizeableItem::SSizeableItem 
(
	CWnd*	Control,
	int		Attachments
)
:m_Control		(Control),
 m_Attachments	(Attachments)
{
	Control->GetWindowRect (m_InitialPos);
	Control->GetParent ()->ScreenToClient (m_InitialPos);
}//SSizeableItem::SSizeableItem

SSizeableItem::EComb SSizeableItem::HStretchType () const
{
	if (m_Attachments & A_H_CENT)
		return HS_CENTRE;
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
	else if (m_Attachments & A_RIGHT)
		return HS_RIGHT;
	else if (m_Attachments & A_LEFT)
		return HS_LEFT;
	//if

	return C_NONE;
}//SSizeableItem::HStretchType

SSizeableItem::EComb SSizeableItem::VStretchType () const
{
	if (m_Attachments & A_V_CENT)
		return VS_CENTRE;
	else if ((m_Attachments & A_TOP) && (m_Attachments & A_BOTTOM))
		return VS_TOP_AND_BOTTOM;
	else if (m_Attachments & A_V_PROPORTION)
	{
		if (m_Attachments & A_TOP)
			return VS_TOPPROP;
		else if (m_Attachments & A_BOTTOM)
			return VS_BOTTOMPROP;
		//if
	}
	else if (m_Attachments & A_TOP)
		return VS_TOP;
	else if (m_Attachments & A_BOTTOM)
		return VS_BOTTOM;
	//if

	return C_NONE;
}//SSizeableItem::VStretchType

void SSizeableItem::Resize 
(
	const CSize& OldSize,
	const CSize& NewSize
)
{
	int TLX = m_InitialPos.TopLeft ().x;
	int TLY = m_InitialPos.TopLeft ().y;
	int Wid = m_InitialPos.Width ();
	int Hei = m_InitialPos.Height ();

	if ((m_Attachments & A_MANUAL_H) || (m_Attachments & A_MANUAL_V))
	{
		CRect RectNow;

		m_Control->GetWindowRect (RectNow);
		m_Control->GetParent ()->ScreenToClient (RectNow);

		if (m_Attachments & A_MANUAL_H) 
		{
			TLX = RectNow.TopLeft ().x;
			Wid = RectNow.Width ();
		}//if

		if (m_Attachments & A_MANUAL_V)
		{
			TLY = RectNow.TopLeft ().y;
			Hei = RectNow.Height ();
		}//if
	}//if

	switch (HStretchType ())
	{
		default:		break;
		case HS_LEFT:	break;
		case HS_CENTRE:	
			TLX = NewSize.cx/2 - (OldSize.cx/2 - m_InitialPos.left);
			break;
		case HS_LEFT_AND_RIGHT:
			Wid = NewSize.cx - OldSize.cx + m_InitialPos.Width ();
			break;
		case HS_RIGHT:
			TLX = NewSize.cx - OldSize.cx + m_InitialPos.TopLeft ().x;
			break;
		case HS_LEFTPROP:
			Wid = (NewSize.cx * m_InitialPos.Width ())/OldSize.cx;
			break;
		case HS_RIGHTPROP:
			Wid = (NewSize.cx * m_InitialPos.Width ())/OldSize.cx;
			TLX = m_InitialPos.TopLeft ().x + m_InitialPos.Width () - Wid - OldSize.cx + NewSize.cx;
			break;	
	}//switch

	switch (VStretchType ())
	{
		default:		break;
		case VS_TOP:	break;
		case VS_CENTRE:	
			TLY = NewSize.cy/2 - (OldSize.cy/2 - m_InitialPos.top);
			break;
		case VS_TOP_AND_BOTTOM:
			Hei = NewSize.cy - OldSize.cy + m_InitialPos.Height ();
			break;
		case VS_BOTTOM:
			TLY = NewSize.cy - OldSize.cy + m_InitialPos.TopLeft ().y;
			break;
		case VS_TOPPROP:
			Hei = (NewSize.cy * m_InitialPos.Height ())/OldSize.cy;
			break;
		case VS_BOTTOMPROP:
			Hei = (NewSize.cy * m_InitialPos.Height ())/OldSize.cy;
			TLY = m_InitialPos.TopLeft ().y + m_InitialPos.Height () - Hei - OldSize.cy + NewSize.cy;
			break;
	}//switch

	m_Control->MoveWindow (TLX,TLY,Wid,Hei);
}//SSizeableItem::Resize

void SSizeableItem::Redraw ()
{
	m_Control->RedrawWindow ();
}//SSizeableItem::Redraw


