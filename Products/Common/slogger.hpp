#ifndef __SLogger_hpp
#define __SLogger_hpp

#include <afx.h>

class SLogger
{
private:

	static SLogger*	sm_Instance;

	CStdioFile		m_File;
	bool			m_Open;

	SLogger ();

public:

	static SLogger*	Instance ();

	void StartLogging (const CString& Filename);
	
	void Log (const CString& MesS);
	void Log (const CString& MesS,unsigned MesL);
};//SLogger

#endif

