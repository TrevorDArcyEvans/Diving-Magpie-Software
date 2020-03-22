{
JustOne v1.2
(32 bit version)
By: Steven L. Keyser
March 17, 1996
CompuServe Address:	71214,3117
e-mail							71214.3117@compuserve.com

Purpose:  JustOne is a Delphi component which allows the developer of an
application to easily limit the number of that app's instances to just one.
When a user attempts to start a second instance of the application, JustOne
checks for the existence of a previous instance.  If one is found, JustOne
brings the first instance to the front and stops the second instance from
fully launching.  If the first instance was minimized to an icon, it is
'RESTORED' to its previous

Version 1.2	- This is the first release of the 32 bit version of JustOne.
(3/17/96)			While this version is functionally equivalent to the 16 bit
							version, the code is significantly different as earlier versions
              relied on Windows 3.1 features not supported in WIN95.

Version 1.1 -	16 bit version...
(1/14/96)			- Added the 'About' property
							- Eliminated the AllowMultInst property
              - Eliminated the Execute property
              - Added help file
              - Added keyword file

Version 1.0 -	16 bit version... Original release
(Oct '95)

Comments:			This source code includes the support of an 'About' box
							appearing as a property on the JustOne component in design mode.
              To see how to add 'About' properties to your own components,
              perform a search on this file for the word 'about', then utilze
              those sections and concepts in your own work.

}
unit Just1_32;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  Dialogs{, DsgnIntf};

type
  TJustOne32 = class(TComponent)
  private
    FAbout:	string;
  public
    constructor Create(AOwner:TComponent); override;
    destructor Destroy; override;
    procedure ShowAbout;
  published
    property About: string read FAbout write FAbout stored False;
  end;

type
	TPreviousInstance = class(TObject)
  private
		FAppName: string;
    FMutexHandle: THandle;
    FhPrevInst: boolean;
    function GetAppName: string;
    procedure SetAppName(filename: string);
  public
    property AppName: string read GetAppName write SetAppName;
    property MutexHandle: THandle read FMutexHandle write FMutexHandle;
    property hPrevInst: boolean read FhPrevInst write FhPrevInst;
   	procedure SethPrevInst;
  end;

procedure Register;

implementation
var
	PreviousInstance1: TPreviousInstance;

{########################################################################}
function TPreviousInstance.GetAppName: string;
begin
  GetAppName := FAppName;
end;
{########################################################################}
procedure TPreviousInstance.SetAppName(filename: string);
begin
	{check to see if the filename includes the '.exe' extension}
  if Pos('.EXE', filename) > 0 then
  	{delete the extension and reset the AppName field}
   	FAppName := Copy(filename, 1, (Length(filename) - 4));

end;
{########################################################################}
{$IFDEF BCB4}
type
  TAboutProperty = class(TPropertyEditor)
  public
    procedure Edit; override;
    function GetAttributes: TPropertyAttributes; override;
    function GetValue:string; override;
  end;
{$ENDIF}
{#############################################################################}
procedure Register;
begin
	{JustOne will appear on a new component palette page called 'SLicK'.  If
  you want it on a different page, replace 'SLicK' below with the page name
  of your choice.}
  RegisterComponents('Samples', [TJustOne32]);
  {register the 'About' property editor}
  {$IFDEF BCB4}
  RegisterPropertyEditor(TypeInfo(String), TJustOne32, 'About',
  	TAboutProperty);
  {$ENDIF}
end;

{#############################################################################}
procedure TPreviousInstance.SethPrevInst;
var
 	zAppName: array[0..260] of char;
begin
	{get the filename of the current program}
 	StrPCopy(zAppName, ExtractFileName(ParamStr(0)));
  {save the filename for future use}
  PreviousInstance1.AppName := StrPas(zAppName);
  {see if the named mutex object existed before this call}
 	MutexHandle := CreateMutex(nil, TRUE, zAppName);
 	if MutexHandle <> 0 then
  	begin
    if GetLastError = ERROR_ALREADY_EXISTS then
    	{set hPrevInst property and close the mutex handle}
      begin
	      hPrevInst := TRUE;
  	    CloseHandle(MutexHandle);
      end
   	else
    	{indicate no previous instance was found}
     	hPrevInst := FALSE;
   	end
  else
   	{indicate no previous instance was found}
 		hPrevInst := FALSE;
end;
{########################################################################}
constructor TJustOne32.Create(AOwner:TComponent);
var
  PrevInstHandle: THandle;
  zAppName : array[0..260] of char;
begin
	inherited Create(AOwner);

	if PreviousInstance1.hPrevInst = TRUE then
    begin
      {convert the Pascal string filename into a null terminated string}
      StrPCopy(zAppName, PreviousInstance1.AppName);
      {find the current window's handle}
			PrevInstHandle := FindWindow(nil, zAppName);
      {change the current window's name to something else (literally)<g>}
      SetWindowText(PrevInsthandle, 'something else');
      {now, we can find the previous window's handle (the one we really want!)}
			PrevInstHandle := FindWindow(nil, zAppName);
      {bring the first instance to the front}
      if PrevInstHandle <> 0 then
  			begin
        	if IsIconic(PrevInstHandle) then
          	ShowWindow(PrevInstHandle,SW_RESTORE)
          else
          	BringWindowToTop(PrevInstHandle);
        end;
      {terminate execution of the second instance}
      halt;
    end;

end;
{########################################################################}
destructor TJustOne32.Destroy;
begin
  inherited Destroy;
end;
{########################################################################}
{$IFDEF BCB4}
procedure TAboutProperty.Edit;
{call the 'About' dialog window when clicking on ... in the Object Inspector}
begin
  TJustOne32(GetComponent(0)).ShowAbout;
end;

{########################################################################}
function TAboutProperty.GetAttributes: TPropertyAttributes;
{set up to display a string in the Object Inspector}
begin
  GetAttributes := [paDialog, paReadOnly];
end;

{########################################################################}
function TAboutProperty.GetValue: String;
{set string to appear in the Object Inspector}
begin
  GetValue := '(About)';
end;
{$ENDIF}

{########################################################################}
procedure TJustOne32.ShowAbout;
var
	msg: string;
const
  cr = chr(13);
begin
  msg := 'JustOne  v1.2' + cr + 'A Freeware component' + cr;
  msg := msg + '(32 bit version)' + cr + cr;
  msg := msg + 'Copyright © 1995, 1996 Steven L. Keyser' + cr;
  msg := msg + 'e-mail 71214.3117@compuserve.com' + cr;
  ShowMessage(msg);
end;
{########################################################################}
initialization
	PreviousInstance1 := TPreviousInstance.Create;
  PreviousInstance1.SethPrevInst;
{#############################################################################}
finalization
	CloseHandle(PreviousInstance1.MutexHandle);
{########################################################################}
end.




