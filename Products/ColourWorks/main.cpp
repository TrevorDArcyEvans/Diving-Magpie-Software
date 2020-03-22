//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "Placemnt"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
// SolidWorks constants
const long          swDocNONE       = 0;
const long          swDocPART       = 1;
const long          swDocASSEMBLY   = 2;
const long          swDocDRAWING    = 3;

// assumes 8 bpp = 24 bit colour
// 0x100 = 256
const long          MAX_BPP         = 0x100;

const int           MAX_TRIES = 6;

#define    WM_AVS_ABOUT     3500
#define    WM_AVS_SPACE     3501

//---------------------------------------------------------------------------
template <class T> T Square(T value)
{
    return value * value;
}
//---------------------------------------------------------------------------
// TfrmMain::rand
// random number generator to return a double value from zero to a maximum value
//
// parameters
//      num
//          maximum value possible to return
//
// returns
//      double
//          random (continuous) number in the range 0 to +num
//
// see also
//      random() in <stdlib.h>
double TfrmMain::rand(double num)
{
    // note lots of casts otherwise gets converted to int
    double          nRetVal = (double ) num * ((double ) (random(RAND_MAX) + 1.0) / (double ) RAND_MAX);

    assert(nRetVal <= RAND_MAX);

    return nRetVal;
}
//---------------------------------------------------------------------------
// TfrmMain::IsTooClose
// determines if two colours are with a specified distance in the 'colour cube'
//
// parameters
//      Red1
//      Green1
//      Blue1
//          RBG values of Colour1
//
//      Red2
//      Green2
//      Blue2
//          RBG values of Colour2
//
//      Tolerance
//          minimum allowable colour distance between Colour1 and Colour2
//
// returns
//      true
//          if Colour1 is within the specified distance of Colour2
//
//      false
//          both colours are more than the specified distance apart
//
// notes
//      does not assume any restrictions on the ranges of Colour1 or Colour2
//      or the distance
//
//      very simplistic concept of 'distance' as no account is taken of the
//      human eye's sensitivity to different colours
bool TfrmMain::IsTooClose
(
    double          Red_1,
    double          Green_1,
    double          Blue_1,
    double          Red_2,
    double          Green_2,
    double          Blue_2,
    double          Tolerance
)
{
    double          DistanceSqared;

    DistanceSqared = Square(Red_1 - Red_2) + Square(Green_1 - Green_2) + Square(Blue_1 - Blue_2);

    return Square(Tolerance) > DistanceSqared;
}
//---------------------------------------------------------------------------
// TfrmMain::IsNotClose
//
// see also
//      TfrmMain::IsTooClose
bool TfrmMain::IsNotClose
(
    double          Red_1,
    double          Green_1,
    double          Blue_1,
    double          Red_2,
    double          Green_2,
    double          Blue_2,
    double          Tolerance
)
{
    return !IsTooClose(Red_1, Green_1, Blue_1, Red_2, Green_2, Blue_2,Tolerance);
}
//---------------------------------------------------------------------------
// TfrmMain::GetNewColour
// parameters
//      ColourSet
//          set of colours for which the new colour must not conflict with
//
//          on successful selection of a new colour, the new colour is *not*
//          added to this set
//
//      NewRed
//      NewGreen
//      NewBlue
//          RBG values of new colour
//
//      Tolerance
//          minimum allowable colour distance between new colour and all
//          colours in the colour set
//
//      MaxColourValue
//          max value of one component of the RBG colour ie bits per pixel
//
//      Attempts
//          number of times to try for a non-conflicting colour before giving up
//
// returns
//      true
//          if new colour was found
//
//          NewRed etc contain new RBG values
//
//      false
//          if new colour not found
//
//          NewRed etc contain RBG values which probably conflict with entries
//          in the colour set 
//
// notes
//      does not assume any restrictions on the ranges of colour or the distance
//
//      caller to add new colour to set
bool TfrmMain::GetNewColour
(
    std::set <COLORREF>         ColourSet,
    double&                     NewRed,
    double&                     NewGreen,
    double&                     NewBlue,
    double                      Tolerance,
    double                      MaxColourValue,
    int                         Attempts
)
{
    int                                 i  = 0;
    std::set <COLORREF> :: iterator     It;
    bool                                bFoundColour;

    for (i = 0; i < Attempts; i++)
        {
        // reset flag
        bFoundColour = true;

        // move to a random position in the colour cube
        NewRed      = rand(MaxColourValue);
        NewGreen    = rand(MaxColourValue);
        NewBlue     = rand(MaxColourValue);

        // see if there's a conflict with what we already have
        for (It = ColourSet.begin(); It != ColourSet.end(); It++)
            {
            double          SetRed      = GetRValue(*It);
            double          SetGreen    = GetGValue(*It);
            double          SetBlue     = GetBValue(*It);

            bFoundColour &= IsNotClose(
                                SetRed, SetGreen, SetBlue,
                                NewRed, NewGreen, NewBlue,
                                Tolerance);
            if (false == bFoundColour)
                {
                // conflicts with existing colour, so try another colour
                break;
                }
            }

        if (true == bFoundColour)
            {
            // found a new colour, so can return
            break;
            }
        }

    // make sure we're within the allowable range
    assert(NewRed   <= MaxColourValue);
    assert(NewGreen <= MaxColourValue);
    assert(NewBlue  <= MaxColourValue);

    assert(NewRed   >= 0);
    assert(NewGreen >= 0);
    assert(NewBlue  >= 0);

    return bFoundColour;
}
//---------------------------------------------------------------------------
// TfrmMain::GetSolidWorksColorTable
// connects to an laready running instance of SolidWorks and adds all the
// entries from the SolidWorks colour table to the specified set
//
// parameters
//      ColourSet
//          set to which to add all the SolidWorks colour table entries
//
// notes
//      set is not cleared before adding SolidWorks entries - beware!
void TfrmMain::GetSolidWorksColorTable
(
    std::set <COLORREF>&            ColourSet
)
{
    TCursor                         Save_Cursor = Screen->Cursor;

    // show hourglass cursor, may take a while
    Screen->Cursor = crHourGlass;

    try
        {
        Variant                         SWApp;
        Variant                         AsmDoc;
        Variant                         ColourTable;
        long                            DocType = -1;
        long                            Count = 0;
        long                            ColourRef;
        long                            i;

        // connect to SW and get all the info
        SWApp = GetActiveOleObject("SldWorks.Application");
        if (SWApp.IsNull() || SWApp.IsEmpty()){ return; }

        AsmDoc = SWApp.OleFunction("ActiveDoc");
        if (AsmDoc.IsNull() || AsmDoc.IsEmpty()){ return; }

        // we only deal with assemblies
        DocType = AsmDoc.OleFunction("GetType");
        if (swDocASSEMBLY != DocType){ return; }

        ColourTable = AsmDoc.OleFunction("GetColorTable");
        Count       = ColourTable.OleFunction("GetCount");

        // colours
        for (i = 0; i < Count; i++)
            {
	        ColourRef  = ColourTable.OleFunction("GetColorRefAtIndex", i);

            ColourSet.insert(ColourRef);
            }
        }
    catch (EOleSysError &e)
        {
        // SolidWorks probably not started, so tell user
        Application->MessageBox(
            ::String(::String("Could not connect to SolidWorks.\n") +
                e.Message).c_str(),
                "Error!",
            MB_OK | MB_ICONERROR);
        }
    catch (...)
        {
        Application->MessageBox(
            ::String("C++ Exception.").c_str(),
            ::String("Error!").c_str(),
            MB_OK | MB_ICONERROR);
        }

    Screen->Cursor = Save_Cursor; // always restore the cursor
}
//---------------------------------------------------------------------------
// TfrmMain::ChangePartColor
// changes specified SolidWorks part to a colour which does not conflict with
// any colours in the specified set.  If the colour is changed, it is added
// to the specified set.
//
// parameters
//      PartDoc
//          SolidWorks part for which to change colour
//
//      ColourSet
//          set of colours for which the new colour must not conflict with
//
//          on successful selection of a new colour, the new colour is
//          added to this set
//
//      Tolerance
//          minimum colour distance the new part colour should be from all
//          other SolidWorks colour table entries and other part colours
//
//          this must be in the range (0, MAX_BPP]
//
// returns
//      true
//          if colour successfully changed for this part and colour set updated
//
//      false
//          colour could not be changed and colour set not updated
bool TfrmMain::ChangePartColor
(
    Variant                     PartDoc,
    std::set <COLORREF>&        ColourSet,
    double                      Tolerance
)
{
    assert(Tolerance <= MAX_BPP);
    assert(Tolerance >  0      );

    TCursor                     Save_Cursor = Screen->Cursor;

    // show hourglass cursor, may take a while
    Screen->Cursor = crHourGlass;

    bool                        bRetVal = true;

    try
        {
        HRESULT                         hr;

        AnsiString                      Text;

        VARIANT                         vMatPropsArray;
        double*                         MatData;
        SAFEARRAY*                      psa;

        double                          Col_R, Col_G, Col_B,
                                        Ambient, Diffuse, Specular,
                                        Shininess, Transparency, Emission;

        double                          NewCol_R, NewCol_G, NewCol_B;

        // for debugging only
        Text = PartDoc.OleFunction("GetPathName");

        // get all the material properties
        vMatPropsArray = PartDoc.OlePropertyGet("MaterialPropertyValues");
        psa =  V_ARRAY(&vMatPropsArray);

        // access the SafeArray data
        hr = SafeArrayAccessData(psa, (void **)&MatData);
        if (S_OK != hr) { goto CLEAN_UP; }

        // use these values for debugging
        Col_R           = MatData[0] * MAX_BPP;
        Col_G           = MatData[1] * MAX_BPP;
        Col_B           = MatData[2] * MAX_BPP;

        Ambient         = MatData[3];
        Diffuse         = MatData[4];
        Specular        = MatData[5];
        Shininess       = MatData[6];
        Transparency    = MatData[7];
        Emission        = MatData[8];

        // casts to shutup compiler
        (void ) Col_R           ;
        (void ) Col_G           ;
        (void ) Col_B           ;

        (void ) Ambient         ;
        (void ) Diffuse         ;
        (void ) Specular        ;
        (void ) Shininess       ;
        (void ) Transparency    ;
        (void ) Emission        ;

        bRetVal &= GetNewColour(
                        ColourSet,
                        NewCol_R, NewCol_G, NewCol_B,
                        Tolerance,
                        MAX_BPP,
                        MAX_TRIES);

        if (true == bRetVal)
            {
            MatData[0] = NewCol_R / MAX_BPP;
            MatData[1] = NewCol_G / MAX_BPP;
            MatData[2] = NewCol_B / MAX_BPP;

            PartDoc.OlePropertySet("MaterialPropertyValues", psa);

            ColourSet.insert(RGB(NewCol_R , NewCol_G, NewCol_B));
            }

        // Unaccess and Destroy the SafeArray
        hr = SafeArrayUnaccessData(psa);
        hr = SafeArrayDestroy(psa);
        }
    catch (...)
        {
        Application->MessageBox(
            ::String("C++ Exception.").c_str(),
            ::String("Error!").c_str(),
            MB_OK | MB_ICONERROR);

        bRetVal = false;
        }

    CLEAN_UP :
        ;

    Screen->Cursor = Save_Cursor; // always restore the cursor

    return bRetVal;
}
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
    HRESULT                 hr;
    try
        {
        hr = m_DMS_Comm.CoCreateInstance(CLSID_DMS_Common);

        // info for about box
        hr = m_DMS_Comm->set_ProductName(WideString(COLORWORKS_WORKS_TITLE));
        hr = m_DMS_Comm->set_Commercial(false);
        hr = m_DMS_Comm->set_Icon((long ) Application->Icon->Handle);

        (void ) hr;
       }
    catch (...)
        {
        Application->MessageBox(
            ::String("C++ Exception.").c_str(),
            ::String("Error!").c_str(),
            MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::WndProc(Messages::TMessage &Message)
{
    // respond to About menu click
    if ((Message.Msg    == WM_SYSCOMMAND) &&
        (Message.WParam == WM_AVS_ABOUT ) )
        {
        try
            {
            HRESULT                         hr;

            hr = m_DMS_Comm->About();

            (void ) hr;
            }
        catch (...)
            {
            Application->MessageBox(
                ::String("C++ Exception.").c_str(),
                ::String("Error!").c_str(),
                MB_OK | MB_ICONERROR);
            }

        Message.Result = true;
        }
    else
        {
        TForm::WndProc(Message);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    // add About menu
    HMENU           hsysmenu = GetSystemMenu(WindowHandle,FALSE);
    if (hsysmenu != NULL)
        {
        AppendMenu(hsysmenu, MF_SEPARATOR, WM_AVS_SPACE, ""         );
        AppendMenu(hsysmenu, MF_STRING   , WM_AVS_ABOUT, "&About...");
        }

    m_Colours.clear();

    // do the cosmetic titles
    Application->Title = COLORWORKS_WORKS_TITLE;
    frmMain->Caption = Application->Title;
}
//---------------------------------------------------------------------------
// TfrmMain::TraverseComponent
// recursively called routine to walk over assembly tree and, for each part,
// change its colour to a value which does not conflict with any SolidWorks
// colour table value, or any other part.  If a part's colour is changed,
// then this new colour is added to the set of colours.
//
// parameters
//      level
//          used to track level of recursion
//
//      Component
//          SolidWorks 'component' ie a part of an assembly, could be an
//          assembly or a part
//
//      ColourSet
//          set of colours for which the new colour must not conflict with
//
//          on successful selection of a new colour, the new colour is
//          added to this set
//
//      Tolerance
//          minimum allowable colour distance between new colour and all
//          colours in the colour set
//
// see also
//      TfrmMain::ChangePartColor()
void TfrmMain::TraverseComponent
(
    int                         level       ,
    Variant                     Component   ,
    std::set <COLORREF>&        ColourSet   ,
    double                      Tolerance
)
{
    // attempt to do the OLE stuff
    try
        {
        HRESULT                         hr;

        AnsiString                      Text;
        Variant                         Children, Child;
        Variant                         PartDoc;
        long                            i, nChildCount;
        SAFEARRAY                       *psa;

        //Perform component specific operations...

        // for debugging only
        Text = Component.OleFunction("Name");

        //Traverse the children
        Children = Component.OleFunction("GetChildren");    //Get the list of children

        // Get the # of elements in the variant safearray. UBound returns the
        // upper element number.  Since the array begins at zero, we must add 1
        // to get the actual number of array elements.  If no elements are
        // in the array, then UBound returns -1.

        psa = V_ARRAY(&Children);
        hr = SafeArrayGetUBound(psa, 1, &nChildCount);

        if (-1 == nChildCount)
            {
            // no children, so must be a part
            PartDoc = Component.OleFunction("GetModelDoc");

            // so change part colour
            // note will add new colour to set here
            ChangePartColor(PartDoc, ColourSet, Tolerance);
            }

        //For each Child in this subassembly
        for(i = 0; i <= nChildCount; i++)
            {
            Child = Children.GetElement(i);
            if (!Child.IsNull() && !Child.IsEmpty())
                {
                //Traverse the child's components
                TraverseComponent(level + 1, Child, ColourSet, Tolerance);
                }
            }

        // Unaccess and Destroy the SafeArray
        hr = SafeArrayUnaccessData(psa);
        hr = SafeArrayDestroy(psa);

        (void ) hr;
        }
    catch(EOleException& e)
        {
        Application->MessageBox(
            ::String("C++ Exception.").c_str(),
            ::String("Error!").c_str(),
            MB_OK | MB_ICONERROR);
        }
    catch(EOleSysError& e)
        {
        // SolidWorks probably not started, so tell user
        Application->MessageBox(
            ::String(::String("Could not connect to SolidWorks.\n") +
                e.Message).c_str(),
                "Error!",
            MB_OK | MB_ICONERROR);
        }
    catch(EOleError& e)
        {
        Application->MessageBox(
            ::String(::String("OLE Error.\n") +
                e.Message).c_str(),
                "Error!",
            MB_OK | MB_ICONERROR);
        }
    catch(...)
        {
        Application->MessageBox(
            ::String("C++ Exception.").c_str(),
            ::String("Error!").c_str(),
            MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnApplyClick(TObject *Sender)
{
    TCursor                         Save_Cursor = Screen->Cursor;

    // show hourglass cursor, may take a while
    Screen->Cursor = crHourGlass;

    try
        {
        double                          Tolerance = sedTolerance->Value;

        Variant                         SWApp;
        Variant                         AsmDoc;
        Variant                         Configuration;
        Variant                         RootComponent;
        Variant                         PartDoc;
        long                            DocType = -1;
        long                            i;

        // connect to SW and get all the info
        SWApp = GetActiveOleObject("SldWorks.Application");
        if (SWApp.IsNull() || SWApp.IsEmpty()){ goto CLEAN_UP; }

        AsmDoc = SWApp.OleFunction("ActiveDoc");
        if (AsmDoc.IsNull() || AsmDoc.IsEmpty()){ goto CLEAN_UP; }

        // we only deal with assemblies
        DocType = AsmDoc.OleFunction("GetType");
        if (swDocASSEMBLY != DocType){ goto CLEAN_UP; }

        // refresh system colour table
        m_Colours.clear();
        GetSolidWorksColorTable(m_Colours);

        // start walking the assembly tree
        Configuration = AsmDoc.OleFunction("GetActiveConfiguration");

        // start at the root
        RootComponent = Configuration.OleFunction("GetRootComponent");
        if (!RootComponent.IsNull() && !RootComponent.IsEmpty())
            {
            // and recurse our way through
            TraverseComponent(1, RootComponent, m_Colours, Tolerance);

            // force redraw so user can see the results
            AsmDoc.OleFunction("GraphicsRedraw2");
            }
        }
    catch (EOleSysError &e)
        {
        // SolidWorks probably not started, so tell user
        Application->MessageBox(
            ::String(::String("Could not connect to SolidWorks.\n") +
                e.Message).c_str(),
                "Error!",
            MB_OK | MB_ICONERROR);
        }
    catch (...)
        {
        Application->MessageBox(
            ::String("C++ Exception.").c_str(),
            ::String("Error!").c_str(),
            MB_OK | MB_ICONERROR);
        }

    CLEAN_UP :
        ;

    Screen->Cursor = Save_Cursor; // always restore the cursor
}
//---------------------------------------------------------------------------

