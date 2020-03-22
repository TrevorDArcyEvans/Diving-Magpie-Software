// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#include "SOleMsgFlt.h"

#if 0
====================================8<====================================

HOWTO Configure DCOM Timeouts

http://codeguru.earthweb.com/atl/dcom_timeout.shtml

This code was contributed by Chris Kohlhepp.

Synopsis

This HOWTO describes the configuration of timeouts on DCOM clients. It
assumes that you are using Visual C++ 5.0 and are linking to MFC in the
client application. Further, it assumes that the client application is not
calling out from a free threaded apartment.

We will also look at how to dispense with the disturbing "Server Not
Responding - Switch To" and "Server Busy" dialog boxes.

Introduction
Not long after my first attempts at ATL and DCOM, I developed two pet
hates:

1) 'Prefab' dialog boxes that interrupt the application and launch the
taskbar START menu when the client cannot connect to the server.

2) Lack of support for timeouts.

A worst case scenario would be: A Windows 95 LAN client belonging to the
domain "engineering.mycompany" attempts to instantiate an object on the
server with the NETBIOS name "Einstein". The client can try to locate
"Einstein" in a number of ways, including concatenating "Einstein" and
"engineering.mycompany" to a single domain name and asking the local name
server to resolve this name. Let us further assume that the LAN is
connected to the internet via a dial-on-demand link and that the local DNS
is not a root server. If "Einstein.engineering.mycompany" cannot be
resolved, the DNS server will attempt to contact the next DNS in the
hierarchy on the internet.

In the meantime, the user of the DCOM client application is either looking
at an hour glass or gets a dialog box encouraging him/her to task-switch
to the server application - as if it were possible to task-switch across a
network.

My friend Bud Millwood and I, here at Weird Solutions Inc., have been
working on a client / server application based on DCOM and devised a
relatively straight forward solution to both problems described above. Bud
suggested that I post our solution onto the DCOM mailing list to encourage
further exploration of the issue and perhaps constructive feedback. So
here it is folks....

Solutions
1) Addressing the "Server Busy" dialog problem.
Declare an object, say "MyFilter" of class "COleMessageFilter" in your
application, ensure that you are including and call the following methods:


MyFilter.EnableNotRespondingDialog(FALSE);
MyFilter.EnableBusyDialog(FALSE);
MyFilter.Register();

This will have registered a new implementation of the IMessageFilter
interface for your application. The IMessageFilter interface is used for
concurrency management. Your new IMessageFilter differs from the default
in that it does not display the notorious dialog boxes.

2) Contemplating a solution to the timeout problem.
The suggested method
to make timeouts configurable is to implement one's own "IMessageFilter"
interface with the "MessagePending" method. >From within this method you
can return PENDINGMSG_CANCELCALL when your patience has expired. This will
unblock your application.

Canceling an ongoing DCOM call might well create temporary orphan
resources on the server, but this seems a small price to pay compared to
an non-responsive application that the user will shut down via task
manager. In any event, one is well advised to exercise good judgement in
establishing timeouts and perhaps even carry out some statistical analysis
of typical response times. I have found, for instance, that starting a
local COM service on my coding machine varies between one and three
seconds. Clearly then, a client timeout of one second would be
inappropriate, while anything in the excess of - say - 10 seconds would
provide an ample safety margin.

The question that presents itself is whether one should implement an
"IMessageFilter" interface from scratch or reuse what already ships with
MFC. The MFC class "COleMessageFilter" almost meets the requirements; it
even has a virtual function "COleMessageFilter::OnMessagePending" that you
can override in a derived class of your own. It does, however, have one
serious flaw. You might wish to examine the source code for this class in
the file "....\vc\mfc\src\olemsgf.cpp".

Two methods are of interest here:

a) "MessagePending"
This maps to the COM interface IMessageFilter::MessagePending method and
is called by DCOM to process pending messages during an otherwise blocking
DCOM call. Its simplified structure is as follows:

MessagePending()
    {

    //do something useful

    //call virtual function OnMessagePending

    return PENDINGMSG_WAITNOPROCESS
    }

