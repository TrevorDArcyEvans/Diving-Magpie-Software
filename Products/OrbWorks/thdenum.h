//---------------------------------------------------------------------------
#ifndef ThdEnumH
#define ThdEnumH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TEnum : public TThread
{
private:
protected:
    void __fastcall Execute();
public:
    __fastcall TEnum(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
