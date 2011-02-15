.PHONY: all clean depend distclean

all:
	set -e; for dir in $(DIRS); do $(MAKE) -C $$dir all; done

clean:
	for dir in $(DIRS); do $(MAKE) -C $$dir clean ; done

distclean:
	for dir in $(DIRS); do $(MAKE) -C $$dir distclean ; done

depend:
	set -e; for dir in $(DIRS); do $(MAKE) -C $$dir depend; done

