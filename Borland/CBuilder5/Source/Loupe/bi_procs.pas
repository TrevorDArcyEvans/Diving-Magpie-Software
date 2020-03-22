unit bi_procs;

interface

//Some of the code here was adapted from code found in the Microsoft Knowledge Base

uses Windows, Classes, Graphics, Forms, Controls, Grids, Dialogs,sysutils,buttons;

procedure DrawBitmapTransparent(Dest: TCanvas; XOrigin, YOrigin: Integer;
  Bitmap: TBitmap; TransparentColor: TColor);
procedure DrawBitmapRectTransparent(Dest: TCanvas; XOrigin, YOrigin: Integer;
  Rect: TRect; Bitmap: TBitmap; TransparentColor: TColor);
procedure StretchBitmapRectTransparent(Dest: TCanvas; X, Y, W, H: Integer;
  Rect: TRect; Bitmap: TBitmap; TransparentColor: TColor);
procedure mygrayedbmp(var bmp1:tbitmap;const c1,c2:tcolor);
procedure DrawPopupMark(theCanvas: TCanvas; x, y: Integer);

   procedure CMYKTORGB(C : byte;
                     M: byte;
                     Y : byte;
                     K : byte;
                     var R : byte;
                     var G : byte;
                     var B : byte);
   procedure RGBTOCMYK(R : byte;
                     G : byte;
                     B : byte;
                     var C : byte;
                     var M : byte;
                     var Y : byte;
                     var K : byte);

var
  HSLRange : integer = 240;

procedure HSLtoRGB (H, S, L: double;var r,g,b:byte);
procedure HSLRangeToRGB (H, S, L : integer;var r,g,b:byte);
procedure RGBtoHSL (r,g,b:byte; var H, S, L : double);
procedure RGBtoHSLRange (r,g,b:byte; var H, S, L : byte);
procedure myDrawButtonFace(Canvas: TCanvas; const Client: TRect;
  BevelWidth: Integer; IsDown:boolean;c1,c2:tcolor);
function booltoint(const b1:boolean):integer;

function getcolorcaps:byte;

type myrgb=record r:byte;
                g:byte;
                b:byte; end;

implementation

const TransparentMask = $02000000;

type
    EDIB = class(Exception);

function Max(const A, B: Longint): Longint;
begin
  if A > B then Result := A
  else Result := B;
end;

function Min(const A, B: Longint): Longint;
begin
  if A < B then Result := A
  else Result := B;
end;

function WidthOf(const R: TRect): Integer;
begin
  Result := R.Right - R.Left;
end;

function HeightOf(const R: TRect): Integer;
begin
  Result := R.Bottom - R.Top;
end;

{**************************************************************************}

{ Transparent bitmap }

procedure DrawTransparentBitmapRect(DC: HDC; Bitmap: HBitmap; xStart, yStart,
  Width, Height: Integer; Rect: TRect; TransparentColor: TColorRef);
var
{$IFDEF WIN32}
  BM: Windows.TBitmap;
{$ELSE}
  BM: WinTypes.TBitmap;
{$ENDIF}
  cColor: TColorRef;
  bmAndBack, bmAndObject, bmAndMem, bmSave: HBitmap;
  bmBackOld, bmObjectOld, bmMemOld, bmSaveOld: HBitmap;
  hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave: HDC;
  ptSize, ptRealSize, ptBitSize, ptOrigin: TPoint;
