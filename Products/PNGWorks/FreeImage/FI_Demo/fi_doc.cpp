// FI_Doc.cpp : implementation of the CFI_Doc class
//

#include "stdafx.h"
#include "FI_Demo.h"

#include "FI_Doc.h"
#include "Dialogs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFI_Doc

IMPLEMENT_DYNCREATE(CFI_Doc, CDocument)

BEGIN_MESSAGE_MAP(CFI_Doc, CDocument)
	//{{AFX_MSG_MAP(CFI_Doc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_IMG_CVT_8, OnConvertTo8Bits)
	ON_UPDATE_COMMAND_UI(ID_IMG_CVT_8, OnUpdateConvertTo8Bits)
	ON_COMMAND(ID_IMG_CVT_16, OnConvertTo16Bits)
	ON_UPDATE_COMMAND_UI(ID_IMG_CVT_16, OnUpdateConvertTo16Bits)
	ON_COMMAND(ID_IMG_CVT_24, OnConvertTo24Bits)
	ON_UPDATE_COMMAND_UI(ID_IMG_CVT_24, OnUpdateConvertTo24Bits)
	ON_COMMAND(ID_IMG_CVT_32, OnConvertTo32Bits)
	ON_UPDATE_COMMAND_UI(ID_IMG_CVT_32, OnUpdateConvertTo32Bits)
	ON_COMMAND(ID_IMG_QUANTIZE, OnColorQuantize)
	ON_UPDATE_COMMAND_UI(ID_IMG_QUANTIZE, OnUpdateColorQuantize)
	ON_COMMAND(ID_IMG_FLIP, OnFlip)
	ON_COMMAND(ID_IMG_MIRROR, OnMirror)
	ON_COMMAND(ID_IMG_INVERT, OnInvert)
	ON_COMMAND(ID_IMG_ROTATE, OnRotate)
	ON_COMMAND(ID_IMG_CVT_GREY, OnConvertToGreyscale)
	ON_UPDATE_COMMAND_UI(ID_IMG_CVT_GREY, OnUpdateConvertToGreyscale)
	ON_COMMAND(ID_IMG_INFOS, OnImageInfos)
	ON_COMMAND(ID_IMG_BLUR, OnBlur)
	ON_UPDATE_COMMAND_UI(ID_IMG_BLUR, OnUpdateBlur)
	ON_COMMAND(ID_IMG_BRIGHTEN, OnBrighten)
	ON_UPDATE_COMMAND_UI(ID_IMG_BRIGHTEN, OnUpdateBrighten)
	ON_COMMAND(ID_IMG_DARKEN, OnDarken)
	ON_UPDATE_COMMAND_UI(ID_IMG_DARKEN, OnUpdateDarken)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Output Message Function

void FreeImage_Output(FREE_IMAGE_FORMAT fif, const char *msg)
{
	AfxMessageBox(msg);
}


/////////////////////////////////////////////////////////////////////////////
// CFI_Doc construction/destruction

CFI_Doc::CFI_Doc()
{
	m_dib = NULL;
	FreeImage_SetOutputMessage(FreeImage_Output);
}

CFI_Doc::~CFI_Doc()
{
	FreeImage_Free(m_dib);
}

/////////////////////////////////////////////////////////////////////////////
// CFI_Doc diagnostics

#ifdef _DEBUG
void CFI_Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFI_Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


///////////////////////////////////////////////////////////////////
// Loading & Saving

// ----- Default IO functions -----------------------

static inline unsigned
_ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fread(buffer, size, count, (FILE *)handle);
}

static inline unsigned
_WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fwrite(buffer, size, count, (FILE *)handle);
}

static inline int
_SeekProc(fi_handle handle, long offset, int origin) {
	return fseek((FILE *)handle, offset, origin);
}

static inline long
_TellProc(fi_handle handle) {
	return ftell((FILE *)handle);
}

// ----- Return the filename extension -----

static char* GetFileExt(const char* filename)
{
   int i;
	char *ext = (char*)filename;
	for(i = strlen(filename); i >= 0; i--)
		if(*(ext+i) == '.')
			break;
	ext += i + 1;
	if(ext != filename)
		return ext;
	return NULL;
}


