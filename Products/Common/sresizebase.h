#ifndef __SResizeBase_h
#define __SResizeBase_h

#include <vector>

enum EAttachments {A_NONE = 0,
				   A_TOP  = 1,
				   A_BOTTOM = 2,
				   A_LEFT	= 4,
				   A_RIGHT  = 8,
				   A_ALL    = 15,
				   A_V_CENT	= 16,
				   A_H_CENT	= 32,
				   A_V_PROPORTION = 64,
				   A_H_PROPORTION = 128,
				   A_MANUAL_H = 256,
				   A_MANUAL_V = 512};

//  Forward declarations for friends
class SControlSizer;
class SResizeBase;

class SSizeItem
{
friend class SControlSizer;
friend class SResizeBase;

private:

	enum EComb 
	{	
		C_NONE,
		HS_LEFT,HS_CENTRE,HS_LEFT_AND_RIGHT,HS_RIGHT,HS_LEFT_AND_CENT,HS_RIGHT_AND_CENT,
		VS_TOP,VS_CENTRE,VS_TOP_AND_BOTTOM,VS_BOTTOM,VS_TOP_AND_CENT,VS_BOTTOM_AND_CENT,
		HS_LEFTPROP,HS_RIGHTPROP,
		VS_TOPPROP,VS_BOTTOMPROP,
        HS_FRACTIONAL,VS_FRACTIONAL
	};

	HWND	m_Control;
	RECT	m_InitialPos;
	int		m_Attachments;

    double m_TopFrac;
    double m_BottomFrac;
    double m_LeftFrac;
    double m_RightFrac;

	EComb HStretchType () const;
	EComb VStretchType () const;

	static RECT ToParentSystem (HWND Control,const RECT& Rect);

	SSizeItem (HWND Control,int Attachments);
	void Resize (const SIZE& OldSize,const SIZE& NewSize);
	void Redraw ();

public:

    void SetHorizontalProportions (double LeftFraction,double RightFraction);
    void SetVerticalProportions   (double TopFraction,double BottomFraction);
};//SSizeItem

typedef std::vector <SSizeItem*> SSizeItemVector;

class SControlSizer
{
private:

	SSizeItemVector	m_Items;
	SIZE			m_InitialSize;

public:

	SControlSizer () {m_InitialSize.cx = m_InitialSize.cx = 0;}
	virtual ~SControlSizer ();

	void Initialize (int cx,int cy) {m_InitialSize.cx = cx; m_InitialSize.cy = cy;}

	SSizeItem* AddItem (HWND Control,int Attachments);

	void Resize (const SIZE& NewSize);
};//SControlSizer

//	Base class for any window class that wants to resize
class SResizeBase
{
private:

	bool	m_FirstTime;

	int		m_MinWid;				// Minimum width -1 = any
	int		m_MaxWid;				// Maximum width -1 = any
	int		m_MinHei;				// Minimum height -1 = any
	int		m_MaxHei;				// Maximum height -1 = any

	HWND	m_MinMaxDeferral;		// Ask this window for min/max data

	virtual const HWND& GetHWND () const  = 0;
    virtual SIZE GetDesiredExtent () const;   // Returns the size the dialog would like to be
    virtual void DoDeferSize (int cx,int cy) {}

    void InitializeNow ();

protected:

    SControlSizer m_Sizer;

	void InnerOnSize	(UINT Type, int cx, int cy);
	void InnerGetMinMax (MINMAXINFO* Info) const;

	void SetMinSize			(int MinWid,int MinHeight);
	void SetMaxSize			(int MaxWid,int MaxHeight);
	void AddBordersToMinMax ();				// Take account of caption and borders in min max

//	Use another window for min/max
	void SetMinMaxDeferral	(const HWND& Window) {m_MinMaxDeferral = Window;} 

	bool IsFirstTime () const {return m_FirstTime;}

public:
	
	SResizeBase ():m_FirstTime (true),
				   m_MinWid (-1),
				   m_MaxWid (-1),
				   m_MinHei (-1),
				   m_MaxHei (-1),
				   m_MinMaxDeferral (0) {}
};//SResizeBase

#endif
