//---------------------------------------------------------------------------

#include "CPUspeed.h"

//---------------------------------------------------------------------------
// GetCPUSpeed
// returns 
//      double
//          CPU speed in MHz
double GetCPUSpeed()
{
    const int   DelayTime = 500; // measure time in ms

    DWORD       TimerHi, TimerLo;
    int         PriorityClass, Priority;

    PriorityClass   = GetPriorityClass(GetCurrentProcess());
    Priority        = GetThreadPriority(GetCurrentThread());

    SetPriorityClass (GetCurrentProcess, REALTIME_PRIORITY_CLASS        );
    SetThreadPriority(GetCurrentThread , THREAD_PRIORITY_TIME_CRITICAL  );

    Sleep(10);
    asm
        {
        dw 310Fh // rdtsc
        mov TimerLo, eax
        mov TimerHi, edx
        }
    Sleep(DelayTime);
    asm
        {
        dw 310Fh // rdtsc
        sub eax, TimerLo
        sbb edx, TimerHi
        mov TimerLo, eax
        mov TimerHi, edx
        }

    SetThreadPriority(GetCurrentThread (), Priority     );
    SetPriorityClass (GetCurrentProcess(), PriorityClass);

    return TimerLo / (1000.0 * DelayTime);
}
//---------------------------------------------------------------------------
