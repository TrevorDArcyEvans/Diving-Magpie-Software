#ifndef __SResizeDialog_hpp
#define __SResizeDialog_hpp

#include <afxwin.h>
#include "SDialogSizer.hpp"

class SSizeSaver
{
public:

	CString m_Name;
	int		m_ClientWidth;
	int		m_ClientHeight;
	int		m_WindowWidth;
	int		m_WindowHeight;
	int		m_WindowTLX;
	int		m_WindowTLY;

	SSizeSaver (const CString& Name = "",
				int ClientWidth = 0,
				int ClientHeight = 0,
				int WindowWidth = 0,
				int WindowHeight = 0,
				int TLX = 0,
				int TLY = 0):m_Name (Name),
		                     m_ClientWidth  (ClientWidth),
							 m_ClientHeight (ClientHeight),
							 m_WindowWidth  (WindowWidth),
							 m_WindowHeight (WindowHeight),
							 m_WindowTLX (TLX),
							 m_WindowTLY (TLY) {}
	
	void SaveSizeToReg () const;
};//SSizeSaver

typedef CArray <SSizeSaver,SSizeSaver&> SSizeSaverArray;

class SResizeDialog:public CDialog
{
private:

	bool					m_FirstTime;
	bool					m_SkipOne;
	static SSizeSaverArray	sm_Sizes;
	int						m_SizeIdx;
	int						m_FixedWidth;
	int						m_FixedHeight;
	CSize					m_MinSize;
	CRect					m_CurrWindRect;
	CRect					m_CurrClientRect;
	bool					m_InitializeNowCalled;

protected:

	SDialogSizer	m_Sizer;
	CString			m_RegName;

	void OnSize(UINT nType, int cx, int cy) ;
	void OnMove(int x, int y) ;
	void OnGetMinMaxInfo (MINMAXINFO* lpMMI);
	virtual BOOL OnInitDialog();

	virtual void DoDeferSize (int cx,int cy) {}

	void SetRegName (const CString& Name) {m_RegName = Name;}

	SResizeDialog (int IDD,CWnd* pParent = NULL):CDialog (IDD,pParent),
												 m_FirstTime (true),
												 m_SizeIdx (-1),
												 m_FixedWidth (0),
												 m_FixedHeight (0),
												 m_MinSize (0,0),
												 m_SkipOne (false),
												 m_InitializeNowCalled (false) {}

	void SetFixedWidth () {m_FixedWidth = -1;}
	void SetFixedHeight () {m_FixedHeight = -1;}

	void SetMinSize (const CSize& Size) {m_MinSize = Size;}

	void InitializeNow ();

	void InitResizing ();

	void SkipOne () {m_SkipOne = true;}

public:

	virtual ~SResizeDialog ();

	void TransferCurrentPos () const;

	void LoadSizeFromReg ();
	static void SaveSizesToReg ();

	DECLARE_MESSAGE_MAP()
};//SModelessDialog

#endif

