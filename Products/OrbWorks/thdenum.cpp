//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "process.h"
#include "ThdEnum.h"
#include <rw/stdmutex.h>
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TEnum::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TEnum::TEnum(bool CreateSuspended)
    : TThread(CreateSuspended)
{
Priority = tpLowest;
FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void __fastcall TEnum::Execute()
{
//---- Place thread code here ----
while (!Terminated)
    {
    LockSWinfo.acquire();

    // reset flag for SW
    bSW_Running = false;

    // now try and find SW
    EnumWindows((WNDENUMPROC ) OrbWorksEnumFunc, (LPARAM ) 1);

    LockSWinfo.release();

    // run every 1.5 seconds
    Sleep(1500);
    }
}
//---------------------------------------------------------------------------
