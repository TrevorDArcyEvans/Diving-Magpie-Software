// DMS_STICKWORKSIMPL : Implementation of TDMS_StickWorksImpl (CoClass: DMS_StickWorks, Interface: IDMS_StickWorks)

#include <vcl.h>
#pragma hdrstop

#include "DMS_STICKWORKSIMPL.H"
#include "main.h"

/////////////////////////////////////////////////////////////////////////////
// TDMS_StickWorksImpl
TDMS_StickWorksImpl::TDMS_StickWorksImpl()
{
    m_Name = "TDE";
}
//---------------------------------------------------------------------
TDMS_StickWorksImpl::~TDMS_StickWorksImpl()
{
}
//---------------------------------------------------------------------
HRESULT TDMS_StickWorksImpl::FinalConstruct()
{
try
    {
    ObjectLock(this);

    m_Icon;
    m_Name = "TDE";

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_StickWorks);
    }
}
//---------------------------------------------------------------------
HRESULT TDMS_StickWorksImpl::FinalRelease  ()
{
try
    {
    ObjectLock(this);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_StickWorks);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_StickWorksImpl::Configure()
{
try
    {
    ObjectLock(this);

    frmJoystick = new TfrmJoystick(NULL);

    frmJoystick->Caption = m_Name;
    frmJoystick->Icon->Handle = m_Icon;
    frmJoystick->ShowModal();

    delete frmJoystick;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_StickWorks);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_StickWorksImpl::get_Name(BSTR* sName)
{
try
    {
    ObjectLock(this);

    *sName = WideString(m_Name).Detach();

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_StickWorks);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_StickWorksImpl::set_Name(BSTR sName)
{
try
    {
    ObjectLock(this);

    m_Name = String(sName);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_StickWorks);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_StickWorksImpl::set_Icon(long hIcon)
{
try
    {
    ObjectLock(this);

    m_Icon = (HICON ) hIcon;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_StickWorks);
    }
}
//---------------------------------------------------------------------

