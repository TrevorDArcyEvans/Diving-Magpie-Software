#ifndef __IContextUser_hpp
#define __IContextUser_hpp

class IContextUser
{
public:

	virtual void OnCommand (unsigned Cmd) = 0;

//	DON'T TRY AN ON UPDATE. IT DOESN'T WORK (at least not in VC++v5.0)

};//IContextUser

#endif

