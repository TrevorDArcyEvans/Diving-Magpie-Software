Delphi Sendkeys 1.2 For Delphi 2.0 and Delphi 3.0
=================================================

TO READ THIS DOCUMENT IN NOTEPAD SET WORDWRAP ON.

Installation
------------

For Delphi 2.0 ...

Copy the following files into your Delphi 2.0/Lib directory :

SendKeysD2.dcu
SendKeysD2.dcr

Then rename to :

SendKeys.dcu
SendKeys.dcr

For Delphi 3.0 ...

Copy the following files to your Lib directory :

SendKeysD3.dcu
SendKeysD3.dcr

Then rename to :

SendKeys.dcu
SendKeys.dcr

Then from within Delphi, click on 'Component', then 'Install' to invoke the Component Installation dialog box.  From here press 'Add' and use the browse button to locate the file SendKeys.dcu which you should have added into your Delphi/Lib directory.  Finally, click on 'OK'.  Delphi will then recompile the component library and after a few seconds, SendKeys should be visible in the Samples tab of the component palette.


The Methods
------------

1) procedure SendKeysTo(Titletext:string; const text :string);
--------------------------------------------------------------

This sends the specified text string to the window with the
specified title.

For special keys see the key constants in section 5.

e.g. To Close Delphi (Not that you'd want to do that) :

SendKeysTo('Delphi 2.0', SK_ALT_DN + 'F' + 'x' + SL_ALT_UP);
 	

2) procedure SendKeys(const text: String);
------------------------------------------

Sends the given text to the active window.
 
   
3) function  HandleFromTitle(const titletext: string): hWnd;
------------------------------------------------------------

Gets the handle of the window with the given text.

   
4) procedure MakeWindowActive(whandle: hWnd);
--------------------------------------------- 

Makes the specified window active for keyboard events   


5) Key Constants
----------------

         SK_BKSP = #8;
         SK_TAB = #9;
         SK_ENTER = #13;
         SK_ESC = #27;
         SK_F1 = #228;
         SK_F2 = #229;
         SK_F3 = #230;
         SK_F4 = #231;
         SK_F5 = #232;
         SK_F6 = #233;
         SK_F7 = #234;
         SK_F8 = #235;
         SK_F9 = #236;
         SK_F10 = #237;
         SK_F11 = #238;
         SK_F12 = #239;
         SK_HOME = #240;
         SK_END = #241;
         SK_UP = #242;
         SK_DOWN = #243;
         SK_LEFT = #244;
         SK_RIGHT = #245;
         SK_PGUP = #246;
         SK_PGDN = #247;
         SK_INS = #248;
         SK_DEL = #249;
         SK_SHIFT_DN = #250;
         SK_SHIFT_UP = #251;
         SK_CTRL_DN = #252;
         SK_CTRL_UP = #253;
         SK_ALT_DN = #254;
         SK_ALT_UP = #255;


