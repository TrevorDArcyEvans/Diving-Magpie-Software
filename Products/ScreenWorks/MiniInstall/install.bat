set Windows=c:\Windows
set System=c:\Windows\System

if %OS%==Windows_NT set Windows=c:\WinNT
if %OS%==Windows_NT set System=c:\WinNT\System32



mkdir "C:\Program Files\SolidPartners"
mkdir "C:\Program Files\SolidPartners\ScreenWorks"

copy *.bat "C:\Program Files\SolidPartners\ScreenWorks"

unzip -uoC ScreenWorks.zip *.txt       -d "C:\Program Files\SolidPartners\ScreenWorks"
unzip -uoC ScreenWorks.zip *.doc       -d "C:\Program Files\SolidPartners\ScreenWorks"
unzip -uoC ScreenWorks.zip readme      -d "C:\Program Files\SolidPartners\ScreenWorks"
unzip -uoC ScreenWorks.zip copying     -d "C:\Program Files\SolidPartners\ScreenWorks"
unzip -uoC ScreenWorks.zip where       -d "C:\Program Files\SolidPartners\ScreenWorks"



unzip -uoC ScreenWorks.zip ScrHots.dll     -d %Windows%
unzip -uoC ScreenWorks.zip ScreenWorks.scr -d %System%
unzip -uoC ScreenWorks.zip XView3d.dll     -d %System%
unzip -uoC ScreenWorks.zip im.dll          -d %System%
unzip -uoC ScreenWorks.zip sg2.dll         -d %System%
unzip -uoC ScreenWorks.zip SWrks.dll       -d %System%

copy ScrWorks.ini %Windows%
copy ScrWorks.bmp %System%

if     %OS%==Windows_NT regedit ScrWorksNT.reg
if not %OS%==Windows_NT regedit ScrWorks95.reg

ScrInstall.exe


C:
cd %System%

regsvr32 /s XView3D.dll
regsvr32 /s IM.dll
regsvr32 /s SG2.dll
regsvr32 /s SWRKS.dll



cd %Windows%

rundll32 ScrHots.dll,RunInstallDialog
rundll32 ScrHots.dll,RunService