bool CFI_Doc::Load(LPCTSTR lpszPathName) 
{
	FreeImageIO io;

	io.read_proc  = _ReadProc;
	io.seek_proc  = _SeekProc;
	io.tell_proc  = _TellProc;
	io.write_proc = _WriteProc;

	FILE *handle = fopen(lpszPathName, "rb");
	if(handle == NULL)
		return false;

	if(m_dib)
		FreeImage_Free(m_dib);

	switch( FreeImage_GetFileTypeFromHandle(&io, handle, 16) )
	{
		case FIF_BMP :
			m_dib = FreeImage_LoadBMPFromHandle(&io, (fi_handle)handle, BMP_DEFAULT);
			break;

		case FIF_JPEG :
			m_dib = FreeImage_LoadJPEGFromHandle(&io, (fi_handle)handle, JPEG_DEFAULT);
			break;

		case FIF_KOALA :
			m_dib = FreeImage_LoadKOALAFromHandle(&io, (fi_handle)handle, KOALA_DEFAULT);
			break;

		case FIF_PCD :
			m_dib = FreeImage_LoadPCDFromHandle(&io, (fi_handle)handle, PCD_DEFAULT);
			break;

		case FIF_PCX :
			m_dib = FreeImage_LoadPCXFromHandle(&io, (fi_handle)handle, PCX_DEFAULT);
			break;

		case FIF_PNG :
			m_dib = FreeImage_LoadPNGFromHandle(&io, (fi_handle)handle, PNG_DEFAULT);
			break;

		case FIF_PBM :
		case FIF_PGM :
		case FIF_PPM :
			m_dib = FreeImage_LoadPNMFromHandle(&io, (fi_handle)handle, PNM_DEFAULT);
			break;

		case FIF_RAS :
			m_dib = FreeImage_LoadRASFromHandle(&io, (fi_handle)handle, RAS_DEFAULT);
			break;

		case FIF_TIFF :
			m_dib = FreeImage_LoadTIFFFromHandle(&io, (fi_handle)handle, TIFF_DEFAULT);
			break;

		case FIF_UNKNOWN :
		{
			// Determine the file format to use based on the filename extension
			char *ext = GetFileExt(lpszPathName);
			if((strcmpi(ext, "tga") == 0) || (strcmpi(ext, "targa") == 0)) {
				m_dib = FreeImage_LoadTARGA(lpszPathName, TARGA_DEFAULT);
				break;
			}
			else if(strcmpi(ext, "ico") == 0) {
				m_dib = FreeImage_LoadICO(lpszPathName, ICO_DEFAULT);
				break;
			}
			else {
				fclose(handle);
				return false;
			}
		}
	}
	fclose(handle);

	if(m_dib == NULL)
		return false;

	return true;
}


bool CFI_Doc::Save(LPCTSTR lpszPathName) 
{
	char *ext;
	bool bSuccess = false;

	// Determine the file format to use based on the filename extension
	ext = GetFileExt(lpszPathName);
	if((strcmpi(ext, "bmp") == 0) || (strcmpi(ext, "dib") == 0))
	{
		bSuccess = FreeImage_SaveBMP(m_dib, lpszPathName, BMP_DEFAULT);
	}
	else if(strcmpi(ext, "png") == 0)
	{
		bSuccess = FreeImage_SavePNG(m_dib, lpszPathName, PNG_DEFAULT);
	}
	else if((strcmpi(ext, "pbm") == 0) || (strcmpi(ext, "pgm") == 0) || (strcmpi(ext, "ppm") == 0))
	{
		bSuccess = FreeImage_SavePNM(m_dib, lpszPathName, PNM_DEFAULT);
	}
	else if((strcmpi(ext, "tif") == 0) || (strcmpi(ext, "tiff") == 0))
	{
		bSuccess = FreeImage_SaveTIFF(m_dib, lpszPathName, TIFF_DEFAULT);
	}
	return bSuccess;
}

/////////////////////////////////////////////////////////////////////////////
// CFI_Doc commands

