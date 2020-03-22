/*

Implementation of SAlertResponsibilitySetStore

$History: SAlertResponsibilitySetStore.cpp $
 * 
 * *****************  Version 7  *****************
 * User: Tim          Date: 10/02/00   Time: 19:17
 * Updated in $/CMIDS/Projects/DatabaseManager
 * Added AutoCloser to ensure Recordsets are closed on exceptions and
 * there filters reset
 * 
 * *****************  Version 6  *****************
 * User: Tim          Date: 19-09-00   Time: 11:20
 * Updated in $/CMIDS/Projects/DatabaseManager
 * Changed all queries to Forward Only and LockReadOnly

*/


#include "stdafx.h"
#include "DatabaseManager.h"
#include "SAlertResponsibilitySetStore.h"
#include "STaskMem.h"

#include "combool.h"


#include <vector>

using namespace std ;

/////////////////////////////////////////////////////////////////////////////
// SAlertResponsibilitySetStore

STDMETHODIMP SAlertResponsibilitySetStore::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAlertResponsibilitySetStore
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


HRESULT SAlertResponsibilitySetStore::FinalConstruct()
{
  try
  {
    SHResult shr = S_OK ;
    CLSID    cls ;

    // Create Master / Slave Database Connection Component

    shr = m_Connect.CreateConnection()  ;
 
    // Create a Recordset to retrieve data with

    m_spADORecordset = NULL ;

    shr = m_spADORecordset.CoCreateInstance( CLSID_CADORecordset ) ;

    // Optimise the retrieval by setting a large cache size

    shr = m_spADORecordset->put_CacheSize( 10 ) ;

	
    // Set Server Side Cursors

    shr = m_spADORecordset->put_CursorLocation( adUseServer ) ;


    // Get the Prog Id for the Alert Responsibility Set Class Factory

    CComBSTR m_bstrAlertResponsibilitySetProgId = OLESTR("AlertManager.SAlertResponsibilitySet") ;
 
    // Get the Class ID of the Alert Responsibility Set Creator

    shr = CLSIDFromProgID( m_bstrAlertResponsibilitySetProgId, &cls ) ;


    // Get and cache the Alert Source Set Class

    shr = CoGetClassObject( cls, CLSCTX_INPROC_SERVER, NULL, 
                         IID_IClassFactory, (void**)&m_spAlertResponsibilitySetCreator ) ;



    // Load the Command Queries


    CComBSTR  bstrQueryByName ;
    bstrQueryByName.LoadString( IDS_ALERTRESPONSIBILITYQUERYUSERCMD ) ;
    m_AlertResponsibilitySetQueryNameCmd.Initialise( bstrQueryByName ) ;

    CComBSTR bstrInsert ;
    bstrInsert.LoadString( IDS_ALERTRESPONSIBILITYINSERTCMD ) ;
    m_AlertResponsibilitySetInsertCmd.Initialise( bstrInsert) ;

    CComBSTR bstrDelete ;
    bstrDelete.LoadString( IDS_ALERTRESPONSIBILITYDELETECMD ) ;
    m_AlertResponsibilitySetDeleteCmd.Initialise( bstrDelete ) ;

 
    CComBSTR bstrQuery ;
    bstrQuery.LoadString( IDS_ALERTRESPONSIBILITYQUERYCMD ) ;
    m_AlertResponsibilitySetQueryCmd.Initialise( bstrQuery ) ;


    return shr ;
  }
  catch( _com_error& e )
  {
    return m_Connect.LogError( e.Error(), _T("SAlertResponsibilitySetStore::FinalConstruct") ) ;
  }
  catch(...)
  {
    return m_Connect.LogError( E_UNEXPECTED, _T("SAlertResponsibilitySetStore::FinalConstruct") ) ;
  }

}



