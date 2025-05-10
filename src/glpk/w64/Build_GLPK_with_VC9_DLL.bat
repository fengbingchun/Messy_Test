rem Build GLPK DLL with Microsoft Visual Studio Express 2008

rem NOTE: Make sure that HOME variable specifies correct path
set HOME="C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC"

call %HOME%\bin\vcvars64.bat
copy config_VC config.h
%HOME%\bin\nmake.exe /f Makefile_VC_DLL
%HOME%\bin\nmake.exe /f Makefile_VC_DLL check

pause
