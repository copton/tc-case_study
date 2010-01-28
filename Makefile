export ROOT=$(shell pwd)

DIRS=configuration implementation
include mak/recurse.mak
