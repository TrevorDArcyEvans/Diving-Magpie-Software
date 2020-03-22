//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
#include "enum.h"
#include "init.h"
#include "main.h"
#include "swOle.h"
#include "process.h"
#include "ThdWind.h"
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
//      void __fastcall TWindow::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TWindow::TWindow(bool CreateSuspended)
    : TThread(CreateSuspended)
{
Priority = tpLowest;
FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void __fastcall TWindow::Execute()
{
//---- Place thread code here ----
while (!Terminated)
    {
    LockSWinfo.acquire();

    if (IsWindow        (swWindow) != 0 &&
        IsWindowVisible (swWindow) != 0 &&
        IsWindowEnabled (swWindow) != 0 &&
        IsIconic        (swWindow) == 0 )       // !=0 means window is NOT iconic
        {
        bSW_Running = true;
        }
    else
        {
        bSW_Running = false;
        }

    LockSWinfo.release();

    // run every 0.1 seconds
    Sleep(10);
    }
}
//---------------------------------------------------------------------------

