//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "enum.h"
#include "errors.h"
#include "main.h"
#include "print_file.h"
#include "print_sel.h"
#include "PrintMap.h"
#include "SWutils.h"
#include "utils.h"

#include <printers.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void TfrmPltWorks::GotoFirstDrawing(Variant     swDrawingDoc)
{
// attempt to do the OLE stuff
try
    {
    Variant     swSheet;
    String      sCurrentSheetName, sPreviousSheetName;

    // get the name of the current sheet
    swSheet             = swDrawingDoc.OleFunction("GetCurrentSheet");
    sCurrentSheetName   = swSheet.OleFunction("GetName");

    // try and move to the previous sheet and get its name
    swDrawingDoc.OleFunction("SheetPrevious");
    swSheet             = NULL;
    swSheet             = swDrawingDoc.OleFunction("GetCurrentSheet");

    // if the previous sheet is valid
    if (!swSheet.IsEmpty() && !swSheet.IsNull())
        {
        // get its name
        sPreviousSheetName  = swSheet.OleFunction("GetName");
        }

    // while there are different sheets
    while (sCurrentSheetName != sPreviousSheetName)
        {
        // reset name of current sheet
        sCurrentSheetName  = sPreviousSheetName;
        sPreviousSheetName = "";

        // try and move to the previous sheet and get its name
        swDrawingDoc.OleFunction("SheetPrevious");
        swSheet             = NULL;
        swSheet             = swDrawingDoc.OleFunction("GetCurrentSheet");

        // if the previous sheet is valid
        if (!swSheet.IsEmpty() && !swSheet.IsNull())
            {
            // get its name
            sPreviousSheetName  = swSheet.OleFunction("GetName");
            }
        }
    }// end try block
PW_CATCH_OLE_ERROR;
}
//---------------------------------------------------------------------------
