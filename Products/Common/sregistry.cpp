#include "stdafx.h"
#include "RegistryService.h"
#include "SRegistry.hpp"
#include "SRegistryAccess.hpp"
#include "SBetterThanMFC.hpp"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SRegistry*		SRegistry::sm_Instance = 0;

SRegistry::SRegistry ()
:m_GeneralDataPath ("c:\\"),
 m_StationTrackWidthKm (200.0),
 m_MapZoomInFactor (2.0),
 m_CrossSecZoomInFactor (2.0),
 m_MetricHeight (true),
 m_Flagger (0)
{
	HRESULT Res = ::CoCreateInstance (__uuidof (SRegistryFlagger),
									  0,
									  CLSCTX_ALL,
									  __uuidof (IRegistryFlagger),
									  (void**)&m_Flagger);
}//SRegistry::SRegistry

SRegistry::~SRegistry ()
{
	if (m_Flagger)
		m_Flagger->Release ();
	//if
}//SRegistry::~SRegistry

bool SRegistry::CheckFlag () const
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

void SRegistry::WriteToReg () const
{
	SRegistryAccess LocalReg (HKEY_LOCAL_MACHINE,"SOFTWARE\\Sigmex");

	LocalReg.WriteString ("WeatherView","GeneralDataPath",m_GeneralDataPath);
	LocalReg.WriteString ("WeatherView","MeteoDBPath",m_MeteoDBPath);
	LocalReg.WriteString ("WeatherView","GribDataPath",m_GribDataPath);
	LocalReg.WriteString ("WeatherView","StationSetPath",m_StationSetPath);

	SRegistryAccess CurrentReg (HKEY_CURRENT_USER,"SOFTWARE\\Sigmex");

	CurrentReg.WriteDouble ("WeatherView","MapZoomInFactor",m_MapZoomInFactor);
	CurrentReg.WriteDouble ("WeatherView","CrossSectionZoomInFactor",m_CrossSecZoomInFactor);
	CurrentReg.WriteDouble ("WeatherView","StationTrackWidthKm",m_StationTrackWidthKm);
	CurrentReg.WriteInt	   ("WeatherView","MetricHeight",m_MetricHeight);

	if (m_Flagger)
		m_Flagger->RegisterChange ();
	//if
}//SRegistry::WriteToReg

void SRegistry::LoadFromReg ()
{
	SRegistryAccess LocalReg (HKEY_LOCAL_MACHINE,"SOFTWARE\\Sigmex");

	m_GeneralDataPath = LocalReg.ReadString ("WeatherView","GeneralDataPath");
	m_MeteoDBPath     = LocalReg.ReadString ("WeatherView","MeteoDBPath",m_GeneralDataPath ^ "PC-Metis.mdb");
	m_GribDataPath	  = LocalReg.ReadString ("WeatherView","GribDataPath",m_GeneralDataPath);
	m_StationSetPath  = LocalReg.ReadString ("WeatherView","StationSetPath",m_GeneralDataPath);

	SRegistryAccess CurrentReg (HKEY_CURRENT_USER,"SOFTWARE\\Sigmex");

	m_MapZoomInFactor		= CurrentReg.ReadDouble ("WeatherView","MapZoomInFactor",m_MapZoomInFactor);
	m_CrossSecZoomInFactor	= CurrentReg.ReadDouble ("WeatherView","CrossSectionZoomInFactor",m_CrossSecZoomInFactor);
	m_StationTrackWidthKm	= CurrentReg.ReadDouble ("WeatherView","StationTrackWidthKm",m_StationTrackWidthKm);
	m_MetricHeight			= CurrentReg.ReadInt	("WeatherView","MetricHeight",m_MetricHeight);
}//SRegistry::LoadFromReg

SRegistry* SRegistry::Instance ()
{
	if (!sm_Instance)
	{
		sm_Instance = new SRegistry;
		sm_Instance->LoadFromReg ();
	}//if

	if (sm_Instance->CheckFlag ())
		sm_Instance->LoadFromReg ();
	//if

	return sm_Instance;
}//SRegistry::Instance

void SRegistry::Destroy ()
{
	if (sm_Instance)
	{
		delete sm_Instance;
		sm_Instance = 0;
	}//if
}//SRegistry::Destroy



	


