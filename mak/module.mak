.PHONY: module-depend module-all module-clean module-distclean

-include depend.mak

CFLAGS=-I $(ROOT)/configuration

%.o: %.c
	$(CC) $(CFLAGS) -c $<

SRC_FILES=$(wildcard *.c)
TARGETS=$(patsubst %.c,%.o,$(SRC_FILES))

module-all: $(TARGETS)

module-clean:
	rm -fr $(TARGETS)

module-distclean: clean
	rm -fr depend.mak

module-depend: depend.mak

depend.mak:
	$(CC) $(CFLAGS) -M $(SRC_FILES) -o $@
