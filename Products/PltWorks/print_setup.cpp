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
void TfrmPltWorks::SetupPrinter(
                        Variant     swApp,
                        Variant     swDrawingDoc,
                        Variant     swSheet,
                        double      *nPrintScale)
/*
    nPrintScale
        the scale, in decimal form.   In other words, to print the document
        at 50% you should pass 0.5, to print at 200% you should pass 2.0.
        If you pass 0.0, the your print will be scaled to fit the page.
*/
{
try
    {
    long        nPaperSize  = -1;
    double      nScaleNum,              // scale numerator
                nScaleDenom,            // scale denominator
                nWidth      =  0,
                nHeight     =  0;
    bool        bLandscape = true;

    Variant     vSheetProps(swSheet.OleFunction("GetProperties"));

    // get all the information for the current sheet
    nPaperSize  = (long ) vSheetProps.GetElement(0).AsType(varDouble);
    nScaleNum   =         vSheetProps.GetElement(2).AsType(varDouble);
    nScaleDenom =         vSheetProps.GetElement(3).AsType(varDouble);
    nWidth      =         vSheetProps.GetElement(5).AsType(varDouble);
    nHeight     =         vSheetProps.GetElement(6).AsType(varDouble);

    // calculate scale from numerator and denominator
    *nPrintScale = nScaleNum / nScaleDenom;

    // we're in landscape mode if it's wider than it is taller
    bLandscape = (nWidth > nHeight);

    switch (nPaperSize)
        {
        case    swDwgPaperAsize              :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPSLetter   );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlA_Landscape->Items->Strings[frmPrintMap->ddlA_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboA_Landscape->Checked ? 0 : frmPrintMap->fleA_Landscape->Value;
            break;

        case    swDwgPaperAsizeVertical      :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPSLetter   );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORPortrait );

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlA_Portrait->Items->Strings[frmPrintMap->ddlA_Portrait->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboA_Portrait->Checked ? 0 : frmPrintMap->fleA_Portrait->Value;
            break;

        case    swDwgPaperBsize              :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPS11x17    );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlB_Landscape->Items->Strings[frmPrintMap->ddlB_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboB_Landscape->Checked ? 0 : frmPrintMap->fleB_Landscape->Value;
            break;

        case    swDwgPaperCsize              :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPS11x17    );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlC_Landscape->Items->Strings[frmPrintMap->ddlC_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboC_Landscape->Checked ? 0 : frmPrintMap->fleC_Landscape->Value;
            break;

        case    swDwgPaperDsize              :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPS11x17    );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlD_Landscape->Items->Strings[frmPrintMap->ddlD_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboD_Landscape->Checked ? 0 : frmPrintMap->fleD_Landscape->Value;
            break;

        case    swDwgPaperEsize              :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPS11x17    );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlE_Landscape->Items->Strings[frmPrintMap->ddlE_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboE_Landscape->Checked ? 0 : frmPrintMap->fleE_Landscape->Value;
            break;

        case    swDwgPaperA4size             :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPSA4       );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlA4_Landscape->Items->Strings[frmPrintMap->ddlA4_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboA4_Landscape->Checked ? 0 : frmPrintMap->fleA4_Landscape->Value;
            break;

        case    swDwgPaperA4sizeVertical     :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPSA4       );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORPortrait );

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlA4_Portrait->Items->Strings[frmPrintMap->ddlA4_Portrait->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboA4_Portrait->Checked ? 0 : frmPrintMap->fleA4_Portrait->Value;
            break;

        case    swDwgPaperA3size             :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPSA3       );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlA3_Landscape->Items->Strings[frmPrintMap->ddlA3_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboA3_Landscape->Checked ? 0 : frmPrintMap->fleA3_Landscape->Value;
            break;

        case    swDwgPaperA2size             :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPS11x17    );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlA2_Landscape->Items->Strings[frmPrintMap->ddlA2_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboA2_Landscape->Checked ? 0 : frmPrintMap->fleA2_Landscape->Value;
            break;

        case    swDwgPaperA1size             :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPS11x17    );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlA1_Landscape->Items->Strings[frmPrintMap->ddlA1_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboA1_Landscape->Checked ? 0 : frmPrintMap->fleA1_Landscape->Value;
            break;

        case    swDwgPaperA0size             :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPS11x17    );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlA0_Landscape->Items->Strings[frmPrintMap->ddlA0_Landscape->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboA0_Landscape->Checked ? 0 : frmPrintMap->fleA0_Landscape->Value;
            break;

        case    swDwgPapersUserDefined       :
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintPaperSize  , vbPRPSUser     );
            swDrawingDoc.OleFunction("PrintSetup"   , swPrintOrientation, vbPRORLandscape);

            swApp.OleFunction("ActivePrinter",
                            frmPrintMap->ddlOther->Items->Strings[frmPrintMap->ddlOther->ItemIndex]);
            *nPrintScale =  frmPrintMap->cboOther->Checked ? 0 : frmPrintMap->fleOther->Value;
            break;

        default :
            break;
        }
    }// end try block
PW_CATCH_OLE_ERROR;
}
//---------------------------------------------------------------------------
