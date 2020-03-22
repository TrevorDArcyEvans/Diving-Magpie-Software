#ifndef __SModelessDialog_hpp
#define __SModelessDialog_hpp

#include "SResizeDialog.hpp"
#include <afxwin.h>

class SModelessDialog:public SResizeDialog
{
private:

	int		m_IDD;
	bool	m_AlreadyCreated;
	bool	m_SelfDestruct;

	bool	m_IsOpen;

	bool	m_IsShown;

	static CObArray	sm_AllDialogs;

protected:

	int	 m_ShowStyle;

	void OnOK();
	void OnCancel();
	void PostNcDestroy ();
	
	void SetSelfDestruct (bool SD) {m_SelfDestruct = SD;}
	void SetNoAutoClose ();

	SModelessDialog (int IDD,CWnd* pParent = NULL);

public:

	virtual ~SModelessDialog ();

	BOOL OnInitDialog();

	bool DoModeless (CWnd* Parent = 0);

	virtual void OnPrint (CDC* pDC,CPrintInfo* pInfo) {}
	virtual int  GetPageCount (CDC* pDC) {return 0;}

	void Close ();

	static void CloseAll ();

	bool IsOpen () const;

	void Show ();
	void Hide ();

	bool IsShown () const {return m_IsShown;}
};//SModelessDialog

#endif

