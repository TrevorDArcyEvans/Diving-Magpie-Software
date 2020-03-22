unit DragDrop;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls,
  Forms,ShellApi;


type
  TFilesDropped = Procedure(NumItems:Integer) of Object;
  TDragDrop = class(TComponent)
  private

    //Define Event
    FFilesDropped:TFilesDropped;

    //Proc Pointers
    OldWndProc : TFarProc;
    NewWndProc : Pointer;

    //Field Variables
    FList:TStringList; // Store dropped files
    FBTF:Boolean; // Bring to front?
    FActive:Boolean; // Accept drops at all?

    procedure HookParent;
    procedure UnhookParent;
    procedure HookWndProc(var Message: TMessage);

    procedure SetActive(YesNo:Boolean);
  protected
    { Protected declarations }
  public
    constructor Create(AOwner:TComponent); override;
    destructor  Destroy; override;
    property DroppedFiles:TStringList Read FList;
  published
    procedure ClearList;

    property Active:Boolean Read FActive Write SetActive;
    property BringToFront:Boolean Read FBTF Write FBTF;


    property OnFilesDropped:TFilesDropped Read FFilesDropped Write FFilesDropped;
  end;

procedure Register;

implementation

constructor TDragDrop.Create(AOwner:TComponent);
Begin
     Inherited Create(AOwner);

     NewWndProc := Nil;
     OldWndProc := Nil;

     FList := TStringList.Create;
     FBTF  := False;

     If ComponentState<>[csDesigning] Then
     Begin
          HookParent;
          SetActive(FActive); //Activate (or don't) the capturing of WM_DROPFILES
     End;
End;

destructor TDragDrop.Destroy;
begin
     UnhookParent;
     FList.Free;

     inherited Destroy;  // Call TComponent's default destroy meathod
end;

procedure TDragDrop.HookParent;
begin
     // Exit if parent doesn't exist
     if (Owner As TWinControl) = NIL then exit;

     //Install Hook
     OldWndProc := TFarProc(GetWindowLong((Owner As TWinControl).Handle, GWL_WNDPROC));
     NewWndProc := MakeObjectInstance(HookWndProc);
     SetWindowLong((Owner As TWinControl).Handle, GWL_WNDPROC, LongInt(NewWndProc));
end;


procedure TDragDrop.UnhookParent;
begin
     if ( (Owner As TWinControl)<> NIL) And (Assigned(OldWndProc) ) then
        SetWindowLong((Owner As TWinControl).Handle, GWL_WNDPROC, LongInt(OldWndProc));
     if assigned(NewWndProc) then
        FreeObjectInstance(NewWndProc);

     NewWndProc := NIL;
     OldWndProc := NIL;
end;

procedure TDragDrop.HookWndProc(var Message: TMessage);
  var I,nl,nFiles:Integer;
      fName:Array[1..255] of Char;
begin
     if (Owner As TWinControl) = NIL then
        Exit;

     With Message Do
     Begin
          Result := CallWindowProc(OldWndProc, (Owner As TWinControl).Handle, Msg, wParam, lParam);

          If (Msg = WM_DROPFILES) Then
          Begin
               If FBTF Then
                  SetForegroundWindow((Owner As TWinControl).Handle);


               //Clear the internal list
               FList.Clear;

               //Using -1 in the index gives me the number of files
               nFiles := DragQueryFile(wParam, $FFFFFFFF, Nil, 0);
               For i:=0 to nFiles-1 do
               Begin
                    //DragQueryFile returns the length of the given file
                    nl := DragQueryFile(wParam,i,@fName,255)+1;

                    //Append a character zero to make null-terminated string
                    fName[nl] := #0;

                    //Add the item
                    FList.Add(fName);
               End;
               If ((nFiles>0) And (Assigned(FFilesDropped))) Then
                  FFilesDropped(nFiles);
          End;
     End;
end;

procedure TDragDrop.ClearList;
Begin
     Try
        FList.Clear;
     Except
     End;
End;

procedure TDragDrop.SetActive(YesNo:Boolean);
Begin

     //Set Private field
     FActive := YesNo;

     If ComponentState=[csDesigning] Then
        Exit; //Don't hook to window at design time!

     If FActive Then
        DragAcceptFiles((Owner As TWinControl).Handle,True)
     Else
        DragAcceptFiles((Owner As TWinControl).Handle,False);
End;

procedure Register;
begin
  RegisterComponents('Samples', [TDragDrop]);
end;

end.
