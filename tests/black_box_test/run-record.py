#!/usr/bin/env python

import sys
import framework
from config import Config
import shutil
import os
import pickle

if len(sys.argv) != 2:
    sys.stderr.write("usage: %s <application>\n" % sys.argv[0])
    sys.exit(1)

shutil.rmtree(Config.path, ignore_errors=True)
os.makedirs(Config.path)

f = open(Config.logfile, "w")
log = framework.record(sys.argv[1])
pickle.dump(log, f)
f.close()
