VERSION 5.00
Object = "{FE0065C0-1B7B-11CF-9D53-00AA003C9CB6}#1.1#0"; "COMCT232.OCX"
Begin VB.Form DirectorySearchForm 
   Caption         =   "Batch Printing"
   ClientHeight    =   8070
   ClientLeft      =   885
   ClientTop       =   2430
   ClientWidth     =   10905
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   8070
   ScaleWidth      =   10905
   Begin VB.CommandButton AddAllFiles 
      Caption         =   "Add All"
      Height          =   495
      Left            =   5760
      TabIndex        =   49
      ToolTipText     =   """Add All Files in this directory"""
      Top             =   1080
      Width           =   1215
   End
   Begin VB.ComboBox PrinterList 
      Height          =   315
      Index           =   5
      Left            =   7440
      TabIndex        =   45
      Top             =   7200
      Width           =   3375
   End
   Begin VB.CheckBox ScaleToFit 
      Caption         =   "Scale To Fit"
      Height          =   255
      Index           =   5
      Left            =   7440
      TabIndex        =   44
      Top             =   7560
      Width           =   1215
   End
   Begin VB.TextBox NumericScale 
      Height          =   285
      Index           =   5
      Left            =   8760
      TabIndex        =   43
      Text            =   "0.0"
      Top             =   7560
      Width           =   495
   End
   Begin VB.ComboBox PrinterList 
      Height          =   315
      Index           =   4
      Left            =   7440
      TabIndex        =   39
      Top             =   6000
      Width           =   3375
   End
   Begin VB.CheckBox ScaleToFit 
      Caption         =   "Scale To Fit"
      Height          =   255
      Index           =   4
      Left            =   7440
      TabIndex        =   38
      Top             =   6360
      Width           =   1215
   End
   Begin VB.TextBox NumericScale 
      Height          =   285
      Index           =   4
      Left            =   8760
      TabIndex        =   37
      Text            =   "0.0"
      Top             =   6360
      Width           =   495
   End
   Begin VB.ComboBox PrinterList 
      Height          =   315
      Index           =   3
      Left            =   7440
      TabIndex        =   33
      Top             =   4800
      Width           =   3375
   End
   Begin VB.CheckBox ScaleToFit 
      Caption         =   "Scale To Fit"
      Height          =   255
      Index           =   3
      Left            =   7440
      TabIndex        =   32
      Top             =   5160
      Width           =   1215
   End
   Begin VB.TextBox NumericScale 
      Height          =   285
      Index           =   3
      Left            =   8760
      TabIndex        =   31
      Text            =   "0.0"
      Top             =   5160
      Width           =   495
   End
   Begin VB.ComboBox PrinterList 
      Height          =   315
      Index           =   2
      Left            =   7440
      TabIndex        =   27
      Top             =   3600
      Width           =   3375
   End
   Begin VB.CheckBox ScaleToFit 
      Caption         =   "Scale To Fit"
      Height          =   255
      Index           =   2
      Left            =   7440
      TabIndex        =   26
      Top             =   3960
      Width           =   1215
   End
   Begin VB.TextBox NumericScale 
      Height          =   285
      Index           =   2
      Left            =   8760
      TabIndex        =   25
      Text            =   "0.0"
      Top             =   3960
      Width           =   495
   End
   Begin VB.ComboBox PrinterList 
      Height          =   315
      Index           =   1
      Left            =   7440
      TabIndex        =   21
      Top             =   2400
      Width           =   3375
   End
   Begin VB.CheckBox ScaleToFit 
      Caption         =   "Scale To Fit"
      Height          =   255
      Index           =   1
      Left            =   7440
      TabIndex        =   20
      Top             =   2760
      Width           =   1215
   End
   Begin VB.TextBox NumericScale 
      Height          =   285
      Index           =   1
      Left            =   8760
      TabIndex        =   19
      Text            =   "0.0"
      Top             =   2760
      Width           =   495
   End
   Begin ComCtl2.UpDown UpDownSizeScale 
      Height          =   285
      Index           =   0
      Left            =   9255
      TabIndex        =   17
      Top             =   1560
      Width           =   240
      _ExtentX        =   423
      _ExtentY        =   503
      _Version        =   327681
      OrigLeft        =   9255
      OrigTop         =   1560
      OrigRight       =   9495
      OrigBottom      =   1845
      Increment       =   0
      Enabled         =   -1  'True
   End
   Begin VB.TextBox NumericScale 
      Height          =   285
      Index           =   0
      Left            =   8760
      TabIndex        =   16
      Text            =   "0.0"
      Top             =   1560
      Width           =   495
   End
   Begin VB.CheckBox ScaleToFit 
      Caption         =   "Scale To Fit"
      Height          =   255
      Index           =   0
      Left            =   7440
      TabIndex        =   15
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CommandButton AdvancedOptions 
      Caption         =   "Advanced -->"
      Height          =   495
      Left            =   5640
      TabIndex        =   11
      Top             =   4560
      Width           =   1215
   End
   Begin VB.ComboBox PrinterList 
      Height          =   315
      Index           =   0
      Left            =   7440
      TabIndex        =   10
      Top             =   1200
      Width           =   3375
   End
   Begin VB.CommandButton ClearList 
      Caption         =   "Clear List"
      Height          =   495
      Left            =   5640
      TabIndex        =   9
      Top             =   6120
      Width           =   1215
   End
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      Height          =   495
      Left            =   5640
      TabIndex        =   8
      Top             =   7320
      Width           =   1215
   End
   Begin VB.CommandButton SubmitPrintJob 
      Caption         =   "Submit Batch"
      Height          =   495
      Left            =   5640
      TabIndex        =   7
      Top             =   6720
      Width           =   1215
   End
   Begin VB.CommandButton RemoveFile 
      Caption         =   "Remove Item"
      Height          =   495
      Left            =   5640
      TabIndex        =   6
      Top             =   5520
      Width           =   1215
   End
   Begin VB.CommandButton AddFile 
      Caption         =   "Add Selected"
      Height          =   495
      Left            =   5760
      TabIndex        =   5
      ToolTipText     =   """Add Selected Files"""
      Top             =   480
      Width           =   1215
   End
   Begin VB.ListBox PrintList 
      Height          =   2400
      Left            =   240
      TabIndex        =   4
      Top             =   5520
      Width           =   5295
   End
   Begin VB.DriveListBox Drives 
      Height          =   315
      Left            =   240
      TabIndex        =   2
      Top             =   120
      Width           =   2415
   End
   Begin VB.DirListBox DirList 
      Height          =   4590
      Left            =   210
      TabIndex        =   1
      Top             =   435
      Width           =   2415
   End
   Begin VB.FileListBox FileList 
      Height          =   4575
      Left            =   2760
      MultiSelect     =   2  'Extended
      Pattern         =   "*.SLDDRW;*.DRW"
      TabIndex        =   0
      Top             =   480
      Width           =   2775
   End
   Begin ComCtl2.UpDown UpDownSizeScale 
      Height          =   285
      Index           =   1
      Left            =   9255
      TabIndex        =   18
      Top             =   2760
      Width           =   240
      _ExtentX        =   423
      _ExtentY        =   503
      _Version        =   327681
      OrigLeft        =   9255
      OrigTop         =   1560
      OrigRight       =   9495
      OrigBottom      =   1845
      Increment       =   0
      Enabled         =   -1  'True
   End
   Begin ComCtl2.UpDown UpDownSizeScale 
      Height          =   285
      Index           =   2
      Left            =   9255
      TabIndex        =   24
      Top             =   3960
      Width           =   240
      _ExtentX        =   423
      _ExtentY        =   503
      _Version        =   327681
      OrigLeft        =   9255
      OrigTop         =   1560
      OrigRight       =   9495
      OrigBottom      =   1845
      Increment       =   0
      Enabled         =   -1  'True
   End
   Begin ComCtl2.UpDown UpDownSizeScale 
      Height          =   285
      Index           =   3
      Left            =   9255
      TabIndex        =   30
      Top             =   5160
      Width           =   240
      _ExtentX        =   423
      _ExtentY        =   503
      _Version        =   327681
      OrigLeft        =   9255
      OrigTop         =   1560
      OrigRight       =   9495
      OrigBottom      =   1845
      Increment       =   0
      Enabled         =   -1  'True
   End
   Begin ComCtl2.UpDown UpDownSizeScale 
      Height          =   285
      Index           =   4
      Left            =   9255
      TabIndex        =   36
      Top             =   6360
      Width           =   240
      _ExtentX        =   423
      _ExtentY        =   503
      _Version        =   327681
      OrigLeft        =   9255
      OrigTop         =   1560
      OrigRight       =   9495
      OrigBottom      =   1845
      Increment       =   0
      Enabled         =   -1  'True
   End
   Begin ComCtl2.UpDown UpDownSizeScale 
      Height          =   285
      Index           =   5
      Left            =   9255
      TabIndex        =   42
      Top             =   7560
      Width           =   240
      _ExtentX        =   423
      _ExtentY        =   503
      _Version        =   327681
      OrigLeft        =   9255
      OrigTop         =   1560
      OrigRight       =   9495
      OrigBottom      =   1845
      Increment       =   0
      Enabled         =   -1  'True
   End
   Begin VB.Label Label5 
      Caption         =   "SolidWorks Drawings:"
      Height          =   240
      Left            =   2760
      TabIndex        =   48
      Top             =   240
      Width           =   1785
   End
   Begin VB.Label Label3 
      Caption         =   "All Other Sheet Sizes"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Index           =   5
      Left            =   7320
      TabIndex        =   47
      Top             =   6720
      Width           =   2265
   End
   Begin VB.Label Label4 
      Caption         =   "Printer:"
      Height          =   225
      Index           =   5
      Left            =   7440
      TabIndex        =   46
      Top             =   6960
      Width           =   2265
   End
   Begin VB.Label Label3 
      Caption         =   "E-Size Sheets"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Index           =   4
      Left            =   7320
      TabIndex        =   41
      Top             =   5520
      Width           =   2265
   End
   Begin VB.Label Label4 
      Caption         =   "Printer:"
      Height          =   225
      Index           =   4
      Left            =   7440
      TabIndex        =   40
      Top             =   5760
      Width           =   2265
   End
   Begin VB.Label Label3 
      Caption         =   "D-Size Sheets"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Index           =   3
      Left            =   7320
      TabIndex        =   35
      Top             =   4320
      Width           =   2265
   End
   Begin VB.Label Label4 
      Caption         =   "Printer:"
      Height          =   225
      Index           =   3
      Left            =   7440
      TabIndex        =   34
      Top             =   4560
      Width           =   2265
   End
   Begin VB.Label Label3 
      Caption         =   "C-Size Sheets"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Index           =   2
      Left            =   7320
      TabIndex        =   29
      Top             =   3120
      Width           =   2265
   End
   Begin VB.Label Label4 
      Caption         =   "Printer:"
      Height          =   225
      Index           =   2
      Left            =   7440
      TabIndex        =   28
      Top             =   3360
      Width           =   2265
   End
   Begin VB.Label Label3 
      Caption         =   "B-Size Sheets"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Index           =   1
      Left            =   7320
      TabIndex        =   23
      Top             =   1920
      Width           =   2265
   End
   Begin VB.Label Label4 
      Caption         =   "Printer:"
      Height          =   225
      Index           =   1
      Left            =   7440
      TabIndex        =   22
      Top             =   2160
      Width           =   2265
   End
   Begin VB.Label Label4 
      Caption         =   "Printer:"
      Height          =   225
      Index           =   0
      Left            =   7440
      TabIndex        =   14
      Top             =   960
      Width           =   2265
   End
   Begin VB.Line Line1 
      X1              =   7080
      X2              =   7080
      Y1              =   -240
      Y2              =   7800
   End
   Begin VB.Label Label3 
      Caption         =   "A-Size Sheets"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Index           =   0
      Left            =   7320
      TabIndex        =   13
      Top             =   720
      Width           =   2265
   End
   Begin VB.Label Label1 
      Caption         =   "Size-Specific Print Settings"
      Height          =   345
      Left            =   7200
      TabIndex        =   12
      Top             =   360
      Width           =   2265
   End
   Begin VB.Label Label2 
      Caption         =   "Files to be Printed"
      Height          =   360
      Left            =   240
      TabIndex        =   3
      Top             =   5280
      Width           =   2265
   End
   Begin VB.Menu Help 
      Caption         =   "Help"
      Index           =   0
      Begin VB.Menu HelpSteps 
         Caption         =   "Help"
         Index           =   2
      End
      Begin VB.Menu About 
         Caption         =   "About"
         Index           =   3
      End
   End
