(*===========================================================================*)
(*                                TWinRoller                                 *)
(*---------------------------------------------------------------------------*)
(*                                                                           *)
(* New Property                                                              *)
(*                                                                           *)
(*    Enabled: Boolean                 Enable TWinRooler                     *)
(*    Roller: Boolean                  Rollup/Rolldown window                *)
(*    Visible: Boolean                 Roller button visible                 *)
(*    OnRoller: TRollerNotifyEvent                                           *)
(*                                                                           *)
(*---------------------------------------------------------------------------*)
(* Environment:                                                              *)
(*   Windows 95                                                              *)
(*   Delphi 2.0                                                              *)
(*                                                                           *)
(* Author: Sean Hsieh                                                        *)
(* E-Mail: sean@mail.linkease.com.tw                                         *)
(*===========================================================================*)
unit WinRoll;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs;

type
  EOwnerError = class(Exception);

  TRollerMode = ( mdRollDown, mdRollUp );
  TRollerNotifyEvent = procedure ( Sender: TObject; mode: TRollerMode ) of object;

  TWinRoller = class(TComponent)
  private
    { Private declarations }
    DefWinProc: TFarProc;
    DefWinProcInstance: Pointer;
    FEnabled: Boolean;
    FOnRoller: TRollerNotifyEvent;
    FOnFormDestroy: TNotifyEvent;
    FRoller: Boolean;
    FVisible: Boolean;
    ButtonArea: TRect;
    DrawPushed: Boolean;
    Pushed: Boolean;
    RestoreWndProc: Boolean;
    rgn: HRGN;
    Stop: Boolean;
    procedure CalcArea;
    procedure OnRollerDestroy( Sender: TObject );
    procedure PaintRollerButton;
    procedure Rollup;
    procedure SetEnabled( Val: Boolean );
    procedure SetRoller( Val: Boolean );
    procedure SetVisible( Val: Boolean );
    procedure WinProc(var Message: TMessage);    
  public
    { Public declarations }
    constructor Create(Owner: TComponent); override;
    destructor Destroy; override;
  published
    { Published declarations }
    property Enabled: Boolean read FEnabled write SetEnabled;
    property Roller: Boolean read FRoller write SetRoller default False;
    property Visible: Boolean read FVisible write SetVisible default True;
    property OnRoller: TRollerNotifyEvent read FOnRoller write FOnRoller;
  end;

procedure Register;

var
  si: UINT;

implementation

procedure Register;
begin
  RegisterComponents('Samples', [TWinRoller]);
end;

constructor TWinRoller.Create(Owner: TComponent);
begin
  inherited;
  FRoller := False;
  FVisible := True;
  DrawPushed := False;
  Pushed := False;
  rgn := 0;
  if not (Owner is TForm) then
    raise EOwnerError.Create('Class of the owner is not a TForm!');
  with TForm(Owner) do
  if not (csDesigning in ComponentState) then
  begin    
    DefWinProcInstance := MakeObjectInstance(WinProc);
    DefWinProc := Pointer(SetWindowLong(Handle, GWL_WNDPROC, Longint(DefWinProcInstance)));
    CalcArea;
    FOnFormDestroy := OnDestroy;
    OnDestroy := OnRollerDestroy;
  end;
end;

destructor TWinRoller.Destroy;
begin
  if not (csDesigning in ComponentState) and not RestoreWndProc then
  begin
    SetWindowLong(TForm(Owner).Handle, GWL_WNDPROC, Longint(DefWinProc));
    FreeObjectInstance(DefWinProcInstance);
  end;
  if rgn <> 0 then
    DeleteObject( rgn );
  inherited;
end;

procedure TWinRoller.OnRollerDestroy( Sender: TObject );
begin
  if Assigned( FOnFormDestroy ) then
    FOnFormDestroy( Sender );
  SetWindowLong(TForm(Owner).Handle, GWL_WNDPROC, Longint(DefWinProc));
  FreeObjectInstance(DefWinProcInstance);
  RestoreWndProc := True;
end;

procedure TWinRoller.CalcArea;
var
  x1, y1, x2, y2, w: Integer;
  Icons: TBorderIcons;
  Style: TFormBorderStyle;
