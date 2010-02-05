#depends on module.mak

.PHONY: app-all app-clean

LD=/usr/bin/gcc
LDFLAGS=-L$(ROOT)

app-all: $(APP)

$(APP): $(TARGETS) $(DEPS)
	$(LD) $(LDFLAGS) -o $@ $^

app-clean:
	rm -fr app

app-distclean: app-clean
