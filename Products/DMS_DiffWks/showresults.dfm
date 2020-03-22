object frmShowResults: TfrmShowResults
  Left = 380
  Top = 460
  Width = 373
  Height = 212
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'DiffWorks Results'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object memResults: TMemo
    Left = 16
    Top = 16
    Width = 329
    Height = 105
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier'
    Font.Style = []
    Lines.Strings = (
      'memResults')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object btnOK: TButton
    Left = 145
    Top = 144
    Width = 75
    Height = 25
    Anchors = [akBottom]
    Cancel = True
    Caption = '&OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = btnOKClick
  end
  object FormStorageResults: TFormStorage
    IniFileName = 'DiffWks.ini'
    IniSection = 'placement results'
    StoredValues = <>
    Left = 248
    Top = 136
  end
end
