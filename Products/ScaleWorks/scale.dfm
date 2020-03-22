object frmScale: TfrmScale
  Left = 690
  Top = 232
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Enter new scale'
  ClientHeight = 99
  ClientWidth = 221
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object sedScale: TRxSpinEdit
    Left = 73
    Top = 16
    Width = 75
    Height = 21
    Decimal = 3
    Increment = 0.05
    MaxValue = 100
    MinValue = 0.05
    ValueType = vtFloat
    Value = 0.05
    TabOrder = 0
  end
  object btnOK: TButton
    Left = 16
    Top = 56
    Width = 75
    Height = 25
    Caption = '&OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object btnCancel: TButton
    Left = 128
    Top = 56
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
