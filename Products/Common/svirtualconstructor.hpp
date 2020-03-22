#ifndef __SVirtualConstructor_hpp
#define __SVirtualConstructor_hpp

#include <String.h>

class SVCLink
{
protected:

	SVCLink*	m_NextLink;

	virtual void* DoConstructObject (LPCTSTR Named) {return 0;}

public:

	SVCLink (int AddToChain = 1);
	virtual ~SVCLink ();

	void* ConstructObject (LPCTSTR Named);
	void AddLink (SVCLink* NewLink);
};//SVCLink

class SVirtualConstructor
{
protected:

	SVCLink	m_FirstLink;

	static SVirtualConstructor*	sm_Instance;

	SVirtualConstructor ():m_FirstLink (0) {}
	~SVirtualConstructor ();

public:

	void* ConstructObject (LPCTSTR Named);
	void  AddLink         (SVCLink* NewLink);

	static SVirtualConstructor* Instance ();

	static void Destroy ();
};//SVirtualConstructor

#define DECLARE_VIRTUAL_CONSTRUCTOR_BASE virtual LPCTSTR vctor_GetName () const {return _T ("");}

#define DECLARE_VIRTUAL_CONSTRUCTOR \
static SVCLink* sm_vctor_link;\
LPCTSTR vctor_GetName () const;

#define IMPLEMENT_VIRTUAL_CONSTRUCTOR(ConstructeeName)\
class SDerivedLink##ConstructeeName : public SVCLink\
{\
protected:\
	void* DoConstructObject (LPCTSTR Named)\
	{\
		if (_tcscmp (Named,_T (#ConstructeeName)) == 0) return new ConstructeeName;\
		else return 0;\
	}\
};\
SVCLink* ConstructeeName::sm_vctor_link = new SDerivedLink##ConstructeeName;\
LPCTSTR ConstructeeName::vctor_GetName () const {return _T (#ConstructeeName);}

#endif

