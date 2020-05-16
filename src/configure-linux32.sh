#!/bin/bash

pushd "`dirname $0`"
source env.sh 
[ ! -d build ] && mkdir build
cd build

cmake ../ -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX"

popd 
