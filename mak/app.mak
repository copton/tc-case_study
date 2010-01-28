.PHONY: app-all app-clean

#depends on module.mak

DEPS=$(ROOT)/configuration/config.o

app-all: $(APP)

$(APP): $(TARGETS) $(DEPS)
	$(CC) $(LDFLAGS) -o $@ $^

app-clean:
	rm -fr app
