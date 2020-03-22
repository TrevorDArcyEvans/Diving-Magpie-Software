{*******************************************************}
{                                                       }
{       TScreenCapture                                  }
{                                                       }
{       Copyright (c) 1997 Alexander Halser             }
{       -----------------------------------             }
{       You will find more interesting programs and     }
{       components on:                                  }
{                                                       }
{       http://www.easycash.co.at/delphi                }
{       EMail: halser@easycash.co.at                    }
{                                                       }
{*******************************************************}

unit SCapture;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, ComCtrls, Menus, Clipbrd;

type
  TScreenCapture = class(TCustomControl)
  private
    fBitmap: TBitmap;
    fActive: Boolean;
    fAutocopy: Boolean;
    fDesktop: Boolean;
    fOnCapture: TNotifyEvent;
    procedure SetActive(Value: Boolean);
  protected
    procedure loaded; override;
    procedure WndProc(var Message: TMessage); override;
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    function    Bitmap: TBitmap;
    procedure   Capture;
    procedure   Copytoclipboard;
  published
    property Autocopy: Boolean read fAutocopy write fAutocopy;
    property Active: Boolean read fActive write SetActive;
    property Desktop: Boolean read fDesktop write fDesktop;
    property OnCapture: TNotifyEvent read fOnCapture write fOnCapture;
  end;

procedure Register;

implementation


constructor TScreenCapture.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  fBitmap := TBitmap.create;
  fActive := false;
  Visible := false;
  height := 28;
  width := 28;
end;

destructor TScreenCapture.Destroy;
begin
  fBitmap.free;
  inherited Destroy;
end;

procedure TScreenCapture.Paint;
var
   PaintRect: TRect;
   Bmp: TBitmap;
   ResName : array[0..15] of char;
begin
   if (csDesigning in ComponentState) then
   begin
        PaintRect := Rect(0, 0, Width, Height);
        Frame3D(Canvas, PaintRect, clBtnHighlight, clBtnShadow, 1);
        Bmp := TBitmap.create;
        StrPCopy(ResName,classname);
        Bmp.handle := LoadBitmap(hinstance,ResName);
        BitBlt(canvas.handle, 2, 2, ClientRect.Right-4, ClientRect.Bottom-4, Bmp.canvas.handle, 0, 0, SRCCOPY);
        Bmp.free;
   end;
end;

function TScreenCapture.Bitmap: TBitmap;
begin
     result := fBitmap;
end;

procedure TScreenCapture.SetActive(Value: Boolean);
begin
     fActive := Value;
end;

procedure TScreenCapture.loaded;
begin
  if not (csDesigning in ComponentState) then RegisterHotkey(handle, IDHOT_SNAPWINDOW, MOD_ALT, VK_F12);
end;

procedure TScreenCapture.WndProc(var Message: TMessage);
begin
    if (Message.Msg = WM_HOTKEY) and (Message.wParam = IDHOT_SNAPWINDOW) and fActive then Capture;
    inherited WndProc(Message);
end;

procedure TScreenCapture.Capture;
var
   winHWND: HWND;
   winDC: HDC;
   Rect: TRect;
begin
     if fDesktop then
     begin
          winHWND := GetDesktopWindow();
          winDC := GetDC(winHWND);
     end else
     begin
          winHWND := Getforegroundwindow();
          winDC := GetwindowDC(winHWND);
     end;
     GetWindowRect(winHWND, rect);
     fBitmap.width := rect.right-rect.left;
     fBitmap.height := rect.bottom-rect.top;
     BitBlt(fBitmap.canvas.handle, 0, 0, fBitmap.width, fBitmap.height, winDC, 0, 0, SRCCOPY);
     ReleaseDC(winHWND, winDC);

     if fAutocopy then Copytoclipboard;
     if assigned(fOnCapture) then fOnCapture(self);
end;

procedure TScreenCapture.CopyToClipboard;
var
   AFormat : Word;
   AData : integer;
   APalette : HPALETTE;
begin
     //fBitmap.SaveToClipBoardFormat(AFormat,AData,APalette);
     //Clipboard.SetAsHandle(AFormat,AData);
end;

procedure Register;
begin
  RegisterComponents('Win32', [TScreenCapture]);
end;

end.
