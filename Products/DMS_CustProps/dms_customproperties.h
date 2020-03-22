// DMS_CustomProperties.h : Declaration of the CDMS_CustomProperties

#ifndef __DMS_CUSTOMPROPERTIES_H_
#define __DMS_CUSTOMPROPERTIES_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDMS_CustomProperties
class ATL_NO_VTABLE CDMS_CustomProperties : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CDMS_CustomProperties, &CLSID_DMS_CustomProperties>,
    public IDMS_CustomProperties
{
public:
     CDMS_CustomProperties();
    ~CDMS_CustomProperties();

    DECLARE_REGISTRY_RESOURCEID(IDR_DMS_CUSTOMPROPERTIES)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct();
    HRESULT FinalRelease  ();


BEGIN_COM_MAP(CDMS_CustomProperties)
    COM_INTERFACE_ENTRY(IDMS_CustomProperties)
END_COM_MAP()

// IDMS_CustomProperties
private:
    void ConvertVarTypeToString
    (
        VARTYPE                     vt,
        WCHAR*                      pwszType
    );

    void ConvertValueToString
    (
        const PROPVARIANT&          propvar,
        WCHAR*                      pwszValue
    );

    void DumpProperty
    (
        const PROPVARIANT&          propvar,
        const STATPROPSTG&          statpropstg
    );

    HRESULT DumpPropertySet
    (
        IPropertyStorage*           pPropStg
    );




public:
    STDMETHOD(LoadFile)(BSTR FileName);
    STDMETHOD(get_SummaryInfo)(long FieldID, /*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_SummaryInfo)(long FieldID, /*[in]*/ BSTR newVal);
    STDMETHOD(GetCustomInfoNames2)(BSTR Configuration, BSTR** RetVal);
    STDMETHOD(get_CustomInfo2)(BSTR Configuration, BSTR FieldName, /*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_CustomInfo2)(BSTR Configuration, BSTR FieldName, /*[in]*/ BSTR newVal);
    STDMETHOD(DeleteCustomInfo2)(BSTR Configuration, BSTR FieldName, BOOL* RetVal);
    STDMETHOD(GetCustomInfoCount2)(BSTR Configuration, long* Count);
    STDMETHOD(AddCustomInfo3)(BSTR Configuration, BSTR FieldName, long FieldType, BSTR FieldValue, BOOL* RetVal);
    STDMETHOD(GetCustomInfoType3)(BSTR Configuration, BSTR FieldName, long* Type );
};

#endif //__DMS_CUSTOMPROPERTIES_H_
