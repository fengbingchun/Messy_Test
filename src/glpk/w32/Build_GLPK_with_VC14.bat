rem Build GLPK with Microsoft Visual Studio Community 2015

rem NOTE: Make sure that HOME variable specifies correct path
set HOME="C:\Program Files\Microsoft Visual Studio 14.0\VC"

call %HOME%\vcvarsall.bat x86
copy config_VC config.h
%HOME%\bin\nmake.exe /f Makefile_VC
%HOME%\bin\nmake.exe /f Makefile_VC check

pause
