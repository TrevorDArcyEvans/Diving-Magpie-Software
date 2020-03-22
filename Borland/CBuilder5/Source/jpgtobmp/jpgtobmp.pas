unit JpgToBmp;
{-----------------------------------------------------------------------------}
{ TJpgToBmp v 1.2                                                             }
{ Copyright 1998,1999, Eric Pedrazzi.  All Rights Reserved.                   }
{-----------------------------------------------------------------------------}
{ A component to translate a jpeg (timage or file) into a bitmap file         }
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
{   http://www.chez.com/epedrazzi                                             }
{ See JpgToBmp.txt for notes, known issues, and revision history.             }
{-----------------------------------------------------------------------------}
{ Date last modified:  April 1999                                             }
{-----------------------------------------------------------------------------}
{ v1.0 : Initial release                                                      }
{ v1.1 : bug reported by Myke Mudford (whariti@manawatu.gen.nz)               }
{        "The color goes funny" bug seems to be corrected                     }
{ v1.2 : Rename of the methods
{        Add Image property
{        Add CopyImageToBmp method
{
{                                                                             }
{-----------------------------------------------------------------------------}

{ This unit provides an invisible component to perform a copy of a bitmap file
  to a jpeg file.

  Properties
  ----------
  Image    : Source Image (TImage)
  JpegFile : Source file in Jpeg format
  BmpFile  : Destination File in bitmap format

  Methods
  -------
  CopyJpgToBmp   : Start jpg file to bmp file translation
  CopyImageToBmp : Start image to bmp file translation

}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs, Jpeg, ExtCtrls;

type
  TJpegToBmp = class(TComponent)
  private
    { Déclarations privées }
    FImage : TImage;
    FStreamBmp, FStreamJpg  : TStream;
    FJpeg    : TJpegImage;
    FBmp     : TBitmap;
    FBmpFile : AnsiString;
    FJpegFile: AnsiString;
  protected
    { Déclarations protégées }
    procedure FCopyJpegToBmp;
    procedure FCopyImageToBmp;
  public
    { Déclarations publiques }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure CopyJpegToBmp;
    procedure CopyImageToBmp;
  published
    { Déclarations publiées }
    property Image : TImage read FImage write FImage;
    property BmpFile : AnsiString read FBmpFile write FBmpFile;
    property JpegFile: AnsiString read FJpegFile write FJpegFile;
  end;

procedure Register;

implementation

procedure TJpegToBmp.FCopyImageToBmp;
begin
  FStreamBmp := TFileStream.Create(FBmpFile,fmCreate);

  try
    FJpeg.Assign(FImage.Picture);

    if FJpeg.PixelFormat = jf24bit then
      FBmp.PixelFormat := pf24bit
    else
      FBmp.PixelFormat := pf8bit;

    FBmp.Width := FJpeg.Width;
    FBmp.Height := FJpeg.Height;
    FBmp.Canvas.Draw(0,0,FJpeg);
    FBmp.SaveToStream(FStreamBmp);
  finally
    FStreamBmp.Free;
  end;
end;

procedure TJpegToBmp.FCopyJpegToBmp;
begin
  if FileExists(FBmpFile) then DeleteFile(FBmpFile);
  FStreamBmp := TFileStream.Create(FBmpFile,fmCreate);
  FStreamJpg := TFileStream.Create(FJpegFile, fmOpenRead);

  try
    if FJpeg.PixelFormat = jf24bit then
      FBmp.PixelFormat := pf24bit
    else
      FBmp.PixelFormat := pf8bit;

    FJpeg.LoadFromStream(FStreamJpg);

    FBmp.Width := FJpeg.Width;
    FBmp.Height := FJpeg.Height;
    FBmp.Canvas.Draw(0,0,FJpeg);
    FBmp.SaveToStream(FStreamBmp);
  finally
    FStreamJpg.Free;
    FStreamBmp.Free;
  end;
end;

constructor TJpegToBmp.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FJpeg := TJpegImage.Create;
  FBmp  := TBitmap.Create;
end;

destructor TJpegToBmp.Destroy;
begin
  FJpeg.Free;
  FBmp.Free;
  inherited Destroy;
end;

procedure TJpegToBmp.CopyImageToBmp;
begin
  FCopyImageToBmp;
end;

procedure TJpegToBmp.CopyJpegToBmp;
begin
  FCopyJpegToBmp;
end;

procedure Register;
begin
  RegisterComponents('Samples', [TJpegToBmp]);
end;

end.
