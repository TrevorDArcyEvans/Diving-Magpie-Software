// pre-compiled headers
#include "stdafx.h"

#include <tchar.h>
#include "WinUtil.h"

void wu_strcpy(char *dest, CString source)
{
for (int i = 0; i < source.GetLength(); i++)
    {
	dest[i] = (char ) source[i];	
	}
dest[source.GetLength()] = '\0';
}