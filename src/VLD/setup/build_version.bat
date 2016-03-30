@ECHO OFF

TITLE Building VLD...

SETLOCAL ENABLEDELAYEDEXPANSION

REM Check if the needed files are present
IF "%VS100COMNTOOLS%"=="" GOTO :BadPaths

CD %~dp0/..

GOTO :GoodPaths

:BadPaths
ECHO: "Not all build dependencies found. To build iZ3D Driver you need:"
ECHO: "* Visual Studio 2010 installed"
PAUSE
GOTO :EndGood

:GoodPaths
SET ProgFiles=%ProgramFiles%
IF /i "%PROCESSOR_ARCHITECTURE%" == "AMD64" SET ProgFiles=%ProgramFiles(x86)%

SET BUILDTYPE=/%1
IF "%1"=="" SET BUILDTYPE=/rebuild
rem IF "%1"=="build" SET BUILDTYPE=

SET ORIGPATH="%CD%"
CALL "%VS100COMNTOOLS%vsvars32.bat"
CD %ORIGPATH%

:: Store start time
FOR /f "tokens=1-4 delims=:.," %%T IN ("%TIME%") DO (
	SET StartTIME=%TIME%
	:: Fix leading zero problem
	SET /a Start100S=%%T*360000+1%%U*6000+1%%V*100+1%%W - 610100
)

devenv /nologo vld_vs10.sln %BUILDTYPE% "Release|Win32" /Project vld
IF %ERRORLEVEL% NEQ 0 GOTO EndBad
devenv /nologo vld_vs10.sln %BUILDTYPE% "Release|x64" /Project vld
IF %ERRORLEVEL% NEQ 0 GOTO EndBad

if not exist "%ProgFiles%\Inno Setup 5\ISCC.exe" GOTO EndBad
"%ProgFiles%\Inno Setup 5\ISCC.exe" setup\vld-setup.iss
IF %ERRORLEVEL% NEQ 0 GOTO EndBad
CD setup

ECHO 

:: Retrieve Stop time
FOR /f "tokens=1-4 delims=:.," %%T IN ("%TIME%") DO (
	SET StopTIME=%TIME%
	:: Fix leading zero problem
	SET /a Stop100S=%%T*360000+1%%U*6000+1%%V*100+1%%W - 610100
)

:: Test midnight rollover. If so, add 1 day=8640000 1/100ths secs
IF %Stop100S% LSS %Start100S% SET /a Stop100S+=8640000
SET /a TookTimeSec=(%Stop100S%-%Start100S%)/100
SET /a TookTimeMin=TookTimeSec/60
SET /a TookTimeSec=%TookTimeSec%-%TookTimeMin%*60

ECHO Started: %StartTime%
ECHO Stopped: %StopTime%
ECHO Elapsed: %TookTimeMin% min. %TookTimeSec% sec.

PAUSE

GOTO :EndGood

:EndBad
CD setup
ECHO: " "
ECHO: ERROR: Build failed and aborted
PAUSE
GOTO :EOF

:EndGood
GOTO :EOF