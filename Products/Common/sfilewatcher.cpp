#include "stdafx.h"
#include "SFileWatcher.hpp"
#include "SMethodLock.hpp"

#include "SLogError.h"

SMultiFileWatcher* SMultiFileWatcher::sm_Instance = 0;

SMultiFileWatcher::~SMultiFileWatcher ()
{
  try
  {
  	for (int i = 0; i < m_Watchers.GetSize (); i++)
	  	m_Watchers[i]->Kill ();
	//for
  }
  catch(...)
  {
    return ;
  }

}//SMultiFileWatcher::~SMultiFileWatcher

SMultiFileWatcher* SMultiFileWatcher::Instance ()
{
  try
  {
  	if (!sm_Instance)
	  	sm_Instance = new SMultiFileWatcher;
  	//if
  
	  return sm_Instance;
  }
  catch(...)
  {
    return 0;
  }
}//SMultiFileWatcher::Instance

void SMultiFileWatcher::AddPath 
(
	const CString&			PathName,
	IFileWatcherNotifiable*	Notifiee
)
{
  try
  {
  	SMethodLock Lock (m_Sema);

  	SFileWatcher* Watcher = 0;

  	for (int i = 0; i < m_Watchers.GetSize (); i++)
  	{
  		if (m_Watchers[i]->GetPath () == PathName)
  		{
  			Watcher = m_Watchers[i];
  			break;
  		}//if
  	}//for

  	if (!Watcher)
  	{
  		Watcher = new SFileWatcher (PathName);
  		m_Watchers.Add (Watcher);
  		Watcher->Run ();
  	}//if

  	Watcher->AddNotifiee (Notifiee);
  }
  catch(...)
  {
    return ;
  }
}//SMultiFileWatcher::AddPath

void SMultiFileWatcher::RemovePath 
(
	const CString&			PathName,
	IFileWatcherNotifiable*	Notifiee
)
{
  try
  {
	  SMethodLock Lock (m_Sema);

	  SFileWatcher* Watcher = 0;
	  
	  int i;
	  for (i = 0; i < m_Watchers.GetSize (); i++)
	  {
		  if (m_Watchers[i]->GetPath () == PathName)
		  {
			  Watcher = m_Watchers[i];
			  break;
		  }//if
	  }//for

	  if (!Watcher)
		  return;
	  //if

	  Watcher->RemoveNotifiee (Notifiee);

	  if (Watcher->NotifieeCount () == 0)
	  {
		  Watcher->Kill ();
		  m_Watchers.RemoveAt (i);
	  }//if
  }
  catch(...)
  {
    return ;
  }
}//SMultiFileWatcher::RemovePath

void SMultiFileWatcher::RemoveNotifiee
(
	IFileWatcherNotifiable* Notifiee
)
{
  try
  {
  	for (int i = m_Watchers.GetSize () - 1; i >= 0; i--)
  	{
  		m_Watchers[i]->RemoveNotifiee (Notifiee);

  		if (m_Watchers[i]->NotifieeCount () == 0)
  		{
  			m_Watchers[i]->Kill ();
  			m_Watchers.RemoveAt (i);
  		}//if
  	}//for
  }
  catch(...)
  {
    return ;
  }
}//SMultiFileWatcher::RemoveNotifiee
		
int SFileWatcher::NotifieeCount () const
{
  try
  {
  	SMethodLock Lock (m_Sema);

  	return m_Notifiees.GetSize ();
  }
  catch(...)
  {
    return 0 ;
  }
}//SFileWatcher::NotifieeCount

void SFileWatcher::AddNotifiee    
(
	IFileWatcherNotifiable* Notifiee
)
{
  try
  {
  	SMethodLock Lock (m_Sema);

  	for (int i = 0; i < m_Notifiees.GetSize (); i++)
  	{
  		if (m_Notifiees[i] == Notifiee)
  			return;
  		//if
  	}//for
  
  	m_Notifiees.Add (Notifiee);
  }
  catch(...)
  {
    return ;
  }
}//SFileWatcher::AddNotifiee

void SFileWatcher::RemoveNotifiee 
(
	const IFileWatcherNotifiable* Notifiee
)
{
  try
  {
  	SMethodLock Lock (m_Sema);

  	for (int i = 0; i < m_Notifiees.GetSize (); i++)
  	{
  		if (m_Notifiees[i] == Notifiee)
  		{
  			m_Notifiees.RemoveAt (i);
  			return;
  		}//if
  	}//for
  }
  catch(...)
  {
    return ;
  }
}//SFileWatcher::RemoveNotifiee
			
