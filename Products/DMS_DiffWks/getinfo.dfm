object frmGetInfo: TfrmGetInfo
  Left = 358
  Top = 118
  Width = 422
  Height = 237
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Select Files'
  Color = clBtnFace
  Constraints.MaxHeight = 237
  Constraints.MinHeight = 237
  Constraints.MinWidth = 200
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 20
    Width = 57
    Height = 13
    Caption = 'Original File:'
  end
  object Label2: TLabel
    Left = 16
    Top = 52
    Width = 65
    Height = 13
    Caption = 'Changed File:'
  end
  object Label3: TLabel
    Left = 16
    Top = 94
    Width = 68
    Height = 13
    Caption = 'Transparency:'
  end
  object Label4: TLabel
    Left = 16
    Top = 133
    Width = 77
    Height = 13
    Caption = 'Highlight Colour:'
    WordWrap = True
  end
  object fedOriginal: TFilenameEdit
    Left = 100
    Top = 16
    Width = 297
    Height = 21
    Filter = 'SolidWorks part files (*.sldprt)|*.sldprt|All files (*.*)|*.*'
    DialogOptions = [ofHideReadOnly, ofPathMustExist, ofFileMustExist]
    DialogTitle = 'Select Original File'
    Anchors = [akLeft, akTop, akRight]
    NumGlyphs = 1
    TabOrder = 0
    Text = 'fedOriginal'
  end
  object fedChanged: TFilenameEdit
    Left = 100
    Top = 48
    Width = 297
    Height = 21
    Filter = 'SolidWorks part files (*.sldprt)|*.sldprt|All files (*.*)|*.*'
    DialogOptions = [ofHideReadOnly, ofPathMustExist, ofFileMustExist]
    DialogTitle = 'Select Changed File'
    Anchors = [akLeft, akTop, akRight]
    NumGlyphs = 1
    TabOrder = 1
    Text = 'fedChanged'
  end
  object sldTransparency: TRxSlider
    Left = 100
    Top = 80
    Width = 150
    Height = 40
    TabOrder = 2
  end
  object ccbxColour: TColorComboBox
    Left = 100
    Top = 128
    Width = 145
    Height = 22
    ColorValue = clRed
    TabOrder = 3
  end
  object btnOK: TButton
    Left = 78
    Top = 168
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = '&OK'
    Default = True
    ModalResult = 1
    TabOrder = 4
  end
  object btnCancel: TButton
    Left = 262
    Top = 168
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Cancel = True
    Caption = '&Cancel'
    ModalResult = 2
    TabOrder = 5
  end
  object FormStorageSelect: TFormStorage
    IniFileName = 'DiffWks.ini'
    IniSection = 'placement select'
    StoredProps.Strings = (
      'fedChanged.InitialDir'
      'fedChanged.FileName'
      'fedOriginal.InitialDir'
      'fedOriginal.FileName'
      'sldTransparency.Value'
      'ccbxColour.ColorValue')
    StoredValues = <>
    Left = 288
    Top = 88
  end
end
