#ifndef __SCreatableRichEditDoc_hpp
#define __SCreatableRichEditDoc_hpp

#include <afxrich.h>

class SCreatableRichEditDoc:public CRichEditDoc
{
DECLARE_DYNCREATE (SCreatableRichEditDoc);

public:

	CRichEditCntrItem* CreateClientItem (REOBJECT* preo) const;
};//SCreatableRichEditDoc

#endif

