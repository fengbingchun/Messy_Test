LibreOffice Basic
=================

This directory contains an example demonstrating how to call the GLPK
library from LibreOffice.

The code was written for LibreOffice 32bit version 5.3 beta. For
execution it requires the stdcall GLPK dynamic link library to be in
the search path for binaries.

From the administration for Basic macros choose the library import and
import script.xlb. This will create a macro libray GLPK. Module lp
contains the macro lp.

The macro creates a linear problem, solves it, and shows the result in
a message box.