begin
  hdcTemp := CreateCompatibleDC(DC);
  SelectObject(hdcTemp, Bitmap);      { Select the bitmap    }
  GetObject(Bitmap, SizeOf(BM), @BM);
  ptRealSize.x := Min(Rect.Right - Rect.Left, BM.bmWidth - Rect.Left);
  ptRealSize.y := Min(Rect.Bottom - Rect.Top, BM.bmHeight - Rect.Top);
  DPtoLP(hdcTemp, ptRealSize, 1);
  ptOrigin.x := Rect.Left;
  ptOrigin.y := Rect.Top;
  DPtoLP(hdcTemp, ptOrigin, 1);       { Convert from device  }
                                      { to logical points    }
  ptBitSize.x := BM.bmWidth;          { Get width of bitmap  }
  ptBitSize.y := BM.bmHeight;         { Get height of bitmap }
  DPtoLP(hdcTemp, ptBitSize, 1);
  if (ptRealSize.x = 0) or (ptRealSize.y = 0) then begin
    ptSize := ptBitSize;
    ptRealSize := ptSize;
  end
  else ptSize := ptRealSize;
  if (Width = 0) or (Height = 0) then begin
    Width := ptSize.x;
    Height := ptSize.y;
  end;

  { Create some DCs to hold temporary data }
  hdcBack   := CreateCompatibleDC(DC);
  hdcObject := CreateCompatibleDC(DC);
  hdcMem    := CreateCompatibleDC(DC);
  hdcSave   := CreateCompatibleDC(DC);
  { Create a bitmap for each DC. DCs are required for a number of }
  { GDI functions                                                 }
  { Monochrome DC }
  bmAndBack   := CreateBitmap(ptSize.x, ptSize.y, 1, 1, nil);
  bmAndObject := CreateBitmap(ptSize.x, ptSize.y, 1, 1, nil);
  bmAndMem    := CreateCompatibleBitmap(DC, Max(ptSize.x, Width), Max(ptSize.y, Height));
  bmSave      := CreateCompatibleBitmap(DC, ptBitSize.x, ptBitSize.y);
  { Each DC must select a bitmap object to store pixel data }
  bmBackOld   := SelectObject(hdcBack, bmAndBack);
  bmObjectOld := SelectObject(hdcObject, bmAndObject);
  bmMemOld    := SelectObject(hdcMem, bmAndMem);
  bmSaveOld   := SelectObject(hdcSave, bmSave);
  { Set proper mapping mode }
  SetMapMode(hdcTemp, GetMapMode(DC));

  { Save the bitmap sent here, because it will be overwritten }
  BitBlt(hdcSave, 0, 0, ptBitSize.x, ptBitSize.y, hdcTemp, 0, 0, SRCCOPY);
  { Set the background color of the source DC to the color,         }
  { contained in the parts of the bitmap that should be transparent }
  cColor := SetBkColor(hdcTemp, TransparentColor);
  { Create the object mask for the bitmap by performing a BitBlt()  }
  { from the source bitmap to a monochrome bitmap                   }
  BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, ptOrigin.x, ptOrigin.y,
    SRCCOPY);
  { Set the background color of the source DC back to the original  }
  { color                                                           }
  SetBkColor(hdcTemp, cColor);
  { Create the inverse of the object mask }
  BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
    NOTSRCCOPY);
  { Copy the background of the main DC to the destination }
  BitBlt(hdcMem, 0, 0, Width, Height, DC, xStart, yStart,
    SRCCOPY);
  { Mask out the places where the bitmap will be placed }
  StretchBlt(hdcMem, 0, 0, Width, Height, hdcObject, 0, 0,
    ptSize.x, ptSize.y, SRCAND);
  {BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);}
  { Mask out the transparent colored pixels on the bitmap }
  BitBlt(hdcTemp, ptOrigin.x, ptOrigin.y, ptSize.x, ptSize.y, hdcBack, 0, 0,
    SRCAND);
  { XOR the bitmap with the background on the destination DC }
  StretchBlt(hdcMem, 0, 0, Width, Height, hdcTemp, ptOrigin.x, ptOrigin.y,
    ptSize.x, ptSize.y, SRCPAINT);
  {BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, ptOrigin.x, ptOrigin.y,
    SRCPAINT);}
  { Copy the destination to the screen }
  BitBlt(DC, xStart, yStart, Max(ptRealSize.x, Width), Max(ptRealSize.y, Height),
    hdcMem, 0, 0, SRCCOPY);
  { Place the original bitmap back into the bitmap sent here }
  BitBlt(hdcTemp, 0, 0, ptBitSize.x, ptBitSize.y, hdcSave, 0, 0, SRCCOPY);

  { Delete the memory bitmaps }
  DeleteObject(SelectObject(hdcBack, bmBackOld));
  DeleteObject(SelectObject(hdcObject, bmObjectOld));
  DeleteObject(SelectObject(hdcMem, bmMemOld));
  DeleteObject(SelectObject(hdcSave, bmSaveOld));
  { Delete the memory DCs }
  DeleteDC(hdcMem);
  DeleteDC(hdcBack);
  DeleteDC(hdcObject);
  DeleteDC(hdcSave);
  DeleteDC(hdcTemp);
end;

procedure DrawTransparentBitmap(DC: HDC; Bitmap: HBitmap;
  xStart, yStart: Integer; TransparentColor: TColorRef);
