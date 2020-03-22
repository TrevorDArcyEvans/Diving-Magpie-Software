//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: XGLWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#include "XGLWorks.h"
#include "XGL_Inflate.h"
#include "SldWorks.h"
#include "swOptions.h"
#include "ExampleApp.h"
#include "resource.h"
#include <shlwapi.h>
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
CXGLWorksApp*                       TheApplication = NULL;

static AFX_EXTENSION_MODULE         XGLWorksDLL = { NULL, NULL };
//------------------------------------------------------------------------
void XGL_CheckRegistered(bool bShowDialog);
void DllExport XGL_OpenFile(LPTSTR FileName, LPSLDWORKS pSolidWorks);
void DllExport XGL_About(void);
int  DllExport XGL_RegisterUpdate(void);
void DllExport XGL_Register(void);
void DllExport XGL_Help(void);
void DllExport XGL_RealityWave(void);
//------------------------------------------------------------------------
int                                 g_bRegistered = false;
//------------------------------------------------------------------------

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("XGLWorks.DLL Initializing!\n");
        
        // Extension DLL one-time initialization
        AfxInitExtensionModule(XGLWorksDLL, hInstance);

        CoInitialize(NULL);

        // check registered status via DMS_Comm
        XGL_CheckRegistered(false);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(XGLWorksDLL);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("XGLWorks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        CoUninitialize();

        // Terminate the library before destructors are called
        AfxTermExtensionModule(XGLWorksDLL);
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
    TheApplication = new CXGLWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    // connected successfully
    return 1;
}
//------------------------------------------------------------------------
// document callbacks
void DllExport XGL_OpenFile(LPTSTR FileName, LPSLDWORKS pSolidWorks)
{
    // registered version has, err, 'optimisations'
    #define UNREG_DELAY \
                if (!g_bRegistered) { Sleep(25); }

    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   XGL_ResourceHandle = GetModuleHandle(XGL_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(XGL_ResourceHandle);


    try
        {
        USES_CONVERSION;

        HRESULT                             hr = S_OK;
        VARIANT_BOOL                        bRetVal = TRUE;
        long                                errors = 0;
        bool                                bDeleteTempXGL_File = false;
        CString                             sFileName(FileName);
        CString                             sSWFileName;
        CString                             sSWRootFileName;
        CString                             sZlibFileName;
        TCHAR                               sProcessFileName[MAX_PATH];
        TCHAR                               sTempName[MAX_PATH];
        TCHAR                               ErrorString[2 * MAX_PATH];

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
        sSWRootFileName = sSWFileName;


        // create our progress pipe and set it up
        STEST_HR(pDMS_ProgPipe.CoCreateInstance(__uuidof(DMS_ProgPipe), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));
        STEST_HR(pDMS_ProgPipe->put_Icon((long ) LoadIcon(XGL_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_XGL_WORKS))));

        // Reset to previous resource handle,
        // otherwise SW calls will fail
        AfxSetResourceHandle(hSaveResource);

        STEST_HR(pDMS_ProgPipe->put_Title(CComBSTR(XGL_WORKS_TITLE)));

        sMessage = CComBSTR(XGL_WORKS_TITLE);
        sMessage.Append(CComBSTR(_T("\nCopyright © 2000\nTrevor D'Arcy-Evans")));
        STEST_HR(pDMS_ProgPipe->put_Message(sMessage));
        STEST_HR(pDMS_ProgPipe->Reset());
        STEST_HR(pDMS_ProgPipe->put_Text(CComBSTR(_T("Initialising..."))));
        STEST_HR(pDMS_ProgPipe->Show());


        // is this a zlib compressed file ie .zgl extension?
        sZlibFileName = sFileName;
        sZlibFileName.MakeLower();
        if (-1 != sZlibFileName.Find(_T(".zgl")))
            {
            sMessage = CComBSTR(_T("Decompressing "));
            sMessage.Append(sProcessFileName);
            sMessage.Append(CComBSTR(_T(" ...")));
            STEST_HR(pDMS_ProgPipe->put_Text(sMessage));

            // then decompress to a temporary xgl file
            TCHAR                       ZGL_FileName[2 * MAX_PATH];
            TCHAR                       TempXGLFileName[2 * MAX_PATH];
            TCHAR                       sTempPath    [MAX_PATH];
            TCHAR                       sTempFileName[MAX_PATH];

            // work out where the temporary files are
            GetTempPath(sizeof(sTempPath) / sizeof(TCHAR), sTempPath);

            // form the output file name
            GetTempFileName(sTempPath, _T("XGLWks"), 0, sTempFileName);

            // remove temp file created by GetTempFileName()
            DeleteFile(sTempFileName);

            PathRenameExtension(sTempFileName, _T(".xml"));

            _tcscpy(ZGL_FileName, LPCTSTR(sFileName));
            _tcscpy(TempXGLFileName, sTempFileName);

            if (0 != Inflate_Zlib_File(ZGL_FileName,TempXGLFileName, ErrorString))
                {
                // remove our temporary file
                DeleteFile(TempXGLFileName);

                // before warning user and exiting
                AfxMessageBox(::CString(ErrorString), MB_OK | MB_ICONSTOP);
                goto CLEAN_UP;
                }
            // set flag so we cleanup on exit
            bDeleteTempXGL_File = true;

            sFileName = TempXGLFileName;
            }


        // setup SolidWorks with a new part file and a new body
        CComPtr   <ISldWorks>                       pSldWorks = pSolidWorks;
        CComQIPtr <IModelDoc>                       pModelDoc;
        CComPtr   <IPartDoc>                        pPartDoc;
        CComPtr   <IBody>                           pBody;
        double                                      Points[9];
        double                                      Normal[3];


        // setup the XML parsing
        CComPtr <MSXML::IXMLDOMDocument>            pXGL_DOM;
        CComPtr <MSXML::IXMLDOMNodeList>            pIObjectNodeList;
        CComPtr <MSXML::IXMLDOMNodeList>            pIMeshNodeList;
        CComPtr <MSXML::IXMLDOMNodeList>            pIPatchNodeList;
        CComPtr <MSXML::IXMLDOMNodeList>            pIFaceNodeList;

        CComPtr <MSXML::IXMLDOMNode>                pIObjectNode;
        CComPtr <MSXML::IXMLDOMNode>                pIPatchNode;

        CComPtr <MSXML::IXMLDOMNode>                pIMeshNode;
        CComPtr <MSXML::IXMLDOMNode>                pIMeshRefNode;
        CComPtr <MSXML::IXMLDOMNamedNodeMap>        pIMeshNodeMap;
        CComPtr <MSXML::IXMLDOMNode>                pIMeshIDNode;

        CComPtr <MSXML::IXMLDOMNode>                pIFaceNode;
        CComPtr <MSXML::IXMLDOMNode>                pIFV_n_Node;
        CComPtr <MSXML::IXMLDOMNode>                pIFV_P_Node;
        CComPtr <MSXML::IXMLDOMNode>                pIFV_N_Node;

        CComBSTR                                    sMeshRefText;
        CComBSTR                                    sMeshIDText;
        CComBSTR                                    sFV_P_Text;
        CComBSTR                                    sFV_N_Text;
        CComBSTR                                    FV_List[3] =
                                                        {
                                                        CComBSTR(_T("FV1")),
                                                        CComBSTR(_T("FV2")),
                                                        CComBSTR(_T("FV3"))
                                                        };

        // have to use variants with MSXML - ewwwww!
        CComVariant                                 pVarXGL_FileName;
        CComBSTR                                    sXGL_FileName(sFileName);
        long                                        ObjectCount = 0;
        long                                        MeshCount   = 0;
        long                                        PatchCount  = 0;
        long                                        FaceCount   = 0;

        long                                        nFirstCommaPos  = -1;
        long                                        nSecondCommaPos = -1;
        CString                                     Node_text;
        CString                                     Node_X_text;
        CString                                     Node_Y_text;
        CString                                     Node_Z_text;
        TCHAR*                                      StopString;
        double                                      Node_X = 0;
        double                                      Node_Y = 0;
        double                                      Node_Z = 0;

        long                                        i = 0, j = 0, k = 0, m = 0;
        long                                        NumSteps = 0;


        // initialise our normal vector
        Normal[ 0] = 0;
        Normal[ 1] = 0;
        Normal[ 2] = 1;

        STEST_HR(pVarXGL_FileName.ChangeType(VT_BSTR));
        STEST_HR(sXGL_FileName.CopyTo(&pVarXGL_FileName.bstrVal));

        // create our DOMs in MSXML.dll v2
        STEST_HR(pXGL_DOM.CoCreateInstance(MSXML::CLSID_DOMDocument));

        STEST_HR(pXGL_DOM->load(pVarXGL_FileName, &bRetVal));


        // get number of Object
        // TODO     iterate over Objects and store each Transform & MeshRef
        STEST_HR(pXGL_DOM->getElementsByTagName(CComBSTR(_T("OBJECT")),  &pIObjectNodeList));
        STEST_HR(pIObjectNodeList->get_length(&ObjectCount));

        STEST_HR(pIObjectNodeList->get_item(0, &pIObjectNode));
        STEST_HR(pIObjectNode->selectSingleNode(CComBSTR(_T("MESHREF")), &pIMeshRefNode));
        STEST_HR(pIMeshRefNode->get_text(&sMeshRefText));


        // get number of Mesh
        STEST_HR(pXGL_DOM->getElementsByTagName(CComBSTR(_T("MESH")),  &pIMeshNodeList));
        STEST_HR(pIMeshNodeList->get_length(&MeshCount));

        // go over each mesh
        for (i = 0; i < MeshCount; i++)
            {
            //reset before we reuse
            pPartDoc    = NULL;
            pModelDoc.p = NULL;
            pBody       = NULL;

            // get a new part
            STEST_HR(pSldWorks->INewPart(&pPartDoc));
            pModelDoc = pPartDoc;
            SASSERT(pModelDoc != NULL);

            // get a new body
            STEST_HR(pPartDoc->ICreateNewBody(&pBody));
            SASSERT(pBody != NULL);


            //reset before we reuse
            pIMeshNode      = NULL;
            pIMeshNodeMap   = NULL;
            pIMeshIDNode    = NULL;
            pIPatchNodeList = NULL;

            STEST_HR(pIMeshNodeList->get_item(i, &pIMeshNode));
            STEST_HR(pIMeshNode->get_attributes(&pIMeshNodeMap));
            STEST_HR(pIMeshNodeMap->getNamedItem(CComBSTR(_T("ID")), &pIMeshIDNode));
            STEST_HR(pIMeshIDNode->get_text(&sMeshIDText));

            STEST_HR(pIMeshNodeList->get_item(i, &pIMeshNode));
            STEST_HR(pIMeshNode->selectNodes(CComBSTR(_T("PATCH")), &pIPatchNodeList));
            STEST_HR(pIPatchNodeList->get_length(&PatchCount));


            // calculate the total number of steps
            // which will be total number of faces in this mesh
            sMessage = CComBSTR(_T("Calculating patch count for mesh "));
            sMessage.Append(sMeshIDText);
            sMessage.Append(CComBSTR(_T(" ...")));
            STEST_HR(pDMS_ProgPipe->put_Text(sMessage));
            STEST_HR(pDMS_ProgPipe->Reset());
            STEST_HR(pDMS_ProgPipe->put_TotalSteps(PatchCount));
            NumSteps = 0;

            for (j = 0; j < PatchCount; j++)
                {
                // reset before we reuse
                pIPatchNode    = NULL;
                pIFaceNodeList = NULL;

                STEST_HR(pIPatchNodeList->get_item(j, &pIPatchNode));
                STEST_HR(pIPatchNode->selectNodes(CComBSTR(_T("F")), &pIFaceNodeList));
                STEST_HR(pIFaceNodeList->get_length(&FaceCount));
                NumSteps += FaceCount;

                STEST_HR(pDMS_ProgPipe->Step());
                }
            STEST_HR(pDMS_ProgPipe->Reset());
            STEST_HR(pDMS_ProgPipe->put_TotalSteps(NumSteps));


            // start to process the file
            sMessage = CComBSTR(_T("Processing mesh "));
            sMessage.Append(sMeshIDText);
            sMessage.Append(CComBSTR(_T(" ...")));
            STEST_HR(pDMS_ProgPipe->put_Text(sMessage));


            // iterate over each Patch for this Mesh
            for (j = 0; j < PatchCount; j++)
                {
                // reset before we reuse
                pIPatchNode    = NULL;
                pIFaceNodeList = NULL;

                // now each Face in this Patch
                STEST_HR(pIPatchNodeList->get_item(j, &pIPatchNode));
                STEST_HR(pIPatchNode->selectNodes(CComBSTR(_T("F")), &pIFaceNodeList));
                STEST_HR(pIFaceNodeList->get_length(&FaceCount));
                for (k = 0; k < FaceCount; k++)
                    {
                    // reset before we reuse
                    pIFaceNode = NULL;

                    // now each of the three Nodes in this Face
                    STEST_HR(pIFaceNodeList->get_item(k, &pIFaceNode));
                    for (m = 0; m < 3; m++)
                        {
                        // reset before we reuse
                        pIFV_n_Node = NULL;
                        pIFV_P_Node = NULL;
                        pIFV_N_Node = NULL;

                        STEST_HR(pIFaceNode->selectSingleNode(FV_List[m], &pIFV_n_Node));

                        STEST_HR(pIFV_n_Node->selectSingleNode(CComBSTR(_T("P")), &pIFV_P_Node));
                        STEST_HR(pIFV_n_Node->selectSingleNode(CComBSTR(_T("N")), &pIFV_N_Node));

                        STEST_HR(pIFV_P_Node->get_text(&sFV_P_Text));
                        STEST_HR(pIFV_N_Node->get_text(&sFV_N_Text));


                        Node_text = sFV_P_Text;
                        nFirstCommaPos  = Node_text.Find(',');
                        nSecondCommaPos = Node_text.ReverseFind(',');

                        Node_X_text = Node_text.Left(nFirstCommaPos);
                        Node_Y_text = Node_text.Mid(nFirstCommaPos + 1, nSecondCommaPos - nFirstCommaPos - 1);
                        Node_Z_text = Node_text.Right(Node_text.GetLength() - nSecondCommaPos - 1);


                        Node_X = _tcstod(LPCTSTR(Node_X_text), &StopString);
                        Node_Y = _tcstod(LPCTSTR(Node_Y_text), &StopString);
                        Node_Z = _tcstod(LPCTSTR(Node_Z_text), &StopString);

                        Points[3 * m + 0] = Node_X;
                        Points[3 * m + 1] = Node_Y;
                        Points[3 * m + 2] = Node_Z;
                        }// for each Node

                    // add this face to the body
                    STEST_HR(pBody->ICreatePlanarTrimSurfaceDLL(3, Points, Normal));
                    STEST_HR(pDMS_ProgPipe->Step());
                    UNREG_DELAY;
                    }// for each Face
                }// for each Patch


            STEST_HR(pDMS_ProgPipe->put_Text(CComBSTR(_T("Knitting surfaces..."))));

            // finally make the body from the surfaces
            STEST_HR(pBody->CreateBodyFromSurfaces(&bRetVal));


            // temporarily remove sldprt extension, increment mesh number 
            // and put extension back on
            _tcscpy(sTempName, sSWRootFileName);
            PathRemoveExtension(sTempName);
            sSWRootFileName = sTempName;
            sSWFileName = sSWRootFileName + sMeshIDText.m_str + _T(".sldprt");


            sMessage = CComBSTR(_T("Saving "));
            sMessage.Append(sSWFileName);
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

            // unregistered version only does the first part
            if (false == g_bRegistered)
                {
                break;
                }
            }// for each Mesh


        // don't really have to hide explicitly since destructor will 
        // do this when it goes out of scope...
        STEST_HR(pDMS_ProgPipe->Hide());

        if (true == bDeleteTempXGL_File)
            {
            // remove any temporary XGL files we may have made
            DeleteFile(LPCTSTR(sFileName));
            }
        }
    catch (_com_error& e)
        {
        LogEvent(_T("COM Error in XGL_OpenFile: %s"), e.ErrorMessage());
        }
    catch (...)
        {
        LogEvent(_T("C++ Error in XGL_OpenFile"));
        }


    CLEAN_UP :
        ;


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
//------------------------------------------------------------------------
void DllExport XGL_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\XGLWorks\\XGLWks.hlp"
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
void XGL_CheckRegistered
(
    bool            bShowDialog
)
{
    // Save the current resource handle
    HINSTANCE                   SaveResource = AfxGetResourceHandle();
    HINSTANCE                   XGL_ResourceHandle = GetModuleHandle(XGL_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(XGL_ResourceHandle);


    try
        {
        CComPtr<IDMS_Common>        DMS_Comm;

        STEST_HR(DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));
        ASSERT(SUCCEEDED(hres));

        STEST_HR(DMS_Comm->put_Commercial(true));
        STEST_HR(DMS_Comm->put_ProductCode(CComBSTR(XGL_WORKS_TITLE_CODE)));
        STEST_HR(DMS_Comm->put_ProductName(CComBSTR(XGL_WORKS_TITLE)));
        STEST_HR(DMS_Comm->put_IniFileName(CComBSTR(XGL_WORKS_INI_FILE_NAME)));

        if (true == bShowDialog)
            {
            STEST_HR(DMS_Comm->put_Icon((long ) LoadIcon(XGL_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_XGL_WORKS))));

            // only run dialog if asked
            // will store result to .ini file if successfully registered
            STEST_HR(DMS_Comm->Register());
            }

        STEST_HR(DMS_Comm->get_IsRegistered(&g_bRegistered));

        DMS_Comm = NULL;
        }
    catch (_com_error& e)
        {
        LogEvent(_T("COM Error in XGL_CheckRegistered: %s"), e.ErrorMessage());
        }
    catch (...)
        {
        LogEvent(_T("C++ Error in XGL_CheckRegistered"));
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(SaveResource);
}
//------------------------------------------------------------------------
int DllExport XGL_RegisterUpdate(void)
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
void DllExport XGL_Register(void)
{
    XGL_CheckRegistered(true);
}
//------------------------------------------------------------------------
void DllExport XGL_About(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   XGL_ResourceHandle = GetModuleHandle(XGL_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(XGL_ResourceHandle);


    try
        {
        CComPtr<IDMS_Common>        DMS_Comm;

        STEST_HR(DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(DMS_Comm->put_Commercial(true));
        STEST_HR(DMS_Comm->put_ProductName(CComBSTR(XGL_WORKS_TITLE)));
        STEST_HR(DMS_Comm->put_Icon((long ) LoadIcon(XGL_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_XGL_WORKS))));

        STEST_HR(DMS_Comm->About());

        DMS_Comm = NULL;
        }
    catch (_com_error& e)
        {
        LogEvent(_T("COM Error in XGL_About: %s"), e.ErrorMessage());
        }
    catch (...)
        {
        LogEvent(_T("C++ Error in XGL_About"));
        }

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
//------------------------------------------------------------------------
void DllExport XGL_RealityWave(void)
{
    ShellExecute(NULL, _T("open"),
        _T("http://www.RealityWave.com"),
        NULL, NULL, SW_SHOWDEFAULT);

    return;
}
//------------------------------------------------------------------------


// --------------------------------
//  End of XGLWorks.cpp
// --------------------------------
