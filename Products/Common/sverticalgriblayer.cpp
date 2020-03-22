#include "stdafx.h"
#include "geographics.h"
#include "SVerticalGribLayer.hpp"
#include "SCrossSectionDoc.h"
#include "SLayeredProductView.hpp"

SVerticalGribLayer::SVerticalGribLayer 
(
	IGribDescriptor*	Descriptor,
	BOOL				HasGrid,
	BOOL				HasContour
)
:SGridProductLayer (Descriptor,HasGrid,HasContour)
{
}//SVerticalGribLayer::SVerticalGribLayer

void SVerticalGribLayer::Serialize 
(
	CArchive& ar
)
{
	SGridProductLayer::Serialize (ar);
}//SVerticalGribLayer::Serialize

bool SVerticalGribLayer::DoLoadGrid 
(
	IGridViewer*	GeoCtrl,
	ISimpleGrid*	Grid,
	CArchive*		ar
)
{
	BOOL Ret = FALSE;

	IVerticalGrid* VGrid;

	Grid->QueryInterface (IID_IVerticalGrid,(void**)&VGrid);

	SCrossSectionDoc* Doc = dynamic_cast <SCrossSectionDoc*> (m_View->GetDocument ());

	if (Doc && VGrid)
	{
		VGrid->SetLinearMap (Doc->LinearMap ());

		GeoCtrl->AddVerticalGrid (VGrid,m_HasContour,(long)this,&Ret,(long)ar);

		VGrid->Release ();
	}//if

	return Ret;
}//SVerticalGribLayer::DoLoadGrid

IMPLEMENT_SERIAL (SVerticalGribLayer,SGridProductLayer,1)


