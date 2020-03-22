object frmMain: TfrmMain
  Left = 300
  Top = 364
  Width = 433
  Height = 441
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'frmMain'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object BI_Loupe: TBI_Loupe
    Left = 0
    Top = 0
    Width = 425
    Height = 414
    ZoomLevel = 1
    Interval = 100
    Active = True
    BevelInner = bvRaised
    BevelOuter = bvLowered
    Bevelwidth = 1
    DrawDesigning = False
    Align = alClient
  end
  object WinRoller: TWinRoller
    Enabled = True
    Left = 144
    Top = 24
  end
  object FormPlacement: TFormPlacement
    IniFileName = 'LoupeWks.ini'
    IniSection = 'placement'
    Left = 192
    Top = 24
  end
end
