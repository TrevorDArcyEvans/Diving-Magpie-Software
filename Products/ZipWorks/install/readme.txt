
	SolidPartners, Inc.

        	ZipWorks v2.x

------------------------------------------------------------------------

Very Important!!
Please make sure you have the correct verison 
of ZipWorks for your operating system.  There
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

1) ZipWorks doesn't:
For those people doing a manual installation,
there are separate version of ZipWorks for
Windows NT and Windows 95.  They are NOT
interchangeable.  Please make sure you are 
using the correct version.

2) ZipWorks still doesn't:
The registry entries assume the 
'Program Files' directory is on the C drive.

3) All zip files not created:
Make sure the InfoZIP program 'zip.exe' is in
your path.  Open up a command window and type:

	zip

you should get the copyright and listing of options.
The installation program will install the InfoZIP
program to your Windows directory.

------------------------------------------------------------------------

Manual Installation:
1) The following files are required:
    All platforms:
        zip.exe                InfoZIP
        IsUn32ex.exe           uninstallation program
                

    Windows NT:
        ZipWorksNT.reg	       registry settings
        ZipWorksNT.dll	       ZipWorks

    Windows 95:
        ZipWorks95.reg         registry settings
        ZipWorks95.dll         ZipWorks

2) Place the InfoZIP zip.exe somewhere in your
path eg C:\Windows or C:\WinNT

3) Place the ZipWorks file in a directory of
your choice.

4) Edit the registry setting file with a
text editor (notepad) to give the full path
to the ZipWorks file.  Don't forget to put in
double backslashes '\\' otherwise it won't work.

5) Double click on the registry settings file
to install it to the Windows registry.

------------------------------------------------------------------------

Manual Uninstallation:
1) run the unistallation program IsUn32ex.exe to remove the
registry settings

2) delete the program, help and configuration files

3) delete the installation directory

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
