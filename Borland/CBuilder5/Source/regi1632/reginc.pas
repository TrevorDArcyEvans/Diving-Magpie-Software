unit Reginc;
{**************************************************************************

  Reginc

  This unit provides access to some of the 32 bit registry-functions of
  WinNT/95 for a 16-bit Program.

  Author: Hannes Danzl (e9026733@stud3.tuwien.ac.at)

  FREEWARE

  If you change it, please send me a copy!!

************************************************************************** }

interface

uses
  WinTypes, WinProcs, Forms, call32nt;

type
  HKEY=Longint;

const
  HKEY_CLASSES_ROOT     = $80000000;
  HKEY_CURRENT_USER     = $80000001;
  HKEY_LOCAL_MACHINE    = $80000002;
  HKEY_USERS            = $80000003;
  HKEY_PERFORMANCE_DATA = $80000004;
  HKEY_CURRENT_CONFIG   = $80000005;
  HKEY_DYN_DATA         = $80000006;

  ERROR_SUCCESS = 0;

 const
  { The following are masks for the predefined standard access types }
  _DELETE                  = $00010000; { Renamed from DELETE }
  READ_CONTROL             = $00020000;
  WRITE_DAC                = $00040000;
  WRITE_OWNER              = $00080000;
  STANDARD_RIGHTS_READ     = READ_CONTROL;
  STANDARD_RIGHTS_WRITE    = READ_CONTROL;
  STANDARD_RIGHTS_EXECUTE  = READ_CONTROL;
  STANDARD_RIGHTS_ALL      = $001F0000;
  SPECIFIC_RIGHTS_ALL      = $0000FFFF;
  ACCESS_SYSTEM_SECURITY   = $01000000;
  MAXIMUM_ALLOWED          = $02000000;
  GENERIC_READ             = $80000000;
  GENERIC_WRITE            = $40000000;
  GENERIC_EXECUTE          = $20000000;
  GENERIC_ALL              = $10000000;

{ Registry Specific Access Rights. }
  SYNCHRONIZE = $00100000;
  KEY_QUERY_VALUE    = $0001;
  KEY_SET_VALUE      = $0002;
  KEY_CREATE_SUB_KEY = $0004;
  KEY_ENUMERATE_SUB_KEYS = $0008;
  KEY_NOTIFY         = $0010;
  KEY_CREATE_LINK    = $0020;
  KEY_READ           = (STANDARD_RIGHTS_READ or
                        KEY_QUERY_VALUE or
                        KEY_ENUMERATE_SUB_KEYS or
                        KEY_NOTIFY) and not
                        SYNCHRONIZE;
  KEY_WRITE          = (STANDARD_RIGHTS_WRITE or
                        KEY_SET_VALUE or
                        KEY_CREATE_SUB_KEY) and not
                        SYNCHRONIZE;
  KEY_EXECUTE        =  KEY_READ and not SYNCHRONIZE;
  KEY_ALL_ACCESS     = (STANDARD_RIGHTS_ALL or
                        KEY_QUERY_VALUE or
                        KEY_SET_VALUE or
                        KEY_CREATE_SUB_KEY or
                        KEY_ENUMERATE_SUB_KEYS or
                        KEY_NOTIFY or
                        KEY_CREATE_LINK) and not
                        SYNCHRONIZE;
  { Registry Predefined Value Types }

  REG_NONE                    = 0;
  REG_SZ                      = 1;
  REG_EXPAND_SZ               = 2;
  REG_BINARY                  = 3;
  REG_DWORD                   = 4;
  REG_DWORD_LITTLE_ENDIAN     = 4;
  REG_DWORD_BIG_ENDIAN        = 5;
  REG_LINK                    = 6;
  REG_MULTI_SZ                = 7;
  REG_RESOURCE_LIST           = 8;
  REG_FULL_RESOURCE_DESCRIPTOR = 9;
  REG_RESOURCE_REQUIREMENTS_LIST = 10;

