//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "scale.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RXSpin"
#pragma link "Placemnt"
#pragma link "RxGrdCpt"
#pragma resource "*.dfm"
TfrmScaleWorks *frmScaleWorks;
//---------------------------------------------------------------------------
const long  swDocNONE           = 0;
const long  swDocPART           = 1;
const long  swDocASSEMBLY       = 2;
const long  swDocDRAWING        = 3;

const int   swScaleAboutCentroid            = 0;
const int   swScaleAboutOrigin              = 1;
const int   swScaleAboutCoordinateSystem    = 2;

const String    FmtFloat        = "0.000";
//---------------------------------------------------------------------------
__fastcall TfrmScaleWorks::TfrmScaleWorks(TComponent* Owner)
    : TForm(Owner)
{
    HRESULT                 hr;
    try
        {
        hr = m_DMS_Comm.CoCreateInstance(CLSID_DMS_Common);

        // info for about box
        hr = m_DMS_Comm->set_ProductName(WideString(SCALEWORKS_WORKS_TITLE));
        hr = m_DMS_Comm->set_Commercial(false);
        hr = m_DMS_Comm->set_Icon((long ) Application->Icon->Handle);

        (void ) hr;
       }
    catch (...)
        {
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::ChangeClick(TObject *Sender)
{
    if (!lvSketches->Selected) { return; }

    frmScale->sedScale->Value = atof(lvSketches->Selected->SubItems->Strings[0].c_str());
    if (mrOk == frmScale->ShowModal())
        {
        String      sTempStr;
        lvSketches->Selected->SubItems->Strings[0] = sTempStr.FormatFloat(FmtFloat, frmScale->sedScale->Value);
        lvSketches->Selected->Checked = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::FormCreate(TObject *Sender)
{
    // do the cosmetic titles
    Application->Title = SCALEWORKS_WORKS_TITLE;
    frmScaleWorks->Caption = Application->Title;
    StatusBar->SimpleText = "Welcome to " + SCALEWORKS_WORKS_TITLE;

    btnRefreshClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::btnApplyClick(TObject *Sender)
{
    // make sure SW hasn't died in the meantime
    try
        {
        HRESULT                 hr;
        int                     bIsSWRunning;

        hr = m_DMS_Comm->IsSolidWorksRunning(&bIsSWRunning);

        (void ) hr;

        if (false == bIsSWRunning) { return; }
        }
    catch (...)
        {
        }
    // must have located an already running instance of SW if we get here
    TCursor                 Save_Cursor = Screen->Cursor;

    Variant                 SWApp;
    Variant                 PartDoc;
    long                    DocType;
    String                  SketchName;

    double                  ScaleFactor_X;
    double                  ScaleFactor_Y;
    double                  ScaleFactor_Z;
    BOOL                    bIsUniform;
    int                     ScaleType;

    double                  Scale;
    bool                    Checked;
    bool                    bRetVal;

    // show hourglass cursor, may take a while
    Screen->Cursor = crHourGlass;

    try
        {
        SWApp = CreateOleObject("SldWorks.Application");
        PartDoc = SWApp.OleFunction("ActiveDoc");
        if (PartDoc.IsNull() || PartDoc.IsEmpty()){ return; }

        DocType = PartDoc.OleFunction("GetType");
        if (swDocPART != DocType) { return; }

        // first do the overall model scaling
        if (true == cboScaleModelEnable->Checked)
            {
            ScaleFactor_X = sedScaleModelX->Value;
            ScaleFactor_Y = sedScaleModelY->Value;
            ScaleFactor_Z = sedScaleModelZ->Value;
            bIsUniform = cboScaleUniform->Checked;
            ScaleType = ddlScaleType->ItemIndex;

            StatusBar->SimpleText = "Inserting overall model scale...";
            PartDoc.OleFunction("InsertScale",
                    ScaleFactor_X,
                    ScaleFactor_Y,
                    ScaleFactor_Z,
                    bIsUniform,
                    ScaleType);

            StatusBar->SimpleText = "Rebuilding...";
            PartDoc.OleFunction("ForceRebuild");
            }


        // now scale each sketch
        for (int i = 0; i < lvSketches->Items->Count; i++)
            {
            SketchName = lvSketches->Items->Item[i]->Caption;
            Scale = atof(lvSketches->Items->Item[i]->SubItems[0].Text.c_str());
            Checked = lvSketches->Items->Item[i]->Checked;

            bRetVal = PartDoc.OleFunction("SelectByID", SketchName, "SKETCH", 0, 0, 0);
            if (true == bRetVal && true == Checked)
                {
                StatusBar->SimpleText = "Changing scale on sketch " + SketchName;
                bRetVal = PartDoc.OleFunction("SketchModifyScale", Scale);

                StatusBar->SimpleText = "Rebuilding...";
                PartDoc.OleFunction("ForceRebuild");
                }
            }
        StatusBar->SimpleText = "Finished";
        }
    __finally
        {
        Screen->Cursor = Save_Cursor; // always restore the cursor
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::lvSketchesSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
    Variant                 SWApp;
    Variant                 PartDoc;
    long                    DocType;
    String                  SketchName;
    bool                    bRetVal;

    if (false == Selected) { return; }

    // must have something selected, so safe to enable menu
    mnuChange->Enabled = true;

    // make sure SW hasn't died in the meantime
    try
        {
        HRESULT                 hr;
        int                     bIsSWRunning;

        hr = m_DMS_Comm->IsSolidWorksRunning(&bIsSWRunning);

        (void ) hr;

        if (false == bIsSWRunning) { return; }
        }
    catch (...)
        {
        }
    // must have located an already running instance of SW if we get here

    try
        {
        SWApp = CreateOleObject("SldWorks.Application");
        PartDoc = SWApp.OleFunction("ActiveDoc");
        if (PartDoc.IsNull() || PartDoc.IsEmpty()){ return; }

        DocType = PartDoc.OleFunction("GetType");
        if (swDocPART != DocType) { return; }

        SketchName = lvSketches->Selected->Caption;
        bRetVal = PartDoc.OleFunction("SelectByID", SketchName, "SKETCH", 0, 0, 0);

        (void ) bRetVal;
        }
    catch (...)
        {
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::btnRefreshClick(TObject *Sender)
{
    TCursor                 Save_Cursor = Screen->Cursor;

    Variant                 SWApp;
    Variant                 PartDoc;
    Variant                 Feat;
    Variant                 SubFeat;
    long                    DocType;
    String                  SubFeatTypeName;
    String                  SubFeatName;
    TListItem*              SketchItem;

    // first clear the list & reset overall scale
    lvSketches->Items->BeginUpdate();
    lvSketches->Items->Clear();
    lvSketches->Items->EndUpdate();

    sedScaleModelX->Value = 1.0;
    sedScaleModelY->Value = 1.0;
    sedScaleModelZ->Value = 1.0;

    ddlScaleType  ->ItemIndex = 0;

    cboScaleModelEnable ->Checked = true;
    cboScaleUniform     ->Checked = true;

    // now try to look for SW since we only want to attach to
    // an instance and not start a new one
    try
        {
        HRESULT                 hr;
        int                     bIsSWRunning;

        hr = m_DMS_Comm->IsSolidWorksRunning(&bIsSWRunning);

        (void ) hr;
        
        if (false == bIsSWRunning) { return; }
        }
    catch (...)
        {
        }
    // must have located an already running instance of SW if we get here

    // show hourglass cursor, may take a while
    Screen->Cursor = crHourGlass;

    // see SW API "Get Sketches Example"
    try
        {
        // connect to SW
        SWApp = CreateOleObject("SldWorks.Application");

        PartDoc = SWApp.OleFunction("ActiveDoc");
        if (PartDoc.IsNull() || PartDoc.IsEmpty()){ goto CLEANUP; }

        DocType = PartDoc.OleFunction("GetType");
        if (swDocPART != DocType) { goto CLEANUP; }

        Feat = PartDoc.OleFunction("FirstFeature");
        while (!Feat.IsNull() && !Feat.IsEmpty())
            {
            SubFeat = Feat.OleFunction("GetFirstSubFeature");
            while (!SubFeat.IsNull() && !SubFeat.IsEmpty())
                {
                SubFeatTypeName = SubFeat.OleFunction("GetTypeName");
                if (SubFeatTypeName == "ProfileFeature")
                    {
                    SubFeatName = SubFeat.OlePropertyGet("Name");
                    SketchItem = lvSketches->Items->Insert(lvSketches->Items->Count);
                    SketchItem->Caption = SubFeatName;
                    SketchItem->SubItems->Add("1.00");
                    }
                SubFeat = SubFeat.OleFunction("GetNextSubFeature");
                }
            Feat = Feat.OleFunction("GetNextFeature");
            }
        }
    __finally
        {
        Screen->Cursor = Save_Cursor; // always restore the cursor
        }
    CLEANUP :
        ;
    Screen->Cursor = Save_Cursor; // always restore the cursor
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::cboScaleModelEnableClick(TObject *Sender)
{
    bool        bEnabled = cboScaleModelEnable->Checked;

    cboScaleUniform     ->Enabled = bEnabled;
    
    sedScaleModelX      ->Enabled = bEnabled;
    sedScaleModelY      ->Enabled = bEnabled;
    sedScaleModelZ      ->Enabled = bEnabled;

    ddlScaleType        ->Enabled = bEnabled;
    
    cboScaleUniformClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::cboScaleUniformClick(TObject *Sender)
{
    bool        bEnabled = cboScaleModelEnable->Checked;
    bool        bUniform = cboScaleUniform->Checked;

    sedScaleModelY->Enabled = !bUniform && bEnabled;
    sedScaleModelZ->Enabled = !bUniform && bEnabled;
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::mnuExitClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::mnuContentsClick(TObject *Sender)
{
    WinExec(
        AnsiString::AnsiString(
            AnsiString::AnsiString("winhlp32 ") +
            Application->HelpFile).c_str(),
            SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmScaleWorks::mnuAboutClick(TObject *Sender)
{
    try
        {
        HRESULT                         hr;

        hr = m_DMS_Comm->About();

        (void ) hr;
        }
    catch (...)
        {
        }
}
//---------------------------------------------------------------------------

