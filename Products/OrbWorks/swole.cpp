//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "orb.h"
#include "process.h"
//---------------------------------------------------------------------------
void	TfrmOrb :: swOleProcedure(
    		int             	SW_OleType 		,
			const String& 		SW_OleProcName	,
    		int             	SW_OleNumParam	,
            int					SW_OleParam1	)
{
// attempt to do the OLE stuff
try
	{
    // first refresh our connection to SolidWorks
	frmOrb->swApp = CreateOleObject("SldWorks.Application");

	// refresh the active document
    swModelDoc  = swApp.OleFunction("ActiveDoc");
    swPart = swModelDoc;
    swAssy = swModelDoc;

    if (SW_OleNumParam == 0)
    	{
    	switch (SW_OleType)
    		{
        	case TYPE_APP	:	swApp       .OleProcedure(SW_OleProcName);		break;
        	case TYPE_DOC   :	swModelDoc  .OleProcedure(SW_OleProcName);		break;
        	case TYPE_ASS   :	swAssy      .OleProcedure(SW_OleProcName);		break;
        	case TYPE_DWG   :	/*swApp     .OleProcedure(SW_OleProcName);*/	break;
        	}
        }

    if (SW_OleNumParam == 1)
    	{
    	switch (SW_OleType)
    		{
        	case TYPE_APP	:	swApp       .OleProcedure(SW_OleProcName, SW_OleParam1);		break;
        	case TYPE_DOC   :	swModelDoc  .OleProcedure(SW_OleProcName, SW_OleParam1);		break;
        	case TYPE_ASS   :	swAssy      .OleProcedure(SW_OleProcName, SW_OleParam1);		break;
        	case TYPE_DWG   :	/*swApp     .OleProcedure(SW_OleProcName, SW_OleParam1);*/		break;
        	}
        }
    }

// OLE automation servers
catch(EOleException& e)
	{
    stbOrb->SimpleText = "OLE Error:  " + e.Message + "(" + e.ErrorCode + ")";
	}

// OLE API errors
catch(EOleSysError& e)
	{
    stbOrb->SimpleText = "OLE Error:  " + e.Message + "(" + e.ErrorCode + ")";
  	}

// OLE automation errors
catch(EOleError& e)
	{
    stbOrb->SimpleText = "OLE Error:  " + e.Message;
    }

//If none of the above exceptions, catch it so that we can close the handle
catch(...)
	{
    stbOrb->SimpleText = "OLE Error:  unknown error";
    }
}
//---------------------------------------------------------------------------
