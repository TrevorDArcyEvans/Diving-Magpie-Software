#include "stdafx.h"
#include "RegistryService.h"
#include "SGribFiltersLoader.hpp"
#include "SRegistryAccess.hpp"
#include "SString.hpp"

SGribFiltersLoader*	SGribFiltersLoader::sm_Instance = 0;

SGribFiltersLoader::SGribFiltersLoader ()
:m_Flagger (0)
{
	HRESULT Res = ::CoCreateInstance (__uuidof (SRegistryFlagger),
								  0,
								  CLSCTX_ALL,
								  __uuidof (IRegistryFlagger),
								  (void**)&m_Flagger);

	LoadFromReg ();
}//SGribFiltersLoader::SGribFiltersLoader

SGribFiltersLoader::~SGribFiltersLoader ()
{
	if (m_Flagger)
		m_Flagger->Release ();
	//if
}//SGribFiltersLoader::~SGribFiltersLoader

void SGribFiltersLoader::LoadFromReg ()
{	
	SRegistryAccess RegAc (HKEY_LOCAL_MACHINE);

	CString Label;
	CString Value;

	CString Key = "Grib Filters\\Issuing Stations";

	int Count = RegAc.GetValueCount (Key);

	for (int i = 0; i < Count; i++)
	{
		RegAc.GetStringPair (Key,i,Label,Value);
		m_StationMap.SetAt (Label,Value);
		m_ReverseStationMap.SetAt (Value,Label);
	}//for

	m_StationOrder = RegAc.ReadString (Key + "\\Sort","");

	Key = "Grib Filters\\Data Types";

	Count = RegAc.GetValueCount (Key);

	for (i = 0; i < Count; i++)
	{
		RegAc.GetStringPair (Key,i,Label,Value);
		m_DataTypeMap.SetAt (Label,Value);
	}//for

	m_DataTypeOrder = RegAc.ReadString (Key + "\\Sort","");

	Key = "Grib Filters\\Data Levels";

	Count = RegAc.GetValueCount (Key);

	for (i = 0; i < Count; i++)
	{
		RegAc.GetStringPair (Key,i,Label,Value);
		m_LevelMap.SetAt (Label,Value);
	}//for

	m_LevelOrder = RegAc.ReadString (Key + "\\Sort","");

	Key = "Grib Filters\\Prognosis Times";

	Count = RegAc.GetValueCount (Key);

	for (i = 0; i < Count; i++)
	{
		RegAc.GetStringPair (Key,i,Label,Value);
		m_PrognosisMap.SetAt (Label,Value);
	}//for

	m_PrognosisOrder = RegAc.ReadString (Key + "\\Sort","");
}//SGribFiltersLoader::SGribFiltersLoader

void SGribFiltersLoader::CommonWriteReg 
(
	const CString& Key,
	const CString& List
)
{
	SRegistryAccess RegAc (HKEY_LOCAL_MACHINE);

	SString EdList = List;

	CString Sort;

	int i = 0;

	SString Pair = EdList.Element ("\r\n",i++);

	while (!Pair.IsEmpty ())
	{
		CString Label = Pair.Element (":",0);
		CString Entry = Pair.Element (":",1);

		RegAc.WriteString (Key,Label,Entry);

		if (i != 1)
			Sort += ",";
		//if

		Sort += Label;

		Pair = EdList.Element ("\r\n",i++);
	}//while

	RegAc.WriteString (Key + "\\Sort","",Sort);
}

bool SGribFiltersLoader::CheckFlag () const
{
	if (m_Flagger)
	{
		BOOL RetVal = FALSE;

		m_Flagger->HasChanged (&RetVal);

		return RetVal;
	}
	else
		return FALSE;
	//if
}//SRegistry::CheckFlag

SGribFiltersLoader* SGribFiltersLoader::Instance ()
{
	if (!sm_Instance)
		sm_Instance = new SGribFiltersLoader;
	//if

	if (sm_Instance->CheckFlag ())
		sm_Instance->LoadFromReg ();
	//if

	return sm_Instance;
}//SGribFiltersLoader::Instance

void SGribFiltersLoader::Destroy ()
{
	if (sm_Instance)
		delete sm_Instance;
	//if
}//SGribFiltersLoader::Destroy

CString SGribFiltersLoader::GetEditableList
(
	const CMapStringToString&	Map,
	const CString&				Order
)const
{
	SString OrderStr = Order;
	CString RetVal;

	int Count = OrderStr.Count (',') + 1;

	for (int i = 0; i < Count; i++)
	{
		if (RetVal != "")
			RetVal += "\r\n";
		//if
	
		CString Value;

		Map.Lookup (OrderStr.Element (",",i),Value);

		RetVal += OrderStr.Element (",",i) + ":" + Value;
	}//for

	return RetVal;
}//SGribFiltersLoader::GetEditableList

