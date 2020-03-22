// DMS_COMMONIMPL.H : Declaration of the TDMS_CommonImpl

#ifndef __DMS_COMMONIMPL_H_
#define __DMS_COMMONIMPL_H_

#include "DMS_Comm_TLB.H"

//---------------------------------------------------------------------------
#ifdef    MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif
//---------------------------------------------------------------------------
GLOBAL    bool        g_bSW_Running;
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// TDMS_CommonImpl     Implements IDMS_Common, default interface of DMS_Common
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : DMS_Comm.DMS_Common
// Description    : 
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TDMS_CommonImpl : 
  public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<TDMS_CommonImpl, &CLSID_DMS_Common>,
  public IDispatchImpl<IDMS_Common, &IID_IDMS_Common, &LIBID_DMS_Comm>
{
public:
  TDMS_CommonImpl();

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("DMS_Comm.DMS_Common");
  DECLARE_DESCRIPTION("");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TDMS_CommonImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }


BEGIN_COM_MAP(TDMS_CommonImpl)
  COM_INTERFACE_ENTRY(IDMS_Common)
  COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

private:
    HICON       m_hIcon;
    String      m_sProductName,
                m_sProductCode,
                m_sAuthCode,
                m_sIniFileName;
    bool        m_bIsRegistered,
                m_bCommercial;
    Variant     m_SolidWorks;

    void        WriteSecurityCode();
    void        ReadSecurityCode ();

// IDMS_Common
public:

  STDMETHOD(About());
  STDMETHOD(get_Commercial(int* Value));
  STDMETHOD(get_IsRegistered(int* bIsRegistered));
  STDMETHOD(get_ProductCode(BSTR* sProductCode));
  STDMETHOD(get_ProductName(BSTR* sProductName));
  STDMETHOD(IsSolidWorksFile(BSTR sFileName, int* bIsSolidWorksFile));
  STDMETHOD(Register());
  STDMETHOD(set_AuthCode(BSTR Param1));
  STDMETHOD(set_Commercial(int Value));
  STDMETHOD(set_Icon(long Param1));
  STDMETHOD(set_ProductCode(BSTR sProductCode));
  STDMETHOD(set_ProductName(BSTR sProductName));
  STDMETHOD(IsSolidWorksRunning(int* bIsSolidWorksRunning));
  STDMETHOD(GetMachineID(BSTR* sMachineID));
  STDMETHOD(get_IniFileName(BSTR* Value));
  STDMETHOD(set_IniFileName(BSTR Value));
  STDMETHOD(set_SolidWorks(IDispatch * Value));
};

#endif //__DMS_COMMONIMPL_H_

