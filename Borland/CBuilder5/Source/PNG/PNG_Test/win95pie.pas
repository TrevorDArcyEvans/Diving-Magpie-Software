unit Win95pie;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, Menus;

type
  TWin95PieChart = class(TCustomPanel)
  private
    { Private declarations }
    FValue, FMaximum, FDepth: integer;
    FUsedColor, FUsedShadowColor, FFreeColor, FFreeShadowColor, FLineColor: TColor;
    FAbout: string;
    procedure DrawPie;
    procedure SetValue(Value: integer);
    procedure SetMaximum(Maximum: integer);
    procedure SetDepth(Depth: integer);
    Procedure SetUsedColor(Color: TColor);
    Procedure SetUsedShadowColor(Color: TColor);
    Procedure SetFreeColor(Color: TColor);
    Procedure SetFreeShadowColor(Color: TColor);
    Procedure SetLineColor(Color: TColor);
  protected
    { Protected declarations }
    {$IFDEF WIN32}
    procedure ValidateRename(AComponent: TComponent; const CurName, NewName: string);  override;
    {$ENDIF}
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    procedure Paint; override;
  published
    { Published declarations }
    property Value: integer read FValue write SetValue;
    property Maximum: integer read FMaximum write SetMaximum;
    property Depth: integer read FDepth write SetDepth;
    property UsedColor: TColor read FUsedColor write SetUsedColor;
    property UsedShadowColor: TColor read FUsedShadowColor write SetUsedShadowColor;
    property FreeColor: TColor read FFreeColor write SetFreeColor;
    property FreeShadowColor: TColor read FFreeShadowColor write SetFreeShadowColor;
    property LineColor: TColor read FLineColor write SetLineColor;

    property Align;
    property BorderStyle;
    property Color;
    property HelpContext;
    property Hint;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Visible;

    property OnClick;
    property OnDblClick;
    property OnEnter;
    property OnExit;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;

    property About: string read FAbout write FAbout;
  end;

procedure Register;

implementation

procedure Register;
begin
  RegisterComponents('BealeARTS', [TWin95PieChart]);
end;


{$IFDEF WIN32}
procedure TWin95PieChart.ValidateRename(AComponent: TComponent;
  const CurName, NewName: string);
begin
  if (AComponent <> nil) and (CompareText(CurName, NewName) <> 0) and
    (FindComponent(NewName) <> nil) then
    raise EComponentError.CreateFmt('A component named %s already exists.', [NewName]);
end;
{$ENDIF}


constructor TWin95PieChart.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);

  Width := 125 + 10;
  Height := 65 + 10;
  BevelOuter := bvNone;

  FValue := 80;
  FMaximum := 100;
  FDepth := 10;
  FUsedColor := clBlue;
  FUsedShadowColor := clNavy;
  FFreeColor := clFuchsia;
  FFreeShadowColor := clPurple;
  FLineColor := clBlack;

end;



procedure TWin95PieChart.DrawPie;
var
   X1, Y1, X2, Y2, Angle: integer;
   DegreeCount: Real;
begin

Angle := Round((FValue/FMaximum)*360);

DegreeCount := (-Angle+270);
X1 := Trunc( 0.5 * Width * SIN(((DegreeCount*PI) / 180)) );
Y1 := Trunc( 0.5 * (Height-FDepth) * COS(((DegreeCount*PI) / 180)) );
X1 := X1 + Trunc(Width/2);
Y1 := Y1 + Trunc((Height-FDepth)/2);

X2 := 0;
Y2 := Trunc((Height-FDepth)/2);

Canvas.Brush.color := Color;
Canvas.FillRect(Rect(0,0,Width,Height));

Canvas.Pen.Color := FLineColor;
Canvas.Brush.Color := FreeShadowColor;
Canvas.Pie(0,FDepth+0,Width,Height,0,Trunc((Height+FDepth)/2),Width,Trunc((Height+FDepth)/2));

Canvas.Pen.Color := FreeShadowColor;
Canvas.MoveTo(X2+1,Y2+FDepth);
Canvas.LineTo(Width-2,Y2+FDepth);
Canvas.Pen.Color := FLineColor;

Canvas.MoveTo(X2,Y2);
Canvas.LineTo(X2,Y2+FDepth);

Canvas.MoveTo(Width-1,Y2);
Canvas.LineTo(Width-1,Y2+FDepth);

if Y1 > Trunc((Height-FDepth)/2) then
begin
Canvas.MoveTo(X1,Y1);
Canvas.LineTo(X1,Y1+FDepth);
end;

Canvas.Brush.Color := FUsedColor;
Canvas.Pie(0,0,Width,Height-FDepth,X1,Y1,X2,Y2);

Canvas.Brush.Color := FreeColor;
Canvas.Pie(0,0,Width,Height-FDepth,X2,Y2,X1,y1);

if Y1 > Trunc((Height-FDepth)/2) then
begin
Canvas.Brush.Color := FreeShadowColor;
Canvas.FloodFill(X1-1 ,Y1+Trunc(FDepth/2),FLineColor,fsBorder);
Canvas.Brush.Color := UsedShadowColor;
Canvas.FloodFill(X1+1 ,Y1+Trunc(FDepth/2),FLineColor,fsBorder);
end
else
begin
Canvas.Brush.Color := FreeShadowColor;
Canvas.FloodFill(Trunc(Width/2),Height-Trunc(FDepth/2),FLineColor,fsBorder);
end;


end;



procedure TWin95PieChart.Paint;
begin
Caption := '';
   inherited Paint;
DrawPie;
end;



procedure TWin95PieChart.SetValue(Value: integer);
begin
if Value < 0 then exit;
FValue := Value;
DrawPie;
end;


procedure TWin95PieChart.SetMaximum(Maximum: integer);
begin
if Maximum < 1 then exit;
FMaximum := Maximum;
DrawPie;
end;


procedure TWin95PieChart.SetDepth(Depth: integer);
begin
if Depth < 0 then exit;
FDepth := Depth;
DrawPie;
end;


Procedure TWin95PieChart.SetUsedColor(Color: TColor);
begin
FUsedColor := Color;
DrawPie;
end;


Procedure TWin95PieChart.SetUsedShadowColor(Color: TColor);
begin
FUsedShadowColor := Color;
DrawPie;
end;


Procedure TWin95PieChart.SetFreeColor(Color: TColor);
begin
FFreeColor := Color;
DrawPie;
end;


Procedure TWin95PieChart.SetFreeShadowColor(Color: TColor);
begin
FFreeShadowColor := Color;
DrawPie;
end;


Procedure TWin95PieChart.SetLineColor(Color: TColor);
begin
FLineColor := Color;
DrawPie;
end;

end.
