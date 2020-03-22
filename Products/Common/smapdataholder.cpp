#include "stdafx.h"
#include "SMapDataHolder.hpp"
#include "SException.hpp"

SMapDataHolder*	SMapDataHolder::sm_Instance = 0;

const CLSID CLSID_RawMapData = {0x135A706E,0xE75B,0x11D2,{0x9A,0x47,0x64,0x1D,0x09,0xC1,0xA2,0x24}};

SMapDataHolder::SMapDataHolder ()
:m_Data (0)
{
	HRESULT ret = CoCreateInstance (CLSID_RawMapData,
									0,
									CLSCTX_INPROC_SERVER,
									IID_IUnknown,
									(void**)&m_Data); 

	if (!SUCCEEDED (ret))
		throw new SException ("Failed to create data loader.");
	//if
}//SMapDataHolder::SMapDataHolder

SMapDataHolder::~SMapDataHolder ()
{
	if (m_Data)
		m_Data->Release ();
	//if
}//SMapDataHolder::~SMapDataHolder

SMapDataHolder*	SMapDataHolder::Instance ()
{
	if (!sm_Instance)
		sm_Instance = new SMapDataHolder;
	//if

	return sm_Instance;
}//SMapDataHolder::Instance

void SMapDataHolder::Destroy ()
{
	if (sm_Instance)
	{
		delete sm_Instance;
		sm_Instance = 0;
	}//if
}//SMapDataHolder::Destroy




