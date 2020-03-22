This zip file contains two Delphi2 components, TMinMax, and TDragDrop.  Each Component uses a technique to capture messages sent to the owner form before it can receive them.

The components in this zip file are provided free of charge and without warranty of any kind.  I make no claim that they will not inadvertently do a bunch of nasty stuff like trash ones hard drive and other such undesirable things.  But, the code is provided, so look at it before installing the components if you are nervous =).


-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
If you experience any problems using the components feel free
to send me an e-mail at the below address.  Also, if you like
the components, an e-mail would be great.

mgrunder@zip2.com
Michael Grunder
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


TMinMax
-------
The TMinMax component provides an easy way to limit a form's minimum and maximum tracking size.

*** Properties ***

MaxHeight - This is the maximum height of the form at Run-Time.
MinHeight - This is the minimum height of the form at Run-Time.
MaxWidth  - This is the maximum width of the form at Run-Time.
MinWidth  - This is the minimum width of the form at Run-Time.

Note:  Setting any of the above four properties to 0 is the same as not constraining by the given axis.  So, setting MinHeight to 0 lets the form be any height (up to whatever MaxHeight is, unless, that to is zero).

DTOptions : This is a useful set of design time options, where you can specify the component to automatically set one of the Height/Width constraints based upon the form's size at design time.  For example, if you set dtOptions = [moMinW], when you resize the width of the form, MinWidth will change with the forms width.  If you set all of the options on, it is the same as choosing bsSingle for the Forms BorderStyle, except that the border looks slightly different.


TDragDrop
-------
The TdragDrop component makes it easy to add inter-application Drag and drop processing to your Delphi application by trapping and handling the WM_DRAGDROP message.

*** Properties ***

Active       - Specifies whether or not drag and drop is enabled.  
BringToFront - When set, the application where files were dropped is automatically brought to the foreground.

DroppedFiles - A TstringList containing each of the dropped files.  Run time only.

*** Events ***
OnFilesDropped(NumFiles:Integer) - This event is called when files are dropped on the form containing an active DragDrop component.





