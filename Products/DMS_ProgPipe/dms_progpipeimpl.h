// DMS_PROGPIPEIMPL.H : Declaration of the TDMS_ProgPipeImpl

#ifndef DMS_ProgPipeImplH
#define DMS_ProgPipeImplH

#include "DMS_ProgPipe_TLB.H"
#include "DMS_ProgDlg.h"

/////////////////////////////////////////////////////////////////////////////
// TDMS_ProgPipeImpl     Implements IDMS_ProgPipe, default interface of DMS_ProgPipe
// ThreadingModel : Both
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : ProgPipe.DMS_ProgPipe
// Description    : 
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TDMS_ProgPipeImpl : 
  public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<TDMS_ProgPipeImpl, &CLSID_DMS_ProgPipe>,
  public IDispatchImpl<IDMS_ProgPipe, &IID_IDMS_ProgPipe, &LIBID_ProgPipe>
{
public:
   TDMS_ProgPipeImpl();
  ~TDMS_ProgPipeImpl();

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct();
  HRESULT FinalRelease  ();

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otBoth);
  DECLARE_PROGID("ProgPipe.DMS_ProgPipe");
  DECLARE_DESCRIPTION("");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TDMS_ProgPipeImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }


BEGIN_COM_MAP(TDMS_ProgPipeImpl)
  COM_INTERFACE_ENTRY(IDMS_ProgPipe)
  COM_INTERFACE_ENTRY2(IDispatch, IDMS_ProgPipe)
END_COM_MAP()

private:
    HICON               m_Icon;
    String              m_Text;
    String              m_Title;
    String              m_Message;
    long                m_TotalSteps;
    long                m_CurrentStep;

    TfrmProgDlg*        m_frmProgDlg;
    void                UpdateSettings();


// IDMS_ProgPipe
public:
 
  STDMETHOD(get_Text(BSTR* Value));
  STDMETHOD(get_Title(BSTR* Value));
  STDMETHOD(get_TotalSteps(long* Value));
  STDMETHOD(Hide());
  STDMETHOD(set_Text(BSTR Value));
  STDMETHOD(set_Title(BSTR Value));
  STDMETHOD(set_TotalSteps(long Value));
  STDMETHOD(Show());
  STDMETHOD(Step());
  STDMETHOD(get_CurrentStep(long* Value));
  STDMETHOD(set_CurrentStep(long Value));
  STDMETHOD(get_Icon(long* Value));
  STDMETHOD(set_Icon(long Value));
  STDMETHOD(Reset());
  STDMETHOD(get_Message(BSTR* Value));
  STDMETHOD(set_Message(BSTR Value));
};

#endif //DMS_ProgPipeImplH
