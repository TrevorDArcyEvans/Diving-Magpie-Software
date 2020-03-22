#include "stdafx.h"
#include "PurgeableCategory.hpp"

// {1D0D1FE0-F741-11d2-9A47-641D09C1A224}
static const GUID CATID_PurgeableAndCreateable = 
{ 0x1d0d1fe0, 0xf741, 0x11d2, { 0x9a, 0x47, 0x64, 0x1d, 0x9, 0xc1, 0xa2, 0x24 } };

HRESULT SPurgeableCategory::RegisterCategory 
(
	const CLSID&	Impl
)
{
	CoInitialize (0);

	ICatRegister* CatReg = 0;

	HRESULT res = CoCreateInstance (CLSID_StdComponentCategoriesMgr,
									0,
									CLSCTX_INPROC_SERVER,
									IID_ICatRegister,
									(void**)&CatReg);

	if (!SUCCEEDED (res))
		return res;
	//if

	CATEGORYINFO CatAr[1];

	CatAr[0].catid = CATID_PurgeableAndCreateable;
	CatAr[0].lcid = 0x0409 ; // english 
	CString Str = "Components that may be purged by the Sigmex File Purger.";
    wcsncpy(CatAr[0].szDescription, Str.AllocSysString (),Str.GetLength () ); 
	CatAr[0].szDescription[Str.GetLength ()] = 0;

	CatReg->RegisterCategories (1,CatAr);

	CATID Arr[1];
	
	Arr[0] = CATID_PurgeableAndCreateable;

	res = CatReg->RegisterClassImplCategories  (Impl,1,Arr);

	CatReg->Release ();

	return res;
}//SPurgeableCategory::RegisterCategory

HRESULT SPurgeableCategory::UnregisterCategory 
(
	REFCLSID Impl
)
{
	CoInitialize (0);

	ICatRegister* CatReg = 0;

	HRESULT res = CoCreateInstance (CLSID_StdComponentCategoriesMgr,
									0,
									CLSCTX_INPROC_SERVER,
									IID_ICatRegister,
									(void**)&CatReg);

	if (!SUCCEEDED (res))
		return res;
	//if

	CATID Arr[1];
	
	Arr[0] = CATID_PurgeableAndCreateable;

	res = CatReg->UnRegisterClassImplCategories (Impl,1,Arr);

	CatReg->Release ();

	return res;
}//SPurgeableCategory::UnregisterCategory

HRESULT SPurgeableCategory::EnumImpls 
(
	SGUIDArray& Impls
)
{
	CoInitialize (0);

	ICatInformation* CatInfo = 0;

	HRESULT res = CoCreateInstance (CLSID_StdComponentCategoriesMgr,
									0,
									CLSCTX_INPROC_SERVER,
									IID_ICatInformation,
									(void**)&CatInfo);

	if (!SUCCEEDED (res))
		return res;
	//if

	CATID Arr[1];
	
	Arr[0] = CATID_PurgeableAndCreateable;

	IEnumGUID* Enum = 0;

	CatInfo->EnumClassesOfCategories (1,Arr,0,0,&Enum);

	if (!SUCCEEDED (res))
		return res;
	//if

	res = CatInfo->Release ();

	ULONG Tot;

	do
	{
		GUID Out[20];

		res = Enum->Next (20,Out,&Tot);

		for (int i = 0; i < 20; i++)
			Impls.Add (Out[i]);
		//for
	} while (Tot == 20);

	Enum->Release ();

	return res;
}//SPurgeableCategory::EnumImpls

