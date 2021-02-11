#!/bin/bash
set -e 
TOP=$(cd $(dirname $0);pwd)
cd "$TOP"

cd src

if [ ! -d build/ ]; then
    ./configure-linux32.sh
fi

cd build

time make install $@