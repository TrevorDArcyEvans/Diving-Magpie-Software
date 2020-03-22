#ifndef _SLayeredProductDoc_hpp
#define _SLayeredProductDoc_hpp

#include <typeinfo>

class SProductLayer;
class SLayeredProductView;

class SLayeredProductDoc:public COleServerDoc
{
private:

	CObArray				m_Layers;
	CString					m_VisibleFeatures;

	bool					m_Serializing;

	SLayeredProductView*	m_View;

protected:

	void BrandNewDoc ();

public:

	SLayeredProductDoc ();
	virtual ~SLayeredProductDoc ();

	const CString&	VisibleFeatures	() const {return m_VisibleFeatures;}
	void SetVisibleFeatures	(const CString& Features);

	int GetLayerCount () const {return m_Layers.GetSize ();}
	SProductLayer* GetLayer (int Idx);
	void AddLayer	 (SProductLayer* Layer);
	void DeleteLayer (SProductLayer* Layer);
	void DeleteLayer (int Idx);

	void Serialize(CArchive& ar);

	void SetView (SLayeredProductView* View) {m_View = View;}

	bool HasLayer (const type_info& Type) const;
	bool HasNonEmptyLayer (const type_info& Type) const;
};//SLayeredProductDoc

#endif

