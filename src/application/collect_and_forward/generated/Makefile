.PHONY: all clean depend distclean

all: module-all app-all
clean: module-clean app-clean
depend: module-depend
distclean: module-distclean

CFLAGS = -I$(ROOT)/src/operating_system/tinyos/tc_pal -I$(ROOT)/src/operating_system/tinyos
include ../../../../mak/module.mak

LDFLAGS=-lpthread
DEPS=$(ROOT)/src/operating_system/tinyos/tc_pal/libtc_pal.a $(ROOT)/src/operating_system/tinyos/raw/libraw.a $(ROOT)/src/hardware_simulation/libhardware_simulation.a $(ROOT)/src/infra/libinfra.a 
include ../../../../mak/app.mak
