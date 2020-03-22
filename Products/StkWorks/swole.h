//---------------------------------------------------------------------------
#ifndef swOleH
#define swOleH
//---------------------------------------------------------------------------
#if 0
//#include <vcl\sysdefs.h>
#include <system.hpp>

//#include <OleAuto.hpp>
#include <Comobj.hpp>
#include <memory>     //for STL auto_ptr
#include <stdio.h>
#include <dir.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <except.h> //for xmsg
#include <cstring.h>

#include <utilcls.h>
#endif

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>

#include <utilcls.h>

//#include <Comobj.hpp>
#include <vcl\Menus.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <Regi1632.hpp>
#include <memory>     //for STL auto_ptr
#include <stdio.h>
#include <dir.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <except.h> //for xmsg
#include <cstring.h>

#include <mmsystem.h>

#include <process.h>
#include <dos.h>

//---------------------------------------------------------------------------
#define CATCH_OLE_ERROR     \
    catch(EOleException& e)                         \
	    {                                           \
        frmJoystick->stbJoystick->SimpleText =      \
            "OLE Error:  " + e.Message              \
            + "(" + e.ErrorCode + ")";              \
	    }                                           \
                                                    \
    catch(EOleSysError& e)                          \
	    {                                           \
        frmJoystick->stbJoystick->SimpleText =      \
            "OLE Error:  " + e.Message              \
            + "(" + e.ErrorCode + ")";              \
  	    }                                           \
                                                    \
    catch(EOleError& e)                             \
	    {                                           \
        frmJoystick->stbJoystick->SimpleText =      \
            "OLE Error:  " + e.Message;             \
        }                                           \
                                                    \
    catch(...)                                      \
	    {                                           \
        frmJoystick->stbJoystick->SimpleText =      \
            "OLE Error:  unknown error";            \
        }
//---------------------------------------------------------------------------
#endif
