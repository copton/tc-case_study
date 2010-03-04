.PHONY: all clean depend distclean

all: module-all app-all
clean: module-clean app-clean
depend: module-depend
distclean: module-distclean

CFLAGS += -I$(ROOT)/src/operating_system/tinyos/ec_pal -I$(ROOT)/src/operating_system/tinyos -DEC_NUMBEROF_THREADS=3
include ../../../../mak/module.mak

ifdef CROSS
	DEPS=$(ROOT)/src/operating_system/tinyos/ec_pal/libec_pal.a $(ROOT)/src/operating_system/tinyos/empty/libempty.a $(ROOT)/src/infra/empty/libempty.a $(ROOT)/src/compiler/libcompiler.a
else
	LDFLAGS += -lpthread
	DEPS=$(ROOT)/src/operating_system/tinyos/ec_pal/libec_pal.a $(ROOT)/src/operating_system/tinyos/raw/libraw.a $(ROOT)/src/hardware_simulation/libhardware_simulation.a $(ROOT)/src/infra/infra/libinfra.a $(ROOT)/src/compiler/libcompiler.a
endif
include ../../../../mak/app.mak
