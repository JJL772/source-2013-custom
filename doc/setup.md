# Setup

Setting everything up in this fork is pretty easy!

## Configuring the Environment

I've put a simple environment script named `env.sh` in `src/`. Make sure to change the directories in there to what they should be, or else some scripts won't be able to install stuff properly. 

Example of env.sh:
```bash
export INSTALL_PREFIX="$HOME/Desktop/Projects/Source-Playground/game" 

# Number of jobs to run make with (only done when running some of the provided scripts)
export JOBS=8
```

## Setting up Links

I usually run the game by setting up various symlinks in the `game/` directory.

The script `setup-game.sh` will do this for you. To use this script, set the environment variable `SOURCE_SDK_2013_MP` in your current shell like so:

```bash
export SOURCE_SDK_2013_MP="/home/jeremy/.steam/steam/steamapps/common/Source SDK Base 2013 Multiplayer/"
```

If not set, it will fallback to `~/.steam/steam/steamapps/common/Source SDK Base 2013 Multiplayer/`.

Now just run it, and it should create the required links.

## Building

Building is done using CMake, which is pretty straightforward.

```bash
mkdir src/build && cd src/build

cmake ../ -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_INSTALL_PREFIX=/your/build/prefix
```

It might complain about not being able to find various libraries. It's up to you to find and install the proper packages, I will assemble a list here at a later date.

Now, to build and install to the prefix, run:
```bash
make -j4 && make install
```

## Running

To run the game, you can use one of the scripts in the root directory, such as `run-linux32.sh` or you can run it by `cd`ing to `game/` and running `launch.sh`.

## Util Scripts

in `src/` there are some utility scripts that you can use to do some things.

`relink-linux32.sh` will force relink the game, without rebuilding all objects. 

`build-linux32.sh` will build everything and install it

`build-run-linux32.sh` will build and run everything

`relink-run-linux32.sh` will relink and run everything

`configure-linux32.sh` will reconfigure the project, but it will not remove the `build` directory.