End
Attribute VB_Name = "DirectorySearchForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'
' DirectorySearchForm.frm
'
' 08/12/98 JPS Added progress meter for feedback during batch print.
' 07/13/98 JPS Save printer and scale values to the registry for future program runs
' 07/10/98 JPS Created and documented
'
'
' ====================================================================================
'
' ========================================
' MENU CONTROLS
' ========================================
'
' "HELP-ABOUT" MENU ITEM
'
Private Sub About_Click(Index As Integer)

    frmAbout.Show

End Sub
'
' "HELP-HELP" MENU ITEM
'
Private Sub HelpSteps_Click(Index As Integer)
    
    frmHelp.Show
    
End Sub
'
' ========================================
' MAIN FORM CONTROLS
' ========================================
'
' "ADD SELECTED" BUTTON
'
' Button to add file to list.  Also can be done by double-clicking the file
'
Private Sub AddFile_Click()
    
   Dim fileToPrint As String

   For i = 0 To FileList.ListCount - 1      ' For each file selected in the "SolidWorks Drawings" list
        
        If FileList.Selected(i) Then
            
            fileToPrint = FileList.Path + "\" + FileList.List(i) ' Change source doc to the
            If (fileToPrint <> "") Then
               PrintList.AddItem fileToPrint
            End If
            
        End If
    Next i

