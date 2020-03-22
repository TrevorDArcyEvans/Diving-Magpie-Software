#include "stdafx.h"
#include "SLogger.hpp"
#include <afx.h>

SLogger* SLogger::sm_Instance = 0;

SLogger::SLogger ()
:m_Open (false)
{
}//SLogger::SLogger

SLogger* SLogger::Instance ()
{
	if (!sm_Instance)
		sm_Instance = new SLogger;
	//if

	return sm_Instance;
}//SLogger::Instance

void SLogger::StartLogging 
(
	const CString& Filename
)
{
	if (m_Open)
	{
		Log ("New Start");
		return;
	}//if

	m_Open = true;

	m_File.Open (Filename,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite|CFile::typeText);
	Log ("Opened");
}//SLogger::StartLogging

void SLogger::Log 
(
	const CString& MesS
)
{
	if (!m_Open)
		return;
	//if

	CString Time;

	Time.Format (" %d",GetTickCount ());

	m_File.WriteString (MesS + Time + "\r\n");
	m_File.Flush ();
}//SLogger::Log

void SLogger::Log 
(
	const CString&	MesS,
	unsigned		MesL
)
{
	if (!m_Open)
		return;
	//if

	CString Out;

	Out.Format (MesS + ": %d",MesL);

	m_File.WriteString (Out + "\r\n");
	m_File.Flush ();
}//SLogger::Log



