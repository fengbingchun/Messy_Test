@echo off
REM w64/check_vb.bat
REM
REM This batch file checks that GLPK can be used with Visual Basic .Net.
REM VB examples in directory ..\examples are built and executed.
REM @author Heinrich Schuchardt, 2017

copy libglpk-cli.dll ..\examples\vb

vbc.exe /r:libglpk-cli.dll ..\examples\vb\version.vb
..\examples\vb\version.exe
echo -
echo Test is passed if the GLPK version is displayed
pause
vbc.exe /r:libglpk-cli.dll ..\examples\vb\lp.vb
..\examples\vb\lp.exe
echo -
echo Test is passed if OPTIMAL LP SOLUTION FOUND
pause
vbc.exe /r:libglpk-cli.dll ..\examples\vb\errordemo.vb
..\examples\vb\errordemo.exe
echo -
echo Test is passed if iterations with and without errors occured.
pause
vbc.exe /r:libglpk-cli.dll ..\examples\vb\gmpl.vb
..\examples\vb\gmpl.exe ..\examples\vb\marbles.mod
echo -
echo Test is passed if INTEGER OPTIMAL SOLUTION FOUND
pause

del ..\examples\vb\libglpk-cli.dll
