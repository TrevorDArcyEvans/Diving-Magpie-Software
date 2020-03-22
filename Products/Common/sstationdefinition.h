#ifndef _SStationDefinition_h
#define _SStationDefinition_h

#include "MeteoDataTypes.h"

#ifndef _AFX
#include "MFCStringImpl.h"
using NotMFC::CString ;
#endif

// Based on the structure StationDefinition
class SStationDefinition
{
private:

	mutable CComBSTR	m_WMOCode;
	mutable CComBSTR	m_ICAOCode;
	mutable CComBSTR	m_IATACode;
	mutable CComBSTR	m_Name;
	mutable CComBSTR	m_Country;
	double				m_Lat;
	double				m_Long;
	double				m_HeightMetres;
	int					m_ID;
	StationClassEnum	m_StationClass;
	double				m_MainRunwayBearing;
				
public:

	SStationDefinition ();
	SStationDefinition (const StationRecord& Other);				// Copies from structure
	~SStationDefinition ();

	SStationDefinition& operator = (const StationRecord& Other);	// Assigns from structure

	StationRecord& AssignTo (StationRecord& LVal) const;			// Assigns to structure

	void SetID 				(int ID)		{m_ID = ID;}
	void SetWMOCode			(CComBSTR WMO)	{WMO.CopyTo (&m_WMOCode);}
	void SetICAOCode		(CComBSTR ICAO) {ICAO.CopyTo (&m_ICAOCode);}
	void SetIATACode		(CComBSTR IATA) {IATA.CopyTo (&m_IATACode);}
	void SetName			(CComBSTR Name) {Name.CopyTo (&m_Name);}
	void SetLat				(double Lat)	{m_Lat = Lat;}
	void SetLong			(double Long)	{m_Long = Long;}
	void SetHeightMetres	(double Height)	{m_HeightMetres = Height;}
	void SetHeightMetres	(const CString& HeightString);
	void SetCountry			(CComBSTR Ctry) {Ctry.CopyTo (&m_Country);}

	int		 GetID				() const {return m_ID;}
	CComBSTR GetWMOCode			() const {return m_WMOCode;}
	CComBSTR GetICAOCode		() const {return m_ICAOCode;}
	CComBSTR GetIATACode		() const {return m_IATACode;}
	CComBSTR GetName			() const {return m_Name;}
	CComBSTR GetCountry			() const {return m_Country;}
	double	 GetLat				() const {return m_Lat;}
	double	 GetLong			() const {return m_Long;}
	double	 GetHeightMetres	() const {return m_HeightMetres;}
	CString	 GetHeightMetresStr	() const;

	operator StationRecord () const;

	CComBSTR GetBestCode		() const;
};//SStationDefinition


inline void FreeStationRecordBSTRs( StationRecord &Record )
{
   ::SysFreeString( Record.WmoCode  ) ;
   ::SysFreeString( Record.IcaoCode ) ;
   ::SysFreeString( Record.IataCode ) ;
   ::SysFreeString( Record.StationName ) ;
   ::SysFreeString( Record.Country ) ;
}


#endif
