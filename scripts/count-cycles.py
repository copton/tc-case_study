#!/usr/bin/env python

import fileinput
import re
import sys

cycles = {
 'rcall' : 3,
 'ldd' : 2,
 'ldi' : 1,
 'pop' : 2,
 'lds' : 3,
 'lsr' : 1,
 'in' : 1,
 'ror' : 1,
 'sbci' : 1,
 'subi' : 1,
 'ld' : 2,
 'cp' : 1,
 'andi' : 1,
 'out' : 1,
 'rjmp' : 2,
 'adiw' : 2,
 'mov' : 1,
 'brne' : 1.5,
 'std' : 2,
 'cpi' : 1,
 'brcs' : 1.5,
 'cpc' : 1,
 'st' : 2,
 'brge' : 1.5,
 'eor' : 1,
 'sts' : 3,
 'push' : 2,
 'sbiw' : 2,
 'or' : 1,
 'breq' : 1.5,
 'add' : 1,
 'adc' : 1,
 'sub' : 1,
 'sbc' : 1,
 'brlt' : 1.5,
 'ret' : 4,
 'cli' : 1,
 'icall' : 3,
 'lpm' : 3,
}


class Process(object):
    def __init__(self):
        self.function_begin = re.compile(r"^[0-9a-f]+ <([^>]*)>:\n$")
        self.command = re.compile(r"^\s*[0-9a-f]+:\s*([0-9a-f]{2} )+\s*([a-z]+).*\n$")
        self.current = None
        self.mnemonics = { }

    def __call__(self, line):
        mo = self.function_begin.match(line)
        if mo:
            function = mo.group(1)
#            print "counting cycles for function", function
            self.current = { }
            self.mnemonics[function] = self.current
            return
    
        if line == "\n":
            self.current = None
            return
    
        if self.current != None:
            mo = self.command.match(line)
            if mo:
                mnemonic = mo.group(2)
                if self.current.has_key(mnemonic):
                    self.current[mnemonic] += 1
                else:
                    self.current[mnemonic] = 1

    def stats(self):
        out = []
        def sum(d):
            result = 0
            for mnemonic, count in d.iteritems():
                result += cycles[mnemonic] * count
            return result

        for function, d in self.mnemonics.iteritems():
            out.append((function, sum(d)))

        out.sort()

        sys.stdout.write("function, total cycles\n")
        for pair in out:
            sys.stdout.write("%s, %d\n" % pair)

process = Process()
for line in fileinput.input():
    process(line)

process.stats()
