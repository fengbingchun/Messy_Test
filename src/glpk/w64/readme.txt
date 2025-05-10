This directory contains batch files and other stuff which you can use
to build GLPK for 64-bit Windows with the native C/C++ compilers.

Before running the batch file do the following:

1. Make sure that you have installed the compiler you are going to use
   to build GLPK.

2. Look into corresponding batch file (just right-click it and choose
   'Edit' in the popup menu; DO NOT choose 'Open'). Make sure that HOME
   variable specifies correct path to the compiler directory; if not,
   make necessary changes.

To run the batch file just double-click it and wait a bit while the
Make utility does its job. The message 'OPTIMAL SOLUTION FOUND' in the
MS-DOS window means that all is OK. If you do not see it, something is
wrong.

Once GLPK has been successfully built, there must appear two files in
this directory:

glpk.lib, which is the GLPK object library, and

glpsol.exe, which is the stand-alone GLPK LP/MIP solver.
