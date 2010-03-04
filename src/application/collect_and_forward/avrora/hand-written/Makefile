.PHONY: all clean depend distclean od

all: module-all app-all od
clean: module-clean app-clean
	rm -f $(OD_FILE)
depend: module-depend
distclean: module-distclean

CFLAGS += -I$(ROOT)/src/operating_system/tinyos/ -I$(ROOT)/src/application/collect_and_forward/
include ../../../../../mak/module.mak

DEPS=$(foreach task, collect receive send, $(ROOT)/src/application/collect_and_forward/hand-written/$(task).o)
DEPS += $(ROOT)/src/operating_system/tinyos/mockup/libmockup.a
ifdef CROSS
	DEPS += $(ROOT)/src/infra/empty/libempty.a
else
	DEPS += $(ROOT)/src/infra/infra/libinfra.a
endif
include ../../../../../mak/app.mak

OD_FILE=$(APP).od
OBJDUMP=$(TOOLCHAIN)/$(CC_PREFIX)objdump
od: $(OD_FILE)

%.od: %
	$(OBJDUMP) -zhD $^ > $@ || rm $@
	
