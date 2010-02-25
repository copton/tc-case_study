#!/usr/bin/env python

# feed this script with the output of
# java avrora.Main -monitors=calls -seconds=5 <test case>

import fileinput
import re
import sys

class Process():
    def __init__(self):
        self.begin = "------------------------------------------------------------------------------\n"
        self.end = "==============================================================================\n"
        self.state = 0
        self.first = None
        self.last = None

    def __call__(self, line):
        if self.state == 0:
            if line == self.begin:
                self.state = 1
        elif self.state == 1:
            parts = re.split("\s*", line)
            self.first = int(parts[2])
            self.state = 2
        elif self.state == 2:
            if line == self.end:
                self.state = 3
            else:
                parts = re.split("\s*", line)
                self.last = int(parts[2])
        else:
            pass

    def dump_stats(self):
        sys.stdout.write(str(self.last - self.first) + "\n")

process = Process()
for line in fileinput.input():
	process(line)

process.dump_stats()
