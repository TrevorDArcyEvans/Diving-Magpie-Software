/* CExtendedList.cpp source file
Copyright:  (c) Sigmex B.V., 2000. All rights reserved.

  Description:
  This file contains the source of the CExtendedList class that provides a convenient wrapper for use with the CListCtrl ActiveX component.
  
    $History: ExtendedList.cpp $
 * 
 * *****************  Version 17  *****************
 * User: Jasper       Date: 21-10-00   Time: 17:12
 * Updated in $/CMIDS/Projects/Common
 * Allow click to edit label in overridden OnClick
 * 
 * *****************  Version 16  *****************
 * User: Tim          Date: 25-09-00   Time: 16:26
 * Updated in $/CMIDS/Projects/Common
 * Added ability to switch off sorting
    * 
    * *****************  Version 13  *****************
    * User: Jasper       Date: 22-08-00   Time: 18:16
    * Updated in $/CMIDS/Projects/Common
    * Only fix sort header problem when there's definately just one column
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
    * *****************  Version 7  *****************
    * User: Jasper       Date: 26-07-00   Time: 15:52
    * Updated in $/CMIDS/Projects/Common
    * Add column header sorting
    [00]     MR    09Feb2000   Created.
    [01]     HB    24Mar2000   Function headers added and redundant "deletes" removed.
    [02]     MR    24Mar2000   Function headers updated and AddRow changed to AddSelectedItems.
    [03]     MR    12Apr2000   SetColumnWidth changed to SetColumnWidths so that the CListCtrl functionality remains accessible.
    [04]     MR    14Apr2000   SetColumnWidths changed to set column width from left to right, setting columns widths from right to left didn't funciton properly, changed convinient to convenient.
    [05]     MR    28Apr2000   Changed <stdafx.h> to "stdafx.h", added null pointer check at start of AddSelectedItems, removed memory leak in delete of local variables in SetColumnHeaders.
*/

#include "stdafx.h"
#include "ExtendedList.h"
#include "SString.hpp"


//////////////////////////////////////////////////////////////////////
// CExtendedList Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/* CExtendedList - Constructor 
*/
CExtendedList::CExtendedList() 
:CListCtrl (), 
m_SortColumn (-1), 
m_LastSortAscending (false),
m_SelectRow (true),
m_SelectStyleChanged (true),
m_IsSorting (false)
{
}

/* CExtendedList - Destructor
*/
CExtendedList::~CExtendedList()
{
}

BEGIN_MESSAGE_MAP (CExtendedList, CListCtrl)
//{{AFX_MSG_MAP (CExtendedList)
ON_NOTIFY_REFLECT (NM_CLICK, OnClick)
ON_NOTIFY_REFLECT (LVN_COLUMNCLICK, OnColumnClick)
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

BOOL CExtendedList::ProcessWindowMessage 
(
 HWND        hWnd,
 UINT        uMsg,
 WPARAM      wParam,
 LPARAM      lParam,
 LRESULT&    lResult
 )
{
   if (uMsg == WM_NOTIFY)
   {
      LPNMHDR Header = (LPNMHDR)lParam;
      
      if (Header->hwndFrom == m_hWnd)
      {
         switch (Header->code)
         {
         default:                break;
         case NM_CLICK:          OnClick (Header, &lResult); break;
         case LVN_COLUMNCLICK:   OnColumnClick (Header,&lResult); break;
         }//switch
      }//if
   }//if
   return FALSE;
}

//  Returns the item for which the pointer is currently anywhere on the row.
// -1 if nothing
// If something found, parameter returns the full row rectangle
int CExtendedList::GetRowSelectedItem 
(
    CRect& Rect
)const
{
   //  Get the current mouse location and convert it to client coordinates.
   DWORD position = GetMessagePos ();
   
   CPoint point (LOWORD (position),HIWORD (position));
   
   ScreenToClient (&point);
   
   //  Get indexes of the first and last visible items in listview control.
   int StartIndex = GetTopIndex ();
   int last_visible_index = StartIndex + GetCountPerPage ();
   
   if (last_visible_index > GetItemCount ())
      last_visible_index = GetItemCount ();
   //if
   
   //  Loop until number visible items has been reached.
   for (int Idx = StartIndex; Idx <= last_visible_index; Idx++)
   {
      // Get the bounding rectangle of an item.
      // If the mouse location is within the bounding rectangle of the item,
      // you know you have found the item that was being clicked.
      GetItemRect (Idx,&Rect,LVIR_BOUNDS);
      
      if (Rect.PtInRect (point))
         return Idx;
      //if
   }//while
   
   return -1;  // Not found
}//CExtendedList::GetRowSelectedItem

