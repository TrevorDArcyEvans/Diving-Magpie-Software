object frmProgDlg: TfrmProgDlg
  Left = 269
  Top = 657
  BorderIcons = []
  BorderStyle = bsSingle
  BorderWidth = 5
  Caption = 'frmProgDlg'
  ClientHeight = 132
  ClientWidth = 331
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object imgIcon: TImage
    Left = 13
    Top = 8
    Width = 32
    Height = 32
  end
  object lblText: TLabel
    Left = 13
    Top = 56
    Width = 31
    Height = 13
    Caption = 'lblText'
  end
  object lblPercent: TLabel
    Left = 142
    Top = 112
    Width = 47
    Height = 13
    Caption = 'lblPercent'
  end
  object lblMessage: TLabel
    Left = 64
    Top = 8
    Width = 53
    Height = 13
    Caption = 'lblMessage'
  end
  object pbProgBar: TProgressBar
    Left = 13
    Top = 88
    Width = 305
    Height = 16
    Anchors = [akLeft, akTop, akRight]
    Min = 0
    Max = 100
    TabOrder = 0
  end
end
