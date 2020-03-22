Attribute VB_Name = "BatchPrint"
' BatchPrint.vbp
'
' 08/12/98 JPS Added progress meter for feedback during batch print.
' 07/10/98 JPS Broke out into separate routines. Added GUI interface.  Added more printers.
' 06/08/98 JPS Created and documented
'
' This program is provided "AS-IS" and without any warranty of any kind.  Neither SolidWorks
' Corporation, nor the program author, can be he held liable or accountable for any kind
' of errors or bugs associated with this program or its output.
'
' This program is a sample designed to demonstrate batch plotting.  Customize
' this program for your needs and adding additional support for various paper sizes
' and orientations as desired.  You could also enhance this program to support print
' scale on a per-file basis.  Good Luck!
'

Sub PrintFiles()

Dim swApp As Object
Dim m_DrawingDoc, Sheet As Object
Dim thePrinter As String
Dim myAsizePrinter, myBsizePrinter As String
Dim emptyStr As String
Dim fileCount As Integer
Dim fileOpenErrors As Long
Dim printScale As Double
Dim fileTitle() As String           ' Array of strings.  Set array size later.
Dim numLoadedFiles As Long

' Microsoft paper size constants (ie - vbPRPSLetter) are defined in the PaperSizeConstants.bas
' and were taken from MSDN documenation.

' SolidWorks Constants for Paper Size constants (ie - swDwgPaperAsize) are defined in swConst.bas
 
' Microsoft paper orientation constants.  Used with API's for Printing
Const vbPRORPortrait = 1                ' Paper orientations
Const vbPRORLandscape = 2

numLoadedFiles = 0                                  ' Number of file successfully loaded

fileCount = DirectorySearchForm.PrintList.ListCount ' Determine number of files selected for printing

If (fileCount > 0) Then
    ProgressBarForm.CurrentProcessLabel.Caption = "Starting/Attaching To SolidWorks...."
    Set swApp = CreateObject("SldWorks.Application")    ' Attach to exising SolidWorks session or start
                                                        ' up a new SolidWorks session in the background.
'    swApp.UserControl = True
Else
    Call MsgBox("'Files to be Printed' list is empty", vbOKOnly)      ' Display error message
    Exit Sub
End If

ReDim fileTitle(fileCount)

progressValue = 0

For i = 0 To (fileCount - 1)

    If (swApp Is Nothing) Then
        Call MsgBox("Error! SolidWorks not running!", vbOKOnly)      ' Display error message
        Exit Sub
    End If
    
