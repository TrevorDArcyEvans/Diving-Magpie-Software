Unit tjoystk32;
{---------------------------------------------------}
{                                                   }
{ This code was written by : Daniel Carey           }
{                                                   }
{---------------------------------------------------}

interface

uses
  windows, sysutils, classes, {dsgnintf,} ExtCtrls, MMSystem;

type
    DCTimerEvent = procedure of object;
    TJoyMoveEvent = procedure(Sender:TObject; Position:Integer) of object;
    TButtonNotifyEvent = procedure(Sender:TObject; Pushed:Boolean )of object;
    TRepeatButton = ( Button01, Button02, Button03, Button04,
                      Button05, Button06, Button07, Button08,
                      Button09, Button10, Button11, Button12,
                      Button13, Button14, Button15, Button16,
                      Button17, Button18, Button19, Button20,
                      Button21, Button22, Button23, Button24,
                      Button25, Button26, Button27, Button28,
                      Button29, Button30, Button31, Button32 );
    TRepeatPosition = ( X, Y, Z, R, U, V, POV );

    TRepeatButtons = set of TRepeatButton;
    TRepeatPositions = set of TRepeatPosition;

  { The Thread class used in the joystick component }
  DCThread = class(TThread)
  private
    { Private declarations }
    FOnTimer : DCTimerEvent;
    FEnabled : Boolean;
    FRun : Boolean;
    FInterval : Integer;
  protected
    procedure Execute; override;
  published
    property OnTimer: DCTimerEvent read FOnTimer write FOnTimer;
    property Enabled: Boolean read FEnabled write FEnabled;
    property Run: Boolean read FRun write FRun;
    property Interval: Integer read FInterval write FInterval;
  end;

  { The main joystick component }
  TJoystick = class(TComponent)
  private
    { Private Declarations }

    { Joystick specific variables }
    JoyId: Word;
    JoyCaps: TJoyCaps;
    JoyInfoEx: TJoyInfoEx;

    {Range Calculation Variables }
    MinX : UINT;
    MinY : UINT;
    MinZ : UINT;
    MinR : UINT;
    MinU : UINT;
    MinV : UINT;
    DeltaX : UINT;
    DeltaY : UINT;
    DeltaZ : UINT;
    DeltaR : UINT;
    DeltaU : UINT;
    DeltaV : UINT;

    {Last Values of Joystick }
    LastX : UINT;
    LastY : UINT;
    LastZ : UINT;
    LastR : UINT;
    LastU : UINT;
    LastV : UINT;
    LastP : UINT;
    LastButton : array [1..32] of Boolean;

    FTimer : DCThread;

    FEnabled: Boolean; {tells whether event is enabled}
    FGamePort: integer;
    FNotifyRangeR: integer;
    FNotifyRangeU: integer;
    FNotifyRangeV: integer;
    FNotifyRangeX: integer;
    FNotifyRangeY: integer;
    FNotifyRangeZ: integer;
    FPollRate: integer;
    FPollPriority: TThreadPriority;
    FRepeatPositions: TRepeatPositions;
    FRepeatButtons: TRepeatButtons;
    FOnButton01: TButtonNotifyEvent;
    FOnButton02: TButtonNotifyEvent;
    FOnButton03: TButtonNotifyEvent;
    FOnButton04: TButtonNotifyEvent;
    FOnButton05: TButtonNotifyEvent;
    FOnButton06: TButtonNotifyEvent;
    FOnButton07: TButtonNotifyEvent;
    FOnButton08: TButtonNotifyEvent;
    FOnButton09: TButtonNotifyEvent;
    FOnButton10: TButtonNotifyEvent;
    FOnButton11: TButtonNotifyEvent;
    FOnButton12: TButtonNotifyEvent;
    FOnButton13: TButtonNotifyEvent;
    FOnButton14: TButtonNotifyEvent;
    FOnButton15: TButtonNotifyEvent;
    FOnButton16: TButtonNotifyEvent;
    FOnButton17: TButtonNotifyEvent;
    FOnButton18: TButtonNotifyEvent;
    FOnButton19: TButtonNotifyEvent;
    FOnButton20: TButtonNotifyEvent;
    FOnButton21: TButtonNotifyEvent;
    FOnButton22: TButtonNotifyEvent;
    FOnButton23: TButtonNotifyEvent;
    FOnButton24: TButtonNotifyEvent;
    FOnButton25: TButtonNotifyEvent;
    FOnButton26: TButtonNotifyEvent;
    FOnButton27: TButtonNotifyEvent;
    FOnButton28: TButtonNotifyEvent;
    FOnButton29: TButtonNotifyEvent;
    FOnButton30: TButtonNotifyEvent;
    FOnButton31: TButtonNotifyEvent;
    FOnButton32: TButtonNotifyEvent;
    FOnJoyMoveR: TJoyMoveEvent;
    FOnJoyMoveU: TJoyMoveEvent;
    FOnJoyMoveV: TJoyMoveEvent;
    FOnJoyMoveX: TJoyMoveEvent;
    FOnJoyMoveY: TJoyMoveEvent;
    FOnJoyMoveZ: TJoyMoveEvent;
    FOnJoyMovePOV: TJoyMoveEvent;

    function GetGamePort: integer;
    procedure SetGamePort(Val: integer);
    function GetNotifyRangeR: integer;
    procedure SetNotifyRangeR(Val: integer);
    function GetNotifyRangeU: integer;
    procedure SetNotifyRangeU(Val: integer);
    function GetNotifyRangeV: integer;
    procedure SetNotifyRangeV(Val: integer);
    function GetNotifyRangeX: integer;
    procedure SetNotifyRangeX(Val: integer);
    function GetNotifyRangeY: integer;
    procedure SetNotifyRangeY(Val: integer);
    function GetNotifyRangeZ: integer;
    procedure SetNotifyRangeZ(Val: integer);
    function GetPollRate: integer;
    procedure SetPollRate(Val: integer);
    function GetPollPriority: TThreadPriority;
    procedure SetPollPriority( Val: TThreadPriority );

    function CalculateRange( Axxis:Char; Position:UINT ):UINT;
    procedure MakeTimer;
    procedure ThreadRoutine;

    procedure CallButton( ButtonNumber:Integer );//Call the associated button routine
    procedure CallPosition( Axxis: Char );

    function StatusPosition( Axxis : Char ):Boolean;
    function StatusButton( Buttonnumber:Integer ):Boolean;
  protected
    { Protected Declarations }
    procedure SetDefaults;

  public
    { Public Declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    function Buttons(Port:UINT):UINT;
    function Devices: UINT;
    procedure Calibrate;

    function GetJoyX: Integer;// Get the current position of the
    function GetJoyY: Integer;// joysticks axxis.
    function GetJoyZ: Integer;
    function GetJoyR: Integer;
    function GetJoyU: Integer;
    function GetJoyV: Integer;
    function GetJoyPOV: Integer;
    function GetButton( ButtonNumber:Integer ):Boolean;// Test button status.

  published
    property GamePort: integer read GetGamePort write SetGamePort Default 1;
    property Enabled: Boolean read FEnabled write FEnabled;
    property NotifyRangeR: integer read GetNotifyRangeR write SetNotifyRangeR Default 20;
    property NotifyRangeU: integer read GetNotifyRangeU write SetNotifyRangeU Default 20;
    property NotifyRangeV: integer read GetNotifyRangeV write SetNotifyRangeV Default 20;
    property NotifyRangeX: integer read GetNotifyRangeX write SetNotifyRangeX Default 20;
    property NotifyRangeY: integer read GetNotifyRangeY write SetNotifyRangeY Default 20;
    property NotifyRangeZ: integer read GetNotifyRangeZ write SetNotifyRangeZ Default 20;
    property PollRate: integer read GetPollRate write SetPollRate Default 50;
    property PollPriority: TThreadPriority read GetPollPriority write SetPollPriority Default tpNormal;

    property StatusPositionChange : TRepeatPositions read FRepeatPositions write FRepeatPositions;
    // True = Every time the position changes from previous
    // False= While position is not 0
    property StatusButtonChange : TRepeatButtons read FRepeatButtons write FRepeatButtons;
    // True = Every time the status changes
    // False= Only onced when pressed

    property OnButton01: TButtonNotifyEvent read FOnButton01 write FOnButton01;
    property OnButton02: TButtonNotifyEvent read FOnButton02 write FOnButton02;
    property OnButton03: TButtonNotifyEvent read FOnButton03 write FOnButton03;
    property OnButton04: TButtonNotifyEvent read FOnButton04 write FOnButton04;
    property OnButton05: TButtonNotifyEvent read FOnButton05 write FOnButton05;
    property OnButton06: TButtonNotifyEvent read FOnButton06 write FOnButton06;
    property OnButton07: TButtonNotifyEvent read FOnButton07 write FOnButton07;
    property OnButton08: TButtonNotifyEvent read FOnButton08 write FOnButton08;
    property OnButton09: TButtonNotifyEvent read FOnButton09 write FOnButton09;
    property OnButton10: TButtonNotifyEvent read FOnButton10 write FOnButton10;
    property OnButton11: TButtonNotifyEvent read FOnButton11 write FOnButton11;
    property OnButton12: TButtonNotifyEvent read FOnButton12 write FOnButton12;
    property OnButton13: TButtonNotifyEvent read FOnButton13 write FOnButton13;
    property OnButton14: TButtonNotifyEvent read FOnButton14 write FOnButton14;
    property OnButton15: TButtonNotifyEvent read FOnButton15 write FOnButton15;
    property OnButton16: TButtonNotifyEvent read FOnButton16 write FOnButton16;
    property OnButton17: TButtonNotifyEvent read FOnButton17 write FOnButton17;
    property OnButton18: TButtonNotifyEvent read FOnButton18 write FOnButton18;
    property OnButton19: TButtonNotifyEvent read FOnButton19 write FOnButton19;
    property OnButton20: TButtonNotifyEvent read FOnButton20 write FOnButton20;
    property OnButton21: TButtonNotifyEvent read FOnButton21 write FOnButton21;
    property OnButton22: TButtonNotifyEvent read FOnButton22 write FOnButton22;
    property OnButton23: TButtonNotifyEvent read FOnButton23 write FOnButton23;
    property OnButton24: TButtonNotifyEvent read FOnButton24 write FOnButton24;
    property OnButton25: TButtonNotifyEvent read FOnButton25 write FOnButton25;
    property OnButton26: TButtonNotifyEvent read FOnButton26 write FOnButton26;
    property OnButton27: TButtonNotifyEvent read FOnButton27 write FOnButton27;
    property OnButton28: TButtonNotifyEvent read FOnButton28 write FOnButton28;
    property OnButton29: TButtonNotifyEvent read FOnButton29 write FOnButton29;
    property OnButton30: TButtonNotifyEvent read FOnButton30 write FOnButton30;
    property OnButton31: TButtonNotifyEvent read FOnButton31 write FOnButton31;
    property OnButton32: TButtonNotifyEvent read FOnButton32 write FOnButton32;
    property OnJoyMoveR: TJoyMoveEvent read FOnJoyMoveR write FOnJoyMoveR;
    property OnJoyMoveU: TJoyMoveEvent read FOnJoyMoveU write FOnJoyMoveU;
    property OnJoyMoveV: TJoyMoveEvent read FOnJoyMoveV write FOnJoyMoveV;
    property OnJoyMoveX: TJoyMoveEvent read FOnJoyMoveX write FOnJoyMoveX;
    property OnJoyMoveY: TJoyMoveEvent read FOnJoyMoveY write FOnJoyMoveY;
    property OnJoyMoveZ: TJoyMoveEvent read FOnJoyMoveZ write FOnJoyMoveZ;
    property OnJoyMovePOV: TJoyMoveEvent read FOnJoyMovePOV write FOnJoyMovePOV;
  end;

procedure Register;

implementation


{--------------------------------------}
{ TJoystick.Create                        }
{--------------------------------------}
constructor TJoystick.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  SetDefaults;

  if (csDesigning in ComponentState)=False then
     MakeTimer;

end;

{--------------------------------------}
{ TJoystick.Destroy                       }
{--------------------------------------}
destructor TJoystick.Destroy;
begin
  if not (FTimer = nil) then
  begin
     FTimer.Run := False;
  end;
  inherited Destroy;
end;

{--------------------------------------}
{ TJoystick.Buttons                       }
{--------------------------------------}
function TJoystick.Buttons(Port:UINT): UINT;
var
   rvalue : MMRESULT;
   ID : UINT;
begin
     rvalue := 0;

     if Enabled = True then
     begin
          Id := JOYSTICKID1 + Port - 1;
          rvalue := joyGetDevCaps( ID, @JoyCaps, SizeOf(JoyCaps) );

          rvalue := JoyCaps.wNumButtons;
     end;

     result := rvalue;

end;

{--------------------------------------}
{ TJoystick.Devices                       }
{--------------------------------------}
function TJoystick.Devices:UINT;
var
   rvalue : UINT;
begin
     rvalue := 0;

     if Enabled = True then
        rvalue := joyGetNumDevs;

     result := rvalue;
end;

{--------------------------------------}
{ TJoystick.GetGamePort                   }
{--------------------------------------}
function TJoystick.GetGamePort: integer;
begin
     result := FGamePort;
end;

{--------------------------------------}
{ TJoystick.SetGamePort                   }
{--------------------------------------}
procedure TJoystick.SetGamePort(Val: integer);
begin
     FGamePort := Val;
     JoyId := JOYSTICKID1 + Val - 1;

end;

{--------------------------------------}
{ TJoystick.GetNotifyRangeR               }
{--------------------------------------}
function TJoystick.GetNotifyRangeR: integer;
begin
     result := FNotifyRangeR;
end;

{--------------------------------------}
{ TJoystick.SetNotifyRangeR               }
{--------------------------------------}
procedure TJoystick.SetNotifyRangeR(Val: integer);
var
   rvalue : MMRESULT;
   Calc1 : UINT;
begin
     FNotifyRangeR := Val;

     rvalue := joyGetDevCaps( JoyID, @JoyCaps, SizeOf(JoyCaps) );

     Calc1 := JoyCaps.wRmax - JoyCaps.wRmin;
     MinR := JoyCaps.wRmin;

     if Calc1 = 0 then
        begin
             DeltaR := 1;
        end
     else
         begin
              DeltaR := Calc1 div ( (FNotifyRangeR*2) + 1 );
         end

end;

{--------------------------------------}
{ TJoystick.GetNotifyRangeU               }
{--------------------------------------}
function TJoystick.GetNotifyRangeU: integer;
begin
     result := FNotifyRangeU;
end;

{--------------------------------------}
{ TJoystick.SetNotifyRangeU               }
{--------------------------------------}
procedure TJoystick.SetNotifyRangeU(Val: integer);
var
   rvalue : MMRESULT;
   Calc1 : UINT;
begin
     FNotifyRangeU := Val;

     rvalue := joyGetDevCaps( JoyID, @JoyCaps, SizeOf(JoyCaps) );

     Calc1 := JoyCaps.wUmax - JoyCaps.wUmin;
     MinU := JoyCaps.wUmin;

     if Calc1 = 0 then
        begin
             DeltaU := 1;
        end
     else
         begin
              DeltaU := Calc1 div ( (FNotifyRangeU*2) + 1 );
         end
end;


{--------------------------------------}
{ TJoystick.GetNotifyRangeV               }
{--------------------------------------}
function TJoystick.GetNotifyRangeV: integer;
begin
     result := FNotifyRangeV;
end;

{--------------------------------------}
{ TJoystick.SetNotifyRangeV               }
{--------------------------------------}
procedure TJoystick.SetNotifyRangeV(Val: integer);
var
   rvalue : MMRESULT;
   Calc1 : UINT;
begin
     FNotifyRangeV := Val;

     rvalue := joyGetDevCaps( JoyID, @JoyCaps, SizeOf(JoyCaps) );

     Calc1 := JoyCaps.wVmax - JoyCaps.wVmin;
     MinV := JoyCaps.wVmin;

     if Calc1 = 0 then
        begin
             DeltaV := 1;
        end
     else
         begin
              DeltaV := Calc1 div ( (FNotifyRangeV*2) + 1 );
         end
end;


{--------------------------------------}
{ TJoystick.GetNotifyRangeX               }
{--------------------------------------}
function TJoystick.GetNotifyRangeX: integer;
begin
     result := FNotifyRangeX;
end;

{--------------------------------------}
{ TJoystick.SetNotifyRangeX               }
{--------------------------------------}
procedure TJoystick.SetNotifyRangeX(Val: integer);
var
   rvalue : MMRESULT;
   Calc1 : UINT;
begin
     FNotifyRangeX := Val;

     rvalue := joyGetDevCaps( JoyID, @JoyCaps, SizeOf(JoyCaps) );

     Calc1 := JoyCaps.wXmax - JoyCaps.wXmin;
     MinX := JoyCaps.wXmin;

     if Calc1 = 0 then
        begin
             DeltaX := 1;
        end
     else
         begin
              DeltaX := Calc1 div ( (FNotifyRangeX*2) + 1 );
         end
end;

{--------------------------------------}
{ TJoystick.GetNotifyRangeY               }
{--------------------------------------}
function TJoystick.GetNotifyRangeY: integer;
begin
     result := FNotifyRangeY;
end;

{--------------------------------------}
{ TJoystick.SetNotifyRangeY               }
{--------------------------------------}
procedure TJoystick.SetNotifyRangeY(Val: integer);
var
   rvalue : MMRESULT;
   Calc1 : UINT;
begin
     FNotifyRangeY := Val;

     rvalue := joyGetDevCaps( JoyID, @JoyCaps, SizeOf(JoyCaps) );

     Calc1 := JoyCaps.wYmax - JoyCaps.wYmin;
     MinY := JoyCaps.wYmin;

     if Calc1 = 0 then
        begin
             DeltaY := 1;
        end
     else
         begin
              DeltaY := Calc1 div ( (FNotifyRangeY*2) + 1 );
         end
end;

{--------------------------------------}
{ TJoystick.GetNotifyRangeZ               }
{--------------------------------------}
function TJoystick.GetNotifyRangeZ: integer;
begin
     result := FNotifyRangeZ;
end;

{--------------------------------------}
{ TJoystick.SetNotifyRangeZ               }
{--------------------------------------}
procedure TJoystick.SetNotifyRangeZ(Val: integer);
var
   rvalue : MMRESULT;
   Calc1 : UINT;
begin
     FNotifyRangeZ := Val;

     rvalue := joyGetDevCaps( JoyID, @JoyCaps, SizeOf(JoyCaps) );

     Calc1 := JoyCaps.wZmax - JoyCaps.wZmin;
     MinZ := JoyCaps.wZmin;

     if Calc1 = 0 then
        begin
             DeltaZ := 1;
        end
     else
         begin
              DeltaZ := Calc1 div ( (FNotifyRangeZ*2) + 1 );
         end
end;

{--------------------------------------}
{ TJoystick.GetPollRate                   }
{--------------------------------------}
function TJoystick.GetPollRate: integer;
begin
     result := FPollRate;
end;

{--------------------------------------}
{ TJoystick.SetPollRate                   }
{--------------------------------------}
procedure TJoystick.SetPollRate(Val: integer);
begin
     FPollRate := Val;

     if not( FTimer = nil ) then
     begin
          FTimer.Interval := PollRate;
     end;

end;

{--------------------------------------}
{ TJoystick.GetPollPriority            }
{--------------------------------------}
function TJoystick.GetPollPriority: TThreadPriority;
begin
     result := FPollPriority;
end;

{--------------------------------------}
{ TJoystick.SetPollPriority            }
{--------------------------------------}
procedure TJoystick.SetPollPriority( Val: TThreadPriority );
begin
     FPollPriority := Val;
     if not( FTimer = nil ) then FTimer.Priority := Val;
end;

{--------------------------------------}
{ TJoystick.SetDefaults                   }
{--------------------------------------}
procedure TJoystick.SetDefaults;
var
   counter : Integer;
begin

     Enabled := True;
     GamePort := 1;
     NotifyRangeR := 20;
     NotifyRangeU := 20;
     NotifyRangeV := 20;
     NotifyRangeX := 20;
     NotifyRangeY := 20;
     NotifyRangeZ := 20;
     PollRate := 50;

     JoyInfoEx.dwSize := SizeOf( JoyInfoEx );

    LastX := 0;
    LastY := 0;
    LastZ := 0;
    LastR := 0;
    LastU := 0;
    LastV := 0;
    LastP := 65535;

    for counter:=1 to 32 do
        LastButton[counter] := False;

      StatusPositionChange := [ X, Y, Z, R, U, V, POV ];
      StatusButtonChange := [];
      PollPriority := tpNormal;
end;

{--------------------------------------}
{ TJoystick.CalculateRange             }
{--------------------------------------}
function TJoystick.CalculateRange( Axxis:Char; Position:UINT ):UINT;
var
   Delta,Min : UINT;
   Calc1,rvalue : UINT;
   range : UINT;
begin
     range := 1;
     case Axxis of
          'X' : begin
                     Delta := DeltaX;
                     Min := MinX;
                     range := FNotifyRangeX;
                end;

          'Y' : begin
                     Delta := DeltaY;
                     Min := MinY;
                     range := FNotifyRangeY;
                end;

          'Z' : begin
                     Delta := DeltaZ;
                     Min := MinZ;
                     range := FNotifyRangeZ;
                end;

          'R' : begin
                     Delta := DeltaR;
                     Min := MinR;
                     range := FNotifyRangeR;
                end;

          'U' : begin
                     Delta := DeltaU;
                     Min := MinU;
                     range := FNotifyRangeU;
                end;

          'V' : begin
                     Delta := DeltaV;
                     Min := MinV;
                     range := FNotifyRangeV;
                end;
     end;

       Calc1 := Position-Min;
       rvalue := Calc1 div Delta;
       rvalue := rvalue - range;

       result := rvalue;
end;

{--------------------------------------}
{ TJoystick.GetJoyX                    }
{--------------------------------------}
function TJoystick.GetJoyX: Integer;
var
   rvalue : MMRESULT;
begin
     if Enabled = True then
     begin
          JoyInfoEx.dwFlags := JOY_RETURNX;

          rvalue := joyGetPosEx( JoyID, @JoyInfoEx);

          LastX := CalculateRange( 'X', JoyInfoEx.wXpos );

     end;
     result := LastX;
end;

{--------------------------------------}
{ TJoystick.GetJoyY                    }
{--------------------------------------}
function TJoystick.GetJoyY: Integer;
var
   rvalue : MMRESULT;
   flipvalue : Integer;
begin

     if Enabled = True then
     begin
          JoyInfoEx.dwFlags := JOY_RETURNY;

          rvalue := joyGetPosEx( JoyID, @JoyInfoEx);

          flipvalue := CalculateRange( 'Y', JoyInfoEx.wYpos );
          flipvalue := flipvalue * -1;

          LastY := flipvalue;

     end;
     result := LastY;

end;

{--------------------------------------}
{ TJoystick.GetJoyZ                    }
{--------------------------------------}
function TJoystick.GetJoyZ: Integer;
var
   rvalue : MMRESULT;
   flipvalue : Integer;
begin

     if Enabled = True then
     begin
        JoyInfoEx.dwFlags := JOY_RETURNZ;

        rvalue := joyGetPosEx( JoyID, @JoyInfoEx);

        flipvalue := CalculateRange( 'Z', JoyInfoEx.wZpos );
        flipvalue := flipvalue * -1;

        LastZ := flipvalue;

     end;
     result := LastZ;
end;

{--------------------------------------}
{ TJoystick.GetJoyR                    }
{--------------------------------------}
function TJoystick.GetJoyR: Integer;
var
   rvalue : MMRESULT;
begin

     if Enabled = True then
     begin
          JoyInfoEx.dwFlags := JOY_RETURNR;

          rvalue := joyGetPosEx( JoyID, @JoyInfoEx);

          LastR := CalculateRange( 'R', JoyInfoEx.dwRpos );

     end;
     result := LastR;
end;

{--------------------------------------}
{ TJoystick.GetJoyU                    }
{--------------------------------------}
function TJoystick.GetJoyU: Integer;
var
   rvalue : MMRESULT;
begin

     if Enabled = True then
     begin
          JoyInfoEx.dwFlags := JOY_RETURNU;

          rvalue := joyGetPosEx( JoyID, @JoyInfoEx);

          LastU := CalculateRange( 'U', JoyInfoEx.dwUpos );

     end;
     result := LastU;
end;

{--------------------------------------}
{ TJoystick.GetJoyV                    }
{--------------------------------------}
function TJoystick.GetJoyV: Integer;
var
   rvalue : MMRESULT;
begin

     if Enabled = True then
     begin
          JoyInfoEx.dwFlags := JOY_RETURNV;

          rvalue := joyGetPosEx( JoyID, @JoyInfoEx);

          LastV := CalculateRange( 'V', JoyInfoEx.dwVpos );

     end;
     result := LastV;
end;


{--------------------------------------}
{ TJoystick.GetJoyPOV                  }
{--------------------------------------}
function TJoystick.GetJoyPOV: Integer;
var
   rvalue : MMRESULT;
begin

     if Enabled = True then
     begin
          JoyInfoEx.dwFlags := JOY_RETURNPOV;

          rvalue := joyGetPosEx( JoyID, @JoyInfoEx);

          LastP := JoyInfoEx.dwPOV;

     end;
     result := LastP;

end;

{--------------------------------------}
{ TJoystick.GetGetButton               }
{--------------------------------------}
function TJoystick.GetButton( ButtonNumber:Integer ):Boolean;
var
   rvalue : MMRESULT;
   button : UINT;
   pressed : Boolean;
begin

     pressed := False;
     if Enabled = True then
     begin
          JoyInfoEx.dwFlags := JOY_RETURNBUTTONS;

          rvalue := joyGetPosEx( JoyID, @JoyInfoEx);

     { could have bit shifted the incoming value but
       afraid of what changes may be made to these
       constant values }
       case ButtonNumber of
          1 : button := JOY_BUTTON1;
          2 : button := JOY_BUTTON2;
          3 : button := JOY_BUTTON3;
          4 : button := JOY_BUTTON4;
          5 : button := JOY_BUTTON5;
          6 : button := JOY_BUTTON6;
          7 : button := JOY_BUTTON7;
          8 : button := JOY_BUTTON8;
          9 : button := JOY_BUTTON9;
          10: button := JOY_BUTTON10;
          11: button := JOY_BUTTON11;
          12: button := JOY_BUTTON12;
          13: button := JOY_BUTTON13;
          14: button := JOY_BUTTON14;
          15: button := JOY_BUTTON15;
          16: button := JOY_BUTTON16;
          17: button := JOY_BUTTON17;
          18: button := JOY_BUTTON18;
          19: button := JOY_BUTTON19;
          20: button := JOY_BUTTON20;
          21: button := JOY_BUTTON21;
          22: button := JOY_BUTTON22;
          23: button := JOY_BUTTON23;
          24: button := JOY_BUTTON24;
          25: button := JOY_BUTTON25;
          26: button := JOY_BUTTON26;
          27: button := JOY_BUTTON27;
          28: button := JOY_BUTTON28;
          29: button := JOY_BUTTON29;
          30: button := JOY_BUTTON30;
          31: button := JOY_BUTTON31;
          32: button := JOY_BUTTON32;
       else
         button := JOY_BUTTON1;
       end;

       if (JoyInfoEx.wButtons and button ) = button then
          pressed := True
       else
           pressed := False;

       LastButton[ButtonNumber] := pressed;
     end;

     result := pressed;

end;

{--------------------------------------}
{ TJoystick.CallButton                 }
{--------------------------------------}
procedure TJoystick.CallButton( ButtonNumber:Integer );
begin
     case ButtonNumber of
          1 : if Assigned( FOnButton01 ) then FOnButton01(Self,GetButton(ButtonNumber));
          2 : if Assigned( FOnButton02 ) then FOnButton02(Self,GetButton(ButtonNumber));
          3 : if Assigned( FOnButton03 ) then FOnButton03(Self,GetButton(ButtonNumber));
          4 : if Assigned( FOnButton04 ) then FOnButton04(Self,GetButton(ButtonNumber));
          5 : if Assigned( FOnButton05 ) then FOnButton05(Self,GetButton(ButtonNumber));
          6 : if Assigned( FOnButton06 ) then FOnButton06(Self,GetButton(ButtonNumber));
          7 : if Assigned( FOnButton07 ) then FOnButton07(Self,GetButton(ButtonNumber));
          8 : if Assigned( FOnButton08 ) then FOnButton08(Self,GetButton(ButtonNumber));
          9 : if Assigned( FOnButton09 ) then FOnButton09(Self,GetButton(ButtonNumber));
          10: if Assigned( FOnButton10 ) then FOnButton10(Self,GetButton(ButtonNumber));
          11: if Assigned( FOnButton11 ) then FOnButton11(Self,GetButton(ButtonNumber));
          12: if Assigned( FOnButton12 ) then FOnButton12(Self,GetButton(ButtonNumber));
          13: if Assigned( FOnButton13 ) then FOnButton13(Self,GetButton(ButtonNumber));
          14: if Assigned( FOnButton14 ) then FOnButton14(Self,GetButton(ButtonNumber));
          15: if Assigned( FOnButton15 ) then FOnButton15(Self,GetButton(ButtonNumber));
          16: if Assigned( FOnButton16 ) then FOnButton16(Self,GetButton(ButtonNumber));
          17: if Assigned( FOnButton17 ) then FOnButton17(Self,GetButton(ButtonNumber));
          18: if Assigned( FOnButton18 ) then FOnButton18(Self,GetButton(ButtonNumber));
          19: if Assigned( FOnButton19 ) then FOnButton19(Self,GetButton(ButtonNumber));
          20: if Assigned( FOnButton20 ) then FOnButton20(Self,GetButton(ButtonNumber));
          21: if Assigned( FOnButton21 ) then FOnButton21(Self,GetButton(ButtonNumber));
          22: if Assigned( FOnButton22 ) then FOnButton22(Self,GetButton(ButtonNumber));
          23: if Assigned( FOnButton23 ) then FOnButton23(Self,GetButton(ButtonNumber));
          24: if Assigned( FOnButton24 ) then FOnButton24(Self,GetButton(ButtonNumber));
          25: if Assigned( FOnButton25 ) then FOnButton25(Self,GetButton(ButtonNumber));
          26: if Assigned( FOnButton26 ) then FOnButton26(Self,GetButton(ButtonNumber));
          27: if Assigned( FOnButton27 ) then FOnButton27(Self,GetButton(ButtonNumber));
          28: if Assigned( FOnButton28 ) then FOnButton28(Self,GetButton(ButtonNumber));
          29: if Assigned( FOnButton29 ) then FOnButton29(Self,GetButton(ButtonNumber));
          30: if Assigned( FOnButton30 ) then FOnButton30(Self,GetButton(ButtonNumber));
          31: if Assigned( FOnButton31 ) then FOnButton31(Self,GetButton(ButtonNumber));
          32: if Assigned( FOnButton32 ) then FOnButton32(Self,GetButton(ButtonNumber));
     end;
end;

{--------------------------------------}
{ TJoystick.CallPoistion               }
{--------------------------------------}
procedure TJoystick.CallPosition( Axxis: Char );
begin
     case Axxis of
          'X': if Assigned( FOnJoyMoveX ) then FOnJoyMoveX(Self,GetJoyX);
          'Y': if Assigned( FOnJoyMoveY ) then FOnJoyMoveY(Self,GetJoyY);
          'Z': if Assigned( FOnJoyMoveZ ) then FOnJoyMoveZ(Self,GetJoyZ);
          'R': if Assigned( FOnJoyMoveR ) then FOnJoyMoveR(Self,GetJoyR);
          'U': if Assigned( FOnJoyMoveU ) then FOnJoyMoveU(Self,GetJoyU);
          'V': if Assigned( FOnJoyMoveV ) then FOnJoyMoveV(Self,GetJoyV);
          'P': if Assigned( FOnJoyMovePOV ) then FOnJoyMovePOV(Self,GetJoyPOV);
     end;

end;

{--------------------------------------}
{ TJoystick.MakeTimer                  }
{--------------------------------------}
procedure TJoystick.MakeTimer;
begin
     FTimer := DCThread.Create(False);
     FTimer.Enabled := False;

     FTimer.Interval := PollRate;
     FTimer.OnTimer := ThreadRoutine;

     FTimer.Enabled := True;

end;

{--------------------------------------}
{ TJoystick.StatusButton               }
{   returns the boolean value of the   }
{   given buttons status value         }
{--------------------------------------}
function TJoystick.StatusButton( Buttonnumber:Integer ):Boolean;
var
   rvalue : Boolean;
begin
     rvalue := False;

     case Buttonnumber of
          1 : if Button01 in StatusButtonChange then rvalue := True;
          2 : if Button02 in StatusButtonChange then rvalue := True;
          3 : if Button03 in StatusButtonChange then rvalue := True;
          4 : if Button04 in StatusButtonChange then rvalue := True;
          5 : if Button05 in StatusButtonChange then rvalue := True;
          6 : if Button06 in StatusButtonChange then rvalue := True;
          7 : if Button07 in StatusButtonChange then rvalue := True;
          8 : if Button08 in StatusButtonChange then rvalue := True;
          9 : if Button09 in StatusButtonChange then rvalue := True;
          10: if Button10 in StatusButtonChange then rvalue := True;
          11: if Button11 in StatusButtonChange then rvalue := True;
          12: if Button12 in StatusButtonChange then rvalue := True;
          13: if Button13 in StatusButtonChange then rvalue := True;
          14: if Button14 in StatusButtonChange then rvalue := True;
          15: if Button15 in StatusButtonChange then rvalue := True;
          16: if Button16 in StatusButtonChange then rvalue := True;
          17: if Button17 in StatusButtonChange then rvalue := True;
          18: if Button18 in StatusButtonChange then rvalue := True;
          19: if Button19 in StatusButtonChange then rvalue := True;
          20: if Button20 in StatusButtonChange then rvalue := True;
          21: if Button21 in StatusButtonChange then rvalue := True;
          22: if Button22 in StatusButtonChange then rvalue := True;
          23: if Button23 in StatusButtonChange then rvalue := True;
          24: if Button24 in StatusButtonChange then rvalue := True;
          25: if Button25 in StatusButtonChange then rvalue := True;
          26: if Button26 in StatusButtonChange then rvalue := True;
          27: if Button27 in StatusButtonChange then rvalue := True;
          28: if Button28 in StatusButtonChange then rvalue := True;
          29: if Button29 in StatusButtonChange then rvalue := True;
          30: if Button30 in StatusButtonChange then rvalue := True;
          31: if Button31 in StatusButtonChange then rvalue := True;
          32: if Button32 in StatusButtonChange then rvalue := True;
     end;

     result := rvalue;
end;

{--------------------------------------}
{ TJoystick.StatusPosition             }
{   returns the boolean value of the   }
{   given joystick position            }
{--------------------------------------}
function TJoystick.StatusPosition( Axxis : Char ):Boolean;
var
   rvalue : Boolean;
begin
     rvalue := False;
     case Axxis of
          'X' : if X in StatusPositionChange then rvalue := True;
          'Y' : if Y in StatusPositionChange then rvalue := True;
          'Z' : if Z in StatusPositionChange then rvalue := True;
          'R' : if R in StatusPositionChange then rvalue := True;
          'U' : if U in StatusPositionChange then rvalue := True;
          'V' : if V in StatusPositionChange then rvalue := True;
          'P' : if POV in StatusPositionChange then rvalue := True;
     end;

     result := rvalue;
end;


{--------------------------------------}
{ TJoystick.Calibrate                  }
{--------------------------------------}
procedure TJoystick.Calibrate;
begin
     if Enabled = True then
        WinExec('control joy.cpl', SW_NORMAL);
end;

{--------------------------------------}
{ TJoystick.ThreadRoutine              }
{--------------------------------------}
procedure TJoystick.ThreadRoutine;
var
   counter : Integer;
   lbutton : Boolean;
   lposition : Integer;
   nowbutton : Boolean;
begin
     if Enabled = True then
     begin
          { check buttons all 32 buttons}
          { if the status button is true then run button }
          { code every time the last button != current button }
          { if the status button is false then run only when }
          { the button is pressed }
          for counter := 1 to 32 do
          begin
               lbutton := LastButton[counter];
               nowbutton := GetButton(counter);
               if StatusButton(counter) then
                  begin
                       if lbutton <> nowbutton then CallButton(counter);
                  end
               else
                   begin
                        if (nowbutton = True) and (lbutton = False)
                           then CallButton(counter);
                   end;
          end;

          { If StatusPosition is true, run position code }
          { every time last position != Current Position }
          { If StatusPosition is false, then call        }
          { position every time the position != 0        }

          lposition := LastX;
          if StatusPosition( 'X' ) then
             begin
                  if lposition <> GetJoyX then CallPosition( 'X' );
             end
          else
              begin
                   if GetJoyX <> 0 then CallPosition( 'X' );
              end;


          lposition := LastY;
          if StatusPosition( 'Y' ) then
             begin
                  if lposition <> GetJoyY then CallPosition( 'Y' );
             end
          else
              begin
                   if GetJoyY <> 0 then CallPosition( 'Y' );
              end;

          lposition := LastZ;
          if StatusPosition( 'Z' ) then
             begin
                  if lposition <> GetJoyZ then CallPosition( 'Z' );
             end
          else
              begin
                   if GetJoyZ <> 0 then CallPosition( 'Z' );
              end;


          lposition := LastR;
          if StatusPosition( 'R' ) then
             begin
                  if lposition <> GetJoyR then CallPosition( 'R' );
             end
          else
              begin
                   if GetJoyR <> 0 then CallPosition( 'R' );
              end;

          lposition := LastU;
          if StatusPosition( 'U' ) then
             begin
                  if lposition <> GetJoyU then CallPosition( 'U' );
             end
          else
              begin
                   if GetJoyU <> 0 then CallPosition( 'U' );
              end;



          lposition := LastV;
          if StatusPosition( 'V' ) then
             begin
                  if lposition <> GetJoyV then CallPosition( 'V' );
             end
          else
              begin
                   if GetJoyV <> 0 then CallPosition( 'V' );
              end;


          lposition := LastP;
          if StatusPosition( 'P' ) then
             begin
                  if lposition <> GetJoyPOV then CallPosition( 'P' );
             end
          else
              begin
                   if GetJoyPOV <> 65535 then CallPosition( 'P' );
              end;

     end;
end;

{-------------------------------------------------------------}
{ The Threading Functions                                     }
{-------------------------------------------------------------}
procedure DCThread.Execute;
begin
  Run := True;
  while Run = True do
  begin
       if Enabled then
          if Assigned(OnTimer) then Synchronize(OnTimer);
       if Interval < 1 then Interval := 10;
       Sleep(Interval);
  end;
  Free;
end;


{--------------------------------------}
{ Register                             }
{--------------------------------------}
procedure Register;
begin
  RegisterComponents('Samples', [TJoystick]);
end;

end.
