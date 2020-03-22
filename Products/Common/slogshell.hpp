#ifndef _SLogShell_hpp
#define _SLogShell_hpp

class ILogger;

class SLogShell
{
private:

	static SLogShell*	sm_Instance;

	ILogger*	m_Logger;

	SLogShell ();
	~SLogShell ();

public:

	static SLogShell* Instance ();
	static void Destroy ();

	void LogMessage (const CString& Message,const CString& SourceApp,short Severity = -1) const;
};//SLogShell

#endif

