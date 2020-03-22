//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: VRMLWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#include "VRMLWorks.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "resource.h"
#include <math.h>
#include <tchar.h>

#include "SLogError.h"

#include "DMS_Comm.h"
#include "DMS_Comm_i.c"

#include "DMS_ProgPipe.h"
#include "DMS_ProgPipe_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------------------
// the application object
CVRMLWorksApp*                       TheApplication = NULL;
static AFX_EXTENSION_MODULE         VRMLWorksDLL = { NULL, NULL };
//------------------------------------------------------------------------
bool VRML_ExtractVector
(
    CString                 VRML_Line,
    double*                 Vector_X,
    double*                 Vector_Y,
    double*                 Vector_Z
);

void VRML_CheckRegistered(bool bShowDialog);
void DllExport VRML_OpenFile(LPTSTR FileName, LPSLDWORKS pSolidWorks);
void DllExport VRML_About(void);
int  DllExport VRML_RegisterUpdate(void);
void DllExport VRML_Register(void);
void DllExport VRML_Help(void);
void DllExport VRML_RealityWave(void);
//------------------------------------------------------------------------
int                                 g_bRegistered = false;
//------------------------------------------------------------------------
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("VRMLWorks.DLL Initializing!\n");
        
        // Extension DLL one-time initialization
        AfxInitExtensionModule(VRMLWorksDLL, hInstance);

        CoInitialize(NULL);

        // check registered status via DMS_Comm
        VRML_CheckRegistered(false);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(VRMLWorksDLL);

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("VRMLWorks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        CoUninitialize();

        // Terminate the library before destructors are called
        AfxTermExtensionModule(VRMLWorksDLL);
    }
    return 1;   // ok
}

// --------------------------------
//  connections to SolidWorks
// --------------------------------

#define DllExport __declspec( dllexport )
//------------------------------------------------------------------------
// this is the function SolidWorks calls to connect
// to the add-in application
long DllExport InitUserDLL3(LPSLDWORKS pSldWorks)
{
    // this function should be called once per session
    if ( TheApplication != NULL )
    {
        ASSERT ( FALSE );
        return 0;
    }

    // start the application
    TheApplication = new CVRMLWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    // connected successfully
    return 1;
}
//------------------------------------------------------------------------
// document callbacks

