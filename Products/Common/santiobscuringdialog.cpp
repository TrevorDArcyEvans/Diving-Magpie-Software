#include "SAntiObscuringDialog.hpp"
#include "SUseful.hpp"

SAntiObscuringDialog::SAntiObscuringDialog 
(
	int		IDD,
	CWnd*	pParent
)
:SModelessDialog(IDD, pParent)
{
	m_ToAvoid.SetRectEmpty ();
}//SAntiObscuringDialog::SAntiObscuringDialog

void SAntiObscuringDialog::Avoid 
(
	long Left,
	long Top,
	long Right,
	long Bottom
)
{
	m_ToAvoid.SetRect (Left,Top,Right,Bottom);
}//SActualDialog::Avoid

BOOL SAntiObscuringDialog::OnInitDialog () 
{
	BOOL RetVal = CDialog::OnInitDialog ();

	if (m_ToAvoid.IsRectNull ())
		return RetVal;
	//if

	CRect Rect;
	GetWindowRect (Rect);

	int ScrWidth  = GetSystemMetrics (SM_CXFULLSCREEN);
	int ScrHeight = GetSystemMetrics (SM_CYFULLSCREEN);

    if ((m_ToAvoid.BottomRight ().x < 0)
	 || (m_ToAvoid.BottomRight ().y < 0)
	 || (m_ToAvoid.TopLeft ().x > ScrWidth)
	 || (m_ToAvoid.TopLeft ().y > ScrHeight))
		return RetVal;
	//if
	
	int DlgWidth  = Rect.Width ();
	int DlgHeight = Rect.Height ();

	int BotCut   = DlgHeight - ScrHeight + m_ToAvoid.BottomRight ().y;
	int TopCut   = DlgHeight - m_ToAvoid.TopLeft ().y;
	int RightCut = DlgWidth  - ScrWidth + m_ToAvoid.BottomRight ().x;
	int LeftCut  = DlgWidth  - m_ToAvoid.TopLeft ().x;

	int WhichOne = -1;
	bool Trunc = false;

	if (BotCut < 0)
		WhichOne = 0;
	else if (TopCut < 0)
		WhichOne = 1;
	else if (RightCut < 0)
		WhichOne = 2;
	else if (LeftCut < 0)
		WhichOne = 3;
	else 
	{
		WhichOne = SUseful::MinOf (BotCut,TopCut,RightCut,LeftCut);
		Trunc = true;
	}//if

	int PosX;
	int PosY;

	switch (WhichOne)
	{
		default:
		case 0:		PosX = (ScrWidth - DlgWidth)/2;
					if (Trunc)
						PosY = ScrHeight -  DlgHeight;
					else
						PosY = m_ToAvoid.BottomRight ().y;
					//if
					break;

		case 1:		PosX = (ScrWidth - DlgWidth)/2;
					if (Trunc)
						PosY = 0;
					else
						PosY = m_ToAvoid.TopLeft ().y - DlgHeight;
					//if
					break;

		case 2:		if (Trunc)
						PosX = ScrWidth - DlgWidth;
					else
						PosX = m_ToAvoid.BottomRight ().x;
					//if
					PosY = (ScrHeight - DlgHeight)/2;
					break;

		case 3:		if (Trunc)
						PosX = 0;
					else
						PosX = m_ToAvoid.TopLeft ().x - DlgWidth;
					//if
					PosY = (ScrHeight - DlgHeight)/2;
					break;
	}//switch

	SetWindowPos (0,PosX,PosY,0,0,SWP_NOSIZE|SWP_NOZORDER);

	return RetVal;
}//SAntiObscuringDialog::OnInitDialog

