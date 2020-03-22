/*
History:
    [01]    TDE     16May00     changed to use Pencil.h
*/

#ifndef __SEchoContext_hpp
#define __SEchoContext_hpp

#include <afx.h>
#include "Pencil.h" // [01]
#include "GeoGraphics.h"

class ICallback;
class CPoint;
class CPen;
class CDC;

enum EFinishOn {F_DOWN_FIRST,F_UP,F_DOWN_AGAIN,F_DBL_CLICK};

class SEchoContext
{
private:

	virtual void IntermediateClick (const CPoint& Point,bool Ctrl = false,bool Shift = false) {}

protected:

	ICallback*	m_OnAbort;
	ICallback*	m_OnCompletion;
	ICallback*	m_OnMove;

	EFinishOn	m_FinishOn;

	bool		m_CtrlShift;
	bool		m_Done;

	SEchoContext (EFinishOn	FinishOn);

public:

	void MouseDownFirst (const CPoint& Point,bool Ctrl = false,bool Shift = false);
	void MouseDownAgain (const CPoint& Point,bool Ctrl = false,bool Shift = false);
	void MouseMove		(const CPoint& Point,bool Ctrl = false,bool Shift = false);
	void MouseUp		(const CPoint& Point,bool Ctrl = false,bool Shift = false);
	void LButtonDblClk	(const CPoint& Point,bool Ctrl = false,bool Shift = false);

	virtual void Initiate (const CPoint& Point,bool Ctrl = false,bool Shift = false) = 0;
	virtual void Move     (const CPoint& Point,bool Ctrl = false,bool Shift = false) = 0;
	virtual void Complete (const CPoint& Point,bool Ctrl = false,bool Shift = false) = 0;
	virtual void Abort    ();

	virtual ~SEchoContext ();

	const bool& CtrlShift () const {return m_CtrlShift;}

    void SetAbortAction (ICallback* Action) {m_OnAbort = Action;}

	void SetCompletionAction (ICallback* Action) {m_OnCompletion = Action;}
	void DoCompletionAction ();

	void SetMoveAction (ICallback* Action) {m_OnMove = Action;}
	void DoMoveAction (bool CtrlShift = false);

	bool Done () const {return m_Done;}

	virtual HCURSOR GetCursor () const {return 0;}
};//SEchoContext

class SXORUsingEchoContext:public SEchoContext
{
private:

	CPen*	m_Pen;

protected:

	CDC*	m_DC;

	SXORUsingEchoContext (EFinishOn	FinishOn,CWnd* Window);
	virtual ~SXORUsingEchoContext ();
};//SXORUsingEchoContext

class SEchoController
{
private:

	ICallback*		m_OnTermination;
					
	EFinishOn		m_FinishOn;
	bool			m_Persistent;

	MouseModeEnum	m_MouseMode;

	SEchoContext*	m_Pending;
	SEchoContext*	m_Current;

	bool			m_AntiRecurse;

public:

	SEchoController ();
	~SEchoController ();

	void SetTerminationCallback (ICallback*	CBK) {m_OnTermination = CBK;}

	bool Active () const {return m_Pending || m_Current;}

	const EFinishOn& FinishOn () const {return m_FinishOn;}
	EFinishOn& FinishOn () {return m_FinishOn;}

	const bool& Persistent () const {return m_Persistent;}
	bool& Persistent () {return m_Persistent;}

	void SetMouseMode (MouseModeEnum MouseMode) {m_MouseMode = MouseMode;}
	MouseModeEnum GetMouseMode () const {return m_MouseMode;}

	void Initiate (SEchoContext* NewContext);

	void OnButtonDown		(unsigned nFlags,const CPoint& point);
	void OnMouseMove		(unsigned nFlags,const CPoint& point);
	void OnButtonUp			(unsigned nFlags,const CPoint& point);
	void OnLButtonDblClk	(unsigned nFlags,const CPoint& point);

	void Terminate (bool UseCallback = true);

	SEchoContext* GetContext () {return m_Current?m_Current:m_Pending;}

	void Abort ();

	HCURSOR GetCursor () const;
};//SEchoController

#endif