begin
  DrawTransparentBitmapRect(DC, Bitmap, xStart, yStart, 0, 0, Rect(0, 0, 0, 0),
    TransparentColor);
end;

procedure InternalDrawTransBmpRect(Dest: TCanvas; X, Y, W, H: Integer;
  Rect: TRect; Bitmap: TBitmap; TransparentColor: TColor);
var
  MemImage: TBitmap;
  R: TRect;
begin
  MemImage := TBitmap.Create;
  try
    R := Bounds(0, 0, Bitmap.Width, Bitmap.Height);
    if TransparentColor = clNone then begin
      if (WidthOf(Rect) <> 0) and (HeightOf(Rect) <> 0) then R := Rect;
      MemImage.Width := WidthOf(R);
      MemImage.Height := HeightOf(R);
      MemImage.Canvas.CopyRect(Bounds(0, 0, MemImage.Width, MemImage.Height),
        Bitmap.Canvas, R);
      if (W = 0) or (H = 0) then Dest.Draw(X, Y, MemImage)
      else Dest.StretchDraw(Bounds(X, Y, W, H), MemImage);
    end
    else  begin
      MemImage.Width := WidthOf(R);
      MemImage.Height := HeightOf(R);
      MemImage.Canvas.CopyRect(R, Bitmap.Canvas, R);
      DrawTransparentBitmapRect(Dest.Handle, MemImage.Handle, X, Y, W, H,
        Rect, ColorToRGB(TransparentColor and not TransparentMask));
      { TBitmap.TransparentColor property return TColor value equal   }
      { to (Bitmap.Canvas.Pixels[0, Height - 1] or TransparentMask).  }
    end;
  finally
    MemImage.Free;
  end;
end;

procedure StretchBitmapRectTransparent(Dest: TCanvas; X, Y, W, H: Integer;
  Rect: TRect; Bitmap: TBitmap; TransparentColor: TColor);
begin
  InternalDrawTransBmpRect(Dest, X, Y, W, H, Rect, Bitmap,
    TransparentColor);
end;

procedure DrawBitmapRectTransparent(Dest: TCanvas; XOrigin, YOrigin: Integer;
  Rect: TRect; Bitmap: TBitmap; TransparentColor: TColor);
begin
  InternalDrawTransBmpRect(Dest, XOrigin, YOrigin, 0, 0, Rect, Bitmap,
    TransparentColor);
end;

procedure DrawBitmapTransparent(Dest: TCanvas; XOrigin, YOrigin: Integer;
  Bitmap: TBitmap; TransparentColor: TColor);
begin
  InternalDrawTransBmpRect(Dest, XOrigin, YOrigin, 0, 0, Rect(0, 0, 0, 0),
    Bitmap, TransparentColor);
end;

{ ChangeBitmapColor. This function create new TBitmap object.
  You must destroy it outside by calling TBitmap.Free method. }

function ChangeBitmapColor(Bitmap: TBitmap; Color, NewColor: TColor): TBitmap;
var
  R: TRect;
begin
  Result := TBitmap.Create;
  try
    with Result do begin
      Height := Bitmap.Height;
      Width := Bitmap.Width;
      R := Bounds(0, 0, Width, Height);
      Canvas.Brush.Color := NewColor;
      Canvas.FillRect(R);
      Canvas.BrushCopy(R, Bitmap, R, Color);
    end;
  except
    Result.Free;
    raise;
  end;
end;

{ CreateDisabledBitmap. Creating TBitmap object with disable button glyph
  image. You must destroy it outside by calling TBitmap.Free method. }

function CreateDisabledBitmap(FOriginal: TBitmap; OutlineColor: TColor): TBitmap;
const
  ROP_DSPDxax = $00E20746;
var
  MonoBmp: TBitmap;
  IRect: TRect;
