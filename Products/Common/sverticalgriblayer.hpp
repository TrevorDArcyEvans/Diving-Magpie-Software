#ifndef _SVerticalGribLayer_hpp
#define _SVerticalGribLayer_hpp

#include "GeoGraphics.h"
#include "SProductLayer.hpp"

class SVerticalGribLayer:public SGridProductLayer
{
DECLARE_SERIAL (SVerticalGribLayer)

private:

	bool DoLoadGrid (IGridViewer* GeoCtrl,ISimpleGrid* Grid,CArchive* ar);
	bool IsVertical () {return true;}

public:
	
	SVerticalGribLayer () {}
	SVerticalGribLayer (IGribDescriptor* Descriptor,BOOL HasGrid = true,BOOL HasContour = true);
	virtual ~SVerticalGribLayer () {}

	void Serialize (CArchive& ar);
};//SVerticalGribLayer

#endif

