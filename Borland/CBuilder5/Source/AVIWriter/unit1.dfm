object Form1: TForm1
  Left = 318
  Top = 121
  Width = 263
  Height = 441
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 51
    Top = 160
    Width = 77
    Height = 13
    Caption = 'Frame Time (ms)'
  end
  object Label2: TLabel
    Left = 51
    Top = 192
    Width = 31
    Height = 13
    Caption = 'Height'
  end
  object Label3: TLabel
    Left = 51
    Top = 232
    Width = 28
    Height = 13
    Caption = 'Width'
  end
  object Button1: TButton
    Left = 64
    Top = 40
    Width = 113
    Height = 25
    Caption = 'Add a Bitmap'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 64
    Top = 96
    Width = 113
    Height = 25
    Caption = 'Add a WAV File'
    TabOrder = 1
    OnClick = Button2Click
  end
  object seFrameTime: TSpinEdit
    Left = 147
    Top = 152
    Width = 57
    Height = 22
    MaxValue = 10000
    MinValue = 1
    TabOrder = 2
    Value = 1
  end
  object seHeight: TSpinEdit
    Left = 147
    Top = 184
    Width = 57
    Height = 22
    MaxLength = 10
    MaxValue = 800
    MinValue = 1
    TabOrder = 3
    Value = 1
  end
  object seWidth: TSpinEdit
    Left = 147
    Top = 224
    Width = 57
    Height = 22
    MaxValue = 800
    MinValue = 10
    TabOrder = 4
    Value = 10
  end
  object cbStretch: TCheckBox
    Left = 91
    Top = 268
    Width = 73
    Height = 17
    Caption = 'Stretch'
    TabOrder = 5
  end
  object Button3: TButton
    Left = 71
    Top = 315
    Width = 113
    Height = 25
    Caption = 'Write the AVI'
    Enabled = False
    TabOrder = 6
    OnClick = Button3Click
  end
  object MediaPlayer1: TMediaPlayer
    Left = 9
    Top = 360
    Width = 57
    Height = 30
    Enabled = False
    VisibleButtons = [btPlay, btPause]
    Visible = False
    TabOrder = 8
  end
  object Button4: TButton
    Left = 71
    Top = 355
    Width = 113
    Height = 25
    Caption = 'Play'
    Enabled = False
    TabOrder = 7
    OnClick = Button4Click
  end
  object AviWriter1: TAviWriter
    Height = 76
    Width = 102
    FrameTime = 1000
    Stretch = True
    Left = 8
    Top = 8
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Btimaps (*.bmp)|*.bmp'
    Left = 8
    Top = 56
  end
  object OpenDialog2: TOpenDialog
    Filter = 'WAV Files (*.wav)|*.wav'
    Left = 8
    Top = 96
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'avi'
    Filter = 'AVI File|*.avi'
    Left = 8
    Top = 144
  end
end
