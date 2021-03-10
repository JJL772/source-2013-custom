#!/usr/bin/python3

# Builds maps
# NOTES:
# 	- Must be run from content/

import json
import os
import sys
import configparser
import config
import argparse
import multiprocessing
import subprocess
import shutil

argparser = argparse.ArgumentParser(description="Batch compiles all maps")
argparser.add_argument('--force', action='store_true', dest='FORCE', help='Forces rebuild of all maps')
argparser.add_argument('--final', action='store_true', dest='FINAL', help='Final release map compile')
argparser.add_argument('--threads', type=int, dest='THREADS', default=multiprocessing.cpu_count(), help='Number of threads to build maps with')
argparser.add_argument('--low', action='store_true', dest='LOW', help='Build in low priority mode')
argparser.add_argument('--fast', action='store_true', dest='FAST', help='Fast map build')
argparser.add_argument('--no-hdr', action='store_true', dest='NO_HDR', help='Disable HDR for vrad')
argparser.add_argument('--dry-run', action='store_true', dest='DRY_RUN', help='Dry run only')
args = argparser.parse_args()

cfg = config.Config()

class VRad():
	def __init__(self):
		self.args = [cfg.vrad]
		if args.FINAL:
			self.args.append('-final')
		self.args.append('-threads')
		self.args.append(str(args.THREADS))
		if args.LOW:
			self.args.append('-low')
		if args.FAST:
			self.args.append('-fast')
		if not args.NO_HDR:
			self.args.append('-hdr')
			
	def run(self, map, extra_args: list) -> int:
		_args = self.args
		_args += extra_args
		_args.append(map)
		if args.DRY_RUN:
			print(_args)
			return 0
		else:
			print(_args)
			res = subprocess.run(_args)
			return res.returncode

	
class VVis():
	def __init__(self):
		self.args = [cfg.vvis]
		self.args.append('-threads')
		self.args.append(str(args.THREADS))
		if args.LOW:
			self.args.append('-low')
		if args.FAST:
			self.args.append('-fast')

	def run(self, map, extra_args: list) -> int:
		_args = self.args
		_args += extra_args
		_args.append(map)
		if args.DRY_RUN:
			print(_args)
			return 0
		else:
			print(_args)
			res = subprocess.run(_args)
			return res.returncode

	
class VBsp():
	def __init__(self):
		self.args = [cfg.vbsp]
		if args.LOW:
			self.args.append('-low')
			
	def run(self, map, extra_args: list) -> int:
		_args = self.args
		_args += extra_args
		_args.append(map)
		if args.DRY_RUN:
			print(_args)
			return 0
		else:
			print(_args)
			res = subprocess.run(_args)
			return res.returncode


class App():
	def __init__(self):
		self.vvis = VVis()
		self.vrad = VRad()
		self.vbsp = VBsp()
	
	# Checks if we should compile the map or not and updates the manifest
	def should_compile_map(self, map) -> bool:
		if args.FORCE:
			return True
		try:
			m = self.manifest[map]
			nt = os.path.getmtime(map)
			if m < nt:
				self.manifest[map] = nt
				return True
			return False
		except:
			self.manifest[map] = os.path.getmtime(map)
			return True
			
	def save_manifest(self):
		with open("maps.manifest", "w") as fp:
			for m, t in dict(self.manifest).items():
				fp.write("{0} {1}\n".format(m, t))
	
	# Fun stuff incoming: need to properly configure the LD_LIBRARY_PATH and cwd for vbsp to work
	def setup_paths(self):
		if not sys.platform.startswith('linux'):
			return # Windows doesn't need this
		os.environ['LD_LIBRARY_PATH'] = os.path.abspath('../game/bin/')
		
	def run(self):
		# Parse the maps json
		with open("maps.json", "r") as fp:
			self.maps = json.load(fp)
		
		# Read the manifest now
		self.manifest = {}
		if os.path.exists("maps.manifest"):
			with open("maps.manifest", "r") as fp:
				for line in fp.readlines():
					s = line.split(' ')
					self.manifest[s[0]] = float(s[1])
					
		# Setup LD_LIBRARY_PATH
		self.setup_paths()
					
		# Now let's build everything
		for map in self.maps:
			m = os.path.abspath(map['file'])
			bsp = str(m).replace('.vmf', '.bsp')
			vra = map['vrad_args'] + ['-game', cfg.mod]
			vba = map['vbsp_args'] + ['-game', cfg.mod]
			vva = map['vvis_args'] + ['-game', cfg.mod]
			pcwd = os.getcwd()
			os.chdir('../game/')
			if not self.should_compile_map(m):
				print("Map '{0}' up to date".format(m))
				continue
			if self.vbsp.run(m, vba) != 0:
				print("Map compile failed!")
				exit(1)
			if self.vrad.run(bsp, vra) != 0:
				print("VRad failed!")
				exit(1)
			if self.vvis.run(bsp, vva) != 0:
				print("VVis failed!")
				exit(1)
			os.chdir(pcwd)
			# Copy to the mod
			print("Copying '{0}' into mod '{1}'".format(bsp, cfg.mod))
			shutil.copy(bsp, os.path.abspath('../game/{0}/maps/'.format(cfg.mod)))
			print("Finished map {0}".format(m))
			
		self.save_manifest()
			
				
	
if __name__ == "__main__":
	app = App()
	app.run()