// VRML_ExtractVector
// extracts three values, separated by spaces, from a string
// The string will generally have a format like:
//
//         "     -1.370172e+000 -4.848075e+000 -7.085170e+000    "
//
// All leading and trailing white space is stripped from the string
// before extracting the values.
//
// parameters
//      VRML_Line
//          string from which to extract the values
//
//      Vector_X
//      Vector_Y
//      Vector_Z
//          receives values
//
// returns
//      true
//          if successful
//
//      false
//          otherwise, C++ exception?
bool VRML_ExtractVector
(
    CString                 VRML_Line,
    double*                 Vector_X,
    double*                 Vector_Y,
    double*                 Vector_Z
)
{
    try
        {
        int                                         nFirstSpacePos  = 0;
        int                                         nSecondSpacePos = 0;
        CString                                     X_val_text;
        CString                                     Y_val_text;
        CString                                     Z_val_text;
        TCHAR*                                      StopString;

        VRML_Line.TrimLeft ();
        VRML_Line.TrimRight();

        nFirstSpacePos  = VRML_Line.Find(' ');
        nSecondSpacePos = VRML_Line.ReverseFind(' ');
        SASSERT(-1 != nFirstSpacePos );
        SASSERT(-1 != nSecondSpacePos);

        X_val_text = VRML_Line.Left(nFirstSpacePos);
        Y_val_text = VRML_Line.Mid(nFirstSpacePos + 1, nSecondSpacePos - nFirstSpacePos - 1);
        Z_val_text = VRML_Line.Right(VRML_Line.GetLength() - nSecondSpacePos - 1);

        *Vector_X = _tcstod(LPCTSTR(X_val_text), &StopString);      SASSERT(errno != ERANGE);
        *Vector_Y = _tcstod(LPCTSTR(Y_val_text), &StopString);      SASSERT(errno != ERANGE);
        *Vector_Z = _tcstod(LPCTSTR(Z_val_text), &StopString);      SASSERT(errno != ERANGE);
        }
    catch (_com_error& e)
        {
        LogEvent(_T("COM Error in VRML_ExtractVector: %s"), e.ErrorMessage());
        return false;
        }
    catch (...)
        {
        LogEvent(_T("C++ Error in VRML_ExtractVector"));
        return false;
        }

    return true;
}
//------------------------------------------------------------------------
void DllExport VRML_OpenFile(LPTSTR FileName, LPSLDWORKS pSolidWorks)
{
    // registered version has, err, 'optimisations'
    #define UNREG_DELAY \
                if (!g_bRegistered) { Sleep(25); }

    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   VRML_ResourceHandle = GetModuleHandle(VRML_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(VRML_ResourceHandle);

    try
        {
        USES_CONVERSION;

        HRESULT                             hr = S_OK;
        VARIANT_BOOL                        bRetVal = TRUE;
        long                                errors = 0;
        CString                             sFileName(FileName);
        CString                             sSWFileName;
        TCHAR                               sProcessFileName[MAX_PATH];
        TCHAR                               sTempName[MAX_PATH];

        int                                 DotPos = -1;
        int                                 SpacePos = -1;

        CComPtr   <IDMS_ProgPipe>           pDMS_ProgPipe;
        CComBSTR                            sMessage;


        // strip off short file name and trailing file access letter
        DotPos = sFileName.Find(_T('.'));
        if (-1 != DotPos)
            {
            SpacePos = sFileName.Find(_T(' '), DotPos);
            }
        else
            {
            SpacePos = sFileName.Find(_T(' '), 0);
            }
        sFileName.SetAt(SpacePos, _T('\0'));

        // get the short name of the file
        _tcscpy(sProcessFileName, sFileName);
        PathStripPath(sProcessFileName);

        // change to sldprt extension
        _tcscpy(sTempName, sFileName);
        PathRenameExtension(sTempName, _T(".sldprt"));
        sSWFileName = sTempName;


        if (PathFileExists(sSWFileName))
            {
            // SW file already exists, so ask about overwriting
            int             nRetVal;
            nRetVal = AfxMessageBox(sSWFileName + _T(" already exists.\nDo you want to overwrite this file?"),
                        MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2);

            switch (nRetVal)
                {
                case IDYES :
                    //overwriting, so proceed with existing file name
                    break;

                default :
                case IDCANCEL :
                    goto CLEAN_UP;
                    break;

                case IDNO :
                    // doesn't want to overwrite, so get new name
                    CFileDialog             fd(FALSE, _T("sldprt"), sSWFileName,
                                                OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                                                _T("SolidWorks part files (*.sldprt)|*.sldprt|All files (*.*)|*.*||\0"),
                                                NULL);

                    if (IDOK == fd.DoModal())
                        {
                        // already been prompted about overwriting, so update file
                        sSWFileName = fd.GetFileName();
                        }
                    else
                        {
                        // cancelled, so exit
                        goto CLEAN_UP;
                        }
                    break;
                }
            }


        // create our progress pipe and set it up
        STEST_HR(pDMS_ProgPipe.CoCreateInstance(__uuidof(DMS_ProgPipe), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));
        STEST_HR(pDMS_ProgPipe->put_Icon((long ) LoadIcon(VRML_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_VRML_WORKS))));

        // Reset to previous resource handle,
        // otherwise SW calls will fail
        AfxSetResourceHandle(hSaveResource);

        STEST_HR(pDMS_ProgPipe->put_Title(CComBSTR(VRML_WORKS_TITLE)));

        sMessage = CComBSTR(VRML_WORKS_TITLE);
        sMessage.Append(CComBSTR(_T("\nCopyright © 2000\nTrevor D'Arcy-Evans")));
        STEST_HR(pDMS_ProgPipe->put_Message(sMessage));
        STEST_HR(pDMS_ProgPipe->Reset());
        STEST_HR(pDMS_ProgPipe->put_Text(CComBSTR(_T("Initialising..."))));
        STEST_HR(pDMS_ProgPipe->Show());


        // setup SolidWorks with a new part file and a new body
        CComPtr   <ISldWorks>                       pSldWorks = pSolidWorks;
        CComQIPtr <IModelDoc>                       pModelDoc;
        CComPtr   <IPartDoc>                        pPartDoc;
        CComPtr   <IBody>                           pBody;

        // get a new part
        STEST_HR(pSldWorks->INewPart(&pPartDoc));
        pModelDoc = pPartDoc;
        SASSERT(pModelDoc != NULL);

        // get a new body
        STEST_HR(pPartDoc->ICreateNewBody(&pBody));
        SASSERT(pBody != NULL);

        // now open up the VRML file and get the info for SW
        CStdioFile                                  VRML_File(sFileName, 
                                                        CFile::typeText | CFile::modeRead);
        double                                      Points[9];
        double                                      Normal[3];
        CString                                     VRML_Line;

        // initialise our normal vector
        Normal[ 0] = 0;
        Normal[ 1] = 0;
        Normal[ 2] = 1;


        // use the file size to gauge progress
        sMessage = CComBSTR(_T("Processing "));
        sMessage.Append(sProcessFileName);
        sMessage.Append(CComBSTR(_T(" ...")));
        STEST_HR(pDMS_ProgPipe->put_Text(sMessage));
        STEST_HR(pDMS_ProgPipe->put_TotalSteps(VRML_File.GetLength()));


        while (VRML_File.ReadString(VRML_Line))
            {
            // no need to slow this down, it's already slow since it's disk bound
            STEST_HR(pDMS_ProgPipe->put_CurrentStep(VRML_File.GetPosition()));

// each patch in the VRML file looks like:
/*
      Coordinate3
                {
                point [

                       -0.047756379	 -0.200078224	 -0.088900000,
                       -0.047756379	 -0.200078224	 -0.127000000,
                       -0.038231379	 -0.200078224	 -0.088900000,
                       -0.038231379	 -0.200078224	 -0.088900000,
                       -0.047756379	 -0.200078224	 -0.127000000,
                       -0.038231379	 -0.200078224	 -0.127000000
                      ]           # End of points
               }              # End of coords
*/
// the coords are in multiples of three, so we add each face this way
// note that numbers are tab separated - beware

            const CString START_POINTS      = _T("point [");
            const CString END_POINTS        = _T("End of points");


            if (-1 != VRML_Line.Find(START_POINTS))
                {
                // found the start of a block of points,
                // so go through them all
                while (true)
                    {
                    // remove all leading and trailing white space
                    VRML_File.ReadString(VRML_Line);
                    VRML_Line.TrimLeft ();
                    VRML_Line.TrimRight();

                    // skip the empty lines
                    if (0 == VRML_Line.GetLength())
                        {
                        continue;
                        }

                    // keep going over the points in the patch
                    while (-1 == VRML_Line.Find(END_POINTS))
                        {
                        // add each face by reading in a group of three points
                        for (int i = 0; i < 3; i++)
                            {
                            // replace each tab with a single space
                            VRML_Line.Replace(_T("\t"), _T(" "));
                            VRML_Line.TrimLeft ();
                            VRML_Line.TrimRight();

                            VRML_ExtractVector(VRML_Line,
                                &Points[3 * i + 0],
                                &Points[3 * i + 1],
                                &Points[3 * i + 2]);
                            VRML_File.ReadString(VRML_Line);
                            }

                        // and add this face to the body
                        STEST_HR(pBody->ICreatePlanarTrimSurfaceDLL(3,
                            Points,
                            Normal));
                        UNREG_DELAY;
                        }//while !END_POINTS

                    // if we get to here, we've reached the end of 
                    // this patch, so jump out
                    break;
                    }//true
                }//if START_POINTS
            }//while scanning file


        STEST_HR(pDMS_ProgPipe->put_Text(CComBSTR(_T("Knitting surfaces..."))));

        // finally make the body from the surfaces
        STEST_HR(pBody->CreateBodyFromSurfaces(&bRetVal));


        // this will be the short file name with the .sldprt extension
        PathRenameExtension(sProcessFileName, _T(".sldprt"));

        sMessage = CComBSTR(_T("Saving "));
        sMessage.Append(sProcessFileName);
        sMessage.Append(CComBSTR(_T(" ...")));
        STEST_HR(pDMS_ProgPipe->put_Text(sMessage));

        // save it, overwriting any existing one
        // we have to do this, otherwise SW thinks we haven't done anything
        // and shows an error message
        STEST_HR(pModelDoc->SaveAs2(CComBSTR(sSWFileName), 0, FALSE, TRUE, &errors));


        STEST_HR(pModelDoc->put_Visible(TRUE));

        // change to Isometric, shaded and zoomed to fit
        // FIX ME!      changing to shaded mode not working
        STEST_HR(pModelDoc->ShowNamedView2(CComBSTR(_T("*Isometric")), -1));
        STEST_HR(pModelDoc->ViewZoomtofit2());
        STEST_HR(pModelDoc->ViewDisplayShaded());

        STEST_HR(pDMS_ProgPipe->Hide());
        }
    catch (_com_error& e)
        {
        LogEvent(_T("COM Error in VRML_OpenFile: %s"), e.ErrorMessage());
        }
    catch (...)
        {
        LogEvent(_T("C++ Error in VRML_OpenFile"));
        }

    CLEAN_UP :
        ;


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);
}
//------------------------------------------------------------------------
void DllExport VRML_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\VRMLWorks\\VRMLWks.hlp"
        , SW_NORMAL);

    return;
}
//------------------------------------------------------------------------
// 
// parameters
//      bShowDialog
//          true if dialog is to be shown
//          false if just want to check .ini file
// notes
//      updates g_bRegistered
void VRML_CheckRegistered
(
    bool            bShowDialog
)
{
    // Save the current resource handle
    HINSTANCE                   SaveResource = AfxGetResourceHandle();
    HINSTANCE                   VRML_ResourceHandle = GetModuleHandle(VRML_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(VRML_ResourceHandle);


    try
        {
        CComPtr<IDMS_Common>        DMS_Comm;

        STEST_HR(DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(DMS_Comm->put_Commercial(true));
        STEST_HR(DMS_Comm->put_ProductCode(CComBSTR(VRML_WORKS_TITLE_CODE)));
        STEST_HR(DMS_Comm->put_ProductName(CComBSTR(VRML_WORKS_TITLE)));
        STEST_HR(DMS_Comm->put_IniFileName(CComBSTR(VRML_WORKS_INI_FILE_NAME)));

        if (true == bShowDialog)
            {
            STEST_HR(DMS_Comm->put_Icon((long ) LoadIcon(VRML_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_VRML_WORKS))));

            // only run dialog if asked
            // will store result to .ini file if successfully registered
            STEST_HR(DMS_Comm->Register());
            }

        STEST_HR(DMS_Comm->get_IsRegistered(&g_bRegistered));

        DMS_Comm = NULL;
        }
    catch (_com_error& e)
        {
        LogEvent(_T("COM Error in VRML_CheckRegistered: %s"), e.ErrorMessage());
        }
    catch (...)
        {
        LogEvent(_T("C++ Error in VRML_CheckRegistered"));
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(SaveResource);
}
//------------------------------------------------------------------------
int DllExport VRML_RegisterUpdate(void)
{
    #if 0
    return 0;      // If you want the menu item to be unchecked and disabled (grayed out)
    return 1;      // If you want the menu item to be unchecked and enabled
    return 2;      // If you want the menu item to be checked and disabled (grayed out)
    return 3;     // If you want the menu item to be checked and enabled
    #endif

    return g_bRegistered == true ? 0 : 1;
}
//------------------------------------------------------------------------
void DllExport VRML_Register(void)
{
    VRML_CheckRegistered(true);
}
//------------------------------------------------------------------------
void DllExport VRML_About(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   VRML_ResourceHandle = GetModuleHandle(VRML_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(VRML_ResourceHandle);


    try
        {
        CComPtr<IDMS_Common>        DMS_Comm;

        STEST_HR(DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(DMS_Comm->put_Commercial(true));
        STEST_HR(DMS_Comm->put_ProductName(CComBSTR(VRML_WORKS_TITLE)));
        STEST_HR(DMS_Comm->put_Icon((long ) LoadIcon(VRML_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_VRML_WORKS))));

        STEST_HR(DMS_Comm->About());

        DMS_Comm = NULL;
        }
    catch (_com_error& e)
        {
        LogEvent(_T("COM Error in VRML_About: %s"), e.ErrorMessage());
        }
    catch (...)
        {
        LogEvent(_T("C++ Error in VRML_About"));
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
//------------------------------------------------------------------------

// --------------------------------
//  End of VRMLWorks.cpp
// --------------------------------
