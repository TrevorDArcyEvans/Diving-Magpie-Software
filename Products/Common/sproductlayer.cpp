/*
History:
    [01]    TDE     03Jul00     added include for SException
*/

#include "stdafx.h"
#include "GeoGraphics.h"
#include "GribSelection.h"
#include "gribdecoder.h"
#include "SProductLayer.hpp"
#include "SHResult.hpp"
#include "SStringPasser.hpp"
#include "SRegistry.hpp"
#include "SMainFrame.hpp"
#include "SLayeredProductView.hpp"

#include "SException.hpp"   // [01]

SProductLayer::SProductLayer ()
:m_View (0) 
{
	SMainFrame* Main = dynamic_cast <SMainFrame*> (::AfxGetMainWnd ());

	if (Main)
	{
		SLayeredProductView* LatestView = Main->GetLatestView ();

		if (LatestView)
			m_View = LatestView;
		//if
	}//if
}//SProductLayer::SProductLayer

void SProductLayer::SetLatestView 
(
	SLayeredProductView* View
)
{
	SMainFrame* Main = dynamic_cast <SMainFrame*> (::AfxGetMainWnd ());

	if (Main)
		Main->SetLatestView (View);
	//if
}//SProductLayer::SetLatestView

SGridProductLayer::SGridProductLayer 
(
	IGribDescriptor*	Descriptor,
	BOOL				HasGrid,
	BOOL				HasContour
)
:m_Descriptor	(Descriptor),
 m_HasGrid		(HasGrid),
 m_HasContour	(HasContour),
 m_Created		(false)
{
	if (m_Descriptor)
		m_Descriptor->AddRef ();
	//if
}//SGridProductLayer::SGridProductLayer

SGridProductLayer::~SGridProductLayer ()
{
	if (m_Descriptor)
		m_Descriptor->Release ();
	//if
}//SGridProductLayer::~SGridProductLayer

void SGridProductLayer::CreateGribLayer
(
	IGridViewer*	Grid,
	CArchive*		ar
)
{
	if (m_Created)
		return;
	//if

	m_Created = true;

	ISimpleGrid* Decoder;

	m_Descriptor->SetSearchPath (SRegistry::Instance ()->m_GeneralDataPath.AllocSysString ());
	m_Descriptor->SetAllLevels (IsVertical ());
	m_Descriptor->Generate ();
	m_Descriptor->GetGribLayer (0,&Decoder);

	BSTR DataTypeB;

	m_Descriptor->get_DataType (&DataTypeB);

	CString DataType = SStringPasser::GetCString (DataTypeB);

	if (Decoder)
	{
		((SMainFrame*)::AfxGetMainWnd ())->SetStatusText ("Loading " + DataType + " Grid...");
		DoLoadGrid (Grid,Decoder,ar);
	}
	else
		::AfxMessageBox (DataType + " grid unavailable",MB_OK);
	//if

	((SMainFrame*)::AfxGetMainWnd ())->SetStatusText ("Ready");
}//SGridProductLayer::CreateGribLayer

bool SGridProductLayer::DoLoadGrid 
(
	IGridViewer*	GeoCtrl,
	ISimpleGrid*	Grid,
	CArchive*		ar
)
{
	BOOL Ret;

	GeoCtrl->AddGrid (Grid,m_HasContour,(long)this,&Ret,(long)ar);

	return Ret;
}//SGridProductLayer::DoLoadGrid

void SGridProductLayer::OpenLayer 
(
	SLayeredProductView* View
)
{
	m_View = View;
	
	IGridViewer* Grid;

	SHResult Res = View->GetGeoControl ()->QueryInterface (IID_IGridViewer,(void**)&Grid);

	CreateGribLayer (Grid);

	Grid->Release ();
}//SGridProductLayer::OpenLayer

void SGridProductLayer::RemoveLayer 
(
	SLayeredProductView* View
)
{
	IGridViewer* Grid;

	SHResult Res = View->GetGeoControl ()->QueryInterface (IID_IGridViewer,(void**)&Grid);

	Grid->RemoveGridLayer ((long)this,true,true);

	Grid->Release ();
}//SGridProductLayer::RemoveLayer