BOOL CFI_Doc::OnNewDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::OnNewDocument();
}

BOOL CFI_Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	BOOL bSuccess = Load(lpszPathName);
	if (!bSuccess)
		ReportSaveLoadException(lpszPathName, NULL,	FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
	else
	{
		SetPathName(lpszPathName);
		SetModifiedFlag(FALSE);
	}

	return bSuccess;
}
BOOL CFI_Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// Determine if the file format can be saved with this extension
	char *ext = GetFileExt(lpszPathName);
	switch( FreeImage_GetFileTypeFromExt(ext) ) {
		case FIF_BMP:
		case FIF_PNG:
		case FIF_PBM:
		case FIF_PGM:
		case FIF_PPM:
		case FIF_TIFF:
			BOOL bSuccess = Save(lpszPathName);
			if(!bSuccess)
				ReportSaveLoadException(lpszPathName, NULL,	FALSE, AFX_IDP_FAILED_TO_SAVE_DOC);
			else
				SetModifiedFlag(FALSE);
			return bSuccess;
	}
	OnFileSaveAs();
	return TRUE;
}

static char BASED_CODE sFilter[] =
"Tag Image File Format (.tif)|*.tif|\
PNG (Portable Network Graphics) (.png)|*.png|\
Windows Bitmap (.bmp)|*.bmp|\
Portable Anymap File Format (.pbm, .pgm .ppm)|*.pbm; *.pgm; *.ppm||";

void CFI_Doc::OnFileSaveAs() 
{
	// Bring up the File save as dialog with the customized filter string
	CFileDialog dlgFile(FALSE, NULL, GetPathName(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sFilter, NULL);
	if(dlgFile.DoModal() == IDOK)
	{
		CWaitCursor wait;
		// Do the actual save
		CString sPathName = dlgFile.GetPathName();
		if(dlgFile.GetFileExt() == "")
			sPathName += ".tif";	// Default extension
		if( Save(sPathName) )
		{
			SetPathName(sPathName, TRUE);
			SetModifiedFlag(FALSE);
		}
		else
			ReportSaveLoadException(sPathName, NULL, FALSE, AFX_IDP_FAILED_TO_SAVE_DOC);
	}	
}

/////////////////////////////////////////////////////////////////////////////
// Conversion functions

void CFI_Doc::OnConvertTo8Bits() 
{
	void *dib8 = FreeImage_ConvertTo8Bits(m_dib);
	if(dib8)
	{
		FreeImage_Free(m_dib);
		m_dib = dib8;
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);
	}
}

void CFI_Doc::OnUpdateConvertTo8Bits(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FreeImage_GetBPP(m_dib) != 8);
}

void CFI_Doc::OnConvertTo16Bits() 
{
	void *dib16 = FreeImage_ConvertTo16Bits(m_dib, true);
	if(dib16)
	{
		FreeImage_Free(m_dib);
		m_dib = dib16;
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);
	}	
}

void CFI_Doc::OnUpdateConvertTo16Bits(CCmdUI* pCmdUI) 
{
	BYTE bpp = FreeImage_GetBPP(m_dib);
	pCmdUI->Enable((bpp != 1) && (bpp != 16));	
}

void CFI_Doc::OnConvertTo24Bits() 
{
	void *dib24 = FreeImage_ConvertTo24Bits(m_dib, true);
	if(dib24)
	{
		FreeImage_Free(m_dib);
		m_dib = dib24;
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);
	}	
}

void CFI_Doc::OnUpdateConvertTo24Bits(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FreeImage_GetBPP(m_dib) != 24);	
}

void CFI_Doc::OnConvertTo32Bits() 
{
	void *dib32 = FreeImage_ConvertTo32Bits(m_dib, true);
	if(dib32)
	{
		FreeImage_Free(m_dib);
		m_dib = dib32;
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);
	}	
}

void CFI_Doc::OnUpdateConvertTo32Bits(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FreeImage_GetBPP(m_dib) != 32);	
}

void CFI_Doc::OnColorQuantize() 
{
	CWaitCursor wait;
	void *dib8 = FreeImage_ColorQuantize(m_dib, FIQ_WUQUANT);
	if(dib8)
	{
		FreeImage_Free(m_dib);
		m_dib = dib8;
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);
	}	
}

