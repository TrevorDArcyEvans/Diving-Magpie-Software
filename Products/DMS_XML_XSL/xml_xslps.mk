
XML_XSLps.dll: dlldata.obj XML_XSL_p.obj XML_XSL_i.obj
	link /dll /out:XML_XSLps.dll /def:XML_XSLps.def /entry:DllMain dlldata.obj XML_XSL_p.obj XML_XSL_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del XML_XSLps.dll
	@del XML_XSLps.lib
	@del XML_XSLps.exp
	@del dlldata.obj
	@del XML_XSL_p.obj
	@del XML_XSL_i.obj
