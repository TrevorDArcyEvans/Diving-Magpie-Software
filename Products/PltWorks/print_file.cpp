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
void TfrmPltWorks::PrintFiles(void)
{
int             i = 0, statloc;
long            swFileType = 0;
bool            bFileLoadedOK   = false,
                bErrorsPrinting = false;
AnsiString      FileName;
Variant         swApp, swModelDoc;

// attempt to do the OLE stuff
try
    {
    if (0 == lbxList->Items->Count)
        {
        return;
        }

    // clear error log
    frmError->memError->Lines->Clear();

    // set flag for having started SW & printing
    m_bPrinted = true;

    // first attach to an instance of SolidWorks
    PW_LOG_ERROR("Connecting to SolidWorks...");
    swApp = CreateOleObject("SldWorks.Application");
    wait(&statloc);

    // have to set UserControl to true to acknowledge printer problems
    swApp.OleFunction("UserControl", true);
    wait(&statloc);

    swApp.OleFunction("Visible", false);
    wait(&statloc);

    // for each file in the list
    for (i = 0; i < lbxList->Items->Count; i++)
        {
        if (i > MAX_DOC && false == m_bRegistered) break;

        FileName = lbxList->Items->Strings[i].LowerCase();

        // first determine if we have a SW file because the list
        // may have been loaded from disk
        if (false == IsSolidWorksFile(FileName))
            {
            // if this isn't a SW file, then we skip it
            continue;
            }

        // open the file
        OpenFile(swApp, FileName, &bFileLoadedOK, &bErrorsPrinting);

        // skip if we haven't successfully loaded this file
        if (true != bFileLoadedOK)
            {
            continue;
            }

        // activate the file
        PW_LOG_ERROR("Activating " + FileName);
        swModelDoc  = swApp.OleFunction("ActivateDoc", FileName);
        wait(&statloc);

        PW_LOG_ERROR("Printing " + FileName);

        // then find out the file type
        swFileType = swModelDoc.OleFunction("GetType");

        switch (swFileType)
            {
            default :
            case    swDocPART       :
            case    swDocASSEMBLY   :
                // set print options for models (parts & assys)
                // isometric view
                if (true == chkIsometric->Checked)
                    {
                    swModelDoc.OleFunction("ShowNamedView", "*Isometric");
                    wait(&statloc);
                    }

                // hidden lines visible
                if (true == rdoHiddenVisible->Checked)
                    {
                    PW_LOG_ERROR("Applying hidden lines from " + FileName);
                    swModelDoc.OleFunction("ViewDisplayWireframe");
                    wait(&statloc);
                    }

                // hidden lines grayed
                if (true == rdoHiddenGrayed->Checked)
                    {
                    PW_LOG_ERROR("Graying hidden lines from " + FileName);
                    swModelDoc.OleFunction("ViewDisplayHiddengreyed");
                    wait(&statloc);
                    }

                // hidden lines removed
                if (true == rdoHiddenRemoved->Checked)
                    {
                    PW_LOG_ERROR("Removing hidden lines from " + FileName);
                    swModelDoc.OleFunction("ViewDisplayHiddenRemoved");
                    wait(&statloc);
                    }

                // shaded
                if (true == rdoShaded->Checked)
                    {
                    PW_LOG_ERROR("Shading " + FileName);
                    swModelDoc.OleFunction("ViewDisplayShaded");
                    wait(&statloc);
                    }

                // zoom to fit
                if (true == chkZoomFit->Checked)
                    {
                    PW_LOG_ERROR("Zooming to fit " + FileName);
                    swModelDoc.OleFunction("ViewZoomtofit");
                    wait(&statloc);
                    }

                // print preview
                // note can print from preview...
                if (true == chkPreview->Checked)
                    {
                    PW_LOG_ERROR("Previewing " + FileName);
                    swModelDoc.OleFunction("PrintPreview");
                    wait(&statloc);
                    }

                // set SW printer to the selected printer
                swApp.OleFunction("ActivePrinter",
                    frmPrinters->ddlPrinters->Items->Strings[m_nCurrentPrinter]);

                // finally, we get to print the file
                swModelDoc.OleFunction("PrintDirect");
                wait(&statloc);
                break;


            case    swDocDrawing    :
                PrintDrawingFile(swApp, swModelDoc);
                wait(&statloc);
                break;
            }

        // ugly hack to allow time for grandchild process (printing)
        // to finish
        Sleep(SW_PAUSE);

        // close file without saving
        PW_LOG_ERROR("Closing " + FileName);
        swApp.OleFunction("QuitDoc", FileName);
        wait(&statloc);
        }// end for each file loop
    }// end try block
PW_CATCH_OLE_ERROR;

if (true == bErrorsPrinting)
    {
    if (IDYES == Application->MessageBox("There were errors printing.\nWould you like to view these errors now?",
        frmPltWorks->Caption.c_str(), MB_YESNO))
        {
        frmError->ShowModal();
        }
    }
}
//---------------------------------------------------------------------------