void CExtendedList::OnClick (NMHDR * pNMHDR, LRESULT * pResult)
{
// This is the best place to catch the select style change
    if (m_SelectStyleChanged)
    {
        if (m_SelectRow)
            SetExtendedStyle (GetExtendedStyle () | LVS_EX_FULLROWSELECT);  // Select whole row
        else
            SetExtendedStyle (GetExtendedStyle () & ~LVS_EX_FULLROWSELECT); // Select leftmost item
        //if

        m_SelectStyleChanged = false;
    }//if
   
    CRect RowRect;
   
    int SelectedIndex = GetRowSelectedItem (RowRect);    // Get the index and bouding rect of selected row
   
    if (SelectedIndex >= 0)
    {
        if (IsSelected (SelectedIndex))
        {
//          Already selected. Might be an attempt to deselect or to edit label
            if (!TryEditLabel (SelectedIndex))
            {
//              Okay, it wasn't so deselect it
                SetItemState (SelectedIndex, 0, LVIS_SELECTED | LVIS_FOCUSED);
                RemoveSelection (SelectedIndex);
            }//if
        }
        else
        {
            SetItemState (SelectedIndex, 
                          LVIS_SELECTED | LVIS_FOCUSED, 
                          LVIS_SELECTED | LVIS_FOCUSED);

            if (GetSelectedCount () == 1)
                m_SelectedItems.clear ();
            //if

            AddSelection (SelectedIndex);
        }//if
    }//if

   *pResult = 0;
}

bool CExtendedList::TryEditLabel 
(
    int ItemIdx
)
{
//  First, check we are already selected
    if (!IsSelected (ItemIdx))
        return false;
    //if

//  Check we have edit label style
    if (!(GetStyle () & LVS_EDITLABELS))
        return false;
    //if

//  Get the pointer position
    DWORD Pos = GetMessagePos ();

    CPoint Point (LOWORD (Pos),HIWORD (Pos));

    ScreenToClient (&Point);

    CRect Rect;

//  Get the rect of the label
    GetItemRect (ItemIdx,Rect,LVIR_LABEL);

    if (Rect.PtInRect (Point))
    {
//      Dooooo it
        EditLabel (ItemIdx);
        return true;
    }
    else
        return false;
    //if
}//CExtendedList::TryEditLabel

void CExtendedList::OnColumnClick (NMHDR * pNMHDR, LRESULT * pResult)
{
   LPNMLISTVIEW Data = (LPNMLISTVIEW) pNMHDR; 
   
   SortByColumn (Data->iSubItem);
   
   *pResult = 0;
}

void CExtendedList::SetColumnHeaders(UINT headers, const CString& delimiters)
{
   CString HeadersString;
   
   HeadersString.LoadString (headers);
   
   SetColumnHeaders (HeadersString,delimiters);
}

/* SetColumnHeaders - Set the column headers of the list control

  Input : headers    - CString with column headers
  delimited by delimeter characters in "delimiters",
  e.g. "Car,Boat,Bike". Delimiter after last header
  is not required
  delimiters - CString with delimter, e.g. ","
*/
void CExtendedList::SetColumnHeaders (const CString& headers, const CString& delimiter)
{
   SString HeadStr = headers;	// Transfer to SString for extra features
   
   //	Initialise the extraction
   SElementExtractor Ext = HeadStr.ExtractStart (delimiter);	
   
   int index = 0;
   
   while (Ext.Active ())
   {
      SString header = HeadStr.ExtractNext (Ext);	// Get the column
      
      LVCOLUMN lvcolumn;
      
      lvcolumn.mask = LVCF_TEXT;
      lvcolumn.fmt = LVCFMT_LEFT;
      lvcolumn.pszText = (LPTSTR)(LPCTSTR)header;
      
      InsertColumn (index ++, &lvcolumn);
   }//while
   
   SetColumnWidths (LVSCW_AUTOSIZE_USEHEADER);
}

