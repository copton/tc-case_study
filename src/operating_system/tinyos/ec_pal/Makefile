.PHONY: all clean depend distclean

all: module-all
clean: module-clean
depend: module-depend
distclean: module-distclean

CFLAGS += -I$(ROOT)/src/operating_system/tinyos -DEC_NUMBEROF_THREADS=3

include ../../../../mak/module.mak
