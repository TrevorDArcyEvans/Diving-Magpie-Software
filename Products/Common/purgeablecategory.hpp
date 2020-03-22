#ifndef _SPurgeableCategory_hpp
#define _SPurgeableCategory_hpp

#include <afxtempl.h>

typedef CArray <GUID,GUID&> SGUIDArray;

class SPurgeableCategory
{
public:

	static HRESULT RegisterCategory (REFCLSID Impl);
	static HRESULT UnregisterCategory (REFCLSID Impl);

	static HRESULT EnumImpls (SGUIDArray& Impls);
};//SPurgeableCategory

#endif