End Sub
'
' "ADD ALL" BUTTON
'
' Add all files currently displayed in the "SolidWorks Drawings" list.
'
Private Sub AddAllFiles_Click()
   
   Dim fileToPrint As String

   For i = 0 To FileList.ListCount - 1      ' For each file selected in the "SolidWorks Drawings" list
       
            fileToPrint = FileList.Path + "\" + FileList.List(i) ' Change source doc to the
            If (fileToPrint <> "") Then
               PrintList.AddItem fileToPrint
            End If
            
    Next i

End Sub
'
' "ADVANCED-->" BUTTON
'
' This button will display an "Advanced" portion of the form for additional settings.
'
Private Sub AdvancedOptions_Click()

    If DirectorySearchForm.Width = 7200 Then
      DirectorySearchForm.Width = 11000
      Line1.Visible = True
    Else
      DirectorySearchForm.Width = 7200
      Line1.Visible = False
    End If

' All controls on the ADVANCED portion of the page are set up as a Control Array.
' The INDEX value indicates which set of controls the user has clicked.  These
' controls are currently set up as
'    Index 0 = A-Size controls
'      thru
'    Index 5 = All Other Print Sizes
'
    For i = 0 To 5
        If ScaleToFit(i).Value = 1 Then            ' If "Scale to Fit" is checked
            NumericScale(i).Enabled = False          ' Disable specific scaling.
            UpDownSizeScale(i).Enabled = False
        Else
            NumericScale(i).Enabled = True           ' Enable specific scaling.
            UpDownSizeScale(i).Enabled = True
        End If
    Next i