b) "OnMessagePending"
This is the virtual function called by
MessagePending(). You may override this function in a derived class to
customize the behaviour of your application.
Now here is the problem: Microsoft has already decided for us what will be
returned by MessagePending(). The return value of your implementation of
OnMessagePending() is ignored completely in the parent function
MessagePending(). Hence, whatever you return from OnMessagePending() is
inconsequential.

What now?
We could of course modify the source of "COleMessageFilter" and rebuild
MFC. For our purposes, this was inappropriate.

The MS Visual C++ 5.0 help files state:
"You will probably want to implement your own message filter.The default
implementation provided by COM offers only minimal message filtering
capability."

Rather than building the message filter from scratch, I have opted to take
over the code base from "COleMessageFilter" to create my own base class
with an identical interface and named it "COleMsgFilter". It exists
parallel to and independent from the MFC class "COleMessageFilter". The
minor - but crucial - change in the implementation of
COleMsgFilter::MessagePending() is to actually return the value from the
function call to COleMsgFilter::OnMessagePending(). This will allow
returning PENDINGMSG_CANCELCALL from within OnMessagePending() and thus
allow controlling the DCOM timeout.

3) Implementing the solution to the timeout problem.

Prepare the class header file.
------------------------------
a) Open the file "../vc/mfc/include/afxole.h". "afxole.h" is a collection
header file for a number of OLE classes. Look for the definition of the
"COleMessageFilter" class. It is prefixed with the following header:

///////////////////////////////////////////////////////////////////
////////// // COleMessageFilter (implements IMessageFilter)

Mark and copy the COMPLETE class definition and paste it to a new header
file, named "OleMsgFlt.h".
b) Search for every instance of "COleMessageFilter" in the file
OleMsgFlt.h and replace it with "COleMsgFilter".
c) Change the return type of OnMessagePending() from BOOL to DWORD.

Prepare the class CPP file.
------------------------------
a) Open the file "../vc/mfc/src/olemsgf.cpp", copy its contents to a new
file, and save it in your project directory under "OleMsgFlt.cpp".
b) Search for every instance of "COleMessageFilter" in the file
OleMsgFlt.cpp and replace it with "COleMsgFilter".
c) Insert the statement shown below at the top of your CPP file.

    #include "OleMsgFlt.h"

d) Insert the line shown below at the top of your CPP file

    #include

e) From the file "../vc/mfc/src/afximpl.h" copy the line shown below to
the top of your CPP file

    #define _countof(array) (sizeof(array)/sizeof(array[0]))

f) From the file ""../vc/mfc/include/afxpriv.h" copy the line shown below
to the top of your CPP file

    #define WM_KICKIDLE         0x036A

g) Find the method "COleMsgFilter::XMessageFilter::MessagePending" and
within it, the line where OnMessagePending() is called. It should look
like this:

               pThis->OnMessagePending(&msg);

Prefix this line with "return", like so:

    return pThis->OnMessagePending(&msg);

h) Change the return type of the implementation of OnMessagePending() from
BOOL to DWORD.
i) You will find that some of the initialization functions for the class'
data members are absent from the class implementation. This is because
they are in-lined in the file "AfxOle.inl". Their non in-lined
counterparts are shown below. You can just copy and paste them directly
into your CPP file.

void COleMsgFilter::SetRetryReply(DWORD nRetryReply)
{
  m_nRetryReply = nRetryReply;
}
void COleMsgFilter::SetMessagePendingDelay(DWORD nTimeout)
{
   m_nTimeout = nTimeout;
}
void COleMsgFilter::SetBusyReply(SERVERCALL nBusyReply)
{
  m_nBusyReply = nBusyReply;
}
void COleMsgFilter::EnableBusyDialog(BOOL bEnableBusy)
{
  m_bEnableBusy = bEnableBusy;
}
void COleMsgFilter::EnableNotRespondingDialog(BOOL bEnableNotResponding )
{
  m_bEnableNotResponding = bEnableNotResponding;
}

Compilation and linking
Insert both files into your project, make sure as well as the standard
DCOM / OLE headers are included in your project, and compile...

