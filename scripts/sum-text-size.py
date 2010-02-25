#!/usr/bin/env python

import fileinput
import re
import sys

from function_deco import FunctionDeco

class Process(object):
    def __init__(self):
        self.function_begin = re.compile(r"^[0-9a-f]+ <([^>]*)>:\n$")
        self.command = re.compile(r"^\s*[0-9a-f]+:\s*(([0-9a-f]{2} )+)\s*([a-z]+).*\n$")
        self.current = None
        self.sums = { }
        self.total = 0
        self.deco = FunctionDeco()

    def __call__(self, line):
        mo = self.function_begin.match(line)
        if mo:
            function = mo.group(1)
#            print "summing up for function", function
            self.current = self.deco.getDecoName(function)
            self.sums[self.current] = 0
            return
    
        if line == "\n":
            self.current = None
            return
    
        if self.current != None:
            mo = self.command.match(line)
            size = len(mo.group(1))
            assert size % 3 == 0, "'%s'" % mo.group(1)
            numberofBytes = size / 3
            self.sums[self.current] += numberofBytes
            self.total += numberofBytes

    def dump_stats(self):
        out = []

        for function, sum in self.sums.iteritems():
            out.append((function, sum))

        out.sort()

        sys.stdout.write("function, size\n")
        for pair in out:
            sys.stdout.write("%s, %d\n" % pair)

    def dump_total(self):
        sys.stdout.write("total, " + str(self.total) + "\n")

process = Process()
for line in fileinput.input(sys.argv[1]):
    process(line)

if len(sys.argv) > 2 and sys.argv[2] == "-t":
    process.dump_total()
else:
    process.dump_stats()
