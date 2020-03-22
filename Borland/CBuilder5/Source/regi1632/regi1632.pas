unit Regi1632;

{**************************************************************************

  TRegistry1632

  This unit provides access to the registry in Delphi 1.0 AND Delphi 2.0

  Author: Hannes Danzl (e9026733@stud3.tuwien.ac.at)

  FREEWARE

  If you change it, please send me a copy!!

  When running the Application in Windows 3.x the registry-functions do
  nothing!

************************************************************************** }

{$R-}

interface

uses Classes, SysUtils,
     {$ifdef win32}Windows{$else}Wintypes, Winprocs, Reginc{$endif};

const keynotfoundvalue='xyxyxyxyxyxyxyxyxyxyxyxyxyx';

type
  TRegistry1632 = class(TComponent)
  private
    fRunningWin31:Boolean;
    fIniFileName:String;
    fWasError:Boolean;
    fErrorMessage:String;
    function ReadKey(Where:LongInt;Key, Path:String):string;
    procedure WriteKey(Where:LongInt;Key, Path, Value:String);
  protected
  public
    constructor Create(AOwner:TComponent);override;
    destructor Destroy; override;

    { Reads a Value from the registry in HKEY_LOCAL_MACHINE }
    function ReadString(Path, Key:String): string;
    { Reads a Value from the registry in HKEY_CURRENT_USER }
    function ReadUserString(Path, Key:string): string;
    { Writes a Value to the registry in HKEY_LOCAL_MACHINE }
    procedure WriteString(Path, Key, Value:String);
    { Writes a Value from the registry in HKEY_CURRENT_USER }
    procedure WriteUserString(Path, Key, Value:String);

    property WasError:boolean read fWasError;
    property ErrorMessage:string read fErrorMessage;
  published
    property RunningWin31:Boolean read FRunningWin31 write FRunningWin31;
    property IniFileName:string read fIniFileName write fIniFileName;
  end;

procedure Register;

implementation

uses dialogs, inifiles;

procedure Register;
begin
  RegisterComponents('Samples', [TRegistry1632]);
end;

constructor TRegistry1632.Create;
var along1,along2,along:longint;
    mainversion, subversion:longint;
begin
  inherited Create(AOwner);
  IniFileName:='registry.ini';
  fWasError:=false;
  fErrorMessage:='';

  frunningwin31:=false;
  {$ifndef win32}
  { check for windowsnt or wind95 }
  { thanks to Per Bak (Per.Bak@post3.tele.dk), who corrected the bug! }
  if (GetWinFlags and $4000 {WF_WINNT} ) = 0 then
      if lobyte(loword(getversion))<4 then
       if hibyte(loword(getversion))<95 then
        frunningwin31:=true;
  {$endif}
end;

destructor TRegistry1632.Destroy;
begin
  inherited Destroy;
end;

procedure TRegistry1632.WriteString(Path, Key, Value:String);
begin
  WriteKey(HKEY_LOCAL_MACHINE,Key,path, Value);
end;

procedure TRegistry1632.WriteUserString(Path, Key, Value:String);
begin
  WriteKey(HKEY_CURRENT_USER,Key,path, Value);
end;

