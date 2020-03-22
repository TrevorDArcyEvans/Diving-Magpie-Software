#include "stdafx.h"
#include "SRubberRectContext.hpp"
#include "SVectors.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HCURSOR	SRubberRectContext::sm_AllCursor = 0;
HCURSOR	SRubberRectContext::sm_CrossCursor = 0;
HCURSOR	SRubberRectContext::sm_NWSECursor = 0;
HCURSOR	SRubberRectContext::sm_NESWCursor = 0;
HCURSOR	SRubberRectContext::sm_WECursor = 0;
HCURSOR	SRubberRectContext::sm_NSCursor = 0;

SRubberRectContext::SRubberRectContext 
(
	bool		AllowRotation,
	bool		FixAspRat,
	EFinishOn	FinishOn,
	CWnd*		Window,
	double		AspRat
)
:SEchoContext		(FinishOn),
 m_AllowRotation	(AllowRotation), 
 m_FixAspRat		(FixAspRat),
 m_RectDrawn		(false),
 m_AspRat			(AspRat),
 m_DC				(0),
 m_Pen				(0),
 m_Initiated		(false)
{
	if (!sm_AllCursor)
	{
		sm_AllCursor	= ::LoadCursor (0,IDC_SIZEALL);
		sm_CrossCursor	= ::LoadCursor (0,IDC_CROSS);
		sm_NWSECursor	= ::LoadCursor (0,IDC_SIZENWSE);
		sm_NESWCursor	= ::LoadCursor (0,IDC_SIZENESW);
		sm_WECursor		= ::LoadCursor (0,IDC_SIZEWE);
		sm_NSCursor		= ::LoadCursor (0,IDC_SIZENS);
	}//if

	if (Window)
	{
		m_DC = new CClientDC (Window);

		m_Pen = new CPen (PS_SOLID,2,RGB (0,0,0));

		m_DC->SelectObject (m_Pen);
		m_DC->SetROP2 (R2_NOT);
	}//if
}//SRubberRectContext::SRubberRectContext

SRubberRectContext::~SRubberRectContext ()
{
	if (m_DC)
		delete m_DC;
	//if

	if (m_Pen)
		delete m_Pen;
	//if
}//SRubberRectContext::~SRubberRectContext
	
void SRubberRectContext::Initiate
(
	const CPoint&	Point,
	bool			Ctrl,
	bool			Shift
)
{
	m_Initiated = true;

	m_Anchor = 
	m_CurrentPoint = 
	m_RectPoints[0] = 
	m_RectPoints[1] = 
	m_RectPoints[2] = 
	m_RectPoints[3] = 
	m_RectPoints[4] = Point;
}//SRubberRectContext::Initiate

CRect SRubberRectContext::AsRect () const
{
	CRect RetVal (m_RectPoints[0],m_RectPoints[2]);

	RetVal.NormalizeRect ();

	return RetVal;
}//SRubberRectContext::AsRect

void SRubberRectContext::ClearRect ()
{
	if (m_RectDrawn)
	{
		DrawIt ();

		m_RectDrawn = false;
	}//if
}//SRubberRectContext::ClearRect

void SRubberRectContext::DrawIt ()
{
	m_DC->Polyline (m_RectPoints,5);
}//SRubberRectContext::DrawIt

void SRubberRectContext::DrawRect ()
{
	CalcPoints ();

	DrawIt ();

	m_RectDrawn = true;
}//SRubberRectContext::DrawRect