STDMETHODIMP SAlertResponsibilitySetStore::GetUserList(long *pNoOfUsers, BSTR **ppUserList)
{
	
  try
  {
    ObjectLock lock(this) ;   // Lock out others

	  CComPtr<IADORecordBinding>          arb ;                         // Binding interface to bind data to C++ objects
    SAlertResponsibilitySetNameRS       AlertResponsibilitySetNameRs; // C++ Object to receive data
    SHResult                            shr = S_OK ;                   // Exception throwing HRESULT
    VARIANT_BOOL                        RSEof ;

    CComBool    sbMasterConnected ;
    CComBool    sbSlaveConnected  ;

    SAutoClose     Close( m_spADORecordset ) ;

    // Check the Master connection status. 

    shr = IsConnected( &sbMasterConnected, &sbSlaveConnected ) ;
    if (  sbMasterConnected == false   )
      return DB_E_DISCONNECTED ;

    // Attach the Connection To This Command

    shr = m_AlertResponsibilitySetQueryNameCmd.SetConnection( CComVariant( m_Connect.Master() ) ) ;
 

    VARIANT vNull ;
  	vNull.vt					= VT_ERROR ;
	  vNull.scode				= DISP_E_PARAMNOTFOUND ;


    // Execute the Query

    shr = m_spADORecordset->Open( CComVariant( m_AlertResponsibilitySetQueryNameCmd.GetCommand() ), vNull, adOpenForwardOnly, adLockReadOnly, adCmdText ) ;

    
    // Get the hidden bind interface

    shr = m_spADORecordset.QueryInterface( &arb ) ;

 
    // bind the the returned record to our special C++ record

    shr = arb->BindToRecordset( &AlertResponsibilitySetNameRs ) ;
    
    
    // Get the first Alert Responsibility in the Recordset

    shr = m_spADORecordset->get_EOF( &RSEof ) ;

    int i = 0 ;
    vector< CComBSTR > ResultList ;


    while ( RSEof == VARIANT_FALSE )
    {
    
      if ( AlertResponsibilitySetNameRs.m_AlertResponsibilitySetNameStat == adFldOK )
      {
        CComBSTR bstrSetName = AlertResponsibilitySetNameRs.m_AlertResponsibilitySetName ;
        ResultList.push_back( bstrSetName ) ;
      }

      i++ ;
      AlertResponsibilitySetNameRs.ClearRecord() ;       // Nullify all fields
      m_spADORecordset->MoveNext() ;             // Look at next record
      m_spADORecordset->get_EOF( &RSEof) ;       // check for the EOF

    } ;
  

    // Find out how any Records we got back and allocate some COM
    // memory and populate it


    if ( i )
  		*ppUserList = STaskMem<BSTR>::AllocArray ( i );

    for ( i = 0; i < ResultList.size (); i++ )
      ResultList[i].CopyTo( &(*ppUserList)[i] ) ;

    *pNoOfUsers = ResultList.size ();



    ATLTRACE(_T("SALertResponsibilitySetStore::GetUserList: Retrieved %d Users\n"), i ) ;

    return S_OK ;

  }
  catch( _com_error &e )
  {
    return m_Connect.LogError( e.Error(), _T("SAlertResponsibilitySetStore::GetUserList") ) ; 
  }
  catch ( ... )
  {
    return m_Connect.LogError( E_UNEXPECTED, _T("SAlertResponsibilitySetStore::GetUserList") ) ;
  }

}