End Sub
'
' "REMOVE ITEM" BUTTON
'
' Button to remove the selected item from the "Files to be Printed" list
'
Private Sub RemoveFile_Click()
    Dim fileToRemove As Integer
    
    fileToRemove = PrintList.ListIndex
    If (fileToRemove <> -1) Then
       PrintList.RemoveItem (fileToRemove)  ' Remove file from print list
    End If
End Sub
'
' "CLEAR" BUTTON
'
' Button to clear the "Files to be Printed" list
'
Private Sub ClearList_Click()

    PrintList.Clear
    
End Sub
'
' "SUBMIT BATCH" BUTTON
'
' Button to take the current set of file in the "Files to be Printed" list and submit
' them for printing.
'
Private Sub SubmitPrintJob_Click()

    Screen.MousePointer = vbHourglass
    
    fileCount = DirectorySearchForm.PrintList.ListCount ' Determine number of files selected for printing
    
    ProgressBarForm.Show
    ProgressBarForm.ProgressBar1.Min = 0
    ProgressBarForm.ProgressBar1.Value = ProgressBarForm.ProgressBar1.Min
    ProgressBarForm.ProgressBar1.Max = fileCount * 2    ' Will increment counter twice for each file
                                                        ' Once on load, second on print complete

    Call PrintFiles                                       ' Print all files in the PrintList box
    
    ProgressBarForm.ProgressBar1.Value = ProgressBarForm.ProgressBar1.Min
    ProgressBarForm.Hide

    Screen.MousePointer = vbDefault
    
