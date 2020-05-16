#!/bin/bash

source env.sh 
pushd "`dirname $0`/build/"

make -j$JOBS && make install

cd "$INSTALL_PREFIX"
./launch.sh

popd 