STDMETHODIMP SAlertResponsibilitySetStore::GetAlertResponsibilitySet(BSTR User, IAlertResponsibilitySet **ppAlertResponsibilitySet, long *pCount)
{
	
  try
  {
    ObjectLock lock(this) ;                                       // Lock out others

	  CComPtr<IADORecordBinding>        arb ;                       // Binding interface to bind data to C++ objects
    SAlertResponsibilityRS            AlertResponsibilitySetRs;   // C++ Object to receive data
    SHResult                          shr = S_OK ;                // Exception throwing HRESULT
    VARIANT_BOOL                      RSEof ;
    CComPtr<IAlertResponsibilitySet>  spAlertResponsibilitySet ;

    CComBool    sbMasterConnected ;
    CComBool    sbSlaveConnected  ;

    SAutoClose     Close( m_spADORecordset ) ;

    // Check the Master connection status. 

    shr = IsConnected( &sbMasterConnected, &sbSlaveConnected ) ;
    if (  sbMasterConnected == false   )
      return DB_E_DISCONNECTED ;


    shr = m_AlertResponsibilitySetQueryCmd.SetParameter( _T("User"), CComVariant( User ) ) ;


    if ( sbMasterConnected )
    {
      shr = m_AlertResponsibilitySetQueryCmd.SetConnection( CComVariant( m_Connect.Master() ) ) ;
    }


    VARIANT vNull ;
  	vNull.vt					= VT_ERROR ;
	  vNull.scode				= DISP_E_PARAMNOTFOUND ;


    shr = m_spADORecordset->Open( CComVariant( m_AlertResponsibilitySetQueryCmd.GetCommand() ), vNull, adOpenForwardOnly, adLockReadOnly, adCmdText ) ;
    
    // Get the hidden bind interface

    shr = m_spADORecordset.QueryInterface( &arb ) ;

 
    // bind the the returned record to our special C++ record

    shr = arb->BindToRecordset( &AlertResponsibilitySetRs ) ;
    
    
    // Get the first Alert Responsibility in the Recordset

    shr = m_spADORecordset->get_EOF( &RSEof ) ;


    // Create an Alert Responsibility Set

    shr = m_spAlertResponsibilitySetCreator->CreateInstance( NULL, __uuidof(IAlertResponsibilitySet), (void**)&spAlertResponsibilitySet ) ;

    
    // Assign the User Name

    if ( ( RSEof == VARIANT_FALSE ) && ( AlertResponsibilitySetRs.m_UserStat == adFldOK ) )
      shr = spAlertResponsibilitySet->SetUser( CComBSTR( AlertResponsibilitySetRs.m_User ) ) ;


    int i = 0 ;
    while ( RSEof == VARIANT_FALSE )
    {
    
       // Assign the database fields to the Alert Responsibility Object

      if ( ( AlertResponsibilitySetRs.m_AlertSourceSetStat == adFldOK )  )
         shr = spAlertResponsibilitySet->AppendSourceSetByName( CComBSTR(AlertResponsibilitySetRs.m_AlertSourceSet) ) ;     

 
      // Get next Alert Responsibility

      i++ ;
      AlertResponsibilitySetRs.ClearRecord() ;                    // Nullify all fields
      m_spADORecordset->MoveNext() ;                              // Look at next record
      m_spADORecordset->get_EOF( &RSEof) ;                        // check for the EOF

    } ;

 
    // Return the Alert

    spAlertResponsibilitySet.CopyTo( ppAlertResponsibilitySet ) ;
    *pCount = i ;


    ATLTRACE(_T("SALertResponsibilitySetStore::GetAlertResponsibilitySet: Retrieved %d Responsibilities\n"), i ) ;

    return S_OK ;

  }
  catch( _com_error &e )
  {
    return m_Connect.LogError( e.Error(), _T("SAlertResponsibilitySetStore::GetAlertResponsibilitySet") ) ; 
  }
  catch ( ... )
  {
    return m_Connect.LogError( E_UNEXPECTED, _T("SAlertResponsibilitySetStore::GetAlertResponsibilitySet") ) ;
  }

}




STDMETHODIMP SAlertResponsibilitySetStore::StoreAlertResponsibilitySet(IAlertResponsibilitySet *pAlertResponsibilitySet)
{
  try
  {

    SHResult shr = S_OK ;
    CComBSTR      bstrUserName ;
    
    CComBool    sbMasterConnected ;
    CComBool    sbSlaveConnected  ;
    long        Count ;

    IAlertSourceSet **ppAlertSourceSets = 0 ;


    // Check the Master connection status. 

    shr = IsConnected( &sbMasterConnected, &sbSlaveConnected ) ;
    if (  sbMasterConnected == false   )
      return DB_E_DISCONNECTED ;


    // Get the User Name

    shr = pAlertResponsibilitySet->GetUser( &bstrUserName ) ;


   // Delete Existing Alert Responsibilities

    shr = DeleteAlertResponsibilities( bstrUserName ) ;


    // Get the List of Source Sets, he is responsible for

    shr = pAlertResponsibilitySet->GetAllSourceSets( &Count, &ppAlertSourceSets ) ;


    // Insert Into Master Database

    for ( int i = 0 ; i < Count ; i++ )
    {
      CComBSTR              bstrAlertSourceSet ;

      // Get Parameters
     
      shr = ppAlertSourceSets[i]->GetName( &bstrAlertSourceSet ) ;

      // Set Parameters

      shr = m_AlertResponsibilitySetInsertCmd.SetParameter( _T("User"), CComVariant( bstrUserName ) ) ;

      shr = m_AlertResponsibilitySetInsertCmd.SetParameter( _T("AlertSet"), CComVariant( bstrAlertSourceSet ) ) ;

 
      // Insert Into Master Database

      if ( sbMasterConnected )
      {
        shr = m_AlertResponsibilitySetInsertCmd.SetConnection( CComVariant(m_Connect.Master()) ) ;

        shr = m_AlertResponsibilitySetInsertCmd.Execute() ;
      }

    } // for


    // Insert Into Slave Database

    for (  i = 0 ; i < Count ; i++ )
    {
      CComBSTR              bstrAlertSourceSet ;

      // Get Parameters
     
      shr = ppAlertSourceSets[i]->GetName( &bstrAlertSourceSet ) ;

      // Set Parameters

      m_AlertResponsibilitySetInsertCmd.SetParameter( _T("User"), CComVariant( bstrUserName ) ) ;

      m_AlertResponsibilitySetInsertCmd.SetParameter( _T("AlertSet"), CComVariant( bstrAlertSourceSet ) ) ;

 
      // Insert Into Slave Database

      if ( sbSlaveConnected )
      {
        shr = m_AlertResponsibilitySetInsertCmd.SetConnection( CComVariant(m_Connect.Slave()) ) ;

        shr = m_AlertResponsibilitySetInsertCmd.Execute() ;
      }

    } // for


    // Free the memory and nullify pointer, so we don't free it twice

    CoTaskMemFree( (void *)ppAlertSourceSets ) ;
    ppAlertSourceSets = 0 ;

    ATLTRACE(_T("SALertResponsibilitySetStore::StoreStoreAlertResponsibilitySet: Stored %d Alert Source Sets\n"), Count ) ;

	  return S_OK;
  }
  catch( _com_error &e )
  {
    return m_Connect.LogError( e.Error(), _T("SAlertResponsibilitySetStore::StoreAlertResponsibilitySet") ) ;
  }
  catch ( ... )
  {
    return m_Connect.LogError( E_UNEXPECTED, _T("SAlertResponsibilitySetStore::StoreAlertResponsibilitySet") ) ;
  }
}



