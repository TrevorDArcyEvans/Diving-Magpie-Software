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
void TfrmPltWorks::OpenFile(
                        Variant     swApp,
                        String      FileName,
                        bool        *bFileLoadedOK,
                        bool        *bErrorsPrinting)
{
long            Errors;
int             statloc,
                swFileType = GetType(FileName);

PW_LOG_ERROR("Opening " + FileName);
swApp.OleFunction("OpenDocSilent", FileName, swFileType, &Errors);
wait(&statloc);

if (swFileNotFoundError == (swFileNotFoundError & Errors))
    {
    PW_LOG_ERROR("Unable to locate " + FileName);
    *bErrorsPrinting = true;
    *bFileLoadedOK   = false;
    }

if (swIdMatchError == (swIdMatchError & Errors))
    {
    PW_LOG_ERROR("The internal ID of document " + FileName +
        " does not match the internal ID saved with the referencing document.");
    *bErrorsPrinting = true;
    *bFileLoadedOK   = true;
    }

if (swBasePartNotLoadedWarn == (swBasePartNotLoadedWarn & Errors))
    {
    PW_LOG_ERROR(FileName +
        "  has an external reference which is not open so changes will not be " +
        "propagated to the file.");
    *bErrorsPrinting = true;
    *bFileLoadedOK   = true;
    }

if (swNeedsRegenWarn == (swNeedsRegenWarn & Errors))
    {
    PW_LOG_ERROR(FileName + " or " + FileName + " reference needs to be rebuilt.");
    *bErrorsPrinting = true;
    *bFileLoadedOK   = true;
    }

if (swSheetScaleUpdateWarn == (swSheetScaleUpdateWarn & Errors))
    {
    PW_LOG_ERROR("Sheet scales have not been applied to drawing sketch entities in "
        + FileName + ".");
    *bErrorsPrinting = true;
    *bFileLoadedOK   = true;
    }

if (swDrawingANSIUpdateWarn == (swDrawingANSIUpdateWarn & Errors))
    {
    PW_LOG_ERROR("Geometric Tolerance symbol update to conform to ANSI/ISO "
        "standards have not been made to the drawing file " + FileName);
    *bErrorsPrinting = true;
    *bFileLoadedOK   = true;
    }

if (swSharingViolationWarn == (swSharingViolationWarn & Errors))
    {
    PW_LOG_ERROR("The " + FileName + " is being used by another user.");
    *bErrorsPrinting = true;
    *bFileLoadedOK   = true;
    }

if (swReadOnlyWarn == (swReadOnlyWarn & Errors))
    {
    PW_LOG_ERROR("The " + FileName + " file is not available for write access.");
    *bErrorsPrinting = true;
    *bFileLoadedOK   = true;
    }

if (swGenericError == (swGenericError & Errors))
    {
    PW_LOG_ERROR("Another error was encountered.");
    *bErrorsPrinting = true;
    *bFileLoadedOK   = false;
    }

if (0 == Errors)
    {
    //The file was loaded successfully.
    PW_LOG_ERROR("Successfully opened " + FileName);
    *bFileLoadedOK = true;
    }
}
//---------------------------------------------------------------------------

