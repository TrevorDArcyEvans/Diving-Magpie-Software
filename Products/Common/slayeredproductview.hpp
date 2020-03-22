#ifndef _SLayeredProductView_hpp
#define _SLayeredProductView_hpp

#include <afxwin.h>

class IGlobalGraphics;

class SLayeredProductView:public CView
{
public:

	virtual IGeoGraphicsCtrl* GetGeoControl () {return 0;}
	virtual void LoadPlotLayer () {}
};//SLayeredProductView

#endif