void SRubberRectContext::CalcPoints ()
{
	if (m_AllowRotation)
	{
		SVector Base (m_CurrentPoint.x - m_Anchor.x,
					  m_CurrentPoint.y - m_Anchor.y);

		SVector Side = -Base.Perp ().Hat () * m_AspRat * Base.Mod ();

		m_RectPoints[1] = m_CurrentPoint;
		m_RectPoints[2] = m_CurrentPoint + CPoint (Side.m_X,Side.m_Y);
		m_RectPoints[3] = m_Anchor  + CPoint (Side.m_X,Side.m_Y);
	}
	else if (m_FixAspRat)
	{
		SVector Diagish (m_CurrentPoint.x - m_Anchor.x,
					     m_CurrentPoint.y - m_Anchor.y);

		if (fabs (Diagish.Gradient ()) > m_AspRat)
		{
			if (Diagish.m_X < 0)
				m_RectPoints[1] = m_Anchor + CPoint (-abs (Diagish.m_Y)/m_AspRat,0);
			else
				m_RectPoints[1] = m_Anchor + CPoint (abs (Diagish.m_Y)/m_AspRat,0);
			//if

			m_RectPoints[3] = m_Anchor + CPoint (0,Diagish.m_Y);
		}
		else
		{
			m_RectPoints[1] = m_Anchor + CPoint (Diagish.m_X,0);

			if (Diagish.m_Y < 0)
				m_RectPoints[3] = m_Anchor + CPoint (0,-abs (Diagish.m_X) * m_AspRat);
			else
				m_RectPoints[3] = m_Anchor + CPoint (0,abs (Diagish.m_X) * m_AspRat);
			//if
		}//if

		m_RectPoints[2].x = m_RectPoints[1].x;
		m_RectPoints[2].y = m_RectPoints[3].y;
	}
	else
	{
		m_RectPoints[1].x = m_CurrentPoint.x;
		m_RectPoints[1].y = m_Anchor.y;

		m_RectPoints[2]   = m_CurrentPoint;

		m_RectPoints[3].x = m_Anchor.x;
		m_RectPoints[3].y = m_CurrentPoint.y;
	}//if
}//SRubberRectContext::CalcPoints

const CPoint& SRubberRectContext::BaseL () const
{
	if (m_AllowRotation)
		return m_RectPoints[0];
	else
	{
		if (m_RectPoints[0].x < m_RectPoints[1].x)
		{
			if (m_RectPoints[0].y > m_RectPoints[3].y)
				return m_RectPoints[0];
			else
				return m_RectPoints[3];
			//if
		}
		else
		{
			if (m_RectPoints[1].y > m_RectPoints[2].y)
				return m_RectPoints[1];
			else
				return m_RectPoints[2];
			//if
		}//if
	}//if
}//SRubberRectContext::BaseL

const CPoint& SRubberRectContext::BaseR () const
{
	if (m_AllowRotation)
		return m_RectPoints[1];
	else
	{
		if (m_RectPoints[0].x > m_RectPoints[1].x)
		{
			if (m_RectPoints[0].y > m_RectPoints[3].y)
				return m_RectPoints[0];
			else
				return m_RectPoints[3];
			//if
		}
		else
		{
			if (m_RectPoints[1].y > m_RectPoints[2].y)
				return m_RectPoints[1];
			else
				return m_RectPoints[2];
			//if
		}//if
	}//if
}//SRubberRectContext::BaseR

const CPoint& SRubberRectContext::TopR () const
{
	if (m_AllowRotation)
		return m_RectPoints[2];
	else
	{
		if (m_RectPoints[0].x > m_RectPoints[1].x)
		{
			if (m_RectPoints[0].y > m_RectPoints[3].y)
				return m_RectPoints[3];
			else
				return m_RectPoints[0];
			//if
		}
		else
		{
			if (m_RectPoints[1].y > m_RectPoints[2].y)
				return m_RectPoints[2];
			else
				return m_RectPoints[1];
			//if
		}//if
	}//if
}//SRubberRectContext::TopR

void SRubberRectContext::Move 
(
	const CPoint&	Point,
	bool			Ctrl,
	bool			Shift
)
{
	ClearRect ();

	m_CurrentPoint = Point;

	DoMoveAction (Ctrl || Shift);

	DrawRect ();
}//SRubberRectContext::OnMouseMove

void SRubberRectContext::Complete      
(
	const CPoint&	Point,
	bool			Ctrl,
	bool			Shift
)
{
	ClearRect ();
	DoCompletionAction ();
}//SRubberRectContext::OnLBUp

HCURSOR SRubberRectContext::GetCursor () const
{
	if (!m_Initiated)
		return sm_CrossCursor;
	else if (m_CurrentPoint == m_Anchor)
		return sm_AllCursor;
	else if (m_CurrentPoint.x == m_Anchor.x)
		return sm_WECursor;
	else if (m_CurrentPoint.y == m_Anchor.y)
		return sm_NSCursor;
	else if (((m_CurrentPoint.x > m_Anchor.x) && (m_CurrentPoint.y > m_Anchor.y))
	      || ((m_CurrentPoint.x < m_Anchor.x) && (m_CurrentPoint.y < m_Anchor.y)))
		return sm_NWSECursor;
	else
		return sm_NESWCursor;
	//if
}//SRubberRectContext::GetCursor



