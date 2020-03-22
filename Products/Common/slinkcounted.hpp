#ifndef __SLinkCounted_hpp
#define __SLinkCounted_hpp

class SLinkCounted
{
private:

	int	m_Count;

public:

	SLinkCounted ();
	virtual ~SLinkCounted () {}

	void Link ();
	void Unlink ();
};//SLinkCounted

#endif
