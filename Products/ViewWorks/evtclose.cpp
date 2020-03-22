// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: EvtClose.cpp
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
#include "debug.h"
#include "EvtClose.h"

#include "ExampleApp.h"

// --------------------------------
//  Part Events
// --------------------------------

BEGIN_EVENTSINK_MAP(swEventClose, CControlItem)
	ON_EVENT (swEventClose, (unsigned int)-1, swPartDestroyNotify       , OnDestroy, VTS_NONE)
	ON_EVENT (swEventClose, (unsigned int)-1, swAssemblyDestroyNotify   , OnDestroy, VTS_NONE)
	ON_EVENT (swEventClose, (unsigned int)-1, swDrawingDestroyNotify    , OnDestroy, VTS_NONE)
END_EVENTSINK_MAP()
// --------------------------------
HRESULT swEventClose::OnDestroy(void)
{
	// tde
	VW_OutputDebugString(_T("swEventClose::OnDestroy"));

	LPMODELDOC      pModelDoc = NULL;
    BSTR            bstrDocName;
    TCHAR           strTempFileDir  [MAX_PATH];

    HRESULT         hres;
    BOOL            bret;
    VARIANT_BOOL    bIsViewOnly;

    // first get ModelDoc being closed
    hres = TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc);

    // get name of doc being closed
    pModelDoc->GetPathName(&bstrDocName);

    // and if it is in view only mode
    hres = pModelDoc->IsOpenedViewOnly(&bIsViewOnly);

    // before getting rid of ModelDoc
    pModelDoc->Release();
		
    // get temporary directory
    GetTempPath(MAX_PATH, strTempFileDir);

    // initialise CString's
    CString         cstrTempFileDir(strTempFileDir),
                    cstrDocName    (bstrDocName   );

    // change both to uppercase since not interested in case of filenames
    cstrTempFileDir.MakeUpper();
    cstrDocName    .MakeUpper();

    // if the doc is in the temp directory & it's view only- it's fair game!
    if (-1 != cstrDocName.Find(cstrTempFileDir) &&
        TRUE == bIsViewOnly)
        {
        // remove the file
        bret = DeleteFile(cstrDocName);
        }

	delete this;
	return S_OK;
}
// --------------------------------
//  End of EvtClose.cpp
// --------------------------------