STDMETHODIMP SAlertResponsibilitySetStore::DeleteAlertResponsibilities(BSTR User)
{
  try
  {
    ObjectLock lock(this) ;

    SHResult shr = S_OK ;

    CComBool    sbMasterConnected ;
    CComBool    sbSlaveConnected  ;

    USES_CONVERSION ;

    // Check the Master connection status. 

    shr = IsConnected( &sbMasterConnected, &sbSlaveConnected ) ;
    if (  sbMasterConnected == false   )
      return DB_E_DISCONNECTED ;


    // Set the Delete Parameters

    shr = m_AlertResponsibilitySetDeleteCmd.SetParameter( _T("User"), CComVariant(User) ) ;

    // Delete From the Master Database Only

    if ( sbMasterConnected )
    {
      shr = m_AlertResponsibilitySetDeleteCmd.SetConnection( CComVariant(m_Connect.Master()) ) ;

      shr = m_AlertResponsibilitySetDeleteCmd.Execute() ;
    }

    if ( sbSlaveConnected )
    {
      shr = m_AlertResponsibilitySetDeleteCmd.SetConnection( CComVariant(m_Connect.Slave()) ) ;

      shr = m_AlertResponsibilitySetDeleteCmd.Execute() ;
    }
    

    long i = 0 ;

    m_AlertResponsibilitySetDeleteCmd.GetNoOfRecsAffected( &i ) ;

    ATLTRACE(_T("SAlertResponsibilitySetStore::DeleteAlertResponsibilitites: Deleted %d Alert Source Sets for User %s\n"), i, OLE2T( User ) )  ;

	  return S_OK;

  }
  catch( _com_error &e )
  {
    return m_Connect.LogError( e.Error(), _T("SAlertResponsibilitySetStore::DeleteAlertResponsibilitities") ) ;
  }
  catch(...)
  {
    return m_Connect.LogError( E_UNEXPECTED, _T("SAlertResponsibilitySetStore::DeleteAlertResponsibilities") ) ;
  }


}

STDMETHODIMP SAlertResponsibilitySetStore::SetDataService( IUnknown* DataService)
{
  ObjectLock lock(this) ;
 
  m_spDataService = DataService ;

  return S_OK ;
}