Usage
Derive from COleMsgFilter and implement your own OnMessagePending()
function. Here you can check for timeout and return PENDINGMSG_CANCELCALL
when your application has timed out.

====================================8<====================================

#endif

#ifdef AFX_OLE4_SEG
#pragma code_seg(AFX_OLE4_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

#define _countof(array) (sizeof(array)/sizeof(array[0]))

#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in

/////////////////////////////////////////////////////////////////////////////
// SOleMsgFilter::IMessageFilter implementation

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

SOleMsgFilter::SOleMsgFilter()
{
    // begin in not-busy state
    m_nBusyCount = 0;

    // dialogs are enabled by default
    m_bEnableBusy = TRUE;
    m_bEnableNotResponding = TRUE;

    m_nBusyReply = SERVERCALL_RETRYLATER;
        // effective only when m_nBusyCount != 0

    m_nRetryReply = 10000;  // default is 10 sec
    m_nTimeout = 8000;  // default is 8 sec

    m_bUnblocking = FALSE;
        // TRUE to avoid re-entrancy when busy dialog is up

    m_bRegistered = FALSE;

    ASSERT_VALID(this);
}

#ifdef AFX_TERM_SEG
#pragma code_seg(AFX_TERM_SEG)
#endif

SOleMsgFilter::~SOleMsgFilter()
{
    ASSERT_VALID(this);

    Revoke();
}

/////////////////////////////////////////////////////////////////////////////
// Busy state management

#ifdef AFX_OLE4_SEG
#pragma code_seg(AFX_OLE4_SEG)
#endif

void SOleMsgFilter::BeginBusyState()
{
    ASSERT_VALID(this);
    ++m_nBusyCount;
}

void SOleMsgFilter::EndBusyState()
{
    ASSERT_VALID(this);
    if (m_nBusyCount != 0)
        --m_nBusyCount;
}

/////////////////////////////////////////////////////////////////////////////
// SOleMsgFilter operations

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

BOOL SOleMsgFilter::Register()
{
    ASSERT_VALID(this);
    ASSERT(!m_bRegistered); // calling Register twice?

    if (::CoRegisterMessageFilter(&m_xMessageFilter, NULL) == S_OK)
    {
        m_bRegistered = TRUE;
        return TRUE;
    }
    return FALSE;
}

#ifdef AFX_TERM_SEG
#pragma code_seg(AFX_TERM_SEG)
#endif

void SOleMsgFilter::Revoke()
{
    ASSERT_VALID(this);

    if (m_bRegistered)
    {
        ::CoRegisterMessageFilter(NULL, NULL);
        m_bRegistered = FALSE;
    }
}

/////////////////////////////////////////////////////////////////////////////
// SOleMsgFilter standard implementation of callbacks

#ifdef AFX_OLE4_SEG
#pragma code_seg(AFX_OLE4_SEG)
#endif

DWORD SOleMsgFilter::OnMessagePending(const MSG* /*pMsg*/)
{
    // By default we rely on OLE's default message handling for every message
    //  except WM_PAINT messages.  WM_PAINT messages should not generate
    //  out-going calls.

    BOOL bEatMessage = FALSE;
    MSG msg;
    while (::PeekMessage(&msg, NULL, WM_PAINT, WM_PAINT, PM_REMOVE|PM_NOYIELD))
    {
        bEatMessage = TRUE;
        DispatchMessage(&msg);
    }
    return bEatMessage;
}

AFX_STATIC_DATA const UINT _afxSignificantMsgs[] =
{
    WM_KEYDOWN, WM_SYSKEYDOWN,  WM_TIMER,
    WM_LBUTTONDOWN, WM_RBUTTONDOWN, WM_MBUTTONDOWN,
    WM_NCLBUTTONDOWN, WM_NCRBUTTONDOWN, WM_NCMBUTTONDOWN,
    WM_LBUTTONDBLCLK, WM_RBUTTONDBLCLK, WM_MBUTTONDBLCLK,
    WM_NCLBUTTONDBLCLK, WM_NCRBUTTONDBLCLK, WM_NCMBUTTONDBLCLK
};

