// DMS_WEBWORKSIMPL.H : Declaration of the TDMS_WebWorksImpl

#ifndef DMS_WebWorksImplH
#define DMS_WebWorksImplH

#include "DMS_WebWks_TLB.H"
#include "DMS_Comm_TLB.h"
#include "XML_XSLLib_TLB.h"
#include "MSXML_TLB.h"

//---------------------------------------------------------------------
const String                WebWorksIniFileName = "WebWks.ini";

// from SW header file
enum swLengthUnit_e
{
    swMM            = 0,
    swCM            = 1,
    swMETER         = 2,
    swINCHES        = 3,
    swFEET          = 4,
    swFEETINCHES    = 5
};

//---------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////
// TDMS_WebWorksImpl     Implements IDMS_WebWorks, default interface of DMS_WebWorks
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : DMS_WebWks.DMS_WebWorks
// Description    :
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TDMS_WebWorksImpl :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<TDMS_WebWorksImpl, &CLSID_DMS_WebWorks>,
  public IDispatchImpl<IDMS_WebWorks, &IID_IDMS_WebWorks, &LIBID_DMS_WebWks>
{
public:
   TDMS_WebWorksImpl();
  ~TDMS_WebWorksImpl();

  // Data used when registering Object
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("DMS_WebWks.DMS_WebWorks");
  DECLARE_DESCRIPTION("");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TDMS_WebWorksImpl>
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }

DECLARE_PROTECT_FINAL_CONSTRUCT()

HRESULT FinalConstruct();
HRESULT FinalRelease  ();

BEGIN_COM_MAP(TDMS_WebWorksImpl)
  COM_INTERFACE_ENTRY(IDMS_WebWorks)
  COM_INTERFACE_ENTRY2(IDispatch, IDMS_WebWorks)
END_COM_MAP()

private:
    CComPtr <IDMS_Common>       m_DMS_Comm;

    HICON                       m_hIcon;
    Variant                     m_SolidWorks;

    String                      m_XSL_FileName;

    bool                        m_SummInfo;
    bool                        m_CustomProps;

    bool                        m_FileInfo;
    bool                        m_Bitmap;
    bool                        m_BitmapSize;
    bool                        m_FileName;
    bool                        m_FileNameOnly;
    bool                        m_IncDirectory;
    bool                        m_FileSize;
    bool                        m_DateTime;

    bool                        m_MassProps;
    bool                        m_CentreOfMass;
    bool                        m_Mass;
    bool                        m_Area;
    bool                        m_Volume;
    bool                        m_MassMoment;
    bool                        m_BoundBox;

    int                         m_BitmapWidth ;
    int                         m_BitmapHeight;

    void __fastcall ExtractSW_BitmapToJPG_File
    (
    String      strSWFileName   ,
    String      strJPGFileName  ,
    int         nWidth          ,
    int         nHeight         ,
    bool        bStretch
    );

    void DoLoadSettings();

// IDMS_WebWorks
public:

  STDMETHOD(Configure());
  STDMETHOD(set_SolidWorks(LPDISPATCH Param1));
  STDMETHOD(SaveAsHTML(BSTR sFileName, long bKeepXML));
  STDMETHOD(SaveAsXML(BSTR sFileName));
  STDMETHOD(get_XSL_FileName(BSTR* sFileName));
  STDMETHOD(set_XSL_FileName(BSTR sFileName));
  STDMETHOD(set_Icon(long Value));
  STDMETHOD(LoadSettings());
};

#endif //DMS_WebWorksImplH

