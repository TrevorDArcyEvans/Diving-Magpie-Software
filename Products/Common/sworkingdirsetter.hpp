#ifndef _SWorkingDirSetter_hpp
#define _SWorkingDirSetter_hpp

#include <direct.h>

class SWorkingDirSetter
{
private:

	char	m_Old[1024];

public:

	SWorkingDirSetter (const char* New)
	{
		::_getcwd (m_Old,1024);

		::_chdir (New);
	}

	~SWorkingDirSetter ()
	{
		::_chdir (m_Old);
	}
};//SWorkingDirSetter

#endif