int CExtendedList::AddRow(int rownumber,UINT items, const CString& delimiters)
{
   CString ItemsString;
   
   ItemsString.LoadString (items);
   
   return AddRow (rownumber,ItemsString,delimiters);
}

/* AddRow - Add a row to the list

  Input : rownumber   - zero-based row number
  items       - CString with the row items
  delimited by delimiter charactes in "delimiters",
  e.g. "Car,Boat,Bike". Delimiter after last header
  is not required
  delimiters  - CString with delimter, e.g. ","
*/
int CExtendedList::AddRow(int rownumber, const CString& items, const CString& delimiter)
{
   SString ItemsStr = items;	// Transfer to SString for extra features
   
   //	Initialise the extraction
   SElementExtractor Ext = ItemsStr.ExtractStart (delimiter);	
   
   SString item = ItemsStr.ExtractNext (Ext);	// Get the first item
   
   int Column = 0;
   
   LV_ITEM lvitem;
   
   lvitem.mask		= LVIF_TEXT;
   lvitem.iItem	= rownumber;
   lvitem.iSubItem = Column;
   lvitem.pszText	= (LPTSTR)(LPCTSTR)item;
   
   //	If list is sorted added position may not be same as requested, so remember the return
   int RetVal = InsertItem (&lvitem);
   
   while (Ext.Active ())
   {
      Column++;
      item = ItemsStr.ExtractNext (Ext);	// Get the next item
      SetItemText (RetVal,Column, item);
   }//while
   
   //  Refresh sorting
   if (m_SortColumn != -1)
      SortByColumn (m_SortColumn,m_LastSortAscending);
   //if
   
   SetColumnWidths (LVSCW_AUTOSIZE_USEHEADER);
   
   return RetVal;	// The actual row
}

/* SetColumnWidths - Make all columns the same width

  Input : size - width of columns
  May be set to a fixed size or one of the following variables:
  LVSCW_AUTOSIZE - Automatically sizes the column. 
  LVSCW_AUTOSIZE_USEHEADER  - Automatically sizes the column to fit the header text.
  If you use this value with the last column,
  its width is set to fill the remaining width of the list view control. 
*/
void CExtendedList::SetColumnWidths(int size)
{
   for (int i = 0; i < GetHeaderCtrl ()->GetItemCount (); i ++)
   {
      SetColumnWidth (i, size);
   }
}

void CExtendedList::AddSelectedItems 
(
	CListCtrl*				FromList,				// List copying from
   bool					TransferItemData,		// Copy over the item data DWORD
   const SFilterFunctor*	Filter,					// Filter of which to transfer
   const CString&			PadWith,				// Strings to pad extra fields
   const CString&			Delimiter				// Delimiter on ParWith
   )
{
   if (FromList)
   {
      SString PadElements = PadWith;	// Convert to SString which has Element () method
      
      int FromColumnCount = FromList->GetHeaderCtrl ()->GetItemCount ();	// Columns in from list
      int ToColumnCount   = this->ColumnCount ();							// Columns in to list
      
      POSITION position = FromList->GetFirstSelectedItemPosition (); 
      
      //		Iterate through selected items
      while (position)
      {
         //			Get index of the selected item and move position on
         int index		= FromList->GetNextSelectedItem (position);
         DWORD ItemData	= FromList->GetItemData (index);
         
         //			Only transfer if the filter lets us (or if there's no filter)
         if (!Filter || Filter->AllowThrough (ItemData))
         {
            CString itemtext;
            
            //				Run through the columns
            for (int i = 0; i < ToColumnCount; i++)
            {
               if (i < FromColumnCount)		// If we have columns to copy from
                  //						Add new column to end of string
                  itemtext += FromList->GetItemText (index, i);
               else						
                  //						Use next element in padding list
                  itemtext += PadElements.Element (Delimiter,i - FromColumnCount);
               //if
               
               itemtext += Delimiter;						// Add separator
            }//for
            
            FromList->DeleteItem (index);
            position = FromList->GetFirstSelectedItemPosition ();
            int IndexIn = AddRow (GetItemCount (), itemtext, Delimiter);
            
            if (TransferItemData)
               SetItemData (IndexIn,ItemData);			// Transfer the item data
            //if
         }//if
      }//while
      
      SetColumnWidths (LVSCW_AUTOSIZE_USEHEADER);
   }//if
}//CExtendedList::InnerAddSelectedItems

