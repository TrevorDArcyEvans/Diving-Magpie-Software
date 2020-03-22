//---------------------------------------------------------------------------
#ifndef unfragH
#define unfragH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <ExtCtrls.hpp>
#include "FindFile.hpp"
#include "FngDirWatch.hpp"
#include "Regi1632.hpp"
//---------------------------------------------------------------------------
enum ScheduleHourType {
        e_Continuous    = 0,
        e__1_hourly     = 1,
        e__2_hourly     = 2,
        e__4_hourly     = 4,
        e__6_hourly     = 6,
        e__8_hourly     = 7,
        e_12_hourly     = 12,
        e_24_hourly     = 24
        };

enum ScheduleDayType {
        e_Every_Day,
        e_Every_WeekDay,
        e_Every_Weekend,

        e_Every_Monday,
        e_Every_Tuesday,
        e_Every_Wednesday,
        e_Every_Thursday,
        e_Every_Friday,
        e_Every_Saturday,
        e_Every_Sunday,

        e_Except_Monday,
        e_Except_Tuesday,
        e_Except_Wednesday,
        e_Except_Thursday,
        e_Except_Friday,
        e_Except_Saturday,
        e_Except_Sunday
        };

enum PriorityType {
        e_High    = 0,
        e_Idle       ,
        e_Normal
        };

#define     SUNDAY                  1
#define     MONDAY                  2
#define     TUESDAY                 3
#define     WEDNESDAY               4
#define     THURSDAY                5
#define     FRIDAY                  6
#define     SATURDAY                7

#define     MAX_UNREG_UNFRAGS       5

#define     DATE_TIME_FORMAT        "dd mmm yyyy hh:nn:ss"
//---------------------------------------------------------------------------
class TUnfragWorks : public TService
{
__published:    // IDE-managed Components
    TTimer *tmrUnfrag;
    TFindFile *ffilUnfrag;
    TFnugryDirWatch *dirwUnfrag01;
    TFnugryDirWatch *dirwUnfrag02;
    TFnugryDirWatch *dirwUnfrag03;
    TFnugryDirWatch *dirwUnfrag04;
    TFnugryDirWatch *dirwUnfrag05;
    TRegistry1632 *regUnfrag;
    void __fastcall UnfragWorksExecute(TService *Sender);
    void __fastcall UnfragWorksStart(TService *Sender, bool &Started);
    void __fastcall UnfragWorksStop(TService *Sender, bool &Stopped);
    void __fastcall tmrUnfragTimer(TObject *Sender);
    void __fastcall UnfragWorksCreate(TObject *Sender);
    void __fastcall UnfragWorksDestroy(TObject *Sender);
    void __fastcall dirwUnfrag01Notify(TObject *Sender, int Action,
          const AnsiString FileName);
    void __fastcall dirwUnfrag02Notify(TObject *Sender, int Action,
          const AnsiString FileName);
    void __fastcall dirwUnfrag03Notify(TObject *Sender, int Action,
          const AnsiString FileName);
    void __fastcall dirwUnfrag04Notify(TObject *Sender, int Action,
          const AnsiString FileName);
    void __fastcall dirwUnfrag05Notify(TObject *Sender, int Action,
          const AnsiString FileName);

private:        // User declarations
    void __fastcall dirwUnfragNotify(
                        TFnugryDirWatch     *DirWatch,
                        int                 Action,
                        const AnsiString    FileName);

public:         // User declarations
	__fastcall TUnfragWorks(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);

	friend void __stdcall ServiceController(unsigned CtrlCode);

    void                ScanFiles();

    bool    UnfragToday(
                TDateTime	        dtCurrentDate   ,
                ScheduleDayType     eSchedulerDay   );

    bool    UnfragNow(
                TDateTime	        dtCurrentDate   ,
                TDateTime	        dtLastDate      ,
                TDateTime	        dtScheduleTime  ,
                ScheduleHourType    eSchedulerHour  );


};
//---------------------------------------------------------------------------
extern PACKAGE TUnfragWorks *UnfragWorks;
//---------------------------------------------------------------------------
#endif
