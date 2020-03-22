
	SolidPartners, Inc.

		BMPWorks v1.x

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

1) SolidWorks bitmap is not correct:
quite often, the SolidWorks bitmap is pasted with
black or blotchy areas at the top and bottom.  We
believe this is a problem with the way in which
SolidWorks stores the bitmaps and we are working
on a fix for this.

------------------------------------------------------------------------

Manual Installation:
1) The following files are required:
    Windows NT & 95:
	BMPWorks.dll		BMPWorks
	BMPWorks.hlp		help file
	SldAsm.reg		registry file
	SldDrw.reg		registry file
	SldPrt.reg		registry file

2) Place all the BMPWorks files, except for
BMPWorks.dll, in the:

    C:\Program Files\SolidPartners\BMPWorks

directory.  If this directory does not exist, create it.

Place BMPWorks.dll in your Windows directory, usually
C:\WinNT (Windows NT) or C:\Windows (Windows 95).

3) Double click on the registry settings files
to install them to the Windows registry.

------------------------------------------------------------------------

Manual Uninstallation:
1) use the registry editor and remove the following
keys:

	[HKEY_CLASSES_ROOT\SldAssem.Document\shell\Copy &bitmap]
	[HKEY_CLASSES_ROOT\SldDraw.Document\shell\Copy &bitmap]
	[HKEY_CLASSES_ROOT\SldPart.Document\shell\Copy &bitmap]

2) delete BMPWorks.dll and help files

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