procedure TRegistry1632.WriteKey(Where:LongInt;Key, Path, Value:String);
var
  aValue:array[0..256] of char;
  aname:array[0..256] of char;
  DataType:Longint;
  DataLen:longint;
  QueryResult:LongInt;
  aIniFile:TInifile;
{$ifdef win32}
  KeyHandle: HKEY;
{$else}
  KeyHandle: LongInt;
{$endif}
begin
  fwaserror:=false;
  if runningwin31 then
  begin
    try
      aIniFile:=TIniFile.Create(IniFileName);
      if where=HKEY_LOCAL_MACHINE then
        path:='LM_'+path
      else
        path:='CU_'+path;
      aIniFile.WriteString(path,key,value);
    except
      ainifile.free;
      ferrormessage:=Format('Writekey to Inifile failed: %s set to %s in file %s',
        [Path+Key, Value, IniFileName]);
      fwaserror:=true;
    end;
    ainifile.free;
    exit;
  end;

  strpcopy(aname,Path);
  if RegOpenKeyEx(where,aname,0,KEY_ALL_ACCESS, keyHandle)<>error_success then
  begin
    ferrormessage:=Format('Openkey failed for path "%s"', [Path]);
    fwaserror:=true;
    exit;
  end;

  strpcopy(avalue,value);
  DataType := REG_SZ;
  DataLen:=strlen(avalue);

  strpcopy(aname,key);
  QueryResult:=RegSetValueEx(KeyHandle, @aName, 0, DataType, PByte(@aValue),
    DataLen);
  if QueryResult <> ERROR_SUCCESS then
  begin
    ferrormessage:=Format('RegSetValueEX failed for path "%s" key "%s"', [Path, Key]);
    fwaserror:=true;
    exit;
  end;
  if Keyhandle<>0 then
    RegCloseKey(Keyhandle);
end;

function TRegistry1632.ReadString(Path: string; Key:String): string;
begin
  Result:=ReadKey(HKEY_LOCAL_MACHINE,Key, path);
end;

function TRegistry1632.ReadUserString(Path: string; Key:string): string;
begin
  Result:=ReadKey(HKEY_CURRENT_USER,Key, path);
end;

function TRegistry1632.ReadKey(Where:LongInt;Key, Path:String):string;
var
  aresult:array[0..256] of char;
  aname:array[0..256] of char;
{$ifdef win32}
  bufsize:Integer;
  DataType:Integer;
  KeyHandle: HKEY;
{$else}
  bufsize:Longint;
  DataType:Longint;
  KeyHandle: LongInt;
{$endif}
  QueryResult:longint;
  aIniFile:TIniFile;

begin
  fWasError:=false;
  if runningwin31 then
  begin
    try
      aIniFile:=TIniFile.Create(IniFileName);
      if where=HKEY_LOCAL_MACHINE then
        path:='LM_'+path
      else
        path:='CU_'+path;
      result:=aIniFile.ReadString(path,key,keynotfoundvalue);
      if result=keynotfoundvalue then
      begin
        result:='';
        ferrormessage:=Format('Key "%s" not found in pathh "%s"; FileName: "%s"', [Path, Key, IniFileName]);
        fwaserror:=true;
        exit;
      end;
    except
      ainifile.free;
      result:='';
      ferrormessage:=Format('Key "%s" not found in path "%s"; FileName: "%s"', [Path, Key, IniFileName]);
      fwaserror:=true;
      exit;
    end;
    ainifile.free;
    exit;
  end;

  strpcopy(aname,Path);
  result:='';
  if RegOpenKeyEx(where,aname,0,KEY_ALL_ACCESS, keyHandle)<>error_success then
  begin
    ferrormessage:=Format('Openkey failed for path "%s"', [Path]);
    fwaserror:=true;
    exit;
  end;

  DataType := REG_SZ;
  BufSize:=255;
  strpcopy(aname,key);
{$ifndef win32}
  QueryResult:=RegQueryValueEx(KeyHandle, @aName, nil, @DataType, PByte(@aresult),
    BufSize);
{$else}
  QueryResult:=RegQueryValueEx(KeyHandle, @aName, nil, pDWord(@DataType), PByte(@aresult),
    pDWord(@BufSize));
{$endif}
  if QueryResult <> ERROR_SUCCESS then
  begin
    ferrormessage:=Format('Key "%s" not found in path "%s"; FileName: "%s"', [Path, Key, IniFileName]);
    fwaserror:=true;
  end
  else
    result:=strpas(aresult);
  if Keyhandle<>0 then
    RegCloseKey(Keyhandle);
end;

end.


