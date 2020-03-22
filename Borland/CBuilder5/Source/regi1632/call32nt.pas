Unit Call32nt;
{Delphi/TPW/BPW Unit to call 32-bit functions from 16 bit programs}
{Written in Turbo Pascal for Windows 1.5 /Delphi}
{By Christian Ghisler, CIS: 100332,1175         }
{Released to the public domain on June 14,1995  }

{$W-}
{No Windows Stack frame!}
{$R-}
{No range checking!}

{
Translation by Christian Ghisler, from:
//----------------------------------------------------------
// CALL32.C
//
// This creates a DLL for 16-bit Visual Basic programs to
// call 32-bit DLLs on Windows NT 3.1.  It uses the 
// Generic Thunks feature of the WOW subsystem on Windows
// NT to load and call 32 bit DLLs.  This file should
// be compile into a 16-bit DLL.
//
// Writted by Peter Golde.
//----------------------------------------------------------
}
interface

uses wintypes,
     winprocs,
     {$ifdef ver80}sysutils {$else} strings {$endif};

const Call32NTError:boolean=false;

type tPROC32ENTRY=record
    hinst:longint;      { 32-bit instance handle of library                  }
    lpfunc:tfarproc;    { 32-bit function address of function                }
    dwAddrXlat,         { bit mask of params: 1 indicates arg is address     }
    dwHwndXlat,         { bit mask of params: 1 indicates arg is 16-bit hwnd }
    nParams:longint;    { number of parameters                               }
  end;
  pPROC32ENTRY=^tPROC32ENTRY;
  tPROC32LIST=array[0..0] of tPROC32ENTRY;
  pPROC32LIST=^tPROC32LIST;

{ rgProc32Entry points to an array of PROC32ENTRY functions, which
  is grown as needed.  The value returned by Declare32 is an
  index into this array.}
const
  cRegistered:integer=0;          { number of registered functions. }
  cAlloc:integer=0;               { number of alloced PROC32ENTRY structures. }
  rgPROC32ENTRY:pPROC32LIST=nil;  { array of PROC32ENTRY structures. }
  CALLOCGROW=10;                  { number of entries to grow rgProc32Entry by}
  rgProc32handle:thandle=0;       { Handle auf globalen Speicherbereich für rgProc32Entry }

{ These are the addresses of the Generic Thunk functions in 
  the WOW KERNEL.}  
  fGotProcs:bool=FALSE;        { Did we successfully get the addresses? }

var
  Callproc32W:function (address:pointer;n,c:longint):longint;
  FreeLibrary32W:function(handle:longint):bool;
  GetProcAddress32W:function(module:longint;funcname:pchar):pointer;
  LoadLibraryEx32W:function(libname:pchar;a,b:longint):longint;
  lpvGetLastError:function:pchar;
  lpvGetCapture:pointer;

procedure Call32(iProc:longint);
function Declare32(lpstrName,lpstrLib,lpstrArg:pchar):longint;
function GetVDMPointer32W(name:pchar;Length:word):longint;    {Get 32-bit pointer from 16-bit pointer and length}

implementation



