#!/bin/bash

source env.sh 

pushd "$INSTALL_PREFIX"

./launch.sh 

popd 
