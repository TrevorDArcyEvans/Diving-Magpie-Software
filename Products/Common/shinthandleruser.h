#ifndef _SHintHandlerUser_h
#define _SHintHandlerUser_h

class SHintHandlerUser:public IDataServiceEvents
{
public:

	STDMETHOD (QueryInterface) (REFIID iid,void ** ppvObject) {return S_OK;}
	STDMETHOD_ (ULONG,AddRef) () {return 0;}
	STDMETHOD_ (ULONG,Release) () {return 0;} 
};

#endif

