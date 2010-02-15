#!/usr/bin/env python

import sys
import getopt
import traceback
import sys

import record
import verify

def usage(whatswrong=None):
    sys.stderr.write("usage: %s: -t test_case (-r|-v) [-h] [-- <test case parameters>]\n" % sys.argv[0])
    sys.stderr.write("-r: record\n")
    sys.stderr.write("-v: verify\n")
    sys.stderr.write("-h: help\n")
    if whatswrong:
        sys.stderr.write(whatswrong + "\n")
    sys.exit(1)


def run():
    main_options = "t:hrv"
    opts,args = getopt.getopt(sys.argv[1:], main_options)

    test = None
    command = None
    help = False
    for option, value in opts:
        if option == "-h":
            help = True
        elif option == "-t":
            test = value
        elif option == "-r":
            if command != None:
                usage("-r conflicts with -v")
            command = record.cmd
        elif option == "-v":
            if command != None:
                usage("-v conflicts with -r")
            command = verify.cmd

    if test == None:
        usage("-t not given")

    if command == None:
        usage("neither -r nor -v given")

    if help:
        usage()

    test_main = load_code("test_cases." + test + ".main")
    test_main.setArgs(args)

    command(test_main)

    sys.stdout.write("all done\n")

def load_code(path):
    parts = path.split('.')
    module_name = '.'.join(parts[:-1])
    attribute_name = parts[-1]
 
    try:
        module = __import__(module_name, {}, {}, [attribute_name], level=0)
        return getattr(module, parts[-1])
    except ImportError, e:
        raise ImportError("failed to import '%s':\n%s" % (module_name, traceback.format_exc()))
    except AttributeError, e:
        raise ImportError("attribute '%s' not found in '%s':\n%s" % (attribute_name, module_name, traceback.format_exc()))

run()
