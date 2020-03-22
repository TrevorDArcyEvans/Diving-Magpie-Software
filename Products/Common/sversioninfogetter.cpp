#include "SVersionInfoGetter.hpp"

SVersionInfoGetter::SVersionInfoGetter ()
:m_Buffer (0)
{
	char FullPath[1024];

	GetModuleFileName (0,FullPath, sizeof(FullPath));

	DWORD Dum;
    int Size = GetFileVersionInfoSize(FullPath, &Dum);

	if (Size)
	{
		m_Buffer = new char[Size];

		GetFileVersionInfo (FullPath,0,Size,m_Buffer);
	}//if
}//SVersionInfoGetter::SVersionInfoGetter

SVersionInfoGetter::~SVersionInfoGetter ()
{
	if (m_Buffer)
		delete m_Buffer;
	//if
}//SVersionInfoGetter::~SVersionInfoGetter

char* SVersionInfoGetter::GetSection
(
	const CString& Section
)const
{
	char* Buf;
	unsigned int Size = 0;

	if (VerQueryValue ((void*)m_Buffer,(LPTSTR)(LPCTSTR)("\\StringFileInfo\\040904b0\\" + Section),(void**)(&Buf),&Size))
		return Buf;
	else
		return "";
	//if
}//SVersionInfoGetter::GetSection

CString SVersionInfoGetter::ProductName () const
{
	return GetSection ("ProductName");
}//SVersionInfoGetter::ProductName

CString SVersionInfoGetter::Copyright () const
{
	return GetSection ("LegalCopyright");
}//SVersionInfoGetter::Copyright

CString SVersionInfoGetter::Version () const
{
	return GetSection ("ProductVersion");
}//SVersionInfoGetter::Copyright
