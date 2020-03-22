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
void TfrmPltWorks::PrintDrawingFile(
                        Variant     swApp,
                        Variant     swDrawingDoc)
{
// attempt to do the OLE stuff
try
    {
    GotoFirstDrawing(swDrawingDoc);

    Variant     swSheet;
    String      sCurrentSheetName, sPreviousSheetName;
    int         nPageNumber = 0,
                nNumCopies  = 1;
    double      nPrintScale;

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
        // configure & select printer for this sheet
        // and get the scale (for this sheet)
        SetupPrinter(swApp, swDrawingDoc, swSheet, &nPrintScale);

        // set page range to be the current page
        nPageNumber++;

        // now print it out to the current SW printer
        swDrawingDoc.OleFunction("PrintOut2", nPageNumber, nPageNumber,
            nNumCopies, false, NULL, nPrintScale, false, "");

        // reset name of current sheet
        sCurrentSheetName  = sPreviousSheetName;
        sPreviousSheetName = "";

        // try and move to the next sheet and get its name
        swDrawingDoc.OleFunction("SheetNext");
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
