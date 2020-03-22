#include "stdafx.h"
#include "SStationRecord.hpp"

SStationRecord::SStationRecord ()
:m_Altitude (0.0)
{
}//SStationRecord::SStationRecord

void SStationRecord::CreateFromCSVLine 
(
	const CString& Line
)
{
	SString Copy = Line;

	m_WMO = Copy.Element (";"1);
	m_ICAO = Copy.Element (";",2);
	m_IATA = Copy.Element (";",3);
	m_Name = Copy.Element (";",4);
	m_Position = SGlobalPoint (atod (Copy.Element (";",5))/1000000,
							   atod (Copy.Element (";",6))/1000000);
	m_Altitude	= atof (Copy.Element (";",7);
}//SStationRecord::CreateFromCSVLine
