#ifndef __SView_hpp
#define __SView_hpp

#include <afxtempl.h>

class CObject;
class SModel;

class SView
{
protected:

	SView () {}

public:

	virtual ~SView () {}

	virtual void UpdateObserver (CObject* Hint,const SModel* Model) = 0;
};//SView

typedef CArray <SView*,SView*> SViewArray;

#endif



