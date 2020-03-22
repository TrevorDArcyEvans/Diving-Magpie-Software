//---------------------------------------------------------------------------
#ifndef swOleH
#define swOleH
//---------------------------------------------------------------------------
#include <vcl\sysdefs.h>

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
//---------------------------------------------------------------------------
#define CATCH_OLE_ERROR     \
    catch(EOleException& e)                         \
	    {                                           \
        frmOrb->stbOrb->SimpleText =                \
            "OLE Error:  " + e.Message              \
            + "(" + e.ErrorCode + ")";              \
	    }                                           \
                                                    \
    catch(EOleSysError& e)                          \
	    {                                           \
        frmOrb->stbOrb->SimpleText =                \
            "OLE Error:  " + e.Message              \
            + "(" + e.ErrorCode + ")";              \
  	    }                                           \
                                                    \
    catch(EOleError& e)                             \
	    {                                           \
        frmOrb->stbOrb->SimpleText =                \
            "OLE Error:  " + e.Message;             \
        }                                           \
                                                    \
    catch(...)                                      \
	    {                                           \
        frmOrb->stbOrb->SimpleText =                \
            "OLE Error:  unknown error";            \
        }
//---------------------------------------------------------------------------
#endif
