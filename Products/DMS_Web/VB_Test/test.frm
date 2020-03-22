VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command2 
      Caption         =   "HTML page"
      Default         =   -1  'True
      Height          =   375
      Left            =   1080
      TabIndex        =   0
      Top             =   1200
      Width           =   1815
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   720
      TabIndex        =   2
      Text            =   "v:\test.html"
      Top             =   360
      Width           =   3495
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Configure"
      Height          =   495
      Left            =   1080
      TabIndex        =   1
      Top             =   2280
      Width           =   2055
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    Dim Test As New DMS_WebWks.DMS_WebWorks
    
    Test.Configure
    
    Set Test = Nothing
End Sub

Private Sub Command2_Click()
    Dim Test As New DMS_WebWks.DMS_WebWorks
    
    Test.LoadSettings
    Test.SaveAsHTML Text1.Text, True
    
    Set Test = Nothing

End Sub