' It is recommended you run this program with SolidWorks 98 version 1998/202 or higher to take
' advantage of the OpenDocSilent command which will avoid error dialogs during file open.
    ProgressBarForm.CurrentProcessLabel.Caption = "Loading File...."
    ProgressBarForm.CurrentItemLabel.Caption = DirectorySearchForm.PrintList.List(i)
    
    Set m_DrawingDoc = Nothing
    If (swApp.DateCode > 1998165) Then              ' New OpenDocSilent function will avoid dialogs
        Set m_DrawingDoc = swApp.OpenDocSilent(DirectorySearchForm.PrintList.List(i), swDocDRAWING, fileOpenErrors)
    Else
        Set m_DrawingDoc = swApp.OpenDoc(DirectorySearchForm.PrintList.List(i), swDocDRAWING)
    End If

    progressValue = progressValue + 1                   ' Increment progress by 1 for file getting loaded
    ProgressBarForm.ProgressBar1.Value = progressValue

    If (m_DrawingDoc Is Nothing) Then
        ProgressBarForm.CurrentProcessLabel.Caption = "Error Loading File...."
        GoTo 999 ' Dont laugh at this. I couldnt figure out how to continue the FOR loop at the next increment
                 ' Any suggestions that dont include bracketing all the code below inside this !If ???
    End If
                                                ' Error occurred when opening this file.
    If (fileOpenErrors <> 0) Then               ' Make your own coding decision here.  I choose NOT to print it.
        ProgressBarForm.CurrentProcessLabel.Caption = "Error Loading File...."
        fileTitle(numLoadedFiles) = m_DrawingDoc.GetTitle    ' File was loaded but is no good.  Make sure we
        numLoadedFiles = numLoadedFiles + 1                  ' add it to our list of files to be closed.
        Set m_DrawingDoc = Nothing
        GoTo 999
    End If
    
    ' Determine the document type.  If the document is not a drawing then send a message
    ' to the user.  This program can be enhanced to support parts and assemblies if desired.
    If (m_DrawingDoc.GetType <> swDocDRAWING) Then
        'swApp.SendMsgToUser ("Program currently supports only drawings.")
        fileTitle(numLoadedFiles) = m_DrawingDoc.GetTitle    ' File was loaded but is not .slddrw.  Make sure we
        numLoadedFiles = numLoadedFiles + 1                  ' add it to our list of files to be closed.
        Set m_DrawingDoc = Nothing
        GoTo 999
    End If
    
    
    ProgressBarForm.CurrentProcessLabel.Caption = "File Loaded...."
    
    '
    ' This next section of code will make "Sheet1" the active sheet.
    '
    Set Sheet = m_DrawingDoc.GetCurrentSheet        ' Get the current sheet
    currentSheetName = Sheet.GetName
    
    m_DrawingDoc.SheetPrevious                      ' If not on "Sheet1", move to the previous Sheet
    Set Sheet = Nothing
    Set Sheet = m_DrawingDoc.GetCurrentSheet        ' Get the current sheet
    If (Not Sheet Is Nothing) Then
        previousSheetName = Sheet.GetName           ' Get this sheets name
    End If
    
    While (currentSheetName <> previousSheetName)
    
        currentSheetName = previousSheetName
        previousSheetName = ""
        
        m_DrawingDoc.SheetPrevious                      ' Move to the previous Sheet
        Set Sheet = Nothing
        Set Sheet = m_DrawingDoc.GetCurrentSheet        ' Get the sheet object
        If (Not Sheet Is Nothing) Then
            previousSheetName = Sheet.GetName            ' Get this sheets name
        End If
    Wend
    
    '
    ' We should now have the FIRST sheet as the active sheet.  Now we will traverse
    ' the sheets in a "forward" manner and print each sheet.
    '
    Set Sheet = m_DrawingDoc.GetCurrentSheet        ' Get the current sheet
    currentSheetName = Sheet.GetName
    previousSheetName = ""
    pageNumber = 0
    While (currentSheetName <> previousSheetName)
        
        '
        ' YOU MAY NEED TO CUSTOMIZE THIS SUBROUTINE BASED ON YOUR NEEDS.
        '
        ProgressBarForm.CurrentProcessLabel.Caption = "Printing " + currentSheetName + "...."
        
        drawingPageSetup ByVal m_DrawingDoc, ByVal Sheet, ByVal swApp, printScale
        
       
        ' Print to the Default System Printer which was set above
        pageNumber = pageNumber + 1                 ' Set page range to be the current sheet number
        numCopies = 1                               ' Set the number of copies
        
        m_DrawingDoc.PrintOut2 pageNumber, pageNumber, numCopies, False, emptyStr, printScale, False, ""
    
        previousSheetName = currentSheetName
        currentSheetName = ""
    
        m_DrawingDoc.SheetNext                              ' Move to the next Sheet
        Set Sheet = Nothing
        Set Sheet = m_DrawingDoc.GetCurrentSheet            ' Get the sheet object
        If (Not Sheet Is Nothing) Then
            currentSheetName = Sheet.GetName                ' Get this sheets name
        End If
    Wend
    
    progressValue = progressValue + 1                   ' Increment progress by 1 for file getting printed
    ProgressBarForm.ProgressBar1.Value = progressValue
    
    fileTitle(numLoadedFiles) = m_DrawingDoc.GetTitle                    ' Use later to close the doc
    numLoadedFiles = numLoadedFiles + 1
    
    Set Sheet = Nothing
    Set m_DrawingDoc = Nothing

999:
    ProgressBarForm.CurrentProcessLabel.Caption = ""
    ProgressBarForm.CurrentItemLabel.Caption = ""

Next                                        ' Process next file in list

1100:
For i = 0 To (numLoadedFiles - 1)
    swApp.QuitDoc (fileTitle(i))            ' Close the documents when complete
Next

Set swApp = Nothing

End Sub

