#! /bin/bash

echo "Note: new create build directory, and executable binary file in build"
echo ${PWD}
mkdir -p build
cd build
cmake ..
make