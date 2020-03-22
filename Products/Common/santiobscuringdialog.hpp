#ifndef __SAntiObscuringDialog_hpp
#define __SAntiObscuringDialog_hpp

#include "SModelessDialog.hpp" 

class SAntiObscuringDialog:public SModelessDialog
{
private:

	CRect	m_ToAvoid;

protected:

	SAntiObscuringDialog (int IDD,CWnd* pParent = NULL);

public:

	void Avoid (long Left,long Top,long Right,long Bottom);

	BOOL OnInitDialog();
};//SAntiObscuringDialog

#endif

