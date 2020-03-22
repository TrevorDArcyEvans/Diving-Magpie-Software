#include "stdafx.h"
#include "SLinkCounted.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SLinkCounted::SLinkCounted ()
:m_Count (0)
{
}//SLinkCounted::SLinkCounted

void SLinkCounted::Link ()
{
	m_Count++;
}//SLinkCounted::Link

void SLinkCounted::Unlink ()
{
	if (--m_Count <= 0)
		delete this;
	//if
}//SLinkCounted::Unlink
