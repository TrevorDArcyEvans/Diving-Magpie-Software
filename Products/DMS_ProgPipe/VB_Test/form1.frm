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
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   2520
      TabIndex        =   5
      Text            =   "Loading..."
      Top             =   240
      Width           =   1935
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Icon"
      Height          =   375
      Left            =   600
      TabIndex        =   4
      Top             =   240
      Width           =   1335
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Reset"
      Height          =   375
      Left            =   2400
      TabIndex        =   3
      Top             =   960
      Width           =   1335
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Hide"
      Height          =   375
      Left            =   2040
      TabIndex        =   2
      Top             =   2040
      Width           =   1335
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Increment"
      Height          =   375
      Left            =   600
      TabIndex        =   1
      Top             =   960
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Show"
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Top             =   2040
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim ProgPipe As New DMS_ProgPipe
Private Sub Command1_Click()
ProgPipe.Text = Text1.Text

ProgPipe.Show

End Sub

Private Sub Command2_Click()
ProgPipe.Step
End Sub

Private Sub Command3_Click()
ProgPipe.Hide
End Sub

Private Sub Command4_Click()
ProgPipe.Reset
End Sub

Private Sub Command5_Click()
ProgPipe.Icon = Icon
End Sub
