#include "stdafx.h"
#include "SWindArrowSingleton.hpp"
#include "SHResult.hpp"

IWindVane*	SWindArrowSingleton::sm_VaneIFace = 0;


IWindVane* SWindArrowSingleton::Instance ()
{	
	if (!sm_VaneIFace)
		SHResult Res = ::CoCreateInstance (CLSID_SWindVane,
										   0,
										   CLSCTX_ALL,
										   IID_IWindVane,
										   (void**)&sm_VaneIFace);
	//if

	return sm_VaneIFace;
}//SWindArrowSingleton::Instance
	
void SWindArrowSingleton::Destroy ()
{
	if (sm_VaneIFace)
		sm_VaneIFace->Release ();
	//if
}//SWindArrowSingleton::Destroy
