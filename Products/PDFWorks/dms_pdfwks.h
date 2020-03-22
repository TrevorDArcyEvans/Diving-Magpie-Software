/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Nov 05 15:14:43 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_PDFWorks\DMS_PDFWks.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __DMS_PDFWks_h__
#define __DMS_PDFWks_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __DMS_PDFWorks_FWD_DEFINED__
#define __DMS_PDFWorks_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_PDFWorks DMS_PDFWorks;
#else
typedef struct DMS_PDFWorks DMS_PDFWorks;
#endif /* __cplusplus */

#endif 	/* __DMS_PDFWorks_FWD_DEFINED__ */


#ifndef __IDMS_PDFWorks_FWD_DEFINED__
#define __IDMS_PDFWorks_FWD_DEFINED__
typedef interface IDMS_PDFWorks IDMS_PDFWorks;
#endif 	/* __IDMS_PDFWorks_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DMS_PDFWks_LIBRARY_DEFINED__
#define __DMS_PDFWks_LIBRARY_DEFINED__

/* library DMS_PDFWks */
/* [custom][custom][helpstring][version][uuid] */ 

typedef 
enum tagtagPDF_PAPER_SIZE
    {	PAPER_SIZE_A0	= 0,
	PAPER_SIZE_A1	= 1,
	PAPER_SIZE_A2	= 2,
	PAPER_SIZE_A3	= 3,
	PAPER_SIZE_A4	= 4,
	PAPER_SIZE_A5	= 5,
	PAPER_SIZE_A6	= 6,
	PAPER_SIZE_B5	= 7,
	PAPER_SIZE_LETTER	= 8,
	PAPER_SIZE_LEGAL	= 9,
	PAPER_SIZE_LEDGER	= 10,
	PAPER_SIZE_P11x17	= 11,
	PAPER_SIZE_USER	= 12
    }	tagPDF_PAPER_SIZE;

typedef 
enum tagtagPDF_UNITS
    {	UNITS_MILLIMETERS	= 0,
	UNITS_INCHES	= 1,
	UNITS_POINTS	= 2
    }	tagPDF_UNITS;

typedef struct  tagtagPDF_Info
    {
    BSTR InfoSubject;
    BSTR InfoTitle;
    BSTR InfoCreator;
    BSTR InfoAuthor;
    BSTR InfoKeyWords;
    }	tagPDF_Info;

typedef struct  tagtagPDF_ImageSetup
    {
    long JPGQuality;
    long ImageHeight;
    long ImageWidth;
    long Stretch;
    }	tagPDF_ImageSetup;

typedef struct  tagtagPDF_PageSetup
    {
    long MarginTop;
    long MarginBottom;
    long MarginLeft;
    long MarginRight;
    tagPDF_PAPER_SIZE PaperSize;
    long PaperHeight;
    long PaperWidth;
    long Landscape;
    long ScaleToFit;
    long KeepAspectRatio;
    double Scale;
    long CentreOnPage;
    }	tagPDF_PageSetup;

typedef struct  tagtagPDF_Setup
    {
    tagPDF_PageSetup PageSetup;
    tagPDF_Info Info;
    tagPDF_ImageSetup ImageSetup;
    tagPDF_UNITS Units;
    }	tagPDF_Setup;


DEFINE_GUID(LIBID_DMS_PDFWks,0xB147E1AA,0x33C6,0x11D4,0x89,0xE8,0x00,0x20,0xAF,0xCC,0x56,0x95);

