#ifndef _SUniqueID_h
#define _SUniqueID_h

#include <set>
#include <map>

// Class containing unqiue ID, guaranteed unique of linkage of static set 
// and with the lowest available value
class SUniqueID
{
private:

    static std::set <int>       sm_FreeIDs;         // Set of available IDs
    static int                  sm_MaxAvailable;    // Last value which has been put in the set
    static std::map <int,int>   sm_UsageCounts;     // Number of copies of a unique ID given out

    int                         m_MyID;

public:

    SUniqueID ();
    virtual ~SUniqueID ();

    SUniqueID (const SUniqueID& RVal);              
    SUniqueID& operator = (const SUniqueID& RVal);  

    operator int () const {return m_MyID;}
};//SUniqueID

#endif