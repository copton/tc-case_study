.PHONY: all clean depend distclean

ifdef MEASURE
all: module-all
else
all: module-all app-all
endif
clean: module-clean app-clean
depend: module-depend
distclean: module-distclean

CFLAGS = -I$(ROOT)/src/operating_system/tinyos/raw
include ../../../../mak/module.mak

ifdef MEASURE
	DEPS=$(ROOT)/src/operating_system/tinyos/empty/libempty.a $(ROOT)/src/infra/libinfra.a
else
	LDFLAGS=-lpthread
	DEPS=$(ROOT)/src/operating_system/tinyos/raw/libraw.a $(ROOT)/src/hardware_simulation/libhardware_simulation.a $(ROOT)/src/infra/libinfra.a
endif
include ../../../../mak/app.mak