CString CExtendedList::GetColumnHeader (int Column) const
{
   CExtendedList* const ncThis = const_cast <CExtendedList* const> (this);
   
   HDITEM Item;
   
   TCHAR Buf[1024];
   
   Item.mask = HDI_TEXT;
   Item.pszText = Buf;	// C crap
   Item.cchTextMax = sizeof (Buf);
   
   ncThis->GetHeaderCtrl ()->GetItem (Column,&Item);
   
   return Item.pszText;
}//CExtendedList::GetColumnHeader

int CExtendedList::GetVertOffset 
(
	int	PageHeight,
   int	FieldHeight,
   int	Align
   )const
{
   switch (Align & 12)				// Get the vertical bits
   {
      //						Top is where it will go anyway
   case A_TOP:		return 0;	
      
      //						Move it down by the space available minus the space needed
   case A_BOTTOM:	return PageHeight - FieldHeight;
      
      //						Move it down by half the space available minus the space needed
   case A_Y_MIDDLE:
   default:		return (PageHeight - FieldHeight)/2;
   }//switch
}//CExtendedList::GetVertOffset

int CExtendedList::GetHorzOffset 
(
	int	PageWidth,
   int	FieldWidth,
   int	Align
   )const
{
   switch (Align & 3)				// Get the horizontal bits
   {
      //						Left is where it will go anyway
   case A_LEFT:	return 0;
      
      //						Move it across by the space available minus the space needed
   case A_RIGHT:	return PageWidth - FieldWidth;
      
      //						Move it across by the half space available minus the space needed
   case A_X_MIDDLE:
   default:		return (PageWidth - FieldWidth)/2;
   }//switch
}//CExtendedList::GetHorzOffset

int CExtendedList::ColumnCount () const
{
   CExtendedList* const ncThis = const_cast <CExtendedList* const> (this);
   
   return ncThis->GetHeaderCtrl ()->GetItemCount ();
}//CExtendedList::ColumnCount

void CExtendedList::PrintRow
(
	CDC&						DC,
   int							Row,
   int							x,
   int							y,
   const std::valarray <int>&	Widths
   )const
{
   const int Border = 16;				// Space between text and lines
   const int HalfBorder = Border/2;
   
   if (ColumnHeaderShown ())
      Row -= 1;						// We're counting the header as a row
   //if
   
   int Cols = ColumnCount ();
   
   DC.MoveTo (x,y);					// Start border
   
   if (Row == -1)						// If it is the header
   {
      for (int i = 0; i < Cols; i++)
      {	
         DC.TextOut (x + Border,y + HalfBorder,GetColumnHeader (i));
         
         x += Widths[i];
      }//for
   }
   else
   {
      for (int i = 0; i < Cols; i++)
      {	
         DC.TextOut (x + Border,y + HalfBorder,GetItemText (Row,i));
         
         x += Widths[i];
      }//for
   }//if
   
   DC.LineTo (x,y);					// Border top
}//CExtendedList::PrintRow

std::valarray <int> CExtendedList::CalcColumnWidths
(
	CDC&					DC
   )const
{
   int Cols = ColumnCount ();
   
   std::valarray <int>	Widths (0,Cols);
   
   if (ColumnHeaderShown ())
   {
      //		Get maximum widths of text for header
      for (int i = 0; i < Cols; i++)
         Widths[i] = DC.GetTextExtent (GetColumnHeader (i)).cx;
      //for
   }//if
   
   //	And for rows
   for (int i = 0; i < GetItemCount (); i++)
   {
      for (int j = 0; j < Cols; j++)
         Widths[j] = __max (Widths[j],DC.GetTextExtent (GetItemText (i,j)).cx);
      //for
   }//for
   
   const int Spacer = 32;
   
   Widths += Spacer;					// Add spacer to all widths
   
   return Widths;
}//CExtendedList::CalcColumnWidths

