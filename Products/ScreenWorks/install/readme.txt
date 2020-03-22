
	SolidPartners, Inc.

		ScreenWorks v1.x

------------------------------------------------------------------------

ScreenWorks only works with SolidWorks 99 files.  It does not
read SolidWorks 98Plus files.

------------------------------------------------------------------------

Manual Installation:
run the supplied install.bat batch file.  The batch file
assumes that Windows is installed on your C drive in the 
default directories:

	Windows NT
		WinNT\system32

	Windows 95
		Windows\system

You may edit the batch file to suit your specific setup.


Installation Steps:
The steps to install ScreenWorks by hand are as follows:

  * unzip all the files to a temporary directory

  * essential file locations are as follows:

        \Program Files\
            readme.txt
            license.txt
            install.bat
            uninstall.bat
            ScrWorks.reg

        \Windows\    or    \WinNT\
            ScrWorks.ini
            ScrHots.dll

        \Windows\System    or    \WinNT\System32
            ScrWorks.scr
            ScrWorks.bmp

            XView3D.dll
            im.dll
            sg2.dll
            SWrks.dll

  * create any of these directories as needed

  * the following support files are only required
    by the install.bat batch file:

        unzip.exe
        unzip.doc
        readme
        copying
        where

    They are not necessary when doing a manual install.

  * in Windows Explorer, double click the ScrWorks.reg
    file to enter the registry settings

  * open a Command Prompt window and navigate to the
    \Windows\ or \WinNT\ directory

  * at the command line, type:

        rundll32 ScrHots.dll,RunInstallDialog

    to install the screen saver hotspots utility

  * navigate to the \Windows\System or \WinNT\System32
    directory

  * register the ActiveX components by typing:

        regsvr32 /s XView3D.dll
        regsvr32 /s IM.dll
        regsvr32 /s SG2.dll
        regsvr32 /s SWRKS.dll

    at the command line

  * installation is now complete!

------------------------------------------------------------------------

Manual Uninstallation:
run the supplied uninstall.bat batch file.  The batch file
assumes that Windows is installed on your C drive in the 
default directories as per the install batch file (see above).


Uninstallation Steps:
  * delete all the files installed in the installation
    procedure above

  * open the registry editor (Start\Run...\regedit.exe)

  * delete following the keys and sub-keys:

        [HKEY_CURRENT_USER\Software\SolidPartners\ScreenWorks]
        [HKEY_CLASSES_ROOT\CLSID\{9CB48109-E0FC-11D0-8E0C-C52523886C3B}]
        [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Controls Folder\Display\shellex\PropertySheetHandlers\ScrHots Properties]


  * open a Command Prompt window and navigate to the
    \Windows\System or \WinNT\System32 directory

  * unregister the ActiveX components by typing:

        regsvr32 /u XView3D.dll
        regsvr32 /u IM.dll
        regsvr32 /u SG2.dll
        regsvr32 /u SWRKS.dll

    at the command line

  * installation is now complete!

------------------------------------------------------------------------

Please report all bugs to:

	SolidPartners, Inc.
	2155  Las Positas Ct, Suite D
	Livermore, California  94550
	USA

	tel:    925-373-3443
	fax:    925-373-3445
	email:  sales@SolidPartners.com
	web:    www.SolidPartners.com

------------------------------------------------------------------------
