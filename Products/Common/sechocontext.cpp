#include "stdafx.h"
#include "SEchoContext.hpp"
#include "ICallback.hpp"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SEchoContext::SEchoContext 
(
	EFinishOn	FinishOn
)
:m_OnAbort          (0),
 m_OnCompletion		(0),
 m_OnMove			(0),
 m_Done				(false),
 m_FinishOn			(FinishOn),
 m_CtrlShift		(false)
{
}//SEchoContext::SEchoContext

SEchoContext::~SEchoContext () 
{
	if (m_OnCompletion)
		delete m_OnCompletion;
	//if

	if (m_OnMove)
		delete m_OnMove;
	//if
}//SEchoContext::~SEchoContext

void SEchoContext::MouseDownFirst
(
	const CPoint&	Point,
	bool			Ctrl,
	bool			Shift
)
{
	m_CtrlShift = Ctrl || Shift;

	switch (m_FinishOn)
	{
		case F_DOWN_FIRST:	Initiate (Point,Ctrl,Shift);
							Complete (Point,Ctrl,Shift);
							m_Done = true;
							break;

		default:			Initiate (Point,Ctrl,Shift);
							break;
	}//switch
}//SEchoContext::MouseDownFirst

void SEchoContext::MouseDownAgain
(
	const CPoint&	Point,
	bool			Ctrl,
	bool			Shift
)
{
	m_CtrlShift = Ctrl || Shift;

	switch (m_FinishOn)
	{
		default:				Complete (Point,Ctrl,Shift);
								m_Done = true;
								break;

		case F_DBL_CLICK:		IntermediateClick (Point,Ctrl,Shift);
								break;
	}//switch
}//SEchoContext::MouseDownFirst

void SEchoContext::LButtonDblClk	
(
	const CPoint&	Point,
	bool			Ctrl,
	bool			Shift
)
{
	m_CtrlShift = Ctrl || Shift;

	Complete (Point,Ctrl,Shift);
	m_Done = true;
}//SEchoContext::LButtonDblClk

void SEchoContext::MouseMove 
(
	const CPoint&	Point,
	bool			Ctrl,
	bool			Shift
)
{
	m_CtrlShift = Ctrl || Shift;

	Move (Point,Ctrl,Shift);
}//SEchoContext::MouseMove

void SEchoContext::MouseUp   
(
	const CPoint&	Point,
	bool			Ctrl,
	bool			Shift
)
{
	m_CtrlShift = Ctrl || Shift;

	if (m_FinishOn == F_UP)
	{
		Complete (Point,Ctrl,Shift);
		m_Done = true;
	}//if
}//SEchoContext::MouseUp


void SEchoContext::DoCompletionAction ()
{
	if (m_OnCompletion)
		m_OnCompletion->Invoke ();
	//if
}//SEchoContext::DoCompletionAction

void SEchoContext::DoMoveAction 
(
	bool CtrlShift
)
{
	m_CtrlShift = CtrlShift;

	if (m_OnMove)
		m_OnMove->Invoke ();
	//if
}//SEchoContext::DoMoveAction

void SEchoContext::Abort ()
{
	ICallback*	OldOnCompletion = m_OnCompletion;

	m_OnCompletion = m_OnAbort;

	Complete (CPoint (0,0),false,false);

	m_OnCompletion = OldOnCompletion;
}//SEchoContext::Abort

SXORUsingEchoContext::SXORUsingEchoContext 
(
	EFinishOn	FinishOn,
	CWnd*		Window
)
:SEchoContext (FinishOn)
{
	if (Window)
	{
		m_DC = new CClientDC (Window);

		m_Pen = new CPen (PS_SOLID,2,RGB (0,0,0));

		m_DC->SelectObject (m_Pen);
		m_DC->SetROP2 (R2_NOT);
	}//if
}//SXORUsingEchoContext::SXORUsingEchoContext

SXORUsingEchoContext::~SXORUsingEchoContext ()
{
	if (m_DC)
		delete m_DC;
	//if

	if (m_Pen)
		delete m_Pen;
	//if
}//SXORUsingEchoContext::~SXORUsingEchoContext

SEchoController::SEchoController ()
:m_FinishOn			(F_DOWN_AGAIN),
 m_Persistent		(false),
 m_MouseMode		(EMOUSE_NONE),
 m_Pending			(0),
 m_Current			(0),
 m_OnTermination	(0),
 m_AntiRecurse		(false)
{
}//SEchoController::SEchoController

SEchoController::~SEchoController ()
{
	if (m_OnTermination)
	{
//		Do this before calling terminate because callback object probably already destroyed
		delete m_OnTermination;
		m_OnTermination = 0;
	}//if

	Terminate ();
}//SEchoController::~SEchoController

void SEchoController::Initiate 
(
	SEchoContext* NewContext
)
{
	Terminate (false);

	m_Pending = NewContext;
}//SEchoController::Initiate

void SEchoController::OnButtonDown 
(
	unsigned		nFlags,
	const CPoint&	point
)
{
	if (m_Pending)
	{
		m_Pending->MouseDownFirst (point,nFlags&MK_CONTROL,nFlags&MK_SHIFT);

		if (m_Pending->Done ())
			Terminate ();
		else
		{
			m_Current  = m_Pending;
			m_Pending = 0;
		}//if
	}
	else if (m_Current)
	{
		m_Current->MouseDownAgain (point,nFlags&MK_CONTROL,nFlags&MK_SHIFT);

		if (m_Current->Done ())
			Terminate ();
		//if
	}//if
}//SEchoController::OnButtonDown

void SEchoController::OnMouseMove  
(
	unsigned		nFlags,
	const CPoint&	point
)
{
	if (m_Current)
	{
		m_Current->MouseMove (point,nFlags&MK_CONTROL,nFlags&MK_SHIFT);

		if (m_Current->Done ())
			Terminate ();
		//if
	}//if
}//SEchoController::OnMouseMove

void SEchoController::OnButtonUp   
(
	unsigned		nFlags,
	const CPoint&	point
)
{
	if (m_Current)
	{
		m_Current->MouseUp (point,nFlags&MK_CONTROL,nFlags&MK_SHIFT);

		if (m_Current->Done ())
			Terminate ();
		//if
	}//if
}//SEchoController::OnButtonUp
	
void SEchoController::OnLButtonDblClk	
(
	unsigned		nFlags,
	const CPoint&	point
)
{
	if (m_Current)
	{
		m_Current->LButtonDblClk (point,nFlags&MK_CONTROL,nFlags&MK_SHIFT);

		if (m_Current->Done ())
			Terminate ();
		//if
	}//if
}//SEchoController::OnLButtonDblClk

void SEchoController::Terminate 
(
	bool UseCallback
)
{
	if (!m_AntiRecurse)
	{
		m_AntiRecurse = true;

		if (m_Pending)
		{
			delete m_Pending;
			m_Pending = 0;
		}//if

		if (m_Current)
		{
			delete m_Current;
			m_Current = 0;
		}//if

		if (UseCallback && m_OnTermination)
			m_OnTermination->Invoke ();
		//if

		if (!m_Persistent)
			m_MouseMode = EMOUSE_NONE;
		//if

		m_AntiRecurse = false;
	}//if
}//SEchoController::Terminate

HCURSOR SEchoController::GetCursor () const
{
	if (m_Current)
		return m_Current->GetCursor ();
	else if (m_Pending)
		return m_Pending->GetCursor ();
	else
		return 0;
	//if
}//SEchoController::GetCursor

void SEchoController::Abort ()
{
	if (m_Current)
		m_Current->Abort ();
	//if

	Terminate (false);
}//SEchoController::Abort






