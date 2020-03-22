object frmMain: TfrmMain
  Left = 195
  Top = 212
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'ColorWorks v1.0'
  ClientHeight = 91
  ClientWidth = 211
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 21
    Width = 51
    Height = 13
    Caption = '&Tolerance:'
    FocusControl = sedTolerance
  end
  object btnApply: TButton
    Left = 68
    Top = 56
    Width = 75
    Height = 25
    Caption = '&Apply'
    Default = True
    TabOrder = 1
    OnClick = btnApplyClick
  end
  object sedTolerance: TCSpinEdit
    Left = 81
    Top = 16
    Width = 49
    Height = 22
    TabStop = True
    MaxValue = 255
    MinValue = 1
    ParentColor = False
    TabOrder = 0
    Value = 5
  end
  object FormStorage: TFormStorage
    IniFileName = 'ColorWks.ini'
    IniSection = 'placement'
    StoredProps.Strings = (
      'sedTolerance.Value')
    StoredValues = <>
    Left = 176
    Top = 40
  end
end
