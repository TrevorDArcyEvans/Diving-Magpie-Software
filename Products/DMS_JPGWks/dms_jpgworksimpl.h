// DMS_JPGWORKSIMPL.H : Declaration of the TDMS_JPGWorksImpl

#ifndef DMS_JPGWorksImplH
#define DMS_JPGWorksImplH

#include "DMS_JPGWks_TLB.H"


/////////////////////////////////////////////////////////////////////////////
// TDMS_JPGWorksImpl     Implements IDMS_JPGWorks, default interface of DMS_JPGWorks
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : DMS_JPGWks.DMS_JPGWorks
// Description    : 
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TDMS_JPGWorksImpl : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<TDMS_JPGWorksImpl, &CLSID_DMS_JPGWorks>,
  public IDispatchImpl<IDMS_JPGWorks, &IID_IDMS_JPGWorks, &LIBID_DMS_JPGWks>
{
public:
  ~TDMS_JPGWorksImpl();
   TDMS_JPGWorksImpl();

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("DMS_JPGWks.DMS_JPGWorks");
  DECLARE_DESCRIPTION("");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TDMS_JPGWorksImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct();
    HRESULT FinalRelease  ();

BEGIN_COM_MAP(TDMS_JPGWorksImpl)
  COM_INTERFACE_ENTRY(IDMS_JPGWorks)
  COM_INTERFACE_ENTRY2(IDispatch, IDMS_JPGWorks)
END_COM_MAP()

// IDMS_JPGWorks
private:
    HICON           m_Icon;

public:
 
  STDMETHOD(Configure());
  STDMETHOD(SaveAsJPEG(BSTR FileName, long Handle));
};

#endif //DMS_JPGWorksImplH