begin
  IRect := Rect(0, 0, FOriginal.Width, FOriginal.Height);
  Result := TBitmap.Create;
  try
    Result.Width := FOriginal.Width;
    Result.Height := FOriginal.Height;
    MonoBmp := TBitmap.Create;
    try
      with MonoBmp do begin
        Assign(FOriginal);
{$IFDEF RX_D3}
        HandleType := bmDDB;
{$ENDIF}
        Canvas.Brush.Color := clBlack;
        if Monochrome then begin
          Canvas.Font.Color := clWhite;
          Monochrome := False;
          Canvas.Brush.Color := clWhite;
        end;
        Monochrome := True;
      end;
      with Result.Canvas do begin
        Brush.Color := clBtnFace;
        FillRect(IRect);
        Brush.Color := clBtnHighlight;
        SetTextColor(Handle, clBlack);
        SetBkColor(Handle, clWhite);
        BitBlt(Handle, 1, 1, WidthOf(IRect), HeightOf(IRect),
          MonoBmp.Canvas.Handle, 0, 0, ROP_DSPDxax);
        Brush.Color := clBtnShadow;
        SetTextColor(Handle, clBlack);
        SetBkColor(Handle, clWhite);
        BitBlt(Handle, 0, 0, WidthOf(IRect), HeightOf(IRect),
          MonoBmp.Canvas.Handle, 0, 0, ROP_DSPDxax);
      end;
    finally
      MonoBmp.Free;
    end;
  except
    Result.Free;
    raise;
  end;
end;

{**************************************************************************}

function CreateTwoColorsBrushPattern(Color1, Color2: TColor): TBitmap;
var
  X, Y: Integer;
begin
  Result := TBitmap.Create;
  Result.Width := 8;
  Result.Height := 8;
  with Result.Canvas do
  begin
    Brush.Style := bsSolid;
    Brush.Color := Color1;
    FillRect(Rect(0, 0, Result.Width, Result.Height));
    for Y := 0 to 7 do
      for X := 0 to 7 do
        if (Y mod 2) = (X mod 2) then  { toggles between even/odd pixles }
          Pixels[X, Y] := Color2;      { on even/odd rows }
  end;
end;

{**************************************************************************}


 procedure RGBTOCMYK(R : byte;
                     G : byte;
                     B : byte;
                     var C : byte;
                     var M : byte;
                     var Y : byte;
                     var K : byte);
 begin
   C := 255 - R;
   M := 255 - G;
   Y := 255 - B;
   if C < M then
     K := C else
     K := M;
   if Y < K then
     K := Y;
   if k > 0 then begin
     c := c - k;
     m := m - k;
     y := y - k;
   end;
 end;

 procedure CMYKTORGB(C : byte;
                     M: byte;
                     Y : byte;
                     K : byte;
                     var R : byte;
                     var G : byte;
                     var B : byte);
 begin
    if (Integer(C) + Integer(K)) < 255 then
      R := 255 - (C + K) else
      R := 0;
    if (Integer(M) + Integer(K)) < 255 then
      G := 255 - (M + K) else
      G := 0;
    if (Integer(Y) + Integer(K)) < 255 then
      B := 255 - (Y + K) else
      B := 0;
 end;

procedure mygrayedbmp(var bmp1:tbitmap;const c1,c2:tcolor);
var x,y,tmp:integer;
    _c:integer;
    __c:tcolor;
begin
if bmp1.width*bmp1.height>10000 then exit;
//I don't want the button spend hours for this when repainting.
//Anyway, only very dull people will use 100*100 glyphs, hopefully :-)
for x:=0 to bmp1.width do
    for y:=0 to bmp1.height do
        begin
            __c:=bmp1.canvas.pixels[x,y];
            if __c<>bmp1.canvas.pixels[0,0] then
               begin
               _c:=colortorgb(__c);
               tmp:= (_c shr 16)+
                     ((_c shr 8) and $00FF)+
                     (_c and $0000FF);
               if tmp>550 then bmp1.canvas.pixels[x,y]:=clwhite
               else
               if tmp>250 then bmp1.canvas.pixels[x,y]:=c1
               else
               if tmp>60 then bmp1.canvas.pixels[x,y]:=c2
               else bmp1.canvas.pixels[x,y]:=clblack;
               end;
        end;
end;


procedure DrawPopupMark(theCanvas: TCanvas; x, y: Integer);
var _pts    : array[1..3] of tpoint;
begin
	thecanvas.brush.color := theCanvas.font.Color;
        thecanvas.pen.color:=theCanvas.font.Color;
        _pts[1]:=point(x,y);
        _pts[2]:=point(x+3,y);
        _pts[3]:=point(x+2,y+2);
        thecanvas.polygon(_pts);
end;

