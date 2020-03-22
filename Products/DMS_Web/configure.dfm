object frmConfigure: TfrmConfigure
  Left = 364
  Top = 503
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Configuration'
  ClientHeight = 409
  ClientWidth = 395
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
  object Label2: TLabel
    Left = 16
    Top = 16
    Width = 78
    Height = 13
    Caption = 'XML style sheet:'
  end
  object Label1: TLabel
    Left = 120
    Top = 176
    Width = 51
    Height = 13
    Caption = 'pixels wide'
  end
  object Label3: TLabel
    Left = 120
    Top = 208
    Width = 49
    Height = 13
    Caption = 'pixels high'
  end
  object chkBoundBox: TCheckBox
    Left = 234
    Top = 193
    Width = 97
    Height = 17
    Caption = 'Bounding box'
    TabOrder = 19
  end
  object chkDateTime: TCheckBox
    Left = 32
    Top = 329
    Width = 121
    Height = 17
    Caption = 'Current date && time'
    TabOrder = 12
  end
  object chkFileSize: TCheckBox
    Left = 32
    Top = 305
    Width = 97
    Height = 17
    Caption = 'File size (bytes)'
    TabOrder = 11
  end
  object chkFileName: TCheckBox
    Left = 32
    Top = 233
    Width = 97
    Height = 17
    Caption = 'File name'
    TabOrder = 8
    OnClick = chkFileNameClick
  end
  object chkCentreOfMass: TCheckBox
    Left = 234
    Top = 72
    Width = 97
    Height = 17
    Caption = 'Centre of mass'
    TabOrder = 14
  end
  object chkVolume: TCheckBox
    Left = 234
    Top = 96
    Width = 97
    Height = 17
    Caption = 'Volume'
    TabOrder = 15
  end
  object chkArea: TCheckBox
    Left = 234
    Top = 120
    Width = 97
    Height = 17
    Caption = 'Area'
    TabOrder = 16
  end
  object chkMass: TCheckBox
    Left = 234
    Top = 145
    Width = 97
    Height = 17
    Caption = 'Mass'
    TabOrder = 17
  end
  object chkMassMoment: TCheckBox
    Left = 234
    Top = 169
    Width = 137
    Height = 17
    Caption = 'Mass moment of inertia'
    TabOrder = 18
  end
  object chkBitmap: TCheckBox
    Left = 32
    Top = 120
    Width = 97
    Height = 17
    Caption = 'Bitmap'
    TabOrder = 4
    OnClick = chkBitmapClick
  end
  object rdoIncDirectory: TRadioButton
    Left = 48
    Top = 281
    Width = 113
    Height = 17
    Caption = 'include path details'
    TabOrder = 10
  end
  object rdoFileNameOnly: TRadioButton
    Left = 48
    Top = 257
    Width = 113
    Height = 17
    Caption = 'only'
    Checked = True
    TabOrder = 9
    TabStop = True
  end
  object chkMassProps: TCheckBox
    Left = 218
    Top = 48
    Width = 97
    Height = 17
    Caption = 'Mass properties'
    TabOrder = 13
    OnClick = chkMassPropsClick
  end
  object btnCancel: TButton
    Left = 75
    Top = 366
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Cancel'
    ModalResult = 2
    TabOrder = 20
    OnClick = btnCancelClick
  end
  object btnOK: TButton
    Left = 245
    Top = 366
    Width = 75
    Height = 25
    Caption = '&OK'
    Default = True
    ModalResult = 1
    TabOrder = 21
    OnClick = btnOKClick
  end
  object fedXSL_FileName: TFilenameEdit
    Left = 104
    Top = 16
    Width = 275
    Height = 21
    Filter = 'XML style sheets (*.xsl)|*.xsl|All files (*.*)|*.*'
    DialogOptions = [ofHideReadOnly, ofPathMustExist, ofFileMustExist]
    DialogTitle = 'Browse for XSL file'
    NumGlyphs = 1
    TabOrder = 0
    Text = 'fedXSL_FileName'
  end
  object chkFileInfo: TCheckBox
    Left = 16
    Top = 96
    Width = 97
    Height = 17
    Caption = 'File information'
    TabOrder = 3
    OnClick = chkFileInfoClick
  end
  object chkSummInfo: TCheckBox
    Left = 16
    Top = 48
    Width = 121
    Height = 17
    Caption = 'Summary information'
    TabOrder = 1
  end
  object chkCustomProps: TCheckBox
    Left = 16
    Top = 72
    Width = 113
    Height = 17
    Caption = 'Custom properties'
    TabOrder = 2
  end
  object chkBitmapSize: TCheckBox
    Left = 48
    Top = 144
    Width = 97
    Height = 17
    Caption = 'Specify size'
    TabOrder = 5
    OnClick = chkBitmapSizeClick
  end
  object sedHeight: TCSpinEdit
    Left = 64
    Top = 200
    Width = 49
    Height = 22
    TabStop = True
    Increment = 10
    MaxValue = 2000
    MinValue = 10
    ParentColor = False
    TabOrder = 7
  end
  object sedWidth: TCSpinEdit
    Left = 64
    Top = 168
    Width = 49
    Height = 22
    TabStop = True
    Increment = 10
    MaxValue = 2000
    MinValue = 10
    ParentColor = False
    TabOrder = 6
  end
  object FormStorage: TFormStorage
    IniFileName = 'WebWorks.ini'
    IniSection = 'Configuration'
    StoredProps.Strings = (
      'chkArea.Checked'
      'chkBitmap.Checked'
      'chkBoundBox.Checked'
      'chkCentreOfMass.Checked'
      'chkCustomProps.Checked'
      'chkDateTime.Checked'
      'chkFileInfo.Checked'
      'chkFileName.Checked'
      'chkFileSize.Checked'
      'chkMass.Checked'
      'chkMassMoment.Checked'
      'chkMassProps.Checked'
      'chkSummInfo.Checked'
      'chkVolume.Checked'
      'fedXSL_FileName.Text'
      'rdoFileNameOnly.Checked'
      'rdoIncDirectory.Checked'
      'chkBitmapSize.Checked'
      'sedWidth.Value'
      'sedHeight.Value')
    StoredValues = <>
    Left = 320
    Top = 272
  end
end
