#ifndef __STableReader_hpp
#define __STableReader_hpp

#include <afxtempl.h>

class STableReader
{
private:

	CString m_Filename;
	int		m_Columns;
	int		m_NumberColumn;
	UINT	m_ResID;

	bool	m_Loaded;

	CArray <CStringArray*,CStringArray*>	m_Table;

	void LoadFromFile ();
	void LoadFromResource ();

public:

	STableReader (const CString& Filename,int Columns = 1,int NumberColumn = -1);
	STableReader (UINT ResID,int Columns = 1,int NumberColumn = -1);
	virtual ~STableReader ();

	void Load ();

	void Clear ();

	CString GetEntry (int Row,int Column = 0) const;
};//STableReader

#endif