procedure HSLtoRGB (H, S, L: double;var r,g,b:byte);
var
  M1,
  M2: double;
  function HueToColourValue (Hue: double) : byte;
  var
    V : double;
  begin
    if Hue < 0 then
      Hue := Hue + 1
    else
      if Hue > 1 then
        Hue := Hue - 1;

    if 6 * Hue < 1 then
      V := M1 + (M2 - M1) * Hue * 6
    else
      if 2 * Hue < 1 then
        V := M2
      else
        if 3 * Hue < 2 then
          V := M1 + (M2 - M1) * (2/3 - Hue) * 6
        else
          V := M1;
    Result := round (255 * V)
  end;
begin
  if S = 0 then
  begin
    R := round (255 * L);
    G := R;
    B := R
  end else begin
    if L <= 0.5 then
      M2 := L * (1 + S)
    else
      M2 := L + S - L * S;
    M1 := 2 * L - M2;
    R := HueToColourValue (H + 1/3);
    G := HueToColourValue (H);
    B := HueToColourValue (H - 1/3)
  end;
end;

procedure HSLRangeToRGB (H, S, L : integer;var r,g,b:byte);
begin
  HSLToRGB (H / (HSLRange-1), S / HSLRange, L / HSLRange,r,g,b)
end;

procedure RGBtoHSL (r,g,b:byte; var H, S, L : double);
  function Max (a, b : double): double;
  begin
    if a > b then
      Result := a
    else
      Result := b
  end;
  function Min (a, b : double): double;
  begin
    if a < b then
      Result := a
    else
      Result := b
  end;
var
  D,
  Cmax,
  Cmin: double;
begin
  Cmax := Max (R, Max (G, B));
  Cmin := Min (R, Min (G, B));
  L := (Cmax + Cmin) / 2;
  if Cmax = Cmin then  // it's grey
  begin
    H := 0; // it's actually undefined
    S := 0
  end else begin
    D := Cmax - Cmin;
    if L < 0.5 then
      S := D / (Cmax + Cmin)
    else
      S := D / (2 - Cmax - Cmin);
    if R = Cmax then
      H := (G - B) / D
    else
      if G = Cmax then
        H  := 2 + (B - R) /D
      else
        H := 4 + (R - G) / D;
    H := H / 6;
    if H < 0 then
      H := H + 1
  end
end;

procedure RGBtoHSLRange (r,g,b:byte; var H, S, L : byte);
var
  Hd,
  Sd,
  Ld: double;
begin
  RGBtoHSL (r,g,b, Hd, Sd, Ld);
  H := round (Hd * (HSLRange-1));
  S := round (Sd * HSLRange);
  L := round (Ld * HSLRange);
end;

function getcolorcaps:byte;
var ScreenDC: HDC;
begin
ScreenDC:=GetDC(0);
try
   result := (GetDeviceCaps(ScreenDC,BITSPIXEL) * GetDeviceCaps(ScreenDC, PLANES));
finally
   ReleaseDC(0, ScreenDC);
end;
end;

procedure myDrawButtonFace(Canvas: TCanvas; const Client: TRect;
  BevelWidth: Integer; IsDown:boolean;c1,c2:tcolor);
  {c1 & c2 reserved for future use}
var
  R: TRect;
  DC: THandle;
begin
  R := Client;
  with Canvas do
  begin
      Brush.Style := bsclear;
      DC := Canvas.Handle;   
      if IsDown then
      begin    { DrawEdge is faster than Polyline }
        DrawEdge(DC, R, BDR_SUNKENINNER, BF_TOPLEFT);              { black     }
        DrawEdge(DC, R, BDR_SUNKENOUTER, BF_BOTTOMRIGHT);          { btnhilite }
        Dec(R.Bottom);
        Dec(R.Right);
        Inc(R.Top);
        Inc(R.Left);
        DrawEdge(DC, R, BDR_SUNKENOUTER, BF_TOPLEFT); { btnshadow }
      end
      else
      begin
        DrawEdge(DC, R, BDR_RAISEDOUTER, BF_BOTTOMRIGHT);          { black }
        Dec(R.Bottom);
        Dec(R.Right);
        DrawEdge(DC, R, BDR_RAISEDINNER, BF_TOPLEFT);              { btnhilite }
        Inc(R.Top);
        Inc(R.Left);
        DrawEdge(DC, R, BDR_RAISEDINNER, BF_BOTTOMRIGHT); { btnshadow }
      end;
    end
end;

function booltoint(const b1:boolean):integer;
begin
if b1 then result:=1 else result:=0;
end;


end.
