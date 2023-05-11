#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"
./run-docker.sh cmake . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -GNinja -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32 
