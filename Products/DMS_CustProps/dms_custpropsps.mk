
DMS_CustPropsps.dll: dlldata.obj DMS_CustProps_p.obj DMS_CustProps_i.obj
	link /dll /out:DMS_CustPropsps.dll /def:DMS_CustPropsps.def /entry:DllMain dlldata.obj DMS_CustProps_p.obj DMS_CustProps_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DMS_CustPropsps.dll
	@del DMS_CustPropsps.lib
	@del DMS_CustPropsps.exp
	@del dlldata.obj
	@del DMS_CustProps_p.obj
	@del DMS_CustProps_i.obj
