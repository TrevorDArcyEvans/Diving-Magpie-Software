object frmConfigure: TfrmConfigure
  Left = 303
  Top = 729
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Configure'
  ClientHeight = 101
  ClientWidth = 202
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 52
    Top = 16
    Width = 30
    Height = 13
    Caption = '&Zoom:'
    FocusControl = sedZoom
  end
  object sedZoom: TRxSpinEdit
    Left = 100
    Top = 12
    Width = 49
    Height = 21
    Increment = 0.1
    MaxValue = 5
    MinValue = 1
    ValueType = vtFloat
    Value = 1
    TabOrder = 0
  end
  object bnOK: TButton
    Left = 15
    Top = 56
    Width = 75
    Height = 25
    Caption = '&OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = bnOKClick
  end
  object btnCancel: TButton
    Left = 111
    Top = 56
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Cancel'
    ModalResult = 2
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object FormStorage: TFormStorage
    IniFileName = 'LoupeWks.ini'
    IniSection = 'Configure'
    Options = []
    StoredProps.Strings = (
      'sedZoom.Value')
    StoredValues = <>
    Left = 168
    Top = 16
  end
end
