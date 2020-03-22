#ifndef __SFloatListFile_hpp
#define __SFloatListFile_hpp

#include <afx.h>

class CString;

class SFloatListFile
{
private:

	 CStdioFile	m_File;
	 bool		m_EOF;

public:

	SFloatListFile (const CString& FileName);
	~SFloatListFile ();

	bool EndOfFile () const;

	double Get ();
};//SFloatListFile

#endif