'
' This routine will set the print page setup based on the size and orientation of
' the drawing sheet passed in.  You may need to customize this routine to fit
' the needs or your site.  You may also want to set the print scale here based on
' the sheet size and printer you'll be using.
'
Private Sub drawingPageSetup(ByVal m_DrawingDoc As Object, ByVal Sheet As Object, ByVal swApp As Object, printScale As Double)
    
    printScale = 0              ' Default to "Scale to fit"
    
    If ((m_DrawingDoc Is Nothing) Or (swApp Is Nothing)) Then
        Set m_DrawingDoc = Nothing      ' Passed ByVal so these are copies of the objects and
        Set Sheet = Nothing             ' should be released???
        Set swApp = Nothing
        Exit Sub
    End If
    
    If (Not Sheet Is Nothing) Then
        sheetProps = Sheet.GetProperties            ' Get the sheet properties

        PaperSize = sheetProps(0)                   ' Determine the paper size
        '
        ' A-Size Sheets
        '
        If (PaperSize = swDwgPaperAsize) Then
            If (DirectorySearchForm.PrinterList(0) <> "") Then
                swApp.ActivePrinter DirectorySearchForm.PrinterList(0)    ' Set the desired printer
            End If
            printScale = DirectorySearchForm.NumericScale(0).Text  ' Set the desired print scale
            m_DrawingDoc.PrintSetup 0, vbPRPSLetter                ' Paper Size set to "A-size"
            m_DrawingDoc.PrintSetup 1, vbPRORLandscape             ' Orientation set to Landscape
        ElseIf (PaperSize = swDwgPaperAsizeVertical) Then
            If (DirectorySearchForm.PrinterList(0) <> "") Then
                swApp.ActivePrinter DirectorySearchForm.PrinterList(0)    ' Set the desired printer
            End If
            printScale = DirectorySearchForm.NumericScale(0)    ' Set the desired print scale
            m_DrawingDoc.PrintSetup 0, vbPRPSLetter             ' Paper Size set to "A-Size"
            m_DrawingDoc.PrintSetup 1, vbPRORPortrait           ' Orientation set to Portrait
        '
        ' B-Size Sheets
        '
        ElseIf (PaperSize = swDwgPaperBsize) Then
            If (DirectorySearchForm.PrinterList(1) <> "") Then
                swApp.ActivePrinter DirectorySearchForm.PrinterList(1)    ' Set the desired printer
            End If
            printScale = DirectorySearchForm.NumericScale(1)    ' Set the desired print scale
            m_DrawingDoc.PrintSetup 0, vbPRPS11x17              ' Paper Size set to "11x17"
            m_DrawingDoc.PrintSetup 1, vbPRORLandscape          ' Orientation set to Landscape
        '
        ' C-Size Sheets
        '
        ElseIf (PaperSize = swDwgPaperCsize) Then
            If (DirectorySearchForm.PrinterList(2) <> "") Then
                swApp.ActivePrinter DirectorySearchForm.PrinterList(2)    ' Set the desired printer
            End If
            printScale = DirectorySearchForm.NumericScale(2)    ' Set the desired print scale
            m_DrawingDoc.PrintSetup 0, vbPRPS11x17              ' Paper Size set to "11x17"
            m_DrawingDoc.PrintSetup 1, vbPRORLandscape          ' Orientation set to Landscape
        '
        ' D-Size Sheets
        '
        ElseIf (PaperSize = swDwgPaperDsize) Then
            If (DirectorySearchForm.PrinterList(3) <> "") Then
                swApp.ActivePrinter DirectorySearchForm.PrinterList(3)    ' Set the desired printer
            End If
            printScale = DirectorySearchForm.NumericScale(3)    ' Set the desired print scale
            m_DrawingDoc.PrintSetup 0, vbPRPS11x17              ' Paper Size set to "11x17"
            m_DrawingDoc.PrintSetup 1, vbPRORLandscape          ' Orientation set to Landscape
        '
        ' E-Size Sheets
        '
        ElseIf (PaperSize = swDwgPaperEsize) Then
            If (DirectorySearchForm.PrinterList(4) <> "") Then
                swApp.ActivePrinter DirectorySearchForm.PrinterList(4)    ' Set the desired printer
            End If
            printScale = DirectorySearchForm.NumericScale(4)    ' Set the desired print scale
            m_DrawingDoc.PrintSetup 0, vbPRPS11x17              ' Paper Size set to "11x17"
            m_DrawingDoc.PrintSetup 1, vbPRORLandscape          ' Orientation set to Landscape
        
        'Etc
        'Etc    PUT IN YOUR SITE-SPECIFIC CODE HERE AND MODIFY ABOVE AS NEEDED!!
        'Etc
        '
        ' All Other Sheet Sizes.  This is a default and can be customized by you.
        '
        Else
            If (DirectorySearchForm.PrinterList(5) <> "") Then
                swApp.ActivePrinter DirectorySearchForm.PrinterList(5)  ' Set the desired printer
            End If
            printScale = DirectorySearchForm.NumericScale(5)            ' Set the desired print scale
       
        End If                  ' End if based on sheet size
    
    End If              ' End if Sheet object is valid

    Set m_DrawingDoc = Nothing      ' Passed ByVal so these are copies of the objects and
    Set Sheet = Nothing             ' should be released???
    Set swApp = Nothing

End Sub
