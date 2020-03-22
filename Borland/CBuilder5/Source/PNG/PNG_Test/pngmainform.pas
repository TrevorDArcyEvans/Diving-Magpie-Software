unit PNGMainForm;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, StdCtrls, ExtCtrls, Buttons, PNGImage, ExtDlgs, ImgList, Win95Pie,
  Math, jpeg;

type
  {Pixel memory access}
  pRGBLine = ^TRGBLine;
  TRGBLine = Array[Word] of TRGBTriple;
  pRGBALine = ^TRGBALine;
  TRGBALine = Array[Word] of TRGBQuad;

  TIDATAccess = class(TChunkIDAT);

  TGammaTester = class(TCustomPanel)
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Paint; Override;
    procedure OnResize(var Message: TWMSize); message WM_SIZE;
    procedure RecreateBitmap;
  private
    Table: Array[Byte] of Byte;
    Bitmap: TBitmap;
    vGamma: Double;
    procedure SetGamma(Value: Double);
  public
    property Gamma: Double read vGamma write SetGamma;
  end;

  TMainForm = class(TForm)
    TOPPANEL: TPanel;
    MainIcon: TImage;
    TopTITLE: TLabel;
    TopExplanation: TLabel;
    RightPanel: TPanel;
    RightTitle: TLabel;
    ChunkList: TListView;
    AddChunk: TSpeedButton;
    DeleteChunk: TSpeedButton;
    Status: TStatusBar;
    LeftPanel: TPanel;
    LeftTitle: TLabel;
    BrowseFolder: TSpeedButton;
    FileList: TListView;
    SaveFile: TSpeedButton;
    LoadFile: TSpeedButton;
    ToggleLeft: TSpeedButton;
    ToggleRight: TSpeedButton;
    LoadFileDialog: TOpenPictureDialog;
    Props: TNotebook;
    PaletteArea: TPaintBox;
    PaletteTitle: TPanel;
    IHDR: TTreeView;
    Images: TImageList;
    Progressive: TCheckBox;
    Reload: TSpeedButton;
    Divide: TShape;
    BarHolder: TPanel;
    SizeHolder: TGroupBox;
    CSize: TLabel;
    USize: TLabel;
    Legend1: TShape;
    Legend2: TShape;
    GAMA: TLabel;
    TestGroup: TGroupBox;
    NoGammaLabel: TLabel;
    DefaultGammaLabel: TLabel;
    KeywordLabel: TLabel;
    Keyword: TComboBox;
    TextLabel: TLabel;
    Text: TMemo;
    SaveFileDialog: TSaveDialog;
    SpeedButton1: TSpeedButton;
    MonthLabel: TLabel;
    DayLabel: TLabel;
    YearLabel: TLabel;
    MonthEdit: TEdit;
    DayEdit: TEdit;
    YearEdit: TEdit;
    MonthScroll: TUpDown;
    YearScroll: TUpDown;
    DayScroll: TUpDown;
    HourScroll: TUpDown;
    HourEdit: TEdit;
    HourLabel: TLabel;
    MinLabel: TLabel;
    MinEdit: TEdit;
    SecondEdit: TEdit;
    SecondLabel: TLabel;
    MinScroll: TUpDown;
    SecondScroll: TUpDown;
    procedure StatusDrawPanel(StatusBar: TStatusBar; Panel: TStatusPanel;
      const Rect: TRect);
    procedure ToggleLeftClick(Sender: TObject);
    procedure ToggleRightClick(Sender: TObject);
    procedure ChunkListAdvancedCustomDraw(Sender: TCustomListView;
      const ARect: TRect; Stage: TCustomDrawStage;
      var DefaultDraw: Boolean);
    procedure LoadFileClick(Sender: TObject);
    procedure ImageProgress(Sender: TObject; Stage: TProgressStage;
      PercentDone: Byte; RedrawNow: Boolean; const R: TRect;
      const Msg: String);
    procedure PropsClick(Sender: TObject);
    procedure PaletteAreaPaint(Sender: TObject);
    procedure ChunkListChange(Sender: TObject; Item: TListItem;
      Change: TItemChange);
    procedure FormPaint(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure ReloadClick(Sender: TObject);
    procedure SaveFileClick(Sender: TObject);
    procedure TextExit(Sender: TObject);
    procedure SaveFileDialogShow(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    MyPie: TWin95PieChart;
    PLTEPalette: TBitmap;
    Gamma1, Gamma2: TGammaTester;
    LoadPicture: TPicture;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Progress(Value: Byte);
    procedure LoadFromFile(Filename: String);
  end;

var
  MainForm: TMainForm;

implementation

var
  Loading: Boolean = FALSE;
  LastPos: Integer;

{$R *.DFM}

{ TMainForm }

{Toggle the visibility of a panel}
procedure TogglePanel(Panel: TPanel; Button: TSpeedButton);
var
  Visible: Boolean;
begin
  Visible := (Button.Caption = '«');

  {Save the old width}
  if not Visible then
  begin
    Button.Caption := '«';
    Panel.Tag := Panel.Width;
    while Panel.Width > 14 do
    begin
      Panel.Width := Panel.Width - 1;
      {From time to time make it appears sliding}
      if Panel.Width mod 4 = 0 then
        Application.Processmessages;
    end;
  end
  else
  begin
    Button.Caption := '»';
    while Panel.Width < Panel.Tag do
    begin
      Panel.Width := Panel.Width + 1;
      {From time to time make it appears sliding}
      if Panel.Width mod 4 = 0 then
        Application.Processmessages;
    end;
  end;

end;

{When the form is being created}
constructor TMainForm.Create(AOwner: TComponent);
var
  i : Integer;
begin
  inherited;
  Props.PageIndex := 0;

  Gamma1 := TGammaTester.Create(TestGroup);
  Gamma2 := TGammaTester.Create(TestGroup);

  with Gamma1 do
  begin
    Parent := TestGroup;
    Visible := True;
    SetBounds(NoGammaLabel.Left, NoGammaLabel.Top + 3 + NoGammaLabel.Height,
       TestGroup.Width - (NoGammaLabel.Left * 2), 15);
    Gamma := 1;
  end;

  with Gamma2 do
  begin
    Parent := TestGroup;
    Visible := True;
    SetBounds(DefaultGammaLabel.Left, DefaultGammaLabel.Top + 3 + 
       DefaultGammaLabel.Height,
       TestGroup.Width - (DefaultGammaLabel.Left * 2), 15);
  end;

  Mypie := TWin95PieChart.Create(BarHolder);
  with MyPie do
  begin
    Parent := BarHolder;
    Visible := TRUE;
    Align := alClient;
    Color := clAppWorkspace;
    Depth := 10;
    DoubleBuffered := TRUE;
  end;

  LoadPicture := TPicture.Create;
  LoadPicture.OnProgress := ImageProgress;

  {Create bitmap to show the PNG palette}
  PltePalette := TBitmap.Create;
  with PltePalette do
  begin
    PixelFormat := pf24Bit;
    Width := Props.Width;
    Height := Props.Height;
  end;

  {Turn on double buffering to avoid flickering}
  IF ComponentCount > 0 THEN
  FOR i := 0 TO ComponentCount - 1 DO
    IF Components[i] is TWINControl then
      TWINControl(Components[i]).DoubleBuffered := TRUE;
end;

{Change the value of the progress area}
procedure TMainForm.Progress(Value: Byte);
begin
  {Ensures that the value does not pass 100}
  if Value > 100 then
    Value := 100;

  {Set the panel text}
  Status.Panels[1].Text := INTTOSTR(Value);

end;

{Custom drawning for a panel}
procedure TMainForm.StatusDrawPanel(StatusBar: TStatusBar;
  Panel: TStatusPanel; const Rect: TRect);
var
  CleanRect,
  DrawRect  : TRect;
begin
  {Test if it is the progress panel}
  if Panel.Index = 1 then
  begin
    {Make a copy of the rect}
    DrawRect := Rect;
    {Set the rect of the drawning area}
    DrawRect.Right := Rect.Left + strtointdef(Panel.Text, 0);
    {Draw the blue area}
    FillRect(StatusBar.Canvas.Handle, DrawRect, COLOR_HIGHLIGHT + 1);
    {Set to drawn the non used area}
    SubtractRect(CleanRect, Rect, DrawRect);
    FillRect(StatusBar.Canvas.Handle, CleanRect, COLOR_BTNFACE + 1);
  end;
end;

{Toggle left panel size}
procedure TMainForm.ToggleLeftClick(Sender: TObject);
begin
  TogglePanel(LeftPanel, TSpeedButton(Sender));
end;

{Toggle right panel size}
procedure TMainForm.ToggleRightClick(Sender: TObject);
begin
  ChunkList.ShowColumnHeaders := FALSE;
  TogglePanel(RightPanel, TSpeedButton(Sender));
  ChunkList.ShowColumnHeaders := TRUE;
end;

{When drawing the chunk list}
procedure TMainForm.ChunkListAdvancedCustomDraw(Sender: TCustomListView;
  const ARect: TRect; Stage: TCustomDrawStage; var DefaultDraw: Boolean);
var
  OldFont, NewFont: HFont;
begin
  {If not a TPNGImage then}
  if not (LoadPicture.Graphic is TPNGImage) then
  begin
    {Create a font}
    NewFont := CreateFont(-20, 20, -450, -450, FW_BOLD, 1, 0, 0,
      ANSI_CHARSET, OUT_DEFAULT_PRECIS	, CLIP_DEFAULT_PRECIS,
      ANTIALIASED_QUALITY, DEFAULT_PITCH, 'Tahoma');
    OldFont := SelectObject(Sender.Canvas.Handle, NewFont);
    {Draw the text}
    SetTextColor(Sender.Canvas.Handle, GetSysColor(COLOR_APPWORKSPACE));
    TextOut(Sender.Canvas.Handle, 14, 20, 'Not a PNG', 9);
    DeleteObject(SelectObject(Sender.Canvas.Handle, OldFont));
  end;
end;

{Load a file using open dialog}
procedure TMainForm.LoadFileClick(Sender: TObject);
begin
  if LoadFileDialog.Execute then
    LoadFromFile(LoadFileDialog.Filename);
end;

{Load a file}
procedure TMainForm.LoadFromFile(Filename: String);
var
  PNG: TPNGImage;
    i: Integer;
Tempo: Double;
begin
  LastPos := 0;
  Loading := TRUE;
  {Checks if shows the image progressively}
  if Progressive.Checked then
    LoadPicture.OnProgress := ImageProgress
  else
    LoadPicture.OnProgress := nil;


  FillRect(Canvas.Handle, ClientRect, COLOR_BTNFACE + 1);

  {Load the image}
  Tempo := GetTickCount;
  LoadPicture.LoadFromFile(Filename);
  Progress(0);
  {Set the file panel}
  Status.Panels[0].Text := Extractfilename(Filename);

  Props.PageIndex := 0;

  {Set the chunk listbox}
  ChunkList.Items.Clear;

  {Do the work if it is a PNG image}
  if LoadPicture.Graphic is TPNGImage then
  begin
    {Copy pointer}
    PNG := TPNGImage(LoadPicture.Graphic);

    if PNG.Chunks.Count > 0 then
    FOR i := 0 TO PNG.Chunks.Count - 1 DO
      with ChunkList.Items.Add do
      begin
        Caption := PNG.Chunks[I].ChunkType;
        subitems.Add(Format('%d bytes', [PNG.Chunks[i].Size]));
      end;

  end;

  Status.Panels[2].Text := format('%n s', [(GetTickCount - Tempo) / 1000]);
  Loading := FALSE;

  Canvas.Draw((Width div 2) - (LoadPicture.Width div 2),
    ((Height) div 2) - (LoadPicture.Height div 2),
    LoadPicture.Graphic);
end;

{Loading progress}
procedure TMainForm.ImageProgress(Sender: TObject; Stage: TProgressStage;
  PercentDone: Byte; RedrawNow: Boolean; const R: TRect;
  const Msg: String);
begin

  {If it is a TPNG image we can show it progressive}
  if Sender is TPNGImage then
  begin

    Progress(PercentDone);
    if (PercentDone mod 5 = 0) and
      (TChunkIHDR(TPNGIMAGE(SENDER).Chunks[0]).Interlaced = 0) then
    begin
      BitBlt(Canvas.Handle, (Width - TBitmap(Sender).Width) div 2,
        ((Height - TBitmap(Sender).Height) div 2) + LastPos,
        R.Right, R.Bottom - LastPos,
        TBitmap(Sender).Canvas.Handle, 0, LastPos, SRCCOPY);
      LastPos := R.Bottom;
    end
    else if (TChunkIHDR(TPNGIMAGE(SENDER).Chunks[0]).Interlaced = 1) then
      Canvas.Draw((Width - TBitmap(Sender).Width) div 2, 
      ((Height) - TBitmap(Sender).Height) div 2, TBItmap(sender));
  end;

  Application.Processmessages;
end;

procedure TMainForm.PropsClick(Sender: TObject);
begin

end;

{When the main form is being destroyed}
destructor TMainForm.Destroy;
begin
  Gamma1.Free;
  Gamma2.Free;
  Mypie.free;
  LoadPicture.Free;
  PltePalette.Free;
  inherited;
end;

{When painting the area that shows the image palette}
procedure TMainForm.PaletteAreaPaint(Sender: TObject);
begin
  if Assigned(PltePalette) then
    PaletteArea.Canvas.Draw(0, 0, PltePalette);
end;

{When changing ocurrs (like selection change)}
procedure TMainForm.ChunkListChange(Sender: TObject; Item: TListItem;
  Change: TItemChange);
label
  finished;
var
  IDATC     : TChunkIDAT;
  PalEntries: WORD;
  IHDRC     : TChunkIHDR;
  TEXTC     : TChunkText;
  TIMEC     : TChunkTime;
  ZTXTC     : TChunkZTXT;
  i, j, x   : Integer;
  MaxPal    : TMaxLogPalette;
  Pal       : HPalette;
  Value1,
  Value2,
  Value3,
  Value4    : Word;
  DateTime  : TDateTime;
begin
  {Only selection matters}
  if not Assigned(ChunkList.Selected)  then exit;


  if (ChunkList.Selected.Caption = 'tIME') then
  begin
    Props.PageIndex := 6;
    TIMEC := TChunkTIME(TPNGIMAGE(LoadPicture.Graphic).Chunks[
      ChunkList.Selected.Index]);
    DateTime := TIMEC.DateTime;
    {Get the values}
    {time}
    DecodeTime(DateTime, Value1, Value2, Value3, Value4);
    HourScroll.Position := Value1;
    MinScroll.Position := Value2;
    SecondScroll.Position := Value3;
    {date}
    DecodeDate(DateTime, Value1, Value2, Value3);
    YearScroll.Position := Value1;
    MonthScroll.Position := Value2;
    DayScroll.Position := Value3;
  end
  else if (ChunkList.Selected.Caption = 'zTXt') then
  begin
    Props.PageIndex := 5;
    ZTXTC := TChunkZTXT(TPNGIMAGE(LoadPicture.Graphic).Chunks[
      ChunkList.Selected.Index]);

    {Set the text values}
    Keyword.Text := ZTXTC.Keyword;
    Text.Text := ZTXTC.Text;
  end
  {If the current selected item is a tEXt chunk}
  else if (ChunkList.Selected.Caption = 'tEXt') then
  begin
    Props.PageIndex := 5;
    TEXTC := TChunkTEXT(TPNGIMAGE(LoadPicture.Graphic).Chunks[
      ChunkList.Selected.Index]);

    {Set the text values}
    Keyword.Text := TEXTC.Keyword;
    Text.Text := TEXTC.Text;
  end
  {If the current selected item is a gama chunk}
  else if ChunkList.Selected.Caption = 'gAMA' then
  begin
    Props.PageIndex := 4;
    Gama.Caption := 'Gamma intensity: ' + floattostr(
      TChunkGAMA(TPNGIMAGE(LoadPicture.Graphic).Chunks[
      ChunkList.Selected.Index]).Value / 100000);
      Gamma2.Gamma := TChunkGAMA(TPNGIMAGE(LoadPicture.Graphic).Chunks[
      ChunkList.Selected.Index]).Value / 100000;
  end
  {If the current selected item is a palette}
  else if ChunkList.Selected.Caption = 'IDAT' then
  begin
    {Select the IDAT page}
    Props.PageIndex := 3;
    IDATC := TChunkIDAT(TPNGImage(LoadPicture.Graphic).Chunks[ChunkList.Selected.Index]);
    MyPie.Maximum := 100;
    MyPie.Value := MulDiv(100, IDATC.Size,
      ((TIDATAccess(IDATC).GetBufferWidth + 1) *  LoadPicture.Height));

    CSize.Caption := '    Compressed: ' + inttostr(MyPie.Value) + '%'#13#10 + ChunkList.Selected.subitems[0];
    USize.Caption := '    Uncompressed: 100%'#13#10 +
      inttostr((TIDATAccess(IDATC).GetBufferWidth + 1) *  LoadPicture.Height) + ' bytes';
  end
  {If the current selected item is a palette}
  else if ChunkList.Selected.Caption = 'PLTE' then
  begin
    {Select the palette area}
    Props.PageIndex := 1;
    {Get palette info}
    Pal := TChunkPLTE(TPNGImage(LoadPicture.Graphic).Chunks[ChunkList.Selected.Index]).Palette;
    GetObject(Pal, SIZEOF(WORD), @PalEntries);
    GetPaletteEntries(Pal, 0, PalEntries, MaxPal.palpalentry);
    PaletteTitle.Caption := 'Palette entries: ' + inttostr(palentries);

    {Draw the pallete}
    x := 0; j := 0;
    PltePalette.Canvas.Brush.Color := clWhite;
    PltePalette.Canvas.FillRect(Rect(0, 0, PltePalette.Width, PltePalette.Height));

    repeat
      i := 0;
      repeat
        with MaxPal.palPalEntry[x] do
          PltePalette.Canvas.Brush.Color := RGB(peRed, peGreen, peBlue);
        PltePalette.Canvas.Rectangle(i, j, i + 10, j + 10);
        inc(x);
        inc(i, 10);
        if x > PalEntries - 1 then
          goto FInished;
      until i >= PltePalette.Width;
      inc(j, 10);
    until j >= PltePalette.Height;

    finished:
    {Repaint the palette area}
    PaletteAreaPaint(Sender);
  end
  else if ChunkList.Selected.Caption = 'IHDR' then
  begin
    {Select IHDR page}
    Props.PageIndex := 2;
    {Expand all nodes and remove "checks"}
    FOR i := 0 to IHDR.Items.Count - 1 do
    begin
      IHDR.Items[i].Expand(TRUE);
      if (IHDR.Items[i].ImageIndex = 0) and
        (IHDR.Items[i].Owner.Count > 1) then
      begin
        IHDR.Items[i].ImageIndex := -1;
        IHDR.Items[i].SelectedIndex := -1;
      end;

    end;

    {Pointer to the IHDR chunk}
    IHDRC := TChunkIHDR(TPNGImage(LoadPicture.Graphic).Chunks[ChunkList.Selected.Index]);

    {Compression}
    IHDR.Items[13].ImageIndex := 0;
    IHDR.Items[13].SelectedIndex := 0;
    {Filter set}
    IHDR.Items[15].ImageIndex := 0;
    IHDR.Items[15].SelectedIndex := 0;

    {Filter set}
    IHDR.Items[19].Text := 'Width: ' + inttostr(IHDRC.Width);
    {Filter set}
    IHDR.Items[20].Text := 'Height: ' + inttostr(IHDRC.Height);

    {Interlacing}
    if IHDRC.Interlaced = 1 then
    begin
      IHDR.Items[17].ImageIndex := 0;
      IHDR.Items[17].SelectedIndex := 0;
    end
    else
    begin
      IHDR.Items[18].ImageIndex := 0;
      IHDR.Items[18].SelectedIndex := 0;
    end;

    {Bit depth}
    CASE IHDRC.BitDepth of
      1:begin
        IHDR.Items[7].ImageIndex := 0;
        IHDR.Items[7].SelectedIndex := 0;
        end;
      2:begin
        IHDR.Items[8].ImageIndex := 0;
        IHDR.Items[8].SelectedIndex := 0;
        end;
      4:begin
        IHDR.Items[9].ImageIndex := 0;
        IHDR.Items[9].SelectedIndex := 0;
        end;
      8:begin
        IHDR.Items[10].ImageIndex := 0;
        IHDR.Items[10].SelectedIndex := 0;
        end;
      16:begin
        IHDR.Items[11].ImageIndex := 0;
        IHDR.Items[11].SelectedIndex := 0;
        end;
    end;

    {Set the color type}
    CASE IHDRC.ColorType of
      0:begin
        IHDR.Items[1].ImageIndex := 0;
        IHDR.Items[1].SelectedIndex := 0;
        end;
      2:begin
        IHDR.Items[2].ImageIndex := 0;
        IHDR.Items[2].SelectedIndex := 0;
        end;
      3:begin
        IHDR.Items[3].ImageIndex := 0;
        IHDR.Items[3].SelectedIndex := 0;
        end;
      4:begin
        IHDR.Items[4].ImageIndex := 0;
        IHDR.Items[4].SelectedIndex := 0;
        end;
      6:begin
        IHDR.Items[5].ImageIndex := 0;
        IHDR.Items[5].SelectedIndex := 0;
        end;
    end;

    IHDR.ScrollBy(0, -1000);
  end
  else
    Props.PageIndex := 0;


end;

{When painting the form}
procedure TMainForm.FormPaint(Sender: TObject);
begin
  if Loading then exit;
  FillRect(Canvas.Handle, ClientRect, COLOR_BTNFACE + 1);
  Canvas.Draw((Width div 2) - (LoadPicture.Width div 2),
    ((Height) div 2) - (LoadPicture.Height div 2),
    LoadPicture.Graphic);
end;

procedure TMainForm.FormResize(Sender: TObject);
begin
  FormPaint(Sender);
end;

{Reload the last file}
procedure TMainForm.ReloadClick(Sender: TObject);
begin
  if Fileexists(LoadFileDialog.Filename) then
    LoadFromFile(LoadFileDialog.Filename)
  else
    Showmessage('No last file loaded!');
end;


{ TGammaTester }

{When the object is being created}
constructor TGammaTester.Create(AOwner: TComponent);
begin
  inherited;

  DoubleBuffered := TRUE;
  
  {Create the backbuffer bitmap}
  Bitmap := TBitmap.Create;

  {Set 24bits format}
  with Bitmap do
    PixelFormat := pf24bit;

end;

{When the object is being destroyed}
destructor TGammaTester.Destroy;
begin
  {Free the backbuffer bitmap}
  Bitmap.Free;
  inherited;
end;

{When the control is being resized}
procedure TGammaTester.OnResize(var Message: TWMSize);
begin
  inherited;

  RecreateBitmap;
end;


{When the control is being painted}
procedure TGammaTester.Paint;
begin
  inherited;
  Canvas.Draw(0, 0, Bitmap);
end;

{Redraw the gamma bitmap}
procedure TGammaTester.RecreateBitmap;
var
  Line   : pRGBLine;
  x, y   : Integer;
begin
  {Set the bitmap size}
  Bitmap.Width := Width;
  Bitmap.Height := Height;

  {Paint each line}
  for y := 0 to Bitmap.Height - 1 do
  begin
    Line := Bitmap.ScanLine[y];
    for x := 0 to Bitmap.Width - 1 do
    begin
      {Set the line color}
      with Line^[x] do
      begin
        rgbtRed := Table[MulDiv(255, x, Bitmap.Width)];
        rgbtGreen := rgbtRed;
        rgbtBlue := rgbtRed;
      end;
    end;
  end;

  {Repaint}
  Paint;
end;

{When the property gamma is being set}
procedure TGammaTester.SetGamma(Value: Double);
var
  I: Integer;
begin
  FOR I := 0 TO 255 DO
    Table[I] := Round(Power((I / 255), 1 / (Value * 2.2)) * 255);

  vGamma := Value;
  RecreateBitmap;
end;

procedure TMainForm.SaveFileClick(Sender: TObject);
var
  SaveFilters: TEncodeFilterSet;
  Tempo: Double;

begin
  if LoadPicture.Graphic = nil then
  begin
    showmessage('There is no image currently loaded to save.');
    exit;
  end;

  if SaveFileDialog.Execute  then
  begin
  Tempo := GetTickCount;

  with TPNGImage.Create do
  begin
    {Test which filters the user selected}
//    SaveFilters := [];
{    with SaveSelect.FilterSelect do
    begin
      if Items[0].Checked then
        Include(SaveFilters, efSub);
      if Items[1].Checked then
        Include(SaveFilters, efUp);
      if Items[2].Checked then
        Include(SaveFilters, efAverage);
      if Items[3].Checked then
        Include(SaveFilters, efPaeth);
    end;}

    {Set the filters to use}
    SaveFilters := [efUp];
    Filter := SaveFilters;

    Assign(LoadPicture.Graphic);
    SaveToFile(SaveFileDialog.Filename);
    Status.Panels[2].Text := format('%n s', [(GetTickCount - Tempo) / 1000]);
    free;
  end;
  end;
end;


{When the Text TMEMO for editing the tEXt chunk}
{is changed, change the chunk}
procedure TMainForm.TextExit(Sender: TObject);
var
  TEXTC: TChunkText;
  ZTXTC: TChunkZTXT;
begin

  if TPNGIMAGE(LoadPicture.Graphic).Chunks[ChunkList.Selected.Index] is
    TChunkText then
  begin
    {Copy pointer to the chunk}
    TEXTC := TChunkTEXT(TPNGIMAGE(LoadPicture.Graphic).Chunks[
      ChunkList.Selected.Index]);

    {Change the value}
    TEXTC.Keyword := Keyword.Text;
    TEXTC.Text := Text.Lines.Text;

    ChunkList.Selected.SubItems[0] := inttostr(TEXTC.Size) + ' bytes';
  end
  else
  begin
    {Copy pointer to the chunk}
    ZTXTC := TChunkZTXT(TPNGIMAGE(LoadPicture.Graphic).Chunks[
      ChunkList.Selected.Index]);

    {Change the value}
    ZTXTC.Keyword := Keyword.Text;
    ZTXTC.Text := Text.Lines.Text;

    ChunkList.Selected.SubItems[0] := inttostr(ZTXTC.Size) + ' bytes';
  end;
end;

procedure TMainForm.SaveFileDialogShow(Sender: TObject);
var
  SaveHandle:integer;
begin
  SaveHandle := GetParent(SaveFileDIalog.handle);
  SetWindowPos(SaveHandle, HWND_TOP, 0, 0, 480, 400, SWP_NOMOVE);

end;

procedure TMainForm.SpeedButton1Click(Sender: TObject);
var
  MainForm: TForm;
  EWidth, EHeight: TEdit;
  StretchPNG: TPNGImage;
begin
  if LoadPicture.Graphic = nil then
  begin
    showmessage('There is no image currently loaded to stretch.');
    exit;
  end;

  MainForm := TForm.Create(Self);
  with MainForm do
  begin
    {Dialog properties}
    Caption := 'Select the new size:';
    BorderStyle := bsDialog;
    Position := poMainFormCenter;
    {Size}
    Width := 200;
    Height := 150;

    {Creates the OK button}
    with TButton.Create(MainForm) do
    begin
      Parent := MainForm;
      Caption := '&Ok';
      SetBounds(110, 94, Width, Height);
      ModalResult := mrOk;
    end;

    {Creates the divisor from the buttons and text area}
    with TBevel.Create(MainForm) do
    begin
      Parent := MainForm;
      SetBounds(10, 84, 180, 2);
    end;

    {Creates the width edit}
    EWidth := TEdit.Create(MainForm);
    with EWidth do
    begin
      {Width label}
      with TLabel.Create(MainForm) do
      begin
        Parent := MainForm;
        Caption := 'Width:';
        SetBounds(10, 20, 50, 20);
      end;

      Text := inttostr(LoadPicture.Width);
      Parent := MainForm;
      SetBounds(50, 15, 50, 20);
    end;
    EHeight := TEdit.Create(MainForm);
    with EHeight do
    begin
      Text := inttostr(LoadPicture.Height);
      {Height label}
      with TLabel.Create(MainForm) do
      begin
        Parent := MainForm;
        Caption := 'Height:';
        SetBounds(10, 47, 50, 20);
      end;

      SetBounds(50, 44, 50, 20);
      Parent := MainForm;
    end;

    {Creates the cancel button}
    with TButton.Create(MainForm) do
    begin
      Parent := MainForm;
      Caption := '&Cancel';
      SetBounds(10, 94, Width, Height);
      ModalResult := mrOk;
    end;

    {Show the dialog}
    if ShowModal = mrOk then
    begin
      StretchPNG := TPNGImage.Create;
      with StretchPNG do
      begin
        Assign(LoadPicture.Graphic);
        Width := strtointdef(EWidth.Text, LoadPicture.Width);
        Height := strtointdef(EHeight.Text, LoadPicture.Height);
        Canvas.StretchDraw(Rect(0, 0, Width, Height), LoadPicture.Graphic);
        LoadPicture.Assign(StretchPNG);
        Free;
      end;
    end;
    {Free the dialog}
    free;
  end;
  Repaint;
end;

end.
