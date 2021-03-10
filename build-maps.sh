#!/bin/bash

TOP=$(cd $(dirname $0);pwd)
cd "$TOP/content"

python3 ../scripts/map_build.py $@