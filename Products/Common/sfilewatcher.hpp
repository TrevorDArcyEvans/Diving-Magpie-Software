#ifndef __SFileWatcher_hpp
#define __SFileWatcher_hpp

#include "stdafx.h"
#include "SThread.hpp"


#ifndef __AFX_H__  // Including MFC
#include "MFCStringImpl.h"
using NotMFC::CString ;
#else
#include <afxtempl.h>
#include <afxmt.h>
#endif

#include <vector>

class IFileWatcherNotifiable
{
public:

	virtual void OnFileChange (const CString& Path) = 0;
};//IFileWatcherNotifiable

#ifndef __AFX_H__  // Not including MFC
typedef CSimpleArray <IFileWatcherNotifiable*> SNotifieeArray;
#else
typedef CArray <IFileWatcherNotifiable*,IFileWatcherNotifiable*> SNotifieeArray;
#endif

class SFileWatcher:public SThread
{
private:

	CString						m_Path;
	SNotifieeArray				m_Notifiees;
	mutable SCriticalSection	m_Sema;




public:

	SFileWatcher (const CString& Path):m_Path (Path) {SetSelfDestruct (true);}
	virtual ~SFileWatcher () {}

	CString GetPath       () const {return m_Path;}
	int     NotifieeCount () const;

	void AddNotifiee    (IFileWatcherNotifiable* Notifiee);
	void RemoveNotifiee (const IFileWatcherNotifiable* Notifiee);

	void EntryPoint ();

	CString GetFileString (const CString& Path) const;

	std::vector <CString> GetFileList (const CString& Path) const;

};//SFileWatcher


#ifndef __AFX_H__    // Not including MFC
typedef CSimpleArray <SFileWatcher*> SFileWatcherArray;
#else
typedef CArray <SFileWatcher*,SFileWatcher*> SFileWatcherArray;
#endif


class SMultiFileWatcher
{
private:

	SFileWatcherArray			m_Watchers;

	mutable SCriticalSection			m_Sema;

	static SMultiFileWatcher*	sm_Instance;

public:

	SMultiFileWatcher () {}
	virtual ~SMultiFileWatcher ();

	void AddPath (const CString& PathName,IFileWatcherNotifiable* Notifiee);
	void RemovePath (const CString& PathName,IFileWatcherNotifiable* Notifiee);
	void RemoveNotifiee (IFileWatcherNotifiable* Notifiee);

	static SMultiFileWatcher* Instance ();
};//SMultiFileWatcher

#endif

