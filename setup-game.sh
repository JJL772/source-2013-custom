#!/bin/bash

# Creates various game links

if [ -z $SOURCE_SDK_2013_MP ]; then 
	export SOURCE_SDK_2013_MP="/media/ExtraDisk/SteamLibrary/steamapps/common/Source SDK Base 2013 Multiplayer"
fi


ln -s "$SOURCE_SDK_2013_MP/bin" "$PWD/game/bin"
ln -s "$SOURCE_SDK_2013_MP/hl2" "$PWD/game/hl2"
ln -s "$SOURCE_SDK_2013_MP/hl2mp" "$PWD/game/hl2mp"
ln -s "$SOURCE_SDK_2013_MP/hl2_linux" "$PWD/game/hl2_linux" 
ln -s "$SOURCE_SDK_2013_MP/platform" "$PWD/game/platform"
ln -s "$SOURCE_SDK_2013_MP/hl2.sh" "$PWD/game/hl2.sh"
ln -s "$SOURCE_SDK_2013_MP/sdktools" "$PWD/game/sdktools"
ln -s "$SOURCE_SDK_2013_MP/sourcetest" "$PWD/game/sourcetest"
ln -s "$SOURCE_SDK_2013_MP/steam_appid.txt" "$PWD/game/steam_appid.txt"
