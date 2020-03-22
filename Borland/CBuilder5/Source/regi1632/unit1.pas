unit Unit1;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, Regi1632;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Edit3: TEdit;
    Button2: TButton;
    Label4: TLabel;
    Label5: TLabel;
    Registry16321: TRegistry1632;
    CheckBox1: TCheckBox;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
  private
    { Private-Deklarationen }
  public
    { Public-Deklarationen }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.Button1Click(Sender: TObject);
var value:string;
begin
  edit3.text:=Registry16321.ReadUserString(edit1.text, edit2.text);
  if Registry16321.WasError then
    messagedlg('Error: '+ Registry16321.ErrorMessage,mtinformation,[mbok],0);
end;

procedure TForm1.Button2Click(Sender: TObject);
var value:string;
begin
  Registry16321.WriteUserString(edit1.text, edit2.text, edit3.text);
  if Registry16321.WasError then
    messagedlg('Error: '+ Registry16321.ErrorMessage,mtinformation,[mbok],0);
end;

procedure TForm1.FormShow(Sender: TObject);
begin
  checkbox1.checked:=Registry16321.RunningWin31;
end;

procedure TForm1.CheckBox1Click(Sender: TObject);
begin
  Registry16321.RunningWin31:=checkbox1.checked;
  if checkbox1.checked then
  begin
    label4.caption:='Reads the data path/key from inifile and sets the Result-field!';
    label5.caption:='Writes the data in the results field to the path/key to the inifile!';
  end
  else
  begin
    label4.caption:='Reads the data path/key from registry and sets the Result-field!';
    label5.caption:='Writes the data in the results field to the path/key in the registry!';
  end;
end;

end.
