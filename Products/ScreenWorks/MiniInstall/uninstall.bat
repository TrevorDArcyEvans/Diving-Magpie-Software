set Windows=c:\Windows
set System=c:\Windows\System

if %OS%==Windows_NT set Windows=c:\WinNT
if %OS%==Windows_NT set System=c:\WinNT\System32


del "C:\Program Files\SolidPartners\ScreenWorks\*.txt"
del "C:\Program Files\SolidPartners\ScreenWorks\*.doc"
del "C:\Program Files\SolidPartners\ScreenWorks\*.bat"
del "C:\Program Files\SolidPartners\ScreenWorks\readme"
del "C:\Program Files\SolidPartners\ScreenWorks\copying"
del "C:\Program Files\SolidPartners\ScreenWorks\where"



C:
cd %System%

regsvr32 /u XView3D.dll
regsvr32 /u IM.dll
regsvr32 /u SG2.dll
regsvr32 /u SWRKS.dll



del %Windows%\ScrWorks.ini
del %Windows%\ScrHots.dll
del %System%\ScreenWorks.scr
del %System%\ScrWorks.bmp
del %System%\XView3d.dll
del %System%\im.dll
del %System%\sg2.dll
del %System%\SWrks.dll
