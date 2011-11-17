.PHONY: all clean depend distclean

all: module-all app-all
clean: module-clean app-clean
	rm -f app-ec.c
depend: module-depend
distclean: module-distclean

app-ec.o: app-ec.c

app-ec.c: ../thread-based/app.c
	ocram -c "$(CPPFLAGS) -DOCRAM_MODE" -i $< -o $@ || (rm $@; exit 1)

DEPS=app-ec.o

CPPFLAGS += -I$(ROOT)/src/operating_system/tinyos/threads -I$(ROOT)/src/application/collect_and_forward/thread-based
include ../../../../mak/module.mak

ifdef CROSS
	DEPS+=$(ROOT)/src/operating_system/tinyos/empty/libempty.a $(ROOT)/src/infra/empty/libempty.a $(ROOT)/src/compiler/libcompiler.a
else
	DEPS+=$(ROOT)/src/operating_system/tinyos/raw/libraw.a $(ROOT)/src/hardware_simulation/libhardware_simulation.a $(ROOT)/src/infra/infra/libinfra.a $(ROOT)/src/compiler/libcompiler.a
endif
include ../../../../mak/app.mak