DEFINE_GUID(CLSID_DMS_PDFWorks,0xB147E1AD,0x33C6,0x11D4,0x89,0xE8,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifdef __cplusplus

class DECLSPEC_UUID("B147E1AD-33C6-11D4-89E8-0020AFCC5695")
DMS_PDFWorks;
#endif

#ifndef __IDMS_PDFWorks_INTERFACE_DEFINED__
#define __IDMS_PDFWorks_INTERFACE_DEFINED__

/* interface IDMS_PDFWorks */
/* [object][oleautomation][dual][helpstring][version][uuid] */ 


DEFINE_GUID(IID_IDMS_PDFWorks,0xB147E1AB,0x33C6,0x11D4,0x89,0xE8,0x00,0x20,0xAF,0xCC,0x56,0x95);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B147E1AB-33C6-11D4-89E8-0020AFCC5695")
    IDMS_PDFWorks : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT __stdcall Configure( 
            /* [in] */ BSTR sTitle,
            /* [out] */ long __RPC_FAR *bOK,
            /* [out][in] */ tagPDF_Setup __RPC_FAR *pPDF_Setup) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Icon( 
            /* [in] */ long Param1) = 0;
        
        virtual /* [id] */ HRESULT __stdcall ClipBoardToJPGFile( 
            /* [in] */ BSTR sFileName) = 0;
        
        virtual /* [id] */ HRESULT __stdcall ClipBoardToBMPFile( 
            /* [in] */ BSTR sFileName) = 0;
        
        virtual /* [id] */ HRESULT __stdcall ClipBoardToGIFFile( 
            /* [in] */ BSTR sFileName) = 0;
        
        virtual /* [id] */ HRESULT __stdcall ClipBoardToPDFFile( 
            /* [in] */ BSTR sFileName) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_JPGQuality( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_JPGQuality( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_MarginTop( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_MarginTop( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_MarginBottom( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_MarginBottom( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_PaperSize( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_PaperSize( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_PaperWidth( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_PaperWidth( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_PaperHeight( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_PaperHeight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Landscape( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Landscape( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_ScaleToFit( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_ScaleToFit( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_CentreOnPage( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_CentreOnPage( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_InfoSubject( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_InfoSubject( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_InfoTitle( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_InfoTitle( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_InfoCreator( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_InfoCreator( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_InfoAuthor( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_InfoAuthor( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Units( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Units( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Scale( 
            /* [retval][out] */ double __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Scale( 
            /* [in] */ double Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_MarginLeft( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_MarginLeft( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_MarginRight( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_MarginRight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_ImageHeight( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_ImageHeight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_ImageWidth( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_ImageWidth( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Stretch( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Stretch( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_InfoKeyWords( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_InfoKeyWords( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id] */ HRESULT __stdcall Initialise( 
            /* [in] */ tagPDF_Setup PDF_Init) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_KeepAspectRatio( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_KeepAspectRatio( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Amyuni( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Amyuni( 
            /* [in] */ long Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_PDFWorksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_PDFWorks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_PDFWorks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Configure )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR sTitle,
            /* [out] */ long __RPC_FAR *bOK,
            /* [out][in] */ tagPDF_Setup __RPC_FAR *pPDF_Setup);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Icon )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Param1);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *ClipBoardToJPGFile )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR sFileName);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *ClipBoardToBMPFile )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR sFileName);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *ClipBoardToGIFFile )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR sFileName);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *ClipBoardToPDFFile )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR sFileName);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_JPGQuality )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_JPGQuality )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_MarginTop )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_MarginTop )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_MarginBottom )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_MarginBottom )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_PaperSize )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_PaperSize )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_PaperWidth )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_PaperWidth )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_PaperHeight )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_PaperHeight )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Landscape )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Landscape )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_ScaleToFit )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_ScaleToFit )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_CentreOnPage )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_CentreOnPage )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_InfoSubject )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_InfoSubject )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_InfoTitle )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_InfoTitle )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_InfoCreator )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_InfoCreator )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_InfoAuthor )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_InfoAuthor )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Units )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Units )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Scale )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Scale )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ double Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_MarginLeft )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_MarginLeft )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_MarginRight )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_MarginRight )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_ImageHeight )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_ImageHeight )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_ImageWidth )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_ImageWidth )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Stretch )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Stretch )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_InfoKeyWords )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_InfoKeyWords )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Initialise )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ tagPDF_Setup PDF_Init);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_KeepAspectRatio )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_KeepAspectRatio )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Amyuni )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Amyuni )( 
            IDMS_PDFWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        END_INTERFACE
    } IDMS_PDFWorksVtbl;

    interface IDMS_PDFWorks
    {
        CONST_VTBL struct IDMS_PDFWorksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_PDFWorks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_PDFWorks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_PDFWorks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_PDFWorks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDMS_PDFWorks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDMS_PDFWorks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDMS_PDFWorks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDMS_PDFWorks_Configure(This,sTitle,bOK,pPDF_Setup)	\
    (This)->lpVtbl -> Configure(This,sTitle,bOK,pPDF_Setup)

#define IDMS_PDFWorks_put_Icon(This,Param1)	\
    (This)->lpVtbl -> put_Icon(This,Param1)

#define IDMS_PDFWorks_ClipBoardToJPGFile(This,sFileName)	\
    (This)->lpVtbl -> ClipBoardToJPGFile(This,sFileName)

#define IDMS_PDFWorks_ClipBoardToBMPFile(This,sFileName)	\
    (This)->lpVtbl -> ClipBoardToBMPFile(This,sFileName)

#define IDMS_PDFWorks_ClipBoardToGIFFile(This,sFileName)	\
    (This)->lpVtbl -> ClipBoardToGIFFile(This,sFileName)

#define IDMS_PDFWorks_ClipBoardToPDFFile(This,sFileName)	\
    (This)->lpVtbl -> ClipBoardToPDFFile(This,sFileName)

#define IDMS_PDFWorks_get_JPGQuality(This,Value)	\
    (This)->lpVtbl -> get_JPGQuality(This,Value)

#define IDMS_PDFWorks_put_JPGQuality(This,Value)	\
    (This)->lpVtbl -> put_JPGQuality(This,Value)

#define IDMS_PDFWorks_get_MarginTop(This,Value)	\
    (This)->lpVtbl -> get_MarginTop(This,Value)

#define IDMS_PDFWorks_put_MarginTop(This,Value)	\
    (This)->lpVtbl -> put_MarginTop(This,Value)

#define IDMS_PDFWorks_get_MarginBottom(This,Value)	\
    (This)->lpVtbl -> get_MarginBottom(This,Value)

#define IDMS_PDFWorks_put_MarginBottom(This,Value)	\
    (This)->lpVtbl -> put_MarginBottom(This,Value)

#define IDMS_PDFWorks_get_PaperSize(This,Value)	\
    (This)->lpVtbl -> get_PaperSize(This,Value)

#define IDMS_PDFWorks_put_PaperSize(This,Value)	\
    (This)->lpVtbl -> put_PaperSize(This,Value)

#define IDMS_PDFWorks_get_PaperWidth(This,Value)	\
    (This)->lpVtbl -> get_PaperWidth(This,Value)

#define IDMS_PDFWorks_put_PaperWidth(This,Value)	\
    (This)->lpVtbl -> put_PaperWidth(This,Value)

#define IDMS_PDFWorks_get_PaperHeight(This,Value)	\
    (This)->lpVtbl -> get_PaperHeight(This,Value)

#define IDMS_PDFWorks_put_PaperHeight(This,Value)	\
    (This)->lpVtbl -> put_PaperHeight(This,Value)

#define IDMS_PDFWorks_get_Landscape(This,Value)	\
    (This)->lpVtbl -> get_Landscape(This,Value)

#define IDMS_PDFWorks_put_Landscape(This,Value)	\
    (This)->lpVtbl -> put_Landscape(This,Value)

#define IDMS_PDFWorks_get_ScaleToFit(This,Value)	\
    (This)->lpVtbl -> get_ScaleToFit(This,Value)

#define IDMS_PDFWorks_put_ScaleToFit(This,Value)	\
    (This)->lpVtbl -> put_ScaleToFit(This,Value)

#define IDMS_PDFWorks_get_CentreOnPage(This,Value)	\
    (This)->lpVtbl -> get_CentreOnPage(This,Value)

#define IDMS_PDFWorks_put_CentreOnPage(This,Value)	\
    (This)->lpVtbl -> put_CentreOnPage(This,Value)

#define IDMS_PDFWorks_get_InfoSubject(This,Value)	\
    (This)->lpVtbl -> get_InfoSubject(This,Value)

#define IDMS_PDFWorks_put_InfoSubject(This,Value)	\
    (This)->lpVtbl -> put_InfoSubject(This,Value)

#define IDMS_PDFWorks_get_InfoTitle(This,Value)	\
    (This)->lpVtbl -> get_InfoTitle(This,Value)

#define IDMS_PDFWorks_put_InfoTitle(This,Value)	\
    (This)->lpVtbl -> put_InfoTitle(This,Value)

#define IDMS_PDFWorks_get_InfoCreator(This,Value)	\
    (This)->lpVtbl -> get_InfoCreator(This,Value)

#define IDMS_PDFWorks_put_InfoCreator(This,Value)	\
    (This)->lpVtbl -> put_InfoCreator(This,Value)

#define IDMS_PDFWorks_get_InfoAuthor(This,Value)	\
    (This)->lpVtbl -> get_InfoAuthor(This,Value)

#define IDMS_PDFWorks_put_InfoAuthor(This,Value)	\
    (This)->lpVtbl -> put_InfoAuthor(This,Value)

#define IDMS_PDFWorks_get_Units(This,Value)	\
    (This)->lpVtbl -> get_Units(This,Value)

#define IDMS_PDFWorks_put_Units(This,Value)	\
    (This)->lpVtbl -> put_Units(This,Value)

#define IDMS_PDFWorks_get_Scale(This,Value)	\
    (This)->lpVtbl -> get_Scale(This,Value)

#define IDMS_PDFWorks_put_Scale(This,Value)	\
    (This)->lpVtbl -> put_Scale(This,Value)

#define IDMS_PDFWorks_get_MarginLeft(This,Value)	\
    (This)->lpVtbl -> get_MarginLeft(This,Value)

#define IDMS_PDFWorks_put_MarginLeft(This,Value)	\
    (This)->lpVtbl -> put_MarginLeft(This,Value)

#define IDMS_PDFWorks_get_MarginRight(This,Value)	\
    (This)->lpVtbl -> get_MarginRight(This,Value)

#define IDMS_PDFWorks_put_MarginRight(This,Value)	\
    (This)->lpVtbl -> put_MarginRight(This,Value)

#define IDMS_PDFWorks_get_ImageHeight(This,Value)	\
    (This)->lpVtbl -> get_ImageHeight(This,Value)

#define IDMS_PDFWorks_put_ImageHeight(This,Value)	\
    (This)->lpVtbl -> put_ImageHeight(This,Value)

#define IDMS_PDFWorks_get_ImageWidth(This,Value)	\
    (This)->lpVtbl -> get_ImageWidth(This,Value)

#define IDMS_PDFWorks_put_ImageWidth(This,Value)	\
    (This)->lpVtbl -> put_ImageWidth(This,Value)

#define IDMS_PDFWorks_get_Stretch(This,Value)	\
    (This)->lpVtbl -> get_Stretch(This,Value)

#define IDMS_PDFWorks_put_Stretch(This,Value)	\
    (This)->lpVtbl -> put_Stretch(This,Value)

#define IDMS_PDFWorks_get_InfoKeyWords(This,Value)	\
    (This)->lpVtbl -> get_InfoKeyWords(This,Value)

#define IDMS_PDFWorks_put_InfoKeyWords(This,Value)	\
    (This)->lpVtbl -> put_InfoKeyWords(This,Value)

#define IDMS_PDFWorks_Initialise(This,PDF_Init)	\
    (This)->lpVtbl -> Initialise(This,PDF_Init)

#define IDMS_PDFWorks_get_KeepAspectRatio(This,Value)	\
    (This)->lpVtbl -> get_KeepAspectRatio(This,Value)

#define IDMS_PDFWorks_put_KeepAspectRatio(This,Value)	\
    (This)->lpVtbl -> put_KeepAspectRatio(This,Value)

#define IDMS_PDFWorks_get_Amyuni(This,Value)	\
    (This)->lpVtbl -> get_Amyuni(This,Value)

#define IDMS_PDFWorks_put_Amyuni(This,Value)	\
    (This)->lpVtbl -> put_Amyuni(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT __stdcall IDMS_PDFWorks_Configure_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR sTitle,
    /* [out] */ long __RPC_FAR *bOK,
    /* [out][in] */ tagPDF_Setup __RPC_FAR *pPDF_Setup);


void __RPC_STUB IDMS_PDFWorks_Configure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_Icon_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Param1);


