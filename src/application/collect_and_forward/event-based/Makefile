.PHONY: all clean depend distclean

all: module-all app-all
clean: module-clean app-clean
depend: module-depend
distclean: module-distclean

CFLAGS = -I$(ROOT)/src/operating_system/tinyos/emulation
include ../../../../mak/module.mak

LDFLAGS=-lpthread
DEPS=$(ROOT)/src/operating_system/tinyos/emulation/libemulation.a $(ROOT)/src/lib/liblib.a
include ../../../../mak/app.mak
