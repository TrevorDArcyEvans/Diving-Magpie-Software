
        SolidPartners Inc

        	MenuWorks v2.x

------------------------------------------------------------------------

Very Important!!
Please make sure you have the correct version 
of MenuWorks for your operating system.  There
are separate versions for Windows NT and 
Windows 95.  They are not interchangeable.

------------------------------------------------------------------------

Installation:
Several entries have to be made in the registry.
It is highly recommended that this be left to 
the installation program.

For the brave of heart attempting a manual
installation, please read the Manual
Installation section at the end.

------------------------------------------------------------------------

Common Problems:

1) MenuWorks doesn't work:
For those people doing a manual installation,
there are separate version of MenuWorks for
Windows NT and Windows 95.  They are NOT
interchangeable.  Please make sure you are 
using the correct version.

2) MenuWorks still doesn't work:
The registry entries assume the 
'Program Files' directory is on the C drive.


------------------------------------------------------------------------

Manual Installation:
1) The following files are required:
    Windows NT:
        MenuWorksNT.reg            registry settings
        MenuWorksNT.dll            MenuWorks
	MenuWorks.hlp              help file
	MenuWorks.ini              configuration file
	IsUn32ex.exe               uninstallation program

    Windows 95:
        MenuWorks95.reg            registry settings
        MenuWorks95.dll            MenuWorks
	MenuWorks.hlp              help file
	MenuWorks.ini              configuration file
	IsUn32ex.exe               uninstallation program

2) Place all the MenuWorks files, except for
MenuWorks.ini, in the:

	C:\Program Files\SolidPartners\MenuWorks

directory.  If this directory does not exist, create it.

Place MenuWorks.ini in your Windows directory, usually
C:\WinNT (Windows NT) or C:\Windows (Windows 95).

3) Double click on the registry settings file
to install it to the Windows registry.

------------------------------------------------------------------------

Manual Uninstallation:
1) run the unistallation program IsUn32ex.exe to remove the
registry settings

2) delete the program, help and configuration files

3) delete the installation directory

------------------------------------------------------------------------

You can either manually edit the supplied 'MenuWorks.ini' file or use 
the included MenuWorks editor program.

The MenuWorks editor program has restricted functionality for 
unregistered users.

The format of the 'MenuWorks.ini' file is as follows:

	[LM_Main]
	Title="&Utilities"			top level menu name
	
	
	[LM_Program0]				first program
	Prog_Name="explorer.exe"		command line
	Menu_Text="Explorer"			text to appear in menu
	Hint_Text="manage your files"		text to appear in 
							status bar
	
	
	[LM_Program1]				second program etc
	Prog_Name="c:\winzip\winzip32.exe"	full path to program, 
							if not in path
	Menu_Text="WinZip"
	Hint_Text="compress/uncompress a file"

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
