#! /bin/bash

if [ $# != 2 ]; then
    echo "Error: requires two parameters: 1: dynamic or static; 2: Relese or Debug"
    echo "For example: dynamic library, debug mode: $0  dynamic Debug"
    exit -1
fi

if [ $1 != "dynamic" ] && [ $1 != "static" ]; then
    echo "Error: the first parameter can only be dynamic or static"
    exit -1
fi

if [ $2 != "Release"  ] && [ $2 != "Debug" ]; then
    echo "Error: the second parameter can only be Release or Debug"
    exit -1
fi

if [[ ! -d "build" ]]; then
    mkdir build
    cd build
else
    cd build
fi

dynamic_flag=ON
if [ $1 != "dynamic" ]; then
    dynamic_flag=OFF
fi

echo "build: $1 $2"

# vs2022, PostgreSQL 16.4
 cmake \
    -G"Visual Studio 17 2022" -A x64 \
    -DPostgreSQL_ROOT="D:/ProgramFiles/PostgreSQL/16" \
    -DCMAKE_BUILD_TYPE=$2 \
    -DCMAKE_CONFIGURATION_TYPES=$2 \
    -DBUILD_SHARED_LIBS=${dynamic_flag} \
    -DCMAKE_INSTALL_PREFIX=./install \
    ..
make -j2
cmake --build . --target install --config $2
