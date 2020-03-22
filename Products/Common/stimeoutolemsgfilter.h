// STimeOutOleMsgFilter.h: interface for the STimeOutOleMsgFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STIMEOUTOLEMSGFILTER_H__2FD334C4_77F2_11D4_83D9_00104BB2580C__INCLUDED_)
#define AFX_STIMEOUTOLEMSGFILTER_H__2FD334C4_77F2_11D4_83D9_00104BB2580C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SOleMsgFlt.h"
#include "SRegistryAccess.hpp"

// see documentation in SOleMsgFlt.cpp
class STimeOutOleMsgFilter : public SOleMsgFilter
{
private:
    // time (in seconds) to wait for DCOM call to complete
    // default value = 30 seconds
    int                     m_nTimeOutSec;


    COleDateTime            m_StartTime;

    // helper functions
    void Initialise();

public:
    STimeOutOleMsgFilter();
    STimeOutOleMsgFilter
        (
            CString         sRegKey
        );

    virtual ~STimeOutOleMsgFilter();
    virtual DWORD OnMessagePending(const MSG* pMsg);

};

#endif // !defined(AFX_STIMEOUTOLEMSGFILTER_H__2FD334C4_77F2_11D4_83D9_00104BB2580C__INCLUDED_)
