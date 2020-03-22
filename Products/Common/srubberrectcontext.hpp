#ifndef __SRubberRectContext_hpp
#define __SRubberRectContext_hpp

#include "SEchoContext.hpp"
#include <afxwin.h>

class SRubberRectContext:public SEchoContext
{
private:

	static HCURSOR	sm_AllCursor;
	static HCURSOR	sm_CrossCursor;
	static HCURSOR	sm_NWSECursor;
	static HCURSOR	sm_NESWCursor;
	static HCURSOR	sm_WECursor;
	static HCURSOR	sm_NSCursor;

	bool	m_Initiated;

	CPoint	m_Anchor;
	CPoint	m_CurrentPoint; 

	bool	m_AllowRotation;
	bool	m_FixAspRat;
	bool	m_RectDrawn;

	double	m_AspRat;
	CDC*	m_DC;
	CPen*	m_Pen;

	CPoint	m_RectPoints[5];

	void CalcPoints ();
	void DrawIt ();

public:

	SRubberRectContext (bool		AllowRotation	= false,
						bool		FixAspRat		= true,
						EFinishOn	FinishOn		= F_DOWN_AGAIN,
						CWnd* 		Window			= 0,
						double		AspRat			= 1.0);

	virtual ~SRubberRectContext ();

	void ClearRect ();
	void Move (const CPoint& Point);
	void DrawRect ();

	const CPoint& BaseL () const;
	const CPoint& BaseR () const;
	const CPoint& TopR  () const;

	CRect AsRect () const;

	void Initiate (const CPoint& Point,bool Ctrl = false,bool Shift = false);
	void Move     (const CPoint& Point,bool Ctrl = false,bool Shift = false);
	void Complete (const CPoint& Point,bool Ctrl = false,bool Shift = false);

	HCURSOR GetCursor () const;
};//SRubberRectContext

#endif

