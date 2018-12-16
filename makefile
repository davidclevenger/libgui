all: src tests
	$(MAKE) -C ./src
	$(MAKE) -C ./tests
	@echo done.

.PHONY:
clean:
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean
