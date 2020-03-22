// DMS_PSWorks.h : Declaration of the CDMS_PSWorks

#ifndef __DMS_PSWORKS_H_
#define __DMS_PSWORKS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDMS_PSWorks
class ATL_NO_VTABLE CDMS_PSWorks : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CDMS_PSWorks, &CLSID_DMS_PSWorks>,
    public IDispatchImpl<IDMS_PSWorks, &IID_IDMS_PSWorks, &LIBID_DMS_PSWKSLib>
{
public:
     CDMS_PSWorks();
    ~CDMS_PSWorks();

DECLARE_REGISTRY_RESOURCEID(IDR_DMS_PSWORKS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

HRESULT FinalConstruct();
HRESULT FinalRelease  ();


BEGIN_COM_MAP(CDMS_PSWorks)
    COM_INTERFACE_ENTRY(IDMS_PSWorks)
    COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDMS_PSWorks
public:
    STDMETHOD(GetConfigList)
    (
        BSTR                sSW_FileName, 
        BSTR*               sConfigList
    );
    STDMETHOD(ExtractConfig)
    (
        BSTR                sSW_FileName,
        BSTR                sConfigBodyName,
        BSTR                sParasolid_FileName,
        int*                nRetVal
    );
};

#endif //__DMS_PSWORKS_H_
