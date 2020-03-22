#include "stdafx.h"
#include <afx.h>
#include "SFloatListFile.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SFloatListFile::SFloatListFile 
(
	const CString& FileName
)
:m_File (FileName,CFile::modeRead|CFile::typeText),
 m_EOF  (false)
{
}//SFloatListFile::SFloatListFile

SFloatListFile::~SFloatListFile ()
{
}//SFloatListFile::~SFloatListFile

bool SFloatListFile::EndOfFile () const
{
	return m_EOF;
}//SFloatListFile::EndOfFile

double SFloatListFile::Get ()
{
	CString Line;

	m_EOF = !m_File.ReadString (Line);

	return atof	(Line);
}//SFloatListFile::Get

