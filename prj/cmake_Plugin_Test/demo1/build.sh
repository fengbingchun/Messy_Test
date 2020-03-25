#! /bin/bash

usage() {
    echo "usage: $0 param"
    echo "if build plugin, then execute: $0 0"
    echo "if build src and test, then execute: $0 1"
    exit -1
}

if [ $# != 1 ]; then
    usage
fi

real_path=$(realpath $0)
echo "real_path: ${real_path}"
dir_name=`dirname "${real_path}"`
echo "dir_name: ${dir_name}"

build_dir=${dir_name}/build
mkdir -p ${build_dir}
cd ${build_dir}
if [ "$(ls -A ${build_dir})" ]; then
	echo "directory is not empty: ${build_dir}"
else
	echo "directory is empty: ${build_dir}"
fi

platform=`uname`
echo "##### current platform: ${platform}"

if [ ${platform} == "Linux" ]; then
    if [ $1 == 0 ]; then
        echo "########## build plugin ##########"
        cmake -DBUILD_PLUGIN=ON ..
    elif [ $1 == 1 ]; then
        echo "########## build src and test ##########"
        cmake -DBUILD_PLUGIN=OFF ..
    else
        usage
    fi

    make
else
    if [ $1 == 0 ]; then
        echo "########## build plugin ##########"
        cmake -G"Visual Studio 15 2017" -A x64 -DBUILD_PLUGIN=ON ..
    elif [ $1 == 1 ]; then
        echo "########## build src and test ##########"
        cmake -G"Visual Studio 15 2017" -A x64 -DBUILD_PLUGIN=OFF ..
    else
        usage
    fi

    cmake --build . --target ALL_BUILD --config Release
fi

cd -