#!/bin/bash
pushd "`dirname $0`/build"
source env.sh

# Forces a relink
find . -iname "*.o" | xargs touch 
make -j$JOBS && make install 

popd 
