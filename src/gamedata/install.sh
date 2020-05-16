#!/bin/bash

# Install script for various gamedata files

if [ -z $INSTALL_PREFIX ]; then
	INSTALL_PREFIX=$(cat prefix.txt)
fi

cp -v entities/* "$INSTALL_PREFIX/bin"
cp -v scripts/* "$INSTALL_PREFIX/"
