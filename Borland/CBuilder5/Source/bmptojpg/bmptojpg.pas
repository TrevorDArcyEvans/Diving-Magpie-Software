unit BmpToJpg;
{-----------------------------------------------------------------------------}
{ TBmpToJpeg v 1.1                                                            }
{ Copyright 1998,1999, Eric Pedrazzi.  All Rights Reserved.                   }
{-----------------------------------------------------------------------------}
{ A component to translate a bitmap (file or Timage) into a jpeg file         }
{                                                                             }
{ This component can be freely used and distributed in commercial and private }
{ environments, provied this notice is not modified in any way and there is   }
{ no charge for it other than nomial handling fees.  Contact me directly for  }
{ modifications to this agreement.                                            }
{                                                                             }
{-----------------------------------------------------------------------------}
{ Feel free to contact me if you have any questions, comments or suggestions  }
{ at epedrazzi@chez.com                                                       }
{ The latest version will always be available on the web at:                  }
{          http://www.chez.com/epedrazzi                                      }
{ See BmpToJpg.txt for notes, known issues, and revision history.             }
{-----------------------------------------------------------------------------}
{ Date last modified:  April 1999                                             }
{-----------------------------------------------------------------------------}
{ v1.0 : Initial release                                                      }
{ v1.1 : Rename of the methods                                                }
{        Add Image property                                                   }
{        Add CopyImageToJpeg method                                           }
{-----------------------------------------------------------------------------}

{ This unit provides an invisible component to perform a copy of a Timage or a bitmap file
  to a jpeg file.

  Properties
  ----------
  Image    : Source Image (Timage)
  BmpFile  : Source File in bitmap format
  JpegFile : Destination file in Jpeg format

  Methods
  -------
  CopyBmpToJpeg : Start bmp file to jpg file translation
  CopyImageToJpeg : Start image to jpg file translation
}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs, Jpeg, ExtCtrls;

type
  TBmpToJpeg = class(TComponent)
  private
    { Déclarations privées }
    FStream  : TStream;
    FImage   : TImage;
    FJpeg    : TJpegImage;
    FBmp     : TPicture;
    FBmpFile : AnsiString;
    FJpegFile: AnsiString;
  protected
    { Déclarations protégées }
    procedure FCopyBmpToJpeg;
    procedure FCopyImageToJpeg;
  public
    { Déclarations publiques }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure CopyBmpToJpeg;
    procedure CopyImageToJpeg;
  published
    { Déclarations publiées }
    property Image : TImage read FImage write FImage;
    property BmpFile  : AnsiString read FBmpFile write FBmpFile;
    property JpegFile : AnsiString read FJpegFile write FJpegFile;
  end;

procedure Register;

implementation

procedure TBmpToJpeg.FCopyBmpToJpeg;
begin
  if FileExists(FJpegFile) then DeleteFile(FJpegFile);
  FStream := TFileStream.Create(FJpegFile,fmCreate);
  try
    FBmp.LoadFromFile(FBmpFile);
    FJpeg.Assign(FBmp.Bitmap);
    FJpeg.SaveToStream(FStream);
  finally
    FStream.Free;
  end;
end;

procedure TBmpToJpeg.FCopyImageToJpeg;
begin
  FStream := TFileStream.Create(FJpegFile,fmCreate);
  try
    FJpeg.Assign(FImage.Picture.Bitmap);
    FJpeg.SaveToStream(FStream);
  finally
    FStream.Free;
  end;
end;

constructor TBmpToJpeg.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FJpeg := TJpegImage.Create;
  FBmp  := TPicture.Create;
end;

destructor TBmpToJpeg.Destroy;
begin
  FJpeg.Free;
  FBmp.Free;
  inherited Destroy;
end;

procedure TBmpToJpeg.CopyBmpToJpeg;
begin
  FCopyBmpToJpeg;
end;

procedure TBmpToJpeg.CopyImageToJpeg;
begin
  FCopyImageToJpeg;
end;

procedure Register;
begin
  RegisterComponents('Samples', [TBmpToJpeg]);
end;

end.
