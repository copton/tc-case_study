#depends on module.mak for $(TARGET)

.PHONY: app-all app-clean

LD=/usr/bin/gcc
LDFLAGS += 

APP=$(shell basename $(shell pwd))

app-all: $(APP)

$(APP): $(TARGET) $(DEPS)
	$(LD) $(LDFLAGS) -o $@ $^

app-clean:
	rm -fr app
