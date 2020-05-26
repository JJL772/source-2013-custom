#!/bin/bash

# Compiles all maps in the mapsrc directory

# Optionally override root with GAME_ROOT var
[ ! -z $GAME_ROOT ] && ROOT="$GAME_ROOT"
[ -z $MOD ] && MOD=mod_hl2mp && echo "MOD env var not set, defaulting to mod_hl2mp"

# A little bit of a hack to determine the full path to the script
pushd "$(dirname $0)/../" > /dev/null
ROOT="$(pwd -P)"
echo "ROOT=$ROOT"
popd > /dev/null
#ROOT="$HOME/Desktop/Projects/Source-Playground/game/"
#MOD=mod_hl2mp

MAPS=$(find "$PWD/mapsrc" -iname "*.vmf")

pushd "$ROOT" > /dev/null || exit 1 

# Fixup the LD_LIBRARY_PATH
export LD_LIBRARY_PATH="$ROOT/bin/:$LD_LIBRARY_PATH"

# Param1: Map name
# Param2: Out name
function build_map(){
	echo "Building map $1"

	# TODO: Check file times

	VBSP_FLAGS="-game $MOD "
	VRAD_FLAGS="-game $MOD -StaticPropLighting"
	VVIS_FLAGS="-game $MOD "
	echo $PWD
	echo "Running vbsp.."
	"./bin/vbsp" $VBSP_FLAGS "$1"

	"./bin/vrad_launcher" $VRAD_FLAGS "$2"

        "./bin/vvis_launcher" $VVIS_FLAGS "$2"
        
        # Remove previous file if it exists
        #[ -f "$ROOT/$MOD/maps/$2" ] && rm -f "$ROOT/$MOD/maps/$2" 

        # Move the file to the maps directory (and fix any casing issues)
        mv -f "$ROOT/$MOD/mapsrc/$(basename $2 | tr '[:upper:]' '[:lower:]')" "$ROOT/$MOD/maps/$(basename $2)"
}

for map in $MAPS; do
	build_map $map $(echo $map | sed "s/\.vmf/\.bsp/")
done

popd > /dev/null 
