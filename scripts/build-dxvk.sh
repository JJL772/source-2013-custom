#!/bin/bash

TOP=$(cd $(dirname $0);pwd)
cd "$TOP/../src/thirdparty/dxvk-native"

branch=$(git branch --show-current)
if [[ "$branch" != "legacy-source-compat" ]]; then
	git checkout legacy-source-compat
fi

export CXX="g++ -m32"
export CC="gcc -m32"

rm -rf build || true
meson --buildtype release build
pushd build > /dev/null
ninja
popd > /dev/null

cp build/src/d3d9/libdxvk_d3d9.so ../../lib/common/linux32/
cp build/src/dxgi/libdxvk_dxgi.so ../../lib/common/linux32/