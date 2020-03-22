// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: HandleEvents.cpp
//  Description: Implementation of the event handlers for SolidWorks
//               notifications.
//
// -------------------------------------------------------------------

// To Handle events sent by a SolidWorks Object: 
//  	Derive an object like swx*****Events from CControlItem
//  	Define Functions on this object to handle the events you are interested in
//  	Put appropriate ON_EVENT lines for those events in the object's EVENTSINK map
//
// Syntax for ON_EVENT 
//
//  ON_EVENT (object, -1, swxEventID, handlerFunc, handlerFuncArgs)
//   handlerFuncArgs are specified in the API documentation for that event.
//   It is a space seperated list of arguments with appropriate types
//   defined in mfc\include\afxdisp.h file Some common ones are
//  
//   double			VTS_R8
//   long			VTS_I4
//	 boolean		VTS_BOOL
//   IDispatch*     VTS_DISPATCH
//   LPCOLESTR		VTS_WBSTR
//	 No args		VTS_NONE

#include "stdafx.h"

#include "SldWorks.h"
#include "HandleEvents.h"
#include "ExampleApp.h"

// --------------------------------
//  Application Events
// --------------------------------

BEGIN_EVENTSINK_MAP(swAppEvents, CControlItem)
	ON_EVENT (swAppEvents, (unsigned int)-1, swAppActiveModelDocChangeNotify, OnModelDocChange, VTS_NONE)
	ON_EVENT (swAppEvents, (unsigned int)-1, swAppFileOpenNotify, OnDocumentOpen, VTS_BSTR)
	ON_EVENT (swAppEvents, (unsigned int)-1, swAppFileNewNotify, OnDocumentNew, VTS_DISPATCH VTS_I4)
	ON_EVENT (swAppEvents, (unsigned int)-1, swAppDestroyNotify, OnDestroy, VTS_NONE)
END_EVENTSINK_MAP()

// A new document has been actived by the user.
//
HRESULT swAppEvents::OnModelDocChange(void)
{
	// If this is the first time a document of this type has been
	// activated, add the appropriate menus.  This can occur if the
	// application is loaded after SolidWorks is running.
	TheApplication->AddMenus();

	return S_OK;
}

// An existing document has been opened.
//
HRESULT swAppEvents::OnDocumentOpen(BSTR docName)
{
	// make sure a document of this type has menus
	TheApplication->AddMenus();

	return S_OK;
}

// A new document has been created.
//
HRESULT swAppEvents::OnDocumentNew(LPDISPATCH NewDoc, long DocType)
{
	return S_OK;
}

// SolidWorks is shutting down and will destroy this applications
// menus, notification and save-as items
//
HRESULT swAppEvents::OnDestroy(void)
{
	delete  this;
	TheApplication->SetSWApp(NULL);

	return S_OK;
}

// --------------------------------
//  End of HandleEvents.cpp
// --------------------------------
