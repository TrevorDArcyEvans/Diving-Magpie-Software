
VC_XML_XSL_Test_ATLps.dll: dlldata.obj VC_XML_XSL_Test_ATL_p.obj VC_XML_XSL_Test_ATL_i.obj
	link /dll /out:VC_XML_XSL_Test_ATLps.dll /def:VC_XML_XSL_Test_ATLps.def /entry:DllMain dlldata.obj VC_XML_XSL_Test_ATL_p.obj VC_XML_XSL_Test_ATL_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del VC_XML_XSL_Test_ATLps.dll
	@del VC_XML_XSL_Test_ATLps.lib
	@del VC_XML_XSL_Test_ATLps.exp
	@del dlldata.obj
	@del VC_XML_XSL_Test_ATL_p.obj
	@del VC_XML_XSL_Test_ATL_i.obj
