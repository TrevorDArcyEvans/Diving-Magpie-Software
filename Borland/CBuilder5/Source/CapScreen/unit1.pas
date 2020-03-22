unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  SCapture, ExtCtrls, StdCtrls;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Label1: TLabel;
    RbDesktop: TRadioButton;
    RadioButton2: TRadioButton;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    ScrollBox1: TScrollBox;
    Image1: TImage;
    Button1: TButton;
    Button2: TButton;
    SaveDialog1: TSaveDialog;
    ScreenCapture1: TScreenCapture;
    procedure RbDesktopClick(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure CheckBox2Click(Sender: TObject);
    procedure ScreenCapture1Capture(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private-Deklarationen }
  public
    { Public-Deklarationen }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.RbDesktopClick(Sender: TObject);
begin
     Screencapture1.desktop := rbdesktop.checked;
end;


procedure TForm1.CheckBox1Click(Sender: TObject);
begin
     screencapture1.active := checkbox1.checked;
end;

procedure TForm1.CheckBox2Click(Sender: TObject);
begin
     screencapture1.autocopy := checkbox2.checked;
end;

procedure TForm1.ScreenCapture1Capture(Sender: TObject);
begin
     Image1.picture.bitmap.assign(screencapture1.bitmap);
end;


procedure TForm1.Button1Click(Sender: TObject);
begin
     ScreenCapture1.copytoclipboard;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
     if SaveDialog1.execute then ScreenCapture1.Bitmap.savetofile(SaveDialog1.filename);
end;


end.
