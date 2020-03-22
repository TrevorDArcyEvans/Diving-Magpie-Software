// DMS_PDFWORKSIMPL.H : Declaration of the TDMS_PDFWorksImpl

#ifndef __DMS_PDFWORKSIMPL_H_
#define __DMS_PDFWORKSIMPL_H_

#include "DMS_PDFWks_TLB.H"

typedef tagPDF_Setup            PDF_Setup;
typedef tagPDF_PAPER_SIZE       PDF_PAPER_SIZE;
typedef tagPDF_UNITS            PDF_UNITS;

/////////////////////////////////////////////////////////////////////////////
// TDMS_PDFWorksImpl     Implements IDMS_PDFWorks, default interface of DMS_PDFWorks
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : DMS_PDFWks.DMS_PDFWorks
// Description    : DMS PDF Library
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TDMS_PDFWorksImpl : 
  // we have to derive from CComMultiThreadModel if calling from inside
  // SolidWorks - do not derive from CComSingleThreadModel
  // also in Project->Options->ATL tab, we have to set OLE Initialization Flag
  // to MULTITHREADED
  // if we don't do both of these, we will get an unhandled exception thingy
  public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<TDMS_PDFWorksImpl, &CLSID_DMS_PDFWorks>,
  public IDispatchImpl<IDMS_PDFWorks, &IID_IDMS_PDFWorks, &LIBID_DMS_PDFWks>
{
public:
  TDMS_PDFWorksImpl();

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("DMS_PDFWks.DMS_PDFWorks");
  DECLARE_DESCRIPTION("DMS PDF Library");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TDMS_PDFWorksImpl>
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }


BEGIN_COM_MAP(TDMS_PDFWorksImpl)
  COM_INTERFACE_ENTRY(IDMS_PDFWorks)
  COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDMS_PDFWorks
private:
  PDF_Setup         m_PDF_Setup;
  bool              m_bAmyuni;
  HICON             m_hIcon;

  void  BMP2JPG(
            String    sBMPFileName,
            String    sJPGFileName);

public:
  STDMETHOD(Configure(BSTR sTitle, long* bOK, PDF_Setup* pPDF_Setup));
  STDMETHOD(set_Icon(long Param1));
  STDMETHOD(ClipBoardToJPGFile(BSTR sFileName));
  STDMETHOD(ClipBoardToBMPFile(BSTR sFileName));
  STDMETHOD(ClipBoardToGIFFile(BSTR sFileName));
  STDMETHOD(ClipBoardToPDFFile(BSTR sFileName));
  STDMETHOD(get_JPGQuality(long* Value));
  STDMETHOD(set_JPGQuality(long Value));
  STDMETHOD(get_MarginBottom(long* Value));
  STDMETHOD(get_MarginTop(long* Value));
  STDMETHOD(get_PaperHeight(long* Value));
  STDMETHOD(get_PaperSize(long* Value));
  STDMETHOD(get_PaperWidth(long* Value));
  STDMETHOD(set_MarginBottom(long Value));
  STDMETHOD(set_MarginTop(long Value));
  STDMETHOD(set_PaperHeight(long Value));
  STDMETHOD(set_PaperSize(long Value));
  STDMETHOD(set_PaperWidth(long Value));
  STDMETHOD(get_CentreOnPage(long* Value));
  STDMETHOD(get_InfoSubject(BSTR* Value));
  STDMETHOD(get_Landscape(long* Value));
  STDMETHOD(get_ScaleToFit(long* Value));
  STDMETHOD(set_CentreOnPage(long Value));
  STDMETHOD(set_InfoSubject(BSTR Value));
  STDMETHOD(set_Landscape(long Value));
  STDMETHOD(set_ScaleToFit(long Value));
  STDMETHOD(get_InfoCreator(BSTR* Value));
  STDMETHOD(get_InfoTitle(BSTR* Value));
  STDMETHOD(set_InfoCreator(BSTR Value));
  STDMETHOD(set_InfoTitle(BSTR Value));
  STDMETHOD(get_InfoAuthor(BSTR* Value));
  STDMETHOD(set_InfoAuthor(BSTR Value));
  STDMETHOD(get_Units(long* Value));
  STDMETHOD(set_Units(long Value));
  STDMETHOD(get_Scale(double* Value));
  STDMETHOD(set_Scale(double Value));
  STDMETHOD(get_MarginLeft(long* Value));
  STDMETHOD(get_MarginRight(long* Value));
  STDMETHOD(set_MarginLeft(long Value));
  STDMETHOD(set_MarginRight(long Value));
  STDMETHOD(get_ImageHeight(long* Value));
  STDMETHOD(get_ImageWidth(long* Value));
  STDMETHOD(set_ImageHeight(long Value));
  STDMETHOD(set_ImageWidth(long Value));
  STDMETHOD(get_Stretch(long* Value));
  STDMETHOD(set_Stretch(long Value));
  STDMETHOD(get_InfoKeyWords(BSTR* Value));
  STDMETHOD(set_InfoKeyWords(BSTR Value));
  STDMETHOD(Initialise(PDF_Setup PDF_Init));
  STDMETHOD(get_KeepAspectRatio(long* Value));
  STDMETHOD(set_KeepAspectRatio(long Value));
  STDMETHOD(get_Amyuni(long* Value));
  STDMETHOD(set_Amyuni(long Value));
};

#endif //__DMS_PDFWORKSIMPL_H_

