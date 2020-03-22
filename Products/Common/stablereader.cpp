#define NO_TABLE_FILES

#include "stdafx.h"
#include "STableReader.hpp"
#include "SString.hpp"
#include "SException.hpp"

#ifdef NO_TABLE_FILES
#include "SRegistry.hpp"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int _Count = 0;

STableReader::STableReader 
(
	const CString&	Filename,
	int				Columns,
	int				NumberColumn
)
:m_Filename		(Filename),
 m_ResID		(0),
 m_Columns		(Columns),
 m_NumberColumn	(NumberColumn),
 m_Loaded		(false)
{
}//STableReader::STableReader

STableReader::STableReader
(
	UINT	ResID,
	int		Columns,
	int		NumberColumn
)
:m_ResID		(ResID),
 m_Columns		(Columns),
 m_NumberColumn	(NumberColumn),
 m_Loaded		(false)
{
}//STableReader::STableReader

void STableReader::Load ()
{
	if (m_Loaded)
		return;
	//if

	m_Loaded = true;

	if (m_ResID)
		LoadFromResource ();
	else
		LoadFromFile ();
	//if
}//STableReader::Load

void STableReader::LoadFromResource ()
{
	HRSRC hRes = ::FindResource (AfxGetResourceHandle(),(char*)m_ResID,_T("table"));

	if (!hRes)
		throw new SException ("Unable to load table resouce.");
	//if

	HGLOBAL hData = ::LoadResource(AfxGetResourceHandle(),hRes);

	if (!hData)
		throw new SException ("Unable to load table resouce.");
	//if

	SString Data = (char*)::LockResource(hData);

	SElementExtractor Ext = Data.ExtractStart ("\r\n");

	int Index = 0;
	int ColCount = (m_NumberColumn == -1)?m_Columns:m_Columns + 1;

	while (Ext.Active ())
	{
		SString Line = Data.ExtractNext (Ext);

		if (Line == "")
			continue;
		//if

		CStringArray* Row = new CStringArray;
		_Count++;

		for (int i = 0; i < ColCount; i++)
		{
			CString Element = Line.Element ("\t",i);

			if ((m_NumberColumn == -1) || (i < m_NumberColumn))
				Row->SetAtGrow (i,Element);
			else if (i == m_NumberColumn)
				Index =  atoi (Element);
			else // i > NumberColumn
				Row->SetAtGrow (i - 1,Element);
			//if
		}//for

		if (Index < m_Table.GetSize () && m_Table[Index])
			delete Row;
		else
		{
			int OldSize = m_Table.GetSize ();

			m_Table.SetAtGrow (Index,Row);

			for (int Fill = m_Table.GetSize (); Fill < Index; Fill++)
				m_Table[Fill] = 0;
			//for
		}//if

		if (m_NumberColumn == -1)
			Index++;
		//if
	}//while
}//STableReader::LoadFromResource

#ifdef NO_TABLE_FILES

void STableReader::LoadFromFile ()
{
	CStdioFile File;

	if (File.Open (SRegistry::Instance ()->m_GeneralDataPath + m_Filename,CFile::modeRead|CFile::typeText))
	{
		SString Line;

		int Index = 0;
		int ColCount = (m_NumberColumn == -1)?m_Columns:m_Columns + 1;

		while (File.ReadString (Line))
		{
			CStringArray* Row = new CStringArray;
			_Count++;

			for (int i = 0; i < ColCount; i++)
			{
				CString Element = Line.Element ("\t",i);

				if ((m_NumberColumn == -1) || (i < m_NumberColumn))
					Row->SetAtGrow (i,Element);
				else if (i == m_NumberColumn)
					Index =  atoi (Element);
				else // i > NumberColumn
					Row->SetAtGrow (i - 1,Element);
				//if
			}//for

			m_Table.SetAtGrow (Index,Row);

			if (m_NumberColumn == -1)
				Index++;
			//if
		}//while
	}
	else
		throw new SException ("Unable to find table file " + m_Filename);
	//if
}//STableReader::LoadFromFile

#else

void STableReader::LoadFromFile ()
{
	ASSERT (FALSE);
}

#endif

STableReader::~STableReader ()
{
	Clear ();
}//STableReader::~STableReader

void STableReader::Clear ()
{
	for (int i = 0; i < m_Table.GetSize (); i++)
		delete m_Table[i];
	//for

	m_Table.RemoveAll ();
}//STableReader::Clear

CString STableReader::GetEntry 
(
	int Row,
	int Column
)const
{
	if (!m_Loaded)
		((STableReader*)this)->Load ();
	//if

	if (Row >= m_Table.GetSize ())
		throw new SException ("Requested row off end of table.");
	//if

	CStringArray* RowPtr = m_Table[Row];

	if (Column >= RowPtr->GetSize ())
		throw new SException ("Requested column off side of table.");
	//if

	return RowPtr->GetAt (Column);
}//STableReader::GetEntry


