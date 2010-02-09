.PHONY: module-depend module-all module-clean module-distclean

-include depend.mak

CFLAGS += -DDEBUG -g -O0

CFLAGS += -I$(ROOT)/src -Wall #-std=c99 -pedantic

AR=/usr/bin/ar
RANLIB=/usr/bin/ranlib
CC=/usr/bin/gcc

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
