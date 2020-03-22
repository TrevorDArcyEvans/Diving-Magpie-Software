#include "stdafx.h"
#include "SGlobalBox.hpp"
#include "SProjection.hpp"

SPaperBox SGlobalBox::CreatePaperBox 
(
	const SProjection& Projection
)const
{
	SPaperBox RetVal;

	if (m_Virgin)
		return RetVal;
	else if (m_CoversNP)
	{
		if (!Projection.NPIsPoint ())
			return RetVal;
		else
		{
//			NotPerfect
			for (double Long = -150.0; Long <= 150.0; Long += 60.0)
				RetVal.Fit (Projection.GlobalToPaper (SGlobalPoint (m_BottomLat,Long)));
			//for

			return RetVal;
		}//if
	}
	else if (m_CoversSP)
	{
		if (!Projection.SPIsPoint ())
			return RetVal;
		else
		{
//			NotPerfect
			for (double Long = -150.0; Long <= 150.0; Long += 60.0)
				RetVal.Fit (Projection.GlobalToPaper (SGlobalPoint (m_TopLat,Long)));
			//for

			return RetVal;
		}//if
	}
	else
	{
		RetVal.Fit (Projection.GlobalToPaper (SGlobalPoint (m_BottomLat,m_LeftLong)));
		RetVal.Fit (Projection.GlobalToPaper (SGlobalPoint (m_TopLat,m_LeftLong)));
		RetVal.Fit (Projection.GlobalToPaper (SGlobalPoint (m_BottomLat,m_RightLong)));
		RetVal.Fit (Projection.GlobalToPaper (SGlobalPoint (m_TopLat,m_RightLong)));

		return RetVal;
	}//if
}//SGlobalBox::CreatePaperBox

