// DMS_CustomProperties.cpp : Implementation of CDMS_CustomProperties
#include "stdafx.h"
#include "DMS_CustProps.h"
#include "DMS_CustomProperties.h"

#include <atlbase.h>
#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
// CDMS_CustomProperties
CDMS_CustomProperties::CDMS_CustomProperties()
{
}
//------------------------------------------------------------------------
CDMS_CustomProperties::~CDMS_CustomProperties()
{
}
//------------------------------------------------------------------------
HRESULT CDMS_CustomProperties::FinalConstruct()
{
    ObjectLock(this);

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
HRESULT CDMS_CustomProperties::FinalRelease  ()
{
    ObjectLock(this);

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::GetCustomInfoType3
// Returns the type of a Custom Info field that has been defined for the
// document or for the specified configuration.
// 
// parameters
//      Configuration
//          Name of the configuration, see below.
// 
//      FieldName
//          Name of Custom Property
// 
//      Type
//          Type of Custom property
//          see swCustomInfoType_e for possible values.
//
// returns
//      S_OK
//          if Successful
//
// notes
//      File Custom Property Information is stored in the document file.  
//      It maybe general to the file, in which case there is a single 
//      value whatever the models configuration, or it may be 
//      configuration specific, in which case a different value may be 
//      set for each configuration in the model.
//
//      To access a general Custom Property Information value the 
//      configuration argument should be set to be an empty string.
STDMETHODIMP CDMS_CustomProperties::GetCustomInfoType3
(
    BSTR                        Configuration, 
    BSTR                        FieldName,
    long*                       Type 
)
{
    ObjectLock(this);

    if (NULL == Type)
        {
        return E_POINTER;
        }

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::AddCustomInfo3
// Adds a Custom Info field to the document or the specified configuration.
// 
// parameters
//      Configuration
//          Name of the configuration, see below.
//
//      FieldName
//          Name of Custom Property
//
//      FieldType
//          Type of Custom property, see swCustomInfoType_e for possible
//          values.
//
//      FieldValue
//          Value of Custom property.
//
//      RetVal
//          TRUE if added.
//
// returns
//      S_OK
//          if Successful
//
// notes
//      File Custom Property Information is stored in the document file.  
//      It may be general to the file, in which case there is a single 
//      value whatever the models configuration, or it may be configuration
//      specific, in which case a different value may be set for each 
//      configuration in the model.
//
//      To access a general Custom Property Information value the 
//      configuration argument should be set to be an empty string.
STDMETHODIMP CDMS_CustomProperties::AddCustomInfo3
(
    BSTR                        Configuration, 
    BSTR                        FieldName, 
    long                        FieldType, 
    BSTR                        FieldValue, 
    BOOL*                       RetVal
)
{
    ObjectLock(this);

    if (NULL == RetVal)
        {
        return E_POINTER;
        }

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::GetCustomInfoCount2
// Returns the number of Custom Info fields that have been defined for 
// either the specified configuration or for the document.
// 
// parameters
//      Configuration
//          Name of the configuration, see below.
// 
//      Count
//          Number of Custom Info Fields.
// 
// returns
//      S_OK
//          if Successful
//
// notes
//      File Custom Property Information is stored in the document file.  
//      It may be general to the file, in which case there is a single 
//      value whatever the models configuration, or it may be configuration 
//      specific, in which case a different value may be set for each 
//      configuration in the model.
//
//      To access a general Custom Property Information value the 
//      configuration argument should be set to be an empty string.
STDMETHODIMP CDMS_CustomProperties::GetCustomInfoCount2
(
    BSTR                        Configuration, 
    long*                       Count
)
{
    ObjectLock(this);

    if (NULL == Count)
        {
        return E_POINTER;
        }

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::DeleteCustomInfo2
// Deletes a Custom Info field that has been defined for the document or 
// the specified configuration.
// 
// parameters
//      Configuration
//          Name of the configuration, see below.
// 
//      FieldName
//          Name of Custom Property
// 
//      RetVal
//          TRUE if deleted.
// 
// returns
//      S_OK
//          if Successful
STDMETHODIMP CDMS_CustomProperties::DeleteCustomInfo2
(
    BSTR                        Configuration, 
    BSTR                        FieldName, 
    BOOL*                       RetVal
)
{
    ObjectLock(this);

    if (NULL == RetVal)
        {
        return E_POINTER;
        }

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::get_CustomInfo2
// Allows you to get and set File Custom Information for the SolidWorks 
// document.
// 
// parameters
//      Configuration
//          Name of the configuration, see below.
//
//      FieldName
//          Name of field
//
//      pVal
//          Text in the Field
//
// returns
//      S_OK
//          if Successful
//
// notes
//      File Custom Property Information is stored in the document file.  
//      It may be general to the file, in which case there is a single 
//      value whatever the models configuration, or it may be configuration 
//      specific, in which case a different value may be set for each 
//      configuration in the model.
//
//      To access a general Custom Property Information value the 
//      configuration argument should be set to be an empty string.
//
//      In line with MicroSoft recommendations for OLE support, the File 
//      summary information for SolidWorks documents is written as an OLE 
//      property set into a stream named "\005Summary Information" off the 
//      root storage of the SolidWorks document's compound file
STDMETHODIMP CDMS_CustomProperties::get_CustomInfo2
(
    BSTR                        Configuration,
    BSTR                        FieldName, 
    BSTR*                       pVal
)
{
    ObjectLock(this);

    if (NULL == pVal)
        {
        return E_POINTER;
        }

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
STDMETHODIMP CDMS_CustomProperties::put_CustomInfo2
(
    BSTR                        Configuration, 
    BSTR                        FieldName, 
    BSTR                        newVal
)
{
    ObjectLock(this);

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::GetCustomInfoNames2
// Returns a list of strings of the names of the Custom Properties that 
// have been defined in the document or a specified configuration.
//
// parameters
//      Configuration
//          Name of the configuration, see below.
// 
//      RetVal
//          An array of BSTRs of the Custom property Names.
// 
// returns
//      S_OK
//          if Successful
//
// notes
//      To get the size of array needed by IGetCustomInfoNames call 
//      ModelDoc::GetCustomInfoCount2.
//
//      File Custom Property Information is stored in the document file.  
//      It may be general to the file, in which case there is a single 
//      value whatever the models configuration, or it may be configuration 
//      specific, in which case a different value may be set for each 
//      configuration in the model.
//
//      To access a general Custom Property Information value the 
//      configuration argument should be set to be an empty string.
STDMETHODIMP CDMS_CustomProperties::GetCustomInfoNames2
(
    BSTR                        Configuration, 
    BSTR**                      RetVal
)
{
    ObjectLock(this);

    if (NULL == RetVal)
        {
        return E_POINTER;
        }

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::get_SummaryInfo
// Allows you to get and set File Summary Information for the SolidWorks 
// document.
//
// parameters
//      FieldID
//          Identifier for field, see swSummInfoField_e 
// 
//      pVal
//          Text in the Field
// 
// returns
//      S_OK
//          if Successful
//
// notes
//      In line with MicroSoft recommendations for OLE support, the File 
//      summary information for SolidWorks documents is written as an OLE 
//      property set into a stream named "\005Summary Information" off the 
//      root storage of the SolidWorks document's compound file
STDMETHODIMP CDMS_CustomProperties::get_SummaryInfo
(
    long                        FieldID, 
    BSTR*                       pVal
)
{
    ObjectLock(this);

    if (NULL == pVal)
        {
        return E_POINTER;
        }

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
STDMETHODIMP CDMS_CustomProperties::put_SummaryInfo
(
    long                        FieldID, 
    BSTR                        newVal
)
{
    ObjectLock(this);

    HRESULT                             hr = S_OK;
    try
        {
        }
    catch (_com_error& e)
        {
        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::LoadFile
// opens a compound document storage file and reads in all the properties
//
// parameters
//      FileName
//          path to file to open, including any extension
//          should really be fully qualified path
// 
// returns
//      S_OK
//          if Successful
//
//      other
//          either not a SolidWorks/compound document file or
//
//          could not get access to file, probably locked
//
// notes
STDMETHODIMP CDMS_CustomProperties::LoadFile
(
    BSTR                        FileName
)
{
    ObjectLock(this);

    USES_CONVERSION;

    HRESULT                             hr = S_OK;
    try
        {
        CComQIPtr <IStorage>                pRoot;
        CComQIPtr <IPropertySetStorage>     pPropSetStg;

        CComBSTR                            bstrFileName = FileName;

        GUID                                GUIDList[3];

        int                                 nRet;

        GUIDList[0] = FMTID_SummaryInformation;
        GUIDList[1] = FMTID_DocSummaryInformation;
        GUIDList[2] = FMTID_UserDefinedProperties ;

        // only proceed if the file is an OLE compound doc file
        if (S_OK != StgIsStorageFile(bstrFileName)) { _com_raise_error(E_UNEXPECTED); }

        // open file for reading
        StgOpenStorage(
            bstrFileName, NULL,
            STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
            NULL, 0, &pRoot);

        pPropSetStg = pRoot;
        if (pPropSetStg == NULL) { _com_raise_error(E_UNEXPECTED); }

        // dump info for each of the 3 properties
        for (int i = 0; i < 3; i++)
            {
            const int                           GUID_LENGTH = 512;
            CComQIPtr <IPropertyStorage>        pPropStg;
            WCHAR                               wszFMTID[GUID_LENGTH + 1];

            // Open the property set
            hr = pPropSetStg->Open(
                    GUIDList[i],
                    STGM_READ | STGM_SHARE_EXCLUSIVE,
                    &pPropStg);
            if (FAILED(hr)) { _com_raise_error(hr); }

            // Display the name of the property set
            nRet = StringFromGUID2(
                        GUIDList[i],
                        wszFMTID,
                        GUID_LENGTH);
            if (0 == nRet) { throw L"String too short"; }

            // TODO     wprintf( L"\n Property Set %s in %s:\n", wszFMTID, OLE2T(bstrFileName.m_str));

            DumpPropertySet(pPropStg);
            }
        }
    catch (_com_error& e)
        {
        // note capital S for wide strings/Unicode
        // TODO     wprintf(L"COM error : %S\n", e.ErrorMessage());

        (void ) e;
        hr = E_UNEXPECTED;
        }
    catch (LPCWSTR pwszErrorMessage)
        {
        // TODO     wprintf( L"Error : %s", pwszErrorMessage);

        (void ) pwszErrorMessage;
        hr = E_UNEXPECTED;
        }
    catch (...)
        {
        // probably some sort of access violation due to no file
        // specified as the first parameter
        // TODO     wprintf(L"C++ error\n");

        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::ConvertVarTypeToString
// Generate a string for a given vt. For the sake of simplicity it is 
// assumed that the pwszType parameter points to a buffer that is at least 
// MAX_PATH in length.
void CDMS_CustomProperties::ConvertVarTypeToString
(
    VARTYPE                     vt,
    WCHAR*                      pwszType
)
{
    _ASSERTE(pwszType != NULL);

    switch (vt & VT_TYPEMASK)
        {
        case VT_EMPTY           :   wcscpy( pwszType, L"VT_EMPTY"           );        break;
        case VT_NULL            :   wcscpy( pwszType, L"VT_NULL"            );        break;
        case VT_I2              :   wcscpy( pwszType, L"VT_I2"              );        break;
        case VT_I4              :   wcscpy( pwszType, L"VT_I4"              );        break;
        case VT_I8              :   wcscpy( pwszType, L"VT_I8"              );        break;
        case VT_UI2             :   wcscpy( pwszType, L"VT_UI2"             );        break;
        case VT_UI4             :   wcscpy( pwszType, L"VT_UI4"             );        break;
        case VT_UI8             :   wcscpy( pwszType, L"VT_UI8"             );        break;
        case VT_R4              :   wcscpy( pwszType, L"VT_R4"              );        break;
        case VT_R8              :   wcscpy( pwszType, L"VT_R8"              );        break;
        case VT_CY              :   wcscpy( pwszType, L"VT_CY"              );        break;
        case VT_DATE            :   wcscpy( pwszType, L"VT_DATE"            );        break;
        case VT_BSTR            :   wcscpy( pwszType, L"VT_BSTR"            );        break;
        case VT_ERROR           :   wcscpy( pwszType, L"VT_ERROR"           );        break;
        case VT_BOOL            :   wcscpy( pwszType, L"VT_BOOL"            );        break;
        case VT_VARIANT         :   wcscpy( pwszType, L"VT_VARIANT"         );        break;
        case VT_DECIMAL         :   wcscpy( pwszType, L"VT_DECIMAL"         );        break;
        case VT_I1              :   wcscpy( pwszType, L"VT_I1"              );        break;
        case VT_UI1             :   wcscpy( pwszType, L"VT_UI1"             );        break;
        case VT_INT             :   wcscpy( pwszType, L"VT_INT"             );        break;
        case VT_UINT            :   wcscpy( pwszType, L"VT_UINT"            );        break;
        case VT_VOID            :   wcscpy( pwszType, L"VT_VOID"            );        break;
        case VT_SAFEARRAY       :   wcscpy( pwszType, L"VT_SAFEARRAY"       );        break;
        case VT_USERDEFINED     :   wcscpy( pwszType, L"VT_USERDEFINED"     );        break;
        case VT_LPSTR           :   wcscpy( pwszType, L"VT_LPSTR"           );        break;
        case VT_LPWSTR          :   wcscpy( pwszType, L"VT_LPWSTR"          );        break;
        case VT_RECORD          :   wcscpy( pwszType, L"VT_RECORD"          );        break;
        case VT_FILETIME        :   wcscpy( pwszType, L"VT_FILETIME"        );        break;
        case VT_BLOB            :   wcscpy( pwszType, L"VT_BLOB"            );        break;
        case VT_STREAM          :   wcscpy( pwszType, L"VT_STREAM"          );        break;
        case VT_STORAGE         :   wcscpy( pwszType, L"VT_STORAGE"         );        break;
        case VT_STREAMED_OBJECT :   wcscpy( pwszType, L"VT_STREAMED_OBJECT" );        break;
        case VT_STORED_OBJECT   :   wcscpy( pwszType, L"VT_BLOB_OBJECT"     );        break;
        case VT_CF              :   wcscpy( pwszType, L"VT_CF"              );        break;
        case VT_CLSID           :   wcscpy( pwszType, L"VT_CLSID"           );        break;

        default:
            // CHECK    untested code
            swprintf( pwszType, L"Unknown (%d)", vt & VT_TYPEMASK );
            //wsprintf( pwszType, L"Unknown (%d)", vt & VT_TYPEMASK );
            break;
        }

    if (vt & VT_VECTOR  ) { wcscat( pwszType, L" | VT_VECTOR"   ); }
    if (vt & VT_ARRAY   ) { wcscat( pwszType, L" | VT_ARRAY"    ); }
    if (vt & VT_RESERVED) { wcscat( pwszType, L" | VT_RESERVED" ); }
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::ConvertValueToString
// Generate a string for the value in a given PROPVARIANT structure.
// The most common types are supported (that is, those that can be displayed
// with printf).  For other types, only a "..." is used.
//
// It is assumed for simplicity that the pwszValue parameter points to
// a buffer that is at least MAX_PATH in length.
void CDMS_CustomProperties::ConvertValueToString
(
    const PROPVARIANT&          propvar,
    WCHAR*                      pwszValue
)
{
    _ASSERTE(pwszValue != NULL);

    switch (propvar.vt)
        {
        case VT_EMPTY:
            wcscpy( pwszValue, L"" );
            break;
        case VT_NULL:
            wcscpy( pwszValue, L"" );
            break;
        case VT_I2:
            swprintf( pwszValue, L"%i", propvar.iVal );
            break;
        case VT_I4:
        case VT_INT:
            swprintf( pwszValue, L"%li", propvar.lVal );
            break;
        case VT_I8:
            swprintf( pwszValue, L"%I64i", propvar.hVal );
            break;
        case VT_UI2:
            swprintf( pwszValue, L"%u", propvar.uiVal );
            break;
        case VT_UI4:
        case VT_UINT:
            swprintf( pwszValue, L"%lu", propvar.ulVal );
            break;
        case VT_UI8:
            swprintf( pwszValue, L"%I64u", propvar.uhVal );
            break;
        case VT_R4:
            swprintf( pwszValue, L"%f", propvar.fltVal );
            break;
        case VT_R8:
            swprintf( pwszValue, L"%lf", propvar.dblVal );
            break;
        case VT_BSTR:
            swprintf( pwszValue, L"\"%s\"", propvar.bstrVal );
            break;
        case VT_ERROR:
            swprintf( pwszValue, L"0x%08X", propvar.scode );
            break;
        case VT_BOOL:
            swprintf( pwszValue, L"%s", VARIANT_TRUE == propvar.boolVal ? L"True" : L"False" );
            break;
        case VT_I1:
            //swprintf( pwszValue, L"%i", propvar.cVal );
            break;
        case VT_UI1:
            swprintf( pwszValue, L"%u", propvar.bVal );
            break;
        case VT_VOID:
            wcscpy( pwszValue, L"" );
            break;
        case VT_LPSTR:
            swprintf( pwszValue, L"\"%hs\"", propvar.pszVal );
            break;
        case VT_LPWSTR:
            swprintf( pwszValue, L"\"%s\"", propvar.pwszVal );
            break;
        case VT_FILETIME:
            swprintf( pwszValue, L"%08x:%08x", propvar.filetime.dwHighDateTime, propvar.filetime.dwLowDateTime );
            break;
        case VT_CLSID:
            pwszValue[0] = L'\0';
            StringFromGUID2( *propvar.puuid, pwszValue, MAX_PATH );
            break;
        default:
            wcscpy( pwszValue, L"..." );
            break;
        }
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::DumpProperty
//  Dump the ID, name, type, and value of a property.
void CDMS_CustomProperties::DumpProperty
(
    const PROPVARIANT&          propvar,
    const STATPROPSTG&          statpropstg
)
{
    WCHAR                   wsz[MAX_PATH + 1];

    ConvertVarTypeToString( statpropstg.vt, wsz );
    // TODO     wprintf( L"   ----------------------------------------------------\n"
    //         L"   PropID = %-5d VarType = %-23s", statpropstg.propid, wsz );

    if (NULL != statpropstg.lpwstrName)
        {
        // TODO     wprintf( L" Name = %s", statpropstg.lpwstrName );
        }

    ConvertValueToString( propvar, wsz );
    // TODO     wprintf( L"\n   Value = %s\n", wsz );
}
//------------------------------------------------------------------------
// CDMS_CustomProperties::DumpPropertySet
//  Dump all the properties in a given property set.
//
// notes
//      not a COM method
HRESULT CDMS_CustomProperties::DumpPropertySet
(
    IPropertyStorage*           pPropStg
)
{
    _ASSERTE(pPropStg != NULL);

    HRESULT                             hr = S_OK;
    CComQIPtr <IEnumSTATPROPSTG>        penum;
    STATPROPSTG                         statpropstg;
    PROPVARIANT                         propvar;
    PROPSPEC                            propspec;

    PropVariantInit( &propvar );

    try
        {
        // If this property set has a friendly name, display it now.
        PROPID              propid = PID_DICTIONARY;
        WCHAR*              pwszFriendlyName = NULL;

        hr = pPropStg->ReadPropertyNames( 1, &propid, &pwszFriendlyName );
        if (S_OK == hr)
            {
            // TODO     wprintf( L" (\"%s\")\n\n", pwszFriendlyName );
            CoTaskMemFree( pwszFriendlyName );
            pwszFriendlyName = NULL;
            }
        else
            {
            // TODO     wprintf( L"\n" );
            }

        // Get a property enumerator
        hr = pPropStg->Enum( &penum );
        if (FAILED(hr)) throw L"Failed IPropertyStorage::Enum";

        // Get the first property in the enumeration
        memset(&statpropstg, 0, sizeof(statpropstg));
        hr = penum->Next( 1, &statpropstg, NULL );
        while (S_OK == hr)
            {
            // Read the property out of the property set
            PropVariantInit( &propvar );
            propspec.ulKind = PRSPEC_PROPID;
            propspec.propid = statpropstg.propid;

            hr = pPropStg->ReadMultiple( 1, &propspec, &propvar );
            if( FAILED(hr) ) throw L"Failed IPropertyStorage::ReadMultiple";

            // Display the property value, type, etc.
            DumpProperty( propvar, statpropstg );

            // Free buffers that were allocated during the read and by the enumerator.
            PropVariantClear(&propvar);
            CoTaskMemFree(statpropstg.lpwstrName);
            statpropstg.lpwstrName = NULL;

            // Move to the next property in the enumeration
            hr = penum->Next(1, &statpropstg, NULL);
            }
        if (FAILED(hr)) throw L"Failed IEnumSTATPROPSTG::Next";
        }
    catch (LPCWSTR pwszErrorMessage)
        {
        // TODO     wprintf( L"Error in DumpPropertySet: %s (hr = %08x)\n", pwszErrorMessage, hr );
        (void ) pwszErrorMessage;
        hr = E_UNEXPECTED;
        }

    if (NULL != statpropstg.lpwstrName)
        {
        CoTaskMemFree( statpropstg.lpwstrName );
        }
    PropVariantClear(&propvar);

    return hr;
}
//------------------------------------------------------------------------
