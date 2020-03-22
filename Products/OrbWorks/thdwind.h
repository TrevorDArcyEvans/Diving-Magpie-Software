//---------------------------------------------------------------------------
#ifndef ThdWindH
#define ThdWindH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TWindow : public TThread
{
private:
protected:
    void __fastcall Execute();
public:
    __fastcall TWindow(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
