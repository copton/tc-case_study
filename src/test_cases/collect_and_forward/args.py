from getopt import getopt

class Args(object):
    application = None

def setArgs(args):
    opts, args = getopt(args, "a:")
    for option, value in opts:
        if option == "-a":
            Args.application = value
