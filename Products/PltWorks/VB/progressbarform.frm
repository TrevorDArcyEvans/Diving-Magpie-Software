VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form ProgressBarForm 
   Caption         =   "BatchPrinting Progress"
   ClientHeight    =   1590
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   1590
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin ComctlLib.ProgressBar ProgressBar1 
      Height          =   255
      Left            =   480
      TabIndex        =   0
      Top             =   360
      Width           =   3735
      _ExtentX        =   6588
      _ExtentY        =   450
      _Version        =   327682
      Appearance      =   1
   End
   Begin VB.Label CurrentItemLabel 
      Height          =   495
      Left            =   480
      TabIndex        =   2
      Top             =   1080
      Width           =   4095
   End
   Begin VB.Label CurrentProcessLabel 
      Height          =   255
      Left            =   480
      TabIndex        =   1
      Top             =   720
      Width           =   2055
   End
End
Attribute VB_Name = "ProgressBarForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
