// DMS_UNFRAGIMPL : Implementation of TDMS_UnfragImpl (CoClass: DMS_Unfrag, Interface: IDMS_Unfrag)

#include <vcl.h>
#pragma hdrstop

#include <assert.h>

#include "DMS_UNFRAGIMPL.H"
#include "UnfragFile.h"

const String UNFRAG_WORKS_TITLE                 = "UnfragWorks COM object v2.0";
const String UNFRAG_WORKS_TITLE_CODE            = "UnfragWorks COM object v2.x";

const String NETWORK                            = " Network";
const String UNFRAG_WORKS_TITLE_NETWORK         = UNFRAG_WORKS_TITLE      + NETWORK;
const String UNFRAG_WORKS_TITLE_CODE_NETWORK    = UNFRAG_WORKS_TITLE_CODE + NETWORK;

/////////////////////////////////////////////////////////////////////////////
// TDMS_UnfragImpl
TDMS_UnfragImpl::TDMS_UnfragImpl()
{
}//TDMS_UnfragImpl::TDMS_UnfragImpl
//-------------------------------------------------------------------------
TDMS_UnfragImpl::~TDMS_UnfragImpl()
{
}//TDMS_UnfragImpl::~TDMS_UnfragImpl
//-------------------------------------------------------------------------
HRESULT TDMS_UnfragImpl::FinalConstruct()
{
try
    {
    ObjectLock(this);

    m_nTimeout              = 10;
    m_bRegistered           = false;
    m_bRegisteredNetwork    = false;
    m_DMS_Comm              = CoDMS_Common::Create();
    assert(m_DMS_Comm);

    // default to non-network use = lowest version
    m_DMS_Comm->set_ProductCode(WideString(UNFRAG_WORKS_TITLE));

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::FinalConstruct
//-------------------------------------------------------------------------
HRESULT TDMS_UnfragImpl::FinalRelease  ()
{
    m_DMS_Comm->Release();
    
    return S_OK;
}//TDMS_UnfragImpl::FinalRelease
//-------------------------------------------------------------------------
STDMETHODIMP TDMS_UnfragImpl::get_IsRegistered(int* bIsRegistered)
{
try
    {
    ObjectLock(this);

    m_DMS_Comm->set_ProductCode(WideString(UNFRAG_WORKS_TITLE));

    m_DMS_Comm->get_IsRegistered(bIsRegistered);
    m_bRegistered = *bIsRegistered;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::get_IsRegistered
//-------------------------------------------------------------------------
STDMETHODIMP TDMS_UnfragImpl::get_IsRegisteredNetwork(int* bIsRegistered)
{
try
    {
    ObjectLock(this);

    m_DMS_Comm->set_ProductCode(WideString(UNFRAG_WORKS_TITLE_NETWORK));

    m_DMS_Comm->get_IsRegistered(bIsRegistered);
    m_bRegisteredNetwork = *bIsRegistered;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::get_IsRegisteredNetwork
//-------------------------------------------------------------------------
// sets authorisation code and updates internal registration state
STDMETHODIMP TDMS_UnfragImpl::set_AuthCode(BSTR sAuthCode)
{
try
    {
    ObjectLock(this);

    m_DMS_Comm->set_ProductCode(WideString(UNFRAG_WORKS_TITLE_CODE));
    m_DMS_Comm->set_AuthCode(sAuthCode);
    m_DMS_Comm->get_IsRegistered(&m_bRegistered);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::set_AuthCode
//-------------------------------------------------------------------------
// sets authorisation code and updates internal (network) registration state
// will also update non-network registration state
STDMETHODIMP TDMS_UnfragImpl::set_AuthCodeNetwork(BSTR sAuthCode)
{
try
    {
    ObjectLock(this);

    m_DMS_Comm->set_ProductCode(WideString(UNFRAG_WORKS_TITLE_CODE_NETWORK));
    m_DMS_Comm->set_AuthCode(sAuthCode);
    m_DMS_Comm->get_IsRegistered(&m_bRegisteredNetwork);

    // also update non-network regsitration status but only if successful
    // since may have successfully registered for non-network use
    if (true == m_bRegisteredNetwork)
        {
        m_bRegistered = m_bRegisteredNetwork;
        }

    return S_OK;
    }
catch(Exception &e)
    {
  return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::set_AuthCodeNetwork
//-------------------------------------------------------------------------
STDMETHODIMP TDMS_UnfragImpl::get_TimeOut(int* nTimeOut)
{
try
    {
    ObjectLock(this);

    *nTimeOut = m_nTimeout;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::get_TimeOut
//-------------------------------------------------------------------------
STDMETHODIMP TDMS_UnfragImpl::RemoveGeometry(BSTR sFileName)
{
try
    {
    ObjectLock(this);

    if (!ProceedForFile(sFileName)) { return S_OK; }

    int     bIsSolidWorksFile = false;
    m_DMS_Comm->IsSolidWorksFile(sFileName, &bIsSolidWorksFile);

    // only do this for SolidWorks files
    if (true == m_bRegistered       &&
        true == bIsSolidWorksFile   )
        {
        ::RemoveGeometry(m_nTimeout, String(sFileName).c_str());
        }

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::RemoveGeometry
//-------------------------------------------------------------------------
STDMETHODIMP TDMS_UnfragImpl::RemovePreview(BSTR sFileName)
{
try
    {
    ObjectLock(this);

    if (!ProceedForFile(sFileName)) { return S_OK; }

    int     bIsSolidWorksFile = false;
    m_DMS_Comm->IsSolidWorksFile(sFileName, &bIsSolidWorksFile);

    // only do this for SolidWorks files
    if (true == m_bRegistered       &&
        true == bIsSolidWorksFile   )
        {
        ::RemovePreview(m_nTimeout, String(sFileName).c_str());
        }

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::RemovePreview
//-------------------------------------------------------------------------
STDMETHODIMP TDMS_UnfragImpl::set_TimeOut(int nTimeOut)
{
try
    {
    ObjectLock(this);

    m_nTimeout = nTimeOut;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::set_TimeOut
//-------------------------------------------------------------------------
STDMETHODIMP TDMS_UnfragImpl::UnfragFile(BSTR sFileName, long* nBytesSaved)
{
try
    {
    ObjectLock(this);

    if (!ProceedForFile(sFileName))
        {
        *nBytesSaved = 0;
        }
    else
        {
        *nBytesSaved = ::UnfragFile(m_nTimeout, String(sFileName).c_str());
        }

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}//TDMS_UnfragImpl::UnfragFile
//-------------------------------------------------------------------------
// parameters
//       sFileName
//          fully qualified path to file to be processed
// returns
//      true
bool TDMS_UnfragImpl::ProceedForFile(BSTR sFileName)
{
try
    {
    String          sTemp = sFileName;

    if (true == PathIsNetworkPath(sTemp.c_str()))
        {
        return m_bRegisteredNetwork;
        }
    else
        {
        return m_bRegistered;
        }
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Unfrag);
    }
}
//-------------------------------------------------------------------------

