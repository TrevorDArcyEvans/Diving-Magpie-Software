#include "stdafx.h"
#include "SMultiView.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SMultiView* SMultiView::sm_CurrentView = 0;
CObArray	SMultiView::sm_AllViews;

SMultiView::SMultiView ()
{
	sm_AllViews.Add (this);
}//SMultiView::SMultiView

SMultiView::~SMultiView ()
{
	for (int i = 0; i < sm_AllViews.GetSize (); i++)
	{
		if (sm_AllViews[i] == this)
		{
			sm_AllViews.RemoveAt (i);
			break;
		}//if
	}//for

	if (sm_CurrentView == this)
		sm_CurrentView = 0;
	//if
}//SMultiView::~SMultiView

void SMultiView::CloseOldestView ()
{
	if (sm_AllViews.GetSize () >= 1)
		((CView*)sm_AllViews[0])->SendMessage (WM_CLOSE,0,0);
	//if
}//SMultiView::CloseOldestView

SMultiView* SMultiView::CurrentView ()
{
	return sm_CurrentView;
}//SMultiView::CurrentView

void SMultiView::SetCurrentView ()
{
	sm_CurrentView = this;
}//SMultiView::SetCurrentView

void SMultiView::SaveAllPreferences ()
{
	for (int i = 0; i < sm_AllViews.GetSize (); i++)
		((SMultiView*)sm_AllViews[i])->SavePreferences ();
	//for
}//SMultiView::SaveAllPreferences

void SMultiView::Update 
(
	CObject* Hint
)
{
	OnUpdate (0,0,Hint);
}//SMultiView::Update

