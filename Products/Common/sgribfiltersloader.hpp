#ifndef _SGribFiltersLoader_hpp
#define _SGribFiltersLoader_hpp

#include "RegistryService.h"
#include <afxtempl.h>

class SGribFiltersLoader
{
private:

	CMapStringToString	m_StationMap;
	CMapStringToString	m_ReverseStationMap;
	CString				m_StationOrder;
	CMapStringToString	m_DataTypeMap;
	CString				m_DataTypeOrder;
	CMapStringToString	m_LevelMap;
	CString				m_LevelOrder;
	CMapStringToString	m_PrognosisMap;
	CString				m_PrognosisOrder;

	IRegistryFlagger*	m_Flagger;

	static SGribFiltersLoader*	sm_Instance;

	SGribFiltersLoader ();
	virtual ~SGribFiltersLoader ();

	CString GetTabbedOptionList (const CMapStringToString& Map,const CString& Order,bool NoMap = false) const;
	CString GetEditableList		(const CMapStringToString& Map,const CString& Order) const;

	void CommonWriteReg (const CString& Key,const CString& List);
	void LoadFromReg ();
	bool CheckFlag () const;

public:

	static SGribFiltersLoader* Instance ();
	static void Destroy ();

	CString GetStationOptions () const;
	CString GetDataTypeOptions () const;
	CString GetLevelOptions () const;
	CString GetPrognosisOptions () const;

	CString GetStationEditList () const;
	CString GetDataTypeEditList () const;
	CString GetLevelEditList () const;
	CString GetPrognosisEditList () const;

	void SetStationEditList (const CString& List);
	void SetDataTypeEditList (const CString& List);
	void SetLevelEditList (const CString& List);
	void SetPrognosisEditList (const CString& List);

	CString LookupStation (const CString& Key) const;
	CString LookupReverseStation (const CString& Key) const;
	CString LookupDataType (const CString& Key) const;
	CString LookupLevel (const CString& Key) const;
	CString LookupPrognosis (const CString& Key) const;
};//SGribFiltersLoader

#endif


