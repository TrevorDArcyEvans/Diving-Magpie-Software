// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// C++ TLBWRTR : $Revision:   1.0.3.3  $
// File generated on 1/24/2000 9:49:56 AM from Type Library described below.

// ************************************************************************ //
// Type Lib: C:\Program Files\Common Files\Microsoft Shared\VBA\VBEEXT1.OLB (1)
// IID\LCID: {0002E157-0000-0000-C000-000000000046}\0
// Helpfile: C:\Program Files\Common Files\Microsoft Shared\VBA\VEENOB3.HLP
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINNT\System32\stdole2.tlb)
//   (2) v2.0 Office, (D:\Program Files\Microsoft Office\Office\MSO97.DLL)
// Parent TypeLibrary:
//   (0) v2.5 PowerPoint, (g:\rampage\typelib\TypeLibraries\MSPPT8.olb)
// Errors:
//   Hint: Symbol 'Application' renamed to 'App'
//   Hint: Symbol 'Window' renamed to 'WINDOW'
//   Hint: Symbol '_Windows' renamed to '_Windoz'
//   Hint: Symbol 'Windows' renamed to 'Windoz'
//   Hint: Symbol 'Windows' renamed to 'Windoz'
//   Hint: Symbol 'Click' renamed to '_Click'
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include "VBIDE_97.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Vbide_97
{


// *********************************************************************//
// GUIDS declared in the TypeLibrary                                      
// *********************************************************************//
const GUID LIBID_VBIDE = {0x0002E157, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID_App = {0x0002E158, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID_VBE = {0x0002E166, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID_WINDOW = {0x0002E16B, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__Windoz = {0x0002E16A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_Windoz = {0x0002E185, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__LinkedWindows = {0x0002E16C, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_LinkedWindows = {0x0002E187, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID_Events = {0x0002E167, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__VBProjectsEvents = {0x0002E113, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID DIID__dispVBProjectsEvents = {0x0002E103, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__VBComponentsEvents = {0x0002E115, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID DIID__dispVBComponentsEvents = {0x0002E116, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__ReferencesEvents = {0x0002E11A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID DIID__dispReferencesEvents = {0x0002E118, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_ReferencesEvents = {0x0002E119, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__CommandBarControlEvents = {0x0002E130, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID DIID__dispCommandBarControlEvents = {0x0002E131, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_CommandBarEvents = {0x0002E132, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__ProjectTemplate = {0x0002E159, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_ProjectTemplate = {0x32CDF9E0, 0x1602, 0x11CE,{ 0xBF, 0xDC, 0x08, 0x00, 0x2B, 0x2B, 0x8C, 0xDA} };
const GUID IID__VBProject = {0x0002E160, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_VBProject = {0x0002E169, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__VBProjects = {0x0002E165, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_VBProjects = {0x0002E101, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID_SelectedComponents = {0xBE39F3D4, 0x1B13, 0x11D0,{ 0x88, 0x7F, 0x00, 0xA0, 0xC9, 0x0F, 0x27, 0x44} };
const GUID IID__Components = {0x0002E161, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_Components = {0xBE39F3D6, 0x1B13, 0x11D0,{ 0x88, 0x7F, 0x00, 0xA0, 0xC9, 0x0F, 0x27, 0x44} };
const GUID IID__VBComponents = {0x0002E162, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_VBComponents = {0xBE39F3D7, 0x1B13, 0x11D0,{ 0x88, 0x7F, 0x00, 0xA0, 0xC9, 0x0F, 0x27, 0x44} };
const GUID IID__Component = {0x0002E163, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_Component = {0xBE39F3D8, 0x1B13, 0x11D0,{ 0x88, 0x7F, 0x00, 0xA0, 0xC9, 0x0F, 0x27, 0x44} };
const GUID IID__VBComponent = {0x0002E164, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_VBComponent = {0xBE39F3DA, 0x1B13, 0x11D0,{ 0x88, 0x7F, 0x00, 0xA0, 0xC9, 0x0F, 0x27, 0x44} };
const GUID IID_Property = {0x0002E18C, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__Properties = {0x0002E188, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_Properties = {0x0002E18B, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__CodeModule = {0x0002E16E, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_CodeModule = {0x0002E170, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__CodePanes = {0x0002E172, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_CodePanes = {0x0002E174, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__CodePane = {0x0002E176, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID CLSID_CodePane = {0x0002E178, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID__References = {0x0002E17A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID IID_Reference = {0x0002E17E, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
const GUID DIID__dispReferences_Events = {0xCDDE3804, 0x2064, 0x11CF,{ 0x86, 0x7F, 0x00, 0xAA, 0x00, 0x5F, 0xF3, 0x4A} };
const GUID CLSID_References = {0x0002E17C, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };

};     // namespace Vbide_97
