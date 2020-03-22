// DMS_UNFRAGIMPL.H : Declaration of the TDMS_UnfragImpl

#ifndef DMS_UnfragImplH
#define DMS_UnfragImplH

#include "DMS_Unfg_TLB.H"
#include "DMS_Comm_TLB.h"

/////////////////////////////////////////////////////////////////////////////
// TDMS_UnfragImpl     Implements IDMS_Unfrag, default interface of DMS_Unfrag
// ThreadingModel : Both
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : DMS_Unfg.DMS_Unfrag
// Description    : 
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TDMS_UnfragImpl : 
  public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<TDMS_UnfragImpl, &CLSID_DMS_Unfrag>,
  public IDispatchImpl<IDMS_Unfrag, &IID_IDMS_Unfrag, &LIBID_DMS_Unfg>
{
public:
   TDMS_UnfragImpl();
  ~TDMS_UnfragImpl();
  
  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct();
  HRESULT FinalRelease  ();


  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otBoth);
  DECLARE_PROGID("DMS_Unfg.DMS_Unfrag");
  DECLARE_DESCRIPTION("");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TDMS_UnfragImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }


BEGIN_COM_MAP(TDMS_UnfragImpl)
  COM_INTERFACE_ENTRY(IDMS_Unfrag)
  COM_INTERFACE_ENTRY2(IDispatch, IDMS_Unfrag)
END_COM_MAP()

private:
    // time to wait in seconds for file to become free
    int                 m_nTimeout;

    // true if registered for non-network use
    int                 m_bRegistered;

    // true if registered for network use
    int                 m_bRegisteredNetwork;

    TCOMIDMS_Common     m_DMS_Comm;

    bool ProceedForFile(BSTR sFileName);

// IDMS_Unfrag
public:
 
  STDMETHOD(get_IsRegistered(int* bIsRegistered));
  STDMETHOD(get_TimeOut(int* nTimeOut));
  STDMETHOD(RemoveGeometry(BSTR sFileName));
  STDMETHOD(RemovePreview(BSTR sFileName));
  STDMETHOD(set_AuthCode(BSTR Param1));
  STDMETHOD(set_TimeOut(int nTimeOut));
  STDMETHOD(UnfragFile(BSTR sFileName, long* nBytesSaved));
  STDMETHOD(set_AuthCodeNetwork(BSTR Value));
  STDMETHOD(get_IsRegisteredNetwork(int* bIsRegistered));
};

#endif //DMS_UnfragImplH
