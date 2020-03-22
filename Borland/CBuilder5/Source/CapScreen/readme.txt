###############################################################################
TScreenCapture
for Delphi2 + Delphi3 *)

Copyright 1997 EASYCASH SOFTWARE

contact:Alexander Halser
email:	halser@easycash.co.at
www:	http://www.easycash.co.at/delphi
----------------------------------------

*) If this archive contains only the package files for 
   Delphi3, go to our homepage to download the source of TScreenCapture.

   You will find more exiting programs and delphi components there:

   http://www.easycash.co.at/delphi

###############################################################################

LIMITED WARRANTY
================
This component is ... and so on! I am sure you know that a
null-cost freeware component does not provide any guaranties.
Use it *as*it*is* or *do*it*yourself* .



INSTALLATION in DELPHI 3
========================

1) Copy SCAPTURE.DCU and SCAP.* into \Delphi\Lib 
2) Start Delphi 3 and select Components | Install Package from the menu
3) Click Add and locate SCAP.DPL
4) Click OK


OVERVIEW
========

TScreenCapture is a little component, that captures *any* window or the desktop (not even Delphi-forms!).
Drop a TScreenCapture on a form. When the programm is running, press ALT+F12 to capture the desktop.
That's all.

PROPERTIES
==========

ACTIVE:	    Boolean	Determines if TScreenCapture creates a snapshot, when
			the hotkey ALT+F12 is pressed. 

AUTOCOPY:   Boolean	If true, the captured bitmap will automatically be 
			copied to the clipboard.

DESKTOP:    Boolean	If true, TScreenCapture creates a snapshot of the whole desktop.
			If false, TScreenCapture creates a snapshot of the active window.

BITMAP:     TBitmap     Runtime-only! Contains the bitmap, when the user has created 
                        at least 1 snapshot. Please refer to delphi's help on TBitmap
			to get more information about the properties and methods of TBitmap.

Other Properties:	Do not matter. These are published properties of TWinControl.
			TScreenCapture is based on TWinControl because it needs a handle
			to get the hotkey.

METHODS
=======

CopyToClipboard (procedure)    Copies BITMAP to the clipboard. This is done automatically
                               when AUTOCOPY is true.


EVENTS
======

OnCapture:   TNotifyEvent	Is fired after the user created a snapshot pressing ALT+F12.
				The event is NOT fired, when TScreenCapture is not active.


FAQs
====

Q: Why can't I select another hotkey than ALT+F12.
A: You can. Check out the tiny source and modify it.
   The hotkey is registered in the "loaded"-procedure.
   The reason why I did not make it a property, is simple:
   It was no fun to do it.	

Q: Can I have the sourcecode, please ?
A: Go to http://www.easycash.co.at/delphi and download it!

Q: Is TScreenCapture freeware ?
A: Yes.

Q: Can I use it in commercial applications, too ?
A: Yes. Do what you want.

Q: Do you provide any support for TScreenCapture ?
A: No. Since TScreenCapture is freeware, I'm not able 
   to provide any support for it.
