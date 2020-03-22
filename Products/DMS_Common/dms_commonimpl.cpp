// DMS_COMMONIMPL : Implementation of TDMS_CommonImpl (CoClass: DMS_Common, Interface: IDMS_Common)

#include <vcl.h>
#pragma hdrstop

#define        MAIN    1

#include <Registry.hpp>

#include "DMS_COMMONIMPL.H"
#include "about.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "enum.h"
#include "SWutils.h"
#include "utils.h"

/////////////////////////////////////////////////////////////////////////////
// TDMS_CommonImpl
TDMS_CommonImpl::TDMS_CommonImpl()
{
    m_hIcon             = NULL;
    m_bIsRegistered     = false;
    m_bCommercial       = true;
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::About()
{
try
    {
    ObjectLock(this);

    frmAbout = new TfrmAbout(NULL);

    if (!m_sProductName.IsEmpty() &&
         m_sProductName.Length () > 0)
        {
        frmAbout->Caption = m_sProductName;

        // for some strange reason, won't work with +=
        frmAbout->lblProductName->Caption = frmAbout->lblProductName->Caption + m_sProductName;
        }

    frmAbout->lblCommercial->Caption = (true == m_bCommercial) ?
        "Commercial Version" : "Freeware Version" ;

    if (m_hIcon)
        {
        frmAbout->ProgramIcon->Picture->Icon->Handle = m_hIcon;
        }

    frmAbout->ShowModal();

    delete frmAbout;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::get_Commercial(int* Value)
{
try
    {
    ObjectLock(this);

    if (NULL == Value) { return E_POINTER; }

    *Value = m_bCommercial;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
// TDMS_CommonImpl::get_IsRegistered
// returns whether product is registered
//
// parameters
//      [out]   bIsRegistered
//          receives whether product is registered
//
// returns
//      S_OK
//          always
//
// notes
//      product will be considered unregistered if either the ProductCode or
//      Authcode has not been set.
STDMETHODIMP TDMS_CommonImpl::get_IsRegistered(int* bIsRegistered)
{
try
    {
    ObjectLock(this);

    if (NULL == bIsRegistered) { return E_POINTER; }

    // try to read codes from .ini file
    ReadSecurityCode();

    // have to have a product code and an auth code before we try anything
    if (m_sProductCode.IsEmpty()    ||
        m_sAuthCode   .IsEmpty()    )
        {
        ASSERT(false == m_bIsRegistered);
        *bIsRegistered = false;
        return S_OK;
        }

    // if already registered, then don't bother to check again
    if (true == m_bIsRegistered)
        {
        *bIsRegistered = true;
        return S_OK;
        }

    // now start the authorisation code checking
    char            MachineID[MAX_PATH];

    strcpy(MachineID, ::GetMachineID());

    m_bIsRegistered = CheckCode(MachineID, m_sProductCode.c_str(), m_sAuthCode.c_str());

    *bIsRegistered = m_bIsRegistered;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::get_ProductCode(BSTR* sProductCode)
{
try
    {
    ObjectLock(this);

    if (NULL == sProductCode) { return E_POINTER; }

    *sProductCode = WideString(m_sProductCode).Detach();

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::get_ProductName(BSTR* sProductName)
{
try
    {
    ObjectLock(this);

    if (NULL == sProductName) { return E_POINTER; }

    *sProductName = WideString(m_sProductName).Detach();

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::IsSolidWorksFile(BSTR sFileName,
  int* bIsSolidWorksFile)
{
try
    {
    ObjectLock(this);

    if (NULL == bIsSolidWorksFile) { return E_POINTER; }

    *bIsSolidWorksFile = ::IsSolidWorksFile(String(sFileName).c_str());

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
// TDMS_CommonImpl::Register
// run Register dialog and, if successful, update the internal registration state
//
// Dialog will not be run if any of the ProductCode, ProductName or Authcode has
// not been set.
//
// returns
//      S_OK
//          always
//
// notes
//      will write to successful AuthCode to .ini file
//
//      have to have a product code and an auth code before we try anything
STDMETHODIMP TDMS_CommonImpl::Register()
{
try
    {
    ObjectLock(this);

    if (m_sProductCode.IsEmpty()        ||
        m_sProductName.IsEmpty()        ||
        m_sIniFileName.IsEmpty()        )
        {
        ASSERT(false == m_bIsRegistered);
        return S_OK;
        }

    // get a fresh Register dialog
    frmCodeGen = new TfrmCodeGen(NULL);
    frmCodeGen->m_sProductCode = m_sProductCode;
    frmCodeGen->m_sProductName = m_sProductName;

    if (m_hIcon)
        {
        frmCodeGen->Icon->Handle = m_hIcon;
        }

    // run Register dialog and see if user is attempting to register
    if (mrOk == frmCodeGen->ShowModal())
        {
        // retrieve and update registration status and authorisation code
        m_bIsRegistered = frmCodeGen->m_bIsRegistered;
        m_sAuthCode     = frmCodeGen->m_sAuthCode;

        // save to .ini file
        WriteSecurityCode();
        }

    // delete Register dialog
    delete frmCodeGen;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
void TDMS_CommonImpl::WriteSecurityCode()
{
    if (m_sIniFileName.IsEmpty())
        {
        return;
        }

    TIniFile        *iniSecurity = new TIniFile(m_sIniFileName);

    // write code into .ini
    iniSecurity->WriteString("Security", "code", m_sAuthCode);

    delete iniSecurity;
}
//---------------------------------------------------------------------
void TDMS_CommonImpl::ReadSecurityCode()
{
    if (m_sIniFileName.IsEmpty())
        {
        return;
        }

    TIniFile        *iniSecurity = new TIniFile(m_sIniFileName);

    // read code from .ini
    m_sAuthCode = iniSecurity->ReadString("Security", "code", m_sAuthCode);

    delete iniSecurity;
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::set_AuthCode(BSTR sAuthCode)
{
try
    {
    ObjectLock(this);

    m_sAuthCode = String(sAuthCode);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
};
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::set_Commercial(int Value)
{
try
    {
    ObjectLock(this);

    m_bCommercial = Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::set_Icon(long hIcon)
{
try
    {
    ObjectLock(this);

    m_hIcon = (HICON ) hIcon;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::set_ProductCode(BSTR sProductCode)
{
try
    {
    ObjectLock(this);

    m_sProductCode = String(sProductCode);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::set_ProductName(BSTR sProductName)
{
try
    {
    ObjectLock(this);

    m_sProductName = String(sProductName);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::IsSolidWorksRunning(int* bIsSolidWorksRunning)
{
try
    {
    ObjectLock(this);

    if (NULL == bIsSolidWorksRunning) { return E_POINTER; }

    // see if SW is already running
    EnumWindows((WNDENUMPROC ) SolidWorksEnumFunc, (LPARAM ) 1);
    *bIsSolidWorksRunning = g_bSW_Running;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::GetMachineID(BSTR* sMachineID)
{
try
    {
    ObjectLock(this);

    if (NULL == sMachineID) { return E_POINTER; }

    *sMachineID = BSTR(WideString(::GetMachineID()));

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::get_IniFileName(BSTR* Value)
{
try
    {
    ObjectLock(this);

    if (NULL == Value) { return E_POINTER; }

    *Value = WideString(m_sIniFileName).Detach();

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::set_IniFileName(BSTR Value)
{
try
    {
    ObjectLock(this);

    m_sIniFileName = Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_CommonImpl::set_SolidWorks(IDispatch* Value)
{
try
    {
    ObjectLock(this);

    m_SolidWorks = Variant(Value);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_Common);
    }
}
//---------------------------------------------------------------------


