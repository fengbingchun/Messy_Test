////////////////////////////////////////////////////////////////////////////////
//
//  A simple C++ example program for testing the Visual Leak Detector.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

// Include Visual Leak Detector
#include <vld.h>

using namespace std;

int main (int argc, char *argv [])
{
    string *s = new string("Hello World!\n");

    cout << *s;

    //delete s;

    return 0;
}
