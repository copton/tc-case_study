#depends on module.mak for $(TARGET) and $(TOOLCHAIN)

.PHONY: app-all app-clean

LD=$(TOOLCHAIN)/$(CC_PREFIX)gcc
LDFLAGS += 

APP=$(shell basename $(shell pwd))

app-all: $(APP)

$(APP): $(TARGET) $(DEPS)
	$(LD) $(LDFLAGS) -o $@ $^

app-clean:
	rm -fr app
