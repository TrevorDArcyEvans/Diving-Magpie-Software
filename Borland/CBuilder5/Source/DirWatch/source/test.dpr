program test;

uses
  Forms,
  test_main in 'test_main.pas' {MainForm},
  FngDirWatch in 'FngDirWatch.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
