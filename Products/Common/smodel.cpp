#include "stdafx.h"
#include "SModel.hpp"
#include "SView.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void SModel::AddView 
(
	SView* View
)
{
	if (!View)
		return;
	//if

	for (int i = 0; i < m_Views.GetSize (); i++)
	{
		if (m_Views[i] == View)
			return;
		//if
	}//for

	OnAddView (View);

	m_Views.Add (View);
}//SModel::AddView

void SModel::UpdateAllViews 
(
	CObject* Hint
)const
{
	for (int i = 0; i < m_Views.GetSize (); i++)
		m_Views[i]->UpdateObserver (Hint,this);
	//for
}//SModel::UpdateAllViews

void SModel::RemoveView 
(
	SView* View
)const
{
	for (int i = 0; i < m_Views.GetSize (); i++)
	{
		if (View == m_Views[i])
		{
			m_Views.RemoveAt (i);
			return;
		}//if
	}//for
}//SModel::RemoveView

void SModel::CopyViews
(
	const SModel* From
)
{
	for (int i = 0; i < From->m_Views.GetSize (); i++)
		AddView (From->m_Views[i]);
	//for
}//SModel::CopyViews