CString SGribFiltersLoader::GetTabbedOptionList 
(
	const CMapStringToString&	Map,
	const CString&				Order,
	bool						NoMap
)const
{
	SString OrderStr = Order;
	CString RetVal;

	int Count = OrderStr.Count (',') + 1;

	for (int i = 0; i < Count; i++)
	{
		if (RetVal != "")
			RetVal += "\t";
		//if
	
		CString Value;

		if (NoMap)
			Value = OrderStr.Element (",",i);
		else
			Map.Lookup (OrderStr.Element (",",i),Value);
		//if

		RetVal += Value;
	}//for

	return RetVal;
}//SGribFiltersLoader::GetTabbedOptionList

CString SGribFiltersLoader::GetStationEditList () const
{
	return GetEditableList (m_StationMap,m_StationOrder);
}//SGribFiltersLoader::GetStationEditList

CString SGribFiltersLoader::GetStationOptions () const
{
	return GetTabbedOptionList (m_StationMap,m_StationOrder,true);
}//SGribFiltersLoader::GetStationOptions

CString SGribFiltersLoader::GetDataTypeEditList () const
{
	return GetEditableList (m_DataTypeMap,m_DataTypeOrder);
}//SGribFiltersLoader::GetDataTypeEditList

CString SGribFiltersLoader::GetDataTypeOptions () const
{
	return GetTabbedOptionList (m_DataTypeMap,m_DataTypeOrder);
}//SGribFiltersLoader::GetDataTypeOptions

CString SGribFiltersLoader::GetLevelEditList () const
{
	return GetEditableList (m_LevelMap,m_LevelOrder);
}//SGribFiltersLoader::GetLevelEditList

CString SGribFiltersLoader::GetLevelOptions () const
{
	return GetTabbedOptionList (m_LevelMap,m_LevelOrder);
}//SGribFiltersLoader::GetLevelOptions

CString SGribFiltersLoader::GetPrognosisEditList () const
{
	return GetEditableList (m_PrognosisMap,m_PrognosisOrder);
}//SGribFiltersLoader::GetPrognosisEditList

CString SGribFiltersLoader::GetPrognosisOptions () const
{
	return GetTabbedOptionList (m_PrognosisMap,m_PrognosisOrder);
}//SGribFiltersLoader::GetPrognosisOptions

void SGribFiltersLoader::SetStationEditList 
(
	const CString& List
)
{
	CommonWriteReg ("Grib Filters\\Issuing Stations",List);
}//SGribFiltersLoader::SetStationEditList

void SGribFiltersLoader::SetDataTypeEditList 
(
	const CString& List
)
{
	CommonWriteReg ("Grib Filters\\Data Types",List);
}//SGribFiltersLoader::SetDataTypeEditList

void SGribFiltersLoader::SetLevelEditList 
(
	const CString& List
)
{
	CommonWriteReg ("Grib Filters\\Data Levels",List);
}//SGribFiltersLoader::SetLevelEditList

void SGribFiltersLoader::SetPrognosisEditList 
(
	const CString& List
)
{
	CommonWriteReg ("Grib Filters\\Prognosis Times",List);
}//SGribFiltersLoader::SetPrognosisEditList

CString SGribFiltersLoader::LookupReverseStation 
(
	const CString& Key
)const
{
	CString RetVal;

	m_ReverseStationMap.Lookup (Key,RetVal);

	return RetVal;
}//SGribFiltersLoader::LookupReverseStation

CString SGribFiltersLoader::LookupStation 
(
	 const CString& Key
) const
{
	CString RetVal;

	m_StationMap.Lookup (Key,RetVal);

	return RetVal;
}//SGribFiltersLoader::LookupStation

CString SGribFiltersLoader::LookupDataType 
(
	 const CString& Key
) const
{
	CString RetVal;

	m_DataTypeMap.Lookup (Key,RetVal);

	return RetVal;
}//SGribFiltersLoader::LookupDataType

CString SGribFiltersLoader::LookupLevel 
(
	 const CString& Key
) const
{
	CString RetVal;

	m_LevelMap.Lookup (Key,RetVal);

	return RetVal;
}//SGribFiltersLoader::LookupLevel

CString SGribFiltersLoader::LookupPrognosis 
(
	 const CString& Key
) const
{
	CString RetVal;

	m_PrognosisMap.Lookup (Key,RetVal);

	return RetVal;
}//SGribFiltersLoader::LookupPrognosis

