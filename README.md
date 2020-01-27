# source-sdk-2013 custom

This is my personal fork of the source sdk 2013, which I plan to mainly use as a testbed.

### Features

* CMake as the build-system which vastly improves workflow compared to VPC \[Done (for Linux only rn)\] 
* Improved shader compilation scripts and workflow, also WINE compatible \[Planned\]
* CI scripts for various CI systems (azure and appveyor) \[Planned\]
* Scripts for launching and installing the game, both command-line based and Qt based \[Planned\]
* Code quality improvements \[Planned\]
* Cross compile support for various platforms from Linux \[Planned\] (See the section below)
* Additions to mathlib, tier1, etc. \[Planned\]

### Cross Compile Support 

PLANNED, but not completed.

You will be able to cross compile for the following platforms:

Linux -> Windows (via MinGW)
Windows -> Linux (via WSL?)
Linux -> OSX (might not do this because OSX dropped 32-bit and opengl support)