End Sub
'
' "CANCEL" BUTTON
'
' Button to cancel program execution
'
Private Sub Cancel_Click()

    End             ' Terminate the program
        
End Sub
'
' ON FORM LOAD
'
Private Sub Form_Load()
      
      DirectorySearchForm.Width = 7200      ' Set the size to hide the Advanced portion
      Line1.Visible = False

      GetRegistrySettings
      
End Sub
'
' ON FORM TERMINATE
'
Private Sub Form_Terminate()

    End

End Sub
'
'======================================================
' ADVANCED PAGE
'======================================================
'
' All controls on the ADVANCED portion of the page are set up as a Control Array.
' During run-time the INDEX value passed to these subroutines will indicate which
' set of controls the user has clicked.  These controls are currently set up as:
'
'    Index 0 = A-Size controls
'    Index 1 = B-Size controls
'    Index 2 = C-Size controls
'    Index 3 = D-Size controls
'    Index 4 = E-Size controls
'    Index 5 = All Other Print Sizes
'
'
' "SCALE TO FIT" CHECK BOX
'
Private Sub ScaleToFit_Click(Index As Integer)  ' Index if for array of printer controls (A-E size)
    
    If ScaleToFit(Index).Value = 1 Then            ' If "Scale to Fit" is checked
        NumericScale(Index).Text = "0.0"             ' Set scale value to 0 = Fit.  0.0 value use in BatchPrint.bas
        NumericScale(Index).Enabled = False          ' Disable specific scaling.
        UpDownSizeScale(Index).Enabled = False
    Else                                           ' Else if "Scale to Fit" gets unchecked
        NumericScale(Index).Text = "1.0"             ' Set scale value to 1.0 as a default
        NumericScale(Index).Enabled = True           ' Enable specific scaling.
        UpDownSizeScale(Index).Enabled = True
    End If
 
End Sub
'
' DOWN BUTTON FOR SHEET SCALE
'
Private Sub UpDownSizeScale_DownClick(Index As Integer)  ' Index if for array of printer controls (A-E size))

    NumericScale(Index).Text = Val(NumericScale(Index).Text) - 0.1
   