STDMETHODIMP SAlertResponsibilitySetStore::GetAllAlertResponsibilities(long *pSize, IAlertResponsibilitySet ***pppAlertResponsibilitySet)
{  
  try
  {
    ObjectLock lock(this) ;   // Lock out others

	  CComPtr<IADORecordBinding>  arb ;                       // Binding interface to bind data to C++ objects
    SAlertResponsibilityRS      AlertResponsibilitySetRs;   // C++ Object to receive data
    SHResult                    shr = S_OK ;                // Exception throwing HRESULT
    VARIANT_BOOL                RSEof ;
    CComBSTR                    bstrQueryAllCmd ;

    CComBool    sbMasterConnected ;
    CComBool    sbSlaveConnected  ;

    SAutoClose     Close( m_spADORecordset ) ;

    vector< CComPtr< IAlertResponsibilitySet > >  ResponsibilitySetList ;
    vector< CComPtr< IAlertResponsibilitySet > >::iterator  ResponsibilitySetListItr ;


    // Check the Master connection status. 

    shr = IsConnected( &sbMasterConnected, &sbSlaveConnected ) ;
    if (  sbMasterConnected == false   )
      return DB_E_DISCONNECTED ;

    bstrQueryAllCmd.LoadString( IDS_ALERTRESPONSIBILITYQUERYALLCMD ) ;


    shr = m_spADORecordset->Open( CComVariant(bstrQueryAllCmd), CComVariant(m_Connect.Master()), adOpenForwardOnly, adLockReadOnly, adCmdText ) ;
    
    // Get the hidden bind interface

    shr = m_spADORecordset.QueryInterface( &arb ) ;

 
    // bind the the returned record to our special C++ record

    shr = arb->BindToRecordset( &AlertResponsibilitySetRs ) ;
    
    
    // Get the first Alert Source in the Recordset

    shr = m_spADORecordset->get_EOF( &RSEof ) ;


    while( RSEof == VARIANT_FALSE )
    {

      CComPtr<IAlertResponsibilitySet>    spAlertResponsibilitySet ;

      // Create an Alert Responsibility Set

      shr = m_spAlertResponsibilitySetCreator->CreateInstance( NULL, __uuidof(IAlertResponsibilitySet), (void**)&spAlertResponsibilitySet ) ;


      // Append Alert Source Set to Vector

      ResponsibilitySetList.push_back( spAlertResponsibilitySet ) ;


      // Assign the Set Name

      CComBSTR bstrResponsibilitySetUser ;

      if (  AlertResponsibilitySetRs.m_UserStat == adFldOK  )
      {
        bstrResponsibilitySetUser = AlertResponsibilitySetRs.m_User  ;

        shr = spAlertResponsibilitySet->SetUser( bstrResponsibilitySetUser ) ;
      }
      else
        throw _com_error( E_FAIL ) ;


      // Get all the elements of each set

      int i = 0 ;
      while ( RSEof == VARIANT_FALSE && ( ( _tcscmp( AlertResponsibilitySetRs.m_User, OLE2T(bstrResponsibilitySetUser )) == 0 ) ) )
      {
    
       // Assign the database fields to the Alert Responsibility Object

        if (  AlertResponsibilitySetRs.m_AlertSourceSetStat == adFldOK   )
          shr = spAlertResponsibilitySet->AppendSourceSetByName( CComBSTR(AlertResponsibilitySetRs.m_AlertSourceSet) ) ;     
    
 
        // Get next Alert Responsibility

        i++ ;
        AlertResponsibilitySetRs.ClearRecord() ;           // Nullify all fields
        m_spADORecordset->MoveNext() ;             // Look at next record
        m_spADORecordset->get_EOF( &RSEof) ;       // check for the EOF

      } 

    }
  

    // Allocate the Return Array Memory

    *pSize = ResponsibilitySetList.size() ;

		*pppAlertResponsibilitySet = STaskMem< IAlertResponsibilitySet* >::AllocArray (*pSize);


    // Copy the Alert Source Sets to the Return Array

    int i = 0;
    for ( ResponsibilitySetListItr = ResponsibilitySetList.begin(); ResponsibilitySetListItr != ResponsibilitySetList.end(); ++ResponsibilitySetListItr, i++ )
    {
      ResponsibilitySetListItr->CopyTo( &(*pppAlertResponsibilitySet)[i] ) ;
    }

    ATLTRACE(_T("SAlertResponsibilitySetStore::GetAllAlertResponsibilitites: Retrieved %d Alert Responsibility Sets\n"), *pSize )  ;

    return S_OK ;

  }
  catch( _com_error &e )
  {
    return m_Connect.LogError( e.Error(), _T("SAlertResponsibilitySetStore::GetAllAlertResponsibilities") ) ; 
  }
  catch ( ... )
  {
    return m_Connect.LogError( E_UNEXPECTED, _T("SAlertResponsibilitySetStore::GetAllAlertResponsibilities") ) ;
  }
}
