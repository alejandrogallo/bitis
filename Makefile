include config.mk

.PHONY: tests

clean:
	$(MAKE) -C tests clean

tests:
	$(MAKE) -C tests all
