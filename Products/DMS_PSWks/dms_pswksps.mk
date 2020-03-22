
DMS_PSWksps.dll: dlldata.obj DMS_PSWks_p.obj DMS_PSWks_i.obj
	link /dll /out:DMS_PSWksps.dll /def:DMS_PSWksps.def /entry:DllMain dlldata.obj DMS_PSWks_p.obj DMS_PSWks_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DMS_PSWksps.dll
	@del DMS_PSWksps.lib
	@del DMS_PSWksps.exp
	@del dlldata.obj
	@del DMS_PSWks_p.obj
	@del DMS_PSWks_i.obj
