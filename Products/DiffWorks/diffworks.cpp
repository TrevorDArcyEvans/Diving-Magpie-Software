// -------------------------------------------------------------------
//
//     Filename: DiffWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#include "DiffWorks.h"
#include "resource.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include <tchar.h>
#include <shlwapi.h>

#include "SLogError.h"

#include "DMS_Comm.h"
#include "DMS_Comm_i.c"

#include "DMS_DiffWks.h"
#include "DMS_DiffWks_i.c"

#include "DMS_ProgPipe.h"
#include "DMS_ProgPipe_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------------------
// the application object
CDiffWorksApp*                              TheApplication = NULL;
static AFX_EXTENSION_MODULE                 DiffWorksDLL = { NULL, NULL };
//------------------------------------------------------------------------
HRESULT DW_GetMass
(
    CString                 Part,
    double*                 Mass,
    double*                 Volume,
    double*                 Area
);

HRESULT DW_Compare
(
    CString                 OriginalPart,
    CString                 ChangedPart ,
    CString                 DisplayPart ,
    double                  Transparency,
    long                    Colour      
);
void DllExport DW_CompareFiles(void);
void DllExport DW_ShowLast(void);
void DllExport DW_Help(void);
void DW_CheckRegistered(bool bShowDialog);
int DllExport DW_RegisterUpdate(void);
void DllExport DW_Register(void);
void DllExport DW_About(void);
//------------------------------------------------------------------------
int                                         g_bRegistered = false;
long                                        g_NumMaxSections = 5;
long                                        g_NumBodiesRetrieved = -1;
LPBODY*                                     g_pBodyList = NULL;

CComBSTR                                    g_OriginalName;
CComBSTR                                    g_ChangedName;
CComBSTR                                    g_DisplayName;

double                                      g_MassOriginal    = 0.0;
double                                      g_VolumeOriginal  = 0.0;
double                                      g_MassChanged     = 0.0;
double                                      g_VolumeChanged   = 0.0;
double                                      g_AreaOriginal    = 0.0;
double                                      g_AreaChanged     = 0.0;

