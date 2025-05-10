rem Build GLPK for C#/CLI DLL with Microsoft Visual Studio Community 2015
rem and Windows SDK 7.1.
rem NOTE: Make sure that the following variables specify correct paths:
rem HOME, SWIG, SDK, NET.

rem Path to GLPK source (glpk.h will be in $(GLPK_HOME)/src)
set GLPK_HOME=".."
rem Path to Visual Studio Express
set HOME="C:\Program Files (x86)\Microsoft Visual Studio 14.0"
rem Path to SwigWin
set SWIG="C:\Program Files (x86)\swig\swigwin-3.0.12"
rem Path to Windows SDK
set SDK="C:\Program Files (x86)\Windows Kits\10"
rem Path to .NET Framework
set NET="C:\Windows\Microsoft.NET\Framework64\v4.0.30319\"

set PATH=%NET%;%PATH%
cd ..\swig-cli
mkdir src\csharp
mkdir src\c
copy *.cs src\csharp
%SWIG%\swig.exe -I..\src -csharp -dllimport libglpk_cli_native -namespace org.gnu.glpk -o src/c/glpk_wrap.c -outdir src/csharp glpk.i
cd "%~dp0"
del libglpk-cli.dll
csc.exe -target:library -out:libglpk-cli.dll ..\swig-cli\src\csharp\*.cs
set INCLUDE=
set LIB=
call %HOME%\VC\vcvarsall.bat x86_amd64
call %SDK%\bin\x86\rc.exe glpk_cli_dll.rc
%HOME%\VC\bin\nmake.exe /f Makefile_CLI_VC_DLL
%HOME%\VC\bin\nmake.exe /f Makefile_CLI_VC_DLL check
set INCLUDE=
set LIB=
pause
