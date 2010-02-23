.PHONY: module-depend module-all module-clean module-distclean

-include depend.mak

ifdef MEASURE
	CFLAGS += -O0 -DNDEBUG
else
	CFLAGS += -g -O0
endif

TOOLCHAIN?=/usr/bin

CFLAGS += -I$(ROOT)/src -Wall -Werror

AR=$(TOOLCHAIN)/$(CC_PREFIX)ar
RANLIB=$(TOOLCHAIN)/$(CC_PREFIX)ranlib
CC=$(TOOLCHAIN)/$(CC_PREFIX)gcc

%.o: %.c
	$(CC) $(CFLAGS) -c $<

SRC_FILES=$(wildcard *.c)
O_FILES=$(patsubst %.c,%.o,$(SRC_FILES))
TARGET=lib$(shell basename $(shell pwd)).a

$(TARGET): $(O_FILES)
	$(AR) r $@ $^
	$(RANLIB) $@

module-all: $(TARGET)

module-clean:
	rm -fr $(O_FILES) $(TARGET)

module-distclean: clean
	rm -fr depend.mak

module-depend: depend.mak

depend.mak:
	$(CC) $(CFLAGS) -M $(SRC_FILES) > $@ || rm -f $@
