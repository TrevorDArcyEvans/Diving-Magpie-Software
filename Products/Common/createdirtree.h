#if !defined(CREATE_DIR_TREE__INCLUDED_)
#define CREATE_DIR_TREE__INCLUDED_

#include "stdafx.h"

#include "SString.hpp"
#include "Shlwapi.h"

//--------------------------------------------------------------------
bool    CreateDirTree
(
    CString                     DirTree,
    LPSECURITY_ATTRIBUTES       lpSecurityAttributes
);
//--------------------------------------------------------------------
#endif
