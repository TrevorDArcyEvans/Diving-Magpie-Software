TFloatEdit component  Version 1.1 for Delphi 2.0

What's diz ?
 A Delphi component named TFloatedit.
 It's used to input numerical Floating Point Values.
 You can set Min- and Max-Value and the maximal count of decimal digits. 
 
(C) 1996, by Markus Stephany. All rights reserved.
You can use this component free of charge in your public domain, freeware and 
shareware programs.
You must not use this component in any commercial applications withaut my permission.

You may give copies to others by copying the original, unmodified zip file for free.

If there are any questions, comments or suggestions, or if you find any bugs, please send a
mail in English or even better in German (cause my English doesn't take me everywhere) to :

MirBir.St@T-Online.de 

===========
DESCRIPTION
===========

1. Installation
(Cause I don't know the english Delphi-Version, I can't give any guaranty whether the 
Translation of Menu-Entries will be correct.)
- Extract or Copy FlEdit.pas and FlEdit.dcr into your components-directory.
- Choose KOMPONENTE (COMPONENT) / INSTALLIEREN (INSTALL)
- Click the HINZUFÜGEN (ADD) - Button
- Click the DURCHSUCHEN (BROWSE) - Button
- Choose the directory where FlEdit.pas and FlEdit.dcr were copied to.
- Select FlEdit.pas
- Click on the ÖFFNEN (OPEN) - Button
- After Installation, you will find TFloatEdit in the Samples-Folder.

2.Usage
TFloatedit is an descendant of TEdit; therefore the usage is quit similar, but there are a
few added properties:
- Digits:
	That means the max. number of digits after the decimal point.
	Available are values from 0 up to 18.
	if 0 digits are choosen, no decimal separator can be entered into the FloatEdit
- ErrorMessage:
	If this property has an other value then '[No Text]', a message with this value will
	be shown to the user, if his input is invalid (see Min and Max).
- Max:
	The highest valid Value 
- Min:	
	The least valid Value
- Value:
	The Floating Point-Value of FloatEdit's text (Read- and Write- Access).

	The Range of Min,Max and Value is Extended.

***** Revision 1.1
There was a bug in the range checking; I hope it is fixed now.
In V1.0 the value has been checked at each onkeypress-event, and that was not very fine
in some cases. Now the correctness of the value will be checked when the focus get lost.
If the value isn't in the range of min-max, the focus can't get lost.
And now, the user can press the ESC-Key in FloatEdit to restore the value that was set
before he made changes.



Viel Spaß beim Programmieren wünscht

Markus.

