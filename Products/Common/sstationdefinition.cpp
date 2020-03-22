#include "stdafx.h"
#include "SStationDefinition.h"

SStationDefinition::SStationDefinition ()
//	Crazy values for invalidity
:m_Lat					(0.0),
 m_Long					(0.0),
 m_HeightMetres			(-2000),
 m_ID					(-1),
 m_StationClass			(E_UNKNOWN_STATION_CLASS),
 m_MainRunwayBearing	(-300.0)
{
}//SStationDefinition::SStationDefinition

SStationDefinition::SStationDefinition 
(
	const StationRecord& Other
)
{
//	No benefits to duplicating the code
	*this = Other;
}//SStationDefinition::SStationDefinition

SStationDefinition::~SStationDefinition ()
{
}//SStationDefinition::~SStationDefinition

SStationDefinition& SStationDefinition::operator = 
(
	const StationRecord& Other
)
{
	m_Lat				= Other.Latitude;
	m_Long				= Other.Longitude;
	m_HeightMetres		= Other.Altitude;
	m_ID				= Other.StationId;
	m_StationClass		= Other.StationClass;

//	Use CComBSTRs to make copying easy
	m_WMOCode	= Other.WmoCode;
	m_ICAOCode	= Other.IcaoCode;
	m_IATACode	= Other.IataCode;
	m_Name		= Other.StationName;
	m_Country	= Other.Country;

	return *this;
}//SStationDefinition::operator =

StationRecord& SStationDefinition::AssignTo 
(
	StationRecord& LVal
)const
{
	LVal.Latitude		= (float)m_Lat;
	LVal.Longitude		= (float)m_Long;
	LVal.Altitude		= (float)m_HeightMetres;
	LVal.StationId		= m_ID;
	LVal.StationClass	= m_StationClass;

	m_WMOCode.CopyTo (&LVal.WmoCode);
	m_ICAOCode.CopyTo (&LVal.IcaoCode);
	m_IATACode.CopyTo (&LVal.IataCode);
	m_Name.CopyTo (&LVal.StationName);
	m_Country.CopyTo (&LVal.Country);

	return LVal;
}//SStationDefinition::AssignTo

CString	SStationDefinition::GetHeightMetresStr	() const
{
	CString RetVal;

	if (m_HeightMetres < -1000)	// Not known
		RetVal = _T ("");
	else
		RetVal.Format (_T ("%d"),(int)m_HeightMetres);
	//if

	return RetVal;
}//SStationDefinition::GetHeightMetresStr

void SStationDefinition::SetHeightMetres	
(
	const CString& HeightString
)
{
	if (HeightString.IsEmpty ())
		m_HeightMetres = -2000;		// Invalid height
	else
	{
		m_HeightMetres = _ttoi (HeightString);

//		Non numeric string would produce zero
		if (m_HeightMetres == 0 && HeightString != _T ("0"))
			m_HeightMetres = -2000;
		//if
	}//if
}//SStationDefinition::SetHeightMetres

CComBSTR SStationDefinition::GetBestCode () const
{
	if (m_ICAOCode.Length () > 0)
		return m_ICAOCode;
	else if (m_WMOCode.Length () > 0)
		return m_WMOCode;
	else
		return m_IATACode;
	//if
}//SStationDefinition::GetBestCode

SStationDefinition::operator StationRecord () const
{
	StationRecord RetVal;

	RetVal.Latitude		= (float)m_Lat;
	RetVal.Longitude	= (float)m_Long;
	RetVal.Altitude		= (float)m_HeightMetres;
	RetVal.StationId	= m_ID;
	RetVal.StationClass	= m_StationClass;

	m_WMOCode.CopyTo (&RetVal.WmoCode);
	m_ICAOCode.CopyTo (&RetVal.IcaoCode);
	m_IATACode.CopyTo (&RetVal.IataCode);
	m_Name.CopyTo (&RetVal.StationName);
	m_Country.CopyTo (&RetVal.Country);

	return RetVal;
}//SStationDefinition::operator StationRecord
