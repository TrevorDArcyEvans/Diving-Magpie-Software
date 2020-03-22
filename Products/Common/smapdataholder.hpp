#ifndef _SMapDataHolder_hpp
#define _SMapDataHolder_hpp

class IUnknown;

extern const CLSID CLSID_RawMapData;

class SMapDataHolder
{
private:


	static SMapDataHolder*	sm_Instance;

	IUnknown*				m_Data;

	SMapDataHolder ();
	virtual ~SMapDataHolder ();

public:

	static SMapDataHolder*	Instance ();
	static void Destroy ();

	IUnknown* GetData () {return m_Data;}
};//SMapDataHolder

#endif