var
  RegCloseKey32: function (hKey: LongInt;id:longint): Longint;
  RegOpenKeyEx32: function (hKey: LongInt; lpSubKey: PChar; ulOptions: LongInt;
    samDesired: LongInt; var phkResult: LongInt;id:longint): Longint;
  RegQueryValueEx32: function(hKey: LongInt; lpValueName: PChar; lpReserved: Pointer;
    lpType: PLongint; lpData: PByte; var lpcbData: Longint;id:longint): Longint;
  RegCreateKey32: function (hKey: LongInt; lpSubKey: Pointer; var phkResult: LongInt;id:longint): Longint;
  RegSetValueEx32: function (hKey: LongInt; lpValueName: PChar; Reserved: LongInt; dwType: Longint;
    lpData: Pointer; cbData: LongInt; id:Longint): Longint;

  idRegCloseKey32:LongInt;
  idRegOpenKeyEx32:LongInt;
  idRegQueryValueEx32:LongInt;
  idRegCreateKey32:LongInt;
  idRegSetValueEx32:LongInt;


  function RegCloseKey(hKey: LongInt): Longint;
  function RegOpenKeyEx(hKey: LongInt; lpSubKey: PChar; ulOptions: LongInt;
    samDesired: LongInt; var phkResult: LongInt): Longint;
  function RegQueryValueEx (hKey: LongInt; lpValueName: PChar; lpReserved: Pointer;
    lpType: PLongint; lpData: PByte; var lpcbData: Longint): Longint;
  function RegCreateKey(hKey: LongInt; lpSubKey: Pointer; var phkResult: LongInt): Longint;
  function RegSetValueEx(hKey: LongInt; lpValueName: PChar; Reserved: LongInt; dwType: Longint;
    lpData: Pointer; cbData: LongInt): Longint;

implementation

function RegCloseKey(hKey: LongInt): Longint;
begin
  result:=RegCloseKey32(hKey, idRegCloseKey32);
end;

function RegOpenKeyEx(hKey: LongInt; lpSubKey: PChar; ulOptions: LongInt;
  samDesired: LongInt; var phkResult: LongInt): Longint;
begin
  result:=RegOpenKeyEx32(hKey,lpSubKey,ulOptions,samDesired,phkResult,idRegopenKeyEx32);
end;

function RegQueryValueEx(hKey: LongInt; lpValueName: PChar; lpReserved: Pointer;
  lpType: PLongint; lpData: PByte; var lpcbData: Longint): Longint;
begin
  result:=RegQueryValueEx32(hKey,lpValueName,lpReserved,lpType,lpData, lpcbData, idRegQueryValueEx32);
end;

function RegCreateKey(hKey: LongInt; lpSubKey: Pointer; var phkResult: LongInt): Longint;
begin
  result:=RegCreateKey32(hKey,lpSubKey,phkResult, idRegCreateKey32);
end;

function RegSetValueEx(hKey: LongInt; lpValueName: PChar; Reserved: LongInt; dwType: Longint;
  lpData: Pointer; cbData: LongInt): Longint;
begin
  result:=RegSetValueEx32(hKey,lpValueName,Reserved,dwType,lpData,cbData, idRegSetValueEx32);
end;


initialization
  @RegOpenKeyEx32:=@Call32;
  @RegCloseKey32:=@Call32;
  @RegQueryValueEX32:=@Call32;
  @RegCreateKey32:=@Call32;
  @RegSetValueEx32:=@Call32;

  idRegCreateKey32:=Declare32('RegCreateKey', 'advapi32.dll' , 'ipp');
  idRegOpenKeyEx32:=Declare32('RegOpenKeyEx', 'advapi32.dll' , 'ipiip');
  idRegCloseKey32:=Declare32('RegCloseKey', 'advapi32.dll' , 'i');
  idRegQueryValueEx32:=Declare32('RegQueryValueEx', 'advapi32.dll' , 'ippppp');
  idRegSetValueEx32:=Declare32('RegSetValueEx', 'advapi32.dll' , 'ipiipi');
end.