void SGridProductLayer::AlterLayer  
(
	SLayeredProductView* View
)
{
	IGridViewer* Grid;

	SHResult Res = View->GetGeoControl ()->QueryInterface (IID_IGridViewer,(void**)&Grid);

	Grid->RemoveGridLayer ((long)this,!m_HasGrid,!m_HasContour);

	Grid->Release ();
}//SGridProductLayer::AlterLayer

void SGridProductLayer::CreateDescriptor ()
{
	HRESULT Res = ::CoCreateInstance (CLSID_SGribDescriptor,
									  0,
									  CLSCTX_ALL,
									  IID_IGribDescriptor,
									  (void**)&m_Descriptor);

	if (!SUCCEEDED (Res))
		throw new SException ("You do not have Grib Decoding installed on this system.");
	//if
}//SGridProductLayer::CreateDescriptor

IMPLEMENT_SERIAL (SGridProductLayer,CObject,1)

void SGridProductLayer::Serialize 
(
	CArchive& ar
)
{
	IGridViewer* Grid;

	SHResult Res = m_View->GetGeoControl ()->QueryInterface (IID_IGridViewer,(void**)&Grid);

	if (ar.IsStoring ())
	{
		BSTR AsString;

		m_Descriptor->Stringify (&AsString);
		
		ar << SStringPasser::GetCString (AsString);
		ar << m_HasContour;
		ar << m_HasGrid;
		
		Grid->SerializeGridDefinition ((long)&ar,(long)this);
	}
	else
	{
		CString AsString;

		ar >> AsString;

		if (!m_Descriptor)
			CreateDescriptor ();
		//if

		m_Descriptor->Destringify (AsString.AllocSysString ());

		ar >> m_HasContour;
		ar >> m_HasGrid;

		CreateGribLayer (Grid,&ar);
	}//if

	Grid->Release ();
}//SGridProductLayer::Serialize

IMPLEMENT_SERIAL (SAnnotationLayer,CObject,1)

bool SAnnotationLayer::IsEmpty ()
{
	if (m_View)
	{
		BOOL RetVal = FALSE;

		IAnnotation* Annot = 0;

		HRESULT Res = m_View->GetGeoControl ()->QueryInterface (__uuidof (IAnnotation),(void**)&Annot);

		if (SUCCEEDED (Res))
		{
			Annot->AnnotationEmpty (&RetVal);
			Annot->Release ();
		}//if

		return RetVal;
	}
	else
		return false;
	//if
}//SAnnotationLayer::IsEmpty

void SAnnotationLayer::OpenLayer   
(
	SLayeredProductView* View
)
{
	m_View = View;
}//SAnnotationLayer::OpenLayer

void SAnnotationLayer::RemoveLayer 
(
	SLayeredProductView* View
)
{
}//SAnnotationLayer::RemoveLayer

void SAnnotationLayer::AlterLayer  
(
	SLayeredProductView* View
)
{
}//SAnnotationLayer::AlterLayer

void SAnnotationLayer::Serialize 
(
	CArchive& ar
)
{
	if (m_View)
		m_View->GetGeoControl ()->SerializeAnnotation ((long)&ar);
	//if
}//SAnnotationLayer::Serialize

IMPLEMENT_SERIAL (SPlotLayer,CObject,1)

void SPlotLayer::OpenLayer   
(
	SLayeredProductView* View
)
{
	m_View->LoadPlotLayer ();
}//SPlotLayer::OpenLayer

void SPlotLayer::RemoveLayer 
(
	SLayeredProductView* View
)
{
}//SPlotLayer::RemoveLayer

void SPlotLayer::AlterLayer  
(
	SLayeredProductView* View
)
{
}//SPlotLayer::AlterLayer

void SPlotLayer::Serialize (CArchive& ar)
{
//	Nothing do do. This object just needs to exist
}//SPlotLayer::Serialize
