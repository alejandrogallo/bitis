include config.mk

.PHONY: tests clean

tests:
	$(MAKE) -C tests all

clean:
	$(MAKE) -C tests clean
