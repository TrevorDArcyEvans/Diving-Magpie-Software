//---------------------------------------------------------------------------
#define MAIN    1

#include "about.h"
#include "config.h"
#include "SWutils.h"
#include "unfrag.h"
#include "UnfragFile.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FindFile"
#pragma link "FngDirWatch"
#pragma link "Regi1632"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
bool IsInFilterList(String  strFileName);
//---------------------------------------------------------------------------
bool IsInFilterList(String  strFileName)
{
for (int i = 0; i < NUM_FILTER; i++)
    {
    String      sFileExt    = ExtractFileExt(strFileName);
    String      sFilterExt  = ExtractFileExt(cFileFilter[i]);

    // note case insensitive comparison
    if (0 == sFileExt.AnsiCompareIC(sFilterExt))
        {
        return true;
        }
    }

return false;
}
//---------------------------------------------------------------------------

TUnfragWorks *UnfragWorks;
//---------------------------------------------------------------------------
__fastcall TUnfragWorks::TUnfragWorks(TComponent* Owner)
	: TService(Owner)
{
}
//---------------------------------------------------------------------------
TServiceController __fastcall TUnfragWorks::GetServiceController(void)
{
return (TServiceController) ServiceController;
}
//---------------------------------------------------------------------------
void __stdcall ServiceController(unsigned CtrlCode)
{
UnfragWorks->Controller(CtrlCode);
}
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::UnfragWorksExecute(TService *Sender)
{
while (!Terminated)
    {
    Sleep(1000);
    ServiceThread->ProcessRequests(false);
    }
}
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::UnfragWorksStart(TService *Sender,
      bool &Started)
{
String      TempStr;

switch (atoi(frmConfig->regUnfragWksSV->ReadString("Server", "Priority").c_str()))
    {
    case    e_High      :
        SetPriorityClass (GetCurrentProcess(), HIGH_PRIORITY_CLASS   );
        SetThreadPriority(GetCurrentProcess(), THREAD_PRIORITY_NORMAL);
        break;

    case    e_Idle      :
        SetPriorityClass (GetCurrentProcess(), IDLE_PRIORITY_CLASS   );
        SetThreadPriority(GetCurrentProcess(), THREAD_PRIORITY_NORMAL);
        break;

    case    e_Normal    :
        SetPriorityClass (GetCurrentProcess(), NORMAL_PRIORITY_CLASS );
        SetThreadPriority(GetCurrentProcess(), THREAD_PRIORITY_NORMAL);
        break;
    }

if (true == frmConfig->chkStartStopService->Checked)
    {
    DateTimeToString(TempStr, DATE_TIME_FORMAT,
        TDateTime::CurrentDateTime());

    LogMessage("UnfragWorks started at "
        + TempStr,
        EVENTLOG_INFORMATION_TYPE, 0, 0);

    LogMessage("started counting files at "
        + TempStr,
        EVENTLOG_INFORMATION_TYPE, 0, 0);
    }

// get (initial) list of all files in directories
// thus, existing files, probably already unfragged, will again be attempted
// to be unfragged - but that's life...
ScanFiles();

if (true == frmConfig->chkStartStopService->Checked)
    {
    DateTimeToString(TempStr, DATE_TIME_FORMAT,
        TDateTime::CurrentDateTime());

    LogMessage("finished counting files at "
        + TempStr,
        EVENTLOG_INFORMATION_TYPE, 0, 0);

    LogMessage(::String("watching over ") +
        ::String(g_strsFileList->Count) + ::String(" files"),
        EVENTLOG_INFORMATION_TYPE, 0, 0);
    }
}//TUnfragWorks::UnfragWorksStart
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::UnfragWorksStop(TService *Sender,
      bool &Stopped)
{
// if start/stop logging enabled
if (true == frmConfig->chkStartStopService->Checked)
    {
    String      TempStr;

    DateTimeToString(TempStr, DATE_TIME_FORMAT,
        TDateTime::CurrentDateTime());

    LogMessage("UnfragWorks stopped at "
        + TempStr,
        EVENTLOG_INFORMATION_TYPE, 0, 0);
    }
}//TUnfragWorks::UnfragWorksStop
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::tmrUnfragTimer(TObject *Sender)
{
// these static variables should really be member functions...
static TDateTime    dtLastDate = TDateTime::CurrentDateTime();
static int          nNumUnfrags = 0;

bool                bDirWatchState[NUM_DIR];

// return if unregistered and exceeeded trial limit
if (MAX_UNREG_UNFRAGS < nNumUnfrags &&
    false == g_bRegistered)
    {
    return;
    }

// return if no files to process
if (0 == g_strsFileList->Count)
    {
    return;
    }

if (true == UnfragToday(TDateTime::CurrentDateTime(),
                (ScheduleDayType ) frmConfig->cmbSchedDayType->ItemIndex) &&
    false == g_bIsUnfraggingNow                                                                         )
    {
    if (true == UnfragNow(TDateTime::CurrentDateTime(), dtLastDate,
                    frmConfig->dtUnfragTime->Time,
                    (ScheduleHourType ) frmConfig->cmbSchedHourType->ItemIndex))
        {
        dtLastDate = TDateTime::CurrentDateTime();
        g_bIsUnfraggingNow = true;
        nNumUnfrags++;

        String      TempStr;

        // if start/stop unfragging logging enabled
        // and not unfragging continuously (too many log messages otherwise)
        if (true == frmConfig->chkStartStopUnfrag->Checked &&
            e_Continuous != frmConfig->cmbSchedHourType->ItemIndex)
            {
            DateTimeToString(TempStr, DATE_TIME_FORMAT,
                TDateTime::CurrentDateTime());

            LogMessage("Unfragging started at "
                + TempStr,
                EVENTLOG_INFORMATION_TYPE, 0, 0);
            }

        // reset number of bytes saved and files statistics
        g_nBytesSaved = 0;

        // stop timer until we finish unfragging files in list
        tmrUnfrag->Enabled = false;

        // for each dir watcher component
        for (int i = 0; i < NUM_DIR; i++)
            {
            // save state of directory watchers
            bDirWatchState[i] = dynamic_cast<TFnugryDirWatch *>(FindComponent(dirwUnfragName[i]))->Enabled;

            // then disable them or we will get files repeatedly added to the list
            // since unfragging will generate a dir watcher event!
            dynamic_cast<TFnugryDirWatch *>(FindComponent(dirwUnfragName[i]))->Enabled = false;
            }

        // do unfragging for each file in the list
        for (unsigned int i = 0; i < (unsigned ) g_strsFileList->Count; i++)
            {
            // can only remove preview & geometry for SolidWorks files
            if (true == IsSolidWorksFile(g_strsFileList->Strings[i].c_str()))
                {
                // TDE have to do something here for Gold version
                if (true == frmConfig->chkRemovePreview->Checked)
                    {
                    //RemovePreview(1, g_strsFileList->Strings[i].c_str());
                    }

                // TDE have to do something here for Gold version
                if (true == frmConfig->chkRemoveGeom->Checked)
                    {
                    //RemoveGeometry(1, g_strsFileList->Strings[i].c_str());
                    }
                }

            // space is not saved until we unfrag
            // removing bitmap preview and display lists does not save space
            g_nBytesSaved += UnfragFile(frmConfig->sedTimeout->Value,
                                g_strsFileList->Strings[i].c_str());
            }

        // if start/stop unfragging logging enabled
        // and not unfragging continuously (too many log messages otherwise)
        if (true == frmConfig->chkStartStopUnfrag->Checked &&
            e_Continuous != frmConfig->cmbSchedHourType->ItemIndex)
            {
            DateTimeToString(TempStr, DATE_TIME_FORMAT,
                TDateTime::CurrentDateTime());

            LogMessage("Unfragging stopped at "
                + TempStr,
                EVENTLOG_INFORMATION_TYPE, 0, 0);
            }

        // if number of files examined logging enabled
        // and not unfragging continuously (too many log messages otherwise)
        if (true == frmConfig->chkFilesExamineUnfrag->Checked   &&
            e_Continuous != frmConfig->cmbSchedHourType->ItemIndex)
            {
            LogMessage(::String(g_strsFileList->Count) + " files examined",
                EVENTLOG_INFORMATION_TYPE, 0, 0);
            }

        // if bytes saved logging enabled
        // and not unfragging continuously (too many log messages otherwise)
        if (true == frmConfig->chkBytesSaved->Checked   &&
            e_Continuous != frmConfig->cmbSchedHourType->ItemIndex)
            {
            LogMessage(::String(g_nBytesSaved) + " bytes saved",
                EVENTLOG_INFORMATION_TYPE, 0, 0);
            }

        // clear list after unfraggging all files on list
        g_strsFileList->Clear();

        // for each dir watcher component
        for (int i = 0; i < NUM_DIR; i++)
            {
            // restore state of directory watchers
            dynamic_cast<TFnugryDirWatch *>(FindComponent(dirwUnfragName[i]))->Enabled = bDirWatchState[i];
            }

        // finished unfragging so restart timer
        tmrUnfrag->Enabled = true;

        g_bIsUnfraggingNow = false;
        }
    }
}//TUnfragWorks::tmrUnfragTimer
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::dirwUnfragNotify(
        TFnugryDirWatch     *DirWatch,
        int                 Action,
        const AnsiString    FileName)
{
/*
    FILE_ACTION_ADDED               = $00000001;
    FILE_ACTION_REMOVED             = $00000002;
    FILE_ACTION_MODIFIED            = $00000003;
    FILE_ACTION_RENAMED_OLD_NAME    = $00000004;
    FILE_ACTION_RENAMED_NEW_NAME    = $00000005;
*/

// prepend directory to filename to get full path to file
// note that subdirectories are included as part of the filename
String      FullFileName = DirWatch->Directory + ::String("\\") + FileName;

// have to place this variable declaration here to get around compiler bug - I think
int         Index = -1;

switch (Action)
    {
    // The file was added to the directory
    case    FILE_ACTION_ADDED               :

    // The file was modified. This can be a change in the time stamp or attributes
    case    FILE_ACTION_MODIFIED            :

    // The file was renamed and this is the new name
    case    FILE_ACTION_RENAMED_NEW_NAME    :
        // TDE have to do something here for Gold version
        #ifdef UWSV_GOLD
        if (true == IsInFilterList(FullFileName))
        #else
        if (true == IsSolidWorksFile(FullFileName))
        #endif
            {
            g_strsFileList->Add(FullFileName);
            }
        break;

    // The file was removed from the directory.
    case    FILE_ACTION_REMOVED             :

    // The file was renamed and this is the old name
    case    FILE_ACTION_RENAMED_OLD_NAME    :
        if (-1 != (Index = g_strsFileList->IndexOf(FullFileName)))
            {
            g_strsFileList->Delete(Index);
            }
        break;

    default :
        break;
    }//switch
}//TUnfragWorks::dirwUnfragNotify
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::dirwUnfrag01Notify(TObject *Sender,
      int Action, const AnsiString FileName)
{
dirwUnfragNotify(dirwUnfrag01, Action, FileName);
}
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::dirwUnfrag02Notify(TObject *Sender,
      int Action, const AnsiString FileName)
{
dirwUnfragNotify(dirwUnfrag02, Action, FileName);
}
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::dirwUnfrag03Notify(TObject *Sender,
      int Action, const AnsiString FileName)
{
dirwUnfragNotify(dirwUnfrag03, Action, FileName);
}
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::dirwUnfrag04Notify(TObject *Sender,
      int Action, const AnsiString FileName)
{
dirwUnfragNotify(dirwUnfrag04, Action, FileName);
}
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::dirwUnfrag05Notify(TObject *Sender,
      int Action, const AnsiString FileName)
{
dirwUnfragNotify(dirwUnfrag05, Action, FileName);
}
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::UnfragWorksCreate(TObject *Sender)
{
// dynamically create global file list
g_strsFileList = new TStringList;

// sort the list so we can ignore duplicates
g_strsFileList->Sorted = true;

// ignore attempts to add duplicate strings to the sorted list
g_strsFileList->Duplicates = dupIgnore;

g_bIsUnfraggingNow = false;
}
//---------------------------------------------------------------------------
void __fastcall TUnfragWorks::UnfragWorksDestroy(TObject *Sender)
{
// destroy dynamically created global file list
delete g_strsFileList;

// note that g_bRegistered will be initialised in the creation
// of the configuration form.  This is so that we can use the
// regini control
}
//---------------------------------------------------------------------------
void              TUnfragWorks::ScanFiles()
{
// reset global list of files
g_strsFileList->Clear();

// for each dir watcher
for (int i = 0; i < NUM_DIR; i++)
    {
    // if it is enabled
    if (true == dynamic_cast<TFnugryDirWatch *>(FindComponent(dirwUnfragName[i]))->Enabled)
        {
        // for each (SolidWorks) filter
        // TDE have to do something here for Gold version
        for (int j = 0; j < NUM_FILTER; j++)
            {
            // NOTE:  filter is not case sensitive
            ffilUnfrag->Filter = cFileFilter[j];

            ffilUnfrag->Directory = dynamic_cast<TFnugryDirWatch *>(FindComponent(dirwUnfragName[i]))->Directory;
            ffilUnfrag->Recurse   = dynamic_cast<TFnugryDirWatch *>(FindComponent(dirwUnfragName[i]))->WatchSubTree;

            // get list of files
            ffilUnfrag->Execute();

            // add list to global list of files
            g_strsFileList->AddStrings(ffilUnfrag->Files);
            }
        }
    }
}//TUnfragWorks::ScanFiles
//---------------------------------------------------------------------------
bool    TUnfragWorks::UnfragToday(
                TDateTime	        dtCurrentDate   ,
                ScheduleDayType     eSchedulerDay   )
{
bool    bUnfragToday = false;
int     nDayOfWeek = dtCurrentDate.DayOfWeek();

switch (eSchedulerDay)
    {
    case    e_Every_Day         :
        bUnfragToday = true;
        break;

    case    e_Every_WeekDay     :
        if (SATURDAY != nDayOfWeek  &&
            SUNDAY   != nDayOfWeek  )
            {
            bUnfragToday = true;
            }
        break;

    case    e_Every_Weekend     :
        if (SATURDAY == nDayOfWeek  ||
            SUNDAY   == nDayOfWeek  )
            {
            bUnfragToday = true;
            }
        break;

    case    e_Every_Monday      :   bUnfragToday = (MONDAY    == nDayOfWeek) ? true : false; break;
    case    e_Every_Tuesday     :   bUnfragToday = (TUESDAY   == nDayOfWeek) ? true : false; break;
    case    e_Every_Wednesday   :   bUnfragToday = (WEDNESDAY == nDayOfWeek) ? true : false; break;
    case    e_Every_Thursday    :   bUnfragToday = (THURSDAY  == nDayOfWeek) ? true : false; break;
    case    e_Every_Friday      :   bUnfragToday = (FRIDAY    == nDayOfWeek) ? true : false; break;
    case    e_Every_Saturday    :   bUnfragToday = (SATURDAY  == nDayOfWeek) ? true : false; break;
    case    e_Every_Sunday      :   bUnfragToday = (SUNDAY    == nDayOfWeek) ? true : false; break;

    case    e_Except_Monday     :   bUnfragToday = (MONDAY    == nDayOfWeek) ? false : true; break;
    case    e_Except_Tuesday    :   bUnfragToday = (TUESDAY   == nDayOfWeek) ? false : true; break;
    case    e_Except_Wednesday  :   bUnfragToday = (WEDNESDAY == nDayOfWeek) ? false : true; break;
    case    e_Except_Thursday   :   bUnfragToday = (THURSDAY  == nDayOfWeek) ? false : true; break;
    case    e_Except_Friday     :   bUnfragToday = (FRIDAY    == nDayOfWeek) ? false : true; break;
    case    e_Except_Saturday   :   bUnfragToday = (SATURDAY  == nDayOfWeek) ? false : true; break;
    case    e_Except_Sunday     :   bUnfragToday = (SUNDAY    == nDayOfWeek) ? false : true; break;

    default     :
        // Write to error log
        LogMessage("Unexpected error in TUnfragWorks::UnfragToday",
            EVENTLOG_INFORMATION_TYPE, 0, 0);
        bUnfragToday = false;
        break;
    }

return bUnfragToday;
}//TUnfragWorks::UnfragToday
//---------------------------------------------------------------------------
bool    TUnfragWorks::UnfragNow(
                TDateTime	        dtCurrentDate   ,
                TDateTime	        dtLastDate      ,
                TDateTime	        dtScheduleTime  ,
                ScheduleHourType    eSchedulerHour  )
{
if (dtCurrentDate > dtLastDate + TDateTime(eSchedulerHour, 0, 0, 0))
    {
    return true;
    }
else
    {
    return false;
    }
}//TUnfragWorks::UnfragNow
//---------------------------------------------------------------------------

