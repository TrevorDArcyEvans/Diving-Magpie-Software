
C-Builder Demo 4 - A limited application, but it supports
automatic install features.

If this were being distributed in a C-Builder Zip Self-Extracting Archive,
you would tell it to run this command line after extraction:
'><ViewZip /install'.


Ways to test this program from a DOS box:


C:\> CDemo4 /install       Automatically bring up the install menu

C:\> CDemo4 test.zip       Run it with a zip file parameter
 
C:\> start test.zip        Check the File Extension assoc. in Registry

C:\> start CDemo4          Check the Application Path in Registry
 
C:\> CDemo4 /uninstall     Automatically perform uninstall and quit


The uninstall can also be performed from the Control Panel.


===============================================================

This is advanced code that is set up for Win95 systems.
You need to adapt it for use with WinNT.  

WARNING: Use CDemo4 AT YOUR OWN RISK!!!  I still consider it
a "work in progress", but it is very handy code, so I decided
to include it with this release.