double                                      g_Transparency = 0.7;
long                                        g_Colour = RGB(255, 0 , 0);
//------------------------------------------------------------------------

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("DiffWorks.DLL Initializing!\n");
        
        // Extension DLL one-time initialization
        AfxInitExtensionModule(DiffWorksDLL, hInstance);

        CoInitialize(NULL);

        // check registered status via DMS_Comm
        DW_CheckRegistered(false);
        if (true == g_bRegistered)
            {
            // registered program has practically unlimited differences!
            g_NumMaxSections = 2000000;
            }

        g_pBodyList = new LPBODY [g_NumMaxSections];

        for (long i = 0; i < g_NumMaxSections; i++)
            {
            g_pBodyList[i] = NULL;
            }

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(DiffWorksDLL);

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("DiffWorks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        // Terminate the library before destructors are called
        AfxTermExtensionModule(DiffWorksDLL);

        try
            {
            // clean up each object in the list
            for (long i = 0; i < g_NumMaxSections; i++)
                {
                if (NULL != g_pBodyList[i])
                    {
                    g_pBodyList[i]->Release();
                    g_pBodyList[i] = NULL;
                    }
                }
            }
        catch (...)
            {
            }

        delete [] g_pBodyList;
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
    TheApplication = new CDiffWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    // connected successfully
    return 1;
}
//------------------------------------------------------------------------
// DW_GetMass
//
// returns
//      S_OK
//          if successful
//
//      S_FALSE
//          probably if there was a problem loading one of the files, or
//
// notes
//      not a COM method, only used internally
HRESULT DW_GetMass
(
    CString                 Part,
    double*                 Mass,
    double*                 Volume,
    double*                 Area
)
{
    try
        {
        CComPtr   <ISldWorks>           pSldWorks;
        CComPtr   <IModelDoc>           pModelDoc;

        double                          MassPropertyValues[12];
        long                            Errors = 0;
        VARIANT_BOOL                    bRetVal   = FALSE;
        VARIANT_BOOL                    bSaveFlag = TRUE ;

        pSldWorks = TheApplication->GetSWApp();
        SASSERT(pSldWorks != NULL);

        STEST_HR(pSldWorks->IOpenDoc2(CComBSTR(Part), swDocPART, FALSE, FALSE, TRUE, &Errors, &pModelDoc));
        // note that we will probably get a swFileAlreadyOpenWarn
        // for some of these.  This is expected behaviour.
        if (swFileNotFoundError     == Errors   ||
            swGenericError          == Errors   )
            {
            // error loading one of the files
            return S_FALSE;
            }

        // calculate density to be used for the differences
        // density is based on where we will be displaying the diffs
        STEST_HR(pModelDoc->IGetMassProperties(MassPropertyValues, &bRetVal));
        SASSERT(MassPropertyValues[3] > 0.0);
        *Mass   = MassPropertyValues[5];
        *Volume = MassPropertyValues[3];
        *Area   = MassPropertyValues[4];

        return S_OK;
        }
    catch (_com_error& e)
        {
        return e.Error();
        }
    catch (...)
        {
        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
// DW_Compare
// compares two parts and highlights the differences between them.  Will
// also calculate the difference in mass between the two parts
//
// parameters
//      OriginalPart
//          fully qualified name to SW part file containing the original part
//
//      ChangedPart
//          fully qualified name to SW part file containing the changed part
//
//      DisplayPart
//          fully qualified name to SW part file in which to display the 
//          differences.  This will generally be the same as the original
//          part.
//
//      Transparency
//          transparency setting for the display part
//              0.0 is solid
//              1.0 is totally transparent ie invisible
//
//      Colour
//          RGB colour in which to display the differences, as returned
//          from the RGB() macro
//
// returns
//      S_OK
//          if successful
//
//      S_FALSE
//          probably if there was a problem loading one of the files, or
//
//          not enough space for all the differences but highly unlikely...
//
// notes
//      not a COM method, only used internally
HRESULT DW_Compare
(
    CString                 OriginalPart,
    CString                 ChangedPart ,
    CString                 DisplayPart ,
    double                  Transparency,
    long                    Colour      
)
{
    try
        {
        CComPtr   <ISldWorks>           pSldWorks;

        CComPtr   <IModelDoc>           pModelDocOriginal;
        CComPtr   <IModelDoc>           pModelDocChanged;
        CComPtr   <IModelDoc>           pModelDocDisplay;
        CComPtr   <IModelDoc>           pDummy;

        CComQIPtr <IPartDoc>            pPartDocOriginal;
        CComQIPtr <IPartDoc>            pPartDocChanged;
        CComQIPtr <IPartDoc>            pPartDocDisplay;

        CComPtr   <IBody>               pBodyOriginal;
        CComPtr   <IBody>               pBodyChanged;

        CComPtr   <IBody>               pCopyBodyOriginal;
        CComPtr   <IBody>               pCopyBodyChanged;

        double                          MaterialPropertyValues[9];

        long                            errors = 0;
        long                            ErrorsOriginal = 0;
        long                            ErrorsChanged  = 0;
        long                            ErrorsDisplay  = 0;
        long                            i = 0;
        VARIANT_BOOL                    bRetVal   = FALSE;
        VARIANT_BOOL                    bSaveFlag = TRUE ;

        pSldWorks = TheApplication->GetSWApp();
        SASSERT(pSldWorks != NULL);

        STEST_HR(pSldWorks->IOpenDoc2(CComBSTR(OriginalPart), swDocPART, FALSE, FALSE, FALSE, &ErrorsOriginal, &pModelDocOriginal));
        STEST_HR(pSldWorks->IOpenDoc2(CComBSTR(ChangedPart ), swDocPART, FALSE, FALSE, FALSE, &ErrorsChanged , &pModelDocChanged ));
        STEST_HR(pSldWorks->IOpenDoc2(CComBSTR(DisplayPart ), swDocPART, FALSE, FALSE, FALSE, &ErrorsDisplay , &pModelDocDisplay ));

        // note that we will probably get a swFileAlreadyOpenWarn
        // for some of these.  This is expected behaviour.
        if (swFileNotFoundError     == ErrorsOriginal   ||
            swGenericError          == ErrorsOriginal   ||
            swInvalidFileTypeError  == ErrorsOriginal   ||
            swFileNotFoundError     == ErrorsChanged    ||
            swGenericError          == ErrorsChanged    ||
            swInvalidFileTypeError  == ErrorsChanged    ||
            swFileNotFoundError     == ErrorsDisplay    ||
            swGenericError          == ErrorsDisplay    ||
            swInvalidFileTypeError  == ErrorsDisplay    )
            {
            // error loading one of the files
            return S_FALSE;
            }


        pPartDocOriginal = pModelDocOriginal;
        pPartDocChanged  = pModelDocChanged ;
        pPartDocDisplay  = pModelDocDisplay ;
        SASSERT(pPartDocOriginal != NULL);
        SASSERT(pPartDocChanged  != NULL);
        SASSERT(pPartDocDisplay  != NULL);

        STEST_HR(pPartDocOriginal->IBodyObject(&pBodyOriginal));
        STEST_HR(pPartDocChanged ->IBodyObject(&pBodyChanged ));

        STEST_HR(pBodyOriginal->ICopy(&pCopyBodyOriginal));
        STEST_HR(pBodyChanged ->ICopy(&pCopyBodyChanged ));

        STEST_HR(pCopyBodyOriginal->IOperations(SWBODYCUT, pCopyBodyChanged, g_NumMaxSections, g_pBodyList, &g_NumBodiesRetrieved));

        if (g_NumBodiesRetrieved == g_NumMaxSections)
            {
            // oops! not enough bodies allocated in our global list
            // should never get this error...

            if (TRUE == g_bRegistered)
                {
                // FIX ME!      should really release all pointers, delete g_pBodyList, increase g_NumBodiesRetrieved, reallocate g_pBodyList and call ourselves recursviely
                }

            return S_FALSE;
            }

        for (i = 0; i < g_NumBodiesRetrieved; i++)
            {
            STEST_HR(g_pBodyList[i]->IDisplay(pPartDocDisplay, Colour));
            }

        // check whether there are any unsaved changes before we make 
        // our change to the transparency
        STEST_HR(pModelDocDisplay->GetSaveFlag(&bSaveFlag));

        STEST_HR(pModelDocDisplay->get_IMaterialPropertyValues(MaterialPropertyValues));

        // reduce transparency
        MaterialPropertyValues[7] = Transparency;

        STEST_HR(pModelDocDisplay->put_IMaterialPropertyValues(MaterialPropertyValues));

        if (FALSE == bSaveFlag)
            {
            // changing transparency sets the save flag, so we should 
            // clear the save flag if this is the only change which has 
            // been made
            // FIX ME!      awaiting API from SW
            //STEST_HR(pModelDocDisplay->ClearSaveFlag());
            }

        // show the diffs to the user
        pSldWorks->IActivateDoc2(CComBSTR(DisplayPart), TRUE, &errors, &pDummy);

        return S_OK;
        }
    catch (_com_error& e)
        {
        return e.Error();
        }
    catch (...)
        {
        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
class AutoResource
{
private:
    HINSTANCE           m_SaveResource;
    HINSTANCE           m_NewResourceHandle;

public:
    AutoResource(CString    ModuleName)
        {
        m_SaveResource        = AfxGetResourceHandle();
        m_NewResourceHandle   = LoadLibrary(ModuleName);

        // Switch to the Application resources
        AfxSetResourceHandle(m_NewResourceHandle);
        }

    ~AutoResource()
        {
        // Reset to previous resource handle
        AfxSetResourceHandle(m_SaveResource);
        }

    HINSTANCE GetSavedResource()
        {
        return m_SaveResource;
        }

    HINSTANCE GetResource()
        {
        return m_NewResourceHandle;
        }
};
//------------------------------------------------------------------------
void DllExport DW_CompareFiles(void)
{
    // Save the current resource handle
    HINSTANCE                   SaveResource = AfxGetResourceHandle();
    HINSTANCE                   DW_ResourceHandle = GetModuleHandle(DIFF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(DW_ResourceHandle);


    try
        {
        USES_CONVERSION;

        HRESULT                             hres = S_OK;
        HRESULT                             hresOriginal = S_OK;
        HRESULT                             hresChanged  = S_OK;

        CComBSTR                            sMassOriginal   = _T("Loading ");
        CComBSTR                            sMassChanged    = _T("Loading ");
        CComBSTR                            sCompareOriginal= _T("Comparing ");
        CComBSTR                            sCompareChanged = _T("Comparing ");
        CComBSTR                            sCalculating    = _T("Calculating results...");
        CComBSTR                            sDisplaying     = _T("Displaying differences...");
        TCHAR                               sOriginalName[MAX_PATH];
        TCHAR                               sChangedName [MAX_PATH];

        // run dialog to get 3 filenames, transparency & colour
        hres = TheApplication->m_DMS_DiffWks->GetCompareInfo
                    (
                    &g_OriginalName,
                    &g_ChangedName ,
                    &g_DisplayName ,
                    &g_Transparency,
                    &g_Colour
                    );

        if (hres != S_OK)
            {
            // user cancelled selection of files
            goto CLEAN_UP;
            }

        // remove all the path details from the file names
        _tcscpy(sOriginalName, OLE2T(g_OriginalName));
        _tcscpy(sChangedName , OLE2T(g_ChangedName ));

        PathStripPath(sOriginalName);
        PathStripPath(sChangedName );

        // so they display fully in the progress pipe dialog
        sMassOriginal   .Append(sOriginalName);
        sMassChanged    .Append(sChangedName );
        sCompareOriginal.Append(sOriginalName);
        sCompareChanged .Append(sChangedName );


        TheApplication->m_DMS_ProgPipe->Reset();
        TheApplication->m_DMS_ProgPipe->put_TotalSteps(8);

        TheApplication->m_DMS_ProgPipe->Show();
        Sleep(500);

        TheApplication->m_DMS_ProgPipe->Step();

        // get mass info before we start diff'ing
        TheApplication->m_DMS_ProgPipe->put_Text(sMassOriginal);
        TheApplication->m_DMS_ProgPipe->Step();

        // info for original part
        AfxSetResourceHandle(SaveResource);
        hresOriginal = DW_GetMass(g_OriginalName.m_str, &g_MassOriginal, &g_VolumeOriginal, &g_AreaOriginal);
        AfxSetResourceHandle(DW_ResourceHandle);

        TheApplication->m_DMS_ProgPipe->put_Text(sMassChanged);
        TheApplication->m_DMS_ProgPipe->Step();

        // info for changed part
        AfxSetResourceHandle(SaveResource);
        hresChanged = DW_GetMass(g_ChangedName .m_str, &g_MassChanged , &g_VolumeChanged, &g_AreaChanged);
        AfxSetResourceHandle(DW_ResourceHandle);

        // make sure there were no errors loading the two files
        if (S_OK != hresOriginal ||
            S_OK != hresChanged  )
            {
            goto CLEAN_UP;
            }

        TheApplication->m_DMS_ProgPipe->put_Text(sCompareOriginal);
        TheApplication->m_DMS_ProgPipe->Step();

        // compare original -> changed
        AfxSetResourceHandle(SaveResource);
        hresOriginal = DW_Compare(g_OriginalName.m_str, g_ChangedName .m_str, g_OriginalName.m_str, g_Transparency, g_Colour);
        AfxSetResourceHandle(DW_ResourceHandle);


        TheApplication->m_DMS_ProgPipe->put_Text(sCompareChanged);
        TheApplication->m_DMS_ProgPipe->Step();

        // compare changed -> original
        AfxSetResourceHandle(SaveResource);
        hresChanged = DW_Compare(g_ChangedName .m_str, g_OriginalName.m_str, g_OriginalName.m_str, g_Transparency, g_Colour);
        AfxSetResourceHandle(DW_ResourceHandle);

        // make sure there were no errors diff'ing the two files
        if (S_OK != hresOriginal ||
            S_OK != hresChanged  )
            {
            goto CLEAN_UP;
            }

        TheApplication->m_DMS_ProgPipe->put_Text(sCalculating);
        TheApplication->m_DMS_ProgPipe->Step();
        true == g_bRegistered ? Sleep(500) : Sleep(5000);

        TheApplication->m_DMS_ProgPipe->put_Text(sDisplaying);
        TheApplication->m_DMS_ProgPipe->Step();
        true == g_bRegistered ? Sleep(500) : Sleep(5000);

        TheApplication->m_DMS_ProgPipe->Step();
        true == g_bRegistered ? Sleep(500) : Sleep(5000);
        TheApplication->m_DMS_ProgPipe->Hide();


        hres = TheApplication->m_DMS_DiffWks->ShowCompareResults
                    (
                    g_OriginalName,
                    g_ChangedName,
                    g_MassOriginal,
                    g_MassChanged,
                    g_VolumeOriginal,
                    g_VolumeChanged,
                    g_AreaOriginal,
                    g_AreaChanged
                    );
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }


    CLEAN_UP :
        ;
    // always hide the progress bar
    TheApplication->m_DMS_ProgPipe->Hide();

    // Reset to previous resource handle
    AfxSetResourceHandle(SaveResource);
}
//------------------------------------------------------------------------
void DllExport DW_ShowLast(void)
{
    try
        {
        HRESULT                             hres = S_OK;

        hres = TheApplication->m_DMS_DiffWks->ShowCompareResults
                    (
                    g_OriginalName,
                    g_ChangedName,
                    g_MassOriginal,
                    g_MassChanged,
                    g_VolumeOriginal,
                    g_VolumeChanged,
                    g_AreaOriginal,
                    g_AreaChanged
                    );
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------
void DllExport DW_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\DiffWorks\\DiffWks.hlp"
        , SW_NORMAL);
}
//------------------------------------------------------------------------
// 
// parameters
//      bShowDialog
//          true if dialog is to be shown
//          false if just want to check .ini file
// notes
//      updates g_bRegistered
void DW_CheckRegistered
(
    bool            bShowDialog
)
{
    // Save the current resource handle
    HINSTANCE                   SaveResource = AfxGetResourceHandle();
    HINSTANCE                   DW_ResourceHandle = GetModuleHandle(DIFF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(DW_ResourceHandle);


    try
        {
        HRESULT                     hres;
        CComPtr<IDMS_Common>        DMS_Comm;

        hres = DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
        ASSERT(SUCCEEDED(hres));

        DMS_Comm->put_Commercial(true);
        DMS_Comm->put_ProductCode(CComBSTR(DIFF_WORKS_TITLE_CODE));
        DMS_Comm->put_ProductName(CComBSTR(DIFF_WORKS_TITLE));
        DMS_Comm->put_IniFileName(CComBSTR(DIFF_WORKS_INI_FILE_NAME));

        if (true == bShowDialog)
            {
            DMS_Comm->put_Icon((long ) LoadIcon(DW_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_DIFF_WKS)));

            // only run dialog if asked
            // will store result to .ini file if successfully registered
            DMS_Comm->Register();
            }

        DMS_Comm->get_IsRegistered(&g_bRegistered);

        DMS_Comm = NULL;
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(SaveResource);
}
//------------------------------------------------------------------------
int DllExport DW_RegisterUpdate(void)
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
void DllExport DW_Register(void)
{
    DW_CheckRegistered(true);
}
//------------------------------------------------------------------------
void DllExport DW_About(void)
{
    // Save the current resource handle
    HINSTANCE                   SaveResource = AfxGetResourceHandle();
    HINSTANCE                   DW_ResourceHandle = GetModuleHandle(DIFF_DLL_NAME);


    try
        {
        HRESULT                     hres;
        CComPtr<IDMS_Common>        DMS_Comm;

        hres = DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
        ASSERT(SUCCEEDED(hres));

        DMS_Comm->put_Commercial(true);
        DMS_Comm->put_ProductName(CComBSTR(DIFF_WORKS_TITLE));
        DMS_Comm->put_Icon((long ) LoadIcon(DW_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_DIFF_WKS)));

        DMS_Comm->About();

        DMS_Comm = NULL;
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(SaveResource);
}
//------------------------------------------------------------------------

// --------------------------------
//  End of DiffWorks.cpp
// --------------------------------