//  Style, ExStyle: UINT;
begin
//  Style := GetWindowLong( TForm(Owner).Handle, GWL_STYLE );
//  ExStyle := GetWindowLong( TForm(Owner).Handle, GWL_EXSTYLE );
  with TForm(Owner) do
  begin
    if csDesigning in ComponentState then
    begin
      Icons := [biSystemMenu, biMinimize, biMaximize];
      Style := bsSizeable;
    end
    else
    begin
      Icons := BorderIcons;
      Style := BorderStyle;
    end;
  end;
  if Style in [bsSizeToolWin, bsToolWindow] then
  begin
    if Style = bsToolWindow then
      x2 := GetSystemMetrics(SM_CXFIXEDFRAME) + 2
    else
      x2 := GetSystemMetrics(SM_CXSIZEFRAME) + 2;
    if biSystemMenu in Icons then
      Inc(x2, GetSystemMetrics(SM_CXSMSIZE) + 2);
    if Style = bsToolWindow then
      y1 := GetSystemMetrics(SM_CYFIXEDFRAME) + 2
    else
      y1 := GetSystemMetrics(SM_CYSIZEFRAME) + 2;
    y2 := y1 + GetSystemMetrics(SM_CYSMSIZE) - 4;
    x2 := TForm(Owner).Width - x2;
    x1 := x2 - GetSystemMetrics(SM_CXSMSIZE) + 2;
  end
  else
  begin
    if Style in [bsSingle, bsSizeable, bsDialog] then
    begin
      if Style = bsSingle then
        x2 := GetSystemMetrics(SM_CYFIXEDFRAME) + 2
      else
        x2 := GetSystemMetrics(SM_CXSIZEFRAME) + 2;
      if biSystemMenu in Icons then
      begin
        Inc(x2, GetSystemMetrics(SM_CXSIZE) + 2);
        if (Style <> bsDialog) and (Icons * [biMinimize, biMaximize] <> []) then
          Inc(x2, GetSystemMetrics(SM_CXSIZE) * 2 - 6)
        else if biHelp in Icons then
          Inc(x2, GetSystemMetrics(SM_CXSIZE) - 4);
      end;
      if Style in [bsSingle, bsDialog] then
        y1 := GetSystemMetrics(SM_CYFIXEDFRAME) + 2
      else
        y1 := GetSystemMetrics(SM_CYSIZEFRAME) + 2;
      y2 := y1 + GetSystemMetrics(SM_CYSIZE) - 4;
      x2 := TForm(Owner).Width - x2;
      x1 := x2 - GetSystemMetrics(SM_CXSIZE) + 2;
    end;
  end;
  SetRect(ButtonArea, x1, y1, x2, y2);
//  if FRoller then Rollup;
end;

procedure TWinRoller.PaintRollerButton;
var
  h: HDC;
  st: UINT;
  p: array[0..2] of TPoint;
  c: Integer;
  b: HBRUSH;

  procedure DrawTriangle( Up: Boolean; dd: Integer; co: Integer );
  var
    pen: HPEN;
    d, x1, x2, y1, y2: Integer;
  begin
    if DrawPushed then
      d := 1 + dd
    else
      d := 0 + dd;
    with ButtonArea do
    begin
      x1 := Left + 1 + d;
      x2 := Right - 3 + d;
      y1 := Top + d;
      y2 := Bottom + d;
    end;
    p[0].x := x1 + 3;
    p[1].x := ((x1 + x2) shr 1);
    p[2].x := x2 - 3;
    if Up then
    begin      
      p[0].y := ((y1 + y2) shr 1) - 2;
      p[1].y := y1 + 2;
      p[2].y := p[0].y;
    end
    else
    begin
      p[0].y := ((y1 + y2) shr 1);
      p[1].y := y2 - 4;
      p[2].y := p[0].y;
    end;
    case co of
      0:
      begin
        pen := SelectObject( h, GetStockObject( BLACK_PEN ) );
        b := SelectObject( h, GetStockObject( BLACK_BRUSH ) );
      end;
      1:
      begin
        pen := SelectObject( h, GetStockObject( WHITE_PEN ) );
        b := SelectObject( h, GetStockObject( WHITE_BRUSH ) );
      end;
      2:
      begin
        pen := SelectObject( h, CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNSHADOW ) ) );
        b := SelectObject( h, GetStockObject( DKGRAY_BRUSH ) );
      end;
    end;
    if (Up and not FRoller) or (not Up and FRoller) then
      PolyGon( h, p, 3 )
    else
    begin
      Inc( p[2].x );
      if Up then
        Inc( p[2].y )
      else
        Dec( p[2].y );
      PolyLine( h, p, 3 );    
      Inc( p[0].x );
      Dec( p[2].x );
      if Up then
        Inc( p[1].y )
      else
        Dec( p[1].y );
      PolyLine( h, p, 3 );      
    end;
   SelectObject( h, b );    
    if co = 2 then
      DeleteObject( SelectObject( h, pen ) )
    else
      SelectObject( h, pen );
  end;
  
begin
  if not (csDesigning in ComponentState) then
    with TForm(Owner) do
      if not (BorderStyle = bsNone) then
      begin
        h := GetWindowDC( Handle );
        if FVisible then
        begin
          if DrawPushed then
            st := DFCS_PUSHED
          else
            st := 0;
          DrawFrameControl( h, ButtonArea, DFC_BUTTON, DFCS_BUTTONPUSH or st );
          if FEnabled then
          begin
            DrawTriangle( True, 0, 0 );
            DrawTriangle( False, 0, 0 );
          end
          else
          begin
            DrawTriangle( True, 1, 1 );
            DrawTriangle( False, 1, 1 );
            DrawTriangle( True, 0, 2 );
            DrawTriangle( False, 0, 2 );        
          end;
        end
        else
        begin
          if Active then
            c := COLOR_ACTIVECAPTION
          else
            c := COLOR_INACTIVECAPTION;
          b := CreateSolidBrush( GetSysColor( c ) );
          FillRect( h, ButtonArea, b );
          DeleteObject( b );
        end;
        ReleaseDC( Handle, h );
      end;
