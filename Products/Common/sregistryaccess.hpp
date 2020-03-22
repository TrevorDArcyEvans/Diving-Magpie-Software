/*
History:
    [01]    TDE     19May00     changed default key from 'Sigmex BV' to 'Sigmex'
*/

#ifndef __SRegistryAccess_hpp
#define __SRegistryAccess_hpp

#ifndef _AFX
#include "MFCStringImpl.h"
using NotMFC::CString;
#endif

class SRegistryAccess
{
private:

    HKEY        m_Root;
    CString     m_Key;

public:

    SRegistryAccess (HKEY Root = HKEY_CURRENT_USER,const CString& Key = _T ("Software\\Sigmex"));        // [01]
    virtual ~SRegistryAccess () {}

    void SetRoot (HKEY Root);
    void SetKey  (const CString& Key);

    void    WriteString   (const CString& SubKey,const CString& Entry,const CString& Value) const;
    CString ReadString    (const CString& SubKey,const CString& Entry,const CString& Default = _T ("")) const;

    void    WriteInt      (const CString& SubKey,const CString& Entry,int Value  ) const;
    int     ReadInt       (const CString& SubKey,const CString& Entry,int Default) const;

    void    WriteDouble   (const CString& SubKey,const CString& Entry,double Value) const;
    double  ReadDouble    (const CString& SubKey,const CString& Entry,double Default) const;

    bool    ReadBinary    (const CString& SubKey,const CString& Entry,void* Buffer,unsigned long Size);

    int     GetValueCount (const CString& SubKey) const;
    bool    GetStringPair (const CString& SubKey,int Idx,CString& ValueLabel,CString& Value) const;

    bool    DeleteValue   (const CString& SubKey,const CString& Entry) const;
};//SRegistryAccess

#endif

