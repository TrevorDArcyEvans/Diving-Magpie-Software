/* CExtendedList_h include file
Copyright:  (c) Sigmex B.V., 2000. All rights reserved.

Description:
   This file contains the definition of the CExtendedList class that provides a convenient wrapper for use with the CListCtrl ActiveX component.

$History: ExtendedList.h $
 * 
 * *****************  Version 14  *****************
 * User: Jasper       Date: 21-10-00   Time: 17:12
 * Updated in $/CMIDS/Projects/Common
 * Allow click to edit label in overridden OnClick
 * 
 * *****************  Version 12  *****************
 * User: Jasper       Date: 22-08-00   Time: 14:29
 * Updated in $/CMIDS/Projects/Common
 * Add flag to indicate we are in the middle of a sort.
 * Solve a problem with sorting when there's a single column.
 * Make select for whole row work automatically.
 * 
 * *****************  Version 10  *****************
 * User: Jasper       Date: 8-08-00    Time: 21:21
 * Updated in $/CMIDS/Projects/Common
 * Restore previous sort mechanism. Extend to sort numerically or by
 * user-defined functor.
 * Allow message reflections to work when embedded in ATL Composite
 * Control
 * 
 * *****************  Version 8  *****************
 * User: Jasper       Date: 26-07-00   Time: 15:52
 * Updated in $/CMIDS/Projects/Common
 * Add column header sorting
   [00]     MR    09Feb2000   Created
   [01]     HB    24Mar2000   Tabs replaced by spaces
   [02]     MR    11Apr2000   AddRow changed to AddSelectedItems
   [03]     MR    12Apr2000   SetColumnWidth changed to SetColumnWidths so that the CListCtrl functionality remains accessible
   [04]     MR    14Apr2000   Changed convinient to convenient.
   [05]     MR    28Apr2000   Changed delimiters in SetColumnHeaders and AddRow to default to ",".
   [06]     JK    12May2000   Added include file for CListCtrl base class
*/

#ifndef CEXTENDEDLIST_H_
#define CEXTENDEDLIST_H_

#include <afxcmn.h>

#undef min						// MFC macro screws up STL function
#undef max						// MFC macro screws up STL function

#include <valarray>
#include <map>
#include <set>
#include "SAutoNullPtr.h"

class CExtendedList : public CListCtrl
{
public:

//	Abstract bass class for transfer filters. Override AllowThrough with your own rules
	class SFilterFunctor {public: virtual bool AllowThrough (DWORD ItemData) const = 0;};

//  Abstract base class for column sorting. Override Compare with you rules to compare individual string items. Return 0 if l == r, -1 if l < r and +1 if l > r
    class SSortFunctor {public: virtual int Compare (const CString& l,const CString& r) const = 0;};

//  Functor for numerical sort. Is also a singleton
    class SNumericSortFunctor:public SSortFunctor
    {
    private:

        static SNumericSortFunctor* sm_Instance;

        SNumericSortFunctor () {}

    public:

        static SNumericSortFunctor* Instance ();
        
        int Compare (const CString& l,const CString& r) const;
    };//SNumericSortFunctor

private:
//  Class to pass sort parameters down to comparison function
    class SSortRules 
    {
    public:

        int             m_Column;
        bool            m_Ascending;
        CExtendedList*  m_List;

        SSortRules (int Col,bool Asc,CExtendedList* List):m_Column (Col),m_Ascending (Asc),m_List (List) {}
    };

//  Class to store user item data plus our own internal data
    class SBiggerItemData
    {
    public:

        int             m_Index;
        DWORD           m_BaseData;

        SBiggerItemData (int Index,DWORD Base):m_Index (Index),m_BaseData (Base) {}
    };

    bool TryEditLabel (int ItemIdx);   // Start label edit if click was approriate. Return true if it was appropriate
    
