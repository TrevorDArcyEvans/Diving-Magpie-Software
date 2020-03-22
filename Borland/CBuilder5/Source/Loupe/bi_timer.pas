unit bi_timer;

interface

uses  Windows, Messages, SysUtils, Classes, Controls;

type

TBI_Timer = class(TComponent)
  private
    FEnabled: Boolean;
    FInterval: Cardinal;
    FOnTimer: TNotifyEvent;
    FTimerThread: TThread;
    FThreadPriority: TThreadPriority;
    procedure UpdateTimer;
    procedure SetOnTimer(Value: TNotifyEvent);
    procedure SetEnabled(Value: Boolean);
    procedure SetInterval(Value: Cardinal);
    procedure SetThreadPriority(Value: TThreadPriority);
  protected
    procedure Timer; dynamic;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Enabled: Boolean read FEnabled write SetEnabled default True;
    property Interval: Cardinal read FInterval write SetInterval default 1000;
    property ThreadPriority: TThreadPriority read FThreadPriority write
      SetThreadPriority default tpNormal;
    property OnTimer: TNotifyEvent read FOnTimer write SetOnTimer;
    property Name;
  end;

  bi_t_thread = class(tthread)
  private
      FOwner: TBI_Timer;
      FWaitForTerminate: Boolean;
  protected
      procedure Execute; override;
  public
      constructor Create(timer:tbi_timer);
  end;


implementation

procedure bi_t_thread.Execute;
begin
  Priority := FOwner.FThreadPriority;
  repeat
    if SleepEx(FOwner.FInterval, False) = 0 then
      if not FWaitforterminate then synchronize(FOwner.Timer); until Terminated;
end;

constructor bi_t_thread.Create(timer:tbi_timer);
begin
  inherited Create(False);
  FOwner := Timer;
  Priority := FOwner.FThreadPriority;
  FreeOnTerminate := True;
end;

constructor TBI_Timer.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FEnabled := True;
  FInterval := 1000;
  FThreadPriority := tpNormal;
  FTimerThread := bi_t_thread.Create(Self);
end;

destructor TBI_Timer.Destroy;
begin
  FEnabled := False;
  UpdateTimer;
  if FTimerThread <> nil then
  begin
    bi_t_thread(FTimerThread).FWaitForTerminate := True;
    FTimerThread.Free;
  end;
  inherited Destroy;
end;

procedure TBI_Timer.UpdateTimer;
begin
  if FTimerThread <> nil then
    if not FTimerThread.Suspended then FTimerThread.Suspend;
    if FTimerThread = nil then FTimerThread := bi_t_thread.Create(Self);
  if (FInterval <> 0) and FEnabled and Assigned(FOnTimer) then
    begin
      FTimerThread.Priority := FThreadPriority;
      while FTimerThread.Suspended do FTimerThread.Resume;
    end;
end;

procedure TBI_Timer.SetEnabled(Value: Boolean);
begin
  if Value <> FEnabled then begin
    FEnabled := Value;
    UpdateTimer;
  end;
end;

procedure TBI_Timer.SetInterval(Value: Cardinal);
begin
  if Value <> FInterval then begin
    FInterval := Value;
    UpdateTimer;
  end;
end;

procedure TBI_Timer.SetThreadPriority(Value: TThreadPriority);
begin
  if Value <> FThreadPriority then
    FThreadPriority := Value;
end;

procedure TBI_Timer.SetOnTimer(Value: TNotifyEvent);
begin
  FOnTimer := Value;
  UpdateTimer;
end;

procedure TBI_Timer.Timer;
begin
  if FEnabled and Assigned(FOnTimer) then FOnTimer(Self);
end;


end.
 