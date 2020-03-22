extern "C" { 

    HBITMAP _stdcall Load_JPG(char *FileName, bool ShowProgress);
    HBITMAP _stdcall Load_GIF(char *FileName, bool ShowProgress);

    BOOL _stdcall NViewLibSetLanguage(char *Lang);
    void _stdcall NViewLibSetCustomLang(char *pProgress, char *pError, char *pLoad, char *pErrLoad, char *pWarning);
    HBITMAP _stdcall NViewLibLoad(char *FileName, bool ShowProgress);
    bool _stdcall NViewLibSaveAsJPG(int Quality, char *FileName);


           }
