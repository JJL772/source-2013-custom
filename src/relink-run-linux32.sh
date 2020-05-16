#!/bin/bash

# Forces relink and runs game

pushd "`dirname $0`/build"
source env.sh
make -j$JOBS && make install

cd "$INSTALL_PREFIX"

./launch.sh

popd
