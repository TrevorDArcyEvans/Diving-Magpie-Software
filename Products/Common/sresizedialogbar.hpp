#ifndef __SResizeDialogBar_hpp
#define __SResizeDialogBar_hpp

#include <afxwin.h>
#include "SDialogSizer.hpp"

class SResizeDialogBar:public CDialogBar
{
private:

	bool					m_FirstTime;
	CString					m_RegName;
	int						m_SizeIdx;
	int						m_FixedWidth;
	int						m_FixedHeight;

protected:

	SDialogSizer	m_Sizer;

	void OnSize(UINT nType, int cx, int cy) ;
	void OnGetMinMaxInfo (MINMAXINFO* lpMMI);

	virtual void DoDeferSize (int cx,int cy) {}

	void SetRegName (const CString& Name) {m_RegName = Name;}

	SResizeDialogBar ():m_FirstTime (true),m_SizeIdx (-1),m_FixedWidth (0),m_FixedHeight (0) {}

	void SetFixedWidth () {m_FixedWidth = -1;}
	void SetFixedHeight () {m_FixedHeight = -1;}

public:

	virtual ~SResizeDialogBar () {}

	void LoadSizeFromReg ();
	static void SaveSizesToReg ();

	DECLARE_MESSAGE_MAP()
};//SResizeDialogBar

#endif

