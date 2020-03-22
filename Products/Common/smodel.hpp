#ifndef __SModel_hpp
#define __SModel_hpp

#include <afx.h>
#include <afxcoll.h>
#include "SView.hpp"

class SModel:public CObject
{
private:

	mutable SViewArray m_Views;

	virtual void OnAddView (SView* View) {}

protected:

	SModel () {}

public:

	virtual ~SModel () {}

	void AddView (SView* View);
	void RemoveView (SView* View) const;
	void UpdateAllViews (CObject* Hint) const;
	void CopyViews (const SModel* From);
};//SModel

#endif


