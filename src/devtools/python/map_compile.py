#!/usr/bin/env python3

#
# Utility script to batch compile all maps in the maps/ directory
#
# Configs should be named the same as the map they're configuring for
# e.g. CoolMap.vmf should have a corresponding CoolMap.json as a config
#
'''
Schema for the JSON is as follows:

[
    {
        "config": "fast",
        "vbsp-flags": [

        ],
        "vrad-flags": [

        ],
        "vvis-flags": [

        ]
    }
]


'''

import os, json, sys, subprocess, argparse, platform, shutil
from os.path import basename
import settings

if platform.system() == "Linux" or platform.system() == "Darwin":
    vbsp_exe = "vbsp"
    vrad_exe = "vrad_launcher"
    vvis_exe = "vvis_launcher"
else:
    vbsp_exe = "vbsp.exe"
    vrad_exe = "vrad.exe"
    vvis_exe = "vvis.exe"

def main():
    settings.LoadSettings()

    # Now that we have loaded settings, let's fix the LD_LIBRARY_PATH
    myenv = os.environ.copy()
    myenv["LD_LIBRARY_PATH"] = settings.sdk_path + "/bin/"

    config = None

    for arg in sys.argv:
        if arg.startswith("--config="):
            config = arg.replace("--config=", "")

    if config is None:
        print("Config must be specified using --config.")
        print("USAGE: map_compile.py --config=<fast|full|hdr>")
        exit(1)

    for file in os.listdir(os.getcwd() + "/mapsrc/"):
        if not file.endswith(".vmf"):
            continue
        file = os.getcwd() + "/mapsrc/" + file
        bspfile = file.replace(".vmf", ".bsp")
        print("\n\nCompiling {0}\n\n".format(file))

        basefile = os.path.basename(file).replace(".vmf", "")

        vbsp_flags = []
        vrad_flags = []
        vvis_flags = []

        # Load the config json
        _conf = {}
        try:
            with open(os.getcwd() + "/mapsrc/" + basefile + ".json", "r") as fs:
                _conf = json.load(fs)

            # Set the compile flags
            try:
                vbsp_flags = _conf[config]["vbsp-flags"]
                vrad_flags = _conf[config]["vrad-flags"]
                vvis_flags = _conf[config]["vvis-flags"]
            except:
                print("Config does not exist!")
                exit(1)
        except:
            print("Config does not exist, using default settings...")

        # Run VBSP
        vbsp_flags.insert(0, os.getcwd() + "/../bin/" + vbsp_exe)
        vbsp_flags.append(file)

        # Exec vbsp
        print("\n\n==== Running VBSP on {0} ====\n\n".format(file))
        res = subprocess.call(vbsp_flags, env=myenv)

        if res != 0:
            print("\n\nCompilation for {0} failed!!\n\n".format(file))
            continue

        # Run VRAD
        vrad_flags.insert(0, os.getcwd() + "/../bin/" + vrad_exe)
        vrad_flags.append(bspfile)
        print("\n\n==== Running VRAD on {0} ====\n\n".format(file))
        res = subprocess.call(vrad_flags, env=myenv)

        if res != 0:
            print("\n\nVRAD failed for {0}!\n\n".format(file))
            continue

        # Run VVIS
        vvis_flags.insert(0, os.getcwd() + "/../bin/" + vvis_exe)
        vvis_flags.append(bspfile)

        print("\n\n==== Running VVIS on {0} ====\n\n".format(file))
        res = subprocess.call(vvis_flags, env=myenv)

        if res != 0:
            print("\n\nVVIS failed for {0}!\n\n".format(file))
            continue

        # Now that it's done, let's move it from mapsrc to maps
        shutil.move(os.getcwd() + "/mapsrc/" + basefile.lower() + ".bsp", os.getcwd() + "/maps/" + basefile + ".bsp")

if __name__ == "__main__":
    main()