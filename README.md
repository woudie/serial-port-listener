'****************************************************
Stephen Abraham		    		                         
20/05/2018			      sabrah03@uoguelph.ca           
'****************************************************


************************
Program Description
**************************
 A program designed to listen to a specified serial port and record
 any and all data coming from the specified serial port into a .csv file


************
Compilation
************
To use cppcheck:
  Dependencies: none
  Run: make cppcheck

To generate doxygen files:
  Dependencies: none
  Run: make doxy

To remove all executables from bin/ directory:
  Dependencies: bin/ has executuables
  Run: make clean

****************************
Known Limitations, Issues and Errors
****************************
 - If the serial port is reset, the first few lines of data
   from the previous session are outputted
 