end;

procedure TWinRoller.SetEnabled( Val: Boolean );
begin
  if Val <> FEnabled then
  begin
    FEnabled := Val;
    PaintRollerButton;
  end;
end;

procedure TWinRoller.Rollup;
var
  y: Integer;
  r: TRect;
begin
  with TForm(Owner) do
  begin
    y := GetSystemMetrics( SM_CYCAPTION );
    if BorderStyle in [bsSingle, bsDialog, bsToolWindow] then
      Inc( y, GetSystemMetrics(SM_CYFIXEDFRAME) )
    else
      Inc( y, GetSystemMetrics(SM_CYSIZEFRAME) );
    SetWindowRgn( Handle, 0, False );
    if rgn <> 0 then
    begin
      DeleteObject( rgn );
      rgn := 0;
    end;    
    GetWindowRect( Handle, r );
    rgn := CreateRectRgn( 0, 0, r.Right - r.Left, y );
    SetWindowRgn( Handle, rgn, True );
  end;
end;

procedure TWinRoller.SetRoller( Val: Boolean );
begin
  if FEnabled and (Val <> FRoller) then
  begin
    FRoller := Val;
    if Val then
    begin
      Rollup;
      if Assigned( FOnRoller ) then FOnRoller( Self, mdRollUp );
    end
    else
    begin
      SetWindowRgn( TForm(Owner).Handle, 0, True );
      if rgn <> 0 then
      begin
        DeleteObject( rgn );
        rgn := 0;
      end;
      if Assigned( FOnRoller ) then FOnRoller( Self, mdRollDown );
    end;
    PaintRollerButton;
  end;
end;

procedure TWinRoller.SetVisible( Val: Boolean );
begin
  if Val <> FVisible then
  begin
    FVisible := Val;
    CalcArea;
    PaintRollerButton;
  end;
end;

procedure TWinRoller.WinProc(var Message: TMessage);
var
  v: Boolean;
  
  procedure Default;
  begin
    with Message do
      Result := CallWindowProc(DefWinProc, TForm(Owner).Handle, Msg, wParam, lParam);
  end;

  function InArea( InClient: Boolean ): Boolean;
  var
    p: TPoint;
  begin
    p.x := Message.lParamLo;
    p.y := Smallint(Message.lParamHi);
    if InClient then
      ClientToScreen( TForm(Owner).Handle, p );
    Dec( p.x, TForm(Owner).Left );
    Dec( p.y, TForm(Owner).Top );
    Result := PtInRect( ButtonArea, p );
  end;

begin
  if not FVisible then
    Default
  else
  with Message do
    case Msg of
      WM_MOVE:
      begin
        Default;
        Stop := True;
      end;
      WM_SIZE, WM_WINDOWPOSCHANGED:
      begin
        Default;
        v := FVisible;
        FVisible := False;
        PaintRollerButton;
        CalcArea;
        if FRoller and not Stop then Rollup;
        FVisible := v;
//        TForm(Owner).Invalidate;
        PaintRollerButton;
        Stop := False;
      end;
      WM_MOUSEMOVE:
      begin
        if Pushed then
        begin
          if not InArea( True ) then
          begin
            if DrawPushed then
            begin
              DrawPushed := False;
              if FEnabled then
                PaintRollerButton;
            end;
          end
          else
          begin
            if not DrawPushed then
            begin
              DrawPushed := True;
              if FEnabled then
                PaintRollerButton;
            end;
          end;
          Result := 1;
        end
        else
          Default;
      end;
      WM_LBUTTONUP, WM_LBUTTONDBLCLK:
      begin
        DrawPushed := False;
        if Pushed then
        begin
          if InArea( True ) then
          begin
            Stop := True;
            Roller := not FRoller;
            Stop := False;
          end
          else if FEnabled then
            PaintRollerButton;
          Result := 1;
        end
        else
          Default;
        Pushed := False;
        ReleaseCapture;
      end;
      WM_NCLBUTTONDOWN, WM_NCLBUTTONDBLCLK:
      begin
        if InArea( False ) then
        begin
          SetCapture( TForm(Owner).Handle );
          DrawPushed := True;
          Pushed := True;
          if FEnabled then
            PaintRollerButton;
          Result := 1;
        end;
        if Msg = WM_NCLBUTTONDOWN then
          Default;
      end;      
      WM_SETTINGCHANGE: 
      begin
        Default;
        CalcArea;
        if FRoller then
        begin
          Stop := True;
          Rollup;
          Stop := False;
        end;
        PaintRollerButton;
//        TForm(Owner).Invalidate;
      end;
      WM_NCACTIVATE, WM_NCPAINT:
      begin
        Default;
//        with Message do
//          if (Msg = WM_NCACTIVATE) and (wParam = 0) then
//            Result := 1;
        PaintRollerButton;
      end;
      else
        Default;
    end;
end;

end.
 