#!/usr/bin/env bash

cd "$(dirname "$0")"

export LD_PRELOAD="$PWD/bin/libtogl.so"
export LD_LIBRARY_PATH="$PWD/bin"
./hl2_linux -game mod_hl2mp -dev +sv_cheats 1 +map sdk_vehicles
