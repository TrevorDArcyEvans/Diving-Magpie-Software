
DMS_WinErrorps.dll: dlldata.obj DMS_WinError_p.obj DMS_WinError_i.obj
	link /dll /out:DMS_WinErrorps.dll /def:DMS_WinErrorps.def /entry:DllMain dlldata.obj DMS_WinError_p.obj DMS_WinError_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DMS_WinErrorps.dll
	@del DMS_WinErrorps.lib
	@del DMS_WinErrorps.exp
	@del dlldata.obj
	@del DMS_WinError_p.obj
	@del DMS_WinError_i.obj
