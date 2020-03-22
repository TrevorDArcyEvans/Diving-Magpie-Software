#ifndef _SMainFrame_hpp
#define _SMainFrame_hpp

#include "GeoGraphics.h"

class SLayeredProductView;

class SMainFrame:public CMDIFrameWnd
{
public:

	virtual void SetStatusText (const CString& Text) = 0;
	virtual void GiveGeoGraphics (IGeoGraphicsCtrl* Control,bool IsMap) = 0;
	virtual void SetLatestView (SLayeredProductView* View) = 0;
	virtual SLayeredProductView* GetLatestView () = 0;
};//SMainFrame

#endif




