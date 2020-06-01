#
# Settings handling
#

'''

settings schema

{
    "sdk_path": ""
}

'''

import os, sys, json

sdk_path = ""
install_prefix = ""
mod = ""

def LoadSettings():
    try:
        with open("settings.json", "r") as fs:
            _settings = json.load(fs)
            global sdk_path
            sdk_path = os.path.abspath(_settings["sdk_path"])
            global mod
            mod = _settings["mod"]
    except:
        print("Failed to load settings.json. Make sure it exists and you're running from your mod directory.")
        exit(1)