// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// ICDIntf wrapper class

class ICDIntf : public COleDispatchDriver
{
public:
	ICDIntf() {}		// Calls COleDispatchDriver default constructor
	ICDIntf(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ICDIntf(const ICDIntf& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetFontEmbedding();
	void SetFontEmbedding(BOOL);
	BOOL GetPageContentCompression();
	void SetPageContentCompression(BOOL);
	BOOL GetJPEGCompression();
	void SetJPEGCompression(BOOL);
	short GetPaperSize();
	void SetPaperSize(short);
	long GetPaperWidth();
	void SetPaperWidth(long);
	long GetPaperLength();
	void SetPaperLength(long);
	short GetOrientation();
	void SetOrientation(short);
	long GetResolution();
	void SetResolution(long);
	CString GetDefaultDirectory();
	void SetDefaultDirectory(LPCTSTR);
	CString GetDefaultFileName();
	void SetDefaultFileName(LPCTSTR);
	short GetFileNameOptions();
	void SetFileNameOptions(short);
	short GetHorizontalMargin();
	void SetHorizontalMargin(short);
	short GetVerticalMargin();
	void SetVerticalMargin(short);
	BOOL GetHTMLUseLayers();
	void SetHTMLUseLayers(BOOL);
	BOOL GetHTMLMultipleHTMLs();
	void SetHTMLMultipleHTMLs(BOOL);
	long GetAttributes();
	void SetAttributes(long);

// Operations
public:
	long CreateDC();
	BOOL SetDefaultConfig();
	BOOL SetDefaultPrinter();
	BOOL StartSpooler();
	BOOL StopSpooler();
	long PDFDriverInit(LPCTSTR PrinterName);
	long HTMLDriverInit(LPCTSTR PrinterName);
	long EMFDriverInit(LPCTSTR PrinterName);
	void DriverEnd();
	CString GetLastErrorMsg();
	BOOL RestoreDefaultPrinter();
	long DriverInit(LPCTSTR PrinterName);
	CString GetDocumentTitle(long JobID);
	long SetBookmark(long hDC, long lParent, LPCTSTR Title);
	long CaptureEvents(long bCapture);
};
