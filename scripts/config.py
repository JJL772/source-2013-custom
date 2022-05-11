#!/usr/bin/python3

import configparser
import sys
import os

class Config():
	def __init__(self):
		self.cfg = configparser.ConfigParser()
		self.cfg.read('config.ini')
		self.hl2_path = self.cfg['paths']['hl2']
		self.sdk2013_path = self.cfg['paths']['sdk2013mp']
		self.mod = self.cfg['mod']['name']
		
		if sys.platform.startswith('linux'):
			self.vrad = os.path.abspath(self.cfg['compilers']['vrad_linux'])
			self.vvis = os.path.abspath(self.cfg['compilers']['vvis_linux'])
			self.vbsp = os.path.abspath(self.cfg['compilers']['vbsp_linux'])
		else:
			self.vrad = os.path.abspath(self.cfg['compilers']['vrad_windows'])
			self.vvis = os.path.abspath(self.cfg['compilers']['vvis_windows'])
			self.vbsp = os.path.abspath(self.cfg['compilers']['vbsp_windows'])