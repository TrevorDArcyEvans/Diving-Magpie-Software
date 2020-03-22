unit Dropper;

{***********************************************}
{                                               }
{  TFileDropper                                 }
{  Copyright ©1999 Lloyd Kinsella Software.     }
{                                               }
{  Version 1.0                                  }
{                                               }
{  DO NOT MODIFY OR REMOVE THIS HEADER!         }
{                                               }
{***********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ShellAPI;

type
 TOnDrop = procedure (Sender: TObject; Filename: String) of object;

type
  TFileDropper = class(TComponent)
  private
    { Private declarations }
    FWndProcInstance: Pointer;
    FDefProc: LongInt;
    FDropSite: TWinControl;
    FOnDrop: TOnDrop;
    FAllowDir: Boolean;
    FSubFolder: Boolean;
    procedure WndProc(var Message: TMessage);
    procedure DropFile(Drop: HDROP);
    procedure Add(Path: String);
    procedure AddFolder(Path: String);
    function IsDirectory(Path: String): Boolean;
  protected
    { Protected declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Loaded; override;
  public
    { Public declarations }
  published
    { Published declarations }
    property DropSite: TWinControl read FDropSite write FDropSite;
    property OnDrop: TOnDrop read FOnDrop write FOnDrop;
    property AllowDir: Boolean read FAllowDir write FAllowDir;
    property SubFolders: Boolean read FSubFolder write FSubFolder;
  end;

procedure Register;

implementation

constructor TFileDropper.Create(AOwner: TComponent);
begin
 inherited Create(AOwner);
 FAllowDir := False;
 FSubFolder := False;
end;

destructor TFileDropper.Destroy;
begin
 inherited Destroy;
end;

procedure TFileDropper.WndProc(var Message: TMessage);
begin
if Message.Msg = WM_DROPFILES then
 begin
  DropFile(Message.WParam);
  Message.Result := 0;
 end
else
 Message.Result := CallWindowProc(Pointer(FDefProc),FDropSite.Handle,Message.Msg,
 Message.WParam, Message.LParam);
end;

procedure TFileDropper.Loaded;
var
Wnd: HWND;
begin
 inherited Loaded;
  if not (csDesigning in ComponentState) and (FDropSite <> nil) then
   begin
    Wnd := FDropSite.Handle;
    FWndProcInstance := MakeObjectInstance(WndProc);
    FDefProc := SetWindowLong(Wnd,GWL_WNDPROC,LongInt(FWndProcInstance));
    DragAcceptFiles (Wnd, True);
   end;
end;

procedure TFileDropper.DropFile(Drop: HDROP);
var
I, NumFiles: Integer;
lpszFileName: array [0..255] of Char;
begin
NumFiles := DragQueryFile(Drop,$FFFFFFFF,nil,0);
 for I := 0 to NumFiles - 1 do
  begin
   DragQueryFile(Drop,I,lpszFileName,SizeOf(lpszFileName));
   Add(StrPas(lpszFileName));
  end;
DragFinish(Drop);
end;

procedure TFileDropper.Add(Path: String);
begin
if IsDirectory(Path) = False then
 begin
  if Assigned(FOnDrop) then FOnDrop(Self,Path);
 end
else
 if AllowDir then
  begin
   AddFolder(Path);
  end;
end;

procedure TFileDropper.AddFolder(Path: String);
var
I: Integer;
SearchRec: TSearchRec;
begin
I := FindFirst(Path + '\*.*',faAnyFile,SearchRec);
while I = 0 do
 begin
  if (SearchRec.Name[1] <> '.') then
   begin
    if IsDirectory(Path + '\' + SearchRec.Name) = False then
     begin
      if Assigned(FOnDrop) then FOnDrop(Self,Path + '\' + SearchRec.Name);
     end
    else
   if FSubFolder = True then
    begin
     AddFolder(Path + '\' + SearchRec.Name);
    end;
   end;
  I := FindNext(SearchRec);
 end;
FindClose(SearchRec);
end;

function TFileDropper.IsDirectory(Path: String): Boolean;
begin
if (FileGetAttr(Path) and faDirectory) = 0 then
 begin
  Result := False;
 end
else
Result := True;
end;

procedure Register;
begin
  RegisterComponents('Samples', [TFileDropper]);
end;

end.
