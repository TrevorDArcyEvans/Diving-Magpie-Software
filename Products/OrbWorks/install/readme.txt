
	SolidPartners, Inc.

        	OrbWorks v2.x

------------------------------------------------------------------------

OrbWorks *must* be shutdown before SolidWorks
otherwise an error occurs.   

Under Windows NT, this is a Dr Watson error and
another instance of SolidWorks is started.
This is not visible and must be terminated
from the Task Manager.

Under Windows 95, this is causes an OLE error
and another instance of SolidWorks is started.
This is not visible and must be terminated from
the Windows Close Program (press CTRL-ALT-DEL).

------------------------------------------------------------------------

When the program starts, it looks for the file
'OrbWorks.ini' in the Windows directory.  If
this is not found, it will assume default settings.

------------------------------------------------------------------------

There may be problems under Windows 95 when the
program tries to load the supplied 'OrbWorks.ini'
file.  This usually shows up as lots of error
message boxes advising a floating point exception
has occurred.  Delete the supplied 'OrbWorks.ini'
file and the program should start up with default
settings.

------------------------------------------------------------------------

Only one instance of the program is allowed.
This is so that only one set of actions is
interpreted from the SpaceOrb.

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
