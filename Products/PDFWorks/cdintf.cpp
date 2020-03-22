// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "cdintf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ICDIntf properties

BOOL ICDIntf::GetFontEmbedding()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void ICDIntf::SetFontEmbedding(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

BOOL ICDIntf::GetPageContentCompression()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void ICDIntf::SetPageContentCompression(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL ICDIntf::GetJPEGCompression()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void ICDIntf::SetJPEGCompression(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

short ICDIntf::GetPaperSize()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

void ICDIntf::SetPaperSize(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}

long ICDIntf::GetPaperWidth()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

void ICDIntf::SetPaperWidth(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}

long ICDIntf::GetPaperLength()
{
	long result;
	GetProperty(0x6, VT_I4, (void*)&result);
	return result;
}

void ICDIntf::SetPaperLength(long propVal)
{
	SetProperty(0x6, VT_I4, propVal);
}

short ICDIntf::GetOrientation()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}

void ICDIntf::SetOrientation(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}

long ICDIntf::GetResolution()
{
	long result;
	GetProperty(0x8, VT_I4, (void*)&result);
	return result;
}

void ICDIntf::SetResolution(long propVal)
{
	SetProperty(0x8, VT_I4, propVal);
}

CString ICDIntf::GetDefaultDirectory()
{
	CString result;
	GetProperty(0x9, VT_BSTR, (void*)&result);
	return result;
}

void ICDIntf::SetDefaultDirectory(LPCTSTR propVal)
{
	SetProperty(0x9, VT_BSTR, propVal);
}

CString ICDIntf::GetDefaultFileName()
{
	CString result;
	GetProperty(0xa, VT_BSTR, (void*)&result);
	return result;
}

void ICDIntf::SetDefaultFileName(LPCTSTR propVal)
{
	SetProperty(0xa, VT_BSTR, propVal);
}

short ICDIntf::GetFileNameOptions()
{
	short result;
	GetProperty(0xb, VT_I2, (void*)&result);
	return result;
}

void ICDIntf::SetFileNameOptions(short propVal)
{
	SetProperty(0xb, VT_I2, propVal);
}

short ICDIntf::GetHorizontalMargin()
{
	short result;
	GetProperty(0xc, VT_I2, (void*)&result);
	return result;
}

void ICDIntf::SetHorizontalMargin(short propVal)
{
	SetProperty(0xc, VT_I2, propVal);
}

short ICDIntf::GetVerticalMargin()
{
	short result;
	GetProperty(0xd, VT_I2, (void*)&result);
	return result;
}

void ICDIntf::SetVerticalMargin(short propVal)
{
	SetProperty(0xd, VT_I2, propVal);
}

BOOL ICDIntf::GetHTMLUseLayers()
{
	BOOL result;
	GetProperty(0xe, VT_BOOL, (void*)&result);
	return result;
}

void ICDIntf::SetHTMLUseLayers(BOOL propVal)
{
	SetProperty(0xe, VT_BOOL, propVal);
}

BOOL ICDIntf::GetHTMLMultipleHTMLs()
{
	BOOL result;
	GetProperty(0xf, VT_BOOL, (void*)&result);
	return result;
}

void ICDIntf::SetHTMLMultipleHTMLs(BOOL propVal)
{
	SetProperty(0xf, VT_BOOL, propVal);
}

long ICDIntf::GetAttributes()
{
	long result;
	GetProperty(0x1f, VT_I4, (void*)&result);
	return result;
}

void ICDIntf::SetAttributes(long propVal)
{
	SetProperty(0x1f, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// ICDIntf operations

long ICDIntf::CreateDC()
{
	long result;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ICDIntf::SetDefaultConfig()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICDIntf::SetDefaultPrinter()
{
	BOOL result;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICDIntf::StartSpooler()
{
	BOOL result;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICDIntf::StopSpooler()
{
	BOOL result;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

long ICDIntf::PDFDriverInit(LPCTSTR PrinterName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		PrinterName);
	return result;
}

long ICDIntf::HTMLDriverInit(LPCTSTR PrinterName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		PrinterName);
	return result;
}

long ICDIntf::EMFDriverInit(LPCTSTR PrinterName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		PrinterName);
	return result;
}

void ICDIntf::DriverEnd()
{
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString ICDIntf::GetLastErrorMsg()
{
	CString result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL ICDIntf::RestoreDefaultPrinter()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

long ICDIntf::DriverInit(LPCTSTR PrinterName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		PrinterName);
	return result;
}

CString ICDIntf::GetDocumentTitle(long JobID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		JobID);
	return result;
}

long ICDIntf::SetBookmark(long hDC, long lParent, LPCTSTR Title)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		hDC, lParent, Title);
	return result;
}

long ICDIntf::CaptureEvents(long bCapture)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		bCapture);
	return result;
}
