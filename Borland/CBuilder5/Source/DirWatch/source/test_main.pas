unit test_main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, ComCtrls, StdCtrls, FngDirWatch;

const

  Status_State     = 0;
  Status_Directory = 1;

  
type
  TMainForm = class(TForm)
    ToolbarPanel: TPanel;
    StatusBar: TStatusBar;
    Bevel: TBevel;
    StartBtn: TButton;
    SetDirBtn: TButton;
    Memo: TMemo;
    ClearBtn: TButton;
    FDirWatch: TFnugryDirWatch;
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure StartBtnClick(Sender: TObject);
    procedure SetDirCmd(Sender: TObject);
    procedure ClearCmd(Sender: TObject);
    procedure DirWatchChange(Sender :TObject);
    procedure DirWatchNotify(Sender :TObject;
      Action :Integer; const FileName :String);
  private
    procedure UpdateStatus;
    procedure UpdateControls;
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation


{$R *.DFM}

procedure TMainForm.FormDestroy(Sender: TObject);
begin
   FDirWatch.free;
end;

procedure TMainForm.UpdateStatus;
begin
   if assigned(FDirWatch) then
      begin
        StatusBar.Panels[Status_Directory].Text := FDirWatch.Directory;
        if FDirWatch.Enabled then
           StatusBar.Panels[Status_State].Text := 'Enabled'
        else
           StatusBar.Panels[Status_State].Text := 'Disabled';
      end
   else
      begin
        StatusBar.Panels[Status_Directory].Text := 'none';
        StatusBar.Panels[Status_State].Text := 'none'
      end;
end;

procedure TMainForm.UpdateControls;
begin
   StartBtn.Enabled := assigned(FDirWatch);
   SetDirBtn.Enabled := assigned(FDirWatch);
   if assigned(FDirWatch) then
      if FDirWatch.Enabled then
         StartBtn.Caption := 'Stop'
      else
         StartBtn.Caption := 'Start';
end;

procedure TMainForm.FormShow(Sender: TObject);
begin
   UpdateStatus;
   UpdateControls;
end;

procedure TMainForm.DirWatchChange(Sender :TObject);
begin
   UpdateStatus;
   UpdateControls;
end;


procedure TMainForm.StartBtnClick(Sender: TObject);
begin
   FDirWatch.Enabled := not FDirWatch.Enabled;
end;

procedure TMainForm.SetDirCmd(Sender: TObject);
var
   S :String;
begin
   //
   S := FDirWatch.Directory;
   if InputQuery('Change Directory', 'Directory to watch:', S)then
      FDirWatch.Directory := S;
end;

procedure TMainForm.DirWatchNotify(Sender :TObject;
 Action :Integer; const FileName :String);
begin
  memo.lines.add(format('[%s] %s:'#9'%s',
   [FormatDateTime('hh:nn:ss', now),
   FDirWatch.ActionName(Action), FIleName]));
end;

procedure TMainForm.ClearCmd(Sender: TObject);
begin
  memo.clear;
end;

end.
