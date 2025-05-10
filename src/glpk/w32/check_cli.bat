@echo off
REM w64/check_cli.bat
REM
REM This batch file checks that GLPK can be used with C#.
REM C# examples in directory ..\examples are built and executed.
REM @author Heinrich Schuchardt, 2015

csc.exe /platform:x86 /r:libglpk-cli.dll ..\examples\csharp\version.cs
version.exe
echo -
echo Test is passed if the GLPK version is displayed
pause
csc.exe /platform:x86 /r:libglpk-cli.dll ..\examples\csharp\lp.cs
lp.exe
echo -
echo Test is passed if OPTIMAL LP SOLUTION FOUND
pause
csc.exe /platform:x86 /r:libglpk-cli.dll ..\examples\csharp\errordemo.cs
errordemo.exe
echo -
echo Test is passed if iterations with and without errors occured.
pause
csc.exe /platform:x86 /r:libglpk-cli.dll ..\examples\csharp\gmpl.cs
gmpl.exe ..\examples\csharp\marbles.mod
echo -
echo Test is passed if INTEGER OPTIMAL SOLUTION FOUND
pause
csc.exe /platform:x86 /r:libglpk-cli.dll ..\examples\csharp\linord.cs
linord.exe ..\examples\csharp\tiw56r72.mat ..\examples\csharp\tiw56r72.sol
echo -
echo Test is passed if INTEGER OPTIMAL SOLUTION FOUND and
echo file tiw56r72.sol has been written.
pause
csc.exe /platform:x86 /r:libglpk-cli.dll ..\examples\csharp\minimumcostflow.cs
minimumcostflow.exe
del mincost.lp mincost.dimacs
echo -
echo Test is passed if files mincost.lp and mincost.dimacs have been written.
pause
csc.exe /platform:x86 /r:libglpk-cli.dll ..\examples\csharp\relax4.cs
relax4.exe ..\examples\csharp\sample.min
echo -
echo Test is passed if ret = 0.
pause
