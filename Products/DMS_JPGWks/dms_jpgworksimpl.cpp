// DMS_JPGWORKSIMPL : Implementation of TDMS_JPGWorksImpl (CoClass: DMS_JPGWorks, Interface: IDMS_JPGWorks)

#include <vcl.h>
#pragma hdrstop

#include "DMS_JPGWORKSIMPL.H"
#include "Configure.h"

/////////////////////////////////////////////////////////////////////////////
// TDMS_JPGWorksImpl
TDMS_JPGWorksImpl::~TDMS_JPGWorksImpl()
{
}
//------------------------------------------------------------------------
TDMS_JPGWorksImpl::TDMS_JPGWorksImpl()
{
}
//------------------------------------------------------------------------
HRESULT TDMS_JPGWorksImpl::FinalConstruct()
{
    ObjectLock(this);

    HRESULT                     hr = S_OK;
    try
        {
        m_Icon = NULL;
        frmConfigure = new TfrmConfigure(NULL);
        }
    catch (...)
        {
        }

    return hr;
}
//------------------------------------------------------------------------
HRESULT TDMS_JPGWorksImpl::FinalRelease  ()
{
    ObjectLock(this);

    try
        {
        delete frmConfigure;
        }
    catch (...)
        {
        }
    return S_OK;
}
//------------------------------------------------------------------------
STDMETHODIMP TDMS_JPGWorksImpl::Configure()
{
    ObjectLock(this);

    try
        {
        frmConfigure->ShowModal();
        }
    catch (...)
        {
        }
    return S_OK;
}
//------------------------------------------------------------------------
STDMETHODIMP TDMS_JPGWorksImpl::SaveAsJPEG(BSTR FileName, long Handle)
{
    ObjectLock(this);

    try
        {
        HANDLE                  WindowHandle = (HANDLE ) Handle;
        HDC                     winDC = GetWindowDC(WindowHandle);
        int                     Width;
        int                     Height;
        int                     Quality;
        bool                    ProgressiveJPEG;
        TRect                   Rect;

        // get the SW bitmap window size
        GetWindowRect(WindowHandle, &Rect);

        // initially set our image to be the same size as SW
        frmConfigure->SWImage->Width  = Rect.Right  - Rect.Left;
        frmConfigure->SWImage->Height = Rect.Bottom - Rect.Top;

        // do a direct copy from SW to ours
        BitBlt(frmConfigure->SWImage->Canvas->Handle, 0, 0,
            frmConfigure->SWImage->Width,
            frmConfigure->SWImage->Height,
            winDC, 0, 0, SRCCOPY);

            
        // setup all the parameters for our JPEG output
        
        if (true == frmConfigure->chkSpecifySize->Checked)
            {
            Width  = frmConfigure->sedWidth ->Value;
            Height = frmConfigure->sedHeight->Value;
            }
        else
            {
            // box unchecked = use SW image size
            Width  = frmConfigure->SWImage->Width ;
            Height = frmConfigure->SWImage->Height;
            }

        frmConfigure->JPEGFileCompressor->ProgressiveJPEG = frmConfigure->chkProgressive->Checked; 
        frmConfigure->JPEGFileCompressor->Quality         = frmConfigure->sedQuality->Value;

        // ouput to file
        frmConfigure->JPEGFileCompressor->SaveStretchedPictureToFile(
            frmConfigure->SWImage->Picture,
            Width,
            Height,
            ::String(FileName));

        ReleaseDC(WindowHandle, winDC);
        }
    catch (...)
        {
        }

    return S_OK;
}
//------------------------------------------------------------------------

