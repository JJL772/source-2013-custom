#!/bin/bash

# Compiles and installs materials using vtex
# For this to work, you'll need everything in materialsrc/ to correspond to your materials/ directory
#
# How it works...
# materialsrc/models/alyx/alyx_c.tga materials/models/alyx/alyx_c.vtf
# 
# Initially we check the time at which both files are modified. If alyx_c.tga has been modified later than alyx_c.tga, 
#  then we go ahead and convert alyx_c.tga to alyx_c.vtf again. 
#  The same goes for any VMTs in the materialsrc directory
#
# 
