object frmScaleWorks: TfrmScaleWorks
  Left = 323
  Top = 437
  Width = 368
  Height = 439
  Caption = 'ScaleWorks v1.0'
  Color = clBtnFace
  Constraints.MinHeight = 400
  Constraints.MinWidth = 250
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 16
    Top = 184
    Width = 48
    Height = 13
    Caption = '&Sketches:'
    FocusControl = lvSketches
  end
  object Label1: TLabel
    Left = 56
    Top = 148
    Width = 27
    Height = 13
    Caption = '&Type:'
    FocusControl = ddlScaleType
  end
  object Label3: TLabel
    Left = 64
    Top = 52
    Width = 7
    Height = 13
    Caption = '&X'
    FocusControl = sedScaleModelX
  end
  object Label4: TLabel
    Left = 64
    Top = 84
    Width = 7
    Height = 13
    Caption = '&Y'
    FocusControl = sedScaleModelY
  end
  object Label5: TLabel
    Left = 64
    Top = 116
    Width = 7
    Height = 13
    Caption = '&Z'
    FocusControl = sedScaleModelZ
  end
  object lvSketches: TListView
    Left = 16
    Top = 208
    Width = 327
    Height = 113
    Anchors = [akLeft, akTop, akRight, akBottom]
    Checkboxes = True
    Columns = <
      item
        Caption = 'Name'
        Width = 150
      end
      item
        Caption = 'Scale'
      end>
    Items.Data = {
      B70000000500000000000000FFFFFFFFFFFFFFFF010000000000000007536B65
      7463683104312E303000000000FFFFFFFFFFFFFFFF010000000000000007536B
      657463683204312E353000000000FFFFFFFFFFFFFFFF01000000000000000753
      6B657463683304322E303000000000FFFFFFFFFFFFFFFF010000000000000007
      536B657463683404322E353000000000FFFFFFFFFFFFFFFF0100000000000000
      07536B657463683504332E3030FFFFFFFFFFFFFFFFFFFF}
    ReadOnly = True
    RowSelect = True
    PopupMenu = PopupMenu
    SortType = stText
    TabOrder = 6
    ViewStyle = vsReport
    OnDblClick = ChangeClick
    OnSelectItem = lvSketchesSelectItem
  end
  object btnApply: TButton
    Left = 215
    Top = 336
    Width = 75
    Height = 25
    Anchors = [akBottom]
    Caption = '&Apply'
    Default = True
    TabOrder = 8
    OnClick = btnApplyClick
  end
  object btnRefresh: TButton
    Left = 70
    Top = 336
    Width = 75
    Height = 25
    Anchors = [akBottom]
    Caption = '&Refresh'
    TabOrder = 7
    OnClick = btnRefreshClick
  end
  object sedScaleModelX: TRxSpinEdit
    Left = 96
    Top = 48
    Width = 75
    Height = 21
    Decimal = 3
    Increment = 0.05
    MaxValue = 100
    MinValue = 0.05
    ValueType = vtFloat
    Value = 1
    TabOrder = 2
  end
  object cboScaleModelEnable: TCheckBox
    Left = 16
    Top = 8
    Width = 57
    Height = 17
    Caption = '&Model'
    Checked = True
    State = cbChecked
    TabOrder = 0
    OnClick = cboScaleModelEnableClick
  end
  object sedScaleModelY: TRxSpinEdit
    Left = 96
    Top = 80
    Width = 75
    Height = 21
    Decimal = 3
    EditorEnabled = False
    Increment = 0.05
    MaxValue = 100
    MinValue = 0.05
    ValueType = vtFloat
    Value = 1
    TabOrder = 3
  end
  object sedScaleModelZ: TRxSpinEdit
    Left = 96
    Top = 112
    Width = 75
    Height = 21
    Decimal = 3
    EditorEnabled = False
    Increment = 0.05
    MaxValue = 100
    MinValue = 0.05
    ValueType = vtFloat
    Value = 1
    TabOrder = 4
  end
  object cboScaleUniform: TCheckBox
    Left = 56
    Top = 24
    Width = 97
    Height = 17
    Caption = '&Uniform'
    TabOrder = 1
    OnClick = cboScaleUniformClick
  end
  object ddlScaleType: TComboBox
    Left = 96
    Top = 144
    Width = 121
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 5
    Items.Strings = (
      'Centroid'
      'Origin'
      'Coordinate System')
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 374
    Width = 360
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object PopupMenu: TPopupMenu
    Left = 312
    Top = 72
    object Change: TMenuItem
      Caption = '&Change'
      Default = True
      OnClick = ChangeClick
    end
  end
  object FormPlacement: TFormPlacement
    IniFileName = 'ScaleWorks.ini'
    IniSection = 'placement'
    Left = 280
    Top = 72
  end
  object MainMenu: TMainMenu
    Left = 296
    Top = 112
    object mnuFile: TMenuItem
      Caption = '&File'
      object mnuRefresh: TMenuItem
        Caption = '&Refresh'
        OnClick = btnRefreshClick
      end
      object mnuApply: TMenuItem
        Caption = '&Apply'
        OnClick = btnApplyClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object mnuExit: TMenuItem
        Caption = 'E&xit'
        OnClick = mnuExitClick
      end
    end
    object mnuEdit: TMenuItem
      Caption = '&Edit'
      object mnuChange: TMenuItem
        Caption = '&Change'
        Enabled = False
        OnClick = ChangeClick
      end
    end
    object mnuHelp: TMenuItem
      Caption = '&Help'
      object mnuContents: TMenuItem
        Caption = '&Contents'
        OnClick = mnuContentsClick
      end
      object mnuAbout: TMenuItem
        Caption = '&About...'
        OnClick = mnuAboutClick
      end
    end
  end
end
