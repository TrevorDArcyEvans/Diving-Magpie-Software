//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "process.h"
//---------------------------------------------------------------------------
void	TfrmJoystick :: swOleProcedure(
    		int             	SW_OleType 		,
			const String& 		SW_OleProcName	,
    		int             	SW_OleNumParam	,
            int					SW_OleParam1	,
            float               Value           )
{

// attempt to do the OLE stuff
try
	{
    if (SW_OleNumParam == 0)
    	{
    	switch (SW_OleType)
    		{
        	case TYPE_APP	:	swApp       .OleProcedure(SW_OleProcName);		break;
        	case TYPE_DOC   :	swModelDoc  .OleProcedure(SW_OleProcName);		break;
        	case TYPE_ASS   :	swAssy      .OleProcedure(SW_OleProcName);		break;
        	case TYPE_DWG   :	/*swApp.OleProcedure(SW_OleProcName);*/		break;
        	}
        }

    if (SW_OleNumParam == 1)
    	{
    	switch (SW_OleType)
    		{
        	case TYPE_APP	:	swApp       .OleProcedure(SW_OleProcName, SW_OleParam1);		break;
        	case TYPE_DOC   :	swModelDoc  .OleProcedure(SW_OleProcName, SW_OleParam1);		break;
        	case TYPE_ASS   :	swAssy      .OleProcedure(SW_OleProcName, SW_OleParam1);		break;
        	case TYPE_DWG   :	/*swApp.OleProcedure(SW_OleProcName, SW_OleParam1);*/		break;
        	}
        }

    if (SW_OleNumParam == 2)
    	{
    	switch (SW_OleType)
    		{
        	case TYPE_APP	:	swApp       .OleProcedure(SW_OleProcName);		break;
        	case TYPE_DOC   :	swModelDoc  .OleProcedure(SW_OleProcName);		break;
        	case TYPE_ASS   :	swAssy      .OleProcedure(SW_OleProcName);		break;
        	case TYPE_DWG   :	/*swApp.OleProcedure(SW_OleProcName);*/		break;
        	}
        }

    }
CATCH_OLE_ERROR;
}
//---------------------------------------------------------------------------
