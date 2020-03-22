object frmConfigure: TfrmConfigure
  Left = 249
  Top = 610
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'Configure'
  ClientHeight = 209
  ClientWidth = 201
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormShow
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SWImage: TImage
    Left = 136
    Top = 128
    Width = 33
    Height = 33
    Visible = False
  end
  object Label1: TLabel
    Left = 104
    Top = 45
    Width = 52
    Height = 13
    Caption = 'Pixels &wide'
    FocusControl = sedWidth
  end
  object Label2: TLabel
    Left = 104
    Top = 77
    Width = 50
    Height = 13
    Caption = 'Pixels &high'
    FocusControl = sedHeight
  end
  object Label3: TLabel
    Left = 96
    Top = 133
    Width = 32
    Height = 13
    Caption = '&Quality'
    FocusControl = sedQuality
  end
  object chkSpecifySize: TCheckBox
    Left = 32
    Top = 16
    Width = 81
    Height = 17
    Caption = '&Specify size'
    TabOrder = 0
    OnClick = chkSpecifySizeClick
  end
  object chkProgressive: TCheckBox
    Left = 32
    Top = 104
    Width = 121
    Height = 17
    Caption = '&Progressive JPEG'
    TabOrder = 3
  end
  object sedWidth: TCSpinEdit
    Left = 48
    Top = 40
    Width = 49
    Height = 22
    TabStop = True
    Increment = 10
    MaxValue = 2000
    ParentColor = False
    TabOrder = 1
  end
  object sedHeight: TCSpinEdit
    Left = 48
    Top = 72
    Width = 49
    Height = 22
    TabStop = True
    Increment = 10
    MaxValue = 2000
    ParentColor = False
    TabOrder = 2
  end
  object btnOK: TButton
    Left = 15
    Top = 168
    Width = 75
    Height = 25
    Caption = '&OK'
    Default = True
    ModalResult = 1
    TabOrder = 5
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 111
    Top = 168
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Cancel'
    ModalResult = 2
    TabOrder = 6
    OnClick = btnCancelClick
  end
  object sedQuality: TCSpinEdit
    Left = 32
    Top = 128
    Width = 49
    Height = 22
    TabStop = True
    Increment = 5
    MaxValue = 100
    MinValue = 1
    ParentColor = False
    TabOrder = 4
  end
  object FormStorage: TFormStorage
    IniFileName = 'JPGWks.ini'
    IniSection = 'configure'
    Options = []
    StoredProps.Strings = (
      'chkProgressive.Checked'
      'chkSpecifySize.Checked'
      'sedHeight.Value'
      'sedWidth.Value'
      'sedQuality.Value')
    StoredValues = <>
    Left = 168
    Top = 8
  end
  object FormPlacement: TFormPlacement
    IniFileName = 'JPGWks.ini'
    IniSection = 'placement'
    Left = 120
    Top = 8
  end
  object JPEGFileCompressor: TJPEGFileCompressor
    Trace_Level = 0
    GrayscaleOutput = False
    Comment = 'made by JPGWorks from SolidPartners'
    InputGamma = 1
    ProgressiveJPEG = False
    DCTMethod = JDCT_ISLOW
    OptimizeCoding = False
    RestartInterval = 0
    RestartInRows = 0
    SmoothingFactor = 0
    WriteJFIFHeader = True
    DensityUnit = 0
    X_Density = 1
    Y_Density = 1
    DefaultCompressor = False
    Left = 144
    Top = 96
  end
end