{/-----------------------------------------------------
// XlatHwnd
//   Translates a 16-bit HWND into a 32-bit HWND.
//   The HWND must be one in our 16-bit process.
//   NULL is translated to NULL and doesn't cause
//   and error.
//
//   Unfortunately, WOW does not export a function
//   for doing this, so our procedure is as follows:
//   We do 16-bit SetCapture call to the window
//   to set the capture, and then a 32-bit GetCapture
//   call to get the 32-bit equivalent handle.  The
//   capture is then restored to what it was beforehand.
//
//   May cause VB runtime error, and hence never return.
//-----------------------------------------------------}
procedure XlatHwnd(var phwnd:longint);
var hwnd16,
    hwndCapturePrev:word;
    hwnd32,
    hinstUser:longint;

begin
  hwnd16:=LOWORD(phwnd);         { 16-bit hwnd }

  { Check for valid 16-bit handle. }  
  if (phwnd<>word(hwnd16)) then exit; 
  if (hwnd16<>0) and not IsWindow(hwnd16) then exit;

  { Get Address of 32-bit GetCapture }
  if (@lpvGetCapture=nil) then begin
    hinstUser:=LoadLibraryEx32W('user32', 0, 0);
    if (hinstUser<>0) then begin
      lpvGetCapture:=GetProcAddress32W(hinstUser, 'GetCapture');
      FreeLibrary32W(hinstUser);
    end;
    if (@lpvGetCapture=nil) then exit;
  end;

  
  {/ Set capture to window, get capture to get 32-bit handle. 
  // Be sure to restore capture afterward.
  // NULL isn't translated }
  
  if (hwnd16<>0) then begin
    hwndCapturePrev:=SetCapture(hwnd16);
    hwnd32:=CallProc32W(lpvGetCapture,0,0);
    if (hwndCapturePrev<>0) then
      SetCapture(hwndCapturePrev)
    else
      ReleaseCapture;
    if (hwnd32=0) then exit;
  end;

  phwnd:=hwnd32;
end;

{/-----------------------------------------------------
// MungeArgs
//   Modify the args array so it can be passed to
//   to CallProc32W.  This uses the PROC32ENTRY structure
//   to set up the arg list correctly on the stack
//   so CallProc32W can be call.  HWND translation is
//   performed.  The frame is changed as follows:
//           In:                 Out:
//            unused              number of params
//   dwArgs-> unused              address xlat mask
//            PROC32ENTRY index   32-bit function address.
//            argument            argument, possible HWND xlated
//            argument            argument, possible HWND xlated
//            ...                 ...
//-----------------------------------------------------}
type plongint=^longint;
     pfarproc=^tfarproc;

procedure MungeArgs(dwArgs:longint);
var pentry:pPROC32ENTRY;
    iArg:integer;
    dwHwndXlat:longint;

begin
  pentry:=@rgProc32Entry^[plongint(dwArgs+4)^];
  iArg:=2;

  plongint(dwArgs-4)^:=pentry^.nParams;
  plongint(dwArgs)^:=pentry^.dwAddrXlat;
  pfarproc(dwArgs+4)^:=pentry^.lpfunc;
  dwHwndXlat:=pentry^.dwHwndXlat;
  while (dwHwndXlat<>0) do begin
    if (dwHwndXlat and 1)<>0 then
    XlatHwnd(plongint(dwArgs+4*iArg)^);
    inc(iArg);
    dwHwndXlat:=dwHwndXlat shr 1;
  end;
end;

{/-----------------------------------------------------
// Call32
//   This function is called by applications directly.
//   Arguments to the function are also on the stack 
//   (iProc is the PROC32ENTRY index).  We correctly
//   set up the stack frame, then JUMP to CallProc32W,
//   which eventually returns to the user.
//-----------------------------------------------------}

var dest:tfarproc;          {Destination for jump back!}
var addit:word;             {value to add to sp to restore stack pointer}
var _sp,_bp:word;

procedure Call32(iProc:longint);
begin
  if iProc<0 then begin      {Procedure is invalid -> stop execution!}
    if messagebox(0,'Error calling 32 bit function, continue?','Call32',
      mb_yesno or mb_iconquestion)=idno then halt(1);
    addit:=(-iProc) shl 2;  {4 more for id!}
    asm
      mov sp,bp
      pop bp
      pop di
      mov word(dest),di
      pop di
      mov word(dest+2),di
      add sp,addit
      xor ax,ax             {return 0}
      xor dx,dx
      jmp dest
    end;
  end;

  asm                       { here comes the thunking call! }
    pop     bp              { restore BP }
    mov     bx, sp          { bx = sp on entry }
    sub     sp, 8           { 2 additional words }
    mov     ax, ss:[bx]     { ax = return address offst }
    mov     dx, ss:[bx+2]   { dx = return address segment }
    mov     ss:[bx-8], ax
    mov     ss:[bx-6], dx
    push    ds              { Save our DS }
    push    ss
    push    bx              { Push pointer to args }
    call    MungeArgs       { Munge the args }
    pop     es              { es is our DS }
    jmp    CallProc32W      { Jump to the call thunker }
  end;
end;
  
{/-----------------------------------------------------
// Declare32
//   This function is called directly from VB.
//   It allocates and fills in a PROC32ENTRY structure
//   so that we can call the 32 bit function.
//-----------------------------------------------------}
function Declare32(lpstrName,lpstrLib,lpstrArg:pchar):longint;
var
  hinst:longint;                   { 32-bit DLL instance handle }
  lpfunc:pointer;                  { 32-bit function pointer    }
  dwAddrXlat,                      { address xlat mask          }
  dwHwndXlat,                      { hwnd xlat mask             }
  nParams:longint;                 { number of params           }
  szBuffer:array[0..127] of char;  { scratch buffer             }
  hinstKernel:word;                { Instance handle of WOW KERNEL.DLL }
  hinstKernel32:longint;           { Instance handle of Win32 KERNEL32.DLL }
  rg:record
    lpstrName:pchar;
    nparams:longint;
  end;
  olderror:boolean;                { Was there an error before?}

begin
  olderror:=Call32NTError;
  Call32NTError:=true;
  Declare32:=-1-lstrlen(lpstrArg);
  if not fGotProcs then begin
    hinstKernel:=LoadLibrary('KERNEL');
    if (hinstKernel < 32) then exit;

    @CallProc32W:=GetProcAddress(hinstKernel, 'CALLPROC32W');
    @FreeLibrary32W:=GetProcAddress(hinstKernel, 'FREELIBRARY32W');
    @LoadLibraryEx32W:=GetProcAddress(hinstKernel, 'LOADLIBRARYEX32W');
    @GetProcAddress32W:=GetProcAddress(hinstKernel, 'GETPROCADDRESS32W');
    FreeLibrary(hinstKernel);

    if (@LoadLibraryEx32W<>nil) and (@GetProcAddress32W<>nil) and (@FreeLibrary32W<>nil) then begin
      hinstKernel32:=LoadLibraryEx32W('kernel32', 0, 0);
      @lpvGetLastError:=GetProcAddress32W(hinstKernel32, 'GetLastError');
      FreeLibrary32W(hinstKernel);
    end;

    if (@CallProc32W=nil) or (@FreeLibrary32W=nil) or (@LoadLibraryEx32W=nil) or
       (@GetProcAddress32W=nil) or (@lpvGetLastError=nil) then begin
      exit;
    end;
    fGotProcs:=TRUE;
  end;  

  { If needed, allocate a PROC32ENTRY structure }
  if (cRegistered = cAlloc) then begin
    if (rgProc32Entry<>nil) then begin
      globalunlock(rgProc32handle);
      rgProc32handle:=GlobalReAlloc(rgProc32handle,
                       (cAlloc + CALLOCGROW) * sizeof(tPROC32ENTRY), GMEM_MOVEABLE);
      rgProc32Entry:=Globallock(rgProc32handle);
    end else begin
      rgProc32handle:=GlobalAlloc(GMEM_MOVEABLE, CALLOCGROW * sizeof(tPROC32ENTRY));
      rgProc32Entry:=Globallock(rgProc32handle);
    end;
    if (rgProc32Entry=nil) then exit;
    inc(cAlloc,CALLOCGROW);
  end;
  
  {/ Process the arg list descriptor string to 
  // get the hwnd and addr translation masks, and the
  // number of args. }

  dwAddrXlat:=0;
  dwHwndXlat:=0;
  nParams:=lstrlen(lpstrArg);
  if (nParams > 32) then exit;  {Too many parameters}

  while (lpstrArg[0]<>#0) do begin
    dwAddrXlat:=dwAddrXlat shl 1;
    dwHwndXlat:=dwHwndXlat shl 1;
    case lpstrArg[0] of
      'p':dwAddrXlat:=dwAddrXlat or 1;
      'i': ;
      'w':dwHwndXlat:=dwHwndXlat or 1;
    else
      exit;
    end;
    inc(lpstrArg);
  end;

  {/ Load the 32-bit library. } 
  hinst:=LoadLibraryEx32W(lpstrLib, 0, 0);
  if (hinst=0) then begin
    exit;
  end;
  
  {/ Get the 32-bit function address.  Try the following three
  // variations of the name (example: NAME):
  //    NAME
  //    _NAME@nn     (stdcall naming convention: nn is bytes of args)
  //    NAMEA        (Win32 ANSI function naming convention) }
  lpfunc:=GetProcAddress32W(hinst, lpstrName);
  if (lpfunc=nil) and (lstrlen(lpstrName) < 122) then begin
    { Change to stdcall naming convention. }
    rg.lpstrName:=lpstrName;
    rg.nparams:=nParams * 4;
    wvsprintf(szBuffer, '_%s@%d', rg);
    lpfunc:=GetProcAddress32W(hinst, szBuffer);
  end;  
  if (lpfunc=nil) and (lstrlen(lpstrName) < 126) then begin
    { Add suffix "A" for ansi }
    strcopy(szBuffer, lpstrName);
    strcat(szBuffer, 'A');
    lpfunc:=GetProcAddress32W(hinst, szBuffer);
  end;
  if (lpfunc=nil) then begin
    FreeLibrary32W(hinst);
    exit;
  end;
  
  {/ Fill in PROC32ENTRY struct and return index. }
  rgProc32Entry^[cRegistered].hinst:=hinst;
  rgProc32Entry^[cRegistered].lpfunc:=lpfunc;
  rgProc32Entry^[cRegistered].dwAddrXlat:=dwAddrXlat;
  rgProc32Entry^[cRegistered].dwHwndXlat:=dwHwndXlat;
  rgProc32Entry^[cRegistered].nParams:=nParams;
  Declare32:=cRegistered;
  inc(cRegistered);
  Call32NTError:=olderror;  {If there was no error, set Call32NTErrorOccurred to false}
end;

function GetVDMPointer32W(name:pchar;Length:word):longint;
var lpGetVDMPointer32W:function(name:pchar;UINT:word):longint;
begin
  @lpGetVDMPointer32W:=getProcAddress(GetModuleHandle('kernel'),'GetVDMPointer32W');
  if @lpGetVDMPointer32W<>nil then
    GetVDMPointer32W:=lpGetVDMPointer32W(name,Length)
  else
    GetVDMPointer32W:=0;
end;

{/-----------------------------------------------------
// WEP
//   Called when DLL is unloaded.  We free all the
//   32-bit DLLs we were using and clear the
//   PROC32ENTRY list.
//-----------------------------------------------------}
var exitsave:tfarproc;

procedure cleanuplibs; far;
begin
  Exitproc:=Exitsave;
  dec(cRegistered);
  while (cRegistered >= 0) do begin 
    FreeLibrary32W(rgProc32Entry^[cRegistered].hinst);
    dec(cregistered);
  end;
  if (rgProc32Entry<>nil) then begin
    globalunlock(rgProc32handle);
    GlobalFree(rgProc32handle);
  end;
  rgProc32Entry:=NIL;
  rgProc32handle:=0;
  cRegistered:=0;
  cAlloc:=0;
end;

initialization
  @Callproc32W:=nil;
  @FreeLibrary32W:=nil;
  @GetProcAddress32W:=nil;
  @LoadLibraryEx32W:=nil;
  @lpvGetLastError:=nil;
  lpvGetCapture:=nil;
  exitsave:=exitproc;      
  exitproc:=@cleanuplibs;
end.
