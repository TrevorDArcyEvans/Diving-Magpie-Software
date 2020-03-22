#include "stdafx.h"
#include "SUniqueID.h"

// incremental change to total number of available IDs
//
// FIX ME!      artificially restricted ChunkSize to fix problems in AOW
// The AOW dynamic menus exhibited 'strange', specifically graying of the dynamic menu items,
// when the ChunkSize was allowed to exceed this restriction (200).
//
// In the AOW, we allocate a range of 200 for the command IDs for 
// the dynamic menus.  Typically, the dynamic menus will allow 
// bulletins etc to be displayed.  When the bulletin associated with
// a menu item expires, we must remove it from the dynamic menus.
// In this case, the command ID for the just expired menu can then
// be reused.  Unfortunately, this limit of 200 is a compiled in limit and
// is defined (indirectly) in AOW\Resource.h
//
// Thus:
//      ChunkSize <= ID_DYNAMIC_MENU_LAST - ID_DYNAMIC_MENU_FIRST
//          ID_DYNAMIC_MENU_LAST  = 33027   <--------- from 
//          ID_DYNAMIC_MENU_FIRST = 32827   <--------- from AOW\Resource.h
//
// see also
//      AOW project, CMainFrame::AppendToMenu()
static const int        ChunkSize = 200;

// list of available IDs
// when an ID is taken, it is removed from this list
std::set <int>          SUniqueID::sm_FreeIDs;

// total number of available IDs.  Thus, the last free ID will be equal
// to this value ie
//      sm_FreeIDs.end() == sm_MaxAvailable
// will be incremented by ChunkSize if we exhaust them and this new block
// of IDs will be added to the available list (sm_FreeIDs)
int                     SUniqueID::sm_MaxAvailable = 0;

// tracks usage of each of the IDs
// when the usage count of an ID drops to 0, then it is added to the list of
// free IDs (sm_FreeIDs) and then removed from this list (sm_UsageCounts)
//      key   = unique ID
//      value = usage count
std::map <int,int>      SUniqueID::sm_UsageCounts;

SUniqueID::SUniqueID ()
{
    if (sm_FreeIDs.size () == 0) 
    {
        // None free: allocate a new batch
        for (int i = 0; i < ChunkSize; ++i)
            sm_FreeIDs.insert (++sm_MaxAvailable);
        //for
    }//if

    std::set <int>::iterator it = sm_FreeIDs.begin ();  // Get first available

    m_MyID = *it;                                       // Allocate to us
    sm_FreeIDs.erase (it);                              // And remove from set

    sm_UsageCounts[m_MyID] = 1;       // Mark our usage
}//SUniqueID::SUniqueID

SUniqueID::SUniqueID 
(
    const SUniqueID& RVal
)
:m_MyID (RVal.m_MyID) 
{
    // Increment usage
    int     Temp = sm_UsageCounts[m_MyID];

    Temp++;
    sm_UsageCounts[m_MyID] = Temp;
}//SUniqueID::SUniqueID

SUniqueID& SUniqueID::operator = 
(
    const SUniqueID& RVal
)
{
    if (&RVal == this)
    {
        m_MyID = RVal.m_MyID;

        // Increment usage
        int     Temp = sm_UsageCounts[m_MyID];

        Temp++;
        sm_UsageCounts[m_MyID] = Temp;
    }//if

    return *this;
}//SUniqueID::operator =

SUniqueID::~SUniqueID ()
{
    int     Temp = sm_UsageCounts[m_MyID];

    // Decrement usage
    Temp--;
    sm_UsageCounts[m_MyID] = Temp;

    if (sm_UsageCounts[m_MyID] == 0)
    {
//      Last one down
        sm_FreeIDs.insert (m_MyID);     // Give it back
        sm_UsageCounts.erase (m_MyID);
    }//if
}//SUniqueID::~SUniqueID
