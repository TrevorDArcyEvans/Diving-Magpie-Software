#ifndef __SMapPage_hpp
#define __SMapPage_hpp

#include <afx.h>
#include "GeoGraphics.h"

class SMapPage:public CObject
{
DECLARE_SERIAL(SMapPage)

public:

	CString		m_Projection;
	double		m_CentreLat;
	double		m_CentreLong;
	double		m_ViewWidthKm;
	double		m_Rotation;

	SMapPage ();
	SMapPage (IGeoGraphicsCtrl* Ctrl);

	virtual ~SMapPage () {}

	void SaveReg (const CString& Key,int Idx);
	void LoadReg (const CString& Key,int Idx);

	void Serialize (CArchive& Arc);

	SMapPage& operator = (const SMapPage& RVal);

	bool operator != (const SMapPage& RVal) const;
	bool operator == (const SMapPage& RVal) const;
};//SMapPage

#endif


