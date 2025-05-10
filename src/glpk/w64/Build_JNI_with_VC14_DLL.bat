rem Build GLPK JNI DLL with Microsoft Visual Studio Community 2015
rem NOTE: Make sure that the following variables specify correct paths:
rem HOME, SWIG, JAVA_HOME, GLPK_HOME

rem Path to GLPK source (glpk.h will be in $(GLPK_HOME)/src)
set GLPK_HOME=".."
rem Path to Visual Studio
set HOME="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC"
rem Path to SwigWin
set SWIG="C:\Program Files (x86)\swig\swigwin-3.0.12"
rem Path to Windows SDK
set SDK="C:\Program Files (x86)\Windows Kits\10"

set path_build_jni=%path%
cd ..\swig
mkdir target\classes
mkdir target\apidocs
mkdir src\main\java\org\gnu\glpk
mkdir src\c
copy *.java src\main\java\org\gnu\glpk
%SWIG%\swig.exe -DGLPKPRELOAD -I..\src -java -package org.gnu.glpk -o src/c/glpk_wrap.c -outdir src/main/java/org/gnu/glpk glpk.i
"%JAVA_HOME%\bin\javadoc.exe" -locale en_US -encoding UTF-8 -charset UTF-8 -docencoding UTF-8 -sourcepath ./src/main/java org.gnu.glpk -d ./target/apidocs
"%JAVA_HOME%\bin\jar.exe" cf glpk-java-javadoc.jar -C ./target/apidocs .
"%JAVA_HOME%\bin\jar.exe" cf glpk-java-sources.jar -C ./src/main/java .
cd src\main\java
dir /b /s *.java > ..\..\..\sources.txt
"%JAVA_HOME%\bin\javac.exe" -source 1.7 -target 1.7 -d ../../../target/classes @..\..\..\sources.txt
cd ..\..\..
"%JAVA_HOME%\bin\jar.exe" cf glpk-java.jar -C ./target/classes .
cd "%~dp0"
set INCLUDE=
set LIB=
call %HOME%\vcvarsall.bat x86_amd64
call %SDK%\bin\x86\rc.exe glpk_java_dll.rc
set INCLUDE=%INCLUDE%;%JAVA_HOME%\include;%JAVA_HOME%\include\win32
%HOME%\bin\nmake.exe /f Makefile_JNI_VC_DLL
copy ..\swig\*.jar .
%HOME%\bin\nmake.exe /f Makefile_JNI_VC_DLL check
path %path_build_jni%
set INCLUDE=
set LIB=
pause
