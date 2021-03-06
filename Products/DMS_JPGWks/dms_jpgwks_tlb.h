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

// C++ TLBWRTR : $Revision:   1.134.1.41  $
// File generated on 12/22/00 7:39:59 PM from Type Library described below.

// ************************************************************************ //
// Type Lib: C:\Wombat\Pro\DMS_JPGWks\DMS_JPGWks.tlb (1)
// IID\LCID: {49F6D445-D82F-11D4-8E9E-0020AFCC5695}\0
// Helpfile: 
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINNT\System32\Stdole2.tlb)
//   (2) v4.0 StdVCL, (C:\WINNT\System32\STDVCL40.DLL)
// ************************************************************************ //
#ifndef   __DMS_JPGWks_TLB_h__
#define   __DMS_JPGWks_TLB_h__

#pragma option push -b -w-inl

#include <utilcls.h>
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0500)
//
// The code generated by the TLIBIMP utility or the Import|TypeLibrary 
// and Import|ActiveX feature of C++Builder rely on specific versions of
// the header file UTILCLS.H found in the INCLUDE\VCL directory. If an 
// older version of the file is detected, you probably need an update/patch.
//
#error "This file requires a newer version of the header UTILCLS.H" \
       "You need to apply an update/patch to your copy of C++Builder"
#endif
#include <olectl.h>
#include <ocidl.h>
#if defined(USING_ATLVCL) || defined(USING_ATL)
#if !defined(__TLB_NO_EVENT_WRAPPERS)
#include <atl/atlmod.h>
#endif
#endif


// *********************************************************************//
// Forward reference of some VCL types (to avoid including STDVCL.HPP)    
// *********************************************************************//
namespace Stdvcl {class IStrings; class IStringsDisp;}
using namespace Stdvcl;
typedef TComInterface<IStrings> IStringsPtr;
typedef TComInterface<IStringsDisp> IStringsDispPtr;

namespace Dms_jpgwks_tlb
{

// *********************************************************************//
// HelpString: DMS_JPGWks Library
// Version:    1.0
// *********************************************************************//


// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLSID_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
extern __declspec (package) const GUID LIBID_DMS_JPGWks;
extern __declspec (package) const GUID IID_IDMS_JPGWorks;
extern __declspec (package) const GUID CLSID_DMS_JPGWorks;

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
interface DECLSPEC_UUID("{49F6D446-D82F-11D4-8E9E-0020AFCC5695}") IDMS_JPGWorks;
typedef TComInterface<IDMS_JPGWorks, &IID_IDMS_JPGWorks> IDMS_JPGWorksPtr;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
//                                                                        
// The LIBID_OF_ macro(s) map a LIBID_OF_CoClassName to the GUID of this  
// TypeLibrary. It simplifies the updating of macros when CoClass name    
// change.                                                                
// *********************************************************************//
typedef IDMS_JPGWorks DMS_JPGWorks;
typedef IDMS_JPGWorksPtr DMS_JPGWorksPtr;

#define LIBID_OF_DMS_JPGWorks (&LIBID_DMS_JPGWks)
// *********************************************************************//
// Interface: IDMS_JPGWorks
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {49F6D446-D82F-11D4-8E9E-0020AFCC5695}
// *********************************************************************//
interface IDMS_JPGWorks  : public IDispatch
{
public:
  virtual HRESULT STDMETHODCALLTYPE SaveAsJPEG(BSTR FileName/*[in]*/, long Handle/*[in]*/) = 0; // [1]
  virtual HRESULT STDMETHODCALLTYPE Configure(void) = 0; // [2]

#if !defined(__TLB_NO_INTERFACE_WRAPPERS)



#endif //   __TLB_NO_INTERFACE_WRAPPERS

};

#if !defined(__TLB_NO_INTERFACE_WRAPPERS)
// *********************************************************************//
// SmartIntf: TCOMIDMS_JPGWorks
// Interface: IDMS_JPGWorks
// *********************************************************************//
template <class T /* IDMS_JPGWorks */ >
class TCOMIDMS_JPGWorksT : public TComInterface<IDMS_JPGWorks>, public TComInterfaceBase<IUnknown>
{
public:
  TCOMIDMS_JPGWorksT() {}
  TCOMIDMS_JPGWorksT(IDMS_JPGWorks *intf, bool addRef = false) : TComInterface<IDMS_JPGWorks>(intf, addRef) {}
  TCOMIDMS_JPGWorksT(const TCOMIDMS_JPGWorksT& src) : TComInterface<IDMS_JPGWorks>(src) {}
  TCOMIDMS_JPGWorksT& operator=(const TCOMIDMS_JPGWorksT& src) { Bind(src, true); return *this;}

  HRESULT         __fastcall SaveAsJPEG(BSTR FileName/*[in]*/, long Handle/*[in]*/);
  HRESULT         __fastcall Configure(void);

};
typedef TCOMIDMS_JPGWorksT<IDMS_JPGWorks> TCOMIDMS_JPGWorks;

// *********************************************************************//
// DispIntf:  IDMS_JPGWorks
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {49F6D446-D82F-11D4-8E9E-0020AFCC5695}
// *********************************************************************//
template<class T>
class IDMS_JPGWorksDispT : public TAutoDriver<IDMS_JPGWorks>
{
public:
  IDMS_JPGWorksDispT(){}

  IDMS_JPGWorksDispT(IDMS_JPGWorks *pintf)
  {
    TAutoDriver<IDMS_JPGWorks>::Bind(pintf, false);
  }

  IDMS_JPGWorksDispT(IDMS_JPGWorksPtr pintf)
  {
    TAutoDriver<IDMS_JPGWorks>::Bind(pintf, true);
  }

  IDMS_JPGWorksDispT& operator=(IDMS_JPGWorks *pintf)
  {
    TAutoDriver<IDMS_JPGWorks>::Bind(pintf, false);
    return *this;
  }

  IDMS_JPGWorksDispT& operator=(IDMS_JPGWorksPtr pintf)
  {
    TAutoDriver<IDMS_JPGWorks>::Bind(pintf, true);
    return *this;
  }

  HRESULT BindDefault()
  {
    return OLECHECK(Bind(CLSID_DMS_JPGWorks));
  }

  HRESULT BindRunning()
  {
    return BindToActive(CLSID_DMS_JPGWorks);
  }

  HRESULT         __fastcall SaveAsJPEG(BSTR FileName/*[in]*/, long Handle/*[in]*/);
  HRESULT         __fastcall Configure();

};
typedef IDMS_JPGWorksDispT<IDMS_JPGWorks> IDMS_JPGWorksDisp;

// *********************************************************************//
// SmartIntf: TCOMIDMS_JPGWorks
// Interface: IDMS_JPGWorks
// *********************************************************************//
template <class T> HRESULT __fastcall
TCOMIDMS_JPGWorksT<T>::SaveAsJPEG(BSTR FileName/*[in]*/, long Handle/*[in]*/)
{
  return (*this)->SaveAsJPEG(FileName, Handle);
}

template <class T> HRESULT __fastcall
TCOMIDMS_JPGWorksT<T>::Configure(void)
{
  return (*this)->Configure();
}

// *********************************************************************//
// DispIntf:  IDMS_JPGWorks
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {49F6D446-D82F-11D4-8E9E-0020AFCC5695}
// *********************************************************************//
template <class T> HRESULT __fastcall
IDMS_JPGWorksDispT<T>::SaveAsJPEG(BSTR FileName/*[in]*/, long Handle/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("SaveAsJPEG"), DISPID(1));
  TAutoArgs<2> _args;
  _args[1] = FileName /*[VT_BSTR:0]*/;
  _args[2] = Handle /*[VT_I4:0]*/;
  return OleFunction(_dispid, _args);
}

template <class T> HRESULT __fastcall
IDMS_JPGWorksDispT<T>::Configure()
{
  _TDispID _dispid(*this, OLETEXT("Configure"), DISPID(2));
  return OleFunction(_dispid);
}

// *********************************************************************//
// The following typedefs expose classes (named CoCoClassName) that       
// provide static Create() and CreateRemote(LPWSTR machineName) methods   
// for creating an instance of an exposed object. These functions can     
// be used by client wishing to automate CoClasses exposed by this        
// typelibrary.                                                           
// *********************************************************************//

// *********************************************************************//
// COCLASS DEFAULT INTERFACE CREATOR
// CoClass  : DMS_JPGWorks
// Interface: TCOMIDMS_JPGWorks
// *********************************************************************//
typedef TCoClassCreatorT<TCOMIDMS_JPGWorks, IDMS_JPGWorks, &CLSID_DMS_JPGWorks, &IID_IDMS_JPGWorks> CoDMS_JPGWorks;
#endif  //   __TLB_NO_INTERFACE_WRAPPERS


};     // namespace Dms_jpgwks_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Dms_jpgwks_tlb;
#endif

#pragma option pop

#endif // __DMS_JPGWks_TLB_h__
