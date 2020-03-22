unit bi_install;


interface

uses bi_ctrls, bi_timer, classes;


procedure Register;

implementation

{$R bi_library.res}

procedure Register;
begin
  RegisterComponents('Samples', [TBI_Loupe,TBI_Timer]);
end;

end.
 