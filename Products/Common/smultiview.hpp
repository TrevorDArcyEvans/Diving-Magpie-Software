#ifndef __SMultiView_hpp
#define __SMultiView_hpp

#include <afxwin.h>
#include "SView.hpp"

class SMultiView:public CView,public SView
{
private:

	static SMultiView*  sm_CurrentView;
	static CObArray		sm_AllViews;

public:

	SMultiView ();
	virtual ~SMultiView ();

	static SMultiView* CurrentView ();
	static void SaveAllPreferences ();
	static void CloseOldestView ();

	virtual void SavePreferences () const {}
	virtual void LoadPreferences () {}

	void Update (CObject* Hint);

	void UpdateObserver (CObject* Hint,const SModel* Model) {Update (Hint);}

	void SetCurrentView ();
};//SMultiView

#endif

