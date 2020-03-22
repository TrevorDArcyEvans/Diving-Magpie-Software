//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <dir.h>
#include "ZipBrowse.h"
USERC("ZipMsgUS.rc");
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "zipbuilder"
#pragma resource "*.dfm"
TfrmUnzip *frmUnzip;
//---------------------------------------------------------------------------
__fastcall TfrmUnzip::TfrmUnzip(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmUnzip::DriveComboBoxChange(TObject *Sender)
{
DirListBox->Drive = DriveComboBox->Drive;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUnzip::chkOpenClick(TObject *Sender)
{
lbxFileList->Enabled = chkOpen->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUnzip::btnOKClick(TObject *Sender)
{
ZipBuilder->ExtrBaseDir = DirListBox->Directory;

if (true == m_bDirStruct)
    {
    ZipBuilder->ExtrOptions <<  ExtrDirNames;
    }

ZipBuilder->Extract();

if (true == chkOpen->Checked       &&
    -1   != lbxFileList->ItemIndex )
    {
    if (true == m_bDirStruct)
        {
        // prepend extraction dir to selected file
        m_strFileNameToOpen = DirListBox->Directory + ::String("\\") +
                                lbxFileList->Items->Strings[lbxFileList->ItemIndex];
        }
    else
        {
        // discard directory/path from original file
        m_strFileNameToOpen = lbxFileList->Items->Strings[lbxFileList->ItemIndex];

        char    drive   [MAXDRIVE   ],
                dir     [MAXDIR     ],
                file    [MAXFILE    ],
                ext     [MAXEXT     ];

        fnsplit(m_strFileNameToOpen.c_str(), drive, dir, file, ext);

        m_strFileNameToOpen = DirListBox->Directory + ::String("\\") +
                                ::String(file) +
                                ::String(ext);
        }
    }
else
    {
    m_strFileNameToOpen = NULL;
    }

Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUnzip::FormCreate(TObject *Sender)
{
// The easiest way to handle DLL loading and unloading is to load them in
// the form's OnCreate event handler, and unload them in the form's
// OnDestroy event handler.
ZipBuilder->Load_Zip_Dll();
ZipBuilder->Load_Unz_Dll();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUnzip::FormDestroy(TObject *Sender)
{
ZipBuilder->Unload_Zip_Dll();
ZipBuilder->Unload_Unz_Dll();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUnzip::FormShow(TObject *Sender)
{
ZipBuilder->ZipFileName = m_strZipFileName;
ZipBuilder->List();

lbxFileList->Items->Clear();

ZipDirEntry   *pZipDirEntry;
for (int i = 0; i < ZipBuilder->ZipContents->Count; i++)
    {
    pZipDirEntry = (ZipDirEntry *) ZipBuilder->ZipContents->Items[i];
    lbxFileList->Items->Add(pZipDirEntry->FileName);
    }
}
//---------------------------------------------------------------------------

