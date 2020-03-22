#ifndef _SHints_hpp
#define _SHints_hpp

class SNewLayersHint:public CObject
{
private:

	int	m_First;
	int m_Last;

public:

	SNewLayersHint (int First,int Last):m_First (First),m_Last (Last) {}
	virtual ~SNewLayersHint() {}

	int GetFirst () const {return m_First;}
	int GetLast  () const {return m_Last;}
};//SNewLayersHint

class STimeWindowHint:public CObject
{
public:

	STimeWindowHint () {}
	virtual ~STimeWindowHint () {}
};//STimeWindowHint

#endif
