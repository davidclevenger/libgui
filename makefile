all: src tests
	$(MAKE) -C ./src
	$(MAKE) -C ./tests

.PHONY:
clean:
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean
