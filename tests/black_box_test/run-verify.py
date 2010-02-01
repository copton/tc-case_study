#!/usr/bin/env python

import framework
from config import Config
import pickle

f = open(Config.logfile, "r")
log = pickle.load(f)
f.close()

framework.verify(log)