    int GetHorzOffset (int PageWidth,int FieldWidth,int Align = A_X_MIDDLE) const;
	int GetVertOffset (int PageHeight,int FieldHeight,int Align = A_TOP) const;
	void PrintRow (CDC&	DC,int Row,int x,int y,const std::valarray <int>& Widths) const;

    bool m_SelectRow;                           // Selct whole rows rather than just leftmost item
    bool m_SelectStyleChanged;                  // m_SelectRow has been changed

    static int CALLBACK SortCallback (LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);

    int                 m_SortColumn;           // Column that last sort was done on
    bool                m_LastSortAscending;    // Sort was for ascend (or descending if false) on last column 
    bool                m_IsSorting;            // We are in the middle of a sort

    typedef std::map <int,SAutoNullPtr <SSortFunctor> > SortFunctorMap;    // Maps special sorting rules onto a column
    
    SortFunctorMap      m_SortFunctors;

    std::set <int> m_SelectedItems;
    bool IsSelected (int Index);
    void AddSelection (int Index);
    void RemoveSelection (int Index);

//  Returns the item for which the pointer is currently anywhere on the row.
//  -1 if nothing
//  If something found, parameter returns the full row rectangle
    int GetRowSelectedItem (CRect& Rect) const;

protected:

    //{{AFX_MSG(CExtendedList)
    afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:

    enum PrintAlignments {A_LEFT		= 1,	// Numbers chosen to kepp
						  A_X_MIDDLE	= 2,	// horizontal and vertical
						  A_RIGHT		= 3,	// bits separate
						  A_TOP			= 4,
						  A_Y_MIDDLE	= 8,
						  A_BOTTOM		= 12};	

    CExtendedList();
    virtual ~CExtendedList();
    void SetColumnHeaders (const CString& headers, const CString& delimiters = _T (","));
    void SetColumnHeaders (UINT StringResource, const CString& delimiters = _T (","));
 
    BOOL ProcessWindowMessage (HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& lResult);

//	Returns the number columns
	int ColumnCount () const;

//	Returns the actual row added, in case the list is sorted
	int AddRow(int rownumber, const CString& items, const CString& delimiter = _T (","));

//	Returns the actual row added, in case the list is sorted
	int AddRow(int rownumber, UINT StringResource, const CString& delimiter = _T (","));

    void SetColumnWidths (int size);

//  Select whole rows rather than just the leftmost item. Won't show up until next selection
    bool SetRowSelect (bool SelectRow) {m_SelectRow = SelectRow; m_SelectStyleChanged = true;}

//	Removes selected items form the given list and adds them to this one. 
//	If this list has more columns, the padding fields will be added
//	Item data is optionally transferred
    void AddSelectedItems
	(
		CListCtrl*				FromList,						// List copying from
		bool					TransferItemData = true,		// Copy over the item data DWORD
		const SFilterFunctor*	Filter		     = 0,			// Filter of which to transfer
		const CString&			PadWith			 = _T (""),		// Strings to pad extra fields
		const CString&			Delimiter		 = _T (",")		// Delimiter on ParWith
	);

//	Get the header text for the given column
	CString GetColumnHeader (int Column) const;

//	Does it have coulumn headers?
	bool ColumnHeaderShown () const;

//	Get the print widths of columns
	std::valarray <int> CalcColumnWidths (CDC& DC) const;

//	Print the contents of the list
	void Print (HDC DCIn,const CString& Title = _T("")) const;
	void Print (CDC&	DC,
				int		Left = 0,
				int		Top = 0,
				int		Right = -1,
				int		Bottom = -1,
				int		Align = A_X_MIDDLE|A_TOP) const;

    void SortByColumn (int ColNo,bool Ascending);
    void SortByColumn (int ColNo);                              // This overload toggles the last direction used on the column, starting with ascending

    void SetSortFunctor (int ColNo,SSortFunctor* Functor);      // Use non default sorting for this column
    void SetNumericSort (int ColNo,bool Active = true);         // E-Z way to set or unset numeric sort on a column

    bool IsSorting () const {return m_IsSorting;}               // We are in the middle of a sort
};

#endif
