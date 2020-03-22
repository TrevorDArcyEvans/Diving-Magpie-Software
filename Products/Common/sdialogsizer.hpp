#ifndef __SDialogSizer_hpp
#define __SDialogSizer_hpp

#include <afxtempl.h>
#include <afxwin.h>

enum EAttachments {A_NONE = 0,
				   A_TOP  = 1,
				   A_BOTTOM = 2,
				   A_LEFT	= 4,
				   A_RIGHT  = 8,
				   A_V_CENT	= 16,
				   A_H_CENT	= 32,
				   A_V_PROPORTION = 64,
				   A_H_PROPORTION = 128,
				   A_MANUAL_H = 256,
				   A_MANUAL_V = 512};

class SSizeableItem
{
private:

	enum EComb {C_NONE,HS_LEFT,HS_CENTRE,HS_LEFT_AND_RIGHT,HS_RIGHT,
					   VS_TOP,VS_CENTRE,VS_TOP_AND_BOTTOM,VS_BOTTOM,
					   HS_LEFTPROP,HS_RIGHTPROP,
					   VS_TOPPROP,VS_BOTTOMPROP};

	CWnd*	m_Control;
	CRect	m_InitialPos;
	int		m_Attachments;

	EComb HStretchType () const;
	EComb VStretchType () const;

public:

	SSizeableItem (CWnd* Control,int Attachments);
	void Resize (const CSize& OldSize,const CSize& NewSize);
	void Redraw ();
};//SSizeableItem

typedef CArray <SSizeableItem*,SSizeableItem*> SSizeableItemArray;

class SDialogSizer
{
private:

	SSizeableItemArray	m_Items;
	CSize				m_InitialSize;

public:

	SDialogSizer ():m_InitialSize (0,0) {}
	virtual ~SDialogSizer ();

	void Initialize (const CSize& Size) {m_InitialSize = Size;}

	void AddItem (CWnd* Control,int Attachments);

	void Resize (const CSize& NewSize);
};//SDialogSizer

#endif

