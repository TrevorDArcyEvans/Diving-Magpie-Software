program PNGTest;

uses
  Forms,
  PNGMainForm in 'PNGMainForm.pas' {MainForm},
  PNGImage in '..\PngImage.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'Portable Graphics Network Test';
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
