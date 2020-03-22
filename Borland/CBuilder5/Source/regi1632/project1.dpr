program Project1;

uses
  Forms,
  Unit1 in '\REGISTRY\UNIT1.PAS' {Form1};

{$R *.RES}

begin
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
