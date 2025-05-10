rem Build GLPK DLL with Microsoft Visual Studio Express 2010

rem NOTE: Make sure that HOME variable specifies correct path
set HOME="C:\Program Files\Microsoft Visual Studio 10.0\VC"

call %HOME%\vcvarsall.bat x86
copy config_VC config.h
%HOME%\bin\nmake.exe /f Makefile_VC_DLL
%HOME%\bin\nmake.exe /f Makefile_VC_DLL check

pause