End Sub
'
' UP BUTTON FOR SHEET SCALE
'
Private Sub UpDownSizeScale_UpClick(Index As Integer)  ' Index if for array of printer controls (A-E size)

    NumericScale(Index).Text = Val(NumericScale(Index).Text) + 0.1

End Sub
'
' Scale Value changed by up/down arrow or direct text entry.  Save new value to the registry
'
Private Sub NumericScale_Change(Index As Integer)
    
    SaveScaleToRegistry (Index)         ' Save new scale value to the Registry

End Sub
'
' PRINTER LIST DROP-DOWN FIELD
'
' If user clicks the drop-down arrow for printers, fill it with all active printers on network.
'
Private Sub PrinterList_DropDown(Index As Integer)  ' Index if for array of printer controls (A-E size)
    
    Dim x As Printer
    
    ' To keep the list of available printers up-to-date, clear it
    ' each time and research the network for all valid printers.
    PrinterList(Index).Clear           ' Clear all entries in drop-down
    For Each x In Printers              ' Add all printers to drop-down
    
        PrinterList(Index).AddItem x.DeviceName
        
    Next

End Sub
'
' Printer setting changed by drop-down list.  Save new value to the registry
'
Private Sub PrinterList_Click(Index As Integer)
    
    SavePrinterToRegistry (Index)           ' Save new printer choice to the Registry

End Sub
'
' Printer setting changed by direct text entry to the PrinterList field.  Save new value to the registry
'
Private Sub PrinterList_Change(Index As Integer)  ' Index if for array of printer controls (A-E size)
    
    SavePrinterToRegistry (Index)           ' Save new printer choice to the Registry

End Sub
'
'======================================================
' REGISTRY SUBROUTINES
'======================================================
'
'
' Save the specified sheet scale setting to the registry.
'
Private Sub SaveScaleToRegistry(Index As Integer)
    
    newScale = DirectorySearchForm.NumericScale(Index)
    
    If (Index = 0) Then
        SaveSetting "BatchPrinting", "ASizeSheets", "Scale", newScale
    ElseIf (Index = 1) Then
        SaveSetting "BatchPrinting", "BSizeSheets", "Scale", newScale
    ElseIf (Index = 2) Then
        SaveSetting "BatchPrinting", "CSizeSheets", "Scale", newScale
    ElseIf (Index = 3) Then
        SaveSetting "BatchPrinting", "DSizeSheets", "Scale", newScale
    ElseIf (Index = 4) Then
        SaveSetting "BatchPrinting", "ESizeSheets", "Scale", newScale
    ElseIf (Index = 5) Then
        SaveSetting "BatchPrinting", "AllOtherSheets", "Scale", newScale
    End If

End Sub
'
' Save the sheet-specific printer setting to the registry.
'
Private Sub SavePrinterToRegistry(Index As Integer)
   
    newPrinter = DirectorySearchForm.PrinterList(Index)
    
    If (Index = 0) Then
        SaveSetting "BatchPrinting", "ASizeSheets", "Printer", newPrinter
    ElseIf (Index = 1) Then
        SaveSetting "BatchPrinting", "BSizeSheets", "Printer", newPrinter
    ElseIf (Index = 2) Then
        SaveSetting "BatchPrinting", "CSizeSheets", "Printer", newPrinter
    ElseIf (Index = 3) Then
        SaveSetting "BatchPrinting", "DSizeSheets", "Printer", newPrinter
    ElseIf (Index = 4) Then
        SaveSetting "BatchPrinting", "ESizeSheets", "Printer", newPrinter
    ElseIf (Index = 5) Then
        SaveSetting "BatchPrinting", "AllOtherSheets", "Printer", newPrinter
    End If

