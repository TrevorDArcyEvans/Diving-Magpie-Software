// DMS_DIFFWORKSIMPL.H : Declaration of the TDMS_DiffWorksImpl

#ifndef DMS_DiffWorksImplH
#define DMS_DiffWorksImplH

#include "DMS_DiffWks_TLB.H"

#include "ShowResults.h"
#include "GetInfo.h"

/////////////////////////////////////////////////////////////////////////////
// TDMS_DiffWorksImpl     Implements IDMS_DiffWorks, default interface of DMS_DiffWorks
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : DMS_DiffWks.DMS_DiffWorks
// Description    : 
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TDMS_DiffWorksImpl :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<TDMS_DiffWorksImpl, &CLSID_DMS_DiffWorks>,
  public IDispatchImpl<IDMS_DiffWorks, &IID_IDMS_DiffWorks, &LIBID_DMS_DiffWks>
{
public:
     TDMS_DiffWorksImpl();
    ~TDMS_DiffWorksImpl();

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("DMS_DiffWks.DMS_DiffWorks");
  DECLARE_DESCRIPTION("");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TDMS_DiffWorksImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct();
    HRESULT FinalRelease  ();

BEGIN_COM_MAP(TDMS_DiffWorksImpl)
    COM_INTERFACE_ENTRY(IDMS_DiffWorks)
    COM_INTERFACE_ENTRY2(IDispatch, IDMS_DiffWorks)
END_COM_MAP()

// IDMS_DiffWorks
private:
    HICON               m_Icon;
    TfrmShowResults*    m_frmShowResults;

public:
  STDMETHOD(set_Icon(long Param1));
  STDMETHOD(GetCompareInfo(BSTR* OriginalName, BSTR* ChangedName,
      BSTR* DisplayName, double* Transparency, long* Colour));
  STDMETHOD(ShowCompareResults(BSTR OriginalName, BSTR ChangedName,
      double OriginalMass, double ChangedMass, double OriginalVolume,
      double ChangedVolume, double OriginalArea, double ChangedArea));

};

#endif //DMS_DiffWorksImplH
