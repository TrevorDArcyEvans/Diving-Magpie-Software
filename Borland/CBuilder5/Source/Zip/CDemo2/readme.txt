
This is a C++ Builder demo project to
demonstrate the use of the Zip DLL's.

The original author is:
Nikolaj Pagh <nikpagh@image.dk>


--------------------------------------------------------

For those of you who aren't familier with "FILE_ID.DIZ",
this is a special filename that is used to hold a short
description of the files in a zip archive.  It originated
several years ago when dial-up BBS's were very popular.

People were doing a lot of downloading, and they noticed 
that it's hard to remember what's in each zip archive.
The special "FILE_ID.DIZ" file refreshes your memory about
what is in that zip archive.

The official zip format also supports a special kind of
comments field where your comments into a special header
field in the archive - this is called "zip file comments".
However, I believe it's a bad idea to use this official 
"zip file comments" feature because some zip utilities
cause you to lose what you put in the "zip file comments",
and some BBS Sysops and Webmasters INTENTIONALLY overwrite
your own "zip file comments" so they can put in a plug for
their BBS or Web site!  BCB/Delphi Zip can not be used to 
create this type of "zip file comments".

If you use FILE_ID.DIZ to hold your comments, then nobody
will overwrite your comments, and they can easily be 
editted in the future.

--------------------------------------------------------

This demo is basically an editor/browser that lets you go
through your zip files and edit the descriptions in
file: FILE_ID.DIZ.

For zip files that don't have a FILE_ID.DIZ file, you
can easily add one.


Eric Engler
englere@swcp.com