End Sub
'
' Get all the current settings from the registry and fill in the form values.
' If not set yet (ie program never run), then return default settings that can be
' used by the BatchPrint.bas drawingPageSetup subroutine.
'
' This routine is called OnLoad for the form.
'
Private Sub GetRegistrySettings()

    Dim storedPrinterValue(0 To 5) As String
    Dim storedScaleValue(0 To 5) As String
    Dim defaultValue As String
    
    defalutValue = ""     ' If not set yet, return "" value because it is used in BatchPrint.bas
    storedPrinterValue(0) = GetSetting("BatchPrinting", "ASizeSheets", "Printer")
    storedPrinterValue(1) = GetSetting("BatchPrinting", "BSizeSheets", "Printer")
    storedPrinterValue(2) = GetSetting("BatchPrinting", "CSizeSheets", "Printer")
    storedPrinterValue(3) = GetSetting("BatchPrinting", "DSizeSheets", "Printer")
    storedPrinterValue(4) = GetSetting("BatchPrinting", "ESizeSheets", "Printer")
    storedPrinterValue(5) = GetSetting("BatchPrinting", "AllOtherSheets", "Printer")
    
    defalutValue = "0.0"  ' If not set yet, return a default value because it is used in BatchPrint.bas
    storedScaleValue(0) = GetSetting("BatchPrinting", "ASizeSheets", "Scale", defalutValue)
    storedScaleValue(1) = GetSetting("BatchPrinting", "BSizeSheets", "Scale", defalutValue)
    storedScaleValue(2) = GetSetting("BatchPrinting", "CSizeSheets", "Scale", defalutValue)
    storedScaleValue(3) = GetSetting("BatchPrinting", "DSizeSheets", "Scale", defalutValue)
    storedScaleValue(4) = GetSetting("BatchPrinting", "ESizeSheets", "Scale", defalutValue)
    storedScaleValue(5) = GetSetting("BatchPrinting", "AllOtherSheets", "Scale", defalutValue)
   
    For i = 0 To 5          ' For each sheet with specific information saved in registry
                            ' update the form values.
        
        DirectorySearchForm.PrinterList(i) = storedPrinterValue(i)
        DirectorySearchForm.NumericScale(i) = storedScaleValue(i)
        
        If (storedScaleValue(i) = 0) Then
            DirectorySearchForm.ScaleToFit(i).Value = 1             ' If scale = 0, put check in "Scale To Fit"
            DirectorySearchForm.NumericScale(i).Enabled = False     ' Disable specific scaling.
            UpDownSizeScale(i).Enabled = False
        Else
            NumericScale(i).Enabled = True                          ' Enable specific scaling.
            UpDownSizeScale(i).Enabled = True
        End If
        
    Next i

End Sub

'
'======================================================
' DIRECTORY CONTROLS
'======================================================
'
'
Private Sub DirList_Change()
                                  ' Any change in DirList
    FileList.Path = DirList.Path  ' is reflected in FileList

End Sub

Private Sub DirList_DragOver(Source As Control, x As Single, y As Single, State As Integer)
    
    ' Change pointer to no drop.
    If State = 0 Then Source.MousePointer = 12
    ' Use default mouse pointer.
    If State = 1 Then Source.MousePointer = 0
    
End Sub

Private Sub Drives_Change()

On Error GoTo errorhandler                                    ' Any change in Drives
    
    DirList.Path = Drives.Drive     ' is reflected in DirList
    
    Exit Sub
    
errorhandler:
 
 Call MsgBox("Error setting Drive", vbOKOnly, "Batch Printing")  ' Display error message
 
End Sub

Private Sub Drives_DragOver(Source As Control, x As Single, y As Single, State As Integer)
    
    ' Change pointer to no drop.
    If State = 0 Then Source.MousePointer = 12
    ' Use default mouse pointer.
    If State = 1 Then Source.MousePointer = 0

End Sub

Private Sub FileList_DblClick()
    Dim fileToPrint As String
    
   fileToPrint = FileList.Path + "\" + FileList.filename    ' Add file to print list
   PrintList.AddItem fileToPrint
 
End Sub

Private Sub FileList_Click()

'FileList.Refresh

End Sub

