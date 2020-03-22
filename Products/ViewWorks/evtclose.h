// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: EvtClose.h
//  Description: Definition of event handler classes for SolidWorks
//               notifications.
//
// -------------------------------------------------------------------

#if !defined(EVTCLOSE_H)
#define EVTCLOSE_H

#include "ccitem.h"

class swEventClose;

class swEventClose : public CControlItem
{
public:
	swEventClose(){}
	DECLARE_EVENTSINK_MAP()

	HRESULT OnDestroy(void);
};

#endif

// --------------------------------
//  End of EvtClose.h
// --------------------------------
