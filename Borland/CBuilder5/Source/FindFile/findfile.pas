unit FindFile;

//   FindFile version 1.0.1
//
//   Copyright (C) September 1997 Walter Dorawa
//
//   Everyone is free to use this code as they wish, but
//   if you use it commercially then I wouldn't mind a
//   little something.
//
//   Please submit suggestions, bugs, or any improvements to
//   walterd@gte.net
//
//   Improvements:  10-21-97
//         Attributes property               TotalFile
//         Abort property                    TotalSpace
//         OnNewPath event                   TotalDir
//
//         thanks to: Howard Harvey, Jim Keatley and Dale Derix
//         for suggestions and code improvements
//

interface

uses
  Classes, SysUtils, Dialogs;

type
  TAttrOption = (ffReadOnly, ffHidden, ffSystem, ffVolumeID, ffDirectory, ffArchive);
  TAttrOptions = set of TAttrOption;
  TNewPathEvent = procedure(Sender: TObject; NewPath: string; var Abort: boolean) of object;

  TFindFile = class(TComponent)
  private
    { Private declarations }
    FAbort:boolean;
    FTotalSpace:longint;
    FTotalDir:longint;
    FTotalFile:longint;
    FAttribs:TAttrOptions;
    FDirectory:string;
    FRecurse:boolean;
    FFilter :string;
    FFiles: TStrings;
    FBeforeExecute: TNotifyEvent;
    FAfterExecute: TNotifyEvent;
    FOnNewPath: TNewPathEvent;
    procedure SearchCurrentDirectory(Directory:string);
    procedure SearchRecursive(Directory:string);
    function FindSubDirectory(strDirs:TStringList; Directory:string):Boolean;
  protected
    { Protected declarations }
    procedure SetFiles(Value: TStrings);
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Execute; dynamic;
    property TotalSpace: longint read FTotalSpace write FTotalSpace;
    property TotalDir: longint read FTotalDir write FTotalDir;
    property TotalFile: longint read FTotalFile write FTotalFile;
    property Abort: boolean read FAbort write FAbort default False;
  published
    { Published declarations }
    property Recurse: boolean read FRecurse write FRecurse default False;
    property Directory: string read FDirectory write FDirectory;
    property Filter: string read FFilter write FFilter;
    property Files: TStrings read FFiles write SetFiles;
    property Attributes: TAttrOptions read FAttribs write FAttribs
             default [ffReadOnly, ffHidden, ffSystem, ffArchive];
    property BeforeExecute: TNotifyEvent read FBeforeExecute write FBeforeExecute;
    property AfterExecute: TNotifyEvent read FAfterExecute write FAfterExecute;
    property OnNewPath: TNewPathEvent read FOnNewPath write FOnNewPath;
  end;

procedure Register;

//===================================================================================
//===================================================================================

implementation

const
  DefaultFilter = '*.*';

var
  Attribs:integer;

constructor TFindFile.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FFilter:=DefaultFilter;
  FAttribs:=[ffReadOnly, ffHidden, ffSystem, ffArchive];
  FFiles:=TStringList.Create;
end;

destructor TFindFile.Destroy;
begin
  FFiles.Free;
  inherited Destroy;
end;

procedure TFindFile.SetFiles(Value: TStrings);
begin
  FFiles.Assign(Value);
end;

procedure TFindFile.Execute;
begin
  Attribs:=0;
  if ffReadOnly in Attributes then Attribs:=Attribs+faReadOnly;
  if ffHidden    in Attributes then Attribs:=Attribs+faHidden;
  if ffSystem    in Attributes then Attribs:=Attribs+faSysFile;
  if ffVolumeID  in Attributes then Attribs:=Attribs+faVolumeID;
  if ffDirectory in Attributes then Attribs:=Attribs+faDirectory;
  if ffArchive   in Attributes then Attribs:=Attribs+faArchive;

  FFiles.Clear;
  FTotalSpace:=0;
  FTotalDir:=0;
  FTotalFile:=0;
  if Assigned(FBeforeExecute) then FBeforeExecute(Self);
  if Length(FDirectory)<>0 then
    if FRecurse then SearchRecursive(FDirectory)
    else SearchCurrentDirectory(FDirectory);
  if Assigned(FAfterExecute) then FAfterExecute(Self);
end;

procedure TFindFile.SearchCurrentDirectory(Directory:string);
var
  i:integer;
  srchRec:TSearchRec;
begin
  if Directory[Length(Directory)]<>'\' then AppendStr(Directory,'\');
  if Assigned(FOnNewPath) then FOnNewPath(Self,Directory,FAbort);
  if FAbort then Exit;
  i:=FindFirst(Directory+FFilter,Attribs,srchRec);
  while i=0 do
    begin
    if (srchRec.Name<>'.') and (srchRec.Name<>'..')  then
      begin
      FFiles.Add(Directory+srchRec.Name);
      case srchRec.Attr of
        faDirectory: Inc(FTotalDir);
        else         Inc(FTotalFile);
      end;
      FTotalSpace:=FTotalSpace+srchRec.Size;
      end;
    i:=FindNext(srchRec);
    end;
  FindClose(srchRec);
end;

procedure TFindFile.SearchRecursive(Directory:string);
var
  strDirs:TStringList;
begin
  strDirs:=TStringList.Create;
  try
  if Directory[Length(Directory)]<>'\' then AppendStr(Directory,'\');
  strDirs.Clear;
  strDirs.Add(Directory);
  while strDirs.Count<>0 do
    begin
    FindSubDirectory(strDirs,strDirs.Strings[0]);
    SearchCurrentDirectory(strDirs.Strings[0]);
    strDirs.Delete(0);
    if FAbort then Exit;
    end;
  finally
  strDirs.Free;
  end;
end;

function TFindFile.FindSubDirectory(strDirs:TStringList; Directory:string):Boolean;
var
  i:integer;
  srchRec:TSearchRec;
begin
  Result:=True;
  if Directory[Length(Directory)]<>'\' then AppendStr(Directory,'\');
  i:=FindFirst(Directory+'*.*',faAnyFile,srchRec);
  while i=0 do
    begin
    if ((srchRec.Attr and faDirectory)>0) and (srchRec.Name<>'.') and (srchRec.Name<>'..') then
      begin
      strDirs.Add(Directory+srchRec.Name);
      end;
    i:=FindNext(srchRec);
    end;
  FindClose(srchRec);
end;

procedure Register;
begin
  RegisterComponents('Samples', [TFindFile]);
end;

end.
