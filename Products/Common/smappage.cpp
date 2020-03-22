#include "stdafx.h"
#include "SMapPage.hpp"
#include "SUseful.hpp"
#include "GeoGraphics.h"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(SMapPage,CObject,1)

SMapPage::SMapPage ()
:m_Projection	(""),		// An available projection will be chosen
 m_CentreLat    (0.0),
 m_CentreLong   (0.0),
 m_ViewWidthKm  (1500.0),
 m_Rotation		(0.0)
{
}//SMapPage::SMapPage

SMapPage::SMapPage 
(
	IGeoGraphicsCtrl* Ctrl
)
{
	Ctrl->GetMapPage (&m_CentreLat,&m_CentreLong,&m_Rotation,&m_ViewWidthKm);

	USES_CONVERSION;

	BSTR Proj;

	Ctrl->GetCurrentProjFullName (&Proj);

	m_Projection = OLE2T (Proj);
}//SMapPage::SMapPage

void SMapPage::SaveReg
(
	const CString&	Key,
	int				Idx	
)
{
	CWinApp* App = AfxGetApp ();

	CString Name;
	CString Value;

	Name.Format ("AreaProj%d",Idx);

	App->WriteProfileString (Key,Name,m_Projection);

	Name.Format ("AreaLat%d",Idx);
	Value.Format ("%f",m_CentreLat);
	App->WriteProfileString (Key,Name,Value);

	Name.Format ("AreaLong%d",Idx);
	Value.Format ("%f",m_CentreLong);
	App->WriteProfileString (Key,Name,Value);

	Name.Format ("AreaWidth%d",Idx);
	Value.Format ("%f",m_ViewWidthKm);
	App->WriteProfileString (Key,Name,Value);

	Name.Format ("AreaRot%d",Idx);
	Value.Format ("%f",m_Rotation);
	App->WriteProfileString (Key,Name,Value);
}//SMapPage::SaveReg

void SMapPage::LoadReg
(
	const CString&	Key,
	int				Idx	
)
{
	CWinApp* App = AfxGetApp ();

	CString Name;

	Name.Format ("AreaProj%d",Idx);
	m_Projection = App->GetProfileString (Key,Name,m_Projection);

	Name.Format ("AreaLat%d",Idx);
	m_CentreLat = atof (App->GetProfileString (Key,Name,""));

	Name.Format ("AreaLong%d",Idx);
	m_CentreLong = atof (App->GetProfileString (Key,Name,""));

	Name.Format ("AreaWidth%d",Idx);
	m_ViewWidthKm = atof (App->GetProfileString (Key,Name,""));

	Name.Format ("AreaRot%d",Idx);
	m_Rotation = atof (App->GetProfileString (Key,Name,""));
}//SMapPage::LoadReg

void SMapPage::Serialize 
(
	CArchive& Arc
)
{
	if (Arc.IsStoring())
	{
		Arc << m_Projection 
			<< m_CentreLat 
			<< m_CentreLong
			<< m_ViewWidthKm
			<< m_Rotation;
 	}
	else
	{
		Arc >> m_Projection 
			>> m_CentreLat 
			>> m_CentreLong
			>> m_ViewWidthKm
			>> m_Rotation;
	}//if
}//SMapPage::Serialize

SMapPage& SMapPage::operator = 
(
	const SMapPage& RVal
)
{
	m_Projection  = RVal.m_Projection;
	m_CentreLat   = RVal.m_CentreLat;
	m_CentreLong  = RVal.m_CentreLong;
	m_ViewWidthKm = RVal.m_ViewWidthKm;
	m_Rotation	  = RVal.m_Rotation;

	return *this;
}//SMapPage::operator =

bool SMapPage::operator != 
(
	const SMapPage& RVal
)const
{  
	return 	(m_Projection  != RVal.m_Projection)
		 || !SUseful::CloseEnoughAbs (m_CentreLat,RVal.m_CentreLat,0.00001)
		 || !SUseful::CloseEnoughAbs (m_CentreLong,RVal.m_CentreLong,0.00001)
		 || !SUseful::CloseEnoughAbs (m_ViewWidthKm,RVal.m_ViewWidthKm,0.00001)
		 || !SUseful::CloseEnoughAbs (m_Rotation,RVal.m_Rotation,0.00001);
}//SMapPage::operator != 

bool SMapPage::operator == 
(
	const SMapPage& RVal
)const
{
	return 	(m_Projection  == RVal.m_Projection)
		 && SUseful::CloseEnoughAbs (m_CentreLat,RVal.m_CentreLat,0.00001)
		 && SUseful::CloseEnoughAbs (m_CentreLong,RVal.m_CentreLong,0.00001)
		 && SUseful::CloseEnoughAbs (m_ViewWidthKm,RVal.m_ViewWidthKm,0.00001)
		 && SUseful::CloseEnoughAbs (m_Rotation,RVal.m_Rotation,0.00001);
}//SMapPage::operator == 


	


