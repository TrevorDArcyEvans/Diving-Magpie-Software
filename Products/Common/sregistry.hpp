#ifndef __SRegistry_hpp
#define __SRegistry_hpp

#include <afx.h>
#include "RegistryService.h"

class SRegistry
{
private:

	static SRegistry*		sm_Instance;

	IRegistryFlagger*		m_Flagger;	

	bool CheckFlag () const;

public:

	SRegistry ();
	virtual ~SRegistry ();

	CString	m_GeneralDataPath;
	CString m_MeteoDBPath;
	CString m_GribDataPath;
	CString m_StationSetPath;

	double	m_MapZoomInFactor;
	double	m_CrossSecZoomInFactor;

	double  m_StationTrackWidthKm;

	bool	m_MetricHeight;

	virtual void WriteToReg () const;
	void LoadFromReg ();

	static 	SRegistry* Instance ();

	static void Destroy ();
};//SRegistry

#endif

