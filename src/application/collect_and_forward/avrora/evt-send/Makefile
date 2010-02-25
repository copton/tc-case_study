.PHONY: all clean depend distclean

all: module-all app-all
clean: module-clean app-clean
depend: module-depend
distclean: module-distclean

CFLAGS += -I$(ROOT)/src/operating_system/tinyos/raw -I$(ROOT)/src/application/collect_and_forward/
include ../../../../../mak/module.mak

ifdef MEASURE
	DEPS=$(ROOT)/src/operating_system/tinyos/empty/libempty.a $(ROOT)/src/infra/empty/libempty.a
else
	LDFLAGS += -lpthread
	DEPS=$(ROOT)/src/operating_system/tinyos/raw/libraw.a $(ROOT)/src/hardware_simulation/libhardware_simulation.a $(ROOT)/src/infra/infra/libinfra.a
endif
include ../../../../../mak/app.mak