BOOL SOleMsgFilter::IsSignificantMessage(MSG*)
{
    // check for "significant" messages in the queue
    MSG msg;
    for (int i = 0; i < _countof(_afxSignificantMsgs); i++)
    {
        if (::PeekMessage(&msg, NULL, _afxSignificantMsgs[i], _afxSignificantMsgs[i],
            PM_NOREMOVE|PM_NOYIELD))
        {
            if ((msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN) &&
                (HIWORD(msg.lParam) & KF_REPEAT))
            {
                // a key-repeat is a non-significant message
                continue;
            }

            // "significant" message is waiting in the queue
            return TRUE;
        }
    }

    // no significant messages in the queue
    return FALSE;
}

int SOleMsgFilter::OnBusyDialog(HTASK htaskBusy)
{
    COleBusyDialog dlg(htaskBusy, FALSE);

    int nResult = -1;
    TRY
    {
        if (dlg.DoModal() == IDOK)
            nResult = dlg.GetSelectionType();
    }
    END_TRY

    return nResult;
}

int SOleMsgFilter::OnNotRespondingDialog(HTASK htaskBusy)
{
    COleBusyDialog dlg(htaskBusy, TRUE);

    int nResult = -1;
    TRY
    {
        if (dlg.DoModal() == IDOK)
            nResult = dlg.GetSelectionType();
    }
    END_TRY

    return nResult;
}

/////////////////////////////////////////////////////////////////////////////
// SOleMsgFilter OLE interface implementation

BEGIN_INTERFACE_MAP(SOleMsgFilter, CCmdTarget)
    INTERFACE_PART(SOleMsgFilter, IID_IMessageFilter, MessageFilter)
END_INTERFACE_MAP()

STDMETHODIMP_(ULONG) SOleMsgFilter::XMessageFilter::AddRef()
{
    METHOD_PROLOGUE_EX_(SOleMsgFilter, MessageFilter)
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) SOleMsgFilter::XMessageFilter::Release()
{
    METHOD_PROLOGUE_EX_(SOleMsgFilter, MessageFilter)
    return pThis->ExternalRelease();
}

