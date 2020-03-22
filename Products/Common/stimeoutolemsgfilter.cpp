// STimeOutOleMsgFilter.cpp: implementation of the STimeOutOleMsgFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "aow.h"
#include "STimeOutOleMsgFilter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

STimeOutOleMsgFilter::STimeOutOleMsgFilter()
{
    Initialise();
}//STimeOutOleMsgFilter::STimeOutOleMsgFilter
//------------------------------------------------------------------------
// STimeOutOleMsgFilter::STimeOutOleMsgFilter
// constructor to specify for which registry key to read DCOM timeout
//
// parameters
//      sRegKey
//          registry sub key under HKLM\Software\Sigmex from which to
//          read timeout value
//
// note
//      if sRegKey = "CMIDS", the timeout value will be read from:
//          [HKEY_LOCAL_MACHINE\SOFTWARE\Sigmex\CMIDS]
//          "DCOM Timeout"=dword:0000001e
STimeOutOleMsgFilter::STimeOutOleMsgFilter
(
    CString         sRegKey
)
{
    Initialise();

    SRegistryAccess         RegAc(HKEY_LOCAL_MACHINE);

    m_nTimeOutSec = RegAc.ReadInt(
                        sRegKey,
                        _T("DCOM Timeout"),
                        m_nTimeOutSec);
}//STimeOutOleMsgFilter::STimeOutOleMsgFilter
//------------------------------------------------------------------------
// STimeOutOleMsgFilter::Initialise
// function to set member variables - called by both constructors
void STimeOutOleMsgFilter::Initialise()
{
    m_nTimeOutSec   = 30;
    m_StartTime     = COleDateTime::GetCurrentTime();
}//STimeOutOleMsgFilter::Initialise
//------------------------------------------------------------------------
STimeOutOleMsgFilter::~STimeOutOleMsgFilter()
{

}//STimeOutOleMsgFilter::~STimeOutOleMsgFilter
//------------------------------------------------------------------------
// STimeOutOleMsgFilter::OnMessagePending
// returns
//      see MSDN help on
//          PENDINGMSG
//          IMessageFilter::MessagePending
DWORD STimeOutOleMsgFilter::OnMessagePending(const MSG* pMsg)
{
    COleDateTimeSpan        dtsInterval = COleDateTime::GetCurrentTime() - m_StartTime;

    // stop the process if we've timed out, otherwise continue waiting
    return (dtsInterval.GetSeconds() > m_nTimeOutSec) ?
                PENDINGMSG_CANCELCALL :
                TRUE;
}//STimeOutOleMsgFilter::OnMessagePending
//------------------------------------------------------------------------