void __RPC_STUB IDMS_PDFWorks_put_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_PDFWorks_ClipBoardToJPGFile_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR sFileName);


void __RPC_STUB IDMS_PDFWorks_ClipBoardToJPGFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_PDFWorks_ClipBoardToBMPFile_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR sFileName);


void __RPC_STUB IDMS_PDFWorks_ClipBoardToBMPFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_PDFWorks_ClipBoardToGIFFile_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR sFileName);


void __RPC_STUB IDMS_PDFWorks_ClipBoardToGIFFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_PDFWorks_ClipBoardToPDFFile_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR sFileName);


void __RPC_STUB IDMS_PDFWorks_ClipBoardToPDFFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_JPGQuality_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_JPGQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_JPGQuality_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_JPGQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_MarginTop_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_MarginTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_MarginTop_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_MarginTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_MarginBottom_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_MarginBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_MarginBottom_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_MarginBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_PaperSize_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_PaperSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_PaperSize_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_PaperSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_PaperWidth_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_PaperWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_PaperWidth_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_PaperWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_PaperHeight_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_PaperHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_PaperHeight_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_PaperHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_Landscape_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_Landscape_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_Landscape_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_Landscape_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_ScaleToFit_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_ScaleToFit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_ScaleToFit_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_ScaleToFit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_CentreOnPage_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_CentreOnPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_CentreOnPage_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_CentreOnPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_InfoSubject_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_InfoSubject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_InfoSubject_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_PDFWorks_put_InfoSubject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_InfoTitle_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_InfoTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_InfoTitle_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_PDFWorks_put_InfoTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_InfoCreator_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_InfoCreator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_InfoCreator_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_PDFWorks_put_InfoCreator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_InfoAuthor_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_InfoAuthor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_InfoAuthor_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_PDFWorks_put_InfoAuthor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_Units_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_Units_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_Units_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_Units_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_Scale_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_Scale_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ double Value);


void __RPC_STUB IDMS_PDFWorks_put_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_MarginLeft_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_MarginLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_MarginLeft_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_MarginLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_MarginRight_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_MarginRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_MarginRight_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_MarginRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_ImageHeight_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_ImageHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_ImageHeight_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_ImageHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_ImageWidth_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_ImageWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_ImageWidth_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_ImageWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_Stretch_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_Stretch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_Stretch_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_Stretch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_InfoKeyWords_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_InfoKeyWords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_InfoKeyWords_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_PDFWorks_put_InfoKeyWords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_PDFWorks_Initialise_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ tagPDF_Setup PDF_Init);


void __RPC_STUB IDMS_PDFWorks_Initialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_KeepAspectRatio_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_KeepAspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_KeepAspectRatio_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_KeepAspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_PDFWorks_get_Amyuni_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_PDFWorks_get_Amyuni_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_PDFWorks_put_Amyuni_Proxy( 
    IDMS_PDFWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_PDFWorks_put_Amyuni_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_PDFWorks_INTERFACE_DEFINED__ */

#endif /* __DMS_PDFWks_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
