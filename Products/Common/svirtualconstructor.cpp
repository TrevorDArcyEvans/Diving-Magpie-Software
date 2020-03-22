#include "stdafx.h"
#include "SVirtualConstructor.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SVirtualConstructor*	SVirtualConstructor::sm_Instance = 0;

SVCLink::SVCLink 
(
	int AddToChain
)
:m_NextLink (0) 
{
	if (AddToChain)
		SVirtualConstructor::Instance ()->AddLink (this);
	//if		
}//SVCLink::SVCLink

SVCLink::~SVCLink ()
{
	if (m_NextLink)
		delete m_NextLink;
	//if
}//SVCLink::~SVCLink

void SVCLink::AddLink 
(
	SVCLink* NewLink
)
{
	if (m_NextLink)
		m_NextLink->AddLink (NewLink);
	else
		m_NextLink = NewLink;
	//if
}//SVCLink::AddLink

void* SVCLink::ConstructObject 
(
	LPCTSTR Named
)
{
	void* RetVal = DoConstructObject (Named);

	if (RetVal)
		return RetVal;
	else if (m_NextLink)
		return m_NextLink->ConstructObject (Named);
	else
		return 0;
	//if
}//SVCLink::ConstructObject

SVirtualConstructor::~SVirtualConstructor ()
{
}//SVirtualConstructor::~SVirtualConstructor

void SVirtualConstructor::Destroy ()
{
	if (sm_Instance)
	{
		delete sm_Instance;
		sm_Instance = 0; 
	}//if
//	LEAVE NOW
}//SVirtualConstructor::Destroy

SVirtualConstructor* SVirtualConstructor::Instance ()
{
	if (!sm_Instance)
		sm_Instance = new SVirtualConstructor;
	//if

	return sm_Instance;
}//SVirtualConstructor::Instance

void* SVirtualConstructor::ConstructObject 
(
	LPCTSTR Named
)
{
	return m_FirstLink.ConstructObject (Named);
}//SVirtualConstructor::ConstructObject

void  SVirtualConstructor::AddLink
(
	SVCLink* NewLink
)
{
	m_FirstLink.AddLink (NewLink);
}//SVirtualConstructor::AddLink


	
