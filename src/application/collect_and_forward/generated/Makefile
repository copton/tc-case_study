.PHONY: all clean depend distclean

all: module-all app-all
clean: module-clean app-clean
depend: module-depend
distclean: module-distclean

DEPS=app-ec.o

app-ec.o: app-ec.o

app-ec.c: app-tc.c
	ocram -c "$(CFLAGS)" -i $< -o $@

CFLAGS += -I$(ROOT)/src/operating_system/tinyos/threads
include ../../../../mak/module.mak

ifdef CROSS
	LDFLAGS += -u ec_events
	DEPS+=$(ROOT)/src/operating_system/tinyos/empty/libempty.a $(ROOT)/src/infra/empty/libempty.a $(ROOT)/src/compiler/libcompiler.a
else
	LDFLAGS += -lpthread -u ec_events
	DEPS+=$(ROOT)/src/operating_system/tinyos/raw/libraw.a $(ROOT)/src/hardware_simulation/libhardware_simulation.a $(ROOT)/src/infra/infra/libinfra.a $(ROOT)/src/compiler/libcompiler.a
endif
include ../../../../mak/app.mak
