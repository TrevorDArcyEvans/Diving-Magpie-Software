// -------------------------------------------------------------------
//
//     Filename: CcItem.h
//  Description: Implements the CControlItem class which serves as the
//               foundation class for this applications SolidWorks
//               event handlers.
//
// -------------------------------------------------------------------

//////
//////  YOU DO NOT NEED TO CHANGE THIS FILE. SEE HANDLEEVENTS.H FOR DETAILS
//////
#ifndef CCONTROLITEM_H
#define CCONTROLITEM_H

class CControlItem : public CCmdTarget
{
public:
    virtual ~CControlItem();
    virtual LPUNKNOWN   GetInterfaceHook(const void* iid);
    virtual BOOL OnCreate(LPDISPATCH      pDisp);

protected: // Only derived classes may be created.
    CControlItem();
    virtual void    Release(OLECLOSE dwCloseOption = OLECLOSE_NOSAVE);

    LPOLEOBJECT             m_lpObject; // in case you want direct access to the OLE object
    LPCONNECTIONPOINT       m_pConnPt;
    DWORD                   m_dwEventConnection;
    IID                     m_iidEvents;

protected: // IDispatch declaration
    BEGIN_INTERFACE_PART(EventHandler, IDispatch)
        INIT_INTERFACE_PART(CControlItem, EventHandler)
        STDMETHOD(GetTypeInfoCount)(unsigned int*);
        STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**);
        STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, unsigned int, LCID, DISPID*);
        STDMETHOD(Invoke)(DISPID, REFIID, LCID, unsigned short, DISPPARAMS*,
                          VARIANT*, EXCEPINFO*, unsigned int*);
    END_INTERFACE_PART(EventHandler)

DECLARE_INTERFACE_MAP()
DECLARE_EVENTSINK_MAP()
};

#endif

// --------------------------------
//  End of CcItem.h
// --------------------------------
