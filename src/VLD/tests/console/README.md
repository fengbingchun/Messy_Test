Visual Leak Detector Example Console Application
================================================

Example Program Using Visual Leak Detector in a Console Application


About The Example Program:
--------------------------
This is an example Visual C++ 6.0 console application project that
implements the Visual Leak Detector. 

The project actually contains two separate programs. A C program and a
C++ program. The C program is in main.c while the C++ program is in
main.cpp. You can select which one you want to build by selecting the
corresponding project configuration as the active configuration. The purpose
behind including both C and C++ versions is to demonstrate Visual Leak
Detector's compatibility with C's malloc and free as well as C++'s new and
delete.

To build the example project, simply open the project file and start a build.

After the project is built, running the program will display a simple
"Hello World!" message. But a small amount of memory (containing the
"Hello World!" string) will be leaked. If you run the program under the
Visual C++ debugger, you should see a memory leak report in the debug
output window after the program exits. The report will include detailed
stack traces of the calls that allocated the leaked memory blocks.

Double-clicking on a source file/line number in the stack trace will take you to
that file and line in the editor. This allows you to quickly see where in the
program the memory was allocated and how it got there.


Documentation:
--------------

See the [http://vld.codeplex.com/documentation](http://vld.codeplex.com/documentation) for the complete Visual Leak Detector documentation.
