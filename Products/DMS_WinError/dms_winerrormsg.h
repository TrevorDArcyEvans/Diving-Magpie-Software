// DMS_WinErrorMsg.h : Declaration of the DMS_WinErrorMsg

#ifndef __DMS_WINERRORMSG_H_
#define __DMS_WINERRORMSG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// DMS_WinErrorMsg
class ATL_NO_VTABLE DMS_WinErrorMsg : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<DMS_WinErrorMsg, &CLSID_DMS_WinErrorMsg>,
	public IDMS_WinErrorMsg
{
public:
	DMS_WinErrorMsg()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DMS_WINERRORMSG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(DMS_WinErrorMsg)
	COM_INTERFACE_ENTRY(IDMS_WinErrorMsg)
END_COM_MAP()

// IDMS_WinErrorMsg
public:
	STDMETHOD(GetErrorString)(int nErrorCode, BSTR* sErrorString);
};

#endif //__DMS_WINERRORMSG_H_
