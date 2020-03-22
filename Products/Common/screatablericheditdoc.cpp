#include "SCreatableRichEditDoc.hpp"

IMPLEMENT_DYNCREATE (SCreatableRichEditDoc,CRichEditDoc)

CRichEditCntrItem* SCreatableRichEditDoc::CreateClientItem 
(
	REOBJECT* preo
)const
{
	return new CRichEditCntrItem (preo,(CRichEditDoc*)this);
}//SCreatableRichEditDoc::CreateClientItem