void CFI_Doc::OnUpdateColorQuantize(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FreeImage_GetBPP(m_dib) == 24);
}

void CFI_Doc::OnConvertToGreyscale() 
{
	FreeImage_ConvertToGreyscale(m_dib);
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

void CFI_Doc::OnUpdateConvertToGreyscale(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FreeImage_GetBPP(m_dib) != 16);
}

/////////////////////////////////////////////////////////////////////////////
// Symetry functions

void CFI_Doc::OnFlip() 
{
	CWaitCursor wait;
	FreeImage_Flip(m_dib);
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

void CFI_Doc::OnMirror() 
{
	CWaitCursor wait;
	FreeImage_Mirror(m_dib);
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);	
}

void CFI_Doc::OnRotate() 
{
	DlgRotation dlg;
	if(dlg.DoModal() == IDOK)
	{
		CWaitCursor wait;
		void *dib = FreeImage_Rotate(m_dib, dlg.m_Angle);
		if(dib)
		{
			FreeImage_Free(m_dib);
			m_dib = dib;
			SetModifiedFlag(TRUE);
			UpdateAllViews(NULL);
		}	
	}
}

/////////////////////////////////////////////////////////////////////////////
// Image infos

void CFI_Doc::OnImageInfos() 
{
	if(!m_dib)
		return;

	DlgImageInfos dlg;
	BITMAPINFOHEADER *bih = FreeImage_GetInfoHeader(m_dib);
	switch(FreeImage_GetColorType(m_dib))
	{
		case FIC_MINISBLACK:
			switch(bih->biBitCount) {
			  case 1:
			    dlg.m_Class = "BINARY (min value is black)";
				break;
			  case 8:
				dlg.m_Class = "GREYSCALE (min value is black)";
				break;
			}
			break;
		case FIC_MINISWHITE:
			switch(bih->biBitCount) {
			  case 1:
			    dlg.m_Class = "BINARY (min value is white)";
				break;
			  case 8:
				dlg.m_Class = "GREYSCALE (min value is white)";
				break;
			}
			break;
		case FIC_PALETTE:
			dlg.m_Class = "COLOR PALETTE";
			break;
		case FIC_RGB:
			dlg.m_Class = "RGB";
			break;
	}
	dlg.m_Width = bih->biWidth;
	dlg.m_Height = bih->biHeight;
	dlg.m_Depth = bih->biBitCount;
	dlg.m_ResX = bih->biXPelsPerMeter;
	dlg.m_ResY = bih->biYPelsPerMeter;

	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// Effects

void CFI_Doc::OnInvert() 
{
	CWaitCursor wait;
	FreeImage_Invert(m_dib);
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);	
}



void CFI_Doc::OnBlur() 
{
	CWaitCursor wait;
	FreeImage_Blur(m_dib);
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);	
}

void CFI_Doc::OnUpdateBlur(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FreeImage_GetBPP(m_dib) == 24);		
}

void CFI_Doc::OnBrighten() 
{
	DlgFloat dlg;
	dlg.m_sCaption = "Brighten";
	dlg.m_FloatName = "Factor";
	dlg.m_FloatValue = 1.2F;
	if(dlg.DoModal() == IDOK)
	{
		CWaitCursor wait;
		FreeImage_Brighten(m_dib, dlg.m_FloatValue);
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);	
	}	
}

void CFI_Doc::OnUpdateBrighten(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FreeImage_GetBPP(m_dib) == 24);
}

void CFI_Doc::OnDarken() 
{
	DlgFloat dlg;
	dlg.m_sCaption = "Darken";
	dlg.m_FloatName = "Factor";
	dlg.m_FloatValue = 1.2F;
	if(dlg.DoModal() == IDOK)
	{
		CWaitCursor wait;
		FreeImage_Darken(m_dib, dlg.m_FloatValue);
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);	
	}		
}

void CFI_Doc::OnUpdateDarken(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FreeImage_GetBPP(m_dib) == 24);	
}

