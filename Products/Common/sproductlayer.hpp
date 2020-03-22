#ifndef _SProductLayer_hpp
#define _SProductLayer_hpp

#include "GribSelection.h"
#include "gribdecoder.h"

class SLayeredProductView;
class IGridViewer;

class SProductLayer:public CObject
{
protected:

	SLayeredProductView*	m_View;

public:

	SProductLayer ();
	virtual ~SProductLayer () {}

	void SetView (SLayeredProductView* View) {m_View = View;}

	virtual void OpenLayer   (SLayeredProductView* View) = 0;
	virtual void RemoveLayer (SLayeredProductView* View) = 0;
	virtual void AlterLayer  (SLayeredProductView* View) = 0;

	virtual bool IsEmpty () {return false;}

	static void SetLatestView (SLayeredProductView* View);
};//SProductLayer

class SGridProductLayer:public SProductLayer
{
DECLARE_SERIAL (SGridProductLayer)

private:

	IGribDescriptor*	m_Descriptor;
	BOOL				m_HasGrid;

	bool				m_Created;

	void CreateDescriptor ();
	void CreateGribLayer (IGridViewer* Grid,CArchive* ar = 0);
	virtual bool DoLoadGrid (IGridViewer* GeoCtrl,ISimpleGrid* Grid,CArchive* ar);
	virtual bool IsVertical () {return false;}

protected:

	BOOL				m_HasContour;

public:

	SGridProductLayer ():m_HasGrid (true),m_HasContour (true),m_Descriptor (0),m_Created (false) {}
	SGridProductLayer (IGribDescriptor* Descriptor,BOOL HasGrid = true,BOOL HasContour = true);
	virtual ~SGridProductLayer ();

	void OpenLayer	 (SLayeredProductView* View);
	void RemoveLayer (SLayeredProductView* View);
	void AlterLayer  (SLayeredProductView* View);

	void SetGrid    (bool On) {m_HasGrid = On;}
	void SetContour (bool On) {m_HasContour = On;}

	void Serialize (CArchive& ar);

};//SGridProductLayer

class SAnnotationLayer:public SProductLayer
{
DECLARE_SERIAL (SAnnotationLayer)

public:

	SAnnotationLayer () {}
	virtual ~SAnnotationLayer () {}

	void OpenLayer   (SLayeredProductView* View);
	void RemoveLayer (SLayeredProductView* View);
	void AlterLayer  (SLayeredProductView* View);

	bool IsEmpty ();

	void Serialize (CArchive& ar);
};//SAnnotationLayer

class SPlotLayer:public SProductLayer
{
DECLARE_SERIAL (SPlotLayer)

public:

	SPlotLayer () {}
	virtual ~SPlotLayer () {}

	void OpenLayer   (SLayeredProductView* View);
	void RemoveLayer (SLayeredProductView* View);
	void AlterLayer  (SLayeredProductView* View);

	void Serialize (CArchive& ar);
};//SPlotLayer

#endif

