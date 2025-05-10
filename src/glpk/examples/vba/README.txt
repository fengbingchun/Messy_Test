Visual Basic for Applications examples for GLPK
===============================================

This directory contains multiple examples demonstrating calling the GLPK
library from VBA.

- glpk.bas contains the definitions of the library functions.
- errdemo.bas demonstrates error handling.
- gmpl.bas loads a GMPL model and solves the problem.
- lp.bas solves a linear problem.
- mip.bas solves a mixed integer problem.

To run the examples follow the steps below:

- Open Excel
- Either press ALT+F11 or select menu entry Developer -> View code.
- With menu entry File -> Import File import the modules.
- In glpk.bas replace "glpk.dll" with the full path to the relevant dll:
  w32/glpk_4_65_stdcall.dll for 32bit Windows,
  w65/glpk_4_65.dll for 65bit Windows.
- Press CTRL+G or select menu entry View -> Immediate Window.
- Press F5 to run an example. The output is shown in the immediate
  window.
- To run gmpl.bas call function gmpl_main passing the name of a GMPL
  model file as parameter.
