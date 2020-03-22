#include "lupch.h"
#pragma hdrstop
#include <math.h>
#include <stdlib.h>

#include "about.h"
#include "config.h"
#include "main.h"
#include "preview.h"
#include "saver.h"
#include "SWutils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XVIEW3DLib_OCX"
#pragma resource "*.dfm"
TSaverForm *SaverForm;
//---------------------------------------------------------------------------
__fastcall TSaverForm::TSaverForm(TComponent* Owner) : TScrForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSaverForm::FormShow(TObject *Sender)
{
actXView->BackgroundColor = clBlack;
actXView->RGBBackgroundColor = 0;

actXView->MenuEnable(False);

actXView->Height = Screen->Height - 115;

actXView->ViewSetVuvDir(actXView->GetFirstViewport(), 1.0, 1.0, 1.0);

if (g_strsFileList->Count > 0)
    {
    LoadSWFile(g_strsFileList->Strings[0]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSaverForm::LoadSWFile(String   strFileName)
{
if ((true == FileExists         (strFileName)) &&
    (true == IsSolidWorksFile   (strFileName)) )
    {
    actXView->SceneNew();
    actXView->SceneImportModel(::WideString(strFileName.c_str()).c_bstr());

    float       X = actXView->SceneCenterX + actXView->SceneExtensionX,
                Y = actXView->SceneCenterY + actXView->SceneExtensionY,
                Z = actXView->SceneCenterZ + actXView->SceneExtensionZ;

    g_Radius = 1.2 * sqrt(X*X + Y*Y + Z*Z);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSaverForm::FormCreate(TObject *Sender)
{
MainForm->MainFormCreate(Sender);

actXView->setPassword(::WideString("SolidPartnerScreenSaver").c_bstr());

String      strFileFilter;
if (true == g_bIsSolidPartners)
    {
    // ScreenWorks file filter =
    //      SolidWorks part and assy files only
    //      ignore drawing files
    strFileFilter = "*.*prt|*.*asm";
    }
else
    {
    // Actify file filter
    strFileFilter = MainForm->regVar->ReadString("VAR", "filter");
    }

// dynamically create global file list
g_strsFileList = new TStringList;

// scan in list of files
char        cCurrDir[MAX_PATH];
GetCurrentDirectory(sizeof(cCurrDir) / sizeof(char), cCurrDir);

SetCurrentDirectory(MainForm->SW_DirName->Value.c_str());

g_strsFileList->Clear();

int         Posn = 0;

while ((Posn = strFileFilter.Pos("|")) > 0)
    {
    ProcessDirectory(MainForm->SubDir->Value, strFileFilter.SubString(1, Posn - 1));
    strFileFilter.Delete(1, Posn);
    }

if (!strFileFilter.IsEmpty())
    {
    ProcessDirectory(MainForm->SubDir->Value, strFileFilter);
    }

SetCurrentDirectory(cCurrDir);

// set default values for scrolling text etc
Canvas->Brush->Color = clBlack;
Canvas->Font->Color = clWhite;
Canvas->Font->Height = 24;
}
//---------------------------------------------------------------------------
void __fastcall TSaverForm::FormDestroy(TObject *Sender)
{
// destroy dynamically created global file list
delete g_strsFileList;
actXView->SceneDelete();
}
//---------------------------------------------------------------------------
void __fastcall TSaverForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TSaverForm::ProcessDirectory(bool bDoSubfolders, String strFileSpec)
{
WIN32_FIND_DATA         fd;
HANDLE hFind = FindFirstFile(strFileSpec.c_str(), &fd);

if (hFind != INVALID_HANDLE_VALUE)
    {
    do
        {
        if (!(fd.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY |
            FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM |
            FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_OFFLINE |
            FILE_ATTRIBUTE_TEMPORARY)))
            {
        	TCHAR       szPath[MAX_PATH];
        	GetFullPathName((LPCTSTR ) fd.cFileName, sizeof (szPath) / sizeof (TCHAR),
		        szPath, NULL);
            g_strsFileList->Add(szPath);
            }
        } while (FindNextFile(hFind, &fd));
    FindClose(hFind);
    }

//
// Now do the same in this directory's subdirectories if the
// bDoSubfolders flag is true.
//
if (bDoSubfolders)
    {
    HANDLE hFind = FindFirstFile("*.*", &fd);

    if (hFind != INVALID_HANDLE_VALUE)
        {
        do
            {
            if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
                {
                String dir = fd.cFileName;
                if ((dir != ".") && (dir != ".."))
                    {
                    SetCurrentDirectory(dir.c_str());
                    ProcessDirectory(bDoSubfolders, strFileSpec);
                    SetCurrentDirectory("..");
                    }
                }
            } while (FindNextFile(hFind, &fd));
        FindClose(hFind);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TSaverForm::tmrSaverTimer(TObject *Sender)
{
// change the current file name
static TDateTime    dtLastFileChange = TDateTime::CurrentDateTime();
static int          i = 1;

if (TDateTime::CurrentDateTime() > dtLastFileChange + TDateTime(0, (unsigned short ) MainForm->FileChange->Value ,0 , 0))
    {
    dtLastFileChange = TDateTime::CurrentDateTime();

    if (g_strsFileList->Count > 0)
        {
        LoadSWFile(g_strsFileList->Strings[i]);

        i++;
        i = (i >= g_strsFileList->Count) ? 0 : i;
        }
    }



// scroll marquee text
static  int     Xpos = 0 - Canvas->TextWidth(SP_MARQUEE_TEXT1);
static  int     nMarqueeIndex = 0,
                nMaxStrLen;

static String   strLine1 = (true == g_bIsSolidPartners) ? ::String(SP_MARQUEE_TEXT1) : g_strVarBanner,
                strLine2 = (true == g_bIsSolidPartners) ? ::String(SP_MARQUEE_TEXT2) : g_strVarWebSite;

// scroll the marquee text across the screen
TRect           NewRect;

NewRect = Rect(
            Xpos - 3,   // left
            Screen->Height - 100,   // top
            Xpos - 1 + Canvas->TextWidth(strLine1), // right
            Screen->Height - 100 + Canvas->TextHeight(strLine1) //bottom
            );
Canvas->FillRect(NewRect);
Canvas->TextOut(Xpos, Screen->Height - 100, strLine1);

NewRect = Rect(
            Xpos - 1,
            Screen->Height - 75,
            Xpos - 1 + Canvas->TextWidth(strLine2),
            Screen->Height - 75 + Canvas->TextHeight(strLine2)
            );
Canvas->FillRect(NewRect);
Canvas->TextOut(Xpos, Screen->Height - 75, strLine2);

Xpos++; Xpos++;

if (Xpos > Screen->Width)
    {
    nMarqueeIndex++;
    nMarqueeIndex = (nMarqueeIndex > 2) ? 0 : nMarqueeIndex;
    switch (nMarqueeIndex)
        {
        default :
        case    0:
            strLine1 = (true == g_bIsSolidPartners) ? ::String(SP_MARQUEE_TEXT1) : g_strVarBanner ;
            strLine2 = (true == g_bIsSolidPartners) ? ::String(SP_MARQUEE_TEXT2) : g_strVarWebSite;
            break;

        case    1:
            strLine1 = ACT_MARQUEE_TEXT1;
            strLine2 = ACT_MARQUEE_TEXT2;
            break;

        case    2:
            strLine1 = g_strVarBanner;
            strLine2 = g_strVarWebSite;
            break;
        }
    nMaxStrLen = max((int ) Canvas->TextWidth(strLine1), (int ) Canvas->TextWidth(strLine2));
    Xpos = 0 - nMaxStrLen;
    }



// tumble the model
/* ********************************************************* */
/*
this is really great code to fly around latitiudes and longitudes
based on a polar to rectangular conversion.  The bad thing is that
the actXView->SpinX/Y/Z properties do exactly the same thing

Phi         = angle between point, origin and z axis

Theta       = angle in x-y plane between point, origin and x axis
                note that the point is projected into the x-y plane

g_Radius    = distance from origin to point
*/
static double   fTheta = 0,
                fPhi = M_PI / 2.0;
static bool     bLatitude = true;

#define     MAX_SPIN    2.05
#define     MIN_SPIN    0.05
#define     ANG_INCR    ((MIN_SPIN + (MAX_SPIN - MIN_SPIN) * ((double ) MainForm->TumbleSpeed->Value - 1.0) / 99.0) * M_PI / 180.0)

double      X = g_Radius * sin(fPhi) * cos(fTheta),
            Y = g_Radius * sin(fPhi) * sin(fTheta),
            Z = g_Radius * cos(fPhi);

actXView->ViewSetEyePt(actXView->GetFirstViewport(), X, Y, Z);
if (true == bLatitude)
    {
    fPhi = M_PI / 2.0;
    fTheta += ANG_INCR;
    bLatitude = (fTheta > 2 * M_PI) ? false : true;
    }
else
    {
    fTheta = M_PI / 2.0;
    fPhi += ANG_INCR;
    bLatitude = (fPhi > 2 * M_PI) ? true : false;
    }
/* ********************************************************* */




#if 0
/* ********************************************************* */
// yet another spin method about each of the axes based on
// the actXView->SpinX/Y/Z properties

if (1 == nSpinAngle)
    {
    actXView->SpinX = 1;
    actXView->SpinY = 0;
    actXView->SpinZ = 0;
    }
else if (120 == nSpinAngle)
    {
    actXView->SpinX = 0;
    actXView->SpinY = 1;
    actXView->SpinZ = 0;
    }
else if (240 == nSpinAngle)
    {
    actXView->SpinX = 0;
    actXView->SpinY = 0;
    actXView->SpinZ = 1;
    }
else if (360 == nSpinAngle)
    {
    nSpinAngle = 0;
    }

nSpinAngle++;
/* ********************************************************* */
#endif



#if 0
/* --------------------------------------------------------------------------

http://prestwick.simplenet.com/aviation/aviaform.htm#Int

Latitude of point on GC
Intermediate points {lat,lon} lie on the great circle connecting points 1
and 2 when:

lat = atan((sin(lat1) * cos(lat2) * sin(lon - lon2) - sin(lat2) * cos(lat1)
* sin(lon - lon1))
	/ (cos(lat1) * cos(lat2) * sin(lon1 - lon2)))

(not applicable for meridians. i.e if sin(lon1 - lon2) == 0)
-------------------------------------------------------------------------- */

// this is to use the actXView->SpinX/Y/Z properties but there is not
// enough control over the speed.  SpinX = 1 is OK but the speed does
// not increase slowly enough.  Since it is an integer value, there
// is not enough granularity for fine control :-((
#define     MAX_INTERVALS       10

static int  nIntervals = 0,
            nSpinAxis = 1;

if (nIntervals > MAX_INTERVALS)
    {
    nSpinAxis = (nSpinAxis) > 3 ? 1 : nSpinAxis++;

    switch (nSpinAxis)
        {
        default     :
        case    1   :
            actXView->SpinX = MainForm->TumbleSpeed->Value;
            actXView->SpinY = 0;
            actXView->SpinZ = 0;
            break;

        case    2   :
            actXView->SpinX = 0;
            actXView->SpinY = MainForm->TumbleSpeed->Value;
            actXView->SpinZ = 0;
            break;

        case    3   :
            actXView->SpinX = 0;
            actXView->SpinY = 0;
            actXView->SpinZ = MainForm->TumbleSpeed->Value;
            break;
        }
    }
#endif
}
//---------------------------------------------------------------------------