void CExtendedList::Print 
(
	CDC&	DC,
   int		Left,			// Always add Left and Top to x and y values 
   int		Top,			// to keep in the right place
   int		Right,
   int		Bottom,
   int		Align
   )const
{
   int Cols = ColumnCount ();
   
   //	Calc width for each column
   std::valarray <int> Widths = CalcColumnWidths (DC);
   
   int Height = DC.GetTextExtent (_T("H")).cy + 16;	// Row height
   
   //	Calculate vertical alignment
   Top += GetVertOffset (Bottom - Top,GetItemCount () * Height,Align);
   
   //	Calculate horizontal alignment
   Left += GetHorzOffset (Right - Left,Widths.sum (),Align);
   
   int y = 0;
   
   //	Extra row for header
   int RowCount = ColumnHeaderShown ()?GetItemCount () + 1:GetItemCount ();
   
   for (int i = 0; i < RowCount; i++)
   {
      PrintRow (DC,i,Left,Top + y,Widths);	// Print a row
      
      y += Height;							// Move on
   }//for
   
   DC.MoveTo (Left,y + Top);					// Bottom line
   DC.LineTo (Left + Widths.sum (),y + Top);
   
   int x = 0;
   
   //	Draw column dividers
   for (i = 0; i < Cols; i++)
   {
      DC.MoveTo (x + Left,Top);
      DC.LineTo (x + Left,y + Top);
      
      x += Widths[i];
   }//for
   
   DC.MoveTo (x + Left,Top);
   DC.LineTo (x + Left,y + Top);
}//CExtendedList::Print

void CExtendedList::Print 
(
	HDC				DCIn,
   const CString&	Title
   )const
{
   CDC PrintDC;
   
   PrintDC.Attach (DCIn);
   
   PrintDC.StartDoc (_T ("List Contents"));
   
   PrintDC.StartPage ();
   
   int Xmm  = PrintDC.GetDeviceCaps (HORZSIZE);
   int Ymm  = PrintDC.GetDeviceCaps (VERTSIZE);
   int XPix = PrintDC.GetDeviceCaps (HORZRES);
   int YPix = PrintDC.GetDeviceCaps (VERTRES);
   
   double XPixPermm = (double)XPix/Xmm;
   double YPixPermm = (double)YPix/Ymm;
   
   const int Border = 15;		// Crop 15mm on borders
   
   int Top		= Border * YPixPermm;
   int Left	= Border * XPixPermm;
   int Bottom  = YPix - Border * YPixPermm;
   int Right	= XPix - Border * XPixPermm;
   
   if (!Title.IsEmpty ())
   {
      CSize Size = PrintDC.GetTextExtent (Title);
      
      PrintDC.TextOut (Left + GetHorzOffset (Right - Left,Size.cx),Top,Title);
      
      Top += Size.cy * 1.5;			// Move down the rest
   }//if
   
   Print (PrintDC,Left,Top,Right,Bottom);
   
   PrintDC.EndPage ();
   
   PrintDC.EndDoc ();
}//CExtendedList::Print

bool CExtendedList::ColumnHeaderShown () const
{
   return !(GetStyle () & LVS_NOCOLUMNHEADER);
}//CExtendedList::ColumnHeaderShown

int CALLBACK CExtendedList::SortCallback 
(
 LPARAM lParam1,
 LPARAM lParam2,
 LPARAM lParamSort
 )
{
   SSortRules* Rules = (SSortRules*)lParamSort;
   
   CExtendedList* Self = Rules->m_List;  // Fake 'this' because we are not in a member function
   
   SBiggerItemData* Data1 = (SBiggerItemData*)lParam1;
   SBiggerItemData* Data2 = (SBiggerItemData*)lParam2;
   
   //  Sort alphabetiacally for now
   CString    strItem1 = Self->GetItemText(Data1->m_Index,Rules->m_Column);
   CString    strItem2 = Self->GetItemText(Data2->m_Index,Rules->m_Column);
   
   //  Note, ascending/descending is done by swapping parameter order
   if (Self->m_SortFunctors[Rules->m_Column])
   {
      //      If we have special rules for this column (e.g. numerical)
      if (Rules->m_Ascending)
         return Self->m_SortFunctors[Rules->m_Column]->Compare (strItem1,strItem2);
      else
         return Self->m_SortFunctors[Rules->m_Column]->Compare (strItem2,strItem1);
      //if
   }
   //  Otherwise just use alphabetic comparison
   else if (Rules->m_Ascending)
      return _tcsicmp(strItem1,strItem2);
   else
      return _tcsicmp(strItem2,strItem1);
   //if
}

