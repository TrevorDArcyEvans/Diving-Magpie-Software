#ifndef _SCComBSTR_H
#define _SCComBSTR_H

// Version of CComBSTR to be used with std::set and other troublesome containers
// The problem is that std::set uses the address-of operator, which is overloaded
// in CComBSTR to return a BSTR. This causes a type msimatch in std::set.
// Here, & is overloaded back to the usual form.
// We may discover we need some other constructors to make this work fully.
// NEVER use & explicitly on this
// If the problem occurs for types other than CComBSTR, a template could be used here
//
// Usage should be:
//
// std::set <SCComBSTR> MySet;
//
// insert and other operations should just use a CComBSTR: CComBSTR
//
// CComBSTR MyStr = _T ("Hello");
// MySet.insert (MyStr);
//
class SCComBSTR : public CComBSTR
{
public:

    SCComBSTR (const CComBSTR& RVal):CComBSTR (RVal) {}

    SCComBSTR* operator & () {return this;}
};//SCComBSTR

#endif


