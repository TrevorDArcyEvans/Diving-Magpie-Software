//$c01 JPS 06/17/98  Fix event cleanup problem with additions to CControlItem destructor.
//
// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: CcItem.cpp
//  Description: Implements the CControlItem class which serves as the
//               foundation class for this applications SolidWorks
//               event handlers.
//
// -------------------------------------------------------------------

//////
//////  YOU DO NOT NEED TO CHANGE THIS FILE. SEE HANDLEEVENTS.CPP FOR DETAILS
//////
#include "stdafx.h"

#include <initguid.h>
#include <amapp.h>
#include <afxpriv.h>

#include "CcItem.h"
#include "ExampleApp.h"
		 
CControlItem::CControlItem() : CCmdTarget()
{
	TheApplication->AddEvent(this);
}

CControlItem::~CControlItem()
{
	BOOL bres = TheApplication->RemoveEvent(this);
	ASSERT (bres);
	Release();
	m_lpObject = NULL;
}

BOOL CControlItem::OnCreate(LPDISPATCH	  pObject)
{
	LPUNKNOWN 	pUnk = NULL;
	m_lpObject = (struct IOleObject*)pObject;
	//InitControlInfo(pObject);	//only works for inprocess right now, no marshalling code from MicroSoft
	LPPROVIDECLASSINFO2 pPCI2 = NULL;

	if	(SUCCEEDED(m_lpObject->QueryInterface(IID_IProvideClassInfo2, (LPVOID*)&pPCI2)))
	{
		ASSERT(pPCI2 != NULL);

		if (SUCCEEDED(pPCI2->GetGUID(GUIDKIND_DEFAULT_SOURCE_DISP_IID, &m_iidEvents)))
			ASSERT(!IsEqualIID(m_iidEvents, GUID_NULL));
		else
			ASSERT(IsEqualIID(m_iidEvents, GUID_NULL));
		pPCI2->Release();
	}
	else
		return FALSE; // No connections
	if (S_OK!= pObject->QueryInterface(IID_IUnknown, (LPVOID *)&pUnk)) 
		return FALSE;
	LPCONNECTIONPOINTCONTAINER lpContainer;
	if (S_OK!= pUnk->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&lpContainer)) 
		return FALSE;
	if (S_OK == lpContainer->FindConnectionPoint(m_iidEvents, &m_pConnPt)) ;
	{
		ASSERT(m_pConnPt != NULL) ;
		m_pConnPt->Advise(&m_xEventHandler, &m_dwEventConnection);
	}

	pUnk->Release();
	lpContainer->Release();
	return TRUE;
}

BEGIN_INTERFACE_MAP(CControlItem, CCmdTarget)
END_INTERFACE_MAP()

STDMETHODIMP_(ULONG) CControlItem::XEventHandler::AddRef()
{
	METHOD_PROLOGUE(CControlItem, EventHandler)
	return(ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP CControlItem::XEventHandler::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, unsigned int cNames, LCID lcid, DISPID* rgdispid)
{
	METHOD_PROLOGUE(CControlItem, EventHandler)
	ASSERT_VALID(pThis);
	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CControlItem::XEventHandler::GetTypeInfo(unsigned int itinfo, LCID lcid, ITypeInfo** pptinfo)
{
	METHOD_PROLOGUE(CControlItem, EventHandler)
	ASSERT_VALID(pThis);
	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CControlItem::XEventHandler::GetTypeInfoCount(unsigned int* pctinfo)
{
	METHOD_PROLOGUE(CControlItem, EventHandler)
	*pctinfo = 0;
	return NOERROR;
}

STDMETHODIMP CControlItem::XEventHandler::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, unsigned short wFlags, DISPPARAMS* lpDispparams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, unsigned int* puArgErr)
{
		METHOD_PROLOGUE(CControlItem, EventHandler)
	ASSERT_VALID(pThis);

	AFX_EVENT event(AFX_EVENT::event, dispidMember, lpDispparams, pexcepinfo, puArgErr);

	BOOL eventHandled = pThis->OnEvent(1, &event, NULL);

	if (pvarResult != NULL)
		VariantClear(pvarResult);
	

	V_VT(pvarResult) = VT_BOOL;
	V_BOOL(pvarResult) = eventHandled;
	return event.m_hResult;
}

STDMETHODIMP CControlItem::XEventHandler::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CControlItem, EventHandler)
	*ppvObj = NULL;
// || iid  == DIID_DSldWorksEvents || iid  == DIID_DPartDocEvents || iid  == DIID_DModelViewEvents)
//	if(IID_IUnknown == iid || IID_IDispatch == iid || IsEqualIID(iid, pThis->m_iidEvents))
	if(IID_IUnknown == iid || IID_IDispatch == iid || iid == pThis->m_iidEvents)
		*ppvObj = this;
	if (NULL != *ppvObj)
		{
			((LPUNKNOWN)*ppvObj )->AddRef();
			return NOERROR;
		}
	return(HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(ULONG) CControlItem::XEventHandler::Release()
{
	METHOD_PROLOGUE(CControlItem, EventHandler)
	return(ULONG)pThis->ExternalRelease();
}

LPUNKNOWN 	 CControlItem::GetInterfaceHook(const void* iid)
{
	if(*(IID*)iid == m_iidEvents)
		 return &m_xEventHandler;
	return NULL;
}

 void CControlItem::Release(OLECLOSE dwCloseOption)
 {
 	if(m_pConnPt != NULL)
	{
		m_pConnPt->Unadvise(m_dwEventConnection);
		m_pConnPt->Release();	
	}
	m_pConnPt = NULL;
//COleClientItem::Release(dwCloseOption);
 }

BEGIN_EVENTSINK_MAP(CControlItem, CCmdTarget)
END_EVENTSINK_MAP()

// --------------------------------
//  End of CcItem.cpp
// --------------------------------