void CExtendedList::SortByColumn 
(
 int     ColNo,
 bool    Ascending
 )
{
   //  Dreadful hack to get round problems of sorting a list with only one coulmn - JK
   bool ExtraColumn = false;
   
   if (ColumnCount () == 1)
   {
      ExtraColumn = true;
      
      //      Just add an extra column
      LVCOLUMN lvcolumn;
      
      lvcolumn.mask = LVCF_TEXT;
      lvcolumn.fmt = LVCFMT_LEFT;
      lvcolumn.pszText = 0;
      
      InsertColumn (ColumnCount (),&lvcolumn);
   }//if
   
   m_IsSorting = true;
   
   m_SortColumn        = ColNo;
   m_LastSortAscending = Ascending;
   
   //  Item data needed for sort, so lets hijack it
   for (int i = 0; i < GetItemCount (); i++)
   {
      SBiggerItemData* BigData = new SBiggerItemData (i,GetItemData (i));
      
      SetItemData (i,(DWORD)BigData);
   }//for
   
   SSortRules Rules (ColNo,Ascending,this);
   
   SortItems (CExtendedList::SortCallback,(LPARAM)&Rules);
   
   //  Reconstruct item data
   for (i = 0; i < GetItemCount (); i++)
   {
      SBiggerItemData* BigData = (SBiggerItemData*)GetItemData (i);
      
      SetItemData (i,BigData->m_BaseData);
      
      delete BigData;
   }//for
   
   m_IsSorting = false;
   
   if (ExtraColumn)
      //      Undo the dreadful hack
      DeleteColumn (1);
   //if
   
   SetColumnWidths (LVSCW_AUTOSIZE_USEHEADER);
}

// This overload toggles the last direction used on the column, starting with ascending
void CExtendedList::SortByColumn (int ColNo)
{

    // Switch off sorting, if column -1

   if( ColNo == -1 )
   {
     m_LastSortAscending = false ;
     m_SortColumn = ColNo ;
     return ;
   }

   if (ColNo == m_SortColumn)
      m_LastSortAscending = !m_LastSortAscending;
   else
   {
      m_SortColumn = ColNo;
      m_LastSortAscending = true;
   }//if
   
   SortByColumn (ColNo,m_LastSortAscending);
}

// Use non default sorting for this column
void CExtendedList::SetSortFunctor 
(
 int             ColNo,
 SSortFunctor*   Functor
 )
{
   m_SortFunctors[ColNo] = Functor;        // Map expands to fit any column
}//CExtendedList::SetSortFunctor

// E-Z way to set or unset numeric sort on a column
void CExtendedList::SetNumericSort 
(
 int     ColNo,
 bool    Active
 )
{
   if (Active)
      SetSortFunctor (ColNo,SNumericSortFunctor::Instance ());
   else
      SetSortFunctor (ColNo,0);
   //if
}//CExtendedList::SetNumericSort

//  Numeric sort functor stuff
CExtendedList::SNumericSortFunctor* CExtendedList::SNumericSortFunctor::sm_Instance = 0;

CExtendedList::SNumericSortFunctor* CExtendedList::SNumericSortFunctor::Instance ()
{
   if (!sm_Instance)
      sm_Instance = new SNumericSortFunctor;
   //if
   
   return sm_Instance;
}//CExtendedList::SNumericSortFunctor::Instance

// Return 0 if l == r, -1 if l < r and +1 if l > r
int CExtendedList::SNumericSortFunctor::Compare 
(   
 const CString& l,
 const CString& r
 )const
{
   int li = _ttoi (l);
   int ri = _ttoi (r);
   if (li < ri)
      return -1;
   else if (li > ri)
      return 1;
   else
      return 0;
   //if
}//CExtendedList::SNumericSortFunctor::Compare

bool CExtendedList::IsSelected (int Index)
{
   if (m_SelectedItems.find (Index) != m_SelectedItems.end ())
   {
      return true;
   }
   return false;
}

void CExtendedList::RemoveSelection (int Index)
{
   m_SelectedItems.erase (Index);
}

void CExtendedList::AddSelection (int Index)
{
   m_SelectedItems.insert (Index);
}