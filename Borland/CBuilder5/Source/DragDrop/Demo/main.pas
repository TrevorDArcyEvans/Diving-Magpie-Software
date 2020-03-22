unit Main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Menus, StdCtrls, ComCtrls, Dropper;

type
  TDemoForm = class(TForm)
    StatusBar: TStatusBar;
    ListBox1: TListBox;
    MainMenu: TMainMenu;
    FileMenu: TMenuItem;
    ClearItem: TMenuItem;
    N1: TMenuItem;
    ExitItem: TMenuItem;
    OptionsMenu: TMenuItem;
    AllowDirItem: TMenuItem;
    SubFolderItem: TMenuItem;
    FileDropper1: TFileDropper;
    procedure AllowDirItemClick(Sender: TObject);
    procedure OptionsMenuClick(Sender: TObject);
    procedure SubFolderItemClick(Sender: TObject);
    procedure ExitItemClick(Sender: TObject);
    procedure ClearItemClick(Sender: TObject);
    procedure FileDropper1Drop(Sender: TObject; Filename: String);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  DemoForm: TDemoForm;

implementation

{$R *.DFM}

procedure TDemoForm.AllowDirItemClick(Sender: TObject);
begin
FileDropper1.AllowDir := not FileDropper1.AllowDir;
end;

procedure TDemoForm.OptionsMenuClick(Sender: TObject);
begin
AllowDirItem.Checked := FileDropper1.AllowDir;
SubFolderItem.Checked := FileDropper1.SubFolders;
end;

procedure TDemoForm.SubFolderItemClick(Sender: TObject);
begin
FileDropper1.SubFolders := not FileDropper1.SubFolders;
end;

procedure TDemoForm.ExitItemClick(Sender: TObject);
begin
Application.Terminate;
end;

procedure TDemoForm.ClearItemClick(Sender: TObject);
begin
ListBox1.Clear;
end;

procedure TDemoForm.FileDropper1Drop(Sender: TObject; Filename: String);
begin
ListBox1.Items.Add(Filename);
end;

end.
