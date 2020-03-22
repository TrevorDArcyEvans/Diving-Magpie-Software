// XML2XSL.h : Declaration of the CXML2XSL

#ifndef __XML2XSL_H_
#define __XML2XSL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXML2XSL
class ATL_NO_VTABLE CXML2XSL : 
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CXML2XSL, &CLSID_DMS_XML2XSL>,
    public IDMS_XML2XSL
{
public:
     CXML2XSL();
    ~CXML2XSL();

DECLARE_REGISTRY_RESOURCEID(IDR_XML2XSL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

HRESULT FinalConstruct();
HRESULT FinalRelease  ();


BEGIN_COM_MAP(CXML2XSL)
    COM_INTERFACE_ENTRY(IDMS_XML2XSL)
END_COM_MAP()

private:
    CComBSTR            m_XML_FileName;
    CComBSTR            m_XSL_FileName;
    CComBSTR            m_Output_FileName;

public:
// IXML2XSL
    STDMETHOD(Apply_XSL_XML)();
    STDMETHOD(Print)();
    STDMETHOD(get_Output_FileName)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_Output_FileName)(/*[in]*/ BSTR newVal);
    STDMETHOD(get_XSL_FileName)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_XSL_FileName)(/*[in]*/ BSTR newVal);
    STDMETHOD(get_XML_FileName)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_XML_FileName)(/*[in]*/ BSTR newVal);
};

#endif //__XML2XSL_H_