void SFileWatcher::EntryPoint ()
{
  try
  {
	  DWORD	Status; 
	  HANDLE	Handles[2];

	  CString NoTrailSlash;

	  if (m_Path[m_Path.GetLength () - 1] == '\\')
		  NoTrailSlash = m_Path.Left (m_Path.GetLength () - 1);
	  else
		  NoTrailSlash = m_Path;
	  //if

  //	Watch the directory for file creation and deletion. 
 	  Handles[0] = FindFirstChangeNotification (NoTrailSlash,
										    FALSE,
										    FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_LAST_WRITE);
		  
	  if (Handles[0] == INVALID_HANDLE_VALUE) 
	      return;
	  //if
 
	  Handles[1] = m_KillEvent;

  //#define _NT_KLUDGE

  #ifdef _NT_KLUDGE
	  DWORD Timeout = 300000;
  #else
	  DWORD Timeout = INFINITE;
  #endif

	  CString OldFiles;

	  while (true) 
	  { 
		  Status = WaitForMultipleObjects (2,Handles,FALSE,Timeout);
		  
		  switch (Status)
		  {
			  default:	return;

			  case WAIT_OBJECT_0:
			  {
				  FindNextChangeNotification (Handles[0]);

				  m_Sema.Lock ();

				  for (int i = 0; i < m_Notifiees.GetSize (); i++)
					  m_Notifiees[i]->OnFileChange (m_Path);
				  //for

				  m_Sema.Unlock ();
		  
				  break;
			  }//case

			  case WAIT_TIMEOUT:
			  {
				  CString Files = GetFileString (NoTrailSlash);

				  if (OldFiles != Files)
				  {
					  OldFiles = Files;

					  m_Sema.Lock ();

					  for (int i = 0; i < m_Notifiees.GetSize (); i++)
						  m_Notifiees[i]->OnFileChange (m_Path);
					  //for

					  m_Sema.Unlock ();
				  }//if
			  
				  break;
			  }//case
		  }//switch
	  }//while
  LogEvent(_T("SFileWatcher::EntryPoint out of while loop"));
  }//try
  catch(...)
  {
    LogEvent(_T("Unknown error in SFileWatcher::EntryPoint"));
    return ;
  }
}//SFileWatcher::EntryPoint

CString SFileWatcher::GetFileString 
(
	const CString&	Path
)const
{

  try
  {
    CString RetVal ;
    WIN32_FIND_DATA   fd ;
    CString PathSlash ( Path + _T("\\") ) ;
    CString EOFileName( _T(";") ) ;

    HANDLE  hndl =  ::FindFirstFile ( CString( PathSlash + _T("*.*")), &fd );
    if ( hndl != INVALID_HANDLE_VALUE )
    {
      BOOL Okay = TRUE ;
	    while ( Okay )
      {
        CString FileName( fd.cFileName ) ;

        // Make it the full path name of each file delimited by ';'
        // Filter out the special files

        if ( !( (FileName == _T(".")) || ( FileName == _T("..")) ) ) 
		      RetVal += ( PathSlash + FileName + EOFileName ) ;

        Okay = ::FindNextFile( hndl, &fd ) ;
      } //while

      ::FindClose( hndl ) ;
    }

	  return RetVal;
  }
  catch(...)
  {
    return CString(_T(""));
  }

}//SFileWatcher::GetFileString


// SFileWatcher::GetFileList
// returns a list (actually STL vector) of all file names in the specified
// directory.
//
// Each file name is relative to the specified directory.  Thus, if
// the directory is fully qualified, then each file name will also be 
// fully qualified.
//
// parameters
//      Path
//          path to directory without trailing backslash
//
// returns
//      std::vector <CString>
//          list of file names in the specified directory
//          see description above for details
//
//          empty list if there was a problem - beware!
//
// notes
//      this function is a *lot* faster than SFileWatcher::GetFileString()
//      when there are a *lot* (2000+) of files in the directory.  This is 
//      because GetFileString() returns a _single_, semicolon separated 
//      string of all the filenames.  Unfortunately, every time a file
//      name is appended to the end of this (single) string, memory must be 
//      reallocated.  This turns out to be a very expensive process.  In
//      contrast, GetFileList() returns an array of strings, so memory only
//      has to be allocated for each string.  This is a lot faster.
std::vector <CString> SFileWatcher::GetFileList
(
    const CString&      Path
) const
{
    std::vector <CString>           RetVal ;

    try
        {
        WIN32_FIND_DATA                 fd ;
        CString                         PathSlash ( Path + _T("\\") ) ;

        HANDLE                          hndl =  ::FindFirstFile ( CString( PathSlash + _T("*.*")), &fd );
        if ( hndl != INVALID_HANDLE_VALUE )
            {
            BOOL                Okay = TRUE ;
            while (Okay)
                {
                CString             FileName( fd.cFileName ) ;

                // Filter out the special files
                if ( !( (FileName == _T(".")) || ( FileName == _T("..")) ) )
                    {
                    CString             FullFileName = PathSlash + FileName;
                    RetVal.push_back(FullFileName);
                    }

                Okay = ::FindNextFile( hndl, &fd ) ;
                } //while

          ::FindClose( hndl ) ;
            }
        }
    catch (...)
        {
        // probably got here on an STL exception
        // something bad has happened, so return an empty list
        RetVal.clear();
        }

        return RetVal;
}
