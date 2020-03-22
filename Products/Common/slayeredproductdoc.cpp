#include "stdafx.h"
#include <afxole.h>

#include "SLayeredProductDoc.hpp"
#include "SProductLayer.hpp"

SLayeredProductDoc::SLayeredProductDoc ()
:m_Serializing (false) 
{
}//SLayeredProductDoc::SLayeredProductDoc

SLayeredProductDoc::~SLayeredProductDoc ()
{
	for (int i = 0; i < m_Layers.GetSize (); i++)
		delete m_Layers[i];
	//for
}//SLayeredProductDoc::~SLayeredProductDoc

void SLayeredProductDoc::BrandNewDoc ()
{
	m_VisibleFeatures = "/*/";
}//SLayeredProductDoc::BrandNewDoc

void SLayeredProductDoc::Serialize
(
	CArchive& ar
)
{
	m_Serializing = true;

	SProductLayer::SetLatestView (m_View);

	m_Layers.Serialize (ar);

	if (ar.IsStoring ())
	{
		ar << m_VisibleFeatures;
	}
	else
	{
		ar >> m_VisibleFeatures;
	}//if

	m_Serializing = false;
}//SLayeredProductDoc::Serialize

void SLayeredProductDoc::SetVisibleFeatures	
(
	const CString& Features
)
{
	if (m_Serializing)
		return;
	//if
	
	if (Features != m_VisibleFeatures)
	{
		m_VisibleFeatures = Features;
		SetModifiedFlag ();
	}//if
}//SLayeredProductDoc::VisibleFeatures

SProductLayer* SLayeredProductDoc::GetLayer 
(
	int Idx
)
{
	if (m_Layers.GetSize  () > Idx)
		return (SProductLayer*)m_Layers[Idx];
	else
		return 0;
	//if
}//SLayeredProductDoc::GetLayer

void SLayeredProductDoc::AddLayer	 
(
	SProductLayer* Layer
)
{
	for (int i = 0; i < m_Layers.GetSize (); i++)
	{
		if (Layer == m_Layers[i])
			return;
		//if
	}//for

	m_Layers.Add (Layer);
}//SLayeredProductDoc::AddLayer

void SLayeredProductDoc::DeleteLayer 
(
	SProductLayer* Layer
)
{
	for (int i = 0; i < m_Layers.GetSize (); i++)
	{
		if (Layer == m_Layers[i])
		{
			delete m_Layers[i];
			m_Layers.RemoveAt (i);
			return;
		}//if
	}//for
}//SLayeredProductDoc::DeleteLayer

void SLayeredProductDoc::DeleteLayer 
(
	int Idx
)
{
	if (m_Layers.GetSize () > Idx)
	{
		delete m_Layers[Idx];
		m_Layers.RemoveAt (Idx);
	}//if
}//SLayeredProductDoc::DeleteLayer

bool SLayeredProductDoc::HasLayer 
(
	const type_info& Type
)const
{
	for (int i = 0; i < m_Layers.GetSize (); ++i)
	{
		if (typeid (*m_Layers[i]) == Type)
			return true;
		//if
	}//for

	return false;
}//SLayeredProductDoc::HasLayer

bool SLayeredProductDoc::HasNonEmptyLayer 
(
	const type_info& Type
)const
{
	for (int i = 0; i < m_Layers.GetSize (); ++i)
	{
		if (typeid (*m_Layers[i]) == Type)
		{
			((SProductLayer*)m_Layers[i])->SetView (m_View);

			return !((SProductLayer*)m_Layers[i])->IsEmpty ();
		}//if
	}//for

	return false;
}//SLayeredProductDoc::HasNonEmptyLayer


