unit bi_ctrls;

interface

uses Windows, Messages, Classes, Controls, Forms, Graphics,
  ExtCtrls, buttons, bi_timer, sysutils;

type

  TBI_Loupe = class(TGraphicControl)
  private
    _timer:tbi_timer;
    x,y                  : integer;
    DC,dcpuffer,puffer   : hdc;
    fzoom                : double;
    factive              : boolean;
    mybuffer             : tbitmap;
    finterval            : integer;
    fbeveli              : tpanelbevel;
    fbevelo              : tpanelbevel;
    fbevelwidth          : tbevelwidth;
    fdesign              : boolean;
    procedure _mypaint(sender:tobject);
    procedure Resized;
    procedure SetZoom(value:double);
    procedure SetInterval(value:integer);
    procedure SetActive(value:boolean);
    procedure SetDesign(value:boolean);
    procedure SetBeveLi(value:tpanelbevel);
    procedure SetBeveLo(value:tpanelbevel);
    procedure SetBevelWidth(value:tbevelwidth);
    procedure PaintCrosshairs;
  protected
  procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure SaveToFile(s1:string);
  published
    property ZoomLevel:double read fzoom write setzoom;
    property Interval:integer read finterval write setinterval;
    property Active:boolean read factive write setactive;
    property BevelInner:tpanelbevel read fbeveli write setbeveli;
    property BevelOuter:tpanelbevel read fbevelo write setbevelo;
    property Bevelwidth:tbevelwidth read fbevelwidth write setbevelwidth;
    property DrawDesigning:boolean read fdesign write setdesign;
    property Visible;
    property OnClick;
    property OnDblClick;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property ShowHint;
    property ParentFont;
    property Align;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
  end;


implementation

uses consts, bi_procs;

type myrgb=record r:byte;
                g:byte;
                b:byte; end;

//<----------------------------------------------Loupe

constructor TBI_Loupe.Create(AOwner: TComponent);
begin
    inherited Create(AOwner);
    ControlStyle := [csclickevents, csCaptureMouse, csOpaque, csDoubleClicks];
    mybuffer:=tbitmap.create;
    mybuffer.width:=100;
    mybuffer.height:=100;
    _timer:=TBI_timer.create(self);
    _timer.interval:=100;
    finterval:=100;
    width:=100;
    height:=100;
    fbeveli:=bvRaised;
    fbevelwidth:=1;
    fbevelo:=bvlowered;
    fzoom:=1;
    fdesign:=false;
    dc := createdc('DISPLAY',Nil,Nil,Nil);
    dcpuffer := createcompatibledc(dc);
    x:=round(width / fzoom);
    y:=round(height / fzoom);
    if puffer<>0 then deletedc(puffer);
    puffer := createcompatiblebitmap(dc,x,y);
    selectobject(dcpuffer,puffer);
    _timer.enabled:=false;
    active:=false;
    _timer.ontimer:=_mypaint;
end;

destructor TBI_Loupe.Destroy;
begin
    _timer.enabled:=false;
    deletedc(puffer);
    deletedc(dcpuffer);
    deletedc(dc);
    _timer.free;
    mybuffer.free;
    inherited Destroy;
end;

procedure TBI_Loupe._mypaint(Sender: TObject);
    var  position             : tpoint;
begin
    if (csdesigning in componentstate) and (not fdesign) then exit;
    getcursorpos(position);
    bitblt (dcpuffer,0,0,width,height,dc,
         position.x-(x div 2),position.y-(y div 2),SRCCOPY);
    stretchblt (mybuffer.canvas.handle,0,0,width,height,
         DCPuffer,0,0,x,y,SRCCOPY);
    repaint;
end;

procedure TBI_Loupe.Resized;
begin
    mybuffer.width:=width;
    mybuffer.height:=height;
    x:=round(width / fzoom);
    y:=round(height / fzoom);
    if puffer<>0 then deletedc(puffer);
    puffer := createcompatiblebitmap(dc,x,y);
    selectobject(dcpuffer,puffer);
    //PaintCrosshairs(self);
end;

procedure TBI_Loupe.SetZoom(value:double);
begin
    if value > 0 then fzoom:=value else fzoom:=1;
    x:=round(width / fzoom);
    y:=round(height / fzoom);
    if puffer<>0 then deletedc(puffer);
    puffer := createcompatiblebitmap(dc,x,y);
    selectobject(dcpuffer,puffer);
end;

procedure TBI_Loupe.SetInterval(value:integer);
begin
    _timer.enabled:=false;
    finterval:=value;
    _timer.interval:=finterval;
    _timer.enabled:=true;
end;

procedure TBI_Loupe.SetActive(value:boolean);
begin
    factive:=value;
    _timer.enabled:=factive;
end;

procedure TBI_Loupe.Paint;
    var _rect:trect;
    topcolor,bottomcolor:tcolor;
begin
    if (mybuffer.width<>width) or (mybuffer.height<>height) then resized;
        _Rect := GetClientRect;
    if BevelOuter <> bvNone then
    begin
        TopColor := clBtnHighlight;
        if BevelOuter = bvLowered then TopColor := clBtnShadow;
        BottomColor := clBtnShadow;
        if BevelOuter = bvLowered then BottomColor := clBtnHighlight;
        Frame3D(mybuffer.Canvas, _Rect, TopColor, BottomColor, BevelWidth);
    end;
    if BevelInner <> bvNone then
    begin
        TopColor := clBtnHighlight;
        if BevelInner = bvLowered then TopColor := clBtnShadow;
        BottomColor := clBtnShadow;
        if BevelInner = bvLowered then BottomColor := clBtnHighlight;
        Frame3D(mybuffer.Canvas, _Rect, TopColor, BottomColor, BevelWidth);
    end;

    bitblt(canvas.handle,canvas.cliprect.left,canvas.cliprect.top,
    canvas.cliprect.right,canvas.cliprect.bottom,mybuffer.canvas.handle,
    canvas.cliprect.left,canvas.cliprect.top,srccopy);
end;

procedure TBI_Loupe.PaintCrosshairs;
begin
    {bevel1.left:=(image1.width div 2)-1;
    bevel1.top:=(image1.height div 2)-10;
    bevel2.left:=(image1.width div 2)-10;
    bevel2.top:=(image1.height div 2)-1;}
end;

procedure TBI_Loupe.SaveToFile(s1:string);
begin
    _timer.enabled:=false;
    mybuffer.SaveToFile(s1);
    _timer.enabled:=factive;
end;

procedure TBI_Loupe.SetBeveLi(value:tpanelbevel);
begin
    fbeveli:=value;
    invalidate;
end;

procedure TBI_Loupe.SetBeveLo(value:tpanelbevel);
begin
    fbevelo:=value;
    invalidate;
end;

procedure TBI_Loupe.SetDesign(value:boolean);
begin
    fdesign:=value;
    invalidate;
end;

procedure TBI_Loupe.SetBevelWidth(value:tbevelwidth);
begin
    fbevelwidth:=value;
    invalidate;
end;


end.
