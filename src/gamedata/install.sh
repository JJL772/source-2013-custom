#!/bin/bash

# Install script for various gamedata files
pushd `dirname $0`
source ../env.sh 

cp -v entities/* "$INSTALL_PREFIX/bin"
cp -v scripts/* "$INSTALL_PREFIX/"
popd
