// DMS_STICKWORKSIMPL.H : Declaration of the TDMS_StickWorksImpl

#ifndef __DMS_STICKWORKSIMPL_H_
#define __DMS_STICKWORKSIMPL_H_

#include "DMS_StkWks_TLB.H"


/////////////////////////////////////////////////////////////////////////////
// TDMS_StickWorksImpl     Implements IDMS_StickWorks, default interface of DMS_StickWorks
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : DMS_StkWks.DMS_StickWorks
// Description    :
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TDMS_StickWorksImpl :
  public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<TDMS_StickWorksImpl, &CLSID_DMS_StickWorks>,
  public IDispatchImpl<IDMS_StickWorks, &IID_IDMS_StickWorks, &LIBID_DMS_StkWks>
{
public:
   TDMS_StickWorksImpl();
  ~TDMS_StickWorksImpl();

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct();
  HRESULT FinalRelease  ();


  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("DMS_StkWks.DMS_StickWorks");
  DECLARE_DESCRIPTION("");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TDMS_StickWorksImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }


BEGIN_COM_MAP(TDMS_StickWorksImpl)
  COM_INTERFACE_ENTRY(IDMS_StickWorks)
  COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

private:
    HICON       m_Icon;
    String      m_Name;

    // IDMS_StickWorks
public:
 
  STDMETHOD(Configure());
  STDMETHOD(get_Name(BSTR* sName));
  STDMETHOD(set_Name(BSTR sName));
  STDMETHOD(set_Icon(long hIcon));
};

#endif //__DMS_STICKWORKSIMPL_H_
