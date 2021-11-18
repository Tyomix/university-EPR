object Form1: TForm1
  Left = 207
  Top = 306
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1040#1062#1055' USB'
  ClientHeight = 446
  ClientWidth = 1143
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
  object Label1: TLabel
    Left = 72
    Top = 24
    Width = 69
    Height = 13
    Caption = #1048#1085#1090#1077#1088#1074#1072#1083', '#1084#1089
  end
  object b0: TCheckBox
    Left = 8
    Top = 88
    Width = 41
    Height = 17
    Caption = 'b0'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object b1: TCheckBox
    Left = 8
    Top = 104
    Width = 41
    Height = 17
    Caption = 'b1'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object b2: TCheckBox
    Left = 8
    Top = 120
    Width = 41
    Height = 17
    Caption = 'b2'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
  end
  object Button1: TButton
    Left = 112
    Top = 88
    Width = 153
    Height = 33
    Caption = #1053#1072#1095#1072#1090#1100' '#1080#1079#1084#1077#1088#1077#1085#1080#1077
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 112
    Top = 136
    Width = 153
    Height = 33
    Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    Visible = False
  end
  object Edit1: TEdit
    Left = 64
    Top = 56
    Width = 297
    Height = 21
    TabOrder = 5
  end
  object stop: TButton
    Left = 280
    Top = 88
    Width = 65
    Height = 33
    Caption = #1057#1090#1086#1087
    TabOrder = 6
    OnClick = stopClick
  end
  object List1: TListBox
    Left = 376
    Top = 16
    Width = 753
    Height = 384
    Columns = 1
    ItemHeight = 13
    MultiSelect = True
    TabOrder = 7
    TabWidth = 100
  end
  object Button3: TButton
    Left = 280
    Top = 136
    Width = 65
    Height = 33
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 8
    OnClick = Button3Click
  end
  object resulttxt: TEdit
    Left = 272
    Top = 168
    Width = 81
    Height = 21
    TabOrder = 9
    Text = 'result.txt'
  end
  object b3: TCheckBox
    Left = 8
    Top = 136
    Width = 41
    Height = 17
    Caption = 'b3'
    TabOrder = 10
  end
  object b4: TCheckBox
    Left = 8
    Top = 152
    Width = 41
    Height = 17
    Caption = 'b4'
    TabOrder = 11
  end
  object b5: TCheckBox
    Left = 8
    Top = 168
    Width = 41
    Height = 17
    Caption = 'b5'
    TabOrder = 12
  end
  object b6: TCheckBox
    Left = 8
    Top = 184
    Width = 41
    Height = 17
    Caption = 'b6'
    Enabled = False
    TabOrder = 13
  end
  object b7: TCheckBox
    Left = 8
    Top = 200
    Width = 41
    Height = 17
    Caption = 'b7'
    Enabled = False
    TabOrder = 14
  end
  object Button4: TButton
    Left = 376
    Top = 408
    Width = 73
    Height = 33
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 15
    OnClick = Button4Click
  end
  object CSpinEdit1: TCSpinEdit
    Left = 152
    Top = 16
    Width = 89
    Height = 22
    TabOrder = 16
    Value = 25
    OnChange = CSpinEdit1Change
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 25
    OnTimer = Timer1Timer
    Left = 8
    Top = 8
  end
  object Timer2: TTimer
    Interval = 100
    OnTimer = Timer2Timer
    Left = 8
    Top = 40
  end
end
