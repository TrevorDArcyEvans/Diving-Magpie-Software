BatchPrint.exe
==============

Warning: this program is provided on an As-Is basis.  Neither SolidWorks Corporation nor the program author can be held liable for errors in the program or output as a result of running this program.

-------------

This utility will print a list of SolidWorks drawing documents.  Files can be added to the list by double-clicking in the file list or by using one of the "Add" buttons.  Each file will be loaded in the current session of SolidWorks, if one is found, or loaded into a background SolidWorks session if an existing session is not running.  
Print scale and Printer choice can be chosen based on size of the sheet being printed. 

Multi-sheet drawings with varying sheet size are fully supported.   

All user preference settings will be saved to the registry and retrieved for the next program run.   Currently supports A-E size sheets but can be expanded as outlined in BatchPrint.bas.

Program Steps:
1. Execute the BatchPrint.exe program

2. Use the Explorer interface to locate SolidWorks Drawing files (*.slddrw, *.drw) for printing.

3. Add files to the print list by double-clicking the file, or by selecting the file(s) and choosing "Add Selected".  To add all files from the current directory, choose the "Add All" button.

4. Once you have chosen all the files to be printed, select the "Submit Batch" button.  All files that appear in the "Files to be Printed" list will be loaded and printed.

5. If specific printer settings have not been made on the Advanced Page, then values from your last program run will be used. These values are stored and read from the registry.  If no settings have been made, then the default printer will be used and files will be printed to "Fit".