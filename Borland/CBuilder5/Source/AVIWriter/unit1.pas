unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, AviWriter, Spin, MPlayer;

type
  TForm1 = class(TForm)
    AviWriter1: TAviWriter;
    Button1: TButton;
    OpenDialog1: TOpenDialog;
    Button2: TButton;
    OpenDialog2: TOpenDialog;
    seFrameTime: TSpinEdit;
    Label1: TLabel;
    Label2: TLabel;
    seHeight: TSpinEdit;
    Label3: TLabel;
    seWidth: TSpinEdit;
    cbStretch: TCheckBox;
    Button3: TButton;
    SaveDialog1: TSaveDialog;
    MediaPlayer1: TMediaPlayer;
    Button4: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.FormCreate(Sender: TObject);
begin
    seFrameTime.Value := AviWriter1.FrameTime;
    seHeight.Value    := AviWriter1.Height;
    seWidth.Value     := AviWriter1.Width;
    cbStretch.Checked := AviWriter1.Stretch;
end;

procedure TForm1.Button1Click(Sender: TObject);
var
    Bitmap : TBitmap;
begin
    if OpenDialog1.Execute then begin
       Bitmap := TBitmap.Create;
       try
          Bitmap.LoadFromFile(OpenDialog1.FileName);
          AviWriter1.Bitmaps.Add(Bitmap);
          Button3.Enabled := true;
       except
          on E : Exception do begin
            ShowMessage('Cannot load bitmap because: ' + E.Message);
            Bitmap.Free;
          end;
       end;
    end;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
    if OpenDialog2.Execute
       then begin
           AviWriter1.WavFileName := OpenDialog2.FileName;
           Button2.enabled := false;
    end;
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
   if SaveDialog1.Execute then
      if ofExtensionDifferent in SaveDialog1.Options
         then Application.MessageBox
                       ('Extension must be AVI','Error',MB_ICONERROR)
         else begin
                AviWriter1.FileName := SaveDialog1.FileName;
                with AviWriter1 do begin
                     Height     := seHeight.Value;
                     Width      := seWidth.Value;
                     FrameTime  := seFrameTime.Value;
                     Stretch    := cbStretch.Checked;
                     Write;
                     Button4.Enabled := true;
                end;
         end;
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
var
   Bitmap : TBitmap;
begin
   with AviWriter1 do
      while Bitmaps.Count > 0 do begin
         Bitmap := Bitmaps[0];
         Bitmap.Free;
         Bitmaps.Delete(0);
      end;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
   with MediaPlayer1 do begin
       Enabled := true;
       FileName := AviWriter1.FileName;
       Open;
       Wait     := true;
       Play;
       Close;
   end;
end;

end.
