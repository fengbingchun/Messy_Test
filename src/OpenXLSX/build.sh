#! /bin/bash

if [ $HOSTTYPE != "x86_64" ]; then
    echo_error "only support x86_64 architecture: current architecture: $HOSTTYPE"
fi

if [[ "$OSTYPE" != "msys" ]] && [[ "$OSTYPE" != "cygwin" ]]; then
    echo_error "unsupported platform: $OSTYPE"
    exit -1
fi

result_judgment()
{
    rc=$?
    if [[ ${rc} != 0 ]]; then
        echo -e "\033[0;31mError: there are some errors in the above operation, please check: ${rc}\033[0m"
        exit ${rc}
    fi
}

echo_error()
{
    echo -e "\033[0;31mError: $1\033[0m"
}

if [ $# != 1 ]; then
    echo_error "requires a parameter: Release or Debug\n  For example: $0 Debug"
    exit -1
fi

if [ $1 != "Release"  ] && [ $1 != "Debug" ]; then
    echo_error "the parameter can only be Release or Debug"
    exit -1
fi

mkdir -p build && cd build

cmake \
    -G"Visual Studio 17 2022" -A x64 \
    -DCMAKE_BUILD_TYPE=$1 \
    -DCMAKE_CONFIGURATION_TYPES=$1 \
    -DCMAKE_INSTALL_PREFIX=../install/$1 \
    ..
result_judgment

cmake --build . --target install --config $1
result_judgment
cd ../

mkdir -p install/$1/include/external
cp -a OpenXLSX/external/pugixml install/$1/include/external

echo -e "\033[0;32mbuild completed\033[0m"
