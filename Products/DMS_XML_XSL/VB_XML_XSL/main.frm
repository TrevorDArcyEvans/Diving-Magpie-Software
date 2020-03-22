VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "Comdlg32.ocx"
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "XML to XSL"
   ClientHeight    =   3135
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7800
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3135
   ScaleWidth      =   7800
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton btnBrowseOutput 
      Caption         =   "Browse..."
      Height          =   375
      Left            =   6240
      TabIndex        =   5
      Top             =   1560
      Width           =   1095
   End
   Begin VB.CommandButton btrnBrowseXSL 
      Caption         =   "Browse..."
      Height          =   375
      Left            =   6240
      TabIndex        =   3
      Top             =   840
      Width           =   1095
   End
   Begin VB.CommandButton btnBrowseXML 
      Caption         =   "Browse..."
      Height          =   375
      Left            =   6240
      TabIndex        =   1
      Top             =   120
      Width           =   1095
   End
   Begin MSComDlg.CommonDialog dlgOpen 
      Left            =   5040
      Top             =   2280
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton btnApply 
      Caption         =   "&Apply"
      Default         =   -1  'True
      Height          =   495
      Left            =   2280
      TabIndex        =   7
      Top             =   2280
      Width           =   2055
   End
   Begin VB.TextBox edtOutput 
      Height          =   375
      Left            =   1320
      TabIndex        =   4
      Text            =   "c:\Archiver.html"
      Top             =   1560
      Width           =   4815
   End
   Begin VB.TextBox edtXSL 
      Height          =   375
      Left            =   1320
      TabIndex        =   2
      Text            =   "c:\Archiver.xsl"
      Top             =   840
      Width           =   4815
   End
   Begin VB.TextBox edtXML 
      Height          =   375
      Left            =   1320
      TabIndex        =   0
      Text            =   "c:\Archiver.xml"
      Top             =   120
      Width           =   4815
   End
   Begin VB.Label Label3 
      Caption         =   "Output File:"
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   1560
      Width           =   975
   End
   Begin VB.Label Label2 
      Caption         =   "XSL File:"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   960
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "XML File:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub btnApply_Click()
Dim XML_XSL As New DMS_XML2XSL

XML_XSL.XML_FileName = edtXML.Text
XML_XSL.XSL_FileName = edtXSL.Text
XML_XSL.Output_FileName = edtOutput.Text

XML_XSL.Apply_XSL_XML
End Sub

Private Sub btnBrowseOutput_Click()
dlgOpen.DialogTitle = "Browse for Output file"
dlgOpen.Filter = _
    "all files (*.*)|*.*|" & _
    "HTML files (*.ht*)|*.ht*" & _
    "RTF files (*.rtf)|*.rtf"
    
' Specify default filter
dlgOpen.FilterIndex = 2
  
dlgOpen.FileName = edtOutput.Text
dlgOpen.ShowOpen
edtOutput.Text = dlgOpen.FileName
End Sub

Private Sub btnBrowseXML_Click()
dlgOpen.DialogTitle = "Browse for XML data file"
dlgOpen.Filter = _
    "all files (*.*)|*.*|" & _
    "XML files (*.xml)|*.xml"
    
' Specify default filter
dlgOpen.FilterIndex = 2

dlgOpen.FileName = edtXML.Text
dlgOpen.ShowOpen
edtXML.Text = dlgOpen.FileName
End Sub

Private Sub btrnBrowseXSL_Click()
dlgOpen.DialogTitle = "Browse for XSL style sheet"
dlgOpen.Filter = _
    "all files (*.*)|*.*|" & _
    "XSL files (*.xsl)|*.xsl"
    
' Specify default filter
dlgOpen.FilterIndex = 2

dlgOpen.FileName = edtXSL.Text
dlgOpen.ShowOpen
edtXSL.Text = dlgOpen.FileName
End Sub
