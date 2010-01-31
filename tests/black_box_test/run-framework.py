#!/usr/bin/env python

import sys
import framework

if len(sys.argv) != 2:
    sys.stderr.write("usage: %s <application>\n" % sys.argv[0])
    sys.exit(1)

framework.run(sys.argv[1])
