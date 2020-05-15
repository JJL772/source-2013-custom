#!/bin/bash

[ -d $PWD/build ] && rm -rf build 

# Change this if you want
[ -z $BUILD_CHROOT ] && BUILD_CHROOT="build-chroot";

mkdir build

schroot -c $BUILD_CHROOT -d $PWD/build 

cmake ../ -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_INSTALL_PREFIX=../../game 

make -j4  && make install