STDMETHODIMP SOleMsgFilter::XMessageFilter::QueryInterface(
    REFIID iid, LPVOID* ppvObj)
{
    METHOD_PROLOGUE_EX_(SOleMsgFilter, MessageFilter)
    return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(DWORD) SOleMsgFilter::XMessageFilter::HandleInComingCall(
    DWORD dwCallType, HTASK /*htaskCaller*/,
    DWORD /*dwTickCount*/, LPINTERFACEINFO /*lpInterfaceInfo*/)
{
    METHOD_PROLOGUE_EX_(SOleMsgFilter, MessageFilter)

    // check for application busy first...
    if (pThis->m_nBusyCount == 0)
    {
        if (dwCallType == CALLTYPE_TOPLEVEL ||
            dwCallType == CALLTYPE_TOPLEVEL_CALLPENDING)
        {
            // make sure CWinThread::OnIdle has a chance to run later
            MSG msg;
            if (!::PeekMessage(&msg, NULL, WM_KICKIDLE, WM_KICKIDLE, PM_NOREMOVE))
                ::PostThreadMessage(GetCurrentThreadId(), WM_KICKIDLE, 0, 0);
        }
        return SERVERCALL_ISHANDLED;
    }

    if (dwCallType == CALLTYPE_TOPLEVEL ||
        dwCallType == CALLTYPE_TOPLEVEL_CALLPENDING)
    {
        // application is busy and we have rejectable CALLTYPE
        return pThis->m_nBusyReply;
    }

    // application is busy, but CALLTYPE indicates that it *must* be handled
    return SERVERCALL_ISHANDLED;
}

STDMETHODIMP_(DWORD) SOleMsgFilter::XMessageFilter::RetryRejectedCall(
    HTASK htaskCallee, DWORD dwTickCount, DWORD dwRejectType)
{
    METHOD_PROLOGUE_EX(SOleMsgFilter, MessageFilter)
    ASSERT_VALID(pThis);

    // rejected calls get cancelled regardless of timeout
    if (dwRejectType == SERVERCALL_REJECTED)
        return (DWORD)-1;

    // if insignificant time has passed, don't panic -- just retry
    if (dwTickCount <= pThis->m_nRetryReply)
        return 0;   // retry right away (0-100 are retry immediate)

    // too much time has passed, do something more drastic
    if (pThis->m_bEnableBusy)
    {
        // show busy dialog
        int selType = pThis->OnBusyDialog(htaskCallee);

        // take action depending on selection
        switch (selType)
        {
        case -1:
            return (DWORD)-1;   // cancel outgoing call

        case COleBusyDialog::retry:
            return 0;           // retry immediately
        }
    }
    return pThis->m_nRetryReply;    // use standard retry timeout
}

STDMETHODIMP_(DWORD) SOleMsgFilter::XMessageFilter::MessagePending(
    HTASK htaskCallee, DWORD dwTickCount, DWORD /*dwPendingType*/)
{
    METHOD_PROLOGUE_EX(SOleMsgFilter, MessageFilter)
    ASSERT_VALID(pThis);

    MSG msg;
    if (dwTickCount > pThis->m_nTimeout && !pThis->m_bUnblocking &&
        pThis->IsSignificantMessage(&msg))
    {
        if (pThis->m_bEnableNotResponding)
        {
            pThis->m_bUnblocking = TRUE;    // avoid reentrant calls

            // eat all mouse messages in our queue
            while (PeekMessage(&msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST,
                PM_REMOVE|PM_NOYIELD))
                ;
            // eat all keyboard messages in our queue
            while (PeekMessage(&msg, NULL, WM_KEYFIRST, WM_KEYLAST,
                PM_REMOVE|PM_NOYIELD))
                ;

            // show not responding dialog
            pThis->OnNotRespondingDialog(htaskCallee);
            pThis->m_bUnblocking = FALSE;

            return PENDINGMSG_WAITNOPROCESS;
        }
    }

    // don't process re-entrant messages
    if (pThis->m_bUnblocking)
        return PENDINGMSG_WAITDEFPROCESS;

    // allow application to process pending message
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE|PM_NOYIELD))
        return pThis->OnMessagePending(&msg);

    // by default we return pending MSG wait
    return PENDINGMSG_WAITNOPROCESS;
}

/////////////////////////////////////////////////////////////////////////////
// SOleMsgFilter diagnostics

#ifdef _DEBUG
void SOleMsgFilter::AssertValid() const
{
    CCmdTarget::AssertValid();
}

void SOleMsgFilter::Dump(CDumpContext& dc) const
{
    CCmdTarget::Dump(dc);

    dc << "m_bRegistered = " << m_bRegistered;
    dc << "\nm_nBusyCount = " << m_nBusyCount;
    dc << "\nm_bEnableBusy = " << m_bEnableBusy;
    dc << "\nm_bEnableNotResponding = " << m_bEnableNotResponding;
    dc << "\nm_bUnblocking = " << m_bUnblocking;
    dc << "\nm_nRetryReply = " << m_nRetryReply;
    dc << "\nm_nBusyReply = " << m_nBusyReply;
    dc << "\nm_nTimeout = " << m_nTimeout;

    dc << "\n";
}
#endif

/////////////////////////////////////////////////////////////////////////////
// in-lined functions from "AfxOle.inl"

void SOleMsgFilter::SetRetryReply(DWORD nRetryReply)
{
  m_nRetryReply = nRetryReply;
}
void SOleMsgFilter::SetMessagePendingDelay(DWORD nTimeout)
{
   m_nTimeout = nTimeout;
}
void SOleMsgFilter::SetBusyReply(SERVERCALL nBusyReply)
{
  m_nBusyReply = nBusyReply;
}
void SOleMsgFilter::EnableBusyDialog(BOOL bEnableBusy)
{
  m_bEnableBusy = bEnableBusy;
}
void SOleMsgFilter::EnableNotRespondingDialog(BOOL bEnableNotResponding )
{
  m_bEnableNotResponding = bEnableNotResponding;
}
/////////////////////////////////////////////////////////////////////////////

