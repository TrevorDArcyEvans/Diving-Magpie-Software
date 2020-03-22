unit FlEdit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TFloatEdit = class(TEdit)
  private
    { Private-Deklarationen }
    FDigits : byte;
    FMin,FMax    : extended;
    fdec         : char;
    Fertext      : string;
    foldval      : extended;
  protected
    { Protected-Deklarationen }
    procedure setvalue(Newvalue : extended);
    procedure setmin(Newvalue : extended);
    procedure setmax(Newvalue : extended);
    procedure setdigits(Newvalue : byte);
    function getvalue : extended;
    procedure KeyPress(var Key: Char); override;
    procedure doexit;override;
    procedure doEnter;override;
  public
    { Public-Deklarationen }
  published
    { Published-Deklarationen }
    property Digits   : byte read FDigits write setDigits;
    property Value    : extended read getvalue write setValue;
    property Min : extended read Fmin write setMin;
    property Max : extended read Fmax write setmax;
    property ErrorMessage :string read fertext write fertext;
    constructor create (aowner : TComponent);override;
  end;

procedure Register;
const
    notext       = '[No Text]';

implementation
constructor TFloatEdit.create (aowner : TComponent);
begin
     inherited create(aowner);
     fdec := decimalseparator;
     fdigits := 1;
     fmin := 0;
     fmax := 99999999.9;
     fertext := notext;
     setvalue(0.0);
end;

procedure Register;
begin
  RegisterComponents('Samples', [TFloatEdit]);
end;

procedure tfloatedit.doenter;
begin
     foldval:=getvalue;
     inherited;
end;

procedure TFloatedit.doexit;
var ts : string;
    result:extended;
begin
     ts := text;
     inherited;
        try
           result := strtofloat(ts);
        except
           if fertext <> notext then showmessage(fertext);
           setvalue(foldval);
           selectall;
           setfocus;
           exit;
        end;
        if (result < fmin) or (result > fmax) then begin
           if fertext <> notext then showmessage(fertext);
           setvalue(foldval);
           selectall;
           setfocus;
           exit;
        end;
        // Ausgabe formatieren
        text := floattostrf(result,fffixed,18,fdigits);
        value:=strtofloat(text);
        inherited;
end;

procedure TFloatedit.setvalue(Newvalue : extended);
var tmp : string;
begin
        if newvalue > fmax then begin
           if fertext <> notext then showmessage(fertext);
           newvalue := fmax;
        end;
        if newvalue < fmin then begin
           if fertext <> notext then showmessage(fertext);
           newvalue := fmin;
        end;
        tmp := floattostrf(newvalue,fffixed,18,fdigits);
        text:=tmp;
end;

function TFloatedit.getvalue : extended;
var ts : string;
begin
        ts := text;
        if (ts = '-') or (ts = fdec) or (ts = '') then ts := '0';
        try
           result := strtofloat(ts);
        except
           //if fertext <> notext then showmessage(fertext);
           result := fmin;
        end;
        if result < fmin then begin
           //if fertext <> notext then showmessage(fertext);
           result := fmin;
        end;
        if result > fmax then begin
           //if fertext <> notext then showmessage(fertext);
           result := fmax;
        end;
end;

procedure TFloatedit.setdigits;
begin
     if fdigits <> newValue then begin
        if newvalue > 18 then newvalue := 18;
        fdigits := newvalue;
        setvalue(getvalue);
     end;
end;
procedure TFloatedit.setmin;
begin
     if fmin <> newValue then begin
        if fmin > fmax then begin
	   showmessage('Min-Value has to be less than or equal to Max-Value !');
           newvalue := fmax;
	end;	
	fmin := newvalue;
        setvalue(getvalue);
     end;
end;
procedure TFloatedit.setmax;
begin
     if fmax <> newValue then begin
        if fmin > fmax then begin
	   showmessage('Max-Value has to be greater than or equal to Min-Value !');
           newvalue := fmin;
	end;	
        fmax := newvalue;
        setvalue(getvalue);
     end;
end;


procedure TFloatedit.keypress;
var    ts           : string;
       result           : extended;
begin
     if key = #27 then begin
        setvalue(foldval);
        selectall;
        inherited;
        exit;
     end;
     if key < #32 then begin
        inherited;
        exit;
     end;
        ts := copy(text,1,selstart)+copy(text,selstart+sellength+1,500);
     if (key <'0') or (key > '9') then if (key <> fdec) and (key <> '-') then begin
        inherited;
        key := #0;
        exit;
     end;
     if key = fdec then if pos(fdec,ts) <> 0 then begin
        inherited;
        key := #0;
        exit;
     end;
     if key = '-' then if pos('-',ts) <> 0 then begin
        inherited;
        key := #0;
        exit;
     end;
     if key = '-' then if fmin >= 0 then begin
        inherited;
        key := #0;
        exit;
     end;
     if key = fdec then if fdigits = 0 then begin
        inherited;
        key := #0;
        exit;
     end;
     // seltext durch key ersetzen
        ts := copy(text,1,selstart)+key+copy(text,selstart+sellength+1,500);
     // Überprüfen, ob gültiger wert;
     if key > #32 then if pos(fdec,ts)<> 0 then begin
        if length(ts)-pos(fdec,ts) > fdigits then begin
           inherited;
           key := #0;
           exit;
        end;
     end;
     if key = '-' then if pos('-',ts) <> 1 then begin
        inherited;
        key := #0;
        exit;
     end;

     if ts ='' then begin
        inherited;key := #0;
        text := floattostrf(fmin,fffixed,18,fdigits);selectall;
        exit;
     end;
     if ts = '-' then begin
        inherited;key:=#0;
        text := '-0';selstart := 1;sellength:=1;
        exit;
     end;
     if ts = fdec then begin
        inherited;key:=#0;
        text := '0'+fdec+'0';
        selstart :=2;
        sellength:=1;
        exit;
     end;
     inherited;
end;
end.
