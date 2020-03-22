/*
History:
    [01]    TDE     17Jul00     fixed bug with not supporting NotMFC::CString
*/

#include "stdafx.h"
#include "SRegistryAccess.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SRegistryAccess::SRegistryAccess 
(
	HKEY			Root,
	const CString&	Key
)
:m_Root (Root),
 m_Key  (Key)
{
}//SRegistryAccess::SRegistryAccess

void SRegistryAccess::SetRoot 
(
	HKEY Root
)
{
	m_Root = Root;
}//SRegistryAccess::SetRoot

void SRegistryAccess::SetKey  
(
	const CString& Key
)
{
	m_Key = Key;
}//SRegistryAccess::SetKey

void SRegistryAccess::WriteString 
(
	const CString& SubKey,
	const CString& Entry,
	const CString& Value
)const
{
	HKEY hk;
	DWORD dis;
	
	CString FullKey = m_Key;

	if (SubKey != _T (""))
		FullKey += _T ("\\") + SubKey;
	//if

	RegCreateKeyEx (m_Root,
		            FullKey,
					0,
					_T (""),
					REG_OPTION_NON_VOLATILE,
					KEY_SET_VALUE,
					0,&hk,&dis);

    RegSetValueEx (hk,Entry,0,REG_SZ,(const BYTE*)(LPCTSTR)Value,sizeof(TCHAR) * (Value.GetLength () + 1));     // [01]

	RegFlushKey (hk);
}//SRegistryAccess::WriteString

CString SRegistryAccess::ReadString  
(
	const CString& SubKey,
	const CString& Entry,
	const CString& Default
)const
{
	HKEY hk;

	TCHAR  Buf [1024];
	DWORD Type = REG_SZ;
	DWORD Size = 1024;

	CString FullKey = m_Key;

	if (SubKey != _T (""))
		FullKey += _T ("\\") + SubKey;
	//if

	long Err1 = RegOpenKeyEx (m_Root,
	              FullKey,
				  0,
				  KEY_QUERY_VALUE,
				  &hk);
	
	long Err = RegQueryValueEx (hk,Entry,0,&Type,(BYTE*)Buf,&Size);

	RegCloseKey (hk);

	if (Err)
		return Default;
	else
		return Buf;
	//if
}//SRegistryAccess::ReadString

bool SRegistryAccess::ReadBinary
(
	const CString&	SubKey,
	const CString&	Entry,
	void*			Buffer,
	unsigned long	Size
)
{
	HKEY hk;

	DWORD Type = REG_BINARY;

	CString FullKey = m_Key;

	if (SubKey != _T (""))
		FullKey += _T ("\\") + SubKey;
	//if

	RegOpenKeyEx (m_Root,
	              FullKey,
				  0,
				  KEY_QUERY_VALUE,
				  &hk);
	
	long Err = RegQueryValueEx (hk,Entry,0,&Type,(unsigned char*)Buffer,&Size);

	RegCloseKey (hk);

	return !Err;
}//SRegistryAccess::ReadBinary

int SRegistryAccess::ReadInt  
(
	const CString&	SubKey,
	const CString&	Entry,
	int				Default
)const
{
	HKEY hk;

	DWORD Type = REG_DWORD;
	DWORD RetVal;
	DWORD Size = sizeof (RetVal);

	CString FullKey = m_Key;

	if (SubKey != _T (""))
		FullKey += _T ("\\") + SubKey;
	//if

	RegOpenKeyEx (m_Root,
	              FullKey,
				  0,
				  KEY_QUERY_VALUE,
				  &hk);
	
	long Err = RegQueryValueEx (hk,Entry,0,&Type,(unsigned char*)&RetVal,&Size);

	RegCloseKey (hk);

	if (Err)
		return Default;
	else
		return RetVal;
	//if
}//SRegistryAccess::ReadInt

void SRegistryAccess::WriteInt	
(
	const CString&	SubKey,
	const CString&	Entry,
	int				Value
)const
{
	HKEY hk;
	DWORD dis;
	
	CString FullKey = m_Key;

	if (SubKey != _T (""))
		FullKey += _T ("\\") + SubKey;
	//if

	RegCreateKeyEx (m_Root,
		            FullKey,
					0,
					_T (""),
					REG_OPTION_NON_VOLATILE,
					KEY_SET_VALUE,
					0,&hk,&dis);

	RegSetValueEx (hk,Entry,0,REG_DWORD,(unsigned char*)&Value,sizeof (Value));

	RegFlushKey (hk);
}//SRegistryAccess::WriteInt

double SRegistryAccess::ReadDouble	
(
	const CString&	SubKey,
	const CString&	Entry,
	double			Default
)const
{
	CString DefStr;

	DefStr.Format (_T ("%g"),Default);

    CString Str = ReadString (SubKey,Entry,DefStr);

	TCHAR* Dum;			// Dummy for _tcstod

    return _tcstod (Str,&Dum);
}//SRegistryAccess::ReadDouble

void SRegistryAccess::WriteDouble	
(
	const CString&	SubKey,
	const CString&	Entry,
	double			Value
)const
{
	CString ValStr;

	ValStr.Format (_T ("%g"),Value);

	WriteString (SubKey,Entry,ValStr);
}//SRegistryAccess::WriteDouble

int SRegistryAccess::GetValueCount 
(
	const CString& SubKey
)const
{
	CString FullKey = m_Key;

	if (SubKey != _T (""))
		FullKey += _T ("\\") + SubKey;
	//if

	HKEY hk;

	RegOpenKeyEx (m_Root,
	              FullKey,
				  0,
				  KEY_QUERY_VALUE,
				  &hk);
	
	DWORD RetVal = 0;

	RegQueryInfoKey (hk,0,0,0,0,0,0,&RetVal,0,0,0,0);

	RegCloseKey (hk);

	return RetVal;
}//SRegistryAccess::GetValueCount

bool SRegistryAccess::GetStringPair 
(
	const CString&	SubKey,
	int				Idx,
	CString&		ValueLabel,
	CString&		Value
)const
{
	CString FullKey = m_Key;

	if (SubKey != _T (""))
		FullKey += _T ("\\") + SubKey;
	//if

	HKEY hk;

	RegOpenKeyEx (m_Root,
	              FullKey,
				  0,
				  KEY_QUERY_VALUE,
				  &hk);

	TCHAR LabelBuf[1024];
	TCHAR ValueBuf[1024];

	DWORD LabelSize = 1024;
	DWORD ValueSize = 1024;

	DWORD Type;

	long Err = ::RegEnumValue (hk,Idx,LabelBuf,&LabelSize,0,&Type,(BYTE*)ValueBuf,&ValueSize);

	RegCloseKey (hk);

	if (!Err && (Type == REG_SZ))
	{
		ValueLabel  = LabelBuf;
		Value       = ValueBuf;

		return true;
	}
	else
		return false;
	//if
}//SRegistryAccess::GetStringPair

bool SRegistryAccess::DeleteValue 
(
	const CString& SubKey,
	const CString& Entry
)const
{
	HKEY hk;
	DWORD dis;
	
	CString FullKey = m_Key;

	if (SubKey != _T (""))
		FullKey += _T ("\\") + SubKey;
	//if

	RegCreateKeyEx (m_Root,
		            FullKey,
					0,
					_T (""),
					REG_OPTION_NON_VOLATILE,
					KEY_SET_VALUE,
					0,&hk,&dis);

	bool RetVal = ::RegDeleteValue (hk,Entry) == ERROR_SUCCESS;

	RegCloseKey (hk);

	return RetVal;
}//SRegistryAccess::DeleteValue

