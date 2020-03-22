//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <SvcMgr.hpp>
#pragma hdrstop
#define Application Svcmgr::Application
USERES("UnfragWorksSrvc.res");
USEFORM("unfrag.cpp", UnfragWorks); /* TService: DesignClass */
USEUNIT("utils.cpp");
USEUNIT("crc_32.cpp");
USEFORM("about.cpp", frmAbout);
USEFORM("config.cpp", frmConfig);
USEUNIT("UnfragFile.cpp");
USEUNIT("SWutils.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
        // TDE have to do something here for Gold version
        #ifdef UWSV_GOLD
        Application->Title = "UnfragWorks Server Gold";
        #else
        Application->Title = "UnfragWorks Server";
        #endif
        Application->CreateForm(__classid(TUnfragWorks), &UnfragWorks);
        Application->CreateForm(__classid(TfrmAbout), &frmAbout);
        Application->CreateForm(__classid(TfrmConfig), &frmConfig);
        Application->Run();
    }
    catch (Exception &exception)
    {
		Sysutils::ShowException(&exception, Sysutils::ExceptAddr());
    }
    return 0;
}
//---------------------------------------------------------------------------

