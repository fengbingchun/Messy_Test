rem Build GLPK DLL with Microsoft Visual Studio Community 2015

rem NOTE: Make sure that HOME variable specifies correct path
set HOME="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC"

call %HOME%\vcvarsall.bat x64
copy config_VC config.h
%HOME%\bin\nmake.exe /f Makefile_VC_DLL
%HOME%\bin\nmake.exe /f Makefile_VC_DLL check

pause